#include "stdafx.h"
#include "Endox.h"
#include "PdfStampaDlg.h"

#include "DLL_Imaging\h\AmRes.h"
#include "DLL_Imaging\h\AmSumatraPdfViewer.h"

#include "Common.h"
#include "DigitalSignUtil.h"
#include "EsamiView.h"
#include "NumeroCopieStampaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPdfStampaDlg, CDialog)

CPdfStampaDlg::CPdfStampaDlg(CWnd* pParent, CString sRptFile, CString sPdfFile, BOOL bCrypted, long lPrinterToUse, long lCopies, BOOL bFitToPage)
	: CDialog(CPdfStampaDlg::IDD, pParent)
{
	m_sRptFile = sRptFile;
	m_sPdfFile = sPdfFile;
	m_bCrypted = bCrypted;
	m_lPrinterToUse = lPrinterToUse;
	m_lCopies = lCopies;
	m_bFitToPage = bFitToPage;

	m_pBufferPdf = NULL;

	m_uiTemp = 0;
}

CPdfStampaDlg::~CPdfStampaDlg()
{
}

void CPdfStampaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ANIM, m_ctrlAnim);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_ctrlStatic);
}

BEGIN_MESSAGE_MAP(CPdfStampaDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CPdfStampaDlg::OnCancel()
{
}

BOOL CPdfStampaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (HMODULE hModule = ::LoadLibrary("Amres.dll"))
	{
		HINSTANCE hInstance = AfxGetResourceHandle();
		AfxSetResourceHandle(hModule);
		m_ctrlAnim.Open(Amres_waiting);
		m_ctrlAnim.Play(0, -1, -1);
		AfxSetResourceHandle(hInstance);
	}

	m_ctrlStatic.SetFont(&theApp.m_fontBig);

	m_uiTemp = PdfViewer_Initialize(GetDlgItem(IDC_PDF_PLACE)->GetSafeHwnd());

	if (m_bCrypted)
	{
		DWORD dwBufferSize = 0;
		if (CDigitalSignUtil::DecryptPdf(m_sPdfFile, &m_pBufferPdf, &dwBufferSize))
			PdfViewer_LoadFromBuffer(m_uiTemp, m_pBufferPdf, dwBufferSize);
	}
	else
	{
		PdfViewer_Load(m_uiTemp, m_sPdfFile);
	}

	PdfViewer_SetMinZoom(m_uiTemp);

	SetTimer(12345, 500, NULL);

	theApp.LocalizeDialog(this, CPdfStampaDlg::IDD, "PdfStampaDlg");
	return TRUE;
}

HBRUSH CPdfStampaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TEXT:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			break;
		}
	}

	return hReturn;
}

void CPdfStampaDlg::OnOK()
{
}

void CPdfStampaDlg::OnDestroy()
{
	PdfViewer_Close(m_uiTemp);
	PdfViewer_Finalize(m_uiTemp);

	if (m_pBufferPdf)
		delete m_pBufferPdf;
	m_pBufferPdf = NULL;

	CDialog::OnDestroy();
}

void CPdfStampaDlg::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);

	BOOL bReturn = FALSE;
	
	// prendo il messaggio per la stampa //
	CString strPrintingMessage = theApp.GetAppTitle(2);

	// se necessario carico la stampante su cui lanciare la stampa //
	HGLOBAL hDevNames = NULL;
	HGLOBAL hDevMode = NULL;
	if (theApp.m_bLoadPrinterSettings)
		LoadPrinterSettingsFromNumber(m_lPrinterToUse, &hDevNames, &hDevMode);

	// Sandro 23/04/2014 //
	BOOL bContinue = TRUE;
	if ((m_lCopies == 0) && (hDevNames != NULL) && (hDevMode != NULL))
	{
		CNumeroCopieStampaDlg dlgTemp(this, m_sRptFile);

		if (dlgTemp.DoModal() == IDOK)
			m_lCopies = dlgTemp.GetNumeroCopie();
		else
			bContinue = FALSE;
	}

	if (bContinue)
	{
		bReturn = PdfViewer_Print(m_uiTemp, strPrintingMessage.GetBuffer(), hDevNames, hDevMode, m_lCopies, m_bFitToPage);
		strPrintingMessage.ReleaseBuffer();
	}

	CDialog::OnTimer(nIDEvent);

	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	EndDialog(bReturn ? IDOK : IDCANCEL);
}