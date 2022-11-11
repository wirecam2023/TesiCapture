#include "stdafx.h"
#include "Endox.h"
#include "ModifyGridCLPrivilegiConfigDlg.h"

#include "EndoGridCLGruppiUtenteSet.h"
#include "EtichetteSet.h"
#include "GruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CModifyGridCLPrivilegiConfigDlg, CXTResizeDialog)

CModifyGridCLPrivilegiConfigDlg::CModifyGridCLPrivilegiConfigDlg(CWnd* pParent, int iIndex)
: CXTResizeDialog(CModifyGridCLPrivilegiConfigDlg::IDD, pParent)
{
	m_iGridIndex = iIndex;
}

CModifyGridCLPrivilegiConfigDlg::~CModifyGridCLPrivilegiConfigDlg()
{
}

void CModifyGridCLPrivilegiConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_LIST_ON, m_ctrlListOn);
	DDX_Control(pDX, IDC_LIST_OFF, m_ctrlListOff);
	DDX_Control(pDX, IDC_BTN_ON, m_ctrlBtnOn);
	DDX_Control(pDX, IDC_BTN_OFF, m_ctrlBtnOff);	
	DDX_Control(pDX, IDOK, m_ctrlBtnSave);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnAbort);
}

BEGIN_MESSAGE_MAP(CModifyGridCLPrivilegiConfigDlg, CXTResizeDialog)	
	ON_BN_CLICKED(IDC_BTN_ON, &CModifyGridCLPrivilegiConfigDlg::OnBnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_OFF, &CModifyGridCLPrivilegiConfigDlg::OnBnClickedBtnOff)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OFF, &CModifyGridCLPrivilegiConfigDlg::OnLvnItemchangedListOff)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ON, &CModifyGridCLPrivilegiConfigDlg::OnLvnItemchangedListOn)
END_MESSAGE_MAP()

// CModifyFieldAnamnesisDlg message handlers

BOOL CModifyGridCLPrivilegiConfigDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_LIST_OFF, 0.0f, 0.0f, 0.5f, 1.0f);
	SetResize(IDC_LIST_ON, 0.5f, 0.0f, 1.0f, 1.0f);
	SetResize(IDC_BTN_OFF, 0.5f, 0.0f, 0.5f, 0.0f);
	SetResize(IDC_BTN_ON, 0.5f, 0.0f, 0.5f, 0.0f);	
	SetResize(IDOK, 1, 1, 1, 1);
	SetResize(IDCANCEL, 1, 1, 1, 1);

	RiempiListaOff();
	RiempiListaOn();

	GetDlgItem(IDOK)->SetFocus();

	theApp.LocalizeDialog(this, CModifyGridCLPrivilegiConfigDlg::IDD, "ModifyGridCLPrivilegiConfigDlg");
	return FALSE;
}

void CModifyGridCLPrivilegiConfigDlg::OnOK()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIRM), MB_YESNO) == IDNO)
		return;	

	long idEtichetta = CEtichetteSet().GetId("GRIDCL", m_iGridIndex);

	//Rimuovo la vecchia lista da db
	CString sFilter;
	sFilter.Format("IDETICHETTA_GRIDCL=%li", idEtichetta);
	CEndoGridCLGruppiUtenteSet gridCLGruppiSet;
	gridCLGruppiSet.SetOpenFilter(sFilter);

	if (gridCLGruppiSet.OpenRecordset("CModifyGridCLPrivilegiConfigDlg::OnOK"))
	{
		while (!gridCLGruppiSet.IsEOF())
		{
			gridCLGruppiSet.DeleteRecordset("CModifyGridCLPrivilegiConfigDlg::OnOK");

			gridCLGruppiSet.MoveNext();
		}

		gridCLGruppiSet.CloseRecordset("CModifyGridCLPrivilegiConfigDlg::OnOK");
	}

	//Recupero la lista e la salvo in theApp.m_listGridCLGruppiAssociati[m_iGridIndex]
	gridCLGruppiSet.SetOpenFilter("");
	if (gridCLGruppiSet.OpenRecordset("CModifyGridCLPrivilegiConfigDlg::OnOK"))
	{
		theApp.m_listGridCLGruppiAssociati[m_iGridIndex].RemoveAll();

		for (int i = 0; i<m_ctrlListOn.GetItemCount(); i++)
		{
			int idGruppo = m_ctrlListOn.GetItemData(i);
			theApp.m_listGridCLGruppiAssociati[m_iGridIndex].AddTail(idGruppo);

			if (gridCLGruppiSet.AddNewRecordset("CModifyGridCLPrivilegiConfigDlg::OnOK"))
			{
				gridCLGruppiSet.m_lIDEtichetta = idEtichetta;
				gridCLGruppiSet.m_lIDGruppo = idGruppo;

				gridCLGruppiSet.UpdateRecordset("CModifyGridCLPrivilegiConfigDlg::OnOK");
			}

		}

		gridCLGruppiSet.CloseRecordset("CModifyGridCLPrivilegiConfigDlg::OnOK");
	}	

	CDialog::OnOK();
}

void CModifyGridCLPrivilegiConfigDlg::OnCancel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ABORT), MB_YESNO) == IDNO)
		return;

	CDialog::OnCancel();
}


void  CModifyGridCLPrivilegiConfigDlg::RiempiListaOff()
{
	m_ctrlListOff.InsertColumn(0, "");

	CGruppiSet gruppiSet;
	if (gruppiSet.OpenRecordset("CModifyGridCLPrivilegiConfigDlg::RiempiListaOff"))
	{
		int i = 0;

		while (!gruppiSet.IsEOF())
		{
			//Se non è tra i selezionati
			if (theApp.m_listGridCLGruppiAssociati[m_iGridIndex].Find(gruppiSet.m_lID) == NULL)
			{
				int index = m_ctrlListOff.InsertItem(i, gruppiSet.m_sNome);
				m_ctrlListOff.SetItemData(index, gruppiSet.m_lID);
				i++;
			}

			gruppiSet.MoveNext();
		}

		gruppiSet.CloseRecordset("CModifyGridCLPrivilegiConfigDlg::RiempiListaOff");
	}

	m_ctrlListOff.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void  CModifyGridCLPrivilegiConfigDlg::RiempiListaOn()
{
	m_ctrlListOn.InsertColumn(0, "");

	int i = 0;
	POSITION pos = theApp.m_listGridCLGruppiAssociati[m_iGridIndex].GetHeadPosition();
	while (pos)
	{
		int idGruppo = theApp.m_listGridCLGruppiAssociati[m_iGridIndex].GetNext(pos);

		int index = m_ctrlListOn.InsertItem(i, CGruppiSet().GetDescrizione(idGruppo));
		m_ctrlListOn.SetItemData(index, idGruppo);

		i++;
	}

}


void CModifyGridCLPrivilegiConfigDlg::OnBnClickedBtnOn()
{
	POSITION pos = m_ctrlListOff.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlListOff.GetNextSelectedItem(pos);
		if (index >= 0)
		{
			CString temp = m_ctrlListOff.GetItemText(index, 0);
			long itemData = m_ctrlListOff.GetItemData(index);
			m_ctrlListOff.DeleteItem(index);
			int i = m_ctrlListOn.InsertItem(m_ctrlListOn.GetItemCount(), temp);
			m_ctrlListOn.SetItemText(i, 1, temp);			
			m_ctrlListOn.SetItemData(i, itemData);
		}
	}

	m_ctrlListOn.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}


void CModifyGridCLPrivilegiConfigDlg::OnBnClickedBtnOff()
{
	POSITION pos = m_ctrlListOn.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlListOn.GetNextSelectedItem(pos);
		if (index >= 0)
		{
			CString temp = m_ctrlListOn.GetItemText(index, 0);
			long itemData = m_ctrlListOn.GetItemData(index);
			m_ctrlListOn.DeleteItem(index);
			int i = m_ctrlListOff.InsertItem(m_ctrlListOff.GetItemCount(), temp);
			m_ctrlListOff.SetItemData(i, itemData);
		}
	}

	m_ctrlListOn.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void CModifyGridCLPrivilegiConfigDlg::OnLvnItemchangedListOff(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnOn.EnableWindow(m_ctrlListOff.GetSelectedCount() > 0);

	*pResult = 0;
}


void CModifyGridCLPrivilegiConfigDlg::OnLvnItemchangedListOn(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnOff.EnableWindow(m_ctrlListOn.GetSelectedCount() > 0);
		
	*pResult = 0;
}
