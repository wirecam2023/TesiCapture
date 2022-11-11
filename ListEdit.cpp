#include "stdafx.h"
#include "Endox.h"
#include "ListEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CListEdit, CEdit)

CListEdit::CListEdit()
	:CEdit()
{
	m_pParentView	= NULL;
	m_pListBox		= NULL;
}

CListEdit::~CListEdit()
{
}

BEGIN_MESSAGE_MAP(CListEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CListEdit::SetParam(CWnd* pParentForm, CListBox* pListBox)
{
	m_pParentView	= pParentForm;
	m_pListBox		= pListBox;
}

void CListEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
		/**
		case VK_END:
		case VK_HOME:
		case VK_LEFT:
		case VK_RIGHT:
		**/
		case VK_PRIOR:
		case VK_NEXT:
		case VK_UP:
		case VK_DOWN:
			if (m_pListBox)
			{
				WPARAM wParam = nChar;
				LPARAM lParam = MAKELPARAM(nRepCnt, nFlags);

				m_pListBox->PostMessage(WM_KEYDOWN, wParam, lParam);
			}
			break;
		
		default:
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}

}