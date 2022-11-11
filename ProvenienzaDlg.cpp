#include "stdafx.h"
#include "Endox.h"
#include "ProvenienzaDlg.h"

#include "ProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProvenienzaDlg::CProvenienzaDlg(CWnd* pParent, BOOL bSearching)
	: CDialog(CProvenienzaDlg::IDD, pParent)
{
	m_lId = 0;
	m_sDescrizione = "";
	m_sCodiceEsterno = "";
	m_lIdProvenienzaEndox = 0;

	m_bAddNew = FALSE;
	m_bModify = FALSE;
	//m_bOrPressed = FALSE;
	m_bRicercaAttivata = FALSE;
	m_bUserFocus = FALSE;
	m_bValidUser = TRUE;

	m_iItemCount = -1;
	m_iItemPressed = -1;
	m_iSavedPosition = -1;

	m_bSearching = bSearching;	
}

CProvenienzaDlg::~CProvenienzaDlg()
{
}

BEGIN_MESSAGE_MAP(CProvenienzaDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_PROVENIENZA_NUOVO, OnProvenienzaNew)
	ON_BN_CLICKED(IDC_PROVENIENZA_MODIFY, OnProvenienzaEdt)
	ON_BN_CLICKED(IDC_PROVENIENZA_CANC, OnProvenienzaDel)
	ON_BN_CLICKED(IDC_PROVENIENZA_UPDATE, OnProvenienzaSave)
	ON_BN_CLICKED(IDC_PROVENIENZA_REFRESH, OnProvenienzaUndo)

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTA, &CProvenienzaDlg::OnLvnItemchangedLista)

END_MESSAGE_MAP()

void CProvenienzaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizione);
	DDX_Text(pDX, IDC_CODICE, m_sCodiceEsterno);
	DDX_Control(pDX, IDC_CMB_PROVENIENZA, m_ctrlCmbProvenienza);

	if (pDX->m_bSaveAndValidate)
		m_lIdProvenienzaEndox = m_ctrlCmbProvenienza.GetItemData(m_ctrlCmbProvenienza.GetCurSel());
	else
	{
		for(int i=0; i<m_ctrlCmbProvenienza.GetCount(); i++)
		{
			if (m_ctrlCmbProvenienza.GetItemData(i) == m_lIdProvenienzaEndox)
			{
				m_ctrlCmbProvenienza.SetCurSel(i);
				break;
			}
		}
	}

	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);

	DDX_Control(pDX, IDC_DESCRIZIONE, m_ctrlDescrizione);
	DDX_Control(pDX, IDC_CODICE, m_ctrlCodice);	

	DDX_Control(pDX, IDC_PROVENIENZA_NUOVO, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_PROVENIENZA_MODIFY, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_PROVENIENZA_CANC, m_ctrlButtonDel);
	DDX_Control(pDX, IDC_PROVENIENZA_UPDATE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_PROVENIENZA_REFRESH, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
}

BOOL CProvenienzaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);
	
	m_ctrlButtonNew.EnableWindow(TRUE && !m_bSearching);
	m_ctrlButtonEdt.EnableWindow(FALSE && !m_bSearching);
	m_ctrlButtonDel.EnableWindow(FALSE && !m_bSearching);
	m_ctrlButtonSave.EnableWindow(FALSE && !m_bSearching);
	m_ctrlButtonUndo.EnableWindow(FALSE && !m_bSearching);

	m_ctrlDescrizione.EnableWindow(FALSE && !m_bSearching);
	m_ctrlCodice.EnableWindow(FALSE && !m_bSearching);
	m_ctrlCmbProvenienza.EnableWindow(FALSE && !m_bSearching);

	int index = m_ctrlCmbProvenienza.AddString(theApp.GetMessageString(IDS_INVIANTE_INTERNO));
	m_ctrlCmbProvenienza.SetItemData(index, INTERNO);
	index = m_ctrlCmbProvenienza.AddString(theApp.GetMessageString(IDS_INVIANTE_ESTERNO));	
	m_ctrlCmbProvenienza.SetItemData(index, ESTERNO);

	m_ctrlLista.InsertColumn(0, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlLista.InsertColumn(1, theApp.GetMessageString(IDS_CODICE));
	m_ctrlLista.InsertColumn(2, theApp.GetMessageString(IDS_TIPO));

	//m_ctrlLista.SetTabStops(138);
	RiempiListaProvenienza();

	m_iItemPressed = 0;
	m_iItemCount = m_ctrlLista.GetItemCount();	

	//In ricerca la lista diventa multi-selection e nascondo i controlli
	if (m_bSearching)
	{
		m_ctrlLista.ModifyStyle(LVS_SINGLESEL, 0);

		m_ctrlButtonNew.ShowWindow(SW_HIDE);
		m_ctrlButtonEdt.ShowWindow(SW_HIDE);
		m_ctrlButtonDel.ShowWindow(SW_HIDE);
		m_ctrlButtonSave.ShowWindow(SW_HIDE);
		m_ctrlButtonUndo.ShowWindow(SW_HIDE);

		m_ctrlDescrizione.ShowWindow(SW_HIDE);
		m_ctrlCodice.ShowWindow(SW_HIDE);
		m_ctrlCmbProvenienza.ShowWindow(SW_HIDE);

		m_ctrlStatic1.ShowWindow(SW_HIDE);
		m_ctrlStatic2.ShowWindow(SW_HIDE);
		m_ctrlStatic3.ShowWindow(SW_HIDE);

		m_ctrlStatic4.SetFont(&theApp.m_fontBold);
		m_ctrlStatic4.ShowWindow(SW_SHOW);

		m_ctrlButtonOK.SetWindowText(theApp.GetMessageString(IDS_CONFERMA));

		m_idProvenienzaList.RemoveAll();
	}
	
	//
	theApp.LocalizeDialog(this, CProvenienzaDlg::IDD, "ProvenienzaDlg");

	if (!m_bMenu)
		PostMessage(WM_USER);

	return TRUE;
}

/* è na pazzia
LRESULT CMediciCurantiInviantiDlg::OnWMUser(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_RICERCA_STR2)->SetFocus();
	return 0;
}
*/

void CProvenienzaDlg::RiempiListaProvenienza()
{
	BeginWaitCursor();
	m_ctrlLista.SetRedraw(FALSE);
	m_ctrlLista.DeleteAllItems();
	
	int nIndex = 0;

	CProvenienzaSet setTemp;

	if (setTemp.OpenRecordset("CProvenienzaDlg::RiempiListaProvenienza"))
	{				
		while(!setTemp.IsEOF())
		{
			int index = m_ctrlLista.InsertItem(m_ctrlLista.GetItemCount(), setTemp.m_sDescrizione);
			m_ctrlLista.SetItemData(index, setTemp.m_lId);
			m_ctrlLista.SetItemText(index, 1, setTemp.m_sCodice);
			m_ctrlLista.SetItemText(index, 2, (setTemp.m_lIdProvenienzaEndox == 0 ? theApp.GetMessageString(IDS_INVIANTE_INTERNO) : theApp.GetMessageString(IDS_INVIANTE_ESTERNO)));
			
			setTemp.MoveNext();
		}
		
		setTemp.CloseRecordset("CProvenienzaDlg::RiempiListaProvenienza");				
	}

	m_ctrlLista.SetRedraw(TRUE);
	EndWaitCursor();

	for (int h = 0; h<3; h++)
		m_ctrlLista.SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlLista.SetExtendedStyle(m_ctrlLista.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	OnSelchangeLista();
}

void CProvenienzaDlg::OnLbnDblclkLista()
{
	OnOK();
}

void CProvenienzaDlg::OnSelchangeLista() 
{
	CString strDoctor, strTmp;

	if (m_bAddNew || m_bModify)
		return;

	int nCount = m_ctrlLista.GetItemCount();

	m_lId = 0;
	m_sDescrizione = "";
	m_sCodiceEsterno = "";
	m_lIdProvenienzaEndox = -1;
	m_ctrlButtonEdt.EnableWindow(FALSE && !m_bSearching);
	m_ctrlButtonDel.EnableWindow(FALSE && !m_bSearching);
	m_ctrlButtonSave.EnableWindow(FALSE && !m_bSearching);
	m_ctrlButtonUndo.EnableWindow(FALSE && !m_bSearching);

	if (nCount > 0)
	{
		POSITION pos = m_ctrlLista.GetFirstSelectedItemPosition();		

		if (pos)
		{
			int nCurPos = m_ctrlLista.GetNextSelectedItem(pos);

			// recupera il codice del medico appena selezionato	
			DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);

			m_ctrlButtonNew.EnableWindow(TRUE && !m_bSearching);
			m_ctrlButtonEdt.EnableWindow(TRUE && !m_bSearching);
			m_ctrlButtonDel.EnableWindow(TRUE && !m_bSearching);
			m_ctrlButtonSave.EnableWindow(FALSE && !m_bSearching);
			m_ctrlButtonUndo.EnableWindow(FALSE && !m_bSearching);

			if (dwCode >= 0)
			{
				CString strFilter;
				strFilter.Format("Id=%li", (long)dwCode);

				CProvenienzaSet setTemp;
				setTemp.SetOpenFilter(strFilter);

				if (setTemp.OpenRecordset("CProvenienzaDlg::OnSelchangeLista"))
				{				
					if (!setTemp.IsEOF())
					{
						m_lId = setTemp.m_lId;
						m_sDescrizione = setTemp.m_sDescrizione;
						m_sCodiceEsterno = setTemp.m_sCodice;
						m_lIdProvenienzaEndox = setTemp.m_lIdProvenienzaEndox;
					}
		
					setTemp.CloseRecordset("CProvenienzaDlg::OnSelchangeLista");				
				}				
			}
		}
	}

	UpdateData(FALSE);
}

BOOL CProvenienzaDlg::CanBeInserted(long lContatore)
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

void CProvenienzaDlg::OnOK()
{
	UpdateData(FALSE);

	//In ricerca, costruisco la lista degli id selezionati
	if (m_bSearching)
	{
		POSITION pos = m_ctrlLista.GetFirstSelectedItemPosition();

		while (pos)
		{
			int index = m_ctrlLista.GetNextSelectedItem(pos);
			long id = m_ctrlLista.GetItemData(index);
			m_idProvenienzaList.AddTail(id);
		}
	}
	
	CDialog::OnOK();
}

void CProvenienzaDlg::OnCancel()
{
}

void CProvenienzaDlg::OnProvenienzaNew() 
{
	m_ctrlDescrizione.EnableWindow(TRUE);
	m_ctrlCodice.EnableWindow(TRUE);
	m_ctrlCmbProvenienza.EnableWindow(TRUE);
	
	m_ctrlButtonNew.EnableWindow(FALSE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(TRUE);
	m_ctrlButtonUndo.EnableWindow(TRUE);	

	m_ctrlButtonOK.EnableWindow(FALSE);

	m_lId = 0;
	m_sDescrizione = "";
	m_sCodiceEsterno.Empty();
	m_lIdProvenienzaEndox = -1;

	m_bAddNew = TRUE;

	m_ctrlCodice.SetFocus();

	UpdateData(FALSE);
}

void CProvenienzaDlg::OnProvenienzaEdt() 
{
	POSITION pos = m_ctrlLista.GetFirstSelectedItemPosition();
		
	if (pos)
	{
		m_ctrlLista.EnableWindow(TRUE);
		m_ctrlDescrizione.EnableWindow(TRUE);
		m_ctrlCodice.EnableWindow(TRUE);
		m_ctrlCmbProvenienza.EnableWindow(TRUE);		

		m_ctrlButtonNew.EnableWindow(FALSE);
		m_ctrlButtonEdt.EnableWindow(FALSE);
		m_ctrlButtonDel.EnableWindow(FALSE);
		m_ctrlButtonSave.EnableWindow(TRUE);
		m_ctrlButtonUndo.EnableWindow(TRUE);

		m_ctrlButtonOK.EnableWindow(FALSE);

		m_bModify = TRUE;

		m_ctrlCodice.SetFocus();

		UpdateData(FALSE);
	}			
}

void CProvenienzaDlg::OnProvenienzaDel() 
{
	BOOL	bDeleted = FALSE;

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlDescrizione.EnableWindow(TRUE);
	m_ctrlCodice.EnableWindow(FALSE);
	m_ctrlCmbProvenienza.EnableWindow(FALSE);		

	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(TRUE);
	m_ctrlButtonDel.EnableWindow(TRUE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);


	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		// recupera il codice del medico appena selezionato	
		POSITION pos = m_ctrlLista.GetFirstSelectedItemPosition();
			
		if (pos)
		{
			int posiz = m_ctrlLista.GetNextSelectedItem(pos);

			DWORD dwCode = m_ctrlLista.GetItemData(posiz);
		
			if (dwCode >= 0)
			{
				CString strFilter;
				strFilter.Format("Id=%li", (long) dwCode);
			
				CProvenienzaSet setTemp;
				setTemp.SetOpenFilter(strFilter);
			
				if (setTemp.OpenRecordset("CProvenienzaDlg::OnProvenienzaDel"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CProvenienzaDlg::OnProvenienzaDel"))
						{
							int nRemained = m_ctrlLista.DeleteItem(posiz);
							//int nNewPos   = min (posiz, nRemained-1);

							//m_ctrlLista.select(nNewPos);

							OnSelchangeLista();
						}
					}

					
					setTemp.CloseRecordset("CProvenienzaDlg::OnProvenienzaDel");
				}
			}
		}
	}
	
	UpdateData(FALSE);
}

void CProvenienzaDlg::OnProvenienzaSave() 
{
	BOOL bSaved = FALSE;	
	
	UpdateData(TRUE);

	if (m_sDescrizione.IsEmpty() || m_lIdProvenienzaEndox < 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CProvenienzaSet setTemp;
		if (setTemp.OpenRecordset("CProvenienzaDlg::OnProvenienzaSave"))
		{
			setTemp.AddNewRecordset("CProvenienzaDlg::OnProvenienzaSave");
		
			setTemp.m_sDescrizione = m_sDescrizione;
			setTemp.m_sCodice = m_sCodiceEsterno;
			setTemp.m_lIdProvenienzaEndox = m_lIdProvenienzaEndox;

			bSaved = setTemp.UpdateRecordset("CProvenienzaDlg::OnProvenienzaSave");

			m_lId = setTemp.GetLastAdd();

			setTemp.CloseRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate");
		}
	}
	else		
	{
		CString strFilter;
		strFilter.Format("id=%li", m_lId);

		CProvenienzaSet setTemp;
		setTemp.SetOpenFilter(strFilter);
        
		if (setTemp.OpenRecordset("CProvenienzaDlg::OnProvenienzaSave"))
		{
			if (setTemp.IsBOF() && setTemp.IsEOF())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
			}
			else
			{
				if (setTemp.EditRecordset("CProvenienzaDlg::OnProvenienzaSave"))
				{
					setTemp.SetFieldDirty(NULL, TRUE);
					setTemp.SetFieldDirty(&setTemp.m_lId, FALSE);

					setTemp.m_sDescrizione = m_sDescrizione;
					setTemp.m_sCodice = m_sCodiceEsterno;
					setTemp.m_lIdProvenienzaEndox = m_lIdProvenienzaEndox;

					bSaved = setTemp.UpdateRecordset("CProvenienzaDlg::OnProvenienzaSave");
				}
			}

			setTemp.CloseRecordset("CProvenienzaDlg::OnProvenienzaSave");
		}
	}

	if (bSaved)	
	{
		int posiz;

		if (m_bAddNew)
		{
			posiz = m_ctrlLista.InsertItem(m_ctrlLista.GetItemCount(), m_sDescrizione);			

			if (posiz >= 0)
			{
				m_ctrlLista.SetItemText(posiz, 1, m_sCodiceEsterno);
				int sel = m_ctrlCmbProvenienza.GetCurSel();
				m_ctrlLista.SetItemText(posiz, 2, (m_ctrlCmbProvenienza.GetItemData(sel) == 0 ? theApp.GetMessageString(IDS_INVIANTE_INTERNO) : theApp.GetMessageString(IDS_INVIANTE_ESTERNO)));

				m_iSavedPosition = posiz;

				m_ctrlLista.SetItemData(posiz, (DWORD)m_lId);
				//m_ctrlLista.sele(posiz);
			}
		}
		else
		{
			/*POSITION pos = m_ctrlLista.GetFirstSelectedItemPosition();

			if (pos)
			{
				int posiz = m_ctrlLista.GetNextSelectedItem(pos);

				m_ctrlLista.DeleteItem(posiz);

				posiz = m_ctrlLista.InsertItem(posiz, m_sCodiceEsterno);

				if (posiz >= 0)
				{
					m_ctrlLista.SetItemData(posiz, (DWORD)m_lId);
					//m_ctrlLista.SetCurSel(posiz);
				}
			}*/

			RiempiListaProvenienza();
		}

		m_ctrlLista.EnableWindow(TRUE);
		m_ctrlDescrizione.EnableWindow(FALSE);
		m_ctrlCodice.EnableWindow(FALSE);
		m_ctrlCmbProvenienza.EnableWindow(FALSE);	

		m_ctrlButtonNew.EnableWindow(TRUE);
		m_ctrlButtonEdt.EnableWindow(TRUE);
		m_ctrlButtonDel.EnableWindow(TRUE);
		m_ctrlButtonSave.EnableWindow(FALSE);
		m_ctrlButtonUndo.EnableWindow(FALSE);		

		m_ctrlButtonOK.EnableWindow(TRUE);

		m_bModify = FALSE;
		m_bAddNew = FALSE;

		OnSelchangeLista();
	}
}

void CProvenienzaDlg::OnProvenienzaUndo() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlDescrizione.EnableWindow(FALSE);
	m_ctrlCodice.EnableWindow(FALSE);
	m_ctrlCmbProvenienza.EnableWindow(FALSE);

	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(TRUE);
	m_ctrlButtonDel.EnableWindow(TRUE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);

	m_ctrlButtonOK.EnableWindow(TRUE);

	if (m_iSavedPosition <= m_ctrlLista.GetItemCount())
	{
		int nPos = m_iSavedPosition;

		if (nPos < 0 && m_ctrlLista.GetItemCount())
			nPos = 0;
	
		m_iSavedPosition = -1;

		//m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}
}



void CProvenienzaDlg::OnLvnItemchangedLista(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	OnSelchangeLista();

	*pResult = 0;
}
