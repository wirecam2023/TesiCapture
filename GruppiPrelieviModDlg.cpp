#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviModDlg.h"

#include "GruppiPrelieviItemSet.h"
#include "GruppiPrelieviItemView.h"
#include "GruppiPrelieviModPrestDlg.h"
#include "GruppiPrelieviSet.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviModDlg, CDialog)

CGruppiPrelieviModDlg::CGruppiPrelieviModDlg(CWnd* pParent)
	: CDialog(CGruppiPrelieviModDlg::IDD, pParent)
{
}

CGruppiPrelieviModDlg::~CGruppiPrelieviModDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiPrelieviModDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_BTN_NEW_PREL, OnBnClickedBtnNewPrel)
	ON_BN_CLICKED(IDC_BTN_EDT_PREL, OnBnClickedBtnEdtPrel)
	ON_BN_CLICKED(IDC_BTN_DEL_PREL, OnBnClickedBtnDelPrel)
	ON_BN_CLICKED(ID_BTN_ESCI, OnBnClickedBtnEsci)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_1, OnLvnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_2, OnLvnItemchangedList2)
END_MESSAGE_MAP()

void CGruppiPrelieviModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlBtnSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlBtnUndo);
	DDX_Control(pDX, IDC_BTN_NEW_PREL, m_ctrlBtnNewPrel);
	DDX_Control(pDX, IDC_BTN_EDT_PREL, m_ctrlBtnEdtPrel);
	DDX_Control(pDX, IDC_BTN_DEL_PREL, m_ctrlBtnDelPrel);
	DDX_Control(pDX, ID_BTN_ESCI, m_ctrlBtnEsci);

	DDX_Control(pDX, IDC_EDIT, m_ctrlEdit);

	DDX_Control(pDX, IDC_LIST_1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST_2, m_ctrlList2);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
}

BOOL CGruppiPrelieviModDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStatic1.SetFont(&theApp.m_fontBig);
	m_ctrlStatic2.SetFont(&theApp.m_fontBig);

	m_ctrlList1.SetExtendedStyle(m_ctrlList1.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList1.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList1.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList2.SetExtendedStyle(m_ctrlList2.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList2.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList2.InsertColumn(1, "", LVCFMT_LEFT, 0);
	m_ctrlList2.InsertColumn(2, "", LVCFMT_LEFT, 0);
	m_ctrlList2.InsertColumn(3, "", LVCFMT_LEFT, 0);
	m_ctrlList2.InsertColumn(4, "", LVCFMT_LEFT, 0);
	m_ctrlList2.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList2.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList2.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList2.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);

	RiempiLista1();

	theApp.LocalizeDialog(this, CGruppiPrelieviModDlg::IDD, "GruppiPrelieviModDlg");
	return TRUE;
}

void CGruppiPrelieviModDlg::OnBnClickedBtnNew()
{
	for(int i = 0; i < m_ctrlList1.GetItemCount(); i++)
		m_ctrlList1.SetItemState(i, 0, LVIS_SELECTED);

	CGruppiPrelieviItemSet setP;
	setP.SetOpenFilter("IDGruppo=0");
	if (setP.OpenRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnNew"))
	{
		while(!setP.IsEOF())
		{
			setP.DeleteRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnNew");
			setP.MoveNext();
		}

		setP.CloseRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnNew");
	}

	EditDialog(TRUE);
}

void CGruppiPrelieviModDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGruppiPrelieviModDlg::OnBnClickedBtnDel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_GRUPPIPRELIEVI_ERROR_2), MB_YESNO) == IDYES)
	{
		POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

		int nItem = -1;
		if (pos != NULL)
			nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			CString strFilter;
			strFilter.Format("ID=%li", m_ctrlList1.GetItemData(nItem));

			CGruppiPrelieviSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnDel"))
			{
				if (!setTemp.IsEOF())
					setTemp.DeleteRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnDel");

				setTemp.CloseRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnDel");
			}

			RiempiLista1();
		}
	}
}

void CGruppiPrelieviModDlg::OnBnClickedBtnSave()
{
	CString strNome;
	m_ctrlEdit.GetWindowText(strNome);
	strNome.Trim();

	if (strNome.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_GRUPPIPRELIEVI_ERROR_1));
		return;
	}

	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	int nItem = -1;
	if (pos != NULL)
		nItem = m_ctrlList1.GetNextSelectedItem(pos);

	if (nItem >= 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", (long)m_ctrlList1.GetItemData(nItem));

		CGruppiPrelieviSet setTemp;
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave"))
		{
			if (!setTemp.IsEOF())
			{
				if (setTemp.EditRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave"))
				{
					setTemp.m_sDescrizione = strNome;

					setTemp.UpdateRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave");
				}
			}

			setTemp.CloseRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave");
		}
	}
	else
	{
		CGruppiPrelieviSet setTemp;
		if (setTemp.OpenRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave"))
		{
			if (setTemp.AddNewRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave"))
			{
				setTemp.m_sDescrizione = strNome;
				setTemp.m_sAPSede = CSediEsameSet().GetAPSede(theApp.m_lIDSedeEsameDefault);

				if (setTemp.UpdateRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave"))
				{
					long lNewIDGruppo = setTemp.GetLastAdd();

					CGruppiPrelieviItemSet setP;
					setP.SetOpenFilter("IDGruppo=0");
					if (setP.OpenRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave"))
					{
						while(!setP.IsEOF())
						{
							if (setP.EditRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave"))
							{
								setP.m_lIDGruppo = lNewIDGruppo;
								setP.UpdateRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave");
							}

							setP.MoveNext();
						}

						setP.CloseRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave");
					}
				}
			}

			setTemp.CloseRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnSave");
		}
	}

	RiempiLista1();

	EditDialog(FALSE);
}

void CGruppiPrelieviModDlg::OnBnClickedBtnUndo()
{
	EditDialog(FALSE);
}

void CGruppiPrelieviModDlg::OnBnClickedBtnNewPrel()
{
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	int nItem = -1;
	if (pos != NULL)
		nItem = m_ctrlList1.GetNextSelectedItem(pos);

	if (nItem >= 0)
	{
		CGruppiPrelieviModPrestDlg dlg(this, m_ctrlList1.GetItemData(nItem), 0);
		if (dlg.DoModal())
			RiempiLista2(m_ctrlList1.GetItemData(nItem));
	}
	else
	{
		CGruppiPrelieviModPrestDlg dlg(this, 0, 0);
		if (dlg.DoModal())
			RiempiLista2(0);
	}
}

void CGruppiPrelieviModDlg::OnBnClickedBtnEdtPrel()
{
	POSITION pos1 = m_ctrlList1.GetFirstSelectedItemPosition();

	int nItem1 = -1;
	if (pos1 != NULL)
		nItem1 = m_ctrlList1.GetNextSelectedItem(pos1);

	if (nItem1 >= 0)
	{
		POSITION pos2 = m_ctrlList2.GetFirstSelectedItemPosition();

		int nItem2 = -1;
		if (pos2 != NULL)
			nItem2 = m_ctrlList2.GetNextSelectedItem(pos2);

		if (nItem2 >= 0)
		{
			CGruppiPrelieviModPrestDlg dlg(this, m_ctrlList1.GetItemData(nItem1), m_ctrlList2.GetItemData(nItem2));
			if (dlg.DoModal())
				RiempiLista2(m_ctrlList1.GetItemData(nItem1));
		}
	}
	else
	{
		POSITION pos2 = m_ctrlList2.GetFirstSelectedItemPosition();

		int nItem2 = -1;
		if (pos2 != NULL)
			nItem2 = m_ctrlList2.GetNextSelectedItem(pos2);

		if (nItem2 >= 0)
		{
			CGruppiPrelieviModPrestDlg dlg(this, 0, m_ctrlList2.GetItemData(nItem2));
			if (dlg.DoModal())
				RiempiLista2(0);
		}
	}
}

void CGruppiPrelieviModDlg::OnBnClickedBtnDelPrel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_GRUPPIPRELIEVI_ERROR_3), MB_YESNO) == IDYES)
	{
		POSITION pos2 = m_ctrlList2.GetFirstSelectedItemPosition();

		int nItem2 = -1;
		if (pos2 != NULL)
			nItem2 = m_ctrlList2.GetNextSelectedItem(pos2);

		if (nItem2 >= 0)
		{
			CString strFilter;
			strFilter.Format("ID=%li", m_ctrlList2.GetItemData(nItem2));

			CGruppiPrelieviItemSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnDelPrel"))
			{
				if (!setTemp.IsEOF())
					setTemp.DeleteRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnDelPrel");

				setTemp.CloseRecordset("CGruppiPrelieviModDlg::OnBnClickedBtnDelPrel");
			}


			POSITION pos1 = m_ctrlList1.GetFirstSelectedItemPosition();

			int nItem1 = -1;
			if (pos1 != NULL)
				nItem1 = m_ctrlList1.GetNextSelectedItem(pos1);

			if (nItem1 >= 0)
				RiempiLista2(m_ctrlList1.GetItemData(nItem1));
			else
				RiempiLista2(0);
		}
	}
}

void CGruppiPrelieviModDlg::OnBnClickedBtnEsci()
{
	CDialog::OnOK();
}

void CGruppiPrelieviModDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	m_ctrlBtnEdt.EnableWindow(pos != NULL);
	m_ctrlBtnDel.EnableWindow(pos != NULL);

	int nItem = -1;
	if (pos != NULL)
		nItem = m_ctrlList1.GetNextSelectedItem(pos);

	if (nItem >= 0)
	{
		RiempiLista2(m_ctrlList1.GetItemData(nItem));
		m_ctrlEdit.SetWindowText(m_ctrlList1.GetItemText(nItem, 0));
	}
	else
	{
		m_ctrlList2.DeleteAllItems();
		m_ctrlEdit.SetWindowText("");
	}
}

void CGruppiPrelieviModDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();

	m_ctrlBtnEdtPrel.EnableWindow(pos != NULL);
	m_ctrlBtnDelPrel.EnableWindow(pos != NULL);
}

void CGruppiPrelieviModDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList1.EnableWindow(!bEdit);
	m_ctrlEdit.SetReadOnly(!bEdit);
	m_ctrlBtnNew.ShowWindow(!bEdit);
	m_ctrlBtnEdt.ShowWindow(!bEdit);
	m_ctrlBtnDel.ShowWindow(!bEdit);
	m_ctrlBtnSave.ShowWindow(bEdit);
	m_ctrlBtnUndo.ShowWindow(bEdit);

	// m_ctrlList2.EnableWindow(!bEdit);
	m_ctrlBtnNewPrel.ShowWindow(bEdit);
	m_ctrlBtnEdtPrel.ShowWindow(bEdit);
	m_ctrlBtnDelPrel.ShowWindow(bEdit);

	m_ctrlBtnEsci.EnableWindow(!bEdit);
}

void CGruppiPrelieviModDlg::RiempiLista1()
{
	BeginWaitCursor();
	m_ctrlList1.SetRedraw(FALSE);
	m_ctrlList1.DeleteAllItems();

	CString strFilter;
	strFilter.Format("APSede='%s'", CSediEsameSet().GetAPSede(theApp.m_lIDSedeEsameDefault));

	CGruppiPrelieviSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CGruppiPrelieviModDlg::RiempiLista1"))
	{
		int nItem = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlList1.InsertItem(nItem, setTemp.m_sDescrizione);
			m_ctrlList1.SetItemData(nItem, (DWORD)setTemp.m_lID);

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiPrelieviModDlg::RiempiLista1");
	}

	m_ctrlList1.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGruppiPrelieviModDlg::RiempiLista2(long lID)
{
	BeginWaitCursor();
	m_ctrlList2.SetRedraw(FALSE);
	m_ctrlList2.DeleteAllItems();

	CString strFilter;
	strFilter.Format("IDGruppo='%li'", lID);

	CGruppiPrelieviItemView setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CGruppiPrelieviModDlg::RiempiLista2"))
	{
		int nItem = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlList2.InsertItem(nItem, setTemp.m_sTipo);
			m_ctrlList2.SetItemData(nItem, (DWORD)setTemp.m_lID);

			m_ctrlList2.SetItemText(nItem, 1, setTemp.m_sIntervento);

			CString strNum;
			strNum.Format("%li", setTemp.m_lPrelievi);
			m_ctrlList2.SetItemText(nItem, 2, strNum);

			m_ctrlList2.SetItemText(nItem, 3, setTemp.m_sDescrizione);

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiPrelieviModDlg::RiempiLista2");
	}

	m_ctrlList2.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList2.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList2.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList2.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList2.SetRedraw(TRUE);
	EndWaitCursor();
}