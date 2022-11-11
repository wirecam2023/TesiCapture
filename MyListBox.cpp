#include "stdafx.h"
#include "Endox.h"
#include "MyListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMyListBox, CListBox)

CMyListBox::CMyListBox()
{
	m_bEnabled = FALSE;
}

CMyListBox::~CMyListBox()
{
}

BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CMyListBox::EnableWindow(BOOL bEnable)
{
	m_bEnabled = bEnable;

	return bEnable;
}

BOOL CMyListBox::IsWindowEnabled()
{
	return m_bEnabled;
}

void CMyListBox::PreSubclassWindow()
{
	m_bEnabled = CListBox::IsWindowEnabled();

	CListBox::PreSubclassWindow();
}

void CMyListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_bEnabled)
		CListBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyListBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_bEnabled)
		CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMyListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnLButtonDblClk(nFlags, point);
}

void CMyListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnLButtonDown(nFlags, point);
}

void CMyListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnLButtonUp(nFlags, point);
}

void CMyListBox::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnMButtonDblClk(nFlags, point);
}

void CMyListBox::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnMButtonDown(nFlags, point);
}

void CMyListBox::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnMButtonUp(nFlags, point);
}

void CMyListBox::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnRButtonDblClk(nFlags, point);
}

void CMyListBox::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnRButtonDown(nFlags, point);
}

void CMyListBox::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_bEnabled)
		CListBox::OnRButtonUp(nFlags, point);
}