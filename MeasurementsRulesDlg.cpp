//Gabriel - BUG 5533 V2 - Regras medidas biométricas
#include "stdafx.h"
#include "MeasurementsRulesDlg.h"
#include "MeasurementsRulesSet.h"
#include "Endox.h"
#include "MeasurementsAliasMappingSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMeasurementsRulesDlg, CDialog)

CMeasurementsRulesDlg::CMeasurementsRulesDlg(CWnd* pParent)
: CDialog(CMeasurementsRulesDlg::IDD, pParent)
{
	m_lIDSelected = -1;
}

CMeasurementsRulesDlg::~CMeasurementsRulesDlg()
{

}

BEGIN_MESSAGE_MAP(CMeasurementsRulesDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

	ON_CBN_SELCHANGE(IDC_COMBO_CONDITION, OnCbnSelchangeComboCondition)
END_MESSAGE_MAP()

void CMeasurementsRulesDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);

	DDX_Control(pDX, IDC_COMBO_CONDITION_FIELD, m_ctrlComboConditionField);
	DDX_Control(pDX, IDC_COMBO_CONDITION, m_ctrlComboCondition);
	DDX_Control(pDX, IDC_COMBO_RULE_FIELD, m_ctrlComboRuleField);
	DDX_Control(pDX, IDC_COMBO_RULE, m_ctrlComboRule);

	DDX_Text(pDX, IDC_NOME, m_sNome);
	DDX_Text(pDX, IDC_CONDITION_VALUE, m_sValue1);
	DDX_Text(pDX, IDC_CONDITION_VALUE2, m_sValue2);
}

BOOL CMeasurementsRulesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Name", LVCFMT_LEFT, 0);

	RiempiLista();
	RiempiCombo();

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CMeasurementsRulesDlg::IDD, "CMeasurementsRulesDlg");
	return TRUE;
}

void CMeasurementsRulesDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CMeasurementsRulesDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CMeasurementsRulesDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CString sFilter;
	sFilter.Format("UO = %li AND ELIMINATO = 0", theApp.m_lUO);

	CMeasurementsRulesSet setTemp;

	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CMeasurementsRulesDlg::RiempiLista") == TRUE)
	{
		while (setTemp.IsEOF() == FALSE)
		{
			int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), setTemp.m_sName);
			m_ctrlList.SetItemData(nItem, (DWORD)setTemp.m_lID);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMeasurementsRulesDlg::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CMeasurementsRulesDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_NOME, "");
	SetDlgItemText(IDC_CONDITION_VALUE, "");
	SetDlgItemText(IDC_CONDITION_VALUE2, "");
	m_ctrlComboConditionField.SetCurSel(-1);
	m_ctrlComboCondition.SetCurSel(-1);
	m_ctrlComboRuleField.SetCurSel(-1);
	m_ctrlComboRule.SetCurSel(-1);

	AggiornaCombo(FALSE);

	CString sFilter;
	sFilter.Format("ID = %li AND ELIMINATO = 0", m_lIDSelected);

	CMeasurementsRulesSet setTemp;

	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CMeasurementsRulesDlg::CaricaDati") == TRUE)
	{
		if (!setTemp.IsEOF())
		{
			SetDlgItemText(IDC_NOME, setTemp.m_sName);
			m_ctrlComboCondition.SetCurSel(setTemp.m_lIDCondition);
			AggiornaCombo(FALSE);
			
			int nSelectCondition = 0;
			for (int i = 0; i < m_ctrlComboConditionField.GetCount(); i++)
			{
				if (m_ctrlComboConditionField.GetItemData(i) == setTemp.m_lMeasurementCondition)
				{
					nSelectCondition = i;
					break;
				}
			}
			m_ctrlComboConditionField.SetCurSel(nSelectCondition);

			int nSelectRule = 0;
			for (int i = 0; i < m_ctrlComboRuleField.GetCount(); i++)
			{
				if (m_ctrlComboRuleField.GetItemData(i) == setTemp.m_lMeasurementRule)
				{
					nSelectRule = i;
					break;
				}
			}

			m_ctrlComboRuleField.SetCurSel(nSelectRule);
			m_ctrlComboRule.SetCurSel(setTemp.m_lIDRule);
			SetDlgItemText(IDC_CONDITION_VALUE, setTemp.m_sValueCondition1);
			SetDlgItemText(IDC_CONDITION_VALUE2, setTemp.m_sValueCondition2);
		}

		setTemp.CloseRecordset("CMeasurementsRulesDlg::RiempiLista");
	}

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CMeasurementsRulesDlg::UnselectAll()
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

void CMeasurementsRulesDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_NOME, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	m_ctrlComboCondition.EnableWindow(bEdit);
	m_ctrlComboConditionField.EnableWindow(bEdit);
	m_ctrlComboRule.EnableWindow(bEdit);
	m_ctrlComboRuleField.EnableWindow(bEdit);
	GetDlgItem(IDC_NOME)->EnableWindow(bEdit);
	GetDlgItem(IDC_CONDITION_VALUE)->EnableWindow(bEdit);
	GetDlgItem(IDC_CONDITION_VALUE2)->EnableWindow(bEdit);

	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CMeasurementsRulesDlg message handlers
void CMeasurementsRulesDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CMeasurementsRulesDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CMeasurementsRulesDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (CMeasurementsRulesSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CMeasurementsRulesDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CMeasurementsRulesDlg::OnBnClickedBtnSave()
{
	if (!UpdateData(TRUE))
		return;

	if (!CheckRules())
		return;

	CString sNome, sValueCondition1, sValueCondition2;

	GetDlgItemText(IDC_NOME, sNome);
	GetDlgItemText(IDC_CONDITION_VALUE, sValueCondition1);
	GetDlgItemText(IDC_CONDITION_VALUE2, sValueCondition2);
	
	if (!sNome.IsEmpty())
	{
		if (m_lIDSelected <= 0)
		{
			CMeasurementsRulesSet().AddRow(m_ctrlComboCondition.GetCurSel(), m_ctrlComboConditionField.GetItemData(m_ctrlComboConditionField.GetCurSel()), m_ctrlComboRule.GetCurSel(), m_ctrlComboRuleField.GetItemData(m_ctrlComboRuleField.GetCurSel()), sNome, sValueCondition1, sValueCondition2);
		}
		else
		{
			CString sFilter;
			sFilter.Format("ID = %li AND ELIMINATO = 0", m_lIDSelected);

			CMeasurementsRulesSet set;
			set.SetOpenFilter(sFilter);
			if (set.OpenRecordset("CMeasurementsRulesDlg::OnBnClickedBtnSave"))
			{
				if (set.EditRecordset("CMeasurementsRulesDlg::OnBnClickedBtnSave"))
				{
					set.m_sName = sNome;
					set.m_lIDCondition = m_ctrlComboCondition.GetCurSel();
					set.m_lMeasurementCondition = m_ctrlComboConditionField.GetItemData(m_ctrlComboConditionField.GetCurSel());
					set.m_lIDRule = m_ctrlComboRule.GetCurSel();
					set.m_lMeasurementRule = m_ctrlComboRuleField.GetItemData(m_ctrlComboRuleField.GetCurSel());
					set.m_sValueCondition1 = sValueCondition1;
					set.m_sValueCondition2 = sValueCondition2;
					set.m_lUO = theApp.m_lUO;

					set.UpdateRecordset("CMeasurementsRulesDlg::OnBnClickedBtnSave");
				}
				set.CloseRecordset("CMeasurementsRulesDlg::OnBnClickedBtnSave");
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

void CMeasurementsRulesDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CMeasurementsRulesDlg::RiempiCombo()
{
	m_ctrlComboConditionField.ResetContent();
	m_ctrlComboCondition.ResetContent();
	m_ctrlComboRuleField.ResetContent();
	m_ctrlComboRule.ResetContent();

	m_ctrlComboCondition.InsertString(0, "");
	m_ctrlComboCondition.SetItemData(0, 0);

	m_ctrlComboCondition.InsertString(1, "Igual a");
	m_ctrlComboCondition.SetItemData(1, 1);

	m_ctrlComboCondition.InsertString(2, "Diferente de");
	m_ctrlComboCondition.SetItemData(2, 2);

	m_ctrlComboCondition.InsertString(3, "Maior que");
	m_ctrlComboCondition.SetItemData(3, 3);

	m_ctrlComboCondition.InsertString(4, "Menor que");
	m_ctrlComboCondition.SetItemData(4, 4);

	m_ctrlComboCondition.InsertString(5, "Maior ou igual que");
	m_ctrlComboCondition.SetItemData(5, 5);

	m_ctrlComboCondition.InsertString(6, "Menor ou igual que");
	m_ctrlComboCondition.SetItemData(6, 6);

	m_ctrlComboCondition.InsertString(7, "Vazio");
	m_ctrlComboCondition.SetItemData(7, 7);

	m_ctrlComboCondition.InsertString(8, "Não vazio");
	m_ctrlComboCondition.SetItemData(8, 8);

	m_ctrlComboCondition.InsertString(9, "Entre");
	m_ctrlComboCondition.SetItemData(9, 9);


	m_ctrlComboRule.InsertString(0, "");
	m_ctrlComboRule.SetItemData(0, 0);

	m_ctrlComboRule.InsertString(1, "Obrigatório");
	m_ctrlComboRule.SetItemData(1, 1);

	m_ctrlComboRule.InsertString(2, "Desabilitado");
	m_ctrlComboRule.SetItemData(2, 2);

	CMeasurementsAliasMappingSet setMeasurements;

	CString sFilter;
	sFilter.Format("UO = %li", theApp.m_lUO);

	setMeasurements.SetOpenFilter(sFilter);
	if (setMeasurements.OpenRecordset("CMeasurementsRulesDlg::RiempiCombo"))
	{
		int nIndex = 0;

		while (!setMeasurements.IsEOF())
		{
			m_ctrlComboConditionField.InsertString(nIndex, setMeasurements.m_sAlias);
			m_ctrlComboConditionField.SetItemData(nIndex, setMeasurements.m_lID);

			m_ctrlComboRuleField.InsertString(nIndex, setMeasurements.m_sAlias);
			m_ctrlComboRuleField.SetItemData(nIndex, setMeasurements.m_lID);

			nIndex++;
			setMeasurements.MoveNext();
		}

		setMeasurements.CloseRecordset("CMeasurementsRulesDlg::RiempiCombo");
	}
}

void CMeasurementsRulesDlg::OnCbnSelchangeComboCondition()
{
	AggiornaCombo(TRUE);
}

BOOL CMeasurementsRulesDlg::CheckRules()
{
	BOOL bReturn = FALSE;

	CString sNome, sValueCondition1;
	long lCondition = m_ctrlComboCondition.GetCurSel();
	long lConditionField = m_ctrlComboConditionField.GetItemData(m_ctrlComboConditionField.GetCurSel());
	long lRule = m_ctrlComboRule.GetCurSel();
	long lRuleField = m_ctrlComboRuleField.GetItemData(m_ctrlComboRuleField.GetCurSel());
	GetDlgItemText(IDC_NOME, sNome);
	GetDlgItemText(IDC_CONDITION_VALUE, sValueCondition1);
	
	if (lCondition < 1 || lConditionField < 1 || lRule < 1 || lRuleField < 1 || sNome.Trim().IsEmpty())
		return FALSE;
	else
	{
		CString sValueCondition2;
		GetDlgItemText(IDC_CONDITION_VALUE2, sValueCondition2);

		if (lCondition == 9)
		{
			if (sValueCondition2.Trim().IsEmpty() || sValueCondition1.Trim().IsEmpty())
				return FALSE;
			if (sValueCondition1.Trim().Compare("0") != 0 && sValueCondition2.Trim().Compare("0") != 0)
			{
				float fValue1 = (float)atof(sValueCondition1);
				float fValue2 = (float)atof(sValueCondition2);
				if (fValue2 <= 0 || fValue1 <= 0)
					return FALSE;
			}
		}
		if (lCondition == 3 || lCondition == 4 || lCondition == 5 || lCondition == 6)
		{
			float fValue1 = (float)atof(sValueCondition1);
			if (sValueCondition1.Trim().Compare("0") != 0)
			{
				if (fValue1 <= 0 || sValueCondition1.Trim().IsEmpty())
					return FALSE;
			}
		}
		
		bReturn = TRUE;
	}
	
	return bReturn;
}

void CMeasurementsRulesDlg::AggiornaCombo(BOOL bEdit)
{
	m_ctrlComboCondition.EnableWindow(bEdit);
	m_ctrlComboConditionField.EnableWindow(bEdit);
	m_ctrlComboRule.EnableWindow(bEdit);
	m_ctrlComboRuleField.EnableWindow(bEdit);
	GetDlgItem(IDC_NOME)->EnableWindow(bEdit);
	GetDlgItem(IDC_CONDITION_VALUE)->EnableWindow(bEdit);
	GetDlgItem(IDC_CONDITION_VALUE2)->EnableWindow(bEdit);

	long lCondition = m_ctrlComboCondition.GetCurSel();
	switch (lCondition)
	{
	case -1:
	case 0:
		m_ctrlComboCondition.ShowWindow(SW_SHOW);
		m_ctrlComboConditionField.ShowWindow(SW_SHOW);
		m_ctrlComboRule.ShowWindow(SW_SHOW);
		m_ctrlComboRuleField.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_NOME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONDITION_VALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONDITION_VALUE2)->ShowWindow(SW_SHOW);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		m_ctrlComboCondition.ShowWindow(SW_SHOW);
		m_ctrlComboConditionField.ShowWindow(SW_SHOW);
		m_ctrlComboRule.ShowWindow(SW_SHOW);
		m_ctrlComboRuleField.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_NOME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONDITION_VALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONDITION_VALUE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_HIDE);
		break;
	case 7:
	case 8:
		m_ctrlComboCondition.ShowWindow(SW_SHOW);
		m_ctrlComboConditionField.ShowWindow(SW_SHOW);
		m_ctrlComboRule.ShowWindow(SW_SHOW);
		m_ctrlComboRuleField.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_NOME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONDITION_VALUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONDITION_VALUE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_HIDE);
		break;
	case 9:
		m_ctrlComboCondition.ShowWindow(SW_SHOW);
		m_ctrlComboConditionField.ShowWindow(SW_SHOW);
		m_ctrlComboRule.ShowWindow(SW_SHOW);
		m_ctrlComboRuleField.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_NOME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONDITION_VALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONDITION_VALUE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
		break;
	
	}
}
