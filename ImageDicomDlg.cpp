#include "stdafx.h"
#include "Endox.h"
#include "ImageDicomDlg.h"

#include "DLL_Imaging\h\AmDcmViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CImageDicomDlg, CEndoxResizableDlg)

CImageDicomDlg::CImageDicomDlg(CWnd* pParent, CString strDicomFileName)
	: CEndoxResizableDlg(CImageDicomDlg::IDD, pParent)
{
	m_sDicomFileName = strDicomFileName;
	m_iDicomViewerID = -1;
}

CImageDicomDlg::~CImageDicomDlg()
{
}

BEGIN_MESSAGE_MAP(CImageDicomDlg, CEndoxResizableDlg)

	// ON_MESSAGE(EPM_RCLICK, OnRClick) // serve eventualmente per la selezione //

	ON_WM_DESTROY()
	ON_WM_SIZE()

END_MESSAGE_MAP()

void CImageDicomDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_FRAME, m_ctrlStaticFrame);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

BOOL CImageDicomDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_FRAME, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	theApp.LocalizeDialog(this, CImageDicomDlg::IDD, "ImageDicomDlg");

	if (AmdcmViewer_Initialize(&m_iDicomViewerID, m_ctrlStaticFrame.GetSafeHwnd(), m_sDicomFileName.GetBuffer(), EPM_RCLICK, FALSE))
	{
		AmdcmViewer_Repos(m_iDicomViewerID);
		m_ctrlStaticFrame.SetFocus();
	}

	return FALSE;
}

void CImageDicomDlg::OnDestroy()
{
	AmdcmViewer_Finalize(m_iDicomViewerID);
	m_iDicomViewerID = -1;

	CEndoxResizableDlg::OnDestroy();
}

void CImageDicomDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	AmdcmViewer_Repos(m_iDicomViewerID);
}