#include "stdafx.h"
#include "Endox.h"
#include "EndoGridCLOptionDlg.h"

#include "EndoGridComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLOptionDlg, CDialog)

CEndoGridCLOptionDlg::CEndoGridCLOptionDlg(CEndoGridCLParameterSet* pUserField, CWnd* pParentWnd)
: CDialog(CEndoGridCLOptionDlg::IDD, pParentWnd)
{
	m_pUserField = pUserField;

	switch (m_pUserField->GetFieldType())
	{
	case CEndoGridCLParameterSet::type_double: //float
		if (!pUserField->IsFieldNull(&m_pUserField->m_fDefaultFloat))
			m_fDefaultReal = m_pUserField->m_fDefaultFloat;
		else
			m_fDefaultReal = 0;

		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_check:
		if (!pUserField->IsFieldNull(&m_pUserField->m_bDefaultBool))
			m_bDefaultCheck = m_pUserField->m_bDefaultBool;
		else
			m_bDefaultCheck = FALSE;

		m_bDefaultBool = FALSE;
		m_fDefaultReal = 0;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_bool: //bool
		if (!pUserField->IsFieldNull(&m_pUserField->m_bDefaultBool))
			m_bDefaultBool = m_pUserField->m_bDefaultBool;
		else
			m_bDefaultBool = FALSE;

		m_bDefaultCheck = FALSE;
		m_fDefaultReal = 0;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_integer: //int
		if (!pUserField->IsFieldNull(&m_pUserField->m_lDefaultInt))
			m_lDefaultInt = m_pUserField->m_lDefaultInt;
		else
			m_lDefaultInt = 0;

		m_fDefaultReal = 0;
		m_bDefaultCheck = FALSE;
		m_bDefaultBool = FALSE;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_combo: //combo
		m_strDefaultCombo = m_pUserField->m_sDefaultString;

		m_fDefaultReal = 0;
		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_date: //data
		m_strDefaultDate.Format("%s/%s/%s",
			m_pUserField->m_sDefaultString.Mid(6, 2),
			m_pUserField->m_sDefaultString.Mid(4, 2),
			m_pUserField->m_sDefaultString.Mid(0, 4));

		m_fDefaultReal = 0;
		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		break;

	case CEndoGridCLParameterSet::type_string: //string
		m_strDefaultString = m_pUserField->m_sDefaultString;

		m_fDefaultReal = 0;
		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_combo_multi: //combo multi
		m_strDefaultComboMulti = m_pUserField->m_sDefaultString;

		m_fDefaultReal = 0;
		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_notes:
		m_strDefaultNotes = m_pUserField->m_sDefaultString;
		m_fDefaultReal = 0;
		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_combo_fixed:
		m_strDefaultComboFixed = m_pUserField->m_sDefaultString;

		m_fDefaultReal = 0;
		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	case CEndoGridCLParameterSet::type_date_free:
		m_strDefaultDateFree = m_pUserField->m_sDefaultString;

		m_fDefaultReal = 0;
		m_bDefaultBool = FALSE;
		m_bDefaultCheck = FALSE;
		m_lDefaultInt = 0;
		m_strDefaultDate = "__/__/____";
		break;

	default:
		ASSERT(FALSE);
		break;
	}

}

CEndoGridCLOptionDlg::~CEndoGridCLOptionDlg()
{
}

void CEndoGridCLOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_FIELD_TYPE, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_DEFAULT, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_TYPE, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic4);
	DDX_Control(pDX, IDC_FIELD_TYPE_1, m_ctrlButton1);
	DDX_Control(pDX, IDC_FIELD_TYPE_2, m_ctrlButton2);
	DDX_Control(pDX, IDC_FIELD_TYPE_3, m_ctrlButton3);
	DDX_Control(pDX, IDC_FIELD_TYPE_4, m_ctrlButton4);
	DDX_Control(pDX, IDC_FIELD_TYPE_5, m_ctrlButton5);
	DDX_Control(pDX, IDC_FIELD_TYPE_6, m_ctrlButton6);
	DDX_Control(pDX, IDC_FIELD_TYPE_7, m_ctrlButton7);
	DDX_Control(pDX, IDC_FIELD_TYPE_9, m_ctrlButton9);
	DDX_Control(pDX, IDC_FIELD_TYPE_10, m_ctrlButton10);
	DDX_Control(pDX, IDC_FIELD_TYPE_11, m_ctrlButton11);
	DDX_Control(pDX, IDC_FIELD_TYPE_13, m_ctrlButton13);
	DDX_Control(pDX, IDC_CHECK_EXPAND, m_ctrlButton15);
	DDX_Control(pDX, IDC_CHECK_OBBLIGATORY, m_ctrlButton18);
	DDX_Control(pDX, IDC_CHECK_COLOR, m_ctrlButton19);
	DDX_Control(pDX, IDOK, m_ctrlButton20);
	DDX_Control(pDX, IDCANCEL, m_ctrlButton21);

	DDX_Control(pDX, IDC_DEFAULT_DATE, m_ctrlDate);

	DDX_Radio(pDX, IDC_FIELD_TYPE_1, (int&)*m_pUserField->GetType());
	DDX_Check(pDX, IDC_CHECK_EXPAND, (BOOL&)m_pUserField->m_bExpanded);
	DDX_Check(pDX, IDC_CHECK_OBBLIGATORY, (BOOL&)m_pUserField->m_bRequired);
	DDX_Check(pDX, IDC_CHECK_COLOR, (BOOL&)m_pUserField->m_bChangeColor);

	DDX_Text(pDX, IDC_DEFAULT_REAL, m_fDefaultReal);
	DDX_Check(pDX, IDC_DEFAULT_BOOL, m_bDefaultBool);
	DDX_Text(pDX, IDC_DEFAULT_INT, m_lDefaultInt);
	DDX_Text(pDX, IDC_DEFAULT_COMBO, m_strDefaultCombo);
	DDV_MaxChars(pDX, m_strDefaultCombo, 255);
	DDX_Text(pDX, IDC_DEFAULT_DATE, m_strDefaultDate);
	DDX_Text(pDX, IDC_DEFAULT_STRING, m_strDefaultString);
	DDV_MaxChars(pDX, m_strDefaultString, 255);
	DDX_Text(pDX, IDC_DEFAULT_COMBO_MULTI, m_strDefaultComboMulti);
	DDV_MaxChars(pDX, m_strDefaultComboMulti, 255);
	DDX_Text(pDX, IDC_DEFAULT_NOTES, m_strDefaultNotes);
	DDV_MaxChars(pDX, m_strDefaultNotes, 255);
	DDX_Text(pDX, IDC_DEFAULT_COMBO_FIXED, m_strDefaultComboFixed);
	DDV_MaxChars(pDX, m_strDefaultComboFixed, 255);
	DDX_Text(pDX, IDC_DEFAULT_DATE_FREE, m_strDefaultDateFree);
	DDV_MaxChars(pDX, m_strDefaultDateFree, 255);
	DDX_Check(pDX, IDC_DEFAULT_CHECK, m_bDefaultCheck);
}

BEGIN_MESSAGE_MAP(CEndoGridCLOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_FIELD_TYPE_1, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_2, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_3, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_4, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_5, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_6, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_7, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_9, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_10, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_11, OnChangeRadio)
	ON_BN_CLICKED(IDC_FIELD_TYPE_13, OnChangeRadio)
	ON_BN_CLICKED(IDC_BUTTON_COMBO, OnButtonCombo)
	ON_BN_CLICKED(IDC_BUTTON_COMBO_MULTI, OnButtonComboMulti)
	ON_BN_CLICKED(IDC_BUTTON_COMBO_FIXED, OnButtonComboFixed)
END_MESSAGE_MAP()

BOOL CEndoGridCLOptionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlDate.SetEditMask("00/00/0000", "__/__/____");

	theApp.LocalizeDialog(this, CEndoGridCLOptionDlg::IDD, "EndoGridCLOptionDlg");

	CString strTitle;
	GetWindowText(strTitle);
	strTitle = strTitle + m_pUserField->m_sParameterName;
	SetWindowText(strTitle);

	UpdateData(FALSE);
	UpdateDefaultFields();

	return TRUE;
}

void CEndoGridCLOptionDlg::OnOK()
{
	if (!UpdateData(TRUE))
		return;

	if (m_pUserField->GetFieldType() == CEndoGridCLParameterSet::type_date && m_strDefaultDate != "__/__/____")
	{
		COleDateTime date;
		if (!date.ParseDateTime(m_strDefaultDate))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DATE_FORMAT_INVALID), MB_ICONSTOP);
			GetDlgItem(IDC_DEFAULT_DATE)->SetFocus();
			return;
		}
	}

	switch (m_pUserField->GetFieldType())
	{
	case CEndoGridCLParameterSet::type_double: //float
		m_pUserField->m_fDefaultFloat = m_fDefaultReal;

		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		m_pUserField->SetFieldNull(&m_pUserField->m_sDefaultString);
		break;

	case CEndoGridCLParameterSet::type_check:
		m_pUserField->m_bDefaultBool = m_bDefaultCheck;

		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		m_pUserField->SetFieldNull(&m_pUserField->m_sDefaultString);
		break;

	case CEndoGridCLParameterSet::type_bool: //bool
		m_pUserField->m_bDefaultBool = m_bDefaultBool;

		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		m_pUserField->SetFieldNull(&m_pUserField->m_sDefaultString);
		break;

	case CEndoGridCLParameterSet::type_integer: //int
		m_pUserField->m_lDefaultInt = m_lDefaultInt;

		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_sDefaultString);
		break;

	case CEndoGridCLParameterSet::type_combo: //combo
		m_pUserField->m_sDefaultString = m_strDefaultCombo;

		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		break;

	case CEndoGridCLParameterSet::type_date: //data
		m_pUserField->m_sDefaultString.Format("%s%s%s000000",
			m_strDefaultDate.Mid(6, 4),
			m_strDefaultDate.Mid(3, 2),
			m_strDefaultDate.Mid(0, 2));

		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		break;

	case CEndoGridCLParameterSet::type_string: //string
		m_pUserField->m_sDefaultString = m_strDefaultString;

		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		break;

	case CEndoGridCLParameterSet::type_combo_multi: //combo multi
		m_pUserField->m_sDefaultString = m_strDefaultComboMulti;

		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		break;

	case CEndoGridCLParameterSet::type_notes:
		m_pUserField->m_sDefaultString = m_strDefaultNotes;
		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		break;

	case CEndoGridCLParameterSet::type_combo_fixed:
		m_pUserField->m_sDefaultString = m_strDefaultComboFixed;
		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		break;

	case CEndoGridCLParameterSet::type_date_free:
		m_pUserField->m_sDefaultString = m_strDefaultDateFree;
		m_pUserField->SetFieldNull(&m_pUserField->m_fDefaultFloat);
		m_pUserField->SetFieldNull(&m_pUserField->m_bDefaultBool);
		m_pUserField->SetFieldNull(&m_pUserField->m_lDefaultInt);
		break;

	default:
		ASSERT(FALSE);
		break;
	}

	CDialog::OnOK();
}

void CEndoGridCLOptionDlg::OnChangeRadio()
{
	UpdateDefaultFields();
}

void CEndoGridCLOptionDlg::OnButtonCombo()
{
	UpdateData(TRUE);
	CEndoGridComboDlg dlg(m_pUserField->m_lId, m_strDefaultCombo, FALSE, this);
	if (dlg.DoModal() == IDOK)
	{
		m_strDefaultCombo = dlg.m_strEdit;
		UpdateData(FALSE);
	}
}

void CEndoGridCLOptionDlg::OnButtonComboMulti()
{
	UpdateData(TRUE);
	CEndoGridComboDlg dlg(m_pUserField->m_lId, m_strDefaultCombo, TRUE, this);
	if (dlg.DoModal() == IDOK)
	{
		m_strDefaultComboMulti = dlg.m_strEdit;
		UpdateData(FALSE);
	}
}

void CEndoGridCLOptionDlg::OnButtonComboFixed()
{
	UpdateData(TRUE);
	CEndoGridComboDlg dlg(m_pUserField->m_lId, m_strDefaultComboFixed, FALSE, this);
	if (dlg.DoModal() == IDOK)
	{
		m_strDefaultComboFixed = dlg.m_strEdit;
		UpdateData(FALSE);
	}
}

void CEndoGridCLOptionDlg::UpdateDefaultFields()
{
	UpdateData(TRUE);

	UINT iControls[11][2] = { { IDC_DEFAULT_REAL, 0 },
	{ IDC_DEFAULT_BOOL, 0 },
	{ IDC_DEFAULT_INT, 0 },
	{ IDC_DEFAULT_COMBO, IDC_BUTTON_COMBO },	
	{ IDC_DEFAULT_DATE, 0 },
	{ IDC_DEFAULT_STRING, 0 },
	{ IDC_DEFAULT_COMBO_MULTI, IDC_BUTTON_COMBO_MULTI },
	{ IDC_DEFAULT_NOTES, 0 },
	{ IDC_DEFAULT_COMBO_FIXED, IDC_BUTTON_COMBO_FIXED },	
	{ IDC_DEFAULT_DATE_FREE, 0 },
	{ IDC_DEFAULT_CHECK, 0 } };

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (CWnd* pWnd = GetDlgItem(iControls[i][j]))
				pWnd->ShowWindow(m_pUserField->GetFieldType() == i ? SW_SHOW : SW_HIDE);
		}

		if (i == m_pUserField->GetFieldType() && GetDlgItem(iControls[i][0]))
			GetDlgItem(iControls[i][0])->SetFocus();
	}
}