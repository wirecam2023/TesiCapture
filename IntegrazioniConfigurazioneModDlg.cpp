#include "stdafx.h"
#include "Endox.h"
#include "IntegrazioniConfigurazioneModDlg.h"
#include "IntegrazioniParamConfigForm.h"
#include "IntegrazioniParamConfigUOForm.h"
#include "IntegrazioniVitalSignConfigForm.h"
#include "IntegrazioniRobotConfigForm.h"

#include "EsamiView.h"

#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CIntegrazioniConfigurazioneModDlg, CResizableDialog)

CIntegrazioniConfigurazioneModDlg::CIntegrazioniConfigurazioneModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CResizableDialog(CIntegrazioniConfigurazioneModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

}

CIntegrazioniConfigurazioneModDlg::~CIntegrazioniConfigurazioneModDlg()
{
}

void CIntegrazioniConfigurazioneModDlg::OnDestroy()
{
	for (int i = 0; i < _NUMERO_TAB; i++)
		delete(m_pForms[i]);

	CResizableDialog::OnDestroy();
}

BEGIN_MESSAGE_MAP(CIntegrazioniConfigurazioneModDlg, CResizableDialog)
	ON_WM_DESTROY()

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB,		OnTabPageSelChange)
END_MESSAGE_MAP()

void CIntegrazioniConfigurazioneModDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control (pDX, IDC_TAB,			m_ctrlTab);
	DDX_Control(pDX, IDCANCEL,			m_ctrlAbort);
	DDX_Control (pDX, IDOK,				m_ctrlExit);
}

BOOL CIntegrazioniConfigurazioneModDlg::OnInitDialog() 
{
	CResizableDialog::OnInitDialog();

	TC_ITEM TabCtrlItem1, TabCtrlItem2, TabCtrlItem3, TabCtrlItem4;
		
	TabCtrlItem1.mask = TCIF_TEXT;	
	TabCtrlItem1.pszText = "INTEGRAZIONI GENERALI";
	m_ctrlTab.InsertItem(0, &TabCtrlItem1);

	CUOSet uoSet;	
	TabCtrlItem2.mask = TCIF_TEXT;
	CString uo = uoSet.GetDescrizione(theApp.m_lUO);
	uo.MakeUpper();
	CString temp;
	temp.Format("INTEGRAZIONI UO %s", uo);
	TabCtrlItem2.pszText = temp.GetBuffer(255); //"GESTIONE INTEGRAZIONI GENERALI";
	temp.ReleaseBuffer();	
	m_ctrlTab.InsertItem(1, &TabCtrlItem2);

	TabCtrlItem3.mask = TCIF_TEXT;	
	TabCtrlItem3.pszText = "VITALSIGN";
	m_ctrlTab.InsertItem(2, &TabCtrlItem3);

	TabCtrlItem4.mask = TCIF_TEXT;
	TabCtrlItem4.pszText = "ROBOT MASTERIZZATORI";
	m_ctrlTab.InsertItem(3, &TabCtrlItem4);

	m_pForms[0] = (CResizableDialog*) new CIntegrazioniParamConfigForm(GetDlgItem(IDC_PLACE), this);
	m_pForms[1] = (CResizableDialog*) new CIntegrazioniParamConfigUOForm(GetDlgItem(IDC_PLACE), this);	
	m_pForms[2] = (CResizableDialog*) new CIntegrazioniVitalSignConfigForm(GetDlgItem(IDC_PLACE), this);
	m_pForms[3] = (CResizableDialog*) new CIntegrazioniRobotConfigForm(GetDlgItem(IDC_PLACE), this);

	AddAnchor(m_pForms[0]->GetSafeHwnd(), CSize(0,0), CSize(100,100));
	AddAnchor(m_pForms[1]->GetSafeHwnd(), CSize(0,0), CSize(100,100));	
	AddAnchor(m_pForms[2]->GetSafeHwnd(), CSize(0, 0), CSize(100, 100));
	AddAnchor(m_pForms[3]->GetSafeHwnd(), CSize(0, 0), CSize(100, 100));
	AddAnchor(m_ctrlAbort, CSize(0, 100), CSize(0, 100));
	AddAnchor(m_ctrlExit, CSize(100,100), CSize(100,100));

	m_lTab = 0;
	TabSelChange();

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	RedrawWindow();

	theApp.LocalizeDialog(this, CIntegrazioniConfigurazioneModDlg::IDD, "IntegrazioniConfigurazioneModDlg");
	return TRUE;
}

void CIntegrazioniConfigurazioneModDlg::OnTabPageSelChange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TabSelChange();
	
	*pResult = 0;
}

void CIntegrazioniConfigurazioneModDlg::TabSelChange() 
{
	m_lTab = m_ctrlTab.GetCurSel();

	ASSERT(m_lTab >= 0 && m_lTab < _NUMERO_TAB);
	
	for (int i = 0; i < _NUMERO_TAB; i++)
		m_pForms[i]->ShowWindow((i == m_lTab) ? SW_SHOW : SW_HIDE);
}

void  CIntegrazioniConfigurazioneModDlg::OnOK()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVE), MB_YESNO) == IDYES)
	{
		((CIntegrazioniParamConfigForm*)m_pForms[0])->Save();
		((CIntegrazioniParamConfigUOForm*)m_pForms[1])->Save();
		((CIntegrazioniVitalSignConfigForm*)m_pForms[2])->Save();		
		((CIntegrazioniRobotConfigForm*)m_pForms[3])->Save();

		CResizableDialog::OnOK();
	}	
}

void CIntegrazioniConfigurazioneModDlg::OnCancel()
{	
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ABORT), MB_YESNO) == IDYES)
	{
		CResizableDialog::OnCancel();
	}
}
