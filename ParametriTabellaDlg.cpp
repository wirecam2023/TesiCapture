#include "stdafx.h"
#include "Endox.h"
#include "ParametriTabellaDlg.h"

#include "EditStringDlg.h"
#include "ParametriTabellaNewEdtDlg.h"
#include "TabellaParametriSet.h"
#include "TabellaStruttureSet.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CParametriTabellaDlg, CDialog)

CParametriTabellaDlg::CParametriTabellaDlg(CWnd* pParent)
	: CDialog(CParametriTabellaDlg::IDD, pParent)
{
}

CParametriTabellaDlg::~CParametriTabellaDlg()
{
}

BEGIN_MESSAGE_MAP(CParametriTabellaDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_STRUT_NEW, OnBnClickedBtnStrutNew)
	ON_BN_CLICKED(IDC_BTN_STRUT_EDT, OnBnClickedBtnStrutEdt)
	ON_BN_CLICKED(IDC_BTN_STRUT_DEL, OnBnClickedBtnStrutDel)
	ON_BN_CLICKED(IDC_BTN_PARAM_NEW, OnBnClickedBtnParamNew)
	ON_BN_CLICKED(IDC_BTN_PARAM_EDT, OnBnClickedBtnParamEdt)
	ON_BN_CLICKED(IDC_BTN_PARAM_DEL, OnBnClickedBtnParamDel)

	ON_CBN_SELCHANGE(IDC_COMBO_TIPOESAME, OnCbnSelchangeComboTipoEsame)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STRUTTURE, OnLvnItemchangedListStrutture)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PARAMETRI, OnLvnItemchangedListParametri)

	ON_BN_CLICKED(IDC_BTN_STRUT_UP, OnBnClickedBtnStrutUp)
	ON_BN_CLICKED(IDC_BTN_STRUT_DW, OnBnClickedBtnStrutDw)
	ON_BN_CLICKED(IDC_BTN_PARAM_UP, OnBnClickedBtnParamUp)
	ON_BN_CLICKED(IDC_BTN_PARAM_DW, OnBnClickedBtnParamDw)

	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBnClose)

END_MESSAGE_MAP()

void CParametriTabellaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_STRUT_NEW, m_ctrlBtnStrutNew);
	DDX_Control(pDX, IDC_BTN_STRUT_EDT, m_ctrlBtnStrutEdt);
	DDX_Control(pDX, IDC_BTN_STRUT_DEL, m_ctrlBtnStrutDel);
	DDX_Control(pDX, IDC_BTN_STRUT_UP, m_ctrlBtnStrutUp);
	DDX_Control(pDX, IDC_BTN_STRUT_DW, m_ctrlBtnStrutDw);
	DDX_Control(pDX, IDC_BTN_PARAM_NEW, m_ctrlBtnParamNew);
	DDX_Control(pDX, IDC_BTN_PARAM_EDT, m_ctrlBtnParamEdt);
	DDX_Control(pDX, IDC_BTN_PARAM_DEL, m_ctrlBtnParamDel);
	DDX_Control(pDX, IDC_BTN_PARAM_UP, m_ctrlBtnParamUp);
	DDX_Control(pDX, IDC_BTN_PARAM_DW, m_ctrlBtnParamDw);

	DDX_Control(pDX, IDC_COMBO_TIPOESAME, m_ctrlCmbTipoEsame);

	DDX_Control(pDX, IDC_LIST_STRUTTURE, m_ctrlListStrutture);
	DDX_Control(pDX, IDC_LIST_PARAMETRI, m_ctrlListParametri);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
}

void CParametriTabellaDlg::OnCancel()
{
}

BOOL CParametriTabellaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	RiempiComboTipoEsame();

	//

	m_ctrlListStrutture.SetExtendedStyle(m_ctrlListStrutture.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	m_ctrlListStrutture.InsertColumn(0, theApp.GetMessageString(IDS_ORDINE));
	m_ctrlListStrutture.InsertColumn(1, theApp.GetMessageString(IDS_STRUTTURA));

	m_ctrlListStrutture.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListStrutture.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	//

	m_ctrlListParametri.SetExtendedStyle(m_ctrlListParametri.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	m_ctrlListParametri.InsertColumn(0, theApp.GetMessageString(IDS_ORDINE));
	m_ctrlListParametri.InsertColumn(1, theApp.GetMessageString(IDS_PARAMETRO));
	m_ctrlListParametri.InsertColumn(2, theApp.GetMessageString(IDS_FORMULA));
	m_ctrlListParametri.InsertColumn(3, theApp.GetMessageString(IDS_DECIMALI));
	m_ctrlListParametri.InsertColumn(4, theApp.GetMessageString(IDS_RIFERIMENTO_M));
	m_ctrlListParametri.InsertColumn(5, theApp.GetMessageString(IDS_RIFERIMENTO_F));
	m_ctrlListParametri.InsertColumn(6, theApp.GetMessageString(IDS_RIFERIMENTO_PED00));
	m_ctrlListParametri.InsertColumn(7, theApp.GetMessageString(IDS_RIFERIMENTO_PED01));
	m_ctrlListParametri.InsertColumn(8, theApp.GetMessageString(IDS_RIFERIMENTO_PED02));
	m_ctrlListParametri.InsertColumn(9, theApp.GetMessageString(IDS_RIFERIMENTO_PED03));
	m_ctrlListParametri.InsertColumn(10, theApp.GetMessageString(IDS_RIFERIMENTO_PED04));
	m_ctrlListParametri.InsertColumn(11, theApp.GetMessageString(IDS_RIFERIMENTO_PED05));
	m_ctrlListParametri.InsertColumn(12, theApp.GetMessageString(IDS_RIFERIMENTO_PED06));
	m_ctrlListParametri.InsertColumn(13, "");

	m_ctrlListParametri.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(8, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(9, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(10, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(11, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(12, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(13, 0);

	//

	theApp.LocalizeDialog(this, CParametriTabellaDlg::IDD, "ParametriTabellaDlg");
	return TRUE;
}

void CParametriTabellaDlg::OnOK()
{
}

void CParametriTabellaDlg::OnBnClickedBtnClose()
{
	if (m_ctrlBtnClose.IsWindowEnabled())
		CDialog::OnOK();
}

void CParametriTabellaDlg::RiempiComboTipoEsame()
{
	m_ctrlCmbTipoEsame.SetRedraw(FALSE);
	m_ctrlCmbTipoEsame.ResetContent();

	m_ctrlCmbTipoEsame.InsertString(0, "");
	m_ctrlCmbTipoEsame.SetItemData(0, 0);

	CTipoEsameSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CParametriTabellaDlg::RiempiComboTipoEsame"))
	{
		int nIndex = 1;
		while (!setTemp.IsEOF())
		{
			m_ctrlCmbTipoEsame.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCmbTipoEsame.SetItemData(nIndex, setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CParametriTabellaDlg::RiempiComboTipoEsame");
	}

	m_ctrlCmbTipoEsame.SetCurSel(0);
	m_ctrlCmbTipoEsame.SetRedraw(TRUE);
}

void CParametriTabellaDlg::RiempiListaStrutture(long lIDToSel)
{
	BeginWaitCursor();

	m_ctrlListStrutture.SetRedraw(FALSE);
	m_ctrlListParametri.SetRedraw(FALSE);

	m_ctrlListStrutture.DeleteAllItems();
	m_ctrlListParametri.DeleteAllItems();

	m_ctrlBtnStrutNew.EnableWindow(FALSE);
	m_ctrlBtnStrutEdt.EnableWindow(FALSE);
	m_ctrlBtnStrutDel.EnableWindow(FALSE);
	m_ctrlBtnStrutUp.EnableWindow(FALSE);
	m_ctrlBtnStrutDw.EnableWindow(FALSE);

	m_ctrlBtnParamNew.EnableWindow(FALSE);
	m_ctrlBtnParamEdt.EnableWindow(FALSE);
	m_ctrlBtnParamDel.EnableWindow(FALSE);
	m_ctrlBtnParamUp.EnableWindow(FALSE);
	m_ctrlBtnParamDw.EnableWindow(FALSE);

	int nItemToSel = -1;

	int nCurSel = m_ctrlCmbTipoEsame.GetCurSel();
	if (nCurSel > 0)
	{
		long lIDTipoEsame = m_ctrlCmbTipoEsame.GetItemData(nCurSel);
		if (lIDTipoEsame > 0)
		{
			m_ctrlBtnStrutNew.EnableWindow(TRUE);

			CString sFilter;
			sFilter.Format("IDTipoEsame=%li", lIDTipoEsame);

			CTabellaStruttureSet setTemp;
			setTemp.SetOpenFilter(sFilter);
			setTemp.SetSortRecord("Ordine, ID");
			if (setTemp.OpenRecordset("CParametriTabellaDlg::OnCbnSelchangeComboTipoEsame"))
			{
				int nItem = 0;
				while (!setTemp.IsEOF())
				{
					CString sOrdine;
					sOrdine.Format("%d", nItem + 1);

					m_ctrlListStrutture.InsertItem(nItem, sOrdine);
					m_ctrlListStrutture.SetItemData(nItem, setTemp.m_lID);

					m_ctrlListStrutture.SetItemText(nItem, 1, setTemp.m_sStruttura);

					if (setTemp.m_lID == lIDToSel)
						nItemToSel = nItem;

					nItem++;
					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CParametriTabellaDlg::OnCbnSelchangeComboTipoEsame");
			}
		}
	}

	m_ctrlListStrutture.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListStrutture.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListParametri.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(8, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(9, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(10, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(11, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(12, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(13, 0);

	m_ctrlListStrutture.SetRedraw(TRUE);
	m_ctrlListParametri.SetRedraw(TRUE);

	if (nItemToSel >= 0)
		m_ctrlListStrutture.SetItemState(nItemToSel, LVIS_SELECTED, LVIS_SELECTED);

	EndWaitCursor();
}

void CParametriTabellaDlg::RiempiListaParametri(long lIDToSel)
{
	BeginWaitCursor();

	m_ctrlListParametri.SetRedraw(FALSE);
	m_ctrlListParametri.DeleteAllItems();

	m_ctrlBtnStrutEdt.EnableWindow(FALSE);
	m_ctrlBtnStrutDel.EnableWindow(FALSE);
	m_ctrlBtnStrutUp.EnableWindow(FALSE);
	m_ctrlBtnStrutDw.EnableWindow(FALSE);

	m_ctrlBtnParamNew.EnableWindow(FALSE);
	m_ctrlBtnParamEdt.EnableWindow(FALSE);
	m_ctrlBtnParamDel.EnableWindow(FALSE);
	m_ctrlBtnParamUp.EnableWindow(FALSE);
	m_ctrlBtnParamDw.EnableWindow(FALSE);

	int nItemToSel = -1;

	POSITION pos = m_ctrlListStrutture.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListStrutture.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDStruttura = m_ctrlListStrutture.GetItemData(nCurSel);
			if (lIDStruttura > 0)
			{
				m_ctrlBtnStrutEdt.EnableWindow(TRUE);
				m_ctrlBtnStrutDel.EnableWindow(TRUE);

				if (nCurSel > 0)
					m_ctrlBtnStrutUp.EnableWindow(TRUE);

				if (nCurSel < m_ctrlListStrutture.GetItemCount() - 1)
					m_ctrlBtnStrutDw.EnableWindow(TRUE);

				m_ctrlBtnParamNew.EnableWindow(TRUE);

				CString sFilter;
				sFilter.Format("IDStruttura=%li", lIDStruttura);

				CTabellaParametriSet setTemp;
				setTemp.SetOpenFilter(sFilter);
				setTemp.SetSortRecord("Ordine, ID");
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnLvnItemchangedListStrutture"))
				{
					int nItem = 0;
					while (!setTemp.IsEOF())
					{
						CString sOrdine;
						sOrdine.Format("%d", nItem + 1);

						m_ctrlListParametri.InsertItem(nItem, sOrdine);
						m_ctrlListParametri.SetItemData(nItem, setTemp.m_lID);

						m_ctrlListParametri.SetItemText(nItem, 1, setTemp.m_sParametro);

						m_ctrlListParametri.SetItemText(nItem, 2, setTemp.m_sFormula);

						CString sDecimali;
						sDecimali.Format("%li", setTemp.m_lDecimali);
						m_ctrlListParametri.SetItemText(nItem, 3, sDecimali);

						m_ctrlListParametri.SetItemText(nItem, 4, setTemp.m_sRiferimentoM);

						m_ctrlListParametri.SetItemText(nItem, 5, setTemp.m_sRiferimentoF);

						m_ctrlListParametri.SetItemText(nItem, 6, setTemp.m_sRiferimentoPed00);

						m_ctrlListParametri.SetItemText(nItem, 7, setTemp.m_sRiferimentoPed01);

						m_ctrlListParametri.SetItemText(nItem, 8, setTemp.m_sRiferimentoPed02);

						m_ctrlListParametri.SetItemText(nItem, 9, setTemp.m_sRiferimentoPed03);

						m_ctrlListParametri.SetItemText(nItem, 10, setTemp.m_sRiferimentoPed04);

						m_ctrlListParametri.SetItemText(nItem, 11, setTemp.m_sRiferimentoPed05);

						m_ctrlListParametri.SetItemText(nItem, 12, setTemp.m_sRiferimentoPed06);

						if (setTemp.m_lID == lIDToSel)
							nItemToSel = nItem;

						nItem++;
						setTemp.MoveNext();
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnLvnItemchangedListStrutture");
				}
			}
		}
	}

	m_ctrlListParametri.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(8, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(9, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(10, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(11, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(12, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListParametri.SetColumnWidth(13, 0);

	m_ctrlListParametri.SetRedraw(TRUE);

	if (nItemToSel >= 0)
		m_ctrlListParametri.SetItemState(nItemToSel, LVIS_SELECTED, LVIS_SELECTED);

	EndWaitCursor();
}

void CParametriTabellaDlg::OnCbnSelchangeComboTipoEsame()
{
	RiempiListaStrutture(0);
}

void CParametriTabellaDlg::OnLvnItemchangedListStrutture(NMHDR *pNMHDR, LRESULT *pResult)
{
	RiempiListaParametri(0);
}

void CParametriTabellaDlg::OnLvnItemchangedListParametri(NMHDR *pNMHDR, LRESULT *pResult)
{
	BeginWaitCursor();

	m_ctrlBtnParamEdt.EnableWindow(FALSE);
	m_ctrlBtnParamDel.EnableWindow(FALSE);
	m_ctrlBtnParamUp.EnableWindow(FALSE);
	m_ctrlBtnParamDw.EnableWindow(FALSE);

	POSITION pos = m_ctrlListParametri.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListParametri.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDParametro = m_ctrlListParametri.GetItemData(nCurSel);
			if (lIDParametro > 0)
			{
				m_ctrlBtnParamEdt.EnableWindow(TRUE);
				m_ctrlBtnParamDel.EnableWindow(TRUE);

				if (nCurSel > 0)
					m_ctrlBtnParamUp.EnableWindow(TRUE);

				if (nCurSel < m_ctrlListParametri.GetItemCount() - 1)
					m_ctrlBtnParamDw.EnableWindow(TRUE);
			}
		}
	}

	EndWaitCursor();
}

void CParametriTabellaDlg::OnBnClickedBtnStrutNew()
{
	CEditStringDlg dlg(this, IDS_NEW_STRUTTURA, "");
	if (dlg.DoModal() == IDOK)
	{
		CTabellaStruttureSet setTemp;
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutNew"))
		{
			if (setTemp.AddNewRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutNew"))
			{
				setTemp.m_lIDTipoEsame = m_ctrlCmbTipoEsame.GetItemData(m_ctrlCmbTipoEsame.GetCurSel());
				setTemp.m_lOrdine = m_ctrlListStrutture.GetItemCount() + 1;
				setTemp.m_sStruttura = dlg.GetValue();

				if (setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutNew"))
					RiempiListaStrutture(setTemp.GetLastAdd());
			}

			setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutNew");
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnStrutEdt()
{
	POSITION pos = m_ctrlListStrutture.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListStrutture.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDStruttura = m_ctrlListStrutture.GetItemData(nCurSel);
			if (lIDStruttura > 0)
			{
				CEditStringDlg dlg(this, IDS_EDT_STRUTTURA, m_ctrlListStrutture.GetItemText(nCurSel, 1));
				if (dlg.DoModal() == IDOK)
				{
					CString sFilter;
					sFilter.Format("ID=%li", lIDStruttura);

					CTabellaStruttureSet setTemp;
					setTemp.SetOpenFilter(sFilter);
					if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutEdt"))
					{
						if (!setTemp.IsEOF())
						{
							if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutEdt"))
							{
								setTemp.m_sStruttura = dlg.GetValue();

								if (setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutEdt"))
									RiempiListaStrutture(lIDStruttura);
							}
						}

						setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutEdt");
					}
				}
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnStrutDel()
{
	POSITION pos = m_ctrlListStrutture.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListStrutture.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDStruttura = m_ctrlListStrutture.GetItemData(nCurSel);
			if (lIDStruttura > 0)
			{
				if (theApp.AfxMessageBoxEndo(IDS_DEL_STRUTTURA, MB_YESNO) == IDYES)
				{
					BOOL bDeleted = FALSE;
					long lOriginalOrder = 0;

					CString sFilter;
					sFilter.Format("ID=%li", lIDStruttura);

					CTabellaStruttureSet setTemp;
					setTemp.SetOpenFilter(sFilter);
					if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDel"))
					{
						if (!setTemp.IsEOF())
						{
							lOriginalOrder = setTemp.m_lOrdine;
							bDeleted = setTemp.DeleteRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDel");
						}

						setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDel");
					}

					if (bDeleted)
					{
						sFilter.Format("IDTipoEsame=%li AND Ordine>%li", m_ctrlCmbTipoEsame.GetItemData(m_ctrlCmbTipoEsame.GetCurSel()), lOriginalOrder);

						setTemp.SetOpenFilter(sFilter);
						setTemp.SetSortRecord("Ordine, ID");

						if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDel"))
						{
							while (!setTemp.IsEOF())
							{
								if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDel"))
								{
									setTemp.m_lOrdine--;
									setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDel");
								}

								setTemp.MoveNext();
							}

							setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDel");
						}
					}

					RiempiListaStrutture(lIDStruttura);
				}
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnStrutUp()
{
	POSITION pos = m_ctrlListStrutture.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListStrutture.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDStruttura = m_ctrlListStrutture.GetItemData(nCurSel);
			if (lIDStruttura > 0)
			{
				long lOrdinePrec = 0;
				CString sFilter;
				CTabellaStruttureSet setTemp;

				// decremento l'ordine dell'elemento selezionato //

				sFilter.Format("ID=%li", lIDStruttura);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp"))
						{
							setTemp.m_lOrdine--;
							if (setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp"))
								lOrdinePrec = setTemp.m_lOrdine;
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp");
				}

				// incremento l'ordine dell'elemento che stava prima //

				sFilter.Format("IDTipoEsame=%li AND Ordine=%li AND ID<>%li", m_ctrlCmbTipoEsame.GetItemData(m_ctrlCmbTipoEsame.GetCurSel()), lOrdinePrec, lIDStruttura);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp"))
						{
							setTemp.m_lOrdine++;
							setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp");
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutUp");
				}

				//

				RiempiListaStrutture(lIDStruttura);
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnStrutDw()
{
	POSITION pos = m_ctrlListStrutture.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListStrutture.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDStruttura = m_ctrlListStrutture.GetItemData(nCurSel);
			if (lIDStruttura > 0)
			{
				long lOrdineSucc = 0;
				CString sFilter;
				CTabellaStruttureSet setTemp;

				// incremento l'ordine dell'elemento selezionato //

				sFilter.Format("ID=%li", lIDStruttura);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw"))
						{
							setTemp.m_lOrdine++;
							if (setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw"))
								lOrdineSucc = setTemp.m_lOrdine;
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw");
				}

				// decremento l'ordine dell'elemento che stava dopo //

				sFilter.Format("IDTipoEsame=%li AND Ordine=%li AND ID<>%li", m_ctrlCmbTipoEsame.GetItemData(m_ctrlCmbTipoEsame.GetCurSel()), lOrdineSucc, lIDStruttura);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw"))
						{
							setTemp.m_lOrdine--;
							setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw");
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnStrutDw");
				}

				//

				RiempiListaStrutture(lIDStruttura);
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnParamNew()
{
	POSITION pos = m_ctrlListStrutture.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListStrutture.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDStruttura = m_ctrlListStrutture.GetItemData(nCurSel);
			if (lIDStruttura > 0)
			{
				CParametriTabellaNewEdtDlg dlg(this, 0, lIDStruttura, m_ctrlListParametri.GetItemCount() + 1);
				if (dlg.DoModal() == IDOK)
					RiempiListaParametri(dlg.GetLastAdd());
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnParamEdt()
{
	POSITION pos1 = m_ctrlListStrutture.GetFirstSelectedItemPosition();
	if (pos1 != NULL)
	{
		int nCurSel1 = m_ctrlListStrutture.GetNextSelectedItem(pos1);
		if (nCurSel1 >= 0)
		{
			long lIDStruttura = m_ctrlListStrutture.GetItemData(nCurSel1);
			if (lIDStruttura > 0)
			{
				POSITION pos2 = m_ctrlListParametri.GetFirstSelectedItemPosition();
				if (pos2 != NULL)
				{
					int nCurSel2 = m_ctrlListParametri.GetNextSelectedItem(pos2);
					if (nCurSel2 >= 0)
					{
						long lIDParametro = m_ctrlListParametri.GetItemData(nCurSel2);
						if (lIDParametro > 0)
						{
							CParametriTabellaNewEdtDlg dlg(this, lIDParametro, lIDStruttura, 0);
							if (dlg.DoModal() == IDOK)
								RiempiListaParametri(lIDParametro);
						}
					}
				}
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnParamDel()
{
	POSITION pos = m_ctrlListParametri.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListParametri.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDParametro = m_ctrlListParametri.GetItemData(nCurSel);
			if (lIDParametro > 0)
			{
				if (theApp.AfxMessageBoxEndo(IDS_DEL_PARAMETRO, MB_YESNO) == IDYES)
				{
					BOOL bDeleted = FALSE;
					long lOriginalStrut = 0;
					long lOriginalOrder = 0;

					CString sFilter;
					sFilter.Format("ID=%li", lIDParametro);

					CTabellaParametriSet setTemp;
					setTemp.SetOpenFilter(sFilter);
					if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnParamDel"))
					{
						if (!setTemp.IsEOF())
						{
							lOriginalStrut = setTemp.m_lIDStruttura;
							lOriginalOrder = setTemp.m_lOrdine;
							bDeleted = setTemp.DeleteRecordset("CParametriTabellaDlg::OnBnClickedBtnParamDel");
						}

						setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnParamDel");
					}

					if (bDeleted)
					{
						sFilter.Format("IDStruttura=%li AND Ordine>%li", lOriginalStrut, lOriginalOrder);

						setTemp.SetOpenFilter(sFilter);
						setTemp.SetSortRecord("Ordine, ID");

						if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnParamDel"))
						{
							while (!setTemp.IsEOF())
							{
								if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnParamDel"))
								{
									setTemp.m_lOrdine--;
									setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnParamDel");
								}

								setTemp.MoveNext();
							}

							setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnParamDel");
						}
					}

					RiempiListaParametri(lIDParametro);
				}
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnParamUp()
{
	POSITION pos = m_ctrlListParametri.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListParametri.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDParametro = m_ctrlListParametri.GetItemData(nCurSel);
			if (lIDParametro > 0)
			{
				long lStruttPrec = 0;
				long lOrdinePrec = 0;
				CString sFilter;
				CTabellaParametriSet setTemp;

				// decremento l'ordine dell'elemento selezionato //

				sFilter.Format("ID=%li", lIDParametro);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
						{
							setTemp.m_lOrdine--;
							if (setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
							{
								lStruttPrec = setTemp.m_lIDStruttura;
								lOrdinePrec = setTemp.m_lOrdine;
							}
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp");
				}

				// incremento l'ordine dell'elemento che stava prima //

				sFilter.Format("IDStruttura=%li AND Ordine=%li AND ID<>%li", lStruttPrec, lOrdinePrec, lIDParametro);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
						{
							setTemp.m_lOrdine++;
							setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp");
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp");
				}

				//

				RiempiListaParametri(lIDParametro);
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClickedBtnParamDw()
{
	POSITION pos = m_ctrlListParametri.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListParametri.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lIDParametro = m_ctrlListParametri.GetItemData(nCurSel);
			if (lIDParametro > 0)
			{
				long lStruttPrec = 0;
				long lOrdinePrec = 0;
				CString sFilter;
				CTabellaParametriSet setTemp;

				// incremento l'ordine dell'elemento selezionato //

				sFilter.Format("ID=%li", lIDParametro);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
						{
							setTemp.m_lOrdine++;
							if (setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
							{
								lStruttPrec = setTemp.m_lIDStruttura;
								lOrdinePrec = setTemp.m_lOrdine;
							}
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp");
				}

				// decremento l'ordine dell'elemento che stava dopo //

				sFilter.Format("IDStruttura=%li AND Ordine=%li AND ID<>%li", lStruttPrec, lOrdinePrec, lIDParametro);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp"))
						{
							setTemp.m_lOrdine--;
							setTemp.UpdateRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp");
						}
					}

					setTemp.CloseRecordset("CParametriTabellaDlg::OnBnClickedBtnParamUp");
				}

				//

				RiempiListaParametri(lIDParametro);
			}
		}
	}
}

void CParametriTabellaDlg::OnBnClose()
{
	CDialog::OnCancel();
}