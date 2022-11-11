#include "stdafx.h"
#include "Endox.h"
#include "UODlg.h"

#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CUODlg::CUODlg(CWnd* pParent)
	: CDialog(CUODlg::IDD, pParent)
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sCodiceEsterno = "";	

	m_bAddNew = FALSE;
	m_bModify = FALSE;
	//m_bOrPressed = FALSE;
	m_bRicercaAttivata = FALSE;
	m_bUserFocus = FALSE;
	m_bValidUser = TRUE;

	m_iItemCount = -1;
	m_iItemPressed = -1;
	m_iSavedPosition = -1;
}

CUODlg::~CUODlg()
{
}

BEGIN_MESSAGE_MAP(CUODlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_UO_NUOVO, OnUONew)
	ON_BN_CLICKED(IDC_UO_MODIFY, OnUOEdt)
	ON_BN_CLICKED(IDC_UO_CANC, OnUODel)
	ON_BN_CLICKED(IDC_UO_UPDATE, OnUOSave)
	ON_BN_CLICKED(IDC_UO_REFRESH, OnUOUndo)

	//ON_BN_CLICKED(IDC_BTN_OR,        OnBtnOr)

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)

	// ON_MESSAGE(WM_USER, OnWMUser) // è na pazzia //
	
	//ON_EN_CHANGE(IDC_LOGIN, OnEnChangeLogin)
	//ON_EN_SETFOCUS(IDC_LOGIN, OnEnSetfocusLogin)
	//ON_EN_KILLFOCUS(IDC_LOGIN, OnEnKillfocusLogin)
	//ON_BN_CLICKED(IDC_BUTTON_GENERA, OnBnClickedButtonGenera)
END_MESSAGE_MAP()

void CUODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizione);	
	DDX_Text(pDX, IDC_CODICE, m_sCodiceEsterno);	
	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	/* Sandro 19/03/2015
	if (!pDX->m_bSaveAndValidate && (m_lID > 0))
	{
		CString sIDUO;
		sIDUO.Format("%li", m_lID);
		DDX_Text(pDX, IDC_UO_IDENDOX, sIDUO);
	}
	*/

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);	
	DDX_Control(pDX, IDC_UO_NUOVO, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_UO_MODIFY, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_UO_CANC, m_ctrlButtonDel);
	DDX_Control(pDX, IDC_UO_UPDATE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_UO_REFRESH, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
}

BOOL CUODlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	
	GetDlgItem(IDC_UO_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_UO_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_UO_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UO_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);	

	m_ctrlLista.SetTabStops(138);
	RiempiListaUO();
	
	m_iItemPressed = 0;
	m_iItemCount = m_ctrlLista.GetCount();		

	//
	theApp.LocalizeDialog(this, CUODlg::IDD, "UODlg");

	return TRUE;
}

/* è na pazzia
LRESULT CMediciCurantiInviantiDlg::OnWMUser(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_RICERCA_STR2)->SetFocus();
	return 0;
}
*/

void CUODlg::RiempiListaUO()
{
	BeginWaitCursor();
	m_ctrlLista.SetRedraw(FALSE);
	m_ctrlLista.ResetContent();
	
	int nIndex = 0;

	CUOSet setTemp;

	if (setTemp.OpenRecordset("CUODlg::RiempiListaUO"))
	{				
		while(!setTemp.IsEOF())
		{
			int index = m_ctrlLista.InsertString(m_ctrlLista.GetCount(), setTemp.m_sDescrizione);
			m_ctrlLista.SetItemData(index, setTemp.m_lID);
			
			setTemp.MoveNext();
		}
		
		setTemp.CloseRecordset("CUODlg::RiempiListaUO");				
	}

	m_ctrlLista.SetRedraw(TRUE);
	EndWaitCursor();
	
	OnSelchangeLista();
}

void CUODlg::OnLbnDblclkLista()
{
	OnOK();
}

void CUODlg::OnSelchangeLista() 
{
	if (m_bAddNew || m_bModify)
		return;

	int nCount = m_ctrlLista.GetCount();
	if (nCount > 0)
	{
		int nCurPos = m_ctrlLista.GetCurSel();
		if (nCurPos >= 0)
		{
			// recupera il codice del medico appena selezionato	
			DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);

			GetDlgItem(IDC_UO_NUOVO)->EnableWindow(TRUE);
			GetDlgItem(IDC_UO_MODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_UO_CANC)->EnableWindow(TRUE);
			GetDlgItem(IDC_UO_UPDATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_UO_REFRESH)->EnableWindow(FALSE);

			if (dwCode >= 0)
			{
				CString strFilter;
				strFilter.Format("ID=%li", (long)dwCode);

				CUOSet setTemp;
				setTemp.SetOpenFilter(strFilter);

				if (setTemp.OpenRecordset("CUODlg::OnSelchangeLista"))
				{				
					if (!setTemp.IsEOF())
					{
						m_lID = setTemp.m_lID;
						m_sDescrizione = setTemp.m_sDescrizione;
						m_sCodiceEsterno = setTemp.m_sCodiceIntegrazione;						
					}
		
					setTemp.CloseRecordset("CUODlg::OnSelchangeLista");				
				}

				UpdateData(FALSE);
			}
		}
	}
}

BOOL CUODlg::CanBeInserted(long lContatore)
{
	/*CString strContatore, strTmp;

	//Controllo inizio stringa
	strContatore.Format("%i ", lContatore);
	strTmp = m_sRicerca.Left(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;

	//Controllo in mezzo alla stringa
	strContatore.Format(" %i ", lContatore);

	if (m_sRicerca.Find(strContatore) > 0)
		return FALSE;

	//Controllo alla fine
	strContatore.Format(" %i", lContatore);
	strTmp = m_sRicerca.Right(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;*/

	return TRUE;
}

void CUODlg::OnOK()
{
	UpdateData(FALSE);
	
	CDialog::OnOK();
}

void CUODlg::OnUONew() 
{
	GetDlgItem(IDC_CODICE)->EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_UO_NUOVO)->EnableWindow(FALSE);		
	GetDlgItem(IDC_UO_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_UO_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_UO_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_lID = 0;
	m_sDescrizione.Empty();
	m_sCodiceEsterno.Empty();

	m_bAddNew = TRUE;

	GetDlgItem(IDC_DESCRIZIONE)->SetFocus();

	UpdateData(FALSE);
}

void CUODlg::OnUOEdt() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDC_LISTA)	->EnableWindow(FALSE);
		GetDlgItem(IDC_CODICE)	->EnableWindow(TRUE);
		GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(TRUE);		

		GetDlgItem(IDC_UO_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_UO_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_UO_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_UO_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_UO_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		m_bModify = TRUE;

		GetDlgItem(IDC_DESCRIZIONE)->SetFocus();

		UpdateData(FALSE);
	}			
}

void CUODlg::OnUODel() 
{
	BOOL bDeleted = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);	

	GetDlgItem(IDC_UO_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UO_REFRESH)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		// recupera il codice del medico appena selezionato	
		int posiz = m_ctrlLista.GetCurSel();
			
		if (posiz >= 0)
		{
			DWORD dwCode = m_ctrlLista.GetItemData(posiz);
		
			if (dwCode >= 0)
			{
				CString strFilter;
				strFilter.Format("Id=%li", (long) dwCode);
			
				CUOSet setTemp;
				setTemp.SetOpenFilter(strFilter);
			
				if (setTemp.OpenRecordset("CUODlg::OnUODel"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CUODlg::OnUODel"))
						{
							int nRemained = m_ctrlLista.DeleteString(posiz);
							int nNewPos   = min (posiz, nRemained-1);

							m_ctrlLista.SetCurSel(nNewPos);

							OnSelchangeLista();
						}
					}

					
					setTemp.CloseRecordset("CUODlg::OnUODel");
				}
			}
		}
	}
	
	UpdateData(FALSE);
}

void CUODlg::OnUOSave() 
{
	BOOL bSaved = FALSE;
	
	UpdateData(TRUE);

	if (m_sDescrizione.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CUOSet setTemp;
		if (setTemp.OpenRecordset("CUODlg::OnUOSav"))
		{
			setTemp.AddNewRecordset("CUODlg::OnUOSav");
		
			setTemp.m_sCodiceIntegrazione = m_sCodiceEsterno;
			setTemp.m_sDescrizione = m_sDescrizione;

			bSaved = setTemp.UpdateRecordset("CUODlg::OnUOSav");

			m_lID = setTemp.GetLastAdd();

			setTemp.CloseRecordset("CUODlg::OnUOSav");
		}
	}
	else		
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lID);

		CUOSet setTemp;
		setTemp.SetOpenFilter(strFilter);
        
		if (setTemp.OpenRecordset("CUODlg::OnUOSav"))
		{
			if (setTemp.IsBOF() && setTemp.IsEOF())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
			}
			else
			{
				if (setTemp.EditRecordset("CUODlg::OnUOSav"))
				{
					setTemp.SetFieldDirty(NULL, TRUE);
					setTemp.SetFieldDirty(&setTemp.m_lID, FALSE);

					setTemp.m_sCodiceIntegrazione = m_sCodiceEsterno;
					setTemp.m_sDescrizione = m_sDescrizione;					

					bSaved = setTemp.UpdateRecordset("CUODlg::OnUOSav");
				}
			}

			setTemp.CloseRecordset("CUODlg::OnUOSav");
		}
	}

	if (bSaved)	
	{
		int posiz;

		if (m_bAddNew)
		{
			posiz = m_ctrlLista.AddString(m_sCodiceEsterno);

			if (posiz >= 0)
			{
				m_iSavedPosition = posiz;

				m_ctrlLista.SetItemData(posiz, (DWORD)m_lID);
				m_ctrlLista.SetCurSel(posiz);
			}
		}
		else
		{
			posiz = m_ctrlLista.GetCurSel();

			if (posiz >= 0)
			{
				m_ctrlLista.DeleteString(posiz);

				posiz = m_ctrlLista.InsertString(posiz, m_sCodiceEsterno);

				if (posiz >= 0)
				{
					m_ctrlLista.SetItemData(posiz, (DWORD)m_lID);
					m_ctrlLista.SetCurSel(posiz);
				}
			}
		}

		GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
		GetDlgItem(IDC_CODICE)	->EnableWindow(FALSE);
		GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(FALSE);		

		GetDlgItem(IDC_UO_NUOVO)->EnableWindow(TRUE);
		GetDlgItem(IDC_UO_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_UO_CANC)->EnableWindow(TRUE);
		GetDlgItem(IDC_UO_UPDATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_UO_REFRESH)->EnableWindow(FALSE);

		GetDlgItem(IDOK)->EnableWindow(TRUE);

		m_bModify = FALSE;
		m_bAddNew = FALSE;

		OnSelchangeLista();
	}
}

void CUODlg::OnUOUndo() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICE)	->EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(FALSE);	

	GetDlgItem(IDC_UO_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_UO_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UO_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	if (m_iSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_iSavedPosition;

		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;
	
		m_iSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}
}

