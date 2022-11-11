#include "stdafx.h"
#include "Endox.h"
#include "FasiGruppiConfigDlg.h"

#include "FasiEsameGruppiSet.h"
#include "GruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFasiGruppiConfigDlg, CXTResizeDialog)

CFasiGruppiConfigDlg::CFasiGruppiConfigDlg(CWnd* pParent, long lIdFase)
: CXTResizeDialog(CFasiGruppiConfigDlg::IDD, pParent)
{
	m_lIdFase = lIdFase;
}

CFasiGruppiConfigDlg::~CFasiGruppiConfigDlg()
{
}

void CFasiGruppiConfigDlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CFasiGruppiConfigDlg, CXTResizeDialog)
	ON_BN_CLICKED(IDC_BTN_ON, &CFasiGruppiConfigDlg::OnBnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_OFF, &CFasiGruppiConfigDlg::OnBnClickedBtnOff)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OFF, &CFasiGruppiConfigDlg::OnLvnItemchangedListOff)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ON, &CFasiGruppiConfigDlg::OnLvnItemchangedListOn)
END_MESSAGE_MAP()

// CModifyFieldAnamnesisDlg message handlers

BOOL CFasiGruppiConfigDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_LIST_OFF, 0.0f, 0.0f, 0.5f, 1.0f);
	SetResize(IDC_LIST_ON, 0.5f, 0.0f, 1.0f, 1.0f);
	SetResize(IDC_BTN_OFF, 0.5f, 0.0f, 0.5f, 0.0f);
	SetResize(IDC_BTN_ON, 0.5f, 0.0f, 0.5f, 0.0f);
	SetResize(IDOK, 1, 1, 1, 1);
	SetResize(IDCANCEL, 1, 1, 1, 1);
	
	CFasiEsameGruppiSet().GetGruppiList(m_lIdFase, &m_activeGroupList);

	RiempiListaOff();
	RiempiListaOn();

	GetDlgItem(IDOK)->SetFocus();

	theApp.LocalizeDialog(this, CFasiGruppiConfigDlg::IDD, "FasiGruppiConfigDlg");
	return FALSE;
}

void CFasiGruppiConfigDlg::OnOK()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIRM), MB_YESNO) == IDNO)
		return;	

	//Rimuovo la vecchia lista da db
	CString sFilter;
	sFilter.Format("IDFASE=%li", m_lIdFase);
	CFasiEsameGruppiSet fasiGruppiSet;
	fasiGruppiSet.SetOpenFilter(sFilter);

	if (fasiGruppiSet.OpenRecordset("CFasiGruppiConfigDlg::OnOK"))
	{
		while (!fasiGruppiSet.IsEOF())
		{
			fasiGruppiSet.DeleteRecordset("CFasiGruppiConfigDlg::OnOK");

			fasiGruppiSet.MoveNext();
		}

		fasiGruppiSet.CloseRecordset("CFasiGruppiConfigDlg::OnOK");
	}

	//Recupero la lista e la salvo in theApp.m_listGridCLGruppiAssociati[m_iGridIndex]
	fasiGruppiSet.SetOpenFilter("");
	if (fasiGruppiSet.OpenRecordset("CFasiGruppiConfigDlg::OnOK"))
	{
		for (int i = 0; i<m_ctrlListOn.GetItemCount(); i++)
		{
			int idGruppo = m_ctrlListOn.GetItemData(i);

			if (fasiGruppiSet.AddNewRecordset("CFasiGruppiConfigDlg::OnOK"))
			{
				fasiGruppiSet.m_lIDFase = m_lIdFase;
				fasiGruppiSet.m_lIDGruppo = idGruppo;

				fasiGruppiSet.UpdateRecordset("CFasiGruppiConfigDlg::OnOK");
			}

		}

		fasiGruppiSet.CloseRecordset("CFasiGruppiConfigDlg::OnOK");
	}

	CDialog::OnOK();
}

void CFasiGruppiConfigDlg::OnCancel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ABORT), MB_YESNO) == IDNO)
		return;

	CDialog::OnCancel();
}


void  CFasiGruppiConfigDlg::RiempiListaOff()
{
	m_ctrlListOff.InsertColumn(0, "");	

	CGruppiSet gruppiSet;
	if (gruppiSet.OpenRecordset("CFasiGruppiConfigDlg::RiempiListaOff"))
	{
		int i = 0;

		while (!gruppiSet.IsEOF())
		{
			//Se non è tra i selezionati			
			if (m_activeGroupList.Find(gruppiSet.m_lID) == NULL)
			{
				int index = m_ctrlListOff.InsertItem(i, gruppiSet.m_sNome);
				m_ctrlListOff.SetItemData(index, gruppiSet.m_lID);
				i++;
			}

			gruppiSet.MoveNext();
		}

		gruppiSet.CloseRecordset("CFasiGruppiConfigDlg::RiempiListaOff");
	}

	m_ctrlListOff.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void  CFasiGruppiConfigDlg::RiempiListaOn()
{
	m_ctrlListOn.InsertColumn(0, "");

	int i = 0;
	POSITION pos = m_activeGroupList.GetHeadPosition();
	while (pos)
	{
		int idGruppo = m_activeGroupList.GetNext(pos);

		int index = m_ctrlListOn.InsertItem(i, CGruppiSet().GetDescrizione(idGruppo));
		m_ctrlListOn.SetItemData(index, idGruppo);

		i++;
	}

}


void CFasiGruppiConfigDlg::OnBnClickedBtnOn()
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


void CFasiGruppiConfigDlg::OnBnClickedBtnOff()
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

void CFasiGruppiConfigDlg::OnLvnItemchangedListOff(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnOn.EnableWindow(m_ctrlListOff.GetSelectedCount() > 0);

	*pResult = 0;
}


void CFasiGruppiConfigDlg::OnLvnItemchangedListOn(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnOff.EnableWindow(m_ctrlListOn.GetSelectedCount() > 0);

	*pResult = 0;
}
