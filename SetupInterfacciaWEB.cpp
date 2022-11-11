#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "SetupInterfacciaWEB.h"
#include "ConfigurazioniInterfacceSet.h"
#include "EsamiView.h"
#include ".\setupinterfacciaweb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSetupInterfacciaWEB, CDialog)

CSetupInterfacciaWEB::CSetupInterfacciaWEB(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CSetupInterfacciaWEB::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CSetupInterfacciaWEB::~CSetupInterfacciaWEB()
{
}

BEGIN_MESSAGE_MAP(CSetupInterfacciaWEB, CDialog)
	ON_BN_CLICKED(IDC_BTN_PERCORSO, OnBnClickedBtnPercorso)
END_MESSAGE_MAP()

void CSetupInterfacciaWEB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_MODALITA, m_ctrlComboModalita);
}

BOOL CSetupInterfacciaWEB::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlComboModalita.SetCurSel(theApp.m_bPubblicazioneAuto ? 1 : 0);
	SetDlgItemText(IDC_EDIT_PERCORSO, theApp.m_sPercorsoTemporaneoWEB);
	SetDlgItemText(IDC_EDIT_TO, theApp.m_sInterfacciaWebTo);
	SetDlgItemText(IDC_EDIT_FROM, theApp.m_sInterfacciaWebFrom);
	SetDlgItemText(IDC_EDIT_SUPPLIER, theApp.m_sInterfacciaWebSupplier);

	return bReturn;
}

void CSetupInterfacciaWEB::OnOK()
{
	CConfigurazioniInterfacceSet setTemp;

	theApp.m_bPubblicazioneAuto = (m_ctrlComboModalita.GetCurSel() == 1 ? TRUE : FALSE);
	setTemp.SetBoolValue("WEB - Pubblicazione automatica", theApp.m_bPubblicazioneAuto);

	GetDlgItemText(IDC_EDIT_PERCORSO, theApp.m_sPercorsoTemporaneoWEB);
	setTemp.SetStringValue("WEB - Percorso temporaneo", theApp.m_sPercorsoTemporaneoWEB);

	GetDlgItemText(IDC_EDIT_TO, theApp.m_sInterfacciaWebTo);
	setTemp.SetStringValue("WEB - To", theApp.m_sInterfacciaWebTo);

	GetDlgItemText(IDC_EDIT_FROM, theApp.m_sInterfacciaWebFrom);
	setTemp.SetStringValue("WEB - From", theApp.m_sInterfacciaWebFrom);

	GetDlgItemText(IDC_EDIT_SUPPLIER, theApp.m_sInterfacciaWebSupplier);
	setTemp.SetStringValue("WEB - Supplier", theApp.m_sInterfacciaWebSupplier);

	CDialog::OnOK();
}

void CSetupInterfacciaWEB::OnBnClickedBtnPercorso()
{
	CString strTemp;
	GetDlgItemText(IDC_EDIT_PERCORSO, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_8);
	CFolderDialog dlg(strTitle, strTemp, 64, this);
	if (dlg.DoModal() == IDOK)
	{
		strTemp = dlg.GetSelectedFolder();
		if (strTemp.Right(1) != '\\')
			strTemp += "\\";
		SetDlgItemText(IDC_EDIT_PERCORSO, strTemp);
	}
}
