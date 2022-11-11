#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewEtichetteForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT uiTestoVecchioEtichettaEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoEtichettaEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };


CEtichetteNewEtichetteForm::CEtichetteNewEtichetteForm(CWnd* pParent, int index)
	: CMyResizableDialog(CEtichetteNewEtichetteForm::IDD, pParent)
{
	m_iIndex = index;

	///////////
	// TESTI //
	///////////

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelTextEtichette[i + iPage];		
	}

	Create(CEtichetteNewEtichetteForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

}


CEtichetteNewEtichetteForm::~CEtichetteNewEtichetteForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewEtichetteForm, CMyResizableDialog)	
END_MESSAGE_MAP()

void CEtichetteNewEtichetteForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	//

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
		{			
			DDX_Text(pDX, uiTestoVecchioEtichettaEx[i], theApp.m_sLabelTextEtichette[i + iPage]);
		}

		DDX_Text(pDX, uiTestoNuovoEtichettaEx[i], m_sTesto[i]);		
	}
}

BOOL CEtichetteNewEtichetteForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	return TRUE;
}


void CEtichetteNewEtichetteForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// TESTI //
	///////////

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelTextEtichette[i + iPage] = m_sTesto[i];		
	}
}
