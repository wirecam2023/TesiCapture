#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewChecklistForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT uiTestoVecchioCLEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoCLEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };
UINT uiCopiaCLEx[NUM_LABEL_TESTO_PAGE] = { IDC_COPIA_00, IDC_COPIA_01, IDC_COPIA_02, IDC_COPIA_03, IDC_COPIA_04, IDC_COPIA_05, IDC_COPIA_06, IDC_COPIA_07, IDC_COPIA_08, IDC_COPIA_09, IDC_COPIA_10, IDC_COPIA_11, IDC_COPIA_12, IDC_COPIA_13, IDC_COPIA_14, IDC_COPIA_15, IDC_COPIA_16, IDC_COPIA_17, IDC_COPIA_18, IDC_COPIA_19 };
UINT uiEditCL[NUM_LABEL_TESTO_PAGE] = { IDC_EDIT_00, IDC_EDIT_01, IDC_EDIT_02, IDC_EDIT_03, IDC_EDIT_04, IDC_EDIT_05, IDC_EDIT_06, IDC_EDIT_07, IDC_EDIT_08, IDC_EDIT_09, IDC_EDIT_10, IDC_EDIT_11, IDC_EDIT_12, IDC_EDIT_13, IDC_EDIT_14, IDC_EDIT_15, IDC_EDIT_16, IDC_EDIT_17, IDC_EDIT_18, IDC_EDIT_19 };
UINT uiAlarmCL[NUM_LABEL_TESTO_PAGE] = { IDC_ALARM00, IDC_ALARM01, IDC_ALARM02, IDC_ALARM03, IDC_ALARM04, IDC_ALARM05, IDC_ALARM06, IDC_ALARM07, IDC_ALARM08, IDC_ALARM09, IDC_ALARM10, IDC_ALARM11, IDC_ALARM12, IDC_ALARM13, IDC_ALARM14, IDC_ALARM15, IDC_ALARM16, IDC_ALARM17, IDC_ALARM18, IDC_ALARM19 };

CEtichetteNewChecklistForm::CEtichetteNewChecklistForm(CWnd* pParent)
	: CMyResizableDialog(CEtichetteNewChecklistForm::IDD, pParent)
{
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelTextCL[i];
		m_bCopia[i] = theApp.m_bCopyCL[i];
		m_bAlarmCL[i] = theApp.m_bAlarmCL[i];
		m_sParoleChiaveCL[i] = theApp.m_sParoleChiaveCL[i];
	}

	Create(CEtichetteNewChecklistForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

}


CEtichetteNewChecklistForm::~CEtichetteNewChecklistForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewChecklistForm, CMyResizableDialog)

	ON_BN_CLICKED(IDC_ALARM00, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM01, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM02, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM03, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM04, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM05, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM06, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM07, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM08, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM09, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM10, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM11, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM12, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM13, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM14, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM15, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM16, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM17, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM18, OnBnClickedAlarm)
	ON_BN_CLICKED(IDC_ALARM19, OnBnClickedAlarm)

END_MESSAGE_MAP()

void CEtichetteNewChecklistForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);

	//

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
		{
			DDX_Text(pDX, uiTestoVecchioCLEx[i], theApp.m_sLabelTextCL[i]);
		}

		DDX_Text(pDX, uiTestoNuovoCLEx[i], m_sTesto[i]);
		DDX_Check(pDX, uiCopiaCLEx[i], m_bCopia[i]);
		DDX_Check(pDX, uiAlarmCL[i], m_bAlarmCL[i]);
		DDX_Text(pDX, uiEditCL[i], m_sParoleChiaveCL[i]);

		if (m_bAlarmCL[i])
			GetDlgItem(uiEditCL[i])->EnableWindow(TRUE);
		else
			GetDlgItem(uiEditCL[i])->EnableWindow(FALSE);
	}
}

BOOL CEtichetteNewChecklistForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	return TRUE;
}


void CEtichetteNewChecklistForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// CHECKLIST //
	///////////

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelTextCL[i] = m_sTesto[i];
		theApp.m_bCopyCL[i] = m_bCopia[i];
		theApp.m_bAlarmCL[i] = m_bAlarmCL[i];
		theApp.m_sParoleChiaveCL[i] = m_sParoleChiaveCL[i];
	}
}


void CEtichetteNewChecklistForm::OnBnClickedAlarm()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}
