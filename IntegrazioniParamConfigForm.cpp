#include "stdafx.h"
#include "Endox.h"

#include "EsamiDoc.h"
#include "EsamiView.h"

#include "IntegrazioniParamConfigForm.h"
#include "IntegrazioniConfigurazioneModDlg.h"
#include "LivelliUrgenzaDlg.h"
#include "UoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CIntegrazioniParamConfigForm, CResizableDialog)

	ON_WM_CTLCOLOR()
	
	ON_BN_CLICKED(IDC_BTN_UO, &CIntegrazioniParamConfigForm::OnBnClickedBtnUo)

	ON_BN_CLICKED(IDC_BTN_LIVELLIURGENZA, &CIntegrazioniParamConfigForm::OnBnClickedBtnLivelliurgenza)

END_MESSAGE_MAP()

HBRUSH CIntegrazioniParamConfigForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_BTN_UO:
		{
			pDC->SetBkColor(theApp.m_color[0]);
				//SetTextColor
			break;
		}
	}

	return hBrush;
}


CIntegrazioniParamConfigForm::CIntegrazioniParamConfigForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* configDlg) : CResizableDialog(CIntegrazioniParamConfigForm::IDD, pParent)
{
	m_pConfigDlg = configDlg;

	CResizableDialog::Create(CIntegrazioniParamConfigForm::IDD, pParent->GetParent());	

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);
}

CIntegrazioniParamConfigForm::~CIntegrazioniParamConfigForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

void CIntegrazioniParamConfigForm::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);	
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	
	DDX_Control(pDX, IDC_BTN_UO,				m_ctrlBtnUO);	
	DDX_Control(pDX, IDC_CMB_LDAP,				m_ctrlCmbLDAP);	
	DDX_Control(pDX, IDC_CHK_PAZIENTISPORCHI,	m_ctrlChkPazientiSporchi);
}

BOOL CIntegrazioniParamConfigForm::OnInitDialog()
{
	CResizableDialog::OnInitDialog();	
		
	LoadLDAP();	
	LoadGestionePazienti();

	theApp.LocalizeDialog(this, CIntegrazioniParamConfigForm::IDD, "IntegrazioniParamConfigForm");
	return TRUE;
}

void CIntegrazioniParamConfigForm::LoadLDAP()
{
	// 0 normale, 1 o 3 utente windows, 2 o 4 con richiesta della password //

	int index = m_ctrlCmbLDAP.InsertString(0, theApp.GetMessageString(IDS_LOGIN_ENDOX));
	m_ctrlCmbLDAP.SetItemData(index, 0);
	index = m_ctrlCmbLDAP.InsertString(1, theApp.GetMessageString(IDS_LOGIN_SSO));
	m_ctrlCmbLDAP.SetItemData(index, 3);
	index = m_ctrlCmbLDAP.InsertString(2, theApp.GetMessageString(IDS_LOGIN_LDAP));
	m_ctrlCmbLDAP.SetItemData(index, 4);

	switch (theApp.m_lLoginMode)
	{
		case 0:
		{
			m_ctrlCmbLDAP.SetCurSel(0);
			break;
		}
		case 1:
		case 3:
		{
			m_ctrlCmbLDAP.SetCurSel(1);
			break;
		}
		case 2:
		case 4:
		{
			m_ctrlCmbLDAP.SetCurSel(2);
			break;
		}
	}
}

void CIntegrazioniParamConfigForm::LoadGestionePazienti()
{
	m_ctrlChkPazientiSporchi.SetCheck(theApp.m_bDisabilitaEsamiPazientiSenzaAssiden == TRUE ? BST_CHECKED : BST_UNCHECKED );
}

void CIntegrazioniParamConfigForm::SaveLDAP()
{
	int i = m_ctrlCmbLDAP.GetCurSel();
	theApp.m_lLoginMode = m_ctrlCmbLDAP.GetItemData(i);	
}

void CIntegrazioniParamConfigForm::SaveGestionePazienti()
{
	theApp.m_bDisabilitaEsamiPazientiSenzaAssiden = (m_ctrlChkPazientiSporchi.GetCheck() == BST_CHECKED ? TRUE : FALSE);
}

void CIntegrazioniParamConfigForm::Save()
{
	SaveLDAP();	
	SaveGestionePazienti();

	//salvataggio
	CEsamiDoc *doc = (CEsamiDoc*) m_pConfigDlg->m_pEsamiView->GetDocument();
	//doc->OnSalvaConfigurazione();
	doc->OnSalvaConfigurazioneIntegrazioniGenerale();
}

void CIntegrazioniParamConfigForm::OnBnClickedBtnUo()
{
	CUODlg dlg(this);
	dlg.DoModal();
}

void CIntegrazioniParamConfigForm::OnBnClickedBtnLivelliurgenza()
{
	CLivelliUrgenzaDlg dlg(this);
	dlg.DoModal();
}
