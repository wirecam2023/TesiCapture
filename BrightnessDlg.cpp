#include "stdafx.h"
#include "Endox.h"
#include "BrightnessDlg.h"

#include "Common.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBrightnessDlg::CBrightnessDlg(CWnd* pParent, CDib** pDib, CDib** pDibUndo)
	: CDialog(CBrightnessDlg::IDD, pParent)
{
	m_pView		= pParent;
	m_pDib		= pDib;
	m_pDibUndo	= pDibUndo;
	m_pDibReal  = NULL;
	m_pOldPal	= NULL;
	m_pLogPal	= NULL;

	m_nBrightnessLev = g_nBrightnessLev;
}

CBrightnessDlg::~CBrightnessDlg()
{	
	if (m_pDibReal)
	{
		m_pDibReal->ReleaseContents();
		delete m_pDibReal;
		m_pDibReal = NULL;
	}

	if (m_pLogPal)
	{
		GlobalFreePtr(m_pLogPal);
		m_pLogPal = NULL;
	}
	
	if (m_pOldPal)
	{
		GlobalFreePtr(m_pOldPal);
		m_pOldPal = NULL;
	}
}

void CBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRIGHT, m_ctrlBright);
	DDX_Control(pDX, IDC_STATIC_LUM, m_ctrlStaticLabel);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
}


BEGIN_MESSAGE_MAP(CBrightnessDlg, CDialog)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CBrightnessDlg::OnOK() 
{
	if (m_pOldPal)
		(*m_pDib)->CopydaPalette(m_pOldPal);

	if (m_pDibReal)
		**m_pDib = *m_pDibReal;

	BeginWaitCursor();
	ScambiaDib(m_pDib, m_pDibUndo);
	if ((*m_pDib)->IsRGB())
		DoBrightnessRGB(m_nBrightnessLev, *m_pDibUndo, *m_pDib, NULL); 
	else
		DoBrightness(m_nBrightnessLev, *m_pDibUndo, *m_pDib, NULL); 
	EndWaitCursor();

	UpdateData(TRUE);
	
	g_nBrightnessLev = m_nBrightnessLev;

	CDialog::OnOK();
}

void CBrightnessDlg::OnCancel() 
{
	if (m_pOldPal)
		(*m_pDib)->CopydaPalette(m_pOldPal);

	if (m_pDibReal)
		**m_pDib = *m_pDibReal;

    m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
	
	CDialog::OnCancel();
}

BOOL CBrightnessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ((*m_pDib)->IsRGB())
	{
		m_pDibReal = new CDib;

		if (m_pDibReal)
			*m_pDibReal = **m_pDib;
	}
	else
	{
		m_pLogPal = (*m_pDib)->CreateLogPalette();
		m_pOldPal = (*m_pDib)->CreateLogPalette();
	}

	m_ctrlBright.SetScrollRange (-255, 255);
	m_ctrlBright.SetScrollPos (m_nBrightnessLev);

	SetDlgItemInt(IDC_NUM_BRIGHT, m_nBrightnessLev,	(m_nBrightnessLev < 0));

	if ((*m_pDib)->IsRGB())
		DoBrightnessRGB(m_nBrightnessLev, m_pDibReal, *m_pDib, NULL);
	else
		BrightnessPreview(m_nBrightnessLev, *m_pDib, m_pOldPal, m_pLogPal);

	m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE); 

	theApp.LocalizeDialog(this, CBrightnessDlg::IDD, "BrightnessDlg");

	return TRUE;
}

void CBrightnessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

    ////MOVIMENTO EFFETTIVO
	int Min, Max, OldPos, NewPos;

	pScrollBar->GetScrollRange(&Min, &Max);
    OldPos = pScrollBar->GetScrollPos();

	switch(nSBCode)
	{
		case SB_LEFT :
			NewPos = max(Min, OldPos - 1);
			break;

		case SB_RIGHT :
			NewPos = min(Max, OldPos + 1);
			break;

		case SB_LINELEFT :
			NewPos = max(Min, OldPos - 1);
			break;

		case SB_LINERIGHT :
			NewPos = min(Max, OldPos + 1);
			break;

		case SB_PAGELEFT :
			NewPos = max(Min, OldPos - 10);
			break;

		case SB_PAGERIGHT :
			NewPos = min(Max, OldPos + 10);
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			//if ((int)nPos <= Max && (int)nPos >= Min)
				NewPos = nPos;
			break;
		
		default:
			NewPos = OldPos;
	}
	
	if (pScrollBar == &m_ctrlBright)
	{
		m_nBrightnessLev = NewPos;
                                  
		pScrollBar->SetScrollPos(m_nBrightnessLev);
		SetDlgItemInt(IDC_NUM_BRIGHT, m_nBrightnessLev,	(m_nBrightnessLev < 0));

		if (nSBCode == SB_ENDSCROLL)
		{
			if ((*m_pDib)->IsRGB())
				DoBrightnessRGB(m_nBrightnessLev, m_pDibReal, *m_pDib, NULL);
			else
				BrightnessPreview(m_nBrightnessLev, *m_pDib, m_pOldPal, m_pLogPal);
	
			m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE); 
		}
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}