#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewGridCL.h"

#include "EndoGridModifyRulesDlg.h"
#include "ModifyGridCLConfigDlg.h"
#include "ModifyGridCLPrivilegiConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT uiTestoVecchioGridCLEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoGridCLEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };


CEtichetteNewGridCL::CEtichetteNewGridCL(CWnd* pParent, int index)
	: CMyResizableDialog(CEtichetteNewGridCL::IDD, pParent)
{
	m_iIndex = index;

	///////////
	// TESTI //
	///////////

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelTextGridCL[i + iPage];
	}

	Create(CEtichetteNewGridCL::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);
}

CEtichetteNewGridCL::~CEtichetteNewGridCL()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewGridCL, CMyResizableDialog)
	ON_BN_CLICKED(IDC_BTN_CONF_00, &CEtichetteNewGridCL::OnBnClickedBtnConf00)
	ON_BN_CLICKED(IDC_BTN_CONF_01, &CEtichetteNewGridCL::OnBnClickedBtnConf01)
	ON_BN_CLICKED(IDC_BTN_CONF_02, &CEtichetteNewGridCL::OnBnClickedBtnConf02)
	ON_BN_CLICKED(IDC_BTN_CONF_03, &CEtichetteNewGridCL::OnBnClickedBtnConf03)
	ON_BN_CLICKED(IDC_BTN_CONF_04, &CEtichetteNewGridCL::OnBnClickedBtnConf04)
	ON_BN_CLICKED(IDC_BTN_CONF_05, &CEtichetteNewGridCL::OnBnClickedBtnConf05)
	ON_BN_CLICKED(IDC_BTN_CONF_06, &CEtichetteNewGridCL::OnBnClickedBtnConf06)
	ON_BN_CLICKED(IDC_BTN_CONF_07, &CEtichetteNewGridCL::OnBnClickedBtnConf07)
	ON_BN_CLICKED(IDC_BTN_CONF_08, &CEtichetteNewGridCL::OnBnClickedBtnConf08)
	ON_BN_CLICKED(IDC_BTN_CONF_09, &CEtichetteNewGridCL::OnBnClickedBtnConf09)
	ON_BN_CLICKED(IDC_BTN_CONF_10, &CEtichetteNewGridCL::OnBnClickedBtnConf10)
	ON_BN_CLICKED(IDC_BTN_CONF_11, &CEtichetteNewGridCL::OnBnClickedBtnConf11)
	ON_BN_CLICKED(IDC_BTN_CONF_12, &CEtichetteNewGridCL::OnBnClickedBtnConf12)
	ON_BN_CLICKED(IDC_BTN_CONF_13, &CEtichetteNewGridCL::OnBnClickedBtnConf13)
	ON_BN_CLICKED(IDC_BTN_CONF_14, &CEtichetteNewGridCL::OnBnClickedBtnConf14)
	ON_BN_CLICKED(IDC_BTN_CONF_15, &CEtichetteNewGridCL::OnBnClickedBtnConf15)
	ON_BN_CLICKED(IDC_BTN_CONF_16, &CEtichetteNewGridCL::OnBnClickedBtnConf16)
	ON_BN_CLICKED(IDC_BTN_CONF_17, &CEtichetteNewGridCL::OnBnClickedBtnConf17)
	ON_BN_CLICKED(IDC_BTN_CONF_18, &CEtichetteNewGridCL::OnBnClickedBtnConf18)
	ON_BN_CLICKED(IDC_BTN_CONF_19, &CEtichetteNewGridCL::OnBnClickedBtnConf19)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_00, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi00)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_01, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi01)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_02, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi02)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_03, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi03)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_04, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi04)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_05, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi05)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_06, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi06)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_07, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi07)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_08, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi08)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_09, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi09)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_10, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi10)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_11, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi11)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_12, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi12)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_13, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi13)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_14, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi14)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_15, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi15)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_16, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi16)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_17, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi17)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_18, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi18)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGI_19, &CEtichetteNewGridCL::OnBnClickedBtnPrivilegi19)
	ON_BN_CLICKED(IDC_BTN_REGOLE_00, &CEtichetteNewGridCL::OnBnClickedBtnRegole00)
	ON_BN_CLICKED(IDC_BTN_REGOLE_01, &CEtichetteNewGridCL::OnBnClickedBtnRegole01)
	ON_BN_CLICKED(IDC_BTN_REGOLE_02, &CEtichetteNewGridCL::OnBnClickedBtnRegole02)
	ON_BN_CLICKED(IDC_BTN_REGOLE_03, &CEtichetteNewGridCL::OnBnClickedBtnRegole03)
	ON_BN_CLICKED(IDC_BTN_REGOLE_04, &CEtichetteNewGridCL::OnBnClickedBtnRegole04)
	ON_BN_CLICKED(IDC_BTN_REGOLE_05, &CEtichetteNewGridCL::OnBnClickedBtnRegole05)
	ON_BN_CLICKED(IDC_BTN_REGOLE_06, &CEtichetteNewGridCL::OnBnClickedBtnRegole06)
	ON_BN_CLICKED(IDC_BTN_REGOLE_07, &CEtichetteNewGridCL::OnBnClickedBtnRegole07)
	ON_BN_CLICKED(IDC_BTN_REGOLE_08, &CEtichetteNewGridCL::OnBnClickedBtnRegole08)
	ON_BN_CLICKED(IDC_BTN_REGOLE_09, &CEtichetteNewGridCL::OnBnClickedBtnRegole09)
	ON_BN_CLICKED(IDC_BTN_REGOLE_10, &CEtichetteNewGridCL::OnBnClickedBtnRegole10)
	ON_BN_CLICKED(IDC_BTN_REGOLE_11, &CEtichetteNewGridCL::OnBnClickedBtnRegole11)
	ON_BN_CLICKED(IDC_BTN_REGOLE_12, &CEtichetteNewGridCL::OnBnClickedBtnRegole12)
	ON_BN_CLICKED(IDC_BTN_REGOLE_13, &CEtichetteNewGridCL::OnBnClickedBtnRegole13)
	ON_BN_CLICKED(IDC_BTN_REGOLE_14, &CEtichetteNewGridCL::OnBnClickedBtnRegole14)
	ON_BN_CLICKED(IDC_BTN_REGOLE_15, &CEtichetteNewGridCL::OnBnClickedBtnRegole15)
	ON_BN_CLICKED(IDC_BTN_REGOLE_16, &CEtichetteNewGridCL::OnBnClickedBtnRegole16)
	ON_BN_CLICKED(IDC_BTN_REGOLE_17, &CEtichetteNewGridCL::OnBnClickedBtnRegole17)
	ON_BN_CLICKED(IDC_BTN_REGOLE_18, &CEtichetteNewGridCL::OnBnClickedBtnRegole18)
	ON_BN_CLICKED(IDC_BTN_REGOLE_19, &CEtichetteNewGridCL::OnBnClickedBtnRegole19)
END_MESSAGE_MAP()

void CEtichetteNewGridCL::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	//

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
		{
			DDX_Text(pDX, uiTestoVecchioGridCLEx[i], theApp.m_sLabelTextGridCL[i + iPage]);
		}

		DDX_Text(pDX, uiTestoNuovoGridCLEx[i], m_sTesto[i]);
	}
}

BOOL CEtichetteNewGridCL::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	return TRUE;
}


void CEtichetteNewGridCL::Savee()
{
	UpdateData(TRUE);

	///////////
	// TESTI //
	///////////

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelTextGridCL[i + iPage] = m_sTesto[i];
	}
}



void CEtichetteNewGridCL::OnBnClickedBtnConf00()
{
	OpenGridCLConfig(0);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf01()
{
	OpenGridCLConfig(1);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf02()
{
	OpenGridCLConfig(2);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf03()
{
	OpenGridCLConfig(3);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf04()
{
	OpenGridCLConfig(4);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf05()
{
	OpenGridCLConfig(5);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf06()
{
	OpenGridCLConfig(6);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf07()
{
	OpenGridCLConfig(7);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf08()
{
	OpenGridCLConfig(8);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf09()
{
	OpenGridCLConfig(9);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf10()
{
	OpenGridCLConfig(10);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf11()
{
	OpenGridCLConfig(11);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf12()
{
	OpenGridCLConfig(12);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf13()
{
	OpenGridCLConfig(13);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf14()
{
	OpenGridCLConfig(14);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf15()
{
	OpenGridCLConfig(15);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf16()
{
	OpenGridCLConfig(16);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf17()
{
	OpenGridCLConfig(17);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf18()
{
	OpenGridCLConfig(18);
}


void CEtichetteNewGridCL::OnBnClickedBtnConf19()
{
	OpenGridCLConfig(19);
}

void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi00()
{
	OpenGridCLPrivilegiConfig(0);
}

void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi01()
{
	OpenGridCLPrivilegiConfig(1);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi02()
{
	OpenGridCLPrivilegiConfig(2);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi03()
{
	OpenGridCLPrivilegiConfig(3);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi04()
{
	OpenGridCLPrivilegiConfig(4);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi05()
{
	OpenGridCLPrivilegiConfig(5);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi06()
{
	OpenGridCLPrivilegiConfig(6);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi07()
{
	OpenGridCLPrivilegiConfig(7);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi08()
{
	OpenGridCLPrivilegiConfig(8);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi09()
{
	OpenGridCLPrivilegiConfig(9);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi10()
{
	OpenGridCLPrivilegiConfig(10);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi11()
{
	OpenGridCLPrivilegiConfig(11);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi12()
{
	OpenGridCLPrivilegiConfig(12);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi13()
{
	OpenGridCLPrivilegiConfig(13);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi14()
{
	OpenGridCLPrivilegiConfig(14);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi15()
{
	OpenGridCLPrivilegiConfig(15);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi16()
{
	OpenGridCLPrivilegiConfig(16);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi17()
{
	OpenGridCLPrivilegiConfig(17);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi18()
{
	OpenGridCLPrivilegiConfig(18);
}


void CEtichetteNewGridCL::OnBnClickedBtnPrivilegi19()
{
	OpenGridCLPrivilegiConfig(19);
}

void CEtichetteNewGridCL::OnBnClickedBtnRegole00()
{
	OpenGridCLRegoleConfig(0);
}

void CEtichetteNewGridCL::OnBnClickedBtnRegole01()
{
	OpenGridCLRegoleConfig(1);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole02()
{
	OpenGridCLRegoleConfig(2);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole03()
{
	OpenGridCLRegoleConfig(3);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole04()
{
	OpenGridCLRegoleConfig(4);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole05()
{
	OpenGridCLRegoleConfig(5);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole06()
{
	OpenGridCLRegoleConfig(6);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole07()
{
	OpenGridCLRegoleConfig(7);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole08()
{
	OpenGridCLRegoleConfig(8);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole09()
{
	OpenGridCLRegoleConfig(9);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole10()
{
	OpenGridCLRegoleConfig(10);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole11()
{
	OpenGridCLRegoleConfig(11);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole12()
{
	OpenGridCLRegoleConfig(12);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole13()
{
	OpenGridCLRegoleConfig(13);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole14()
{
	OpenGridCLRegoleConfig(14);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole15()
{
	OpenGridCLRegoleConfig(15);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole16()
{
	OpenGridCLRegoleConfig(16);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole17()
{
	OpenGridCLRegoleConfig(17);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole18()
{
	OpenGridCLRegoleConfig(18);
}


void CEtichetteNewGridCL::OnBnClickedBtnRegole19()
{
	OpenGridCLRegoleConfig(19);
}

void CEtichetteNewGridCL::OpenGridCLConfig(int index)
{
	int iPage = index + (m_iIndex*NUM_LABEL_TESTO_PAGE);

	CModifyGridCLConfigDlg(this, iPage).DoModal();
}

void CEtichetteNewGridCL::OpenGridCLPrivilegiConfig(int index)
{
	int iPage = index + (m_iIndex*NUM_LABEL_TESTO_PAGE);

	CModifyGridCLPrivilegiConfigDlg(this, iPage).DoModal();
}

void CEtichetteNewGridCL::OpenGridCLRegoleConfig(int index)
{
	int iPage = index + (m_iIndex*NUM_LABEL_TESTO_PAGE);

	CEndoGridModifyRulesDlg(this, iPage).DoModal();
}