#include "stdafx.h"
#include "Endox.h"
#include "AlbumConfrontoDlg.h"

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\ImgManager.h"

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "ObSelect.h"
#include "PazientiSet.h"
#include "PuntiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAlbumConfrontoDlg::CAlbumConfrontoDlg(CWnd* pParent /*=NULL*/, CEsamiView* pEsamiView /*=NULL*/)
	: CEndoxResizableDlg(CAlbumConfrontoDlg::IDD, pParent)
{
	m_nDiapoPerEsame = DUE_IMMAGINI;

	m_pEsamiView	= pEsamiView;

	for(int i = 0; i < 2; i++)
		for(int j = 0; j < SEI_IMMAGINI; j++)
			m_pFileBmp[i][j] = NULL;
}

CAlbumConfrontoDlg::~CAlbumConfrontoDlg()
{
	CFileBmp::DeleteListSelected(GLOBAL_IMAGES);
	
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<SEI_IMMAGINI; j++)
		{
			if (m_pFileBmp[i][j])
			{
				::DestroyWindow(m_pFileBmp[i][j]->GetSafeHwnd());
				delete m_pFileBmp[i][j];
				m_pFileBmp[i][j] = NULL;
			}
		}
	}

	POSITION pos;

	pos = m_ImgListOrgani[0].GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani[0].GetAt(pos).img.hBmp);
		
		m_ImgListOrgani[0].GetNext(pos);
	}
	m_ImgListOrgani[0].RemoveAll();

	pos = m_ImgListOrgani[1].GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani[1].GetAt(pos).img.hBmp);
		
		m_ImgListOrgani[1].GetNext(pos);
	}
	m_ImgListOrgani[1].RemoveAll();

	m_setEsami[0].CloseRecordset("CAlbumConfrontoDlg::~CAlbumConfrontoDlg");
	m_setEsami[1].CloseRecordset("CAlbumConfrontoDlg::~CAlbumConfrontoDlg");
}


void CAlbumConfrontoDlg::DoDataExchange(CDataExchange* pDX)
{
	int nFlag = 0;

	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL_PAZIENTE_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_08, m_ctrlStatic08);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	if (m_pEsamiView->m_pPazientiSet->IsOpen())
	{
		DDX_FieldText (pDX, IDC_PAZIENTE_FISC,		m_pEsamiView->m_pPazientiSet->m_sCodFisc,	m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_PAZIENTE_SANIT,		m_pEsamiView->m_pPazientiSet->m_sCodSanit,	m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_PAZIENTE_COGNOME,	m_pEsamiView->m_pPazientiSet->m_sCognome,	m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_PAZIENTE_NOME,		m_pEsamiView->m_pPazientiSet->m_sNome,		m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldDate (pDX, IDC_PAZIENTE_NATOIL,	m_pEsamiView->m_pPazientiSet->m_lNatoIlCustom, m_pEsamiView->m_pPazientiSet);

		if (m_pEsamiView->m_pPazientiSet->IsFieldNull(&m_pEsamiView->m_pPazientiSet->m_lSessoPaz) == FALSE)
		{
			switch (m_pEsamiView->m_pPazientiSet->m_lSessoPaz)
			{
			case -1:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
				break;
			case 0:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_MALE));
				break;
			case 1:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE));
				break;
			case 2:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS));
				break;
			case 3:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE));
				break;
			case 4:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER));
				break;
			default:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
				break;
			}
		}
		else
			SetDlgItemText(IDC_PAZIENTE_SESSO, "");
	}

	DDX_Control(pDX, IDC_COMBO1, m_ctrlCombo[0]);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlCombo[1]);
}


BEGIN_MESSAGE_MAP(CAlbumConfrontoDlg, CEndoxResizableDlg)
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_IMM_FIRST_1, OnImmFirst1)
	ON_BN_CLICKED(IDC_IMM_FIRST_2, OnImmFirst2)
	ON_BN_CLICKED(IDC_IMM_LAST_1, OnImmLast1)
	ON_BN_CLICKED(IDC_IMM_LAST_2, OnImmLast2)
	ON_BN_CLICKED(IDC_IMM_NEXT_1, OnImmNext1)
	ON_BN_CLICKED(IDC_IMM_NEXT_2, OnImmNext2)
	ON_BN_CLICKED(IDC_IMM_PREV_1, OnImmPrev1)
	ON_BN_CLICKED(IDC_IMM_PREV_2, OnImmPrev2)
	ON_BN_CLICKED(IDC_CHANGE_VIEW, OnChangeView)
	ON_BN_CLICKED(IDC_PRINT_IMAGES, OnPrintImages)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
END_MESSAGE_MAP()

BOOL CAlbumConfrontoDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	m_BtnImmFirst[0].AutoLoad(IDC_IMM_FIRST_1,	this);
	m_BtnImmPrev[0]. AutoLoad(IDC_IMM_PREV_1,	this);
	m_BtnImmNext[0]. AutoLoad(IDC_IMM_NEXT_1,	this);
	m_BtnImmLast[0]. AutoLoad(IDC_IMM_LAST_1,	this);
	m_BtnImmFirst[1].AutoLoad(IDC_IMM_FIRST_2,	this);
	m_BtnImmPrev[1]. AutoLoad(IDC_IMM_PREV_2,	this);
	m_BtnImmNext[1]. AutoLoad(IDC_IMM_NEXT_2,	this);
	m_BtnImmLast[1]. AutoLoad(IDC_IMM_LAST_2,	this);
	m_BtnChangeView. AutoLoad(IDC_CHANGE_VIEW,	this);
	m_BtnPrintImages.AutoLoad(IDC_PRINT_IMAGES, this);

	CFileBmp::DeleteListSelected(GLOBAL_IMAGES);
	
	for(int i = 0; i < 2; i++)
	{
		int nIndex = 0;
		CString strTemp;
		CCustomDate dateTemp;

		m_setEsami[i].SetOpenFilter(m_pEsamiView->m_pEsamiSet->GetBaseFilter(TRUE));
		m_setEsami[i].SetSortRecord("Data, Contatore");

		if (m_setEsami[i].OpenRecordset("CAlbumConfrontoDlg::OnInitDialog"))
		{
			while(m_setEsami[i].IsEOF() == FALSE)
			{
				dateTemp.SetDate(m_setEsami[i].m_lData);

				strTemp.Format("%d° %s %s", nIndex + 1, theApp.GetMessageString(IDS_ESAME_DEL), dateTemp.GetDate("%d/%m/%Y"));
				m_ctrlCombo[i].InsertString(nIndex, strTemp);
				m_ctrlCombo[i].SetItemData(nIndex, (DWORD)m_setEsami[i].m_lContatore);

				nIndex++;
				m_setEsami[i].MoveNext();
			}
			m_nMaxEsami[i] = nIndex;
			m_setEsami[i].CloseRecordset("CAlbumConfrontoDlg::OnInitDialog");
		}

		if (m_setEsami[i].OpenRecordset("CAlbumConfrontoDlg::OnInitDialog"))
		{
			if (!m_setEsami[i].IsEOF())
				m_setEsami[i].MoveLast();
		}

		m_nEsamePage[i] = m_nMaxEsami[i];
	}

	AddAnchor(IDC_LABEL_PAZIENTE_01, CSize(0, 0), CSize(11, 0));
	AddAnchor(IDC_LABEL_PAZIENTE_02, CSize(0, 0), CSize(11, 0));
	AddAnchor(IDC_PAZIENTE_FISC, CSize(11, 0), CSize(33, 0));
	AddAnchor(IDC_PAZIENTE_SANIT, CSize(11, 0), CSize(33, 0));

	AddAnchor(IDC_LABEL_PAZIENTE_03, CSize(33, 0), CSize(44, 0));
	AddAnchor(IDC_LABEL_PAZIENTE_04, CSize(33, 0), CSize(44, 0));
	AddAnchor(IDC_PAZIENTE_COGNOME, CSize(44, 0), CSize(66, 0));
	AddAnchor(IDC_PAZIENTE_NOME, CSize(44, 0), CSize(66, 0));

	AddAnchor(IDC_LABEL_PAZIENTE_05, CSize(66, 0), CSize(77, 0));
	AddAnchor(IDC_LABEL_PAZIENTE_08, CSize(66, 0), CSize(77, 0));
	AddAnchor(IDC_PAZIENTE_SESSO, CSize(77, 0), CSize(100, 0));
	AddAnchor(IDC_PAZIENTE_NATOIL, CSize(77, 0), CSize(100, 0));

	AddAnchor(IDC_STATIC_LINE1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_COMBO1, CSize(25, 0), CSize(25, 0));
	AddAnchor(IDC_FRAME_SMALL1_1, CSize(0, 1), CSize(25, 34));
	AddAnchor(IDC_FRAME_SMALL2_1, CSize(25, 1), CSize(50, 34));
	AddAnchor(IDC_FRAME_SMALL3_1, CSize(0, 34), CSize(25, 67));
	AddAnchor(IDC_FRAME_SMALL4_1, CSize(25, 34), CSize(50, 67));
	AddAnchor(IDC_FRAME_SMALL5_1, CSize(0, 67), CSize(25, 100));
	AddAnchor(IDC_FRAME_SMALL6_1, CSize(25, 67), CSize(50, 100));
	AddAnchor(IDC_FRAME_LARGE_1, CSize(0, 0), CSize(50, 50));
	AddAnchor(IDC_FRAME_LARGE_2, CSize(0, 50), CSize(50, 100));
	AddAnchor(IDC_IMM_FIRST_1, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_IMM_PREV_1, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_IMM_NEXT_1, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_IMM_LAST_1, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_STATIC_LINE3, CSize(50, 0), CSize(50, 100));
	AddAnchor(IDC_IMM_FIRST_2, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_IMM_PREV_2, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_IMM_NEXT_2, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_IMM_LAST_2, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_COMBO2, CSize(75, 0), CSize(75, 0));
	AddAnchor(IDC_FRAME_SMALL1_2, CSize(50, 1), CSize(75, 34));
	AddAnchor(IDC_FRAME_SMALL2_2, CSize(75, 1), CSize(100, 34));
	AddAnchor(IDC_FRAME_SMALL3_2, CSize(50, 34), CSize(75, 67));
	AddAnchor(IDC_FRAME_SMALL4_2, CSize(75, 34), CSize(100, 67));
	AddAnchor(IDC_FRAME_SMALL5_2, CSize(50, 67), CSize(75, 100));
	AddAnchor(IDC_FRAME_SMALL6_2, CSize(75, 67), CSize(100, 100));
	AddAnchor(IDC_FRAME_LARGE_3, CSize(50, 0), CSize(100, 50));
	AddAnchor(IDC_FRAME_LARGE_4, CSize(50, 50), CSize(100, 100));
	AddAnchor(IDC_STATIC_LINE2, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_CHANGE_VIEW, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_PRINT_IMAGES, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	GetDlgItem(IDC_PAZIENTE_FISC)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_SANIT)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_COGNOME)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_NOME)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_NATOIL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_SESSO)->SetFont(&theApp.m_fontBold, TRUE);

	m_BtnPrintImages.EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::printout ? TRUE : FALSE);

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	OnChangeView();

	theApp.LocalizeDialog(this, CAlbumConfrontoDlg::IDD, "AlbumConfrontoDlg");

	int nTemp;

	nTemp = m_ctrlCombo[0].GetCount();
	if (nTemp > 0)
		m_ctrlCombo[0].SetCurSel(max(nTemp - 1, 0));
	EsamiMove(0);

	nTemp = m_ctrlCombo[1].GetCount();
	if (nTemp > 0)
		m_ctrlCombo[1].SetCurSel(max(nTemp - 2, 0));
	EsamiMove(1);

	return TRUE;
}

void CAlbumConfrontoDlg::ResetVetDiapo(BOOL bReposition , int nEsame)
{   
	POSITION pos = m_ImgListOrgani[nEsame].GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani[nEsame].GetAt(pos).img.hBmp);
		
		m_ImgListOrgani[nEsame].GetNext(pos);
	}
	m_ImgListOrgani[nEsame].RemoveAll();

	if (bReposition)
	{
		m_nMaxDiapo[nEsame] = 0;
		m_nDiapoPage[nEsame] = -1;
	}
}  	

int CAlbumConfrontoDlg::FillDiapoIndex(int nEsame) 
{
	int nImages;
	CImgList listImg;

	BeginWaitCursor();
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore);

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg);
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore, nImages, "CAlbumConfrontoDlg::FillDiapoIndex");

	m_ImgListOrgani[nEsame] = listImg;
	CaricaPunti(nEsame);
	EndWaitCursor();

	return nImages;
}

void CAlbumConfrontoDlg::MoveImage(int nEsame)
{
	int nBase = m_nDiapoPage[nEsame] * m_nDiapoPerEsame; 

	m_BtnImmFirst[nEsame].EnableWindow(m_nDiapoPage[nEsame] > 0);
	m_BtnImmPrev[nEsame].EnableWindow(m_nDiapoPage[nEsame] > 0);
	m_BtnImmNext[nEsame].EnableWindow(m_nDiapoPage[nEsame] < (m_nMaxDiapo[nEsame] / m_nDiapoPerEsame));
	m_BtnImmLast[nEsame].EnableWindow(m_nDiapoPage[nEsame] < (m_nMaxDiapo[nEsame] / m_nDiapoPerEsame));

	if (m_setEsami[nEsame].IsEOF())
	{
		for(int i = 0; i < m_nDiapoPerEsame; i++)
			m_pFileBmp[nEsame][i]->ResetImage();

		return;	
	}

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore);
	
	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);
	for(int i = 0; i < m_nDiapoPerEsame; i++)
	{
		if (nBase + i < m_nMaxDiapo[nEsame])
		{

			if (m_nDiapoPerEsame != SEI_IMMAGINI)
			{
				if (bConfirmed == FALSE)
				{
					if (m_pFileBmp[nEsame][i]->LoadImage(m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore, &m_ImgListOrgani[nEsame], nBase + i, bConfirmed, strDvdLabel, CARICA_IMM) == FALSE)
						m_pFileBmp[nEsame][i]->LoadImage(m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore, &m_ImgListOrgani[nEsame], nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);
				}
				else
				{
					BOOL bDvd = TRUE;

					while(GetVolumeName() != strDvdLabel)
					{
						CEspelliDlg	dlg(this, strDvdLabel);

						if (dlg.DoModal() == IDCANCEL)
						{
							m_pFileBmp[nEsame][i]->LoadImage(m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore, &m_ImgListOrgani[nEsame], nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);
							bDvd = FALSE;
							break;
						}
					}

					if (bDvd == TRUE)
						m_pFileBmp[nEsame][i]->LoadImage(m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore, &m_ImgListOrgani[nEsame], nBase + i, bConfirmed, strDvdLabel, CARICA_IMM);
				}
			}
			else
			{
				m_pFileBmp[nEsame][i]->LoadImage(m_setEsami[nEsame].m_lPaziente, m_setEsami[nEsame].m_lContatore, &m_ImgListOrgani[nEsame], nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);
			}

			CFileBmp::ReselectBmp(m_pFileBmp[nEsame][i], FALSE);
		}
		else
		{
			m_pFileBmp[nEsame][i]->ResetImage();
		}
	}
}

void CAlbumConfrontoDlg::EsamiMove(int nEsame) 
{
	if (!m_setEsami[nEsame].IsEOF() && !m_setEsami[nEsame].IsBOF())
	{
		int nIndex = m_ctrlCombo[nEsame].GetCurSel();
		long lContatore = (long)m_ctrlCombo[nEsame].GetItemData(nIndex);

		m_nEsamePage[nEsame] = 1;
		m_setEsami[nEsame].MoveFirst();
		while(m_setEsami[nEsame].m_lContatore != lContatore)
		{
			m_nEsamePage[nEsame]++;
			m_setEsami[nEsame].MoveNext();
		}

		ResetVetDiapo(TRUE, nEsame);

		m_nMaxDiapo[nEsame] = FillDiapoIndex(nEsame);

		m_nDiapoPage[nEsame] = 0;

		MoveImage(nEsame);

		UpdateData(FALSE);
	}	
}

void CAlbumConfrontoDlg::OnImmFirst1() 
{
    if (m_nDiapoPage[0] == 0)
    	return;

    m_nDiapoPage[0] = 0;
	MoveImage(0);
}

void CAlbumConfrontoDlg::OnImmLast1() 
{
	if (m_nDiapoPage[0] == (m_nMaxDiapo[0] / m_nDiapoPerEsame))
		return;

	m_nDiapoPage[0] = m_nMaxDiapo[0] / m_nDiapoPerEsame;
	MoveImage(0);
}

void CAlbumConfrontoDlg::OnImmNext1() 
{
	if (m_nDiapoPage[0] == (m_nMaxDiapo[0] / m_nDiapoPerEsame))
		return;

	m_nDiapoPage[0]++;
	MoveImage(0);
}

void CAlbumConfrontoDlg::OnImmPrev1() 
{
    if (m_nDiapoPage[0] == 0)
    	return;

    m_nDiapoPage[0]--;
	MoveImage(0);
}

void CAlbumConfrontoDlg::OnImmFirst2() 
{
    if (m_nDiapoPage[1] == 0)
    	return;

    m_nDiapoPage[1] = 0;
	MoveImage(1);
}

void CAlbumConfrontoDlg::OnImmLast2() 
{
	if (m_nDiapoPage[1] == (m_nMaxDiapo[1] / m_nDiapoPerEsame))
		return;

	m_nDiapoPage[1] = m_nMaxDiapo[1] / m_nDiapoPerEsame;
	MoveImage(1);
}

void CAlbumConfrontoDlg::OnImmNext2() 
{
	if (m_nDiapoPage[1] == (m_nMaxDiapo[1] / m_nDiapoPerEsame))
		return;

	m_nDiapoPage[1]++;
	MoveImage(1);
}

void CAlbumConfrontoDlg::OnImmPrev2() 
{
    if (m_nDiapoPage[1] == 0)
    	return;

    m_nDiapoPage[1]--;
	MoveImage(1);
}

void CAlbumConfrontoDlg::OnChangeView() 
{
	CString strTitle;

	if (m_nDiapoPerEsame == SEI_IMMAGINI)
	{
		m_nDiapoPerEsame = DUE_IMMAGINI;
		strTitle = "AlbumC_";
	}
	else
	{
		m_nDiapoPerEsame = SEI_IMMAGINI;
		strTitle = "Alb1_";
	}

	m_BtnChangeView.SetWindowText(strTitle);
	m_BtnChangeView.LoadBitmaps(strTitle + "U", strTitle + "D", strTitle + "F", strTitle + "X");
	m_BtnChangeView.SizeToContent();
	m_BtnChangeView.Invalidate();

	for(int i = 0; i < 2; i++)
	{
		ResetVetDiapo(TRUE , i);

		for(int j = 0; j < SEI_IMMAGINI; j++)
		{
			if (m_pFileBmp[i][j])
			{
				::DestroyWindow(m_pFileBmp[i][j]->GetSafeHwnd());
				delete m_pFileBmp[i][j];
				m_pFileBmp[i][j] = NULL;
			}
		}
	}

	CWnd* pBmpFrame[2][SEI_IMMAGINI];
	
	if (m_nDiapoPerEsame == SEI_IMMAGINI)
	{
		GetDlgItem(IDC_FRAME_LARGE_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_LARGE_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_LARGE_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_LARGE_4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_FRAME_SMALL1_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL2_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL3_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL4_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL5_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL6_1)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_FRAME_SMALL1_2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL2_2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL3_2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL4_2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL5_2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL6_2)->ShowWindow(SW_SHOW);

		pBmpFrame[0][0] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL1_1);
		pBmpFrame[0][1] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL2_1);
		pBmpFrame[0][2] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL3_1);
		pBmpFrame[0][3] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL4_1);
		pBmpFrame[0][4] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL5_1);
		pBmpFrame[0][5] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL6_1);
		
		pBmpFrame[1][0] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL1_2);
		pBmpFrame[1][1] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL2_2);
		pBmpFrame[1][2] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL3_2);
		pBmpFrame[1][3] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL4_2);
		pBmpFrame[1][4] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL5_2);
		pBmpFrame[1][5] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL6_2);
	}
	else
	{
		GetDlgItem(IDC_FRAME_SMALL1_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL2_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL3_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL4_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL5_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL6_1)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_FRAME_SMALL1_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL2_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL3_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL4_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL5_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL6_2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_FRAME_LARGE_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_LARGE_2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_LARGE_3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_LARGE_4)->ShowWindow(SW_SHOW);

		pBmpFrame[0][0] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE_1);
		pBmpFrame[0][1] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE_2);
		pBmpFrame[0][2] = NULL;
		pBmpFrame[0][3] = NULL;
		
		pBmpFrame[1][0] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE_3);
		pBmpFrame[1][1] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE_4);
		pBmpFrame[1][2] = NULL;
		pBmpFrame[1][3] = NULL;
	}

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < m_nDiapoPerEsame; j++)
		{
			if (pBmpFrame[i][j])
			{
				if (CFileBmp::CreateBmp(m_pEsamiView, this, pBmpFrame[i][j], &m_pFileBmp[i][j]))
				{
					m_pFileBmp[i][j]->SetMouseMode(BMP_L_NORMALMODE, BMP_R_NORMALMODE);
					m_pFileBmp[i][j]->SetAlbumType(TRUE); 
					m_pFileBmp[i][j]->ShowWindow(TRUE);
				}
			}
		}
	}

	for(int i = 0; i < 2; i++)
	{
		m_nMaxDiapo[i] = FillDiapoIndex(i);

		m_nDiapoPage[i] = 0;

		MoveImage(i);
	}
}

void CAlbumConfrontoDlg::OnPrintImages() 
{
	m_pEsamiView->AnteprimaStampaImmagini(STAMPA, GLOBAL_IMAGES, 1);

	EsamiMove(0);
	EsamiMove(1);
}

void CAlbumConfrontoDlg::OnSize(UINT nType, int cx, int cy) 
{
	int i;

	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (m_nDiapoPerEsame == DUE_IMMAGINI)
	{
		for(i = 0; i < DUE_IMMAGINI; i++)
		{
			if (m_pFileBmp[0][i] != NULL)
				m_pFileBmp[0][i]->SendMessage(EPM_RESIZE_FORM);
			if (m_pFileBmp[1][i] != NULL)
				m_pFileBmp[1][i]->SendMessage(EPM_RESIZE_FORM);
		}
	}
	else
	{
		for(i = 0; i < SEI_IMMAGINI; i++)
		{
			if (m_pFileBmp[0][i] != NULL)
				m_pFileBmp[0][i]->SendMessage(EPM_RESIZE_FORM);
			if (m_pFileBmp[1][i] != NULL)
				m_pFileBmp[1][i]->SendMessage(EPM_RESIZE_FORM);
		}
	}
}

void CAlbumConfrontoDlg::OnCbnSelchangeCombo1()
{
	EsamiMove(0);
}

void CAlbumConfrontoDlg::OnCbnSelchangeCombo2()
{
	EsamiMove(1);
}

void CAlbumConfrontoDlg::CaricaPunti(int nEsame)
{
	long lIdPunto;
	long lIdOrgano;
	long lX;
	long lY;
	IMG_ORGANI img_organi;

	BOOL bFindIndex;

	POSITION pos1 = m_ImgListOrgani[nEsame].GetHeadPosition();
	POSITION pos2;

	listPunti[nEsame].RemoveAll();
	while(pos1 != NULL)
	{
		lIdPunto = CImmaginiPuntiSet().GetIDPunto(m_ImgListOrgani[nEsame].GetAt(pos1).img.lID);
		if (lIdPunto > 0)
		{
			if (CPuntiSet().GetDatiPunto(lIdPunto, lIdOrgano, lX, lY) == TRUE)
			{
				img_organi = m_ImgListOrgani[nEsame].GetAt(pos1);
				img_organi.iPunto = 0;

				bFindIndex = FALSE;
				pos2 = listPunti[nEsame].GetHeadPosition();
				while(pos2 != NULL)
				{
					if (listPunti[nEsame].GetAt(pos2).lIdOrgano == lIdOrgano)
					{
						if ((lX == listPunti[nEsame].GetAt(pos2).lX) && (lY == listPunti[nEsame].GetAt(pos2).lY))
						{
							bFindIndex = TRUE;
							break;
						}
					}

					listPunti[nEsame].GetNext(pos2);
					img_organi.iPunto++;
				}

				if (bFindIndex == FALSE)
				{
					tagPunti puntoTemp;

					puntoTemp.lIdPunto = lIdPunto;
					puntoTemp.lIdOrgano = lIdOrgano;
					puntoTemp.lX = lX;
					puntoTemp.lY = lY;

					listPunti[nEsame].AddTail(puntoTemp);

					img_organi.iPunto = listPunti[nEsame].GetCount() - 1;
				}

				m_ImgListOrgani[nEsame].SetAt(pos1, img_organi);
			}
		}
		m_ImgListOrgani[nEsame].GetNext(pos1);
	}
}