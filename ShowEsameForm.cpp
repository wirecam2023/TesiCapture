#include "stdafx.h"
#include "Endox.h"
#include "ShowEsameForm.h"

#include "MosaicDlg.h"
#include "ExportDlg.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShowEsameForm::CShowEsameForm(CWnd* pParent)
	: CEndoxResizableDlg(CShowEsameForm::IDD, pParent)
{
	m_nEsame	 = 0;
	m_pRigaEsame = NULL;
	m_pMosaicDlg = NULL;
}


void CShowEsameForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL_1, m_ctrlLabel1);
	DDX_Control(pDX, IDC_LABEL_2, m_ctrlLabel2);

	if (!pDX->m_bSaveAndValidate)
	{
		if (m_pRigaEsame)
		{
			DDX_Text(pDX, IDC_PAZIENTE, m_pRigaEsame->strPaziente);

			DDX_Date(pDX, IDC_DATA, m_pRigaEsame->nDataEsame, 1);

			if (m_pMosaicDlg)
			{
				m_BtnImmFirst.EnableWindow(m_pRigaEsame->nDiapoPage > 0);
				m_BtnImmPrev.EnableWindow(m_pRigaEsame->nDiapoPage > 0);
				m_BtnImmNext.EnableWindow(m_pRigaEsame->nDiapoPage < (m_pRigaEsame->nMaxDiapo / m_pMosaicDlg->m_nDiapoPerEsame));
				m_BtnImmLast.EnableWindow(m_pRigaEsame->nDiapoPage < (m_pRigaEsame->nMaxDiapo / m_pMosaicDlg->m_nDiapoPerEsame));
				GetDlgItem(IDC_BTN_SELECTALL)->EnableWindow((m_pRigaEsame->lPaziente > 0) && (m_pRigaEsame->lEsame > 0) && (m_pRigaEsame->nMaxDiapo >= 0));
			}
		}
	}
}

BOOL CShowEsameForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CShowEsameForm** pDlg)
{
	BOOL bResult = FALSE;

	(*pDlg) = new CShowEsameForm(NULL);
	if (*pDlg)
	{
		(*pDlg)->m_pParentFrame = pParentFrame;

		CRect rectFrame;
		pParentFrame->GetWindowRect(&rectFrame);
		// pParent->ScreenToClient(&rectFrame); // Sandro 17/09/2015 // forse va tolto //
		bResult = (*pDlg)->CreateChildForm(pParent, rectFrame);
	}
	
	return bResult;
}

BOOL CShowEsameForm::CreateChildForm(CWnd* pParentWnd, CRect rectFrame)
{
	BOOL result = FALSE;

	m_pParentWnd = pParentWnd;

	if (result = CEndoxResizableDlg::Create(IDD, pParentWnd))
		SetWindowPos( NULL, rectFrame.left, rectFrame.top, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);

	return result;
}

void CShowEsameForm::SetParameter(int nEsame, structEsame* pRiga)
{ 
	m_nEsame	 = nEsame;
	m_pRigaEsame = pRiga; 
}

BEGIN_MESSAGE_MAP(CShowEsameForm, CEndoxResizableDlg)
	ON_BN_CLICKED(IDC_IMM_FIRST,	OnPageFirst)
	ON_BN_CLICKED(IDC_IMM_PREV,		OnPagePrev)
	ON_BN_CLICKED(IDC_IMM_NEXT,		OnPageNext)
	ON_BN_CLICKED(IDC_IMM_LAST,		OnPageLast)
	ON_BN_CLICKED(IDC_BTN_SELECTALL, OnBnClickedBtnSelectall)
END_MESSAGE_MAP()

BOOL CShowEsameForm::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LABEL_1, CSize(50,45), CSize(50,45));
	AddAnchor(IDC_PAZIENTE, CSize(50,45), CSize(50,45));
	AddAnchor(IDC_LABEL_2, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_DATA, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_IMM_FIRST, CSize(50,55), CSize(50,55));
	AddAnchor(IDC_IMM_PREV, CSize(50,55), CSize(50,55));
	AddAnchor(IDC_IMM_NEXT, CSize(50,55), CSize(50,55));
	AddAnchor(IDC_IMM_LAST, CSize(50,55), CSize(50,55));
	AddAnchor(IDC_BTN_SELECTALL, CSize(50,55), CSize(50,55));

	m_BtnImmFirst.AutoLoad(IDC_IMM_FIRST,	this);
	m_BtnImmPrev .AutoLoad(IDC_IMM_PREV,	this);
	m_BtnImmNext .AutoLoad(IDC_IMM_NEXT,	this);
	m_BtnImmLast .AutoLoad(IDC_IMM_LAST,	this);
	
	theApp.LocalizeDialog(this, CShowEsameForm::IDD, "ShowEsameForm");

	return TRUE;
}

void CShowEsameForm::OnPageFirst()	
{ 
	if (m_pMosaicDlg && m_pRigaEsame)
	{
		m_pMosaicDlg->GoPageFirst(m_nEsame); 

		UpdateData(FALSE);
	}
}
void CShowEsameForm::OnPagePrev()	
{ 
	if (m_pMosaicDlg && m_pRigaEsame)
	{
		m_pMosaicDlg->GoPagePrev(m_nEsame);  

		UpdateData(FALSE);
	}
}

void CShowEsameForm::OnPageNext()
{ 
	if (m_pMosaicDlg && m_pRigaEsame)
	{
		m_pMosaicDlg->GoPageNext(m_nEsame);  

		UpdateData(FALSE);
	}
}

void CShowEsameForm::OnPageLast()
{ 
	if (m_pMosaicDlg && m_pRigaEsame)
	{
		m_pMosaicDlg->GoPageLast(m_nEsame);  

		UpdateData(FALSE);
	}
}

void CShowEsameForm::OnBnClickedBtnSelectall()
{
	if (m_pMosaicDlg && m_pRigaEsame)
	{
		m_pMosaicDlg->SelectAllImages(m_nEsame);  

		UpdateData(FALSE);
	}
}