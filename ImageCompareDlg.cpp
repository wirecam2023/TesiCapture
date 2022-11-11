#include "stdafx.h"
#include "Endox.h"
#include "ImageCompareDlg.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CImageCompareDlg, CEndoxResizableDlg)

CImageCompareDlg::CImageCompareDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDPaziente, long lIDEsameL, long lIDEsameR, CImgListOrgani* pImgListOrganiL, long lIndexL, CImgListOrgani* pImgListOrganiR, long lIndexR)
	: CEndoxResizableDlg(CImageCompareDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;

	m_lIDPaziente = lIDPaziente;
	m_lIDEsameL = lIDEsameL;
	m_lIDEsameR = lIDEsameR;

	m_pImgListOrganiL = pImgListOrganiL;
	m_lIndexL = lIndexL;
	
	m_pImgListOrganiR = pImgListOrganiR;
	m_lIndexR = lIndexR;
}

CImageCompareDlg::~CImageCompareDlg()
{
	//
	m_ctrlStaticImageL.ReleaseResource();
	m_ctrlStaticImageR.ReleaseResource();
}

BEGIN_MESSAGE_MAP(CImageCompareDlg, CEndoxResizableDlg)

	ON_WM_HSCROLL()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()

	ON_WM_PAINT()

END_MESSAGE_MAP()

void CImageCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_IMAGE_L, m_ctrlStaticImageL);
	DDX_Control(pDX, IDC_STATIC_IMAGE_R, m_ctrlStaticImageR);

	DDX_Control(pDX, IDC_SCROLLBAR_L, m_ctrlScrollBarL);
	DDX_Control(pDX, IDC_SCROLLBAR_R, m_ctrlScrollBarR);
}

BOOL CImageCompareDlg::OnInitDialog()
{
	POSITION pos = NULL;

	//
	CEndoxResizableDlg::OnInitDialog();

	// rimuovo WS_THICKFRAME dallo stile della finestra //
	LONG lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyle &= ~WS_THICKFRAME;
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle);

	// blocco i vari controlli //
	AddAnchor(IDC_STATIC_IMAGE_L, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_SCROLLBAR_L, CSize(0, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_IMAGE_R, CSize(50, 0), CSize(100, 100));
	AddAnchor(IDC_SCROLLBAR_R, CSize(50, 100), CSize(100, 100));

	// imposto le due scrollbar //
	m_ctrlScrollBarL.SetScrollRange(0, 359);
	m_ctrlScrollBarL.SetScrollPos(0);
	m_ctrlScrollBarR.SetScrollRange(0, 359);
	m_ctrlScrollBarR.SetScrollPos(0);

	// ridimensiono la finestra a tutto schermo //
	SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_NOZORDER);

	// LEFT //
	m_ctrlStaticImageL.Create();

	pos = m_pImgListOrganiL->FindIndex(m_lIndexL);
	if (pos != NULL)
	{
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lIDPaziente, m_lIDEsameL);
		m_ctrlStaticImageL.SetImage(m_pEsamiView->m_pImgManager->GetImg(m_pImgListOrganiL->GetAt(pos).img.lID, FALSE, FALSE, FALSE));
	}

	// RIGHT //
	m_ctrlStaticImageR.Create();

	pos = m_pImgListOrganiR->FindIndex(m_lIndexR);
	if (pos != NULL)
	{
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lIDPaziente, m_lIDEsameR);
		m_ctrlStaticImageR.SetImage(m_pEsamiView->m_pImgManager->GetImg(m_pImgListOrganiR->GetAt(pos).img.lID, FALSE, FALSE, FALSE));
	}

	//
	m_ctrlStaticImageL.DecreaseZoom();
	m_ctrlStaticImageR.DecreaseZoom();

	//
	return TRUE;
}

void CImageCompareDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CEndoxResizableDlg::OnHScroll(nSBCode, nPos, pScrollBar);

	int nMin;
	int nMax;
	int nOldPos;
	int nNewPos;

	pScrollBar->GetScrollRange(&nMin, &nMax);
    nOldPos = pScrollBar->GetScrollPos();

	switch(nSBCode)
	{
		case SB_LEFT:
		{
			nNewPos = max(nMin, nOldPos - 1);
			break;
		}
		case SB_RIGHT:
		{
			nNewPos = min(nMax, nOldPos + 1);
			break;
		}
		case SB_LINELEFT:
		{
			nNewPos = max(nMin, nOldPos - 1);
			break;
		}
		case SB_LINERIGHT:
		{
			nNewPos = min(nMax, nOldPos + 1);
			break;
		}
		case SB_PAGELEFT:
		{
			nNewPos = max(nMin, nOldPos - 10);
			break;
		}
		case SB_PAGERIGHT:
		{
			nNewPos = min(nMax, nOldPos + 10);
			break;
		}
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
		{
			nNewPos = nPos;
			break;
		}		
		default:
		{
			nNewPos = nOldPos;
		}
	}

	if (pScrollBar == &m_ctrlScrollBarL)
	{
		m_ctrlScrollBarL.SetScrollPos(nNewPos);
		m_ctrlStaticImageL.RotateImage(nNewPos);
	}
	else if (pScrollBar == &m_ctrlScrollBarR)
	{
		m_ctrlScrollBarR.SetScrollPos(nNewPos);
		m_ctrlStaticImageR.RotateImage(nNewPos);
	}
}

void CImageCompareDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rectL;
	CRect rectR;

	m_ctrlStaticImageL.GetWindowRect(&rectL);
	m_ctrlStaticImageR.GetWindowRect(&rectR);

	ScreenToClient(&rectL);
	ScreenToClient(&rectR);

	if (rectL.PtInRect(point))
		m_ctrlStaticImageL.OnMouseClicked(nFlags, point);
	else if (rectR.PtInRect(point))
		m_ctrlStaticImageR.OnMouseClicked(nFlags, point);
}

void CImageCompareDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_ctrlStaticImageL.OnMouseReleased(nFlags, point);
	m_ctrlStaticImageR.OnMouseReleased(nFlags, point);
}

void CImageCompareDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rectL;
	CRect rectR;

	m_ctrlStaticImageL.GetWindowRect(&rectL);
	m_ctrlStaticImageR.GetWindowRect(&rectR);

	ScreenToClient(&rectL);
	ScreenToClient(&rectR);

	if (rectL.PtInRect(point))
		m_ctrlStaticImageL.OnMouseMoved(nFlags, point);
	else if (rectR.PtInRect(point))
		m_ctrlStaticImageR.OnMouseMoved(nFlags, point);
}

BOOL CImageCompareDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CRect rectL;
	CRect rectR;

	m_ctrlStaticImageL.GetWindowRect(&rectL);
	m_ctrlStaticImageR.GetWindowRect(&rectR);

	ScreenToClient(&rectL);
	ScreenToClient(&rectR);

	if (zDelta < 0)
	{
		// girata in giù //

		if (rectL.PtInRect(pt))
			m_ctrlStaticImageL.DecreaseZoom();
		else if (rectR.PtInRect(pt))
			m_ctrlStaticImageR.DecreaseZoom();
	}
	else
	{
		// girata in su //

		if (rectL.PtInRect(pt))
			m_ctrlStaticImageL.IncreaseZoom();
		else if (rectR.PtInRect(pt))
			m_ctrlStaticImageR.IncreaseZoom();
	}

	return CEndoxResizableDlg::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageCompareDlg::OnPaint()
{
	CPaintDC dc(this);
	m_ctrlStaticImageL.DrawPicture(&dc);
	m_ctrlStaticImageR.DrawPicture(&dc);
}
