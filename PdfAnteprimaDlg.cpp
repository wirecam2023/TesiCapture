#include "stdafx.h"
#include "Endox.h"
#include "PdfAnteprimaDlg.h"

#include "DLL_Imaging\h\AmSumatraPdfViewer.h"

#include "EsamiView.h"
#include "FileBmp.h"
#include "LogFileWriter.h"

IMPLEMENT_DYNAMIC(CPdfAnteprimaDlg, CEndoxResizableDlg)

long CPdfAnteprimaDlg::m_lDefaultZoomValue = 100;

CPdfAnteprimaDlg::CPdfAnteprimaDlg(CWnd* pParent, CEsamiView* pEsamiView, CString sPdfFile, long lModalita)
	: CEndoxResizableDlg(CPdfAnteprimaDlg::IDD, pParent)
{
	ASSERT((lModalita == ANTEPRIMADLG_SEMPLICE) || (lModalita == ANTEPRIMADLG_CHIUSURA) || (lModalita == ANTEPRIMADLG_FIRMA) || (lModalita == ANTEPRIMADLG_NO_STAMPA));

	m_pEsamiView = pEsamiView;
	m_sPdfFile = sPdfFile;
	m_lModalita = lModalita;

	m_uiTemp = 0;
}

CPdfAnteprimaDlg::~CPdfAnteprimaDlg()
{
}

BEGIN_MESSAGE_MAP(CPdfAnteprimaDlg, CEndoxResizableDlg)
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BTN_PRINT, OnBnClickedBtnPrint)
	ON_BN_CLICKED(IDC_BTN_FIRMA, OnBnClickedBtnFirma)
	ON_BN_CLICKED(IDC_BTN_PREV, OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_ZOOMIN, OnBnClickedBtnZoomIn)
	ON_BN_CLICKED(IDC_BTN_ZOOMOUT, OnBnClickedBtnZoomOut)
	ON_BN_CLICKED(IDC_BTN_IMMAGINI, OnBnClickedBtnImmagini)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)
END_MESSAGE_MAP()

void CPdfAnteprimaDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_PRINT, m_ctrlBtnPrint);
	DDX_Control(pDX, IDC_BTN_FIRMA, m_ctrlBtnFirma);
	DDX_Control(pDX, IDC_CHK_STAMPA, m_ctrlChkStampa);
	DDX_Control(pDX, IDC_BTN_PREV, m_ctrlBtnPrev);
	DDX_Control(pDX, IDC_BTN_NEXT, m_ctrlBtnNext);
	DDX_Control(pDX, IDC_BTN_ZOOMIN, m_ctrlBtnZoomIn);
	DDX_Control(pDX, IDC_BTN_ZOOMOUT, m_ctrlBtnZoomOut);
	DDX_Control(pDX, IDC_BTN_IMMAGINI, m_ctrlBtnImmagini);
	DDX_Control(pDX, IDC_BTN_EXIT, m_ctrlBtnExit);
}

BOOL CPdfAnteprimaDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	BeginWaitCursor();

	AddAnchor(IDC_PDF_PLACE, CSize(0, 0), CSize(100, 100));

	if (m_lModalita == ANTEPRIMADLG_NO_STAMPA)
	{
		m_ctrlBtnPrint.ShowWindow(SW_HIDE);
		m_ctrlBtnFirma.ShowWindow(SW_HIDE);
		m_ctrlChkStampa.ShowWindow(SW_HIDE);
	}
	else
	{
		m_ctrlBtnPrint.ShowWindow(m_lModalita == ANTEPRIMADLG_FIRMA ? SW_HIDE : SW_SHOW);
		m_ctrlBtnFirma.ShowWindow(m_lModalita == ANTEPRIMADLG_FIRMA ? SW_SHOW : SW_HIDE);
		m_ctrlChkStampa.ShowWindow(m_lModalita == ANTEPRIMADLG_FIRMA ? SW_SHOW : SW_HIDE);
		m_ctrlChkStampa.SetCheck(theApp.m_lFirmaDigitaleStampa == 1 ? BST_CHECKED : BST_UNCHECKED);
	}

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	m_uiTemp = PdfViewer_Initialize(GetDlgItem(IDC_PDF_PLACE)->GetSafeHwnd());
	PdfViewer_Load(m_uiTemp, m_sPdfFile);
	PdfViewer_SetCurrentZoom(m_uiTemp, m_lDefaultZoomValue);

	m_ctrlBtnPrev.EnableWindow(FALSE);
	m_ctrlBtnNext.EnableWindow(PdfViewer_GetNumberOfPages(m_uiTemp) > 1);

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiTemp) + 1, PdfViewer_GetNumberOfPages(m_uiTemp));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiTemp));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);

	if (theApp.m_bPersonalizzazioniBrasileSirio && (m_pEsamiView != NULL))
		m_ctrlBtnImmagini.ShowWindow(SW_SHOW);

	EndWaitCursor();

	theApp.LocalizeDialog(this, CPdfAnteprimaDlg::IDD, "PdfAnteprimaDlg");
	
	if (m_lModalita == ANTEPRIMADLG_CHIUSURA)
		GetDlgItem(IDC_BTN_PRINT)->SetWindowText(theApp.GetMessageString(IDS_CHIUSURA));

	return TRUE;
}

void CPdfAnteprimaDlg::OnDestroy()
{
	m_lDefaultZoomValue = PdfViewer_GetCurrentZoom(m_uiTemp);
	PdfViewer_Close(m_uiTemp);
	PdfViewer_Finalize(m_uiTemp);

	CEndoxResizableDlg::OnDestroy();
}

void CPdfAnteprimaDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	PdfViewer_Resize(m_uiTemp);
}

void CPdfAnteprimaDlg::OnBnClickedBtnPrint()
{
	EndDialog(IDOK);
}

void CPdfAnteprimaDlg::OnBnClickedBtnFirma()
{
	CLogFileWriter::Get()->WriteLogLine0("Firma000");

	UpdateData(TRUE);

	CLogFileWriter::Get()->WriteLogLine0("Firma001");

	if (m_ctrlChkStampa.GetCheck() == BST_CHECKED)
	{
		CLogFileWriter::Get()->WriteLogLine0("Firma002");

		EndDialog(0x777); // firma e stampa //
	}
	else
	{
		CLogFileWriter::Get()->WriteLogLine0("Firma003");

		EndDialog(0x555); // solo firma senza stampa //
	}
}

void CPdfAnteprimaDlg::OnBnClickedBtnPrev()
{
	BeginWaitCursor();

	PdfViewer_GoToPreviousPage(m_uiTemp);

	CRect rectTemp;
	GetDlgItem(IDC_PDF_PLACE)->GetWindowRect(rectTemp);
	ScreenToClient(rectTemp);
	InvalidateRect(rectTemp, FALSE);

	m_ctrlBtnPrev.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) > 0);
	m_ctrlBtnNext.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) + 1 < PdfViewer_GetNumberOfPages(m_uiTemp));

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiTemp) + 1, PdfViewer_GetNumberOfPages(m_uiTemp));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);

	EndWaitCursor();
}

void CPdfAnteprimaDlg::OnBnClickedBtnNext()
{
	BeginWaitCursor();

	PdfViewer_GoToNextPage(m_uiTemp);

	CRect rectTemp;
	GetDlgItem(IDC_PDF_PLACE)->GetWindowRect(rectTemp);
	ScreenToClient(rectTemp);
	InvalidateRect(rectTemp, FALSE);

	m_ctrlBtnPrev.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) > 0);
	m_ctrlBtnNext.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) + 1 < PdfViewer_GetNumberOfPages(m_uiTemp));

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiTemp) + 1, PdfViewer_GetNumberOfPages(m_uiTemp));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);

	EndWaitCursor();
}

void CPdfAnteprimaDlg::OnBnClickedBtnZoomIn()
{
	BeginWaitCursor();

	PdfViewer_ZoomIn(m_uiTemp);

	m_ctrlBtnZoomIn.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomOut.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) > PdfViewer_GetMinZoom());

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiTemp));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);

	EndWaitCursor();
}

void CPdfAnteprimaDlg::OnBnClickedBtnZoomOut()
{
	BeginWaitCursor();

	PdfViewer_ZoomOut(m_uiTemp);

	m_ctrlBtnZoomIn.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomOut.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) > PdfViewer_GetMinZoom());

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiTemp));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);

	EndWaitCursor();
}

void CPdfAnteprimaDlg::OnBnClickedBtnImmagini()
{
	if (m_pEsamiView != NULL)
		m_pEsamiView->AnteprimaStampaImmagini(ANTEPRIMA, LOCAL_IMAGES, 1);
}

void CPdfAnteprimaDlg::OnBnClickedBtnExit()
{
	EndDialog(IDCANCEL);
}