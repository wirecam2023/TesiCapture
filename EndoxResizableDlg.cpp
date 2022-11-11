#include "stdafx.h"
#include "Endox.h"
#include "EndoxResizableDlg.h"
#include "SubForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoxResizableDlg, CResizableDialog)

CEndoxResizableDlg::CEndoxResizableDlg(UINT nID, CWnd* pParent)
	: CResizableDialog(nID, pParent)
{
	m_pParentFrame = NULL;
}

CEndoxResizableDlg::~CEndoxResizableDlg()
{
}

BEGIN_MESSAGE_MAP(CEndoxResizableDlg, CResizableDialog)
	ON_MESSAGE(EPM_RESIZE_FORM, OnResizeForm)
END_MESSAGE_MAP()

void CEndoxResizableDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
}

LRESULT CEndoxResizableDlg::OnResizeForm(WPARAM wParam, LPARAM lParam)
{
	if (m_pParentFrame != NULL)
	{
		CRect rect;
		m_pParentFrame->GetWindowRect(rect);
		m_pParentWnd->ScreenToClient(rect);
		
		// Resize the form based on the new dimensions of static container //
		SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOOWNERZORDER | SWP_NOZORDER);
	}

	return 0;
}