#include "stdafx.h"
#include "Endox.h"
#include "Bmp.h"

#include <io.h>

#include "Check.h"
#include "EditBmp.h"
#include "MaximizeDlg.h"
#include "Common.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEsamiView* CBmp::m_pEsamiView = NULL;
CWnd* CBmp::m_pParentWnd = NULL;
COLORREF CBmp::m_rgbPointColors[6] = { RGB(192, 0, 0), RGB(192, 192, 0), RGB(0, 192, 0), RGB(0, 192, 192), RGB(0, 0, 192), RGB(192, 0, 192) };

CBmp::CBmp()
{
	m_nBtnMouseModeLeft = BMP_L_NORMALMODE;
	m_nBtnMouseModeRight = BMP_R_NORMALMODE;

	m_pActiveView = NULL;
	m_pParentFrame = NULL;
	m_pParentAlbum = NULL;
	m_pParentWnd = NULL;
	m_pDib = NULL;
	m_bIsSelect = FALSE;

	m_bAutoRedraw = TRUE;

	m_pEditWnd = NULL;

	m_iPointNumber = -1;
	m_iPositionNumber = -1;
}

CBmp::~CBmp()
{
	m_pActiveView = NULL;
	m_pParentWnd = NULL;
	m_pParentFrame = NULL;
	m_pParentAlbum = NULL;
}

BEGIN_MESSAGE_MAP(CBmp, CWnd)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()

	ON_MESSAGE(EPM_RESIZE_FORM, OnResizeForm)
END_MESSAGE_MAP()

void CBmp::AssignEdit(CEditBmp* pEdit)
{
	pEdit->AssignBmp(this);
	m_pEditWnd = pEdit;
}

void CBmp::AutoRedraw(CRect* pRect)
{
	RedrawWindow(pRect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_INTERNALPAINT | RDW_NOERASE);
}

BOOL CBmp::Create(const RECT& rect, CWnd* pParentWnd)
{
	return CWnd::Create(NULL, NULL, WS_CHILD, rect, pParentWnd, IDD_CUSTOM_BMP);
}

BOOL CBmp::CreateBmp(CEsamiView* pActiveView, CWnd* pParentWnd, CWnd* pctrFrame, CBmp* pBmp)
{
	ASSERT(pActiveView != NULL);
	ASSERT(pctrFrame != NULL);

	ASSERT(pBmp->m_pParentFrame == NULL);
	ASSERT(pBmp->m_pParentAlbum == NULL);

	CRect rectFrame;
	pctrFrame->GetWindowRect(&rectFrame);
	pParentWnd->ScreenToClient(&rectFrame);

	if (pBmp)
	{
		if (pBmp->Create(rectFrame, pParentWnd))
		{
			pBmp->m_pParentFrame = pctrFrame;
			pBmp->m_pParentAlbum = pParentWnd;
			pBmp->m_pActiveView = pActiveView;
			pBmp->m_pParentWnd = pParentWnd;

			return TRUE;
		}
	}

	return FALSE;
}

void CBmp::DeSelectBmp()
{
	if (IsValidBmp())
	{
		m_bIsSelect = FALSE;

		AutoRedraw();
	}
}

BOOL CBmp::IsSelect()
{
	return m_bIsSelect;
}

BOOL CBmp::IsValidBmp()
{
	return m_pDib && m_pDib->IsValidDib();
}

void CBmp::OnPaint()
{
	CRect		RectClient, RectDib;
	CPaintDC 	dc(this);

	if (!m_bAutoRedraw)
		return;

	GetClientRect(&RectClient);
	RectClient.InflateRect(-2, -2);

	CBrush NullBrush;

	NullBrush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	dc.FillRect(RectClient, &NullBrush);
	NullBrush.DeleteObject();

	if (m_pDib && m_pDib->IsValidDib())
	{
		RectDib = CRect(0, 0, m_pDib->Width(), m_pDib->Height());

		if (RectClient.Width() > RectDib.Width() || RectClient.Height() > RectDib.Height())
		{
			if (RectDib.Width() >= RectDib.Height())
			{
				RectDib.left = (RectDib.Width() - RectDib.Height()) / 2;
				RectDib.right = RectDib.left + RectDib.Height();
			}
			else
			{
				RectDib.top = (RectDib.Height() - RectDib.Width()) / 2;
				RectDib.bottom = RectDib.top + RectClient.Width();
			}
		}

		m_pDib->PaintDIB(dc.GetSafeHdc(), RectClient, RectDib);

		if (m_bIsSelect)
		{
			HICON hIcon;

			hIcon = AfxGetApp()->LoadIcon(IDI_SELECT);

			dc.DrawIcon(RectClient.left, RectClient.top, hIcon);
		}
	}
}

void CBmp::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_nBtnMouseModeRight == BMP_R_NORMALMODE)
		SelectBmp();
	else
		SendBmpMessage(MSG_SELECT_BMP);
}

LRESULT CBmp::OnResizeForm(WPARAM wParam, LPARAM lParam)
{
	if ((m_pParentFrame != NULL) && (m_pParentAlbum != NULL))
	{
		CRect rect;
		m_pParentFrame->GetWindowRect(rect);
		m_pParentAlbum->ScreenToClient(rect);

		SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOOWNERZORDER | SWP_NOZORDER);
	}

	return 0;
}

BOOL CBmp::SelectBmp()
{
	if (IsValidBmp())
	{
		m_bIsSelect = !m_bIsSelect;

		AutoRedraw();

		return TRUE;
	}

	return FALSE;
}

BOOL CBmp::SelectBmp(BOOL bSelect)
{
	if (IsValidBmp())
	{
		m_bIsSelect = bSelect;

		AutoRedraw();

		return TRUE;
	}

	return FALSE;
}

void CBmp::SendBmpMessage(UINT nMsg)
{
	::PostMessage(m_pParentWnd->GetSafeHwnd(), nMsg, (WPARAM)NULL, (LPARAM)this);
}

void CBmp::SetMouseMode(int nLeft, int nRight)
{
	ASSERT((nLeft == BMP_L_NORMALMODE) || (nLeft == BMP_L_NODOUBLECLICK));
	ASSERT((nRight == BMP_R_NORMALMODE) || (nRight == BMP_R_SENDTOPARENT));

	m_nBtnMouseModeLeft = nLeft;
	m_nBtnMouseModeRight = nRight;
}

int CBmp::GetPointNumber()
{
	return m_iPointNumber;
}

int CBmp::GetPositionNumber()
{
	return m_iPositionNumber;
}

void CBmp::SetPoint(int iPointNumber, COLORREF colorCircle, COLORREF colorNumber, BOOL bRedraw)
{
	m_iPointNumber = iPointNumber;
	m_colorCircle = colorCircle;
	m_colorNumber = colorNumber;

	if (bRedraw == TRUE)
		AutoRedraw();
}

void CBmp::SetPointAutoColor(int iPointNumber, BOOL bRedraw)
{
	m_iPointNumber = iPointNumber;
	m_colorCircle = m_rgbPointColors[iPointNumber % 6];
	m_colorNumber = RGB_WHITE;

	if (bRedraw == TRUE)
		AutoRedraw();
}

void CBmp::SetPointColor(COLORREF colorCircle, COLORREF colorNumber, BOOL bRedraw)
{
	m_colorCircle = colorCircle;
	m_colorNumber = colorNumber;

	if (bRedraw == TRUE)
		AutoRedraw();
}

void CBmp::SetPointNumber(int iPointNumber, BOOL bRedraw)
{
	m_iPointNumber = iPointNumber;

	if (bRedraw == TRUE)
		AutoRedraw();
}

void CBmp::SetPositionNumber(int iPositionNumber, int iTotalImageNumber, BOOL bRedraw)
{
	m_iPositionNumber = iPositionNumber;
	m_iTotalImageNumber = iTotalImageNumber;

	if (bRedraw == TRUE)
		AutoRedraw();
}