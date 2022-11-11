#include "stdafx.h"
#include "Endox.h"
#include "ReportDlg.h"

#include <io.h>

#include "Common.h"
#include "DrawTool.h"
#include "Esamiview.h"
#include "FieldDlg.h"
#include "HeaderFooterSet.h"
#include "RectPreviewObj.h"
#include "ReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CReportDlg::CReportDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CResizableDialog(CReportDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;

	m_nFormato	    = FORMATO_REPORT_A4;
	m_bCopiaPDF		= FALSE;
	m_bFitToPage	= FALSE;
	m_nTipoReport   = TIPO_REPORT_NORMALE;
	m_nOrientamento = ORIENT_REPORT_VERT;
	
	// Formati Orientamento Verticale
	m_szFoglioA4 = CSize(210, 297);
	m_szFoglioLegal = CSize(216, 355);
	m_szFoglioLetter = CSize(216, 279);
	m_szFoglioExclusive = CSize(184, 266);
	
	m_szPage = m_szFoglioA4;
	m_rectPage = CRect(0, 0, 0, 0);
	
	m_hCursorAdd  	= AfxGetApp()->LoadCursor(IDC_ADD);
    m_hCursorArrow 	= AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	m_bTipoChanged   = FALSE;
	m_bCambiaAltezza = FALSE;

	m_nAltezzaRiga = 10;

	m_bReportSearch = FALSE;
	m_nMode = REPORT_NOTHING;

	m_lIDStampante = 0;
	m_lIDHeader1 = 0;
	m_lIDHeader2 = 0;
	m_lIDFooter1 = 0;
	m_lIDFooter2 = 0;
	m_nDimHeader = 0;
	m_nDimFooter = 0;
}

CReportDlg::~CReportDlg()
{
	POSITION pos;
		
	pos = m_objects.GetHeadPosition();
	while (pos != NULL)
		delete m_objects.GetNext(pos);

	m_selection.RemoveAll();
}

void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_9, m_ctrlStatic9);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic14);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);

	DDX_Control(pDX, IDC_CONTROLLO_1, m_ctrlButtonCtrl1);
	DDX_Control(pDX, IDC_CONTROLLO_2, m_ctrlButtonCtrl2);
	DDX_Control(pDX, IDC_CONTROLLO_3, m_ctrlButtonCtrl3);
	DDX_Control(pDX, IDC_CONTROLLO_4, m_ctrlButtonCtrl4);
	DDX_Control(pDX, IDC_CONTROLLO_5, m_ctrlButtonCtrl5);
	DDX_Control(pDX, IDC_CONTROLLO_6, m_ctrlButtonCtrl6);
	DDX_Control(pDX, IDC_CONTROLLO_7, m_ctrlButtonCtrl7);
	DDX_Control(pDX, IDC_CONTROLLO_10, m_ctrlButtonCtrl10);
	DDX_Control(pDX, IDC_CONTROLLO_11, m_ctrlButtonCtrl11);
	DDX_Control(pDX, IDC_DELETE, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_LOAD, m_ctrlButtonLoad);
	DDX_Control(pDX, IDC_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_SAVE_AS, m_ctrlButtonSaveAs);
	DDX_Control(pDX, IDC_PREVIEW, m_ctrlButtonPreview);
	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlButtonChiudi);

	DDX_Control (pDX, IDC_SPIN_HEIGHT, m_ctrlSpin);
	DDX_Control (pDX, IDC_PAGE, m_ctrPage);
	DDX_CBIndex (pDX, IDC_COMBO_DIMENSIONE, m_nFormato);
	DDX_Radio   (pDX, IDC_TIPO1, m_nTipoReport);
	DDX_Check	(pDX, IDC_COPIAPDF, m_bCopiaPDF);
	DDX_Check	(pDX, IDC_FIT_TO_PAGE, m_bFitToPage);
	DDX_Text    (pDX, IDC_EDT_HEIGHT, m_nAltezzaRiga);
	DDX_Radio   (pDX, IDC_ORIENTAMENTO1, m_nOrientamento);
	DDX_Radio   (pDX, IDC_CONTROLLO_1, m_nMode);

	DDX_Control(pDX, IDC_COMBO_STAMPANTE, m_ctrlComboStampante);
	DDX_Control(pDX, IDC_COMBO_HEADER1, m_ctrlComboHeader1);
	DDX_Control(pDX, IDC_COMBO_HEADER2, m_ctrlComboHeader2);
	DDX_Control(pDX, IDC_COMBO_FOOTER1, m_ctrlComboFooter1);
	DDX_Control(pDX, IDC_COMBO_FOOTER2, m_ctrlComboFooter2);
}

BEGIN_MESSAGE_MAP(CReportDlg, CResizableDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_BN_CLICKED(IDC_NEW,		    OnNew)
	ON_BN_CLICKED(IDC_LOAD,		    OnLoad)
	ON_BN_CLICKED(IDC_SAVE,			OnSave)
	ON_BN_CLICKED(IDC_SAVE_AS,	    OnSaveAs)
	ON_BN_CLICKED(IDC_PREVIEW,		OnBnClickedPreview) // DA CANCELLARE //
	ON_BN_CLICKED(IDC_BTN_CHIUDI,	OnBtnChiudi)

	ON_CBN_SELCHANGE(IDC_COMBO_DIMENSIONE, OnCambiaPagina)
	ON_BN_CLICKED(IDC_ORIENTAMENTO1, OnCambiaPagina)
	ON_BN_CLICKED(IDC_ORIENTAMENTO2, OnCambiaPagina)

	ON_BN_CLICKED(IDC_TIPO1,	     OnCambiaTipoReport)
	ON_BN_CLICKED(IDC_TIPO2,	     OnCambiaTipoReport)
	
	ON_BN_CLICKED(IDC_COPIAPDF,	     OnCambiaImpostazioni)
	ON_BN_CLICKED(IDC_FIT_TO_PAGE,	 OnCambiaImpostazioni)

	ON_BN_CLICKED(IDC_CONTROLLO_1,   OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_2,   OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_3,   OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_4,   OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_5,   OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_6,   OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_7,   OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_10,  OnCambiaControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_11,  OnCambiaControllo)
	ON_BN_CLICKED(IDC_DELETE,	     OnDelete)

	ON_CBN_SELCHANGE(IDC_COMBO_STAMPANTE, OnCbnSelchangeComboStampante)
	ON_CBN_SELCHANGE(IDC_COMBO_HEADER1, OnCbnSelchangeComboHeader1)
	ON_CBN_SELCHANGE(IDC_COMBO_HEADER2, OnCbnSelchangeComboHeader2)
	ON_CBN_SELCHANGE(IDC_COMBO_FOOTER1, OnCbnSelchangeComboFooter1)
	ON_CBN_SELCHANGE(IDC_COMBO_FOOTER2, OnCbnSelchangeComboFooter2)
	ON_EN_CHANGE(IDC_EDT_HEIGHT, &CReportDlg::OnEnChangeEdtHeight)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CReportDlg::OnCambiaControllo()
{
	UpdateData(TRUE);
	SetFocus();
}

void CReportDlg::Add(CDrawTool* pObj)
{
	m_objects.AddTail(pObj);

	pObj->m_bIsEnable = TRUE;

	Select(pObj, FALSE);
}

void CReportDlg::Remove(CDrawTool* pObj)
{
	// Find and remove from document
	POSITION pos = m_objects.Find(pObj);
	if (pos != NULL)
		m_objects.RemoveAt(pos);

	pos = m_selection.Find(pObj);
	if (pos != NULL)
		m_selection.RemoveAt(pos);

	delete pObj;
}

// point is in logical coordinates
CDrawTool* CReportDlg::ObjectAt(const CPoint& point)
{
	CRect rect(point, CSize(1, 1));

	POSITION pos = m_objects.GetTailPosition();
	
	while (pos != NULL)
	{
		CDrawTool* pObj = m_objects.GetPrev(pos);
		if (pObj->Intersects(rect))
			return pObj;
	}

	return NULL;
}

BOOL CReportDlg::IsSelected(CDrawTool* pObj)
{
	if (m_selection.Find(pObj))
		return TRUE;
	
	return FALSE;
}

void CReportDlg::Select(CDrawTool* pObj, BOOL bAdd)
{
	if (!bAdd)
	{
		m_selection.RemoveAll();
		Invalidate();
	}

	if (pObj == NULL || IsSelected(pObj))
		return;

	m_selection.AddTail(pObj);
	pObj->Invalidate(this);
}

// rect is in device coordinates
void CReportDlg::SelectWithinRect(CRect rect, BOOL bAdd)
{
	if (!bAdd)
		Select(NULL);

	POSITION posObj = m_objects.GetHeadPosition();

	while (posObj != NULL)
	{
		CRect		rc	 = rect;
		CDrawTool*	pObj = m_objects.GetNext(posObj);

		pObj->ClientToDoc(this, rc);
		
		if (pObj->Intersects(rc))
			Select(pObj, TRUE);
	}
}

void CReportDlg::Deselect(CDrawTool* pObj)
{
	POSITION pos = m_selection.Find(pObj);
	
	if (pos != NULL)
	{
		pObj->Invalidate(this);
		m_selection.RemoveAt(pos);
	}
}

CDrawTool* CReportDlg::GetSelect()
{
	CDrawTool* pObj = NULL;

	POSITION posObj = m_selection.GetHeadPosition();

	if (posObj != NULL)
		pObj = m_selection.GetNext(posObj);

	return pObj;
}

BOOL CReportDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	ASSERT(cs.lpszClass == NULL);
	
	cs.lpszClass = AfxRegisterWndClass( CS_DBLCLKS,
										NULL, 
										NULL,	
										NULL);
	return TRUE;
	
	//return CWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CReportDlg message handlers

void CReportDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush page(HS_CROSS, RGB(220,220,220));
	dc.SetBkColor(RGB(255, 255, 255));
	dc.FillRect(m_rectPage, &page);
	page.DeleteObject();

	int nImm = 1;

	if (m_lIDHeader1 > 0)
	{
		CRect rectHeader;
		rectHeader.left   = 0;
		rectHeader.top    = 0;
		rectHeader.right  = m_rectPage.Width();
		rectHeader.bottom = rectHeader.top + (int)((double)m_rectPage.Height() * ((double)m_nDimHeader / (double)m_szPage.cy));
		
		rectHeader.OffsetRect(m_rectPage.left, m_rectPage.top);
		
		CBrush header(HS_DIAGCROSS, RGB(127,127,127));
		dc.SetBkColor(RGB(255, 255, 255));
		
		if (m_nTipoReport == TIPO_REPORT_NORMALE)
			dc.FillRect(rectHeader, &header);
		
		header.DeleteObject();
	}

	if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
	{
        CRect rectFooter;

        rectFooter.left   = 0;
        rectFooter.right  = (int)m_rectPage.Width();
        rectFooter.top    = (int)((double)m_rectPage.Height() * ((double)(m_szPage.cy - m_nDimFooter) / (double)m_szPage.cy));
        rectFooter.bottom = (int)m_rectPage.Height();
        rectFooter.OffsetRect(m_rectPage.left, m_rectPage.top);

        CBrush footer(HS_DIAGCROSS, RGB(127,127,127));
        dc.SetBkColor(RGB(255, 255, 255));

		if (m_nTipoReport == TIPO_REPORT_NORMALE)
			dc.FillRect(rectFooter, &footer);
        
		footer.DeleteObject();
    }

	POSITION pos = m_objects.GetHeadPosition();
	
	while (pos != NULL)
	{
		TrackerState	nTrack	 = normal;
		CDrawTool*		pObj 	 = m_objects.GetNext(pos);
		CString			strTitle = "";
		int				nAlignment = 0;
		int				nRotation = 0;

		if (pObj->m_strType == "Field" || pObj->m_strType == "Label")
		{
			CString strField  = "...";

			for(int i = 0; i < endox_report_field_num_total; i++)
			{
				if (CFieldDlg::m_strFieldEndox[i].sReport == pObj->m_strValue)
				{
					int iContenuto = -1;
					if (CFieldDlg::m_strFieldEndox[i].lID >= 0)
					{
						for(int j = 0; j < form_list_total; j++)
						{
							if (g_FormCaract[j].lID == CFieldDlg::m_strFieldEndox[i].lID)
							{
								iContenuto = j;
								break;
							}
						}
					}

					strField = CFieldDlg::m_strFieldEndox[i].sCombo + GetStringCampoLiberoDatabase(iContenuto);
					
					break;
				}
			}
			
			strTitle = "(" + pObj->m_strType.Left(1) + ")" + strField;
			nAlignment = pObj->m_nAlignment;
			nRotation = pObj->m_nRotation;
		}
		else
		{
			if (pObj->m_strType == "Form")
			{
				if (pObj->m_strValue == "Terapie")
					strTitle = theApp.GetMessageString(IDS_FIELDDLG_FORM_1); // Terapie //
				else if (pObj->m_strValue == "Osservazioni")
					strTitle = theApp.GetMessageString(IDS_FIELDDLG_FORM_2); // Osservazioni //
				else if (pObj->m_strValue == "Patologia")
					strTitle = theApp.GetMessageString(IDS_FIELDDLG_FORM_3); // Patologia //
				else if (pObj->m_strValue == "Diagnosi")
					strTitle = theApp.GetMessageString(IDS_FIELDDLG_FORM_4); // Diagnosi //
				else if (pObj->m_strValue == "Codifica regionale")
					strTitle = theApp.GetMessageString(IDS_FIELDDLG_FORM_5); // Codifica regionale //
				else if (pObj->m_strValue == "Monitoraggio")
					strTitle = theApp.GetMessageString(IDS_FIELDDLG_FORM_6); // Monitoraggio del paziente //
				else
					strTitle = "";
			}
			else if (pObj->m_strType == "Image")
			{
				strTitle.Format("%s %d", theApp.GetMessageString(IDS_IMMAGINE), nImm);
				nAlignment = pObj->m_nAlignment;
				nRotation = pObj->m_nRotation;
				nImm++;
			}
			else if (pObj->m_strType == "Organ")
			{
				strTitle = theApp.GetMessageString(IDS_ORGANO);
				nAlignment = pObj->m_nAlignment;
				nRotation = pObj->m_nRotation;
			}
			else
			{
				strTitle = pObj->m_strValue;
				nAlignment = pObj->m_nAlignment;
				nRotation = pObj->m_nRotation;
			}
		}
		
		if (IsSelected(pObj))
			nTrack = selected;

		LOGFONT lfObj = pObj->m_lfFont;
		pObj->Draw(&dc, strTitle, nAlignment, nRotation, nTrack, &lfObj);
	}
}

void CReportDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (m_nMode == REPORT_NOTHING)
	{
		CDrawTool* pObj = ObjectAt(point);
					
		if ((pObj) && (pObj != GetSelect()))
			Select(pObj, FALSE);

		if (pObj)
		{
			CFieldDlg dlg(this, m_rectPage, pObj, CPoint(0, 0));

			if (dlg.DoModal() == IDOK)
				pObj->Invalidate(this);
		}
	}
	
	CResizableDialog::OnRButtonDown(nFlags, point);
}

void CReportDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDrawTool*	pObj	= NULL;
	CDrawTool*	pSelObj = NULL;
	BOOL		bAddObj = FALSE;
	CSize		szMin(  5,   2);
	CSize		szMax(420, 420);
	CSize		szNor( 10,   4);
	CString		strValue;
	CString		strType;
	int			nParam;
	int			nAlignment = 0;
	int			nRotation = 0;

	switch (m_nMode)
	{
		case REPORT_NOTHING:
		{
			pObj = GetSelect();
			
			if (pObj)
			{
				CPoint pt = point;

				pObj->ClientToDoc(this, m_rectPage, pt, FALSE);
				
				if (pObj->m_pObj->HitTest(pt, this) || pObj->m_pObj->ObjTest(pt))
					pSelObj = pObj;
			}

			if (!pSelObj)
			{
				pObj = ObjectAt(point);
				
				if (pObj && pObj != GetSelect())
				{
					Select(pObj, FALSE);
				}
		
				pSelObj = GetSelect();
			}

			if (pSelObj)
			{
				SetCapture();
				
				if (pSelObj->m_bIsEnable)
					pSelObj->OnLButtonDown(this, m_rectPage, nFlags, point);
			}

			break;
		}
		case REPORT_FIELD:
		{
			bAddObj	 = TRUE;
			strValue = "Anagrafico.A";
			strType  = "Field";
			nParam	 = 0;
			nAlignment = 0;
			nRotation = 0;

			break;
		}
		case REPORT_LABEL:
		{
			bAddObj	 = TRUE;
			strValue = "Anagrafico.A";
			strType  = "Label";
			nParam	 = 0;
			nAlignment = 0;
			nRotation = 0;

			break;
		}
		case REPORT_PARAM:
		{
			bAddObj	 = TRUE;
			strValue = "szData";
			strType  = "Param";
			nParam	 = 0;
			nAlignment = 0;
			nRotation = 0;

			break;
		}
		case REPORT_TEXT:
		{
			bAddObj	 = TRUE;
			strValue = "Testo generico";
			strType  = "Text";
			nParam	 = 0;
			nAlignment = 0;
			nRotation = 0;

			break;
		}
		case REPORT_IMAGE:
		{
			bAddObj	 = TRUE;
			strValue = "Immagine";
			strType  = "Image";
			nParam	 = 0;
			nAlignment = 0;
			nRotation = 0;

			szMin = CSize( 10,  10);
			szMax = CSize(420, 420);
			szNor = CSize(64,  48);

			break;
		}
		case REPORT_BMP:
		{
			bAddObj	 = TRUE;
			strValue = "C:\\BITMAP.BMP";
			strType  = "Icon";
			nParam	 = 0;
			nAlignment = 0;
			nRotation = 0;

			szMin = CSize( 10,  10);
			szMax = CSize(420, 420);
			szNor = CSize( 30,  30);

			break;
		}
		case REPORT_LINE:
		{
			bAddObj	 = TRUE;
			strValue = "";
			strType  = "Line";
			nParam	 = 1;
			nAlignment = 0;
			nRotation = 0;

			szMin = CSize(1,   1);
			szMax = CSize(420, 420);
			szNor = CSize(20,  2);

			break;			
		}
		case REPORT_ORGAN:
		{
			bAddObj	 = TRUE;
			strValue = "Organo";
			strType  = "Organ";
			nParam	 = 0;
			nAlignment = 0;
			nRotation = 0;

			szMin = CSize( 10,  10);
			szMax = CSize(420, 420);
			szNor = CSize(56,  60);

			break;
		}
	}

	if (bAddObj)
	{
		CRect rectPage  = m_rectPage;
		CSize szInPixel = szNor;

		szInPixel.cx = (int)((double)m_rectPage.Width () * (double)szNor.cx / (double)m_szPage.cx);
		szInPixel.cy = (int)((double)m_rectPage.Height() * (double)szNor.cy / (double)m_szPage.cy);

		rectPage.DeflateRect(szInPixel.cx / 2, szInPixel.cy / 2);

		if (rectPage.PtInRect(point))
		{
			pObj = new CDrawTool;

			if (pObj)
			{
				CRealRect	PosObj;
				CRect		RectInMM;
				CPoint		ptInMM;
				CPoint		ptInPixel;

				ptInPixel.x = point.x - m_rectPage.left;
				ptInPixel.y = point.y - m_rectPage.top;

				ptInMM.x = (int)(((double)m_szPage.cx * (double)ptInPixel.x) / (double)m_rectPage.Width ());
				ptInMM.y = (int)(((double)m_szPage.cy * (double)ptInPixel.y) / (double)m_rectPage.Height());

				RectInMM.left   = ptInMM.x - szNor.cx/2;
				RectInMM.right  = ptInMM.x + szNor.cx/2;
				RectInMM.top    = ptInMM.y - szNor.cy/2;
				RectInMM.bottom = ptInMM.y + szNor.cy/2;

				PosObj.SetParam (m_rectPage, CRect(CPoint(0,0), m_szPage), 1);
				PosObj.SetPosRectMM(RectInMM);
			
				double dRap = ((double)m_szPage.cx / (double)m_rectPage.Width()) * (double)1.45;

				pObj->SetObj(&PosObj, 5, szMin, szMax, dRap);
				pObj->m_strValue	= strValue;
				pObj->m_nAlignment	= 0;
				pObj->m_nRotation	= 0;
				pObj->m_strType		= strType;
				pObj->m_bCheck		= TRUE;
				pObj->m_rgbColor	= RGB(0,0,0);
				pObj->m_nParam		= nParam;

				Add(pObj);

				RedrawWindow();
			}
			
			m_nMode = REPORT_NOTHING;
			UpdateData(FALSE);
		}
	}
	
	CResizableDialog::OnLButtonDown(nFlags, point);
}

void CReportDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDrawTool*	pObj = NULL;

	switch (m_nMode)
	{
		case REPORT_NOTHING:
			if (GetCapture() == this)
			{
				pObj = GetSelect();
				
				if (pObj)
				{
					if (pObj->m_bIsEnable)
						pObj->OnLButtonUp(this, m_rectPage, nFlags, point);
				}
			}
			break;
	}

	ReleaseCapture();
	
	CResizableDialog::OnLButtonUp(nFlags, point);
}

void CReportDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	BOOL bAddCursor = FALSE;
	CDrawTool* pObj = NULL;

	switch(m_nMode)
	{
		case REPORT_NOTHING:
		{	
			if (GetCapture() == this)
			{
				pObj = GetSelect();
				
				if (pObj != NULL)
				{
					CRect rectDraw = m_rectPage;

					if (pObj->m_bIsEnable)
						pObj->OnMouseMove(this, rectDraw, point);
				}
			}
			break;
		}
		default:
		{
			if (GetCapture() == NULL)
				bAddCursor = TRUE;

			break;
		}
	}

	if (bAddCursor && m_rectPage.PtInRect(point))
		SetCursor(m_hCursorAdd);
	else
		SetCursor(m_hCursorArrow);

	/*
	if (point.x > (m_rectPage.TopLeft()).x && point.x < (m_rectPage.BottomRight()).x &&
	   point.y > (m_rectPage.TopLeft()).y && point.y < (m_rectPage.BottomRight()).y)
	{
		CPoint pointMinus, pointInMM;
		int nCurrentHeight;

		pointMinus.x = point.x - (m_rectPage.TopLeft()).x;
		pointMinus.y = point.y - (m_rectPage.TopLeft()).y;
		
		if (m_nTipoReport == TIPO_REPORT_NORMALE)
			nCurrentHeight = GetCurrentHeight();
		else
			nCurrentHeight = m_szPage.cy;

		pointInMM.x = (int)(((float)pointMinus.x / (float)m_rectPage.Width()) * (float)GetCurrentWidth()) + 1;
		pointInMM.y = (int)(((float)pointMinus.y / (float)m_rectPage.Height()) * (float)nCurrentHeight) + 1;
	}
	*/

	UpdateData(FALSE);
	CResizableDialog::OnMouseMove(nFlags, point);
}

void CReportDlg::OnCancel()
{
}

BOOL CReportDlg::OnInitDialog() 
{
	CString strTmp;
	
	CResizableDialog::OnInitDialog();

	AddAnchor(IDC_STATIC_LINEV, CSize(100, 0), CSize(100, 100));
	AddAnchor(IDC_CONTROLLO_1, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_LINEH2, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_2, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_4, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_5, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_6, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_3, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_11, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_7, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_CONTROLLO_10, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_LINEH3, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_DELETE, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_LINEH4, CSize(100, 0), CSize(100, 0));

	AddAnchor(IDC_STATIC_LINEH5, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_NEW, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_LOAD, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_SAVE, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_SAVE_AS, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_STATIC_LINEH6, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_PREVIEW, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_STATIC_LINEH7, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_CHIUDI, CSize(100, 100), CSize(100, 100));

	// calcolo la differenza di pixels tra la larghezza del dialog e la larghezza del frame //
	CRect rectDialog;
	GetWindowRect(rectDialog);
	CRect rectFrame;
	m_ctrPage.GetWindowRect(rectFrame);
	nDiffDialogFrame = rectDialog.Width() - rectFrame.Width();
	nHeightDialog = rectDialog.Height();
	nHeightFrame = rectFrame.Height();

	// imposto i fonts //
	GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_4)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_5)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_6)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_12)->SetFont(&theApp.m_fontBold);
	
	m_ctrPage.GetWindowRect(&m_rectPage);
	ScreenToClient(&m_rectPage);

	RiempiCombo();

	m_ctrlSpin.SetRange(1, 100);
	m_ctrlSpin.SetBase(10);
	m_ctrlSpin.SetPos(20);
	NuovoReport();

	m_nTipoReport   = TIPO_REPORT_NORMALE;
	m_nOrientamento = ORIENT_REPORT_VERT;
	UpdateData(FALSE);

	RidimensionaPagina();

	theApp.LocalizeDialog(this, CReportDlg::IDD, "ReportDlg");

	return TRUE;
}

void CReportDlg::OnOK()
{
}

void CReportDlg::OnDelete() 
{
	CDrawTool*	pObj = GetSelect();

	if (pObj)
		Remove(pObj);

	RedrawWindow();
}

void CReportDlg::OnNew() 
{
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PREVIEW)->EnableWindow(FALSE);

	NuovoReport();

	m_bReportSearch = FALSE;
}

void CReportDlg::OnLoad() 
{
	//Estensione RPT report normali
	//           RPS report ricerca

	CString strFilter;
	CString strForm;

	if (m_nTipoReport == TIPO_REPORT_NORMALE)
		strFilter = "Report (*.rpt)|*.rpt|Report auto (*.rpa)|*.rpa|Tutti i file|*.*|";
	else
		strFilter = "Report ricerca (*.rps)|*.rps|Tutti i file|*.*|";

	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_READONLY |OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, this, 0, FALSE);

	FileDlg.GetOFN().lpstrInitialDir = theApp.m_sEditRep; // Sandro Gallina - 04/05/2004 //

	if (FileDlg.DoModal() == IDOK)
	{
		// Sandro Gallina - 04/05/2004 --> //
		if (theApp.m_bCheckRep == FALSE)
		{
			int iTemp = 0;
			int iLastSlash = 0;
			CString strTemp = FileDlg.GetPathName();

			while(iTemp >= 0)
			{
				iTemp = strTemp.Find('\\', iLastSlash);
				if (iTemp >= 0)
					iLastSlash = iTemp + 1;
			}
			
			theApp.m_sEditRep = strTemp.Left(iLastSlash - 1);
			WritePrivateProfileString(szPercorsi, szEditRep, theApp.m_sEditRep, theApp.m_sFileConfig);
		}
		// <-- Sandro Gallina - 04/05/2004 //

		CaricaReport(FileDlg.GetPathName());

		if (m_nTipoReport == TIPO_REPORT_RICERCA)
		{
			m_bReportSearch = TRUE;
			// strForm = "Report risultati ricerca: ";
		}
		else
		{
			m_bReportSearch = FALSE;
			// strForm = "Report: ";
		}

		// strForm += FileDlg.GetFileName();
		// strForm = FileDlg.GetPathName(); // FileDlg.GetFileName();
		SetWindowText(FileDlg.GetPathName());
		GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_PREVIEW)->EnableWindow(TRUE);
	}
}

void CReportDlg::OnSave()
{
	CString strPathName;
	GetWindowText(strPathName);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FILE_OVERWRITE), MB_YESNO) == IDYES)
		SalvaReport(strPathName);
}

void CReportDlg::OnSaveAs() 
{
	CString strFilter;

	if (m_nTipoReport == TIPO_REPORT_NORMALE)
		strFilter = "Report (*.rpt)|*.rpt|Report auto (*.rpa)|*.rpa|Tutti i file|*.*|";
	else
		strFilter = "Report ricerca (*.rps)|*.rps|Tutti i file|*.*|";

	CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY |OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, this, 0, FALSE);

	FileDlg.GetOFN().lpstrInitialDir = theApp.m_sEditRep; // Sandro Gallina - 04/05/2004 //

	if (FileDlg.DoModal() == IDOK)
	{
		CString strPathName = FileDlg.GetPathName();

		if (_access(strPathName, 00) == 0) // il file esiste già... //
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_THEFILE) + strPathName + theApp.GetMessageString(IDS_OVERWRITE_EXISTING), MB_OKCANCEL) == IDCANCEL)
				return;

		if (m_nTipoReport == TIPO_REPORT_NORMALE)
		{
			if ((strPathName.Right(4) != ".rpt") && (strPathName.Right(4) != ".rpa"))
				strPathName += ".rpt";
		}
		else
		{
			if (strPathName.Right(4) != ".rps")
				strPathName += ".rps";
		}

		// Sandro Gallina - 04/05/2004 --> //
		if (theApp.m_bCheckRep == FALSE)
		{
			int iTemp = 0;
			int iLastSlash = 0;
			CString strTemp = strPathName;

			while(iTemp >= 0)
			{
				iTemp = strTemp.Find('\\', iLastSlash);
				if (iTemp >= 0)
					iLastSlash = iTemp + 1;
			}
			
			theApp.m_sEditRep = strTemp.Left(iLastSlash - 1);
			WritePrivateProfileString(szPercorsi, szEditRep, theApp.m_sEditRep, theApp.m_sFileConfig);
		}
		// <-- Sandro Gallina - 04/05/2004 //

		SalvaReport(strPathName);

		SetWindowText(strPathName); // "Report: " + strFileName);
	}
}

void CReportDlg::CaricaReport(CString strFileReport)
{
	LOGFONT		lfPrinterFont;
	
	lfPrinterFont.lfHeight 				= -10;
	lfPrinterFont.lfWidth				= 0;
	lfPrinterFont.lfWeight 				= 400;
	lfPrinterFont.lfItalic 				= 0;
	lfPrinterFont.lfUnderline 			= 0;
	lfPrinterFont.lfEscapement			= 0;
	lfPrinterFont.lfOrientation			= 0;
	lfPrinterFont.lfStrikeOut			= 0;
	lfPrinterFont.lfCharSet				= 0;
	lfPrinterFont.lfOutPrecision		= 1;
	lfPrinterFont.lfClipPrecision		= 2;
	lfPrinterFont.lfQuality				= 1;
	lfPrinterFont.lfPitchAndFamily		= 34;
	strcpy_s(lfPrinterFont.lfFaceName, "MS Sans Serif");

	UpdateData(TRUE);

	//lettura report da disco...
	/////////////////////////////////

	//lettura delle impostazioni....
	//lettura impostazione header/Footer....
	
	m_lIDStampante = GetPrivateProfileInt("Page", "IDStampante", 0, strFileReport);
	m_lIDHeader1 = GetPrivateProfileInt("Page", "IDHeader1", 0, strFileReport);
	m_nDimHeader = m_pEsamiView->GetAltezzaHF(m_lIDHeader1);
	m_lIDHeader2 = GetPrivateProfileInt("Page", "IDHeader2", 0, strFileReport);
	m_lIDFooter1 = GetPrivateProfileInt("Page", "IDFooter1", 0, strFileReport);
	m_lIDFooter2 = GetPrivateProfileInt("Page", "IDFooter2", 0, strFileReport);
	m_nDimFooter = max(m_pEsamiView->GetAltezzaHF(m_lIDFooter1), m_pEsamiView->GetAltezzaHF(m_lIDFooter2));
	m_bCopiaPDF	 = (BOOL)GetPrivateProfileInt("Page", "CopiaPDF", 0, strFileReport);
	m_bFitToPage = (BOOL)GetPrivateProfileInt("Page", "FitToPage", 0, strFileReport);

	if (m_nTipoReport == TIPO_REPORT_NORMALE)
	{
		m_nFormato = FORMATO_REPORT_A4;
		m_szPage.cx = GetPrivateProfileInt("Page", "Width",  210, strFileReport);
		m_szPage.cy = GetPrivateProfileInt("Page", "Height", 297, strFileReport);
		
		if (m_szPage.cy > m_szPage.cx)
		{
			m_nOrientamento = ORIENT_REPORT_VERT;

			switch(m_szPage.cx)
			{
				case 216:
				{
					switch(m_szPage.cy)
					{
						case 279:
						{
							m_nFormato = FORMATO_REPORT_LETTER;
							break;
						}
						case 355:
						{
							m_nFormato = FORMATO_REPORT_LEGAL;
							break;
						}
					}
					break;
				}
				case 184:
				{
					m_nFormato = FORMATO_REPORT_EXCLUSIVE;
					break;
				}
			}
		}
		else
		{
			m_nOrientamento = ORIENT_REPORT_HORZ;

			switch(m_szPage.cy)
			{
				case 216:
				{
					switch(m_szPage.cx)
					{
						case 279:
						{
							m_nFormato = FORMATO_REPORT_LETTER;
							break;
						}
						case 355:
						{
							m_nFormato = FORMATO_REPORT_LEGAL;
							break;
						}
					}
					break;
				}
				case 184:
				{
					m_nFormato = FORMATO_REPORT_EXCLUSIVE;
				}
			}
		}
	}
	else
	{
		m_szPage.cx = GetPrivateProfileInt("Page", "PageWidth",  210,  strFileReport);
		m_szPage.cy = GetPrivateProfileInt("Page", "PageHeight",  297, strFileReport);

		// if (m_szPage == CSize(210, 297) || m_szPage == CSize(297, 210))
			m_nFormato = 0;
		// else
		// 	m_nFormato = 1;
		
		int nDimTotal = 0;
		if (m_lIDHeader1 > 0)
			nDimTotal += m_nDimHeader;
		if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
			nDimTotal += m_nDimFooter;

		m_nAltezzaRiga = GetPrivateProfileInt("Page", "RowHeight",  10, strFileReport);

		UpdateData(FALSE);
	
		m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);
	}
	
	UpdateData(FALSE);
	NuovoReport();
	RidimensionaPagina();
	
	// seleziono le COMBOS //
	int nCurSel;
	int i;

	nCurSel = 0;
	for(i = 0; i < m_ctrlComboStampante.GetCount(); i++)
	{
		if (m_ctrlComboStampante.GetItemData(i) == m_lIDStampante)
		{
			nCurSel = i;
			break;
		}
	}
	m_ctrlComboStampante.SetCurSel(nCurSel);

	nCurSel = 0;
	for(i = 0; i < m_ctrlComboHeader1.GetCount(); i++)
	{
		if (m_ctrlComboHeader1.GetItemData(i) == m_lIDHeader1)
		{
			nCurSel = i;
			break;
		}
	}
	m_ctrlComboHeader1.SetCurSel(nCurSel);

	nCurSel = 0;
	for(i = 0; i < m_ctrlComboHeader2.GetCount(); i++)
	{
		if (m_ctrlComboHeader2.GetItemData(i) == m_lIDHeader2)
		{
			nCurSel = i;
			break;
		}
	}
	m_ctrlComboHeader2.SetCurSel(nCurSel);

	nCurSel = 0;
	for(i = 0; i < m_ctrlComboFooter1.GetCount(); i++)
	{
		if (m_ctrlComboFooter1.GetItemData(i) == m_lIDFooter1)
		{
			nCurSel = i;
			break;
		}
	}
	m_ctrlComboFooter1.SetCurSel(nCurSel);

	nCurSel = 0;
	for (i = 0; i < m_ctrlComboFooter2.GetCount(); i++)
	{
		if (m_ctrlComboFooter2.GetItemData(i) == m_lIDFooter2)
		{
			nCurSel = i;
			break;
		}
	}
	m_ctrlComboFooter2.SetCurSel(nCurSel);

	// UpdateData(TRUE);

	// --- //

	//lettura numero oggetti....
	int	nTotSection = GetPrivateProfileInt("List", "TotSection", 0, strFileReport);

	for(int nSection = 1; nSection <= nTotSection; nSection++)
	{
		CString		strEtichetta;
		CString		strSezione;
		CString		strTipo;
		BOOL		bCheck;
		COLORREF	rgbColor;
		int			nParam;
		int			nLeft;
		int			nTop;
		int			nRight;
		int			nBottom;
		int			nAlignment;
		int			nRotation;

		strSezione.Format("Section%li", nSection);

		strTipo = GetPrivateProfileString("List", strSezione, "", strFileReport);

		if (strTipo != "")
		{
			strEtichetta = GetPrivateProfileString(strSezione, "Value", "", strFileReport);
			nLeft = GetPrivateProfileInt(strSezione, "Left",  0, strFileReport);
			nRight = GetPrivateProfileInt(strSezione, "Right", 0, strFileReport);
			nTop = GetPrivateProfileInt(strSezione, "Top", 0, strFileReport);
			nBottom = GetPrivateProfileInt(strSezione, "Bottom", 0, strFileReport);
			bCheck = GetPrivateProfileInt(strSezione, "Check", 0,  strFileReport);
			rgbColor = (COLORREF)GetPrivateProfileInt(strSezione, "Color", 0, strFileReport);
			nParam = GetPrivateProfileInt(strSezione, "Param", 0, strFileReport);
			nAlignment = GetPrivateProfileInt(strSezione, "Alignment", 0, strFileReport);
			nRotation = GetPrivateProfileInt(strSezione, "Rotation", 0, strFileReport);

			strcpy_s(lfPrinterFont.lfFaceName, GetPrivateProfileString(strSezione, "Font Name", "MS Sans Serif", strFileReport));
			lfPrinterFont.lfPitchAndFamily = GetPrivateProfileInt(strSezione, "Font Family", 34, strFileReport);
			lfPrinterFont.lfHeight = GetPrivateProfileInt(strSezione, "Font Height", -13, strFileReport);
			lfPrinterFont.lfWeight = GetPrivateProfileInt(strSezione, "Font Weight", 400, strFileReport);
			lfPrinterFont.lfUnderline = GetPrivateProfileInt(strSezione, "Font Under", 0, strFileReport);
			lfPrinterFont.lfItalic = GetPrivateProfileInt(strSezione, "Font Italic", 0, strFileReport);

			CDrawTool* pObj = new CDrawTool;

			if (pObj)
			{
				CRealRect	PosObj;
				CRect		RectInMM;
				CSize		szMin;
				CSize		szMax;

				RectInMM.left   = nLeft;
				RectInMM.right  = nRight;
				RectInMM.top    = nTop;
				RectInMM.bottom = nBottom;

				if (strTipo == "Image" || strTipo == "Icon")
				{
					szMin = CSize( 10,  10);
					szMax = CSize(420, 420);
				}
				else
				if (strTipo == "Report")
				{
					szMin = CSize(100,  75);
					szMax = CSize(420, 420);
				}
				else
				if (strTipo == "Form")
				{
					szMin = CSize(50,  25);
					szMax = CSize(420, 420);
				}
				else
				if (strTipo == "Line")
				{
					szMin = CSize(1,   1);
					szMax = CSize(420, 420);
				}
				else
				{
					szMin = CSize(5,   2);
					szMax = CSize(420, 420);
				}

				PosObj.SetParam (m_rectPage, CRect(CPoint(0,0), m_szPage), 1);
				PosObj.SetPosRectMM(RectInMM);

				// aggiungo solo gli oggetti che hanno un rect valido
				if ((RectInMM.Width() > 0) && (RectInMM.Height() > 0))
				{
					double dRap = ((double)m_szPage.cx / (double)m_rectPage.Width()) * (double)1.45;

					pObj->SetObj(&PosObj, 5, szMin, szMax, dRap);
					pObj->m_strValue	= strEtichetta;
					pObj->m_nAlignment	= nAlignment;
					pObj->m_nRotation	= nRotation;
					pObj->m_strType		= strTipo;
					pObj->m_lfFont		= lfPrinterFont;
					pObj->m_bCheck		= bCheck;
					pObj->m_rgbColor	= rgbColor;
					pObj->m_nParam		= nParam;

					Add(pObj);
				}
			}
		}
	}

	RedrawWindow();
}

void CReportDlg::SalvaReport(CString strFileReport)
{
	int			nSection = 1;
	CString		strBuffer;

	//rimozione file....
	remove(strFileReport);
	
	//scrittura report su disco...

	//scrittura delle impostazioni....
	strBuffer.Format("%li", m_lIDStampante);
	WritePrivateProfileString("Page", "IDStampante", strBuffer, strFileReport);
	strBuffer.Format("%li", m_lIDHeader1);
	WritePrivateProfileString("Page", "IDHeader1", strBuffer, strFileReport);
	strBuffer.Format("%li", m_lIDHeader2);
	WritePrivateProfileString("Page", "IDHeader2", strBuffer, strFileReport);
	strBuffer.Format("%li", m_lIDFooter1);
	WritePrivateProfileString("Page", "IDFooter1", strBuffer, strFileReport);
	strBuffer.Format("%li", m_lIDFooter2);
	WritePrivateProfileString("Page", "IDFooter2", strBuffer, strFileReport);
	strBuffer.Format("%li", (long)m_bCopiaPDF);
	WritePrivateProfileString("Page", "CopiaPDF", strBuffer, strFileReport);
	strBuffer.Format("%li", (long)m_bFitToPage);
	WritePrivateProfileString("Page", "FitToPage", strBuffer, strFileReport);
	
	if (m_nTipoReport == TIPO_REPORT_NORMALE)
	{
		strBuffer.Format("%li", m_szPage.cx);
		WritePrivateProfileString("Page", "Width",	strBuffer, strFileReport);
		strBuffer.Format("%li", m_szPage.cy);
		WritePrivateProfileString("Page", "Height",	strBuffer, strFileReport);
	}
	else
	{
		//se il report è del tipo ricerca
		strBuffer.Format("%li", GetCurrentWidth());
		WritePrivateProfileString("Page", "PageWidth",	strBuffer, strFileReport);
		strBuffer.Format("%li", GetCurrentHeight());
		WritePrivateProfileString("Page", "PageHeight",	strBuffer, strFileReport);

		strBuffer.Format("%li", m_nAltezzaRiga);
		WritePrivateProfileString("Page", "RowHeight",	strBuffer, strFileReport);
	}

	//scrittura del numero di oggetti....
	strBuffer.Format("%li", m_objects.GetCount());
	WritePrivateProfileString("List", "TotSection", strBuffer, strFileReport);

	POSITION pos;

	CDrawObjList listTemp;

	// riordino sempre la lista dei campi nel report //

	while(m_objects.GetCount() > 0)
	{
		// cerco il campo più in alto e più a sinistra //

		int nMinX = 32768;
		int nMinY = 32768;
		POSITION posMin = NULL;

		pos = m_objects.GetHeadPosition();
		while(pos != NULL)
		{
			POSITION posBck = pos;
			CDrawTool* pTemp = m_objects.GetNext(pos);

			if (pTemp != NULL)
			{
				CRect rectTemp = pTemp->GetRectInMM();
				if (rectTemp.top < nMinY)
				{ 
					nMinX = rectTemp.left;
					nMinY = rectTemp.top;
					posMin = posBck;
				}
				else
				{
					if (rectTemp.top == nMinY)
					{
						if (rectTemp.left < nMinX)
						{
							nMinX = rectTemp.left;
							nMinY = rectTemp.top;
							posMin = posBck;
						}
					}
				}
			}
		}

		if (posMin != NULL)
		{
			listTemp.AddTail(m_objects.GetAt(posMin));
			m_objects.RemoveAt(posMin);
		}
	}

	// riverso tutto da listTemp a m_objects //
	m_objects.RemoveAll();

	pos = listTemp.GetHeadPosition();
	while(pos != NULL)
	{
		CDrawTool* pTemp = m_objects.GetNext(pos);

		if (pTemp != NULL)
			m_objects.AddTail(pTemp);
	}

	// continuo con il salvataggio tradizionale //
	pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawTool* pObj = m_objects.GetNext(pos);

		if (pObj)
		{
			CRect	rect = pObj->GetRectInMM();
			int		nLeft	= rect.left;
			int		nRight  = rect.right;
			int		nTop	= rect.top;
			int		nBottom = rect.bottom;

			CString strSezione;
			strSezione.Format("Section%li", nSection++);
			
			WritePrivateProfileString("List", strSezione,	pObj->m_strType, strFileReport);

			WritePrivateProfileString(strSezione, "Value",	pObj->m_strValue, strFileReport);
			strBuffer.Format("%li", pObj->m_nAlignment);
			WritePrivateProfileString(strSezione, "Alignment", strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_nRotation);
			WritePrivateProfileString(strSezione, "Rotation", strBuffer, strFileReport);
			
			strBuffer.Format("%li", nLeft);
			WritePrivateProfileString(strSezione, "Left",	strBuffer, strFileReport);
			strBuffer.Format("%li", nRight);
			WritePrivateProfileString(strSezione, "Right",	strBuffer, strFileReport);
			strBuffer.Format("%li", nTop);
			WritePrivateProfileString(strSezione, "Top",	strBuffer, strFileReport);
			strBuffer.Format("%li", nBottom);
			WritePrivateProfileString(strSezione, "Bottom", strBuffer, strFileReport);

			strBuffer.Format("%li", pObj->m_bCheck);
			WritePrivateProfileString(strSezione, "Check",	strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_rgbColor);
			WritePrivateProfileString(strSezione, "Color",	strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_nParam);
			WritePrivateProfileString(strSezione, "Param",	strBuffer, strFileReport);

			strBuffer.Format("%s", pObj->m_lfFont.lfFaceName);
			WritePrivateProfileString(strSezione, "Font Name",	strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_lfFont.lfPitchAndFamily);
			WritePrivateProfileString(strSezione, "Font Family",	strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_lfFont.lfHeight);
			WritePrivateProfileString(strSezione, "Font Height",	strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_lfFont.lfWeight);
			WritePrivateProfileString(strSezione, "Font Weight",	strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_lfFont.lfUnderline);
			WritePrivateProfileString(strSezione, "Font Under",		strBuffer, strFileReport);
			strBuffer.Format("%li", pObj->m_lfFont.lfItalic);
			WritePrivateProfileString(strSezione, "Font Italic",	strBuffer, strFileReport);
		}
	}
}

void CReportDlg::NuovoReport()
{
	SetWindowText("Generazione di un nuovo report");

	// cancellazione del report corrente...
	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
		delete m_objects.GetNext(pos);

	m_objects.  RemoveAll();
	m_selection.RemoveAll();

	m_ctrlComboStampante.SetCurSel(0);
	m_ctrlComboHeader1.SetCurSel(0);
	m_ctrlComboHeader2.SetCurSel(0);
	m_ctrlComboFooter1.SetCurSel(0);
	m_ctrlComboFooter2.SetCurSel(0);

	RedrawWindow();
}

void CReportDlg::RidimensionaPagina()
{
	CRect rectFrame(0, 0, 0, 0);
	CRect rectDlg(0, 0, 0, 0);

	UpdateData(TRUE);
	
	switch(m_nTipoReport)
	{
		case TIPO_REPORT_NORMALE:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
			{
				rectFrame.right = nHeightFrame * m_szPage.cx / m_szPage.cy;
				rectFrame.bottom = nHeightFrame;
			}
			else
			{
				rectFrame.right = nHeightFrame;
				rectFrame.bottom = nHeightFrame * m_szPage.cy / m_szPage.cx;
			}

			break;
		}
		case TIPO_REPORT_RICERCA:
		{
			// m_rectPage = m_rectVertRicerca;
			rectFrame.right = nHeightFrame * m_szFoglioA4.cx / m_szFoglioA4.cy;
			rectFrame.bottom = nHeightFrame;

			break;
		}
	}

	m_ctrPage.SetWindowPos(NULL, 0, 0, rectFrame.Width(), rectFrame.Height(), SWP_NOMOVE | SWP_NOZORDER);

	rectDlg.right = rectFrame.Width() + nDiffDialogFrame;
	rectDlg.bottom = nHeightDialog;
	SetWindowPos(NULL, 0, 0, rectDlg.Width(), rectDlg.Height(), SWP_NOMOVE | SWP_NOZORDER);
	CenterWindow();

	m_ctrPage.GetWindowRect(&m_rectPage);
	ScreenToClient(&m_rectPage);

	RiposizionaOggetti();
}

void CReportDlg::RiposizionaOggetti()
{
	//riposizionamento oggetti
	POSITION pos = m_objects.GetHeadPosition();

	while (pos != NULL)
	{
		CDrawTool* pObj = m_objects.GetNext(pos);

		if (pObj)
		{
			CRealRect* pRealRect = pObj->GetObj();

			if (pRealRect)
				pRealRect->SetParam (m_rectPage, CRect(CPoint(0,0), m_szPage), 1);
		}
	}
	
	RedrawWindow();
}

void CReportDlg::OnCambiaImpostazioni() 
{
	UpdateData(TRUE);

	if (m_nTipoReport == TIPO_REPORT_NORMALE)
	{
		RedrawWindow();
	}
	else
	{
		int nDimTotal = 0;
		if (m_lIDHeader1 > 0)
			nDimTotal += m_nDimHeader;
		if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
			nDimTotal += m_nDimFooter;

		// m_nAltezzaRiga = int((float)(GetCurrentHeight() - nDimTotal) / (float)m_nNumRighe) - 1;
		m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);
	
		RidimensionaPagina();
	}
}

void CReportDlg::OnCambiaPagina() 
{
	if (m_nTipoReport == TIPO_REPORT_RICERCA)
	{
		m_bCambiaAltezza = TRUE;
		
		int nDimTotal = 0;
		if (m_lIDHeader1 > 0)
			nDimTotal += m_nDimHeader;
		if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
			nDimTotal += m_nDimFooter;

		// m_nAltezzaRiga = int(((float)GetCurrentHeight() - nDimTotal) / (float)m_nNumRighe) - 1;
		m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);
	}
	else
	{
		m_szPage = CSize(GetCurrentWidth(), GetCurrentHeight());
	}

	RidimensionaPagina();
}

void CReportDlg::OnCambiaTipoReport() 
{
	// const int nItemsToShow = 2, nItemsToEnable = 3;

	int nTipoReportOld = m_nTipoReport;
	int i = 0;
	
	UINT nItemToEnable[3] = { IDC_CONTROLLO_3, IDC_CONTROLLO_7, IDC_CONTROLLO_11 };

	UpdateData(TRUE);

	if (!m_bReportSearch)
	{
		if (m_nTipoReport != nTipoReportOld)
		{
			m_bTipoChanged = TRUE;

			if (m_nTipoReport == TIPO_REPORT_RICERCA)
			{
				m_bCambiaAltezza = TRUE;
				
				//Se scelgo intestazione e/o piè di pagina tolgo dalla pagina lo spazio non utilizzabile
				int nDimTotal = 0;
				if (m_lIDHeader1 > 0)
					nDimTotal += m_nDimHeader;
				if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
					nDimTotal += m_nDimFooter;

				// m_nAltezzaRiga = int((float)(GetCurrentHeight() - nDimTotal) / (float)m_nNumRighe) - 1;
				m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);

				OnCambiaPagina();
			}
			else
			{
				m_bCambiaAltezza = FALSE;

				OnCambiaPagina();
			}

			GetDlgItem(IDC_COPIAPDF)->ShowWindow(!m_bCambiaAltezza);
			GetDlgItem(IDC_FIT_TO_PAGE)->ShowWindow(!m_bCambiaAltezza);
			GetDlgItem(IDC_STATIC_8)->ShowWindow(!m_bCambiaAltezza);
			GetDlgItem(IDC_STATIC_13)->ShowWindow(!m_bCambiaAltezza);

			GetDlgItem(IDC_SPIN_HEIGHT)->ShowWindow(m_bCambiaAltezza);
			GetDlgItem(IDC_EDT_HEIGHT)->ShowWindow(m_bCambiaAltezza);

			for(i = 0; i < sizeof(nItemToEnable) / sizeof(UINT); i++)
				GetDlgItem(nItemToEnable[i])->EnableWindow(!m_bCambiaAltezza);
		}
	}
	else
	{
		m_nTipoReport = TIPO_REPORT_RICERCA;
		UpdateData(FALSE);
	}
}

int CReportDlg::GetCurrentWidth()
{
	int nReturn;

	UpdateData(TRUE);

	switch(m_nFormato)
	{
		case FORMATO_REPORT_A4:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioA4.cx;
			else
				nReturn = m_szFoglioA4.cy;
			break;
		}
		case FORMATO_REPORT_LEGAL:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioLegal.cx;
			else
				nReturn = m_szFoglioLegal.cy;
			break;
		}
		case FORMATO_REPORT_LETTER:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioLetter.cx;
			else
				nReturn = m_szFoglioLetter.cy;
			break;
		}
		case FORMATO_REPORT_EXCLUSIVE:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioExclusive.cx;
			else
				nReturn = m_szFoglioExclusive.cy;
			break;
		}
	}

	return nReturn;
}

int CReportDlg::GetCurrentHeight()
{
	int nReturn;

	UpdateData(TRUE);

	switch(m_nFormato)
	{
		case FORMATO_REPORT_A4:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioA4.cy;
			else
				nReturn = m_szFoglioA4.cx;
			break;
		}
		case FORMATO_REPORT_LEGAL:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioLegal.cy;
			else
				nReturn = m_szFoglioLegal.cx;
			break;
		}
		case FORMATO_REPORT_LETTER:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioLetter.cy;
			else
				nReturn = m_szFoglioLetter.cx;
			break;
		}
		case FORMATO_REPORT_EXCLUSIVE:
		{
			if (m_nOrientamento == ORIENT_REPORT_VERT)
				nReturn = m_szFoglioExclusive.cy;
			else
				nReturn = m_szFoglioExclusive.cx;
			break;
		}
	}

	return nReturn;
}

void CReportDlg::OnBtnChiudi()
{
	CResizableDialog::OnOK();
}

void CReportDlg::OnBnClickedPreview()
{
	OnSave();

	CString strTemp;
	GetWindowText(strTemp);
	long lPdfId = 0;
	m_pEsamiView->AnteprimaStampaReport(ANTEPRIMA, VERIFICA_NO, strTemp, FALSE, 1, &lPdfId,"");
}

HBRUSH CReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_1:
		case IDC_COMBO_DIMENSIONE:
		case IDC_STATIC_2:
		case IDC_STATIC_3:
		case IDC_STATIC_12:
		case IDC_STATIC_13:
		case IDC_COMBO_STAMPANTE:
		case IDC_STATIC_4:
		case IDC_STATIC_5:
		case IDC_STATIC_10:
		case IDC_COMBO_HEADER1:
		case IDC_STATIC_11:
		case IDC_COMBO_HEADER2:
		case IDC_COMBO_FOOTER:
		case IDC_STATIC_14:
		case IDC_STATIC_15:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_STATIC_6:
		case IDC_STATIC_7:
		case IDC_STATIC_8:
		case IDC_STATIC_9:
		case IDC_EDT_HEIGHT:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			break;
		}
	}

	return hBrush;
}

void CReportDlg::RiempiCombo()
{
	int nIndex;

	m_ctrlComboStampante.ResetContent();
	m_ctrlComboStampante.InsertString(0, "");
	m_ctrlComboStampante.SetItemData(0, (DWORD)Printer_ChiediStampante);
	m_ctrlComboStampante.InsertString(1, "1");
	m_ctrlComboStampante.SetItemData(1, (DWORD)Printer_Report1);
	m_ctrlComboStampante.InsertString(2, "2");
	m_ctrlComboStampante.SetItemData(2, (DWORD)Printer_Report2);
	m_ctrlComboStampante.InsertString(3, "3");
	m_ctrlComboStampante.SetItemData(3, (DWORD)Printer_Report3);
	m_ctrlComboStampante.InsertString(4, "4");
	m_ctrlComboStampante.SetItemData(4, (DWORD)Printer_Report4);
	m_ctrlComboStampante.InsertString(5, "5");
	m_ctrlComboStampante.SetItemData(5, (DWORD)Printer_Report5);
	m_ctrlComboStampante.InsertString(6, "6");
	m_ctrlComboStampante.SetItemData(6, (DWORD)Printer_Report6);
	m_ctrlComboStampante.InsertString(7, "7");
	m_ctrlComboStampante.SetItemData(7, (DWORD)Printer_Report7);
	m_ctrlComboStampante.InsertString(8, "8");
	m_ctrlComboStampante.SetItemData(8, (DWORD)Printer_Report8);
	m_ctrlComboStampante.InsertString(9, "9");
	m_ctrlComboStampante.SetItemData(9, (DWORD)Printer_Report9);

	CHeaderFooterSet setHF;
	setHF.SetSortRecord("Descrizione");

	m_ctrlComboHeader1.ResetContent();
	m_ctrlComboHeader1.InsertString(0, "");
	m_ctrlComboHeader1.SetItemData(0, (DWORD)-1);

	m_ctrlComboHeader2.ResetContent();
	m_ctrlComboHeader2.InsertString(0, "");
	m_ctrlComboHeader2.SetItemData(0, (DWORD)-1);

	setHF.SetOpenFilter("Tipo=1");
	if (setHF.OpenRecordset("CReportDlg::RiempiCombo"))
	{
		nIndex = 1;

		while(!setHF.IsEOF())
		{
			m_ctrlComboHeader1.InsertString(nIndex, setHF.m_sDescrizione);
			m_ctrlComboHeader1.SetItemData(nIndex, (DWORD)setHF.m_lID);

			m_ctrlComboHeader2.InsertString(nIndex, setHF.m_sDescrizione);
			m_ctrlComboHeader2.SetItemData(nIndex, (DWORD)setHF.m_lID);

			nIndex++;
			setHF.MoveNext();
		}

		setHF.CloseRecordset("CReportDlg::RiempiCombo");
	}

	m_ctrlComboFooter1.ResetContent();
	m_ctrlComboFooter1.InsertString(0, "");
	m_ctrlComboFooter1.SetItemData(0, (DWORD)-1);

	m_ctrlComboFooter2.ResetContent();
	m_ctrlComboFooter2.InsertString(0, "");
	m_ctrlComboFooter2.SetItemData(0, (DWORD)-1);

	setHF.SetOpenFilter("Tipo=2");
	if (setHF.OpenRecordset("CReportDlg::RiempiCombo"))
	{
		nIndex = 1;

		while(!setHF.IsEOF())
		{
			m_ctrlComboFooter1.InsertString(nIndex, setHF.m_sDescrizione);
			m_ctrlComboFooter1.SetItemData(nIndex, (DWORD)setHF.m_lID);

			m_ctrlComboFooter2.InsertString(nIndex, setHF.m_sDescrizione);
			m_ctrlComboFooter2.SetItemData(nIndex, (DWORD)setHF.m_lID);

			nIndex++;
			setHF.MoveNext();
		}

		setHF.CloseRecordset("CReportDlg::RiempiCombo");
	}
}

void CReportDlg::OnCbnSelchangeComboStampante()
{
	UpdateData(TRUE);

	m_lIDStampante = m_ctrlComboStampante.GetItemData(m_ctrlComboStampante.GetCurSel());
}

void CReportDlg::OnCbnSelchangeComboHeader1()
{
	UpdateData(TRUE);

	if (m_nTipoReport == TIPO_REPORT_NORMALE)
	{
		m_lIDHeader1 = m_ctrlComboHeader1.GetItemData(m_ctrlComboHeader1.GetCurSel());
		m_nDimHeader = m_pEsamiView->GetAltezzaHF(m_lIDHeader1);

		RedrawWindow();
	}
	else
	{
		int nDimTotal = 0;
		if (m_lIDHeader1 > 0)
			nDimTotal += m_nDimHeader;
		if ((m_lIDFooter1 > 0) || (m_lIDFooter1 > 0))
			nDimTotal += m_nDimFooter;

		// m_nAltezzaRiga = int((float)(GetCurrentHeight() - nDimTotal) / (float)m_nNumRighe) - 1;
		m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);
	
		RidimensionaPagina();
	}
}

void CReportDlg::OnCbnSelchangeComboHeader2()
{
	UpdateData(TRUE);
	m_lIDHeader2 = m_ctrlComboHeader2.GetItemData(m_ctrlComboHeader2.GetCurSel());
}

void CReportDlg::OnCbnSelchangeComboFooter1()
{
	UpdateData(TRUE);

	if (m_nTipoReport == TIPO_REPORT_NORMALE)
	{
		m_lIDFooter1 = m_ctrlComboFooter1.GetItemData(m_ctrlComboFooter1.GetCurSel());
		m_nDimFooter = max(m_pEsamiView->GetAltezzaHF(m_lIDFooter1), m_pEsamiView->GetAltezzaHF(m_lIDFooter2));

		RedrawWindow();
	}
	else
	{
		int nDimTotal = 0;
		if (m_lIDHeader1 > 0)
			nDimTotal += m_nDimHeader;
		if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
			nDimTotal += m_nDimFooter;

		// m_nAltezzaRiga = int((float)(GetCurrentHeight() - nDimTotal) / (float)m_nNumRighe) - 1;
		m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);
	
		RidimensionaPagina();
	}
}

void CReportDlg::OnCbnSelchangeComboFooter2()
{
	UpdateData(TRUE);

	if (m_nTipoReport == TIPO_REPORT_NORMALE)
	{
		m_lIDFooter2 = m_ctrlComboFooter2.GetItemData(m_ctrlComboFooter2.GetCurSel());
		m_nDimFooter = max(m_pEsamiView->GetAltezzaHF(m_lIDFooter1), m_pEsamiView->GetAltezzaHF(m_lIDFooter2));

		RedrawWindow();
	}
	else
	{
		int nDimTotal = 0;
		if (m_lIDHeader1 > 0)
			nDimTotal += m_nDimHeader;
		if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
			nDimTotal += m_nDimFooter;

		// m_nAltezzaRiga = int((float)(GetCurrentHeight() - nDimTotal) / (float)m_nNumRighe) - 1;
		m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);

		RidimensionaPagina();
	}
}

void CReportDlg::OnEnChangeEdtHeight()
{
	if (m_bCambiaAltezza)
	{
		UpdateData(TRUE);

		int nDimTotal = 0;
		if (m_lIDHeader1 > 0)
			nDimTotal += m_nDimHeader;
		if ((m_lIDFooter1 > 0) || (m_lIDFooter2 > 0))
			nDimTotal += m_nDimFooter;

		// m_nAltezzaRiga = int((float)(GetCurrentHeight() - nDimTotal) / (float)m_nNumRighe) - 1;
		m_szPage = CSize(GetCurrentWidth(), (int)m_nAltezzaRiga);
		
		RiposizionaOggetti();
	}
}

void CReportDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TRACE3("--- CReportDlg::OnKeyDown(%d %d %d)\n", nChar, nRepCnt, nFlags);
	
	// CResizableDialog::OnKeyDown(nChar, nRepCnt, nFlags);

	// int nDx = point.x - m_ptLast.x;
	// int nDy = point.y - m_ptLast.y;
	// OnMouseMove(...)

}
