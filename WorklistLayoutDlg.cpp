#include "stdafx.h"
#include "Endox.h"
#include "WorklistLayoutDlg.h"

#include "EsamiView.h"
#include "CupWorkListManager.h"
#include "ConfigurazioniListaPrenotazioniSet.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWorklistLayoutDlg, CDialog)

CWorklistLayoutDlg::CWorklistLayoutDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CWorklistLayoutDlg::IDD, pParent),
	m_ctrlListOn(TRUE, TRUE, FALSE)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

}

CWorklistLayoutDlg::~CWorklistLayoutDlg()
{
}

void CWorklistLayoutDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

BEGIN_MESSAGE_MAP(CWorklistLayoutDlg, CDialog)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ON, &CWorklistLayoutDlg::OnLvnItemchangedListOn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OFF, &CWorklistLayoutDlg::OnLvnItemchangedListOff)
	ON_BN_CLICKED(IDC_BTN_ON, &CWorklistLayoutDlg::OnBnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_OFF, &CWorklistLayoutDlg::OnBnClickedBtnOff)
	ON_BN_CLICKED(IDC_BTN_UP, &CWorklistLayoutDlg::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CWorklistLayoutDlg::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDOK, &CWorklistLayoutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CWorklistLayoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control (pDX, IDC_STATIC_ON,		m_ctrlStaticOn);
	DDX_Control (pDX, IDC_STATIC_OFF,		m_ctrlStaticOff);
	DDX_Control (pDX, IDC_LIST_ON,			m_ctrlListOn);
	DDX_Control (pDX, IDC_LIST_OFF,			m_ctrlListOff);
	DDX_Control (pDX, IDC_BTN_ON,			m_ctrlBtnOn);
	DDX_Control (pDX, IDC_BTN_OFF,			m_ctrlBtnOff);
	DDX_Control (pDX, IDC_BTN_UP,			m_ctrlBtnUp);
	DDX_Control (pDX, IDC_BTN_DOWN,			m_ctrlBtnDown);
	DDX_Control (pDX, IDOK,					m_ctrlBtnSave);
	DDX_Control (pDX, IDCANCEL,				m_ctrlBtnAbort);
}

BOOL CWorklistLayoutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	RiempiListaOff();
	RiempiListaOn();
		
	RedrawWindow();

	theApp.LocalizeDialog(this, CWorklistLayoutDlg::IDD, "WorklistLayoutDlg");
	return TRUE;
}


void  CWorklistLayoutDlg::OnOK()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIRM), MB_YESNO) == IDNO)
		return;

	if (theApp.m_bPrenotazioniCup)
		CCupWorkListManager::LoadIntoMemory();

	CDialog::OnOK();
}

void  CWorklistLayoutDlg::OnCancel()
{
	//if (theApp.AfxMessageBoxEndo("Annullare le modifiche effettuate?", MB_YESNO) == IDNO)
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ABORT), MB_YESNO) == IDNO)	
		return;

	CDialog::OnCancel();
}

void  CWorklistLayoutDlg::RiempiListaOff()
{
	CRecordset recordset(&theApp.m_dbEndox);
	if (recordset.Open(CRecordset::snapshot, "SELECT * FROM VISTA_EXT_ORDINI_LAYOUT WHERE ENDOXORDERID = 0", CRecordset::readOnly))
	{
		CStringList fieldList;
		short fields = recordset.GetODBCFieldCount();

		for(int i=0; i<fields; i++)
		{
			CODBCFieldInfo tempInfo;
			recordset.GetODBCFieldInfo(i, tempInfo);
			bool find = FALSE;

			for(POSITION pos=theApp.m_worklistFields.GetHeadPosition();pos;)
			{
				worklistField tempField = theApp.m_worklistFields.GetNext(pos);
				
				if (tempField.sNomeColonna.CompareNoCase(tempInfo.m_strName) == 0)
				{
					find = TRUE;
					break;
				}				
			}

			if (!find)
			{
				fieldList.AddTail(tempInfo.m_strName);				
			}
			
		}

		//Ordino alfabeticamente la string list
		CArray<CString> tempArray;
		for (int i=0; i<fieldList.GetCount(); i++)
			tempArray.Add(fieldList.GetAt(fieldList.FindIndex(i)));

		std::sort(tempArray.GetData(), tempArray.GetData() + tempArray.GetSize());

		fieldList.RemoveAll();
		for (int i=0; i<tempArray.GetCount(); i++)
			fieldList.AddTail(tempArray.GetAt(i));

		//Ora posso riempire la list control
		for (int i=0; i<fieldList.GetCount(); i++)
			m_ctrlListOff.InsertItem(i, fieldList.GetAt(fieldList.FindIndex(i)));

		recordset.Close();
	}
}

void  CWorklistLayoutDlg::RiempiListaOn()
{
	m_ctrlListOn.InsertColumn(0, theApp.GetMessageString(IDS_CAMPO));
	m_ctrlListOn.InsertColumn(1, theApp.GetMessageString(IDS_TITOLO));
	m_ctrlListOn.InsertColumn(2, theApp.GetMessageString(IDS_DIMSTAMPAPERC));

	int iRow = 0;

	for(POSITION pos=theApp.m_worklistFields.GetHeadPosition();pos;)
	{
		worklistField tempField = theApp.m_worklistFields.GetNext(pos);
			
		int index = m_ctrlListOn.InsertItem(iRow, tempField.sNomeColonna);
		m_ctrlListOn.SetItemText(index, 1, tempField.sTitolo);
		m_ctrlListOn.SetSubItemEdit(index, 1);

		CString sPerc;
		sPerc.Format("%li", tempField.lDimensioneStampaPerc);

		m_ctrlListOn.SetItemText(index, 2, sPerc);
		m_ctrlListOn.SetSubItemEdit(index, 2);

		iRow++;		
	}

	m_ctrlListOn.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListOn.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListOn.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

void CWorklistLayoutDlg::OnLvnItemchangedListOn(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	m_ctrlBtnOff.EnableWindow(m_ctrlListOn.GetSelectedCount() > 0);
	m_ctrlBtnUp.EnableWindow(FALSE);
	m_ctrlBtnDown.EnableWindow(FALSE);

	if (m_ctrlListOn.GetSelectedCount() > 0)
	{
		POSITION pos = m_ctrlListOn.GetFirstSelectedItemPosition();
		if (pos)
		{
			int index = m_ctrlListOn.GetNextSelectedItem(pos);
			if (index > 0)		
				m_ctrlBtnUp.EnableWindow(TRUE);

			if (index < m_ctrlListOn.GetItemCount()-1)
				m_ctrlBtnDown.EnableWindow(TRUE);
		}				
	}

	*pResult = 0;
}


void CWorklistLayoutDlg::OnLvnItemchangedListOff(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	m_ctrlBtnOn.EnableWindow(m_ctrlListOff.GetSelectedCount() > 0);
	*pResult = 0;
}


void CWorklistLayoutDlg::OnBnClickedBtnOn()
{
	POSITION pos = m_ctrlListOff.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlListOff.GetNextSelectedItem(pos);
		if (index >= 0)
		{
			CString temp = m_ctrlListOff.GetItemText(index, 0);
			m_ctrlListOff.DeleteItem(index);
			int i = m_ctrlListOn.InsertItem(m_ctrlListOn.GetItemCount(), temp);
			m_ctrlListOn.SetItemText(i, 1, temp);
			m_ctrlListOn.SetSubItemEdit(i, 1);
			m_ctrlListOn.SetItemText(i, 2, "0");
			m_ctrlListOn.SetSubItemEdit(i, 2);
		}
	}

	m_ctrlListOn.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListOn.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListOn.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}


void CWorklistLayoutDlg::OnBnClickedBtnOff()
{
	POSITION pos = m_ctrlListOn.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlListOn.GetNextSelectedItem(pos);
		if (index >= 0)
		{
			CString temp = m_ctrlListOn.GetItemText(index, 0);
			m_ctrlListOn.DeleteItem(index);
			int i = m_ctrlListOff.InsertItem(m_ctrlListOff.GetItemCount(), temp);
			//m_ctrlListOff.SetItemText(i, 1, temp);
		}
	}

	m_ctrlListOn.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListOn.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListOn.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}


void CWorklistLayoutDlg::OnBnClickedBtnUp()
{
	POSITION pos = m_ctrlListOn.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlListOn.GetNextSelectedItem(pos);
		if (index >= 0)
		{
			CString prevTempCol = m_ctrlListOn.GetItemText(index-1, 0);
			CString prevTempTit = m_ctrlListOn.GetItemText(index-1, 1);
			CString prevTempDim = m_ctrlListOn.GetItemText(index-1, 2);

			m_ctrlListOn.SetItemText(index-1, 0, m_ctrlListOn.GetItemText(index, 0));
			m_ctrlListOn.SetItemText(index-1, 1, m_ctrlListOn.GetItemText(index, 1));
			m_ctrlListOn.SetItemText(index-1, 2, m_ctrlListOn.GetItemText(index, 2));
			
			m_ctrlListOn.SetItemText(index, 0, prevTempCol);
			m_ctrlListOn.SetItemText(index, 1, prevTempTit);
			m_ctrlListOn.SetItemText(index, 2, prevTempDim);

			m_ctrlListOn.SetItemState(index, ~LVIS_SELECTED, LVIS_SELECTED); 
			m_ctrlListOn.SetItemState(index-1, LVIS_SELECTED, LVIS_SELECTED); 
		}
	}
}


void CWorklistLayoutDlg::OnBnClickedBtnDown()
{
	POSITION pos = m_ctrlListOn.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlListOn.GetNextSelectedItem(pos);
		if (index >= 0)
		{
			CString prevTempCol = m_ctrlListOn.GetItemText(index+1, 0);
			CString prevTempTit = m_ctrlListOn.GetItemText(index+1, 1);
			CString prevTempDim = m_ctrlListOn.GetItemText(index+1, 2);

			m_ctrlListOn.SetItemText(index+1, 0, m_ctrlListOn.GetItemText(index, 0));
			m_ctrlListOn.SetItemText(index+1, 1, m_ctrlListOn.GetItemText(index, 1));
			m_ctrlListOn.SetItemText(index+1, 2, m_ctrlListOn.GetItemText(index, 2));
			
			m_ctrlListOn.SetItemText(index, 0, prevTempCol);
			m_ctrlListOn.SetItemText(index, 1, prevTempTit);
			m_ctrlListOn.SetItemText(index, 2, prevTempDim);

			m_ctrlListOn.SetItemState(index, ~LVIS_SELECTED, LVIS_SELECTED); 
			m_ctrlListOn.SetItemState(index+1, LVIS_SELECTED, LVIS_SELECTED); 
		}
	}
}


void CWorklistLayoutDlg::OnBnClickedOk()
{
	//if (theApp.AfxMessageBoxEndo("Salvare il layout della worklist?", MB_YESNO) == IDNO)
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVE), MB_YESNO) == IDNO)		
		return;

	//svuoto la tabella
	CConfigurazioniListaPrenotazioniSet configSet;
	if (configSet.OpenRecordset("CWorklistLayoutDlg::OnBnClickedOk"))
	{
		while(!configSet.IsEOF())
		{
			BOOL find = FALSE;
			int index = -1;

			for(int i=0; i<m_ctrlListOn.GetItemCount(); i++)
			{
				if (m_ctrlListOn.GetItemText(i,0).CompareNoCase(configSet.m_sCampo) == 0)
				{
					find = TRUE;
					index = i;
					break;
				}
			}

			//Se non ho trovato l'elemento nella lista lo rimuovo
			//Se l'ho trovato aggiorno posizione, titolo e dimensione in percentuale
			if (!find)
			{
				configSet.DeleteRecordset("CWorklistLayoutDlg::OnBnClickedOk");
			}
			else
			{
				configSet.EditRecordset("CWorklistLayoutDlg::OnBnClickedOk");
				configSet.m_lOrdine = index;
				configSet.m_sTitolo = m_ctrlListOn.GetItemText(index,1);
				configSet.m_lDimensioneStampaPerc = atoi(m_ctrlListOn.GetItemText(index,2));
				configSet.UpdateRecordset("CWorklistLayoutDlg::OnBnClickedOk");
			}

			configSet.MoveNext();
		}

		configSet.CloseRecordset("CWorklistLayoutDlg::OnBnClickedOk");
	}

	//Inserisco i record nuovi
	for(int i=0; i<m_ctrlListOn.GetItemCount(); i++)
	{
		CConfigurazioniListaPrenotazioniSet configSet;
		CString filter;
		filter.Format("Campo='%s'", m_ctrlListOn.GetItemText(i,0));
		configSet.SetOpenFilter(filter);
		if (configSet.OpenRecordset("CWorklistLayoutDlg::OnBnClickedOk"))
		{
			//Se il record non c'è nel recordset lo devo inserire
			if (configSet.IsEOF())
			{
				if (configSet.AddNewRecordset("CWorklistLayoutDlg::OnBnClickedOk"))
				{
					configSet.m_lOrdine = i;
					configSet.m_sTitolo = m_ctrlListOn.GetItemText(i,1);
					configSet.m_sCampo = m_ctrlListOn.GetItemText(i,0);
					configSet.m_lDimensioneStampaPerc = atoi(m_ctrlListOn.GetItemText(i,2));

					configSet.UpdateRecordset("CWorklistLayoutDlg::OnBnClickedOk");
				}
			}

			configSet.CloseRecordset("CWorklistLayoutDlg::OnBnClickedOk");
		}
	}
	
	OnOK();
}
