#include "stdafx.h"
#include "Endox.h"

#include "EsamiView.h"
#include "FrasiDlg.h"
#include "FrasiExSet.h"
#include "MediciSet.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFrasiExDlg::CFrasiExDlg(CEsamiView* pEsamiView)
	: CDialog(CFrasiExDlg::IDD, pEsamiView)
{
	m_pEsamiView = pEsamiView;
	m_nModalita  = NO_MODE;
	m_lFamiglia  = 0;
}

BEGIN_MESSAGE_MAP(CFrasiExDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_LISTA_FRASI, OnChangeListaFrasi)
	ON_NOTIFY(TCN_SELCHANGE, IDC_FAMIGLIE, OnChangeFamiglia)
	ON_CBN_EDITCHANGE(IDC_TIPO_ESAME, OnChangeTipoEsame)
	ON_CBN_SELCHANGE(IDC_TIPO_ESAME, OnChangeTipoEsame)
	ON_BN_CLICKED(IDC_NEW_CATEG, OnNewCateg)
	ON_BN_CLICKED(IDC_NEW_FRASE, OnNewFrase)
	ON_BN_CLICKED(IDC_MODIFY, OnMod)
	ON_BN_CLICKED(IDC_DELETE, OnDel)
	ON_BN_CLICKED(IDC_SAVE, OnSav)
	ON_BN_CLICKED(IDC_UNDO, OnUnd)
END_MESSAGE_MAP()

void CFrasiExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FAMIGLIE,      m_ctrlFamiglia);
	DDX_Control(pDX, IDC_TIPO_ESAME,    m_ctrlTipoEsame);
	DDX_Control(pDX, IDC_LISTA_FRASI,   m_ctrlListaFrasi);
	DDX_Control(pDX, IDC_STATIC_TITLE,  m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_PHRASE, m_ctrlStatic2);
	DDX_Control(pDX, IDC_NEW_CATEG,     m_ctrlButton1);
	DDX_Control(pDX, IDC_NEW_FRASE,     m_ctrlButton2);
	DDX_Control(pDX, IDC_MODIFY,        m_ctrlButton3);
	DDX_Control(pDX, IDC_DELETE,        m_ctrlButton4);
	DDX_Control(pDX, IDC_SAVE,          m_ctrlButton5);
	DDX_Control(pDX, IDC_UNDO,          m_ctrlButton6);
	DDX_Control(pDX, IDOK,              m_ctrlButtonOK);
}

BOOL CFrasiExDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (RiempiTipoEsame() == FALSE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FRASIEXDLG_NO_EXAM_TYPE));
		OnOK();
	}
	else
	{
		TC_ITEM TabCtrlItem;
		
		TabCtrlItem.mask = TCIF_TEXT;
		TabCtrlItem.pszText = "Frasi standard";
		m_ctrlFamiglia.InsertItem(0, &TabCtrlItem);
    
		TabCtrlItem.mask = TCIF_TEXT;
		TabCtrlItem.pszText = "Risposte standard";
		m_ctrlFamiglia.InsertItem(1, &TabCtrlItem);
    
		TabCtrlItem.mask = TCIF_TEXT;
		TabCtrlItem.pszText = "Anomalie standard";
		m_ctrlFamiglia.InsertItem(2, &TabCtrlItem);
	}

	GetDlgItem(IDC_TIPO_ESAME)->SetFont(&theApp.m_fontBold, TRUE);
	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CFrasiExDlg::IDD, "FrasiExDlg");

	return TRUE;
}

void CFrasiExDlg::OnChangeFamiglia(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_lFamiglia = m_ctrlFamiglia.GetCurSel();

	RiempiListaFrasi();
}

void CFrasiExDlg::OnChangeTipoEsame()
{
	m_lTipoEsame = m_ctrlTipoEsame.GetItemData(m_ctrlTipoEsame.GetCurSel());

	RiempiListaFrasi();
}

void CFrasiExDlg::OnOK()
{
	CDialog::OnOK();
}

CString CFrasiExDlg::GetNomeMedico(long lMedico)
{
	if (lMedico > 0)
	{
		CString strTemp;
		CMediciSet setMedici;

		strTemp.Format("Contatore=%li", lMedico);
		setMedici.SetOpenFilter(strTemp);
		setMedici.OpenRecordset("GetNomeMedico");

		if (setMedici.IsEOF() == FALSE)
		{
			strTemp = setMedici.m_sTitolo + " " + setMedici.m_sNome + " " + setMedici.m_sCognome;

			setMedici.CloseRecordset("GetNomeMedico");

			return strTemp;
		}

		setMedici.CloseRecordset("GetNomeMedico");
	}

	return theApp.GetMessageString(IDS_ALL_DOCTOR);
}

void CFrasiExDlg::RiempiListaFigli(HTREEITEM hPadre, long lPadre)
{
	CString strTemp;
	HTREEITEM hTemp;
	CFrasiExSet setFiglio;

	strTemp.Format("TipoEsame=%li and Famiglia=%li and Padre=%li", m_lTipoEsame, m_lFamiglia, lPadre);
	setFiglio.SetBaseFilter(strTemp);
	setFiglio.SetSortRecord("Contatore");
	setFiglio.OpenRecordset("RiempiListaFrasi - Figlio");
	while(setFiglio.IsEOF() == FALSE)
	{
		hTemp = m_ctrlListaFrasi.InsertItem(TVIF_TEXT | TVIF_PARAM, setFiglio.m_sTitolo, 0, 0, 0, 0, (LPARAM)setFiglio.m_lContatore, hPadre, TVI_LAST);

		RiempiListaFigli(hTemp, setFiglio.m_lContatore);

		setFiglio.MoveNext();
	}
	setFiglio.CloseRecordset("RiempiListaFrasi - Figlio");
}

void CFrasiExDlg::RiempiListaFrasi()
{
	CString strTemp;
	HTREEITEM hTemp;
	CFrasiExSet setPadre;

	m_ctrlListaFrasi.DeleteAllItems();

	strTemp.Format("TipoEsame=%li and Famiglia=%li and Padre=0", m_lTipoEsame, m_lFamiglia);
	setPadre.SetBaseFilter(strTemp);
	setPadre.SetSortRecord("Contatore");
	setPadre.OpenRecordset("RiempiListaFrasi - Padre");
	while(setPadre.IsEOF() == FALSE)
	{
		hTemp = m_ctrlListaFrasi.InsertItem(TVIF_TEXT | TVIF_PARAM, setPadre.m_sTitolo, 0, 0, 0, 0, (LPARAM)setPadre.m_lContatore, TVI_ROOT, TVI_LAST);

		RiempiListaFigli(hTemp, setPadre.m_lContatore);

		setPadre.MoveNext();
	}

	setPadre.CloseRecordset("RiempiListaFrasi - Padre");

	if (m_ctrlListaFrasi.GetCount() > 0)
	{
		GetDlgItem(IDC_NEW_FRASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_DELETE)->EnableWindow(TRUE);

		m_ctrlListaFrasi.SelectItem(m_ctrlListaFrasi.GetFirstVisibleItem());
	}
	else
	{
		GetDlgItem(IDC_NEW_FRASE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);

		GetDlgItem(IDC_TITOLO)->SetWindowText("");
		GetDlgItem(IDC_FRASE)->SetWindowText("");
	}
}

BOOL CFrasiExDlg::RiempiTipoEsame()
{
	int iTemp;
	DWORD dwTemp;
	CTipoEsameSet setTipoEsame;

	//setTipoEsame.SetOpenFilter("Visibile=1");
	setTipoEsame.SetSortRecord("Descrizione");

	setTipoEsame.OpenRecordset("RiempiTipoEsame");

	if (setTipoEsame.IsEOF() == TRUE)
	{
		setTipoEsame.CloseRecordset("RiempiTipoEsame");

		return FALSE;
	}

	m_ctrlTipoEsame.ResetContent();

	while(setTipoEsame.IsEOF() == FALSE)
	{
		iTemp = m_ctrlTipoEsame.AddString(setTipoEsame.m_sDescrizione);
		if (iTemp >= 0)
		{
			dwTemp = (DWORD)setTipoEsame.m_lContatore;
			m_ctrlTipoEsame.SetItemData(iTemp, dwTemp);
		}

		setTipoEsame.MoveNext();
	}

	setTipoEsame.CloseRecordset("RiempiTipoEsame");

	m_ctrlTipoEsame.SetCurSel(0);

	OnChangeTipoEsame();

	return TRUE;
}

void CFrasiExDlg::OnChangeListaFrasi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	CString strTemp;
	CFrasiExSet setFrasi;

	GetDlgItem(IDC_TITOLO)->SetWindowText("");
	GetDlgItem(IDC_FRASE)->SetWindowText("");

	if ((long)pNMTreeView->itemNew.lParam > 0)
	{
		strTemp.Format("Contatore=%li", (long)pNMTreeView->itemNew.lParam);
		setFrasi.SetOpenFilter(strTemp);
		setFrasi.SetSortRecord("Contatore");
		setFrasi.OpenRecordset("OnChangeListaFrasi");

		if (setFrasi.IsEOF() == FALSE)
		{
			GetDlgItem(IDC_TITOLO)->SetWindowText(setFrasi.m_sTitolo);
			GetDlgItem(IDC_FRASE)->SetWindowText(setFrasi.m_sDescrizione);
		}

		setFrasi.CloseRecordset("OnChangeListaFrasi");
	}

	*pResult = 0;
}

void CFrasiExDlg::OnNewCateg() 
{
	GetDlgItem(IDC_TITOLO)->SetWindowText("");
	GetDlgItem(IDC_FRASE)->SetWindowText("");

	ImpostaModalita(ROOT_MODE);

	GetDlgItem(IDC_TITOLO)->SetFocus();
}

void CFrasiExDlg::OnNewFrase() 
{
	GetDlgItem(IDC_TITOLO)->SetWindowText("");
	GetDlgItem(IDC_FRASE)->SetWindowText("");

	ImpostaModalita(ADD_MODE);

	GetDlgItem(IDC_TITOLO)->SetFocus();
}

void CFrasiExDlg::OnDel() 
{
	HTREEITEM hTemp = m_ctrlListaFrasi.GetSelectedItem();
	long lTemp = (long)m_ctrlListaFrasi.GetItemData(hTemp);
	BOOL bDelete = FALSE;

	if (m_ctrlListaFrasi.ItemHasChildren(hTemp) == TRUE)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FRASIEXDLG_DELETE_ITEM), MB_YESNO | MB_ICONQUESTION) == IDYES)
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FRASIEXDLG_CONFIRM_DELETE), MB_YESNO | MB_ICONQUESTION) == IDYES)
				bDelete = TRUE;
	}
	else
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FRASIEXDLG_DELETE_ITEM), MB_YESNO | MB_ICONQUESTION) == IDYES)
			bDelete = TRUE;
	}

	if (bDelete == TRUE)
	{
		CString strTemp;
		CFrasiExSet setTemp;

		strTemp.Format("Contatore=%li", lTemp);
		setTemp.SetOpenFilter(strTemp);
		setTemp.OpenRecordset("OnDel)");
		if (setTemp.IsEOF() == FALSE)
		{
			lTemp = setTemp.m_lPadre;

			if (setTemp.DeleteRecordset("OnDel") == TRUE)
			{

				if (lTemp == 0)
				{
					m_ctrlListaFrasi.DeleteItem(hTemp);
					m_ctrlListaFrasi.SelectItem(m_ctrlListaFrasi.GetFirstVisibleItem());
				}
				else
				{
					HTREEITEM hNewSel = m_ctrlListaFrasi.GetParentItem(hTemp);

					m_ctrlListaFrasi.DeleteItem(hTemp);
					m_ctrlListaFrasi.SelectItem(hNewSel);
				}
			}
		}
		setTemp.CloseRecordset("OnDel");
	}
}

void CFrasiExDlg::OnMod() 
{
	ImpostaModalita(MOD_MODE);

	GetDlgItem(IDC_TITOLO)->SetFocus();
}

void CFrasiExDlg::OnSav() 
{
	switch(m_nModalita)
	{
		case ADD_MODE:
		{
			CString strTemp;
			HTREEITEM hPadre = m_ctrlListaFrasi.GetSelectedItem();
			HTREEITEM hFiglio;
			CFrasiExSet setTemp;

			GetDlgItem(IDC_TITOLO)->GetWindowText(strTemp);
			if (strTemp.IsEmpty() == FALSE)
			{
				setTemp.OpenRecordset("OnSav(ROOT)");
				if (setTemp.AddNewRecordset("OnSav(ROOT)") == TRUE)
				{
					setTemp.m_lTipoEsame = m_lTipoEsame;
					setTemp.m_lFamiglia = m_lFamiglia;
					setTemp.m_lPadre = (long)m_ctrlListaFrasi.GetItemData(hPadre);
					GetDlgItem(IDC_TITOLO)->GetWindowText(setTemp.m_sTitolo);
					GetDlgItem(IDC_FRASE)->GetWindowText(setTemp.m_sDescrizione);

					if (setTemp.UpdateRecordset("OnSav(ROOT)") == TRUE)
					{
						setTemp.MoveLast();
						hFiglio = m_ctrlListaFrasi.InsertItem(TVIF_TEXT | TVIF_PARAM, setTemp.m_sTitolo, 0, 0, 0, 0, (LPARAM)setTemp.m_lContatore, hPadre, TVI_LAST);
						m_ctrlListaFrasi.SelectItem(hFiglio);
					}
					else
					{
						setTemp.NoEditRecordset("OnSav(ROOT)");
					}
				}
				setTemp.CloseRecordset("OnSav(ROOT)");
			}

			break;
		}
		case MOD_MODE:
		{
			CString strTemp;
			HTREEITEM hTemp = m_ctrlListaFrasi.GetSelectedItem();
			CFrasiExSet setTemp;

			GetDlgItem(IDC_TITOLO)->GetWindowText(strTemp);
			if (strTemp.IsEmpty() == FALSE)
			{
				long lTemp = m_ctrlListaFrasi.GetItemData(hTemp);

				strTemp.Format("Contatore=%li", lTemp);
				setTemp.SetOpenFilter(strTemp);
				setTemp.OpenRecordset("OnSav(ROOT)");
				if (setTemp.IsEOF() == FALSE)
				{
					if (setTemp.EditRecordset("OnSav(ROOT)") == TRUE)
					{
						GetDlgItem(IDC_TITOLO)->GetWindowText(setTemp.m_sTitolo);
						GetDlgItem(IDC_FRASE)->GetWindowText(setTemp.m_sDescrizione);

						if (setTemp.UpdateRecordset("OnSav(ROOT)") == TRUE)
						{
							m_ctrlListaFrasi.SetItemText(hTemp, setTemp.m_sTitolo);
							m_ctrlListaFrasi.SelectItem(hTemp);
						}
						else
						{
							setTemp.NoEditRecordset("OnSav(ROOT)");
						}
					}
				}
				setTemp.CloseRecordset("OnSav(ROOT)");
			}

			break;
		}
		case ROOT_MODE:
		{
			HTREEITEM hTemp;
			CString strTemp;
			CFrasiExSet setTemp;

			GetDlgItem(IDC_TITOLO)->GetWindowText(strTemp);
			if (strTemp.IsEmpty() == FALSE)
			{
				setTemp.OpenRecordset("OnSav(ROOT)");
				if (setTemp.AddNewRecordset("OnSav(ROOT)") == TRUE)
				{
					setTemp.m_lTipoEsame = m_lTipoEsame;
					setTemp.m_lFamiglia = m_lFamiglia;
					setTemp.m_lPadre = 0;
					GetDlgItem(IDC_TITOLO)->GetWindowText(setTemp.m_sTitolo);
					GetDlgItem(IDC_FRASE)->GetWindowText(setTemp.m_sDescrizione);

					if (setTemp.UpdateRecordset("OnSav(ROOT)") == TRUE)
					{
						setTemp.MoveLast();
						hTemp = m_ctrlListaFrasi.InsertItem(TVIF_TEXT | TVIF_PARAM, setTemp.m_sTitolo, 0, 0, 0, 0, (LPARAM)setTemp.m_lContatore, TVI_ROOT, TVI_LAST);
						m_ctrlListaFrasi.SelectItem(hTemp);
					}
					else
					{
						setTemp.NoEditRecordset("OnSav(ROOT)");
					}
				}
				setTemp.CloseRecordset("OnSav(ROOT)");
			}

			break;
		}
	}

	ImpostaModalita(NO_MODE);
}

void CFrasiExDlg::OnUnd() 
{
	CString strTemp;
	CFrasiExSet setFrasi;
	long lContatore;

	GetDlgItem(IDC_TITOLO)->SetWindowText("");
	GetDlgItem(IDC_FRASE)->SetWindowText("");

	if (m_ctrlListaFrasi.GetCount() > 0)
	{
		lContatore = (long)m_ctrlListaFrasi.GetItemData(m_ctrlListaFrasi.GetSelectedItem());
		if (lContatore > 0)
		{
			strTemp.Format("Contatore=%li", lContatore);
			setFrasi.SetOpenFilter(strTemp);
			setFrasi.SetSortRecord("Contatore");
			setFrasi.OpenRecordset("OnChangeListaFrasi");

			if (setFrasi.IsEOF() == FALSE)
			{
				GetDlgItem(IDC_TITOLO)->SetWindowText(setFrasi.m_sTitolo);
				GetDlgItem(IDC_FRASE)->SetWindowText(setFrasi.m_sDescrizione);
			}

			setFrasi.CloseRecordset("OnChangeListaFrasi");
		}
	}

	ImpostaModalita(NO_MODE);
}

void CFrasiExDlg::ImpostaModalita(int nModalita)
{
	switch(nModalita)
	{
		case NO_MODE:
		{
			GetDlgItem(IDC_TIPO_ESAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_FAMIGLIE)->EnableWindow(TRUE);
			GetDlgItem(IDC_LISTA_FRASI)->EnableWindow(TRUE);
			((CEdit *)GetDlgItem(IDC_TITOLO))->SetReadOnly(TRUE);
			((CEdit *)GetDlgItem(IDC_FRASE))->SetReadOnly(TRUE);

			GetDlgItem(IDC_NEW_CATEG)->EnableWindow(TRUE);
			GetDlgItem(IDC_NEW_FRASE)->EnableWindow(TRUE);
			GetDlgItem(IDC_MODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_DELETE)->EnableWindow(TRUE);
			GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

			break;
		}
		case ADD_MODE:
		{
			GetDlgItem(IDC_TIPO_ESAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_FAMIGLIE)->EnableWindow(FALSE);
			GetDlgItem(IDC_LISTA_FRASI)->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_TITOLO))->SetReadOnly(FALSE);
			((CEdit *)GetDlgItem(IDC_FRASE))->SetReadOnly(FALSE);

			GetDlgItem(IDC_NEW_CATEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_NEW_FRASE)->EnableWindow(FALSE);
			GetDlgItem(IDC_MODIFY)->EnableWindow(FALSE);
			GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
			GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);

			break;
		}
		case MOD_MODE:
		{
			GetDlgItem(IDC_TIPO_ESAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_FAMIGLIE)->EnableWindow(FALSE);
			GetDlgItem(IDC_LISTA_FRASI)->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_TITOLO))->SetReadOnly(FALSE);
			((CEdit *)GetDlgItem(IDC_FRASE))->SetReadOnly(FALSE);
//			((CEdit *)GetDlgItem(IDC_FRASE))->SetReadOnly(m_ctrlListaFrasi.GetParentItem(m_ctrlListaFrasi.GetSelectedItem()) == NULL);

			GetDlgItem(IDC_NEW_CATEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_NEW_FRASE)->EnableWindow(FALSE);
			GetDlgItem(IDC_MODIFY)->EnableWindow(FALSE);
			GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
			GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);

			break;
		}
		case ROOT_MODE:
		{
			GetDlgItem(IDC_TIPO_ESAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_FAMIGLIE)->EnableWindow(FALSE);
			GetDlgItem(IDC_LISTA_FRASI)->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_TITOLO))->SetReadOnly(FALSE);
			((CEdit *)GetDlgItem(IDC_FRASE))->SetReadOnly(FALSE);
//			((CEdit *)GetDlgItem(IDC_FRASE))->SetReadOnly(TRUE);

			GetDlgItem(IDC_NEW_CATEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_NEW_FRASE)->EnableWindow(FALSE);
			GetDlgItem(IDC_MODIFY)->EnableWindow(FALSE);
			GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
			GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);

			break;
		}
	}

	m_nModalita = nModalita;
}