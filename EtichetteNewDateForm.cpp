#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewDateForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT uiTestoVecchioDateEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoDateEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };

UINT uiCopiaDateEx[NUM_LABEL_TESTO_PAGE] = { IDC_COPIA_00, IDC_COPIA_01, IDC_COPIA_02, IDC_COPIA_03, IDC_COPIA_04, IDC_COPIA_05, IDC_COPIA_06, IDC_COPIA_07, IDC_COPIA_08, IDC_COPIA_09, IDC_COPIA_10, IDC_COPIA_11, IDC_COPIA_12, IDC_COPIA_13, IDC_COPIA_14, IDC_COPIA_15, IDC_COPIA_16, IDC_COPIA_17, IDC_COPIA_18, IDC_COPIA_19 };
UINT uiRadioNumDateEx[NUM_LABEL_TESTO_PAGE] = { IDC_RADIO_NUM00, IDC_RADIO_NUM01, IDC_RADIO_NUM02, IDC_RADIO_NUM03, IDC_RADIO_NUM04, IDC_RADIO_NUM05, IDC_RADIO_NUM06, IDC_RADIO_NUM07, IDC_RADIO_NUM08, IDC_RADIO_NUM09, IDC_RADIO_NUM10, IDC_RADIO_NUM11, IDC_RADIO_NUM12, IDC_RADIO_NUM13, IDC_RADIO_NUM14, IDC_RADIO_NUM15, IDC_RADIO_NUM16, IDC_RADIO_NUM17, IDC_RADIO_NUM18, IDC_RADIO_NUM19 };


CEtichetteNewDateForm::CEtichetteNewDateForm(CWnd* pParent)
	: CMyResizableDialog(CEtichetteNewDateForm::IDD, pParent)
{
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelDate[i];
		m_bCopiaDate[i] = theApp.m_bCopyDate[i];
		m_iRadioDate[i] = theApp.m_iRadioDate[i];
	}

	Create(CEtichetteNewDateForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

}


CEtichetteNewDateForm::~CEtichetteNewDateForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewDateForm, CMyResizableDialog)

END_MESSAGE_MAP()

void CEtichetteNewDateForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);

	//

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
			DDX_Text(pDX, uiTestoVecchioDateEx[i], theApp.m_sLabelDate[i]);

		DDX_Text(pDX, uiTestoNuovoDateEx[i], m_sTesto[i]);
		DDX_Check(pDX, uiCopiaDateEx[i], m_bCopiaDate[i]);
		DDX_Radio(pDX, uiRadioNumDateEx[i], m_iRadioDate[i]);
	}
}

BOOL CEtichetteNewDateForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	return TRUE;
}


void CEtichetteNewDateForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// DATE //
	///////////

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelDate[i] = m_sTesto[i];
		theApp.m_bCopyDate[i] = m_bCopiaDate[i];
		theApp.m_iRadioDate[i] = m_iRadioDate[i];
	}
}
