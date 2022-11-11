#include "stdafx.h"
#include "Endox.h"
#include "EndoxDynForm.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoxDynForm::CEndoxDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(nID, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lColore = -1;

	m_crCampoObbligatorio = 0;
}

CEndoxDynForm::~CEndoxDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CEndoxDynForm, CEndoxResizableDlg)
	ON_WM_PAINT()

	ON_MESSAGE(MSG_FORM_ANNULLAESAME, OnFormAnnullaEsame)
	ON_MESSAGE(MSG_FORM_ANNULLAPAZIENTE, OnFormAnnullaPaziente)
	ON_MESSAGE(MSG_FORM_CLONE, OnFormClone)
	ON_MESSAGE(MSG_FORM_LOAD, OnFormLoad)
	ON_MESSAGE(MSG_FORM_READONLY, OnFormReadOnly)
	ON_MESSAGE(MSG_FORM_RESET, OnFormReset)
	ON_MESSAGE(MSG_FORM_SAVE, OnFormSave)
	ON_MESSAGE(MSG_FORM_SEARCHNEW, OnFormSearchNew)
END_MESSAGE_MAP()

BOOL CEndoxDynForm::CreateChildForm(UINT nID, CWnd* pParentWnd, CRect rectFrame)
{
	BOOL bResult = CEndoxResizableDlg::Create(nID, pParentWnd);

	m_pParentWnd = pParentWnd;

	if (bResult != FALSE)
	{	
		ScreenToClient(rectFrame);
		SetWindowPos(NULL, rectFrame.left, rectFrame.top, rectFrame.Width(), rectFrame.Height(), SWP_NOZORDER | SWP_NOOWNERZORDER);
		ShowWindow(SW_SHOW);
	}

	return bResult;
}

void CEndoxDynForm::OnCancel() 
{
}

void CEndoxDynForm::OnOK() 
{
}

void CEndoxDynForm::EvidenziaCampoObbligatorioEx(COLORREF crColor)
{
	if (m_crCampoObbligatorio != crColor)
	{
		m_crCampoObbligatorio = crColor;
		RedrawWindow();
	}
}

LRESULT CEndoxDynForm::OnFormAnnullaPaziente(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoxDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoxDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoxDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoxDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoxDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoxDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoxDynForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	return 0;
}