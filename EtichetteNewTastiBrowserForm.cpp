#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewTastiBrowserForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT uiTestoVecchioBrowserEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoBrowserEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };
UINT uiEditBrowser[NUM_LABEL_TESTO_PAGE] = { IDC_EDIT_00, IDC_EDIT_01, IDC_EDIT_02, IDC_EDIT_03, IDC_EDIT_04, IDC_EDIT_05, IDC_EDIT_06, IDC_EDIT_07, IDC_EDIT_08, IDC_EDIT_09, IDC_EDIT_10, IDC_EDIT_11, IDC_EDIT_12, IDC_EDIT_13, IDC_EDIT_14, IDC_EDIT_15, IDC_EDIT_16, IDC_EDIT_17, IDC_EDIT_18, IDC_EDIT_19 };


CEtichetteNewTastiBrowserForm::CEtichetteNewTastiBrowserForm(CWnd* pParent)
	: CMyResizableDialog(CEtichetteNewTastiBrowserForm::IDD, pParent)
{
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelTastoBrowser[i];
		m_sTastoBrowserIndirizzo[i] = theApp.m_sTastoBrowserIndirizzo[i];
	}

	Create(CEtichetteNewTastiBrowserForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

}


CEtichetteNewTastiBrowserForm::~CEtichetteNewTastiBrowserForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewTastiBrowserForm, CMyResizableDialog)

END_MESSAGE_MAP()

void CEtichetteNewTastiBrowserForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);

	//

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
			DDX_Text(pDX, uiTestoVecchioBrowserEx[i], theApp.m_sLabelTastoBrowser[i]);

		DDX_Text(pDX, uiTestoNuovoBrowserEx[i], m_sTesto[i]);
		DDX_Text(pDX, uiEditBrowser[i], m_sTastoBrowserIndirizzo[i]);
	}
}

BOOL CEtichetteNewTastiBrowserForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	return TRUE;
}


void CEtichetteNewTastiBrowserForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// TESTI //
	///////////

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelTastoBrowser[i] = m_sTesto[i];
		theApp.m_sTastoBrowserIndirizzo[i] = m_sTastoBrowserIndirizzo[i];
	}
}
