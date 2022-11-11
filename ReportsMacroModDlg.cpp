#include "stdafx.h"
#include "Endox.h"
#include "ReportsMacroModDlg.h"

#include "EditStringDlg.h"
#include "PathNumberDlg.h"
#include "ReportsMacroDettSet.h"
#include "ReportsMacroSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CReportsMacroModDlg, CDialog)

CReportsMacroModDlg::CReportsMacroModDlg(CWnd* pParent)
	: CDialog(CReportsMacroModDlg::IDD, pParent)
{
	m_lIDMacro = 0;
}

CReportsMacroModDlg::~CReportsMacroModDlg()
{
}

BEGIN_MESSAGE_MAP(CReportsMacroModDlg, CDialog)

	ON_WM_CTLCOLOR()

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_1, OnLvnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_2, OnLvnItemchangedList2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_STAMPAIMMAGINI, OnDeltaposSpinStampaImmagini)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ETICHETTEISTOPATOLOGIA, OnDeltaposSpinEtichetteIstopatologia)

	ON_BN_CLICKED(IDC_BTN_NEW1, OnBnClickedBtnNew1)
	ON_BN_CLICKED(IDC_BTN_EDT1, OnBnClickedBtnEdt1)
	ON_BN_CLICKED(IDC_BTN_DEL1, OnBnClickedBtnDel1)
	ON_BN_CLICKED(IDC_BTN_NEW2, OnBnClickedBtnNew2)
	ON_BN_CLICKED(IDC_BTN_EDT2, OnBnClickedBtnEdt2)
	ON_BN_CLICKED(IDC_BTN_DEL2, OnBnClickedBtnDel2)
	ON_BN_CLICKED(IDC_BTN_UP, OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DN, OnBnClickedBtnDn)
	ON_BN_CLICKED(IDC_CHECK_STAMPAIMMAGINI, OnBnClickedCheckStampaImmagini)
	ON_BN_CLICKED(IDC_CHECK_ETICHETTE, OnBnClickedCheckEtichette)

	ON_CBN_SELCHANGE(IDC_COMBO, OnCbnSelchangeCombo)

END_MESSAGE_MAP()

void CReportsMacroModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW1, m_ctrlBtnNew1);
	DDX_Control(pDX, IDC_BTN_EDT1, m_ctrlBtnEdt1);
	DDX_Control(pDX, IDC_BTN_DEL1, m_ctrlBtnDel1);
	DDX_Control(pDX, IDC_BTN_NEW2, m_ctrlBtnNew2);
	DDX_Control(pDX, IDC_BTN_EDT2, m_ctrlBtnEdt2);
	DDX_Control(pDX, IDC_BTN_DEL2, m_ctrlBtnDel2);
	DDX_Control(pDX, IDC_BTN_UP, m_ctrlBtnUp);
	DDX_Control(pDX, IDC_BTN_DN, m_ctrlBtnDn);
	DDX_Control(pDX, IDC_CHECK_STAMPAIMMAGINI, m_ctrlCheckStampaImmagini);
	DDX_Control(pDX, IDC_CHECK_ETICHETTE, m_ctrlCheckEtichette);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_COMBO, m_ctrlCombo);

	DDX_Control(pDX, IDC_EDIT_STAMPAIMMAGINI, m_ctrlEditStampaImmagini);
	DDX_Control(pDX, IDC_EDIT_ETICHETTEISTOPATOLOGIA, m_ctrlEditEtichetteIstopatologia);

	DDX_Control(pDX, IDC_LIST_1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST_2, m_ctrlList2);

	DDX_Control(pDX, IDC_SPIN_STAMPAIMMAGINI, m_ctrlSpinStampaImmagini);
	DDX_Control(pDX, IDC_SPIN_ETICHETTEISTOPATOLOGIA, m_ctrlSpinEtichetteIstopatologia);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
}

void CReportsMacroModDlg::OnCancel()
{
}

HBRUSH CReportsMacroModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_1:
		case IDC_LIST_1:
		case IDC_BTN_NEW1:
		case IDC_BTN_EDT1:
		case IDC_BTN_DEL1:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_STATIC_2:
		case IDC_LIST_2:
		case IDC_BTN_NEW2:
		case IDC_BTN_EDT2:
		case IDC_BTN_DEL2:
		case IDC_BTN_UP:
		case IDC_BTN_DN:
		case IDC_CHECK_STAMPAIMMAGINI:
		case IDC_CHECK_ETICHETTE:
		{
			pDC->SetTextColor(theApp.m_color[3]);
			break;
		}
	}

	return hBrush;
}

BOOL CReportsMacroModDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStatic1.SetFont(&theApp.m_fontBold);
	m_ctrlStatic2.SetFont(&theApp.m_fontBold);
	m_ctrlStatic3.SetFont(&theApp.m_fontBold);
	m_ctrlStatic4.SetFont(&theApp.m_fontBold);

	m_ctrlList1.SetExtendedStyle(m_ctrlList1.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList1.InsertColumn(0, "");
	m_ctrlList1.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList2.SetExtendedStyle(m_ctrlList2.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList2.InsertColumn(0, "", LVCFMT_LEFT, 30);
	m_ctrlList2.InsertColumn(1, "Report", LVCFMT_LEFT, 500);
	m_ctrlList2.InsertColumn(2, "Copie", LVCFMT_CENTER, 45);

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpinStampaImmagini.SetRange32(0, 9);
	m_ctrlSpinStampaImmagini.SetPos32(1);
	m_ctrlSpinStampaImmagini.SetAccel(1, pAccel);

	m_ctrlSpinEtichetteIstopatologia.SetRange32(0, 9);
	m_ctrlSpinEtichetteIstopatologia.SetPos32(1);
	m_ctrlSpinEtichetteIstopatologia.SetAccel(1, pAccel);

	RiempiLista1();

	theApp.LocalizeDialog(this, CReportsMacroModDlg::IDD, "ReportsMacroModDlg");
	return TRUE;
}

void CReportsMacroModDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CReportsMacroModDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bOK = FALSE;
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	m_lIDMacro = 0;

	if (pos != NULL)
	{
		int nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			m_lIDMacro = (long)m_ctrlList1.GetItemData(nItem);

			long lImmaginiCopie = CReportsMacroSet().GetImmaginiCopie(m_lIDMacro);
			if (lImmaginiCopie >= 0)
			{
				m_ctrlCheckStampaImmagini.SetCheck(BST_CHECKED);

				m_ctrlSpinStampaImmagini.SetPos32(lImmaginiCopie);
				m_ctrlSpinStampaImmagini.EnableWindow(TRUE);
			}
			else
			{
				m_ctrlCheckStampaImmagini.SetCheck(BST_UNCHECKED);

				m_ctrlSpinStampaImmagini.SetPos32(1);
				m_ctrlSpinStampaImmagini.EnableWindow(FALSE);
			}

			long lEtichetteIstopatologiaCopie = CReportsMacroSet().GetEtichetteIstopatologiaCopie(m_lIDMacro);
			if (lEtichetteIstopatologiaCopie >= 0)
			{
				m_ctrlCheckEtichette.SetCheck(BST_CHECKED);

				m_ctrlSpinEtichetteIstopatologia.SetPos32(lEtichetteIstopatologiaCopie);
				m_ctrlSpinEtichetteIstopatologia.EnableWindow(TRUE);
			}
			else
			{
				m_ctrlCheckEtichette.SetCheck(BST_UNCHECKED);

				m_ctrlSpinEtichetteIstopatologia.SetPos32(1);
				m_ctrlSpinEtichetteIstopatologia.EnableWindow(FALSE);
			}

			bOK = TRUE;
		}
	}

	m_ctrlBtnEdt1.EnableWindow(bOK);
	m_ctrlBtnDel1.EnableWindow(bOK);
	m_ctrlBtnNew2.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlBtnEdt2.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlBtnDel2.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlBtnUp.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlBtnDn.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlCheckStampaImmagini.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlCheckEtichette.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlStatic3.ShowWindow((bOK && (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)) ? SW_SHOW : SW_HIDE);
	m_ctrlCombo.ShowWindow((bOK && (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)) ? SW_SHOW : SW_HIDE);
	m_ctrlStatic4.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlEditStampaImmagini.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlEditEtichetteIstopatologia.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlSpinStampaImmagini.ShowWindow(bOK ? SW_SHOW : SW_HIDE);
	m_ctrlSpinEtichetteIstopatologia.ShowWindow(bOK ? SW_SHOW : SW_HIDE);

	RiempiLista2();
}

void CReportsMacroModDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bOK = FALSE;
	BOOL bUp = FALSE;
	BOOL bDn = FALSE;
	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList2.GetNextSelectedItem(pos);

		bOK = (nItem >= 0);
		bUp = (nItem > 0);
		bDn = (nItem < m_ctrlList2.GetItemCount() - 1);
	}

	m_ctrlBtnEdt2.EnableWindow(bOK);
	m_ctrlBtnDel2.EnableWindow(bOK);
	m_ctrlBtnUp.EnableWindow(bUp);
	m_ctrlBtnDn.EnableWindow(bDn);
}

void CReportsMacroModDlg::OnBnClickedBtnNew1()
{
	CEditStringDlg dlg(this, IDS_REPORTSMACRO_TITLE_1, "");
	if (dlg.DoModal() == IDOK)
	{
		CReportsMacroSet setTemp;

		if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedBtnNew1"))
		{
			if (setTemp.AddNewRecordset("CReportsMacroModDlg::OnBnClickedBtnNew1"))
			{
				setTemp.m_sDescrizione = dlg.GetValue();
				if (setTemp.UpdateRecordset("CReportsMacroModDlg::OnBnClickedBtnNew1"))
				{
					RiempiLista1();

					for(int i = 0; i < m_ctrlList1.GetItemCount(); i++)
					{
						if ((long)m_ctrlList1.GetItemData(i) == setTemp.GetLastAdd())
						{
							m_ctrlList1.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							break;
						}
					}
				}
			}

			setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedBtnNew1");
		}
	}
}

void CReportsMacroModDlg::OnBnClickedBtnEdt1()
{
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDMacro = (long)m_ctrlList1.GetItemData(nItem);
			CString strDesc = m_ctrlList1.GetItemText(nItem, 0);

			CEditStringDlg dlg(this, IDS_REPORTSMACRO_TITLE_2, strDesc);
			if (dlg.DoModal() == IDOK)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lIDMacro);

				CReportsMacroSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt1"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt1"))
						{
							setTemp.m_sDescrizione = dlg.GetValue();
							if (setTemp.UpdateRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt1"))
							{
								RiempiLista1();

								for(int i = 0; i < m_ctrlList1.GetItemCount(); i++)
								{
									if ((long)m_ctrlList1.GetItemData(i) == lIDMacro)
									{
										m_ctrlList1.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
										break;
									}
								}
							}
						}
					}

					setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt1");
				}
			}
		}
	}
}

void CReportsMacroModDlg::OnBnClickedBtnDel1()
{
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDMacro = (long)m_ctrlList1.GetItemData(nItem);
			CString strDesc = m_ctrlList1.GetItemText(nItem, 0);

			CString strMessage;
			strMessage.Format(theApp.GetMessageString(IDS_REPORTSMACRO_TITLE_3), strDesc);
			if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lIDMacro);

				CReportsMacroSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedBtnDel1"))
				{
					if (!setTemp.IsEOF())
						if (setTemp.DeleteRecordset("CReportsMacroModDlg::OnBnClickedBtnDel1"))
							RiempiLista1();

					setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedBtnDel1");
				}
			}
		}
	}
}

void CReportsMacroModDlg::OnBnClickedBtnNew2()
{
	CPathNumberDlg dlg(this, IDS_REPORTSMACRODETT_TITLE_1, "", 1);
	if (dlg.DoModal() == IDOK)
	{
		CReportsMacroDettSet setTemp;

		if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedBtnNew2"))
		{
			if (setTemp.AddNewRecordset("CReportsMacroModDlg::OnBnClickedBtnNew2"))
			{
				setTemp.m_lIDMacro = m_lIDMacro;
				dlg.GetValue(setTemp.m_sReport, setTemp.m_lCopie);
				if (setTemp.UpdateRecordset("CReportsMacroModDlg::OnBnClickedBtnNew2"))
				{
					RiempiLista2();

					for(int i = 0; i < m_ctrlList2.GetItemCount(); i++)
					{
						if ((long)m_ctrlList2.GetItemData(i) == setTemp.GetLastAdd())
						{
							m_ctrlList2.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							break;
						}
					}
				}
			}

			setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedBtnNew2");
		}
	}
}

void CReportsMacroModDlg::OnBnClickedBtnEdt2()
{
	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList2.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDReport = (long)m_ctrlList2.GetItemData(nItem);
			CString sValue = m_ctrlList2.GetItemText(nItem, 1);
			long lValue = atol(m_ctrlList2.GetItemText(nItem, 2));

			CPathNumberDlg dlg(this, IDS_REPORTSMACRODETT_TITLE_2, sValue, lValue);
			if (dlg.DoModal() == IDOK)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lIDReport);

				CReportsMacroDettSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt2"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt2"))
						{
							dlg.GetValue(setTemp.m_sReport, setTemp.m_lCopie);
							if (setTemp.UpdateRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt2"))
							{
								RiempiLista2();

								for(int i = 0; i < m_ctrlList2.GetItemCount(); i++)
								{
									if ((long)m_ctrlList2.GetItemData(i) == lIDReport)
									{
										m_ctrlList2.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
										break;
									}
								}
							}
						}
					}

					setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedBtnEdt2");
				}
			}
		}
	}
}

void CReportsMacroModDlg::OnBnClickedBtnDel2()
{
	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList2.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDReport = (long)m_ctrlList2.GetItemData(nItem);

			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSMACRODETT_TITLE_3), MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lIDReport);

				CReportsMacroDettSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedBtnDel2"))
				{
					if (!setTemp.IsEOF())
						if (setTemp.DeleteRecordset("CReportsMacroModDlg::OnBnClickedBtnDel2"))
							RiempiLista2();

					setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedBtnDel2");
				}
			}
		}
	}
}

void CReportsMacroModDlg::OnBnClickedBtnUp()
{
	BeginWaitCursor();

	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();

	int nCurSel = -1;
	if (pos != NULL)
		nCurSel = m_ctrlList2.GetNextSelectedItem(pos);

	if (nCurSel < 0)
	{
		EndWaitCursor();
		return;
	}

	long lID = m_ctrlList2.GetItemData(nCurSel);
	if (lID <= 0)
	{
		EndWaitCursor();
		return;
	}

	CReportsMacroDettSet setDett;
	if (setDett.ReportUp(lID, m_lIDMacro))
	{
		RiempiLista2();

		for(int i = 0; i < m_ctrlList2.GetItemCount(); i++)
		{
			if ((long)m_ctrlList2.GetItemData(i) == lID)
			{
				m_ctrlList2.SetItemState(i - 1, LVIS_SELECTED, LVIS_SELECTED);
				break;
			}
		}
	}

	EndWaitCursor();
}

void CReportsMacroModDlg::OnBnClickedBtnDn()
{
	BeginWaitCursor();

	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();

	int nCurSel = -1;
	if (pos != NULL)
		nCurSel = m_ctrlList2.GetNextSelectedItem(pos);

	if (nCurSel < 0)
	{
		EndWaitCursor();
		return;
	}

	long lID = m_ctrlList2.GetItemData(nCurSel);
	if (lID <= 0)
	{
		EndWaitCursor();
		return;
	}

	CReportsMacroDettSet setDett;
	if (setDett.ReportDn(lID, m_lIDMacro))
	{
		RiempiLista2();

		for(int i = 0; i < m_ctrlList2.GetItemCount(); i++)
		{
			if ((long)m_ctrlList2.GetItemData(i) == lID)
			{
				m_ctrlList2.SetItemState(i + 1, LVIS_SELECTED, LVIS_SELECTED);
				break;
			}
		}
	}

	EndWaitCursor();
}

void CReportsMacroModDlg::OnBnClickedCheckStampaImmagini()
{
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDMacro = (long)m_ctrlList1.GetItemData(nItem);

			CString strFilter;
			strFilter.Format("ID=%li", lIDMacro);

			CReportsMacroSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedCheckStampaImmagini"))
			{
				if (!setTemp.IsEOF())
				{
					if (setTemp.EditRecordset("CReportsMacroModDlg::OnBnClickedCheckStampaImmagini"))
					{
						if (m_ctrlCheckStampaImmagini.GetCheck() == BST_CHECKED)
						{
							setTemp.m_lImmaginiCopie = m_ctrlSpinStampaImmagini.GetPos32();
							m_ctrlSpinStampaImmagini.EnableWindow(TRUE);
						}
						else
						{
							setTemp.m_lImmaginiCopie = -1;
							m_ctrlSpinStampaImmagini.EnableWindow(FALSE);
							m_ctrlSpinStampaImmagini.SetPos32(1);
						}

						setTemp.UpdateRecordset("CReportsMacroModDlg::OnBnClickedCheckStampaImmagini");
					}
				}

				setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedCheckStampaImmagini");
			}
		}
	}
}

void CReportsMacroModDlg::OnBnClickedCheckEtichette()
{
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDMacro = (long)m_ctrlList1.GetItemData(nItem);

			CString strFilter;
			strFilter.Format("ID=%li", lIDMacro);

			CReportsMacroSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CReportsMacroModDlg::OnBnClickedCheckEtichette"))
			{
				if (!setTemp.IsEOF())
				{
					if (setTemp.EditRecordset("CReportsMacroModDlg::OnBnClickedCheckEtichette"))
					{
						if (m_ctrlCheckEtichette.GetCheck() == BST_CHECKED)
						{
							setTemp.m_lEtichetteIstopatologiaCopie = m_ctrlSpinEtichetteIstopatologia.GetPos32();
							m_ctrlSpinEtichetteIstopatologia.EnableWindow(TRUE);
						}
						else
						{
							setTemp.m_lEtichetteIstopatologiaCopie = -1;
							m_ctrlSpinEtichetteIstopatologia.EnableWindow(FALSE);
							m_ctrlSpinEtichetteIstopatologia.SetPos32(1);
						}

						setTemp.UpdateRecordset("CReportsMacroModDlg::OnBnClickedCheckEtichette");
					}
				}

				setTemp.CloseRecordset("CReportsMacroModDlg::OnBnClickedCheckEtichette");
			}
		}
	}
}

void CReportsMacroModDlg::OnCbnSelchangeCombo()
{
	BeginWaitCursor();

	CString sReportDaFirmare = "";

	int nCurSel = m_ctrlCombo.GetCurSel();
	if (nCurSel > 0)
		m_ctrlCombo.GetLBText(nCurSel, sReportDaFirmare);

	CReportsMacroSet().SetReportDaFirmare(m_lIDMacro, sReportDaFirmare);

	EndWaitCursor();
}

void CReportsMacroModDlg::RiempiLista1()
{
	BeginWaitCursor();
	m_ctrlList1.SetRedraw(FALSE);

	m_ctrlList1.DeleteAllItems();

	int nItem = 0;

	CReportsMacroSet setMacro;
	setMacro.SetSortRecord("Descrizione");
	if (setMacro.OpenRecordset("CReportsMacroModDlg::RiempiLista1"))
	{
		while(!setMacro.IsEOF())
		{
			m_ctrlList1.InsertItem(nItem, setMacro.m_sDescrizione);
			m_ctrlList1.SetItemData(nItem, setMacro.m_lID);

			nItem++;
			setMacro.MoveNext();
		}

		setMacro.CloseRecordset("CReportsMacroModDlg::RiempiLista1");
	}

	m_ctrlList1.SetRedraw(TRUE);
	EndWaitCursor();
}

void CReportsMacroModDlg::RiempiLista2()
{
	int nCurSel = 0;

	BeginWaitCursor();
	m_ctrlList2.SetRedraw(FALSE);

	m_ctrlList2.DeleteAllItems();
	m_ctrlCombo.ResetContent();

	m_ctrlCombo.InsertString(0, "");

	if (m_lIDMacro > 0)
	{
		int nItem = 0;

		CString strFilter;
		strFilter.Format("IDMacro=%li", m_lIDMacro);

		CReportsMacroDettSet setDett;
		setDett.SetOpenFilter(strFilter);
		setDett.SetSortRecord("ID");
		if (setDett.OpenRecordset("CReportsMacroModDlg::RiempiLista2"))
		{
			CString sReportDaFirmare = CReportsMacroSet().GetReportDaFirmare(m_lIDMacro);

			while(!setDett.IsEOF())
			{
				CString strTemp;

				strTemp.Format("%d", nItem + 1);
				m_ctrlList2.InsertItem(nItem, strTemp);
				m_ctrlList2.SetItemData(nItem, setDett.m_lID);

				m_ctrlList2.SetItemText(nItem, 1, setDett.m_sReport);

				strTemp.Format("%d", setDett.m_lCopie);
				m_ctrlList2.SetItemText(nItem, 2, strTemp);

				//

				int n1 = setDett.m_sReport.ReverseFind('\\');
				int n2 = setDett.m_sReport.ReverseFind('.');

				if ((n1 > 0) && (n2 > n1))
					strTemp.Format("%s", setDett.m_sReport.Mid(n1 + 1, (n2 - n1) - 1));
				else
					strTemp.Format("%s", setDett.m_sReport);

				m_ctrlCombo.InsertString(nItem + 1, strTemp);

				if (strTemp.CompareNoCase(sReportDaFirmare) == 0)
					nCurSel = nItem + 1;

				//

				nItem++;
				setDett.MoveNext();
			}

			setDett.CloseRecordset("CReportsMacroModDlg::RiempiLista2");
		}
	}

	m_ctrlList2.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	//

	m_ctrlCombo.SetCurSel(nCurSel);

	if (nCurSel <= 0)
		CReportsMacroSet().SetReportDaFirmare(m_lIDMacro, "");

	//

	m_ctrlList2.SetRedraw(TRUE);
	EndWaitCursor();
}

void CReportsMacroModDlg::OnDeltaposSpinStampaImmagini(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDMacro = (long)m_ctrlList1.GetItemData(nItem);

			CString strFilter;
			strFilter.Format("ID=%li", lIDMacro);

			CReportsMacroSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CReportsMacroModDlg::OnDeltaposSpinStampaImmagini"))
			{
				if (!setTemp.IsEOF())
				{
					if (setTemp.EditRecordset("CReportsMacroModDlg::OnDeltaposSpinStampaImmagini"))
					{
						int nLower;
						int nUpper;
						m_ctrlSpinStampaImmagini.GetRange32(nLower, nUpper);

						int nCopie;
						if (pNMUpDown->iDelta < 0)
							nCopie = max(nLower, pNMUpDown->iPos + pNMUpDown->iDelta);
						else
							nCopie = min(nUpper, pNMUpDown->iPos + pNMUpDown->iDelta);

						setTemp.m_lImmaginiCopie = nCopie;
						m_ctrlSpinStampaImmagini.EnableWindow(TRUE);

						setTemp.UpdateRecordset("CReportsMacroModDlg::OnDeltaposSpinStampaImmagini");
					}
				}

				setTemp.CloseRecordset("CReportsMacroModDlg::OnDeltaposSpinStampaImmagini");
			}
		}
	}

	*pResult = 0;
}

void CReportsMacroModDlg::OnDeltaposSpinEtichetteIstopatologia(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_ctrlList1.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			long lIDMacro = (long)m_ctrlList1.GetItemData(nItem);

			CString strFilter;
			strFilter.Format("ID=%li", lIDMacro);

			CReportsMacroSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CReportsMacroModDlg::OnDeltaposSpinEtichetteIstopatologia"))
			{
				if (!setTemp.IsEOF())
				{
					if (setTemp.EditRecordset("CReportsMacroModDlg::OnDeltaposSpinEtichetteIstopatologia"))
					{
						int nLower;
						int nUpper;
						m_ctrlSpinEtichetteIstopatologia.GetRange32(nLower, nUpper);

						int nCopie;
						if (pNMUpDown->iDelta < 0)
							nCopie = max(nLower, pNMUpDown->iPos + pNMUpDown->iDelta);
						else
							nCopie = min(nUpper, pNMUpDown->iPos + pNMUpDown->iDelta);

						setTemp.m_lEtichetteIstopatologiaCopie = nCopie;
						m_ctrlSpinStampaImmagini.EnableWindow(TRUE);

						setTemp.UpdateRecordset("CReportsMacroModDlg::OnDeltaposSpinEtichetteIstopatologia");
					}
				}

				setTemp.CloseRecordset("CReportsMacroModDlg::OnDeltaposSpinEtichetteIstopatologia");
			}
		}
	}

	*pResult = 0;
}
