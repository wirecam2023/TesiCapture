#include "stdafx.h"
#include "Endox.h"
#include "ArchiviBackupDlg.h"

#include "DLL_Imaging\h\ImgArchive.h"

#include "EsamiDoc.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CArchiviBackupDlg::CArchiviBackupDlg(CWnd* pParent, CEsamiDoc* pEsamiDoc)
	: CDialog(CArchiviBackupDlg::IDD, (CWnd*)pParent)
{
	m_pEsamiDoc = pEsamiDoc;

	m_sDescrizioneArchivio = "";
	m_sImagePath = "";
	m_sThumbPath = "";
	m_sImagePathWeb = "";
	m_sThumbPathWeb = "";

	m_lSavedPosition = -1;
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CArchiviBackupDlg::~CArchiviBackupDlg()
{
	for(POSITION pos = m_listArchivi.GetHeadPosition(); pos;)
	{
		ArchiveElement* el = (ArchiveElement*) m_listArchivi.GetNext(pos);
		delete(el);
	}
}

BEGIN_MESSAGE_MAP(CArchiviBackupDlg, CDialog)
	ON_BN_CLICKED(IDC_ARCHIVI_CANC,	 OnArchiveDelete)
	ON_BN_CLICKED(IDC_ARCHIVI_MODIFY, OnArchiveModify)
	ON_BN_CLICKED(IDC_ARCHIVI_NUOVO,  OnArchiveNew)
	ON_BN_CLICKED(IDC_ARCHIVI_REFRESH,OnArchiveRefresh)
	ON_BN_CLICKED(IDC_ARCHIVI_UPDATE, OnArchiveUpdate)

	ON_BN_CLICKED(IDC_BTN_PATH_IMM, OnBnClickedBtnPathImm)
	ON_BN_CLICKED(IDC_BTN_PATH_MIN, OnBnClickedBtnPathMin)
	ON_BN_CLICKED(IDC_BTN_PATH_PDF, OnBnClickedBtnPathPdf)
	ON_BN_CLICKED(IDC_BTN_PATH_ALLEGATI_PAZ, OnBnClickedBtnPathAllegatiPaz)
	ON_BN_CLICKED(IDC_BTN_PATH_ALLEGATI_ESA, OnBnClickedBtnPathAllegatiEsa)
	ON_BN_CLICKED(IDC_CHK_PACSATTIVO, OnBnClickedChkPacsAttivo)

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)
END_MESSAGE_MAP()

void CArchiviBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic08);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic09);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);

	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_ARCHIVI_NUOVO, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_ARCHIVI_MODIFY, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_ARCHIVI_CANC, m_ctrlButtonDel);
	DDX_Control(pDX, IDC_ARCHIVI_UPDATE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_ARCHIVI_REFRESH, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_PRIMARIO, m_ctrlPrimario);

	DDX_Control(pDX, IDC_CHK_PACSATTIVO, m_ctrlChkPacsAttivo);
	DDX_Control(pDX, IDC_CHK_PACSSINCRONIZZA, m_ctrlChkPacsSincronizza);
	DDX_Control(pDX, IDC_EDT_PACSRETRIEVEURL, m_ctrlEdtPacsRetrieveURL);

	//

	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizioneArchivio);
	DDX_Text(pDX, IDC_PATH_IMM, m_sImagePath);
	DDX_Text(pDX, IDC_PATH_MIN, m_sThumbPath);
}

BOOL CArchiviBackupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlStatic00.SetFont(&theApp.m_fontBold);
	m_ctrlStatic04.SetFont(&theApp.m_fontBold);
	m_ctrlStatic06.SetFont(&theApp.m_fontBold);
	m_ctrlStatic09.SetFont(&theApp.m_fontBold);
	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIMARIO)->EnableWindow(FALSE);

	RiempiListaArchivi();

	SetDlgItemText(IDC_PATH_PDF, theApp.m_sPercorsoPDF);
	SetDlgItemText(IDC_PATH_ALLEGATI_PAZ, theApp.m_sPercorsoAllegatiPaz);
	SetDlgItemText(IDC_PATH_ALLEGATI_ESA, theApp.m_sPercorsoAllegatiEsa);
	
	m_nItemPressed = 0;
	m_nItemCount = m_ctrlLista.GetCount();
	theApp.LocalizeDialog(this, CArchiviBackupDlg::IDD, "ArchiviBackupDlg");

	return TRUE;
}

void CArchiviBackupDlg::RiempiListaArchivi()
{
	m_ctrlLista.ResetContent();
	m_ctrlLista.SetTabStops(100);

	// recupero lista archivi //
	CImgArchive imgArchive(&theApp.m_dbEndox);
	long lArchiveNum = imgArchive.GetArchivesNumber(TRUE);
	CImgArchive::tagARCHIVEINFO* pArchiveInfo = new CImgArchive::tagARCHIVEINFO[lArchiveNum];

	if (imgArchive.GetArchivesInfo(pArchiveInfo, TRUE))
	{
		for (int i = 0; i < lArchiveNum; i++)
		{
			if (!pArchiveInfo[i].bPacs)
			{
				int posiz = m_ctrlLista.AddString(pArchiveInfo[i].szDescription);

				if (posiz >= 0)
					m_ctrlLista.SetItemData(posiz, (DWORD)pArchiveInfo[i].lID);

				ArchiveElement* tempElement = new ArchiveElement;
				tempElement->sDescrizione = pArchiveInfo[i].szDescription;
				tempElement->lIDArchivio = pArchiveInfo[i].lID;
				tempElement->sPathImage = pArchiveInfo[i].szPathImage;
				tempElement->sPathThumb = pArchiveInfo[i].szPathThumb;
				tempElement->sPathImageWeb = pArchiveInfo[i].szPathImageWeb;
				tempElement->sPathThumbWeb = pArchiveInfo[i].szPathThumbWeb;
				tempElement->bPrimario = pArchiveInfo[i].bPrimary;
				m_listArchivi.AddTail(tempElement);
			}
			else
			{
				// Sandro 05/06/2015 // archivio PACS //

				m_ctrlChkPacsAttivo.SetCheck(BST_CHECKED);

				m_ctrlEdtPacsRetrieveURL.SetReadOnly(FALSE);
				m_ctrlEdtPacsRetrieveURL.SetWindowText(pArchiveInfo[i].szServerDicomRetrieveUrl);

				m_ctrlChkPacsSincronizza.EnableWindow(TRUE);
				m_ctrlChkPacsSincronizza.SetCheck(pArchiveInfo[i].bPacsToBeAligned ? BST_CHECKED : BST_UNCHECKED);
			}
		}
	}

	delete(pArchiveInfo);

	OnSelchangeLista();
}

void CArchiviBackupDlg::OnLbnDblclkLista()
{
	OnOK();
}

void CArchiviBackupDlg::OnSelchangeLista() 
{
	CString strDoctor, strTmp;

	if (m_bAddNew || m_bModify)
		return;

	int nCount = m_ctrlLista.GetCount();

	if (nCount > 0)
	{
		int nCurPos = m_ctrlLista.GetCurSel();

		if (nCurPos >= 0)
		{
			// recupera il codice dell'archivio appena selezionato
			DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);

			GetDlgItem(IDC_ARCHIVI_NUOVO)->EnableWindow(TRUE);
			GetDlgItem(IDC_ARCHIVI_MODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_ARCHIVI_CANC)->EnableWindow(TRUE);
			GetDlgItem(IDC_ARCHIVI_UPDATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_ARCHIVI_REFRESH)->EnableWindow(FALSE);

			if (dwCode >= 0)
			{
				ArchiveElement* el;

				for(POSITION pos = m_listArchivi.GetHeadPosition(); pos;)
				{
					el = (ArchiveElement*) m_listArchivi.GetNext(pos);
					if (el->lIDArchivio == dwCode)
						break;
				}
				
				if (el != NULL)
				{
					m_sDescrizioneArchivio = el->sDescrizione;
					m_sImagePath = el->sPathImage;
					m_sThumbPath = el->sPathThumb;
					m_sImagePathWeb = el->sPathImageWeb;
					m_sThumbPathWeb = el->sPathThumbWeb;
					m_lID = el->lIDArchivio;
					m_ctrlPrimario.SetCheck(el->bPrimario);
				}

				UpdateData(FALSE);
			}
		}
	}
}

void CArchiviBackupDlg::OnOK()
{
	UpdateData(FALSE);

	// Sandro 05/06/2015 // archivio PACS //

	if (m_ctrlChkPacsAttivo.GetCheck() == BST_CHECKED)
	{
		CString sServerDicomRetrieveUrl;
		m_ctrlEdtPacsRetrieveURL.GetWindowText(sServerDicomRetrieveUrl);
		sServerDicomRetrieveUrl.Trim();

		if (sServerDicomRetrieveUrl.IsEmpty())
		{
			theApp.AfxMessageBoxEndo(IDS_RETRIEVEURL_VUOTA);
			return;
		}

		CImgArchive(&theApp.m_dbEndox).AddEditPacsArchive(m_ctrlChkPacsSincronizza.GetCheck() == BST_CHECKED, sServerDicomRetrieveUrl);
	}
	else
	{
		CImgArchive(&theApp.m_dbEndox).DeletePacsArchive();
	}

	//

	GetDlgItemText(IDC_PATH_PDF, theApp.m_sPercorsoPDF);
	GetDlgItemText(IDC_PATH_ALLEGATI_PAZ, theApp.m_sPercorsoAllegatiPaz);
	GetDlgItemText(IDC_PATH_ALLEGATI_ESA, theApp.m_sPercorsoAllegatiEsa);

	long tempUO = theApp.m_lUO;
	theApp.m_lUO = 0;
	m_pEsamiDoc->SetStringValue("Percorso allegati paziente", theApp.m_sPercorsoAllegatiPaz);
	theApp.m_lUO = tempUO;

	m_pEsamiDoc->SetStringValue("Percorso allegati esame", theApp.m_sPercorsoAllegatiEsa);
	m_pEsamiDoc->SetStringValue("Percorso PDF", theApp.m_sPercorsoPDF);

	//

	CDialog::OnOK();
}

void CArchiviBackupDlg::OnArchiveDelete() 
{
	BOOL	bDeleted = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIMARIO)->EnableWindow(FALSE);

	GetDlgItem(IDC_ARCHIVI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARCHIVI_REFRESH)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		int posiz = m_ctrlLista.GetCurSel();
		if (posiz >= 0)
		{
			DWORD dwCode = m_ctrlLista.GetItemData(posiz);
		
			if (dwCode >= 0)
			{
				CImgArchive imgArchive(&theApp.m_dbEndox);
				if (imgArchive.DeleteNonPacsArchive(dwCode))
				{
					UpdateData(FALSE);

					RiempiListaArchivi();

					OnSelchangeLista();
				}
			}
		}
	}
}

void CArchiviBackupDlg::OnArchiveModify() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDC_LISTA)	->EnableWindow(FALSE);
		GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(TRUE);
		GetDlgItem(IDC_PATH_IMM)->EnableWindow(TRUE);
		GetDlgItem(IDC_PATH_MIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PATH_IMM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PATH_MIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_PRIMARIO)->EnableWindow(TRUE);

		GetDlgItem(IDC_ARCHIVI_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARCHIVI_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARCHIVI_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARCHIVI_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_ARCHIVI_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		m_bModify = TRUE;

		GetDlgItem(IDC_DESCRIZIONE)->SetFocus();

		UpdateData(FALSE);
	}			
}

void CArchiviBackupDlg::OnArchiveNew() 
{
	GetDlgItem(IDC_LISTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_PATH_IMM)->EnableWindow(TRUE);
	GetDlgItem(IDC_PATH_MIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PATH_IMM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PATH_MIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRIMARIO)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_ARCHIVI_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARCHIVI_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARCHIVI_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARCHIVI_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_sDescrizioneArchivio.Empty();
	m_sImagePath.Empty();
	m_sThumbPath.Empty();
	m_sImagePathWeb.Empty();
	m_sThumbPathWeb.Empty();
	m_ctrlPrimario.SetCheck(BST_UNCHECKED);

	m_bAddNew = TRUE;

	GetDlgItem(IDC_DESCRIZIONE)->SetFocus();

	UpdateData(FALSE);
}

void CArchiviBackupDlg::OnArchiveRefresh() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIMARIO)->EnableWindow(FALSE);

	GetDlgItem(IDC_ARCHIVI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARCHIVI_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	if (m_lSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_lSavedPosition;

		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;
	
		m_lSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}
}

void CArchiviBackupDlg::OnArchiveUpdate() 
{
	UpdateData(TRUE);

	if (m_sDescrizioneArchivio.IsEmpty() || m_sImagePath.IsEmpty() || m_sThumbPath.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ARCHIVIBACKUPDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		long lIDArchivio = CImgArchive(&theApp.m_dbEndox).AddNonPacsArchive(m_sDescrizioneArchivio, m_sImagePath, m_sThumbPath, m_sImagePathWeb, m_sThumbPathWeb, m_ctrlPrimario.GetCheck() == BST_CHECKED, 0);
		if (lIDArchivio > 0)
		{
			ArchiveElement* tempElement = new ArchiveElement;
			tempElement->lIDArchivio = lIDArchivio;
			tempElement->sDescrizione = m_sDescrizioneArchivio;
			tempElement->sPathImage = m_sImagePath;
			tempElement->sPathThumb = m_sThumbPath;
			tempElement->sPathImageWeb = m_sImagePathWeb;
			tempElement->sPathThumbWeb = m_sThumbPathWeb;
			tempElement->bPrimario = m_ctrlPrimario.GetCheck() == BST_CHECKED;

			if (tempElement->bPrimario)
			{
				// è stato scelto un nuovo primario, bisogna resettare gli altri primari della lista //
				for (POSITION pos = m_listArchivi.GetHeadPosition(); pos; )
				{
					ArchiveElement* el = (ArchiveElement*)m_listArchivi.GetNext(pos);
					el->bPrimario = FALSE;
				}
			}

			m_listArchivi.AddTail(tempElement);

			//

			int nPosiz = m_ctrlLista.AddString(m_sDescrizioneArchivio);
			if (nPosiz >= 0)
			{
				m_ctrlLista.SetItemData(nPosiz, (DWORD)lIDArchivio);
				m_ctrlLista.SetCurSel(nPosiz);
			}
		}
	}
	else		
	{
		if (CImgArchive(&theApp.m_dbEndox).EditNonPacsArchive(m_lID, m_sDescrizioneArchivio, m_sImagePath, m_sThumbPath, m_sImagePathWeb, m_sThumbPathWeb, m_ctrlPrimario.GetCheck() == BST_CHECKED, 0))
		{
			if (m_ctrlPrimario.GetCheck() == BST_CHECKED)
			{
				// è stato scelto un nuovo primario, bisogna resettare gli altri primari della lista //
				for (POSITION pos = m_listArchivi.GetHeadPosition(); pos;)
				{
					ArchiveElement* el = (ArchiveElement*)m_listArchivi.GetNext(pos);
					el->bPrimario = FALSE;
				}
			}

			// riporto le modifiche sull'elemento della lista //
			for (POSITION pos = m_listArchivi.GetHeadPosition(); pos;)
			{
				ArchiveElement* tempElement = (ArchiveElement*)m_listArchivi.GetNext(pos);
				if (tempElement->lIDArchivio == m_lID)
				{
					tempElement->sDescrizione = m_sDescrizioneArchivio;
					tempElement->sPathImage = m_sImagePath;
					tempElement->sPathThumb = m_sThumbPath;
					tempElement->sPathImageWeb = m_sImagePathWeb;
					tempElement->sPathThumbWeb = m_sThumbPathWeb;
					tempElement->bPrimario = m_ctrlPrimario.GetCheck() == BST_CHECKED;

					break;
				}
			}

			//
			int nPosiz = m_ctrlLista.GetCurSel();
			if (nPosiz >= 0)
			{
				m_ctrlLista.DeleteString(nPosiz);

				nPosiz = m_ctrlLista.InsertString(nPosiz, m_sDescrizioneArchivio);
				if (nPosiz >= 0)
				{
					m_ctrlLista.SetItemData(nPosiz, (DWORD)m_lID);
					m_ctrlLista.SetCurSel(nPosiz);
				}
			}
		}
	}
	
	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_IMM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PATH_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRIMARIO)->EnableWindow(FALSE);

	GetDlgItem(IDC_ARCHIVI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARCHIVI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARCHIVI_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	m_bModify = FALSE;
	m_bAddNew = FALSE;

	OnSelchangeLista();
}

void CArchiviBackupDlg::OnBnClickedBtnPathImm()
{
	CString strTemp;
	GetDlgItemText(IDC_PATH_IMM, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_9);
	CFolderDialog dlg(strTitle, strTemp, 64, this);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_PATH_IMM, dlg.GetSelectedFolder());
}

void CArchiviBackupDlg::OnBnClickedBtnPathMin()
{
	CString strTemp;
	GetDlgItemText(IDC_PATH_MIN, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_10);
	CFolderDialog dlg(strTitle, strTemp, 64, this);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_PATH_MIN, dlg.GetSelectedFolder());
}

void CArchiviBackupDlg::OnBnClickedBtnPathPdf()
{
	CString strTemp;
	GetDlgItemText(IDC_PATH_PDF, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_11);
	CFolderDialog dlg(strTitle, strTemp, 64, this);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_PATH_PDF, dlg.GetSelectedFolder());
}

void CArchiviBackupDlg::OnBnClickedBtnPathAllegatiPaz()
{
	CString strTemp;
	GetDlgItemText(IDC_PATH_ALLEGATI_PAZ, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_13);
	CFolderDialog dlg(strTitle, strTemp, 64, this);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_PATH_ALLEGATI_PAZ, dlg.GetSelectedFolder());
}

void CArchiviBackupDlg::OnBnClickedBtnPathAllegatiEsa()
{
	CString strTemp;
	GetDlgItemText(IDC_PATH_ALLEGATI_ESA, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_14);
	CFolderDialog dlg(strTitle, strTemp, 64, this);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_PATH_ALLEGATI_ESA, dlg.GetSelectedFolder());
}

void CArchiviBackupDlg::OnBnClickedChkPacsAttivo()
{
	m_ctrlEdtPacsRetrieveURL.SetReadOnly(m_ctrlChkPacsAttivo.GetCheck() != BST_CHECKED);
	m_ctrlChkPacsSincronizza.EnableWindow(m_ctrlChkPacsAttivo.GetCheck() == BST_CHECKED);
}
