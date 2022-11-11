#include "stdafx.h"
#include "Endox.h"
#include "MyRadio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMyRadio, CButtonLocalize)

CMyRadio::CMyRadio(UINT uiFocus)
{
	m_uiFocus = uiFocus;
}

CMyRadio::~CMyRadio()
{
}

BEGIN_MESSAGE_MAP(CMyRadio, CButtonLocalize)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CMyRadio::OnLButtonUp(UINT nFlags, CPoint point)
{
	CButtonLocalize::OnLButtonUp(nFlags, point);

	// Sandro 27/08/2010 - mando via il focus perchè altrimenti se premo un tasto della tastiera il programma va in loop //
	CWnd* pWnd = GetParent()->GetDlgItem(m_uiFocus);
	if (pWnd != NULL)
		pWnd->SetFocus();
	else
		GetParent()->SetFocus();
}