//Gabriel - BUG 5533 V2 - Cálculos medidas biométricas
#include "stdafx.h"
#include "MeasurementsCalculationDlg.h"
#include "MeasurementsCalculationSet.h"
#include "Endox.h"
#include "MeasurementsAliasMappingSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMeasurementsCalculationDlg, CDialog)

CMeasurementsCalculationDlg::CMeasurementsCalculationDlg(CWnd* pParent)
: CDialog(CMeasurementsCalculationDlg::IDD, pParent)
{
	m_lIDSelected = -1;
	m_lIDCalcSelected = -1;
}

CMeasurementsCalculationDlg::~CMeasurementsCalculationDlg()
{

}

BEGIN_MESSAGE_MAP(CMeasurementsCalculationDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

	ON_CBN_SELCHANGE(IDC_COMBO_FORMULA, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_1, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_2, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_3, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_4, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

void CMeasurementsCalculationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);

	DDX_Control(pDX, IDC_COMBO_FORMULA, m_ctrlComboFormula);
	DDX_Control(pDX, IDC_COMBO_1, m_ctrlComboFormula1);
	DDX_Control(pDX, IDC_COMBO_2, m_ctrlComboFormula2);
	DDX_Control(pDX, IDC_COMBO_3, m_ctrlComboFormula3);
	DDX_Control(pDX, IDC_COMBO_4, m_ctrlComboFormula4);

	DDX_Text(pDX, IDC_NOME, m_sNome);
	DDX_Text(pDX, IDC_VALUE_1, m_fValue1);
}

BOOL CMeasurementsCalculationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Name", LVCFMT_LEFT, 0);

	RiempiLista();
	RiempiCombo();

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CMeasurementsCalculationDlg::IDD, "CMeasurementsCalculationDlg");
	return TRUE;
}

void CMeasurementsCalculationDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CMeasurementsCalculationDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CMeasurementsCalculationDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CString sFilter;
	sFilter.Format("UO = %li AND ELIMINATO = 0", theApp.m_lUO);

	CMeasurementsCalculationSet setTemp;

	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CMeasurementsCalculationDlg::RiempiLista") == TRUE)
	{
		while (setTemp.IsEOF() == FALSE)
		{
			int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), setTemp.m_sName);
			m_ctrlList.SetItemData(nItem, (DWORD)setTemp.m_lID);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMeasurementsMapping::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CMeasurementsCalculationDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_NOME, "");
	SetDlgItemText(IDC_VALUE_1, "0");
	m_ctrlComboFormula.SetCurSel(-1);
	m_ctrlComboFormula1.SetCurSel(-1);
	m_ctrlComboFormula2.SetCurSel(-1);
	m_ctrlComboFormula3.SetCurSel(-1);
	m_ctrlComboFormula4.SetCurSel(-1);

	AggiornaCombo(FALSE);

	CString sFilter;
	sFilter.Format("ID = %li AND ELIMINATO = 0", m_lIDSelected);

	CMeasurementsCalculationSet setTemp;

	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CMeasurementsCalculationDlg::CaricaDati") == TRUE)
	{
		if (!setTemp.IsEOF())
		{
			SetDlgItemText(IDC_NOME, setTemp.m_sName);
			m_ctrlComboFormula.SetCurSel(setTemp.m_lIDCalc);
			AggiornaCombo(FALSE);
			
			int nSelectMeasurement1 = 0;
			for (int i = 0; i < m_ctrlComboFormula1.GetCount(); i++)
			{
				if (m_ctrlComboFormula1.GetItemData(i) == setTemp.m_lMeasurement1)
				{
					nSelectMeasurement1 = i;
					break;
				}
			}
			m_ctrlComboFormula1.SetCurSel(nSelectMeasurement1);

			int nSelectMeasurement2 = 0;
			for (int i = 0; i < m_ctrlComboFormula2.GetCount(); i++)
			{
				if (m_ctrlComboFormula2.GetItemData(i) == setTemp.m_lMeasurement2)
				{
					nSelectMeasurement2 = i;
					break;
				}
			}
			m_ctrlComboFormula2.SetCurSel(nSelectMeasurement2);

			int nSelectMeasurement3 = 0;
			for (int i = 0; i < m_ctrlComboFormula3.GetCount(); i++)
			{
				if (m_ctrlComboFormula3.GetItemData(i) == setTemp.m_lMeasurement3)
				{
					nSelectMeasurement3 = i;
					break;
				}
			}
			m_ctrlComboFormula3.SetCurSel(nSelectMeasurement3);

			int nSelectMeasurement4 = 0;
			for (int i = 0; i < m_ctrlComboFormula4.GetCount(); i++)
			{
				if (m_ctrlComboFormula4.GetItemData(i) == setTemp.m_lMeasurement4)
				{
					nSelectMeasurement4 = i;
					break;
				}
			}
			m_ctrlComboFormula4.SetCurSel(nSelectMeasurement4);
			CString sValue1;
			sValue1.Format("%.2f", setTemp.m_fValue1);
			//strValue2.Format("%.2f", DataSet.m_fValore);
			SetDlgItemText(IDC_VALUE_1, sValue1);
		}

		setTemp.CloseRecordset("CMeasurementsMapping::RiempiLista");
	}

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CMeasurementsCalculationDlg::UnselectAll()
{
	if (m_ctrlList.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
			m_ctrlList.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedList(NULL, NULL);
	}
}

void CMeasurementsCalculationDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_NOME, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	m_ctrlComboFormula.EnableWindow(bEdit);
	m_ctrlComboFormula1.EnableWindow(bEdit);
	m_ctrlComboFormula2.EnableWindow(bEdit);
	m_ctrlComboFormula3.EnableWindow(bEdit);
	m_ctrlComboFormula4.EnableWindow(bEdit);
	GetDlgItem(IDC_NOME)->EnableWindow(bEdit);
	GetDlgItem(IDC_VALUE_1)->EnableWindow(bEdit);

	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CMeasurementsCalculationDlg message handlers
void CMeasurementsCalculationDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CMeasurementsCalculationDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CMeasurementsCalculationDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (CMeasurementsCalculationSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CMeasurementsCalculationDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CMeasurementsCalculationDlg::OnBnClickedBtnSave()
{
	if (!UpdateData(TRUE))
		return;
	
	if (!CheckCombo(m_lIDCalcSelected))
		return;
	
	CString strTemp;

	GetDlgItemText(IDC_NOME, strTemp);
	strTemp.Trim();

	CString sNome, sValue1;

	GetDlgItemText(IDC_NOME, sNome);
	GetDlgItemText(IDC_VALUE_1, sValue1);
	float fValue1 = (float)atof(sValue1);

	if (!strTemp.IsEmpty())
	{
		if (m_lIDSelected <= 0)
		{
			CMeasurementsCalculationSet().AddRow(m_ctrlComboFormula.GetCurSel(), m_ctrlComboFormula1.GetItemData(m_ctrlComboFormula1.GetCurSel()), m_ctrlComboFormula2.GetItemData(m_ctrlComboFormula2.GetCurSel()), m_ctrlComboFormula3.GetItemData(m_ctrlComboFormula3.GetCurSel()), m_ctrlComboFormula4.GetItemData(m_ctrlComboFormula4.GetCurSel()), sNome, fValue1);
		}
		else
		{
			CString sFilter;
			sFilter.Format("ID = %li AND ELIMINATO = 0", m_lIDSelected);

			CMeasurementsCalculationSet set;
			set.SetOpenFilter(sFilter);
			if (set.OpenRecordset("CMeasurementsCalculationDlg::OnBnClickedBtnSave"))
			{
				if (set.EditRecordset("CMeasurementsCalculationDlg::OnBnClickedBtnSave"))
				{
					set.m_sName = sNome;
					set.m_lIDCalc = m_ctrlComboFormula.GetCurSel();
					set.m_lMeasurement1 = m_ctrlComboFormula1.GetItemData(m_ctrlComboFormula1.GetCurSel());
					set.m_lMeasurement2 = m_ctrlComboFormula2.GetItemData(m_ctrlComboFormula2.GetCurSel());
					set.m_lMeasurement3 = m_ctrlComboFormula3.GetItemData(m_ctrlComboFormula3.GetCurSel());
					set.m_lMeasurement4 = m_ctrlComboFormula4.GetItemData(m_ctrlComboFormula4.GetCurSel());
					set.m_fValue1 = fValue1;
					set.m_lUO = theApp.m_lUO;

					set.UpdateRecordset("CMeasurementsCalculationDlg::OnBnClickedBtnSave");
				}
				set.CloseRecordset("CMeasurementsCalculationDlg::OnBnClickedBtnSave");
			}
		}

		UnselectAll();
		RiempiLista();
		EditDialog(FALSE);
	}
	else
	{
		AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO4), MB_ICONSTOP);
	}
}

void CMeasurementsCalculationDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CMeasurementsCalculationDlg::RiempiCombo()
{
	m_ctrlComboFormula.ResetContent();
	m_ctrlComboFormula1.ResetContent();
	m_ctrlComboFormula2.ResetContent();
	m_ctrlComboFormula3.ResetContent();
	m_ctrlComboFormula4.ResetContent();

	m_ctrlComboFormula.InsertString(0, "");
	m_ctrlComboFormula.SetItemData(0, 0);

	m_ctrlComboFormula.InsertString(1, "x + y");
	m_ctrlComboFormula.SetItemData(1, 1);

	m_ctrlComboFormula.InsertString(2, "x - y");
	m_ctrlComboFormula.SetItemData(2, 2);

	m_ctrlComboFormula.InsertString(3, "x * y");
	m_ctrlComboFormula.SetItemData(3, 3);

	m_ctrlComboFormula.InsertString(4, "x / y");
	m_ctrlComboFormula.SetItemData(4, 4);

	m_ctrlComboFormula.InsertString(5, "(x + y) / z");
	m_ctrlComboFormula.SetItemData(5, 5);

	m_ctrlComboFormula.InsertString(6, "(x + y) / n");
	m_ctrlComboFormula.SetItemData(6, 6);

	m_ctrlComboFormula.InsertString(7, "(x * y) / z");
	m_ctrlComboFormula.SetItemData(7, 7);

	m_ctrlComboFormula.InsertString(8, "(x * y) / n");
	m_ctrlComboFormula.SetItemData(8, 8);

	m_ctrlComboFormula1.InsertString(0, "");
	m_ctrlComboFormula1.SetItemData(0, 0);

	m_ctrlComboFormula2.InsertString(0, "");
	m_ctrlComboFormula2.SetItemData(0, 0);

	m_ctrlComboFormula3.InsertString(0, "");
	m_ctrlComboFormula3.SetItemData(0, 0);

	m_ctrlComboFormula4.InsertString(0, "");
	m_ctrlComboFormula4.SetItemData(0, 0);

	CMeasurementsAliasMappingSet setMeasurements;

	CString sFilter;
	sFilter.Format("VALUETYPE = 'Numérico' AND UO = %li", theApp.m_lUO);

	setMeasurements.SetOpenFilter(sFilter);
	if (setMeasurements.OpenRecordset("CMeasurementsCalculationDlg::RiempiCombo"))
	{
		int nIndex = 0;

		while (!setMeasurements.IsEOF())
		{
			m_ctrlComboFormula1.InsertString(nIndex, setMeasurements.m_sAlias);
			m_ctrlComboFormula1.SetItemData(nIndex, setMeasurements.m_lID);

			m_ctrlComboFormula2.InsertString(nIndex, setMeasurements.m_sAlias);
			m_ctrlComboFormula2.SetItemData(nIndex, setMeasurements.m_lID);

			m_ctrlComboFormula3.InsertString(nIndex, setMeasurements.m_sAlias);
			m_ctrlComboFormula3.SetItemData(nIndex, setMeasurements.m_lID);

			m_ctrlComboFormula4.InsertString(nIndex, setMeasurements.m_sAlias);
			m_ctrlComboFormula4.SetItemData(nIndex, setMeasurements.m_lID);

			nIndex++;
			setMeasurements.MoveNext();
		}

		setMeasurements.CloseRecordset("CMeasurementsCalculationDlg::RiempiCombo");
	}
}

void CMeasurementsCalculationDlg::OnCbnSelchangeComboFormula()
{
	m_lIDCalcSelected = m_ctrlComboFormula.GetCurSel();
	AggiornaCombo(TRUE);
}

void CMeasurementsCalculationDlg::OnCbnSelchangeCombo1()
{
	AggiornaCombo(TRUE);
}

void CMeasurementsCalculationDlg::OnCbnSelchangeCombo2()
{
	AggiornaCombo(TRUE);
}

void CMeasurementsCalculationDlg::OnCbnSelchangeCombo3()
{
	AggiornaCombo(TRUE);
}

void CMeasurementsCalculationDlg::OnCbnSelchangeCombo4()
{
	AggiornaCombo(TRUE);
}

BOOL CMeasurementsCalculationDlg::CheckCombo(long lIDCalc)
{
	BOOL bReturn = FALSE;
	long lFormula1 = m_ctrlComboFormula1.GetItemData(m_ctrlComboFormula1.GetCurSel());
	long lFormula2 = m_ctrlComboFormula2.GetItemData(m_ctrlComboFormula2.GetCurSel());
	long lFormula3 = m_ctrlComboFormula3.GetItemData(m_ctrlComboFormula3.GetCurSel());
	long lFormula4 = lIDCalc == 5 || lIDCalc == 7 ? m_ctrlComboFormula4.GetItemData(m_ctrlComboFormula4.GetCurSel()) : 0;

	if (lFormula1 == lFormula2 || lFormula1 == lFormula3 || lFormula1 == lFormula4 || lFormula2 == lFormula3 || lFormula2 == lFormula4 || lFormula3 == lFormula4)
		bReturn = FALSE;
	else
		bReturn = TRUE;

	return bReturn;
}

void CMeasurementsCalculationDlg::AggiornaCombo(BOOL bEdit)
{
	m_ctrlComboFormula.EnableWindow(bEdit);
	m_ctrlComboFormula1.EnableWindow(bEdit);
	m_ctrlComboFormula2.EnableWindow(bEdit);
	m_ctrlComboFormula3.EnableWindow(bEdit);
	m_ctrlComboFormula4.EnableWindow(bEdit);
	GetDlgItem(IDC_NOME)->EnableWindow(bEdit);
	GetDlgItem(IDC_VALUE_1)->EnableWindow(bEdit);
	
	long lFormula = m_ctrlComboFormula.GetCurSel();
	switch (lFormula)
	{
		case -1:
		case 0:
			m_ctrlComboFormula1.ShowWindow(SW_HIDE);
			m_ctrlComboFormula2.ShowWindow(SW_HIDE);
			m_ctrlComboFormula3.ShowWindow(SW_HIDE);
			m_ctrlComboFormula4.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_HIDE);
			SetDlgItemText(IDC_STATIC_5, "");
			break;
		case 1:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "+");
			break;
		case 2:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "-");
			break;
		case 3:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "*");
			break;
		case 4:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "/");
			break;
		case 5:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "+");
			break;
		case 6:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "+");
			break;
		case 7:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "*");
			break;
		case 8:
			m_ctrlComboFormula1.ShowWindow(SW_SHOW);
			m_ctrlComboFormula2.ShowWindow(SW_SHOW);
			m_ctrlComboFormula3.ShowWindow(SW_SHOW);
			m_ctrlComboFormula4.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_VALUE_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_STATIC_5, "*");
			break;
	}
}
