#include "stdafx.h"
#include "Endox.h"
#include "AboutBoxDlg.h"

#include "DLL_Imaging\h\TI_CECertification.h"

#include <GdiPlus.h>

#include "EsamiView.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAboutBoxDlg::CAboutBoxDlg(CWnd* pParent)
	: CDialog(CAboutBoxDlg::IDD, pParent)
{
	m_hCertificateBitmap = NULL;
}

BEGIN_MESSAGE_MAP(CAboutBoxDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

void CAboutBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStaticMail);
	DDX_Control(pDX, IDC_STATIC_34, m_ctrlStaticWeb);
}

void CAboutBoxDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);

	OnCancel();
}

HBRUSH CAboutBoxDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_02:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_STATIC_15:
		case IDC_STATIC_34:
		{
			pDC->SetTextColor(RGB(0, 0, 255));
			break;
		}
		case IDC_STATIC_43:
		case IDC_STATIC_45:
		{
			pDC->SetTextColor(RGB(0, 0, 255));
			break;
		}
	}

	return hBrush;
}

void CAboutBoxDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	if (m_hCertificateBitmap != NULL)
	{
		DeleteObject(m_hCertificateBitmap);
		m_hCertificateBitmap = NULL;
	}
}

BOOL CAboutBoxDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// marcatura CE del prodotto //

	m_hCertificateBitmap = GetCertificateBitmap(theApp.m_sNomeProgramma,
		                                        theApp.m_sNomeProgrammaCertificazione,
												theApp.m_sVersioneFull,
												theApp.m_sDataBuild.Right(4) + "/" + theApp.m_sDataBuild.Mid(3, 2),
												"",
												class_ce_1);

	Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromHBITMAP(m_hCertificateBitmap, NULL);

	CRect rect;
	GetDlgItem(IDC_PLACE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	INT iIncrementX = pBitmap->GetWidth() - rect.Width();
	INT iIncrementY = pBitmap->GetHeight() - rect.Height();

	CRect rectWnd;
	GetWindowRect(&rectWnd);
	SetWindowPos(NULL, 0, 0, rectWnd.Width() + iIncrementX, rectWnd.Height() + iIncrementY, SWP_NOMOVE | SWP_NOZORDER);

	GetDlgItem(IDC_PLACE)->SetWindowPos(NULL, 0, 0, rect.Width() + iIncrementX, rect.Height() + iIncrementY, SWP_NOMOVE | SWP_NOZORDER);

	delete pBitmap;

	// --- //

	CString strTitle = theApp.GetAppTitle(1);

	GetDlgItem(IDC_STATIC_02)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_07)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_08)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_09)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_10)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_35)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_12)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_13)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_14)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_15)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_33)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_34)->SetFont(&theApp.m_fontBold);

	m_ctrlStaticWeb.SetLinkUrl("www.tesi.mi.it");
	m_ctrlStaticWeb.ActiveToolTip(1);
	m_ctrlStaticWeb.SetTootTipText(theApp.GetMessageString(IDS_ABOUTBOX_WEB)); // Visita il nostro sito internet!

	m_ctrlStaticMail.SetLinkUrl("mailto:imaging@tesi.mi.it");
	m_ctrlStaticMail.ActiveToolTip(1);
	m_ctrlStaticMail.SetTootTipText(theApp.GetMessageString(IDS_ABOUTBOX_MAIL)); // Scrivici una mail!

	theApp.LocalizeDialog(this, CAboutBoxDlg::IDD, "AboutBoxDlg");
	SetWindowText(strTitle);

	return TRUE;
}

void CAboutBoxDlg::OnPaint()
{
	CPaintDC dc(this);

	Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromHBITMAP(m_hCertificateBitmap, NULL);
	Gdiplus::Graphics g(GetDlgItem(IDC_PLACE)->GetSafeHwnd());
	g.DrawImage(pBitmap, Gdiplus::Point(0,0));
	delete pBitmap;
}

void CAboutBoxDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnRButtonUp(nFlags, point);

	if (!((nFlags & MK_CONTROL) && (nFlags & MK_SHIFT)))
		OnCancel();
}

void CAboutBoxDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	CDialog::OnRButtonDblClk(nFlags, point);

	if ((nFlags & MK_CONTROL) && (nFlags & MK_SHIFT))
	{
		OnCancel();
		theApp.MessageBoxEndo("PROGRAMMA SVILUPPATO DA\n\nSandro Gallina\nVia Vecchia, 55\n30032 Fiesso d'Artico (VE)\n- ITALIA -\n\nCell.:\t+39 349 543 4217\nEmail:\ttesi@xendar.net", "", MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
	}
}