#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewDlg.h"

#include "EtichetteNewChecklistForm.h"
#include "EtichetteNewDateForm.h"
#include "EtichetteNewEtichetteForm.h"
#include "EtichetteNewGridCL.h"
#include "EtichetteNewTastiBrowserForm.h"
#include "EtichetteNewTastiChiusuraFaseForm.h"
#include "EtichetteNewTastiEseguibileForm.h"
#include "EtichetteNewTastiStampaForm.h"
#include "EtichetteNewTestiForm.h"
#include "EtichetteNewRTFForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEtichetteNewDlg, CResizableDialog)

CEtichetteNewDlg::CEtichetteNewDlg(CWnd* pParent)
	: CResizableDialog(CEtichetteNewDlg::IDD, pParent)
{
}


CEtichetteNewDlg::~CEtichetteNewDlg()
{
}

BEGIN_MESSAGE_MAP(CEtichetteNewDlg, CResizableDialog)
	ON_WM_DESTROY()

	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, &CEtichetteNewDlg::OnTcnSelchangingTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CEtichetteNewDlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDCANCEL, &CEtichetteNewDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CEtichetteNewDlg::OnBnClickedOk)
END_MESSAGE_MAP()


void CEtichetteNewDlg::OnDestroy()
{
	for (int i = 0; i < _NUMERO_TAB_ET; i++)
		delete(m_pForms[i]);

	CDialog::OnDestroy();
}

void CEtichetteNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB, m_ctrlTab);
}

BOOL CEtichetteNewDlg::OnInitDialog()
{
	BeginWaitCursor();

	CResizableDialog::OnInitDialog();

	TC_ITEM tcItem[_NUMERO_TAB_ET];

	CString titles[_NUMERO_TAB_ET] = { "Testi 00-19", "Testi 20-39", "Testi 40-59", "Testi 60-79", "Testi 80-99", "Tesi RTF", "Checklist", "Date", "Tasti stampa", "Tasti browser", "Tasti eseguibile", "Etichette 00-19", "Etichette 20-39", "Tasti chiusura fase", "Checklist a griglia 00-19", "Checklist a griglia 20-39" };

	for (int i = 0; i < _NUMERO_TAB_ET; i++)
	{
		tcItem[i].mask = TCIF_TEXT;
		tcItem[i].pszText = titles[i].GetBuffer(255);
		titles[i].ReleaseBuffer();
		m_ctrlTab.InsertItem(i, &tcItem[i]);		
	}

	m_pForms[0] = (CMyResizableDialog*) new CEtichetteNewTestiForm(GetDlgItem(IDC_PLACE), 0);
	m_pForms[1] = (CMyResizableDialog*) new CEtichetteNewTestiForm(GetDlgItem(IDC_PLACE), 1);
	m_pForms[2] = (CMyResizableDialog*) new CEtichetteNewTestiForm(GetDlgItem(IDC_PLACE), 2);
	m_pForms[3] = (CMyResizableDialog*) new CEtichetteNewTestiForm(GetDlgItem(IDC_PLACE), 3);
	m_pForms[4] = (CMyResizableDialog*) new CEtichetteNewTestiForm(GetDlgItem(IDC_PLACE), 4);
	m_pForms[5] = (CMyResizableDialog*) new CEtichetteNewRTFForm(GetDlgItem(IDC_PLACE));
	m_pForms[6] = (CMyResizableDialog*) new CEtichetteNewChecklistForm(GetDlgItem(IDC_PLACE));
	m_pForms[7] = (CMyResizableDialog*) new CEtichetteNewDateForm(GetDlgItem(IDC_PLACE));
	m_pForms[8] = (CMyResizableDialog*) new CEtichetteNewTastiStampaForm(GetDlgItem(IDC_PLACE));
	m_pForms[9] = (CMyResizableDialog*) new CEtichetteNewTastiBrowserForm(GetDlgItem(IDC_PLACE));
	m_pForms[10] = (CMyResizableDialog*) new CEtichetteNewTastiEseguibileForm(GetDlgItem(IDC_PLACE));
	m_pForms[11] = (CMyResizableDialog*) new CEtichetteNewEtichetteForm(GetDlgItem(IDC_PLACE), 0);
	m_pForms[12] = (CMyResizableDialog*) new CEtichetteNewEtichetteForm(GetDlgItem(IDC_PLACE), 1);
	m_pForms[13] = (CMyResizableDialog*) new CEtichetteNewTastiChiusuraFaseForm(GetDlgItem(IDC_PLACE));
	m_pForms[14] = (CMyResizableDialog*) new CEtichetteNewGridCL(GetDlgItem(IDC_PLACE), 0);
	m_pForms[15] = (CMyResizableDialog*) new CEtichetteNewGridCL(GetDlgItem(IDC_PLACE), 1);

	for (int i = 0; i < _NUMERO_TAB_ET; i++)
		AddAnchor(m_pForms[i]->GetSafeHwnd(), CSize(0, 0), CSize(100, 100));
	
	AddAnchor(IDC_TAB, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));	

	LoadTab(0);

	RedrawWindow();

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	EndWaitCursor();

	return TRUE;
}

void CEtichetteNewDlg::OnTcnSelchangingTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}


void CEtichetteNewDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Carico la tab giusta
	LoadTab(m_ctrlTab.GetCurSel());

	*pResult = 0;
}

void CEtichetteNewDlg::LoadTab(int index)
{
	//Carico la form corrispondente alla tab
	m_lTab = index;

	ASSERT(m_lTab >= 0 && m_lTab < _NUMERO_TAB_ET);

	//SetRedraw(FALSE);
	
	for (int i = 0; i < _NUMERO_TAB_ET; i++)
	{
		BOOL bShow = (i == m_lTab);
		m_pForms[i]->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	}

	//SetRedraw(TRUE);
}

void CEtichetteNewDlg::OnBnClickedCancel()
{
	CResizableDialog::OnCancel();
}


void CEtichetteNewDlg::OnBnClickedOk()
{
	for (int i = 0; i < _NUMERO_TAB_ET; i++)
	{
		m_pForms[i]->Savee();					
	}

	CResizableDialog::OnOK();
}
