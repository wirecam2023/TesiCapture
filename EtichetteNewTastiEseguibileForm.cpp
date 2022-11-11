#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewTastiEseguibileForm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT uiTestoVecchioEseguibileEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoEseguibileEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };
UINT uiEditEseguibile[NUM_LABEL_TESTO_PAGE] = { IDC_EDIT_00, IDC_EDIT_01, IDC_EDIT_02, IDC_EDIT_03, IDC_EDIT_04, IDC_EDIT_05, IDC_EDIT_06, IDC_EDIT_07, IDC_EDIT_08, IDC_EDIT_09, IDC_EDIT_10, IDC_EDIT_11, IDC_EDIT_12, IDC_EDIT_13, IDC_EDIT_14, IDC_EDIT_15, IDC_EDIT_16, IDC_EDIT_17, IDC_EDIT_18, IDC_EDIT_19 };


CEtichetteNewTastiEseguibileForm::CEtichetteNewTastiEseguibileForm(CWnd* pParent)
	: CMyResizableDialog(CEtichetteNewTastiEseguibileForm::IDD, pParent)
{
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelTastoEseguibile[i];
		m_sTastoEseguibileFile[i] = theApp.m_sTastoEseguibileFile[i];
	}

	Create(CEtichetteNewTastiEseguibileForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

}


CEtichetteNewTastiEseguibileForm::~CEtichetteNewTastiEseguibileForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewTastiEseguibileForm, CMyResizableDialog)

END_MESSAGE_MAP()

void CEtichetteNewTastiEseguibileForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);

	//

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
			DDX_Text(pDX, uiTestoVecchioEseguibileEx[i], theApp.m_sLabelTastoEseguibile[i]);

		DDX_Text(pDX, uiTestoNuovoEseguibileEx[i], m_sTesto[i]);
		DDX_Text(pDX, uiEditEseguibile[i], m_sTastoEseguibileFile[i]);
	}
}

BOOL CEtichetteNewTastiEseguibileForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	return TRUE;
}


void CEtichetteNewTastiEseguibileForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// TESTI //
	///////////

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelTastoEseguibile[i] = m_sTesto[i];
		theApp.m_sTastoEseguibileFile[i] = m_sTastoEseguibileFile[i];
	}
}
