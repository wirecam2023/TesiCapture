#include "stdafx.h"
#include "Endox.h"
#include "IntestazioneNewDlg.h"

#include <math.h>

#include "EsamiView.h"
#include "ElemReportSet.h"
#include "ReportDlg.h"
#include "DrawTool.h"
#include "FieldDlg.h"
#include "RealRect.h"
#include "RectPreview.h"
#include "RectPreviewObj.h"
#include "Common.h"
#include "HeaderFooterSet.h"
#include "SetupSet.h"
#include "EditStringDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CIntestazioneNewDlg::CIntestazioneNewDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CIntestazioneNewDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;

	m_bInitializing = TRUE;

	// Formati Orientamento Verticale
	m_szFoglioA4 = CSize(210, 297);
	m_szFoglioLegal = CSize(216, 355);
	m_szFoglioLetter = CSize(216, 279);
	m_szFoglioExclusive = CSize(184, 266);

	// Formati Orientamento Orizzontale
	m_szFoglioA4Landscape = CSize(297, 210);//Gabriel BUG 6303

	// rapporto //
	fMult = 726.0f / (float)m_szFoglioLegal.cy; // 726 è l'altezza del riquadro in pixel, 35.5 e l'altezza massima della pagina in cm (formato legal) //

	// formato pagina //
	m_nFormatoPagina = theApp.m_nFormatoPagina;
	m_nAltezzaHeader = 0;
	m_nAltezzaFooter = 0;

	// modalià //
	m_nMode = CTRL_NOTHING;
	
	// cursori //
	m_hCursorAdd   = AfxGetApp()->LoadCursor(IDC_ADD);
    m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	// blocco modifiche //
	m_bHeaderModified = FALSE;
	m_bFooterModified = FALSE;

	// imposto gli ID //
	m_lIDHeader = 0;
	m_lIDFooter = 0;
}

CIntestazioneNewDlg::~CIntestazioneNewDlg()
{
	POSITION pos;

	pos = m_ObjectsHeader.GetHeadPosition();
	while(pos != NULL)
		delete m_ObjectsHeader.GetNext(pos);
	m_ObjectsHeader.RemoveAll();

	pos = m_ObjectsFooter.GetHeadPosition();
	while (pos != NULL)
		delete m_ObjectsFooter.GetNext(pos);
	m_ObjectsFooter.RemoveAll();

	m_selection.RemoveAll();
}

BEGIN_MESSAGE_MAP(CIntestazioneNewDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()

	ON_CBN_SELCHANGE(IDC_COMBO_DIMENSIONE, OnCbnSelchangeComboDimensione)

	ON_EN_CHANGE (IDC_ALTEZZA_INT,  OnChangeAltezzaInt)
	ON_BN_CLICKED(IDC_NUOVO_INT,    OnBnClickedNuovoInt)
	ON_BN_CLICKED(IDC_MODIFICA_INT, OnBnClickedModificaInt)
	ON_BN_CLICKED(IDC_ELIMINA_INT,  OnBnClickedEliminaInt)
	ON_BN_CLICKED(IDC_SALVA_INT,    OnBnClickedSalvaInt)
	ON_BN_CLICKED(IDC_ANNULLA_INT,  OnBnClickedAnnullaInt)

	ON_EN_CHANGE (IDC_ALTEZZA_CODA, OnChangeAltezzaCoda)
	ON_BN_CLICKED(IDC_NUOVO_CODA,   OnBnClickedNuovoCoda)
	ON_BN_CLICKED(IDC_MODIFICA_CODA,OnBnClickedModificaCoda)
	ON_BN_CLICKED(IDC_ELIMINA_CODA, OnBnClickedEliminaCoda)
	ON_BN_CLICKED(IDC_SALVA_CODA,   OnBnClickedSalvaCoda)
	ON_BN_CLICKED(IDC_ANNULLA_CODA, OnBnClickedAnnullaCoda)

	ON_BN_CLICKED(IDC_CONTROLLO_1,  OnClickControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_2,  OnClickControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_3,  OnClickControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_4,  OnClickControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_5,  OnClickControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_6,  OnClickControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_7,  OnClickControllo)
	ON_BN_CLICKED(IDC_CONTROLLO_8,  OnClickControllo)
	ON_BN_CLICKED(IDC_DELETE,       OnRimuovi)

	ON_BN_CLICKED(IDC_CENTRA_H,     OnCentraH)
	ON_BN_CLICKED(IDC_CENTRA_V,     OnCentraV)

	ON_BN_CLICKED(IDC_ANTEPRIMA,    OnAnteprima)
	ON_BN_CLICKED(IDC_ESCI,         OnEsci)

	ON_CBN_SELCHANGE(IDC_COMBO_HEADER, OnCbnSelchangeComboHeader)
	ON_CBN_SELCHANGE(IDC_COMBO_FOOTER, OnCbnSelchangeComboFooter)

END_MESSAGE_MAP()

void CIntestazioneNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);

	DDX_Control(pDX, IDC_CONTROLLO_1,	m_ctrlButtonControl1);
	DDX_Control(pDX, IDC_CONTROLLO_2,	m_ctrlButtonControl2);
	DDX_Control(pDX, IDC_CONTROLLO_3,	m_ctrlButtonControl3);
	DDX_Control(pDX, IDC_CONTROLLO_4,	m_ctrlButtonControl4);
	DDX_Control(pDX, IDC_CONTROLLO_5,	m_ctrlButtonControl5);
	DDX_Control(pDX, IDC_CONTROLLO_6,	m_ctrlButtonControl6);
	DDX_Control(pDX, IDC_CONTROLLO_7,	m_ctrlButtonControl7);
	DDX_Control(pDX, IDC_CONTROLLO_8,	m_ctrlButtonControl8);
	DDX_Control(pDX, IDC_DELETE,		m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_CENTRA_H,		m_ctrlButtonCentraH);
	DDX_Control(pDX, IDC_CENTRA_V,		m_ctrlButtonCentraV);
	DDX_Control(pDX, IDC_ANTEPRIMA,		m_ctrlButtonAnteprima);

	DDX_Control(pDX, IDC_NUOVO_INT,		m_ctrlButtonNewInt);
	DDX_Control(pDX, IDC_MODIFICA_INT,	m_ctrlButtonEdtInt);
	DDX_Control(pDX, IDC_ELIMINA_INT,	m_ctrlButtonDelInt);
	DDX_Control(pDX, IDC_SALVA_INT,		m_ctrlButtonSaveInt);
	DDX_Control(pDX, IDC_ANNULLA_INT,	m_ctrlButtonUndoInt);

	DDX_Control(pDX, IDC_NUOVO_CODA,    m_ctrlButtonNewCoda);
	DDX_Control(pDX, IDC_MODIFICA_CODA, m_ctrlButtonEdtCoda);
	DDX_Control(pDX, IDC_ELIMINA_CODA,  m_ctrlButtonDelCoda);
	DDX_Control(pDX, IDC_SALVA_CODA,	m_ctrlButtonSaveCoda);
	DDX_Control(pDX, IDC_ANNULLA_CODA,	m_ctrlButtonUndoCoda);

	DDX_Control(pDX, IDC_ESCI,			m_ctrlButtonEsci);

	DDX_Control(pDX, IDC_SPIN_INT,		m_ctrlSpinInt);
	DDX_Control(pDX, IDC_SPIN_CODA,		m_ctrlSpinCoda);

	DDX_Control(pDX, IDC_TOTAL,			m_ctrlFrameTotal);
	DDX_Control(pDX, IDC_HEADER,		m_ctrlFrameHeader);
	DDX_Control(pDX, IDC_FOOTER,		m_ctrlFrameFooter);

	DDX_Control(pDX, IDC_COMBO_HEADER, m_ctrlComboHeader);
	DDX_Control(pDX, IDC_COMBO_FOOTER, m_ctrlComboFooter);

	DDX_CBIndex  (pDX, IDC_COMBO_DIMENSIONE, m_nFormatoPagina);
	DDX_Text     (pDX, IDC_ALTEZZA_INT,  m_nAltezzaHeader);
	DDV_MinMaxInt(pDX, m_nAltezzaHeader, 0, 99);
	DDX_Text     (pDX, IDC_ALTEZZA_CODA, m_nAltezzaFooter);
	DDV_MinMaxInt(pDX, m_nAltezzaFooter, 0, 99);
	DDX_Radio    (pDX, IDC_CONTROLLO_1, m_nMode);

	CRect rectTotal;
	m_ctrlFrameTotal.GetWindowRect(rectTotal);
	ScreenToClient(rectTotal);

	m_ctrlFrameHeader.SetWindowPos(NULL, rectTotal.left, rectTotal.top, rectTotal.Width(), (int)((float)m_nAltezzaHeader * fMult), SWP_NOZORDER);
	m_ctrlFrameHeader.GetWindowRect(m_rectHeader);
	ScreenToClient(m_rectHeader);

	m_ctrlFrameFooter.SetWindowPos(NULL, rectTotal.left, rectTotal.bottom - (int)((float)m_nAltezzaFooter * fMult) /* + 1*/, rectTotal.Width(), (int)((float)m_nAltezzaFooter * fMult), SWP_NOZORDER);
	m_ctrlFrameFooter.GetWindowRect(m_rectFooter);
	ScreenToClient(m_rectFooter);
}

BOOL CIntestazioneNewDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlFrameTotal.SetWindowPos(NULL, 0, 0, (int)((float)GetCurrentWidth() * fMult), (int)((float)GetCurrentHeight() * fMult), SWP_NOMOVE | SWP_NOZORDER);

	GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_4)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_ESCI)->SetFont(&theApp.m_fontBold);
	
	m_ctrlFrameTotal.GetWindowRect(&m_rectTotal);
	m_ctrlFrameHeader.GetWindowRect(&m_rectHeader);
	m_ctrlFrameFooter.GetWindowRect(&m_rectFooter);
	
	ScreenToClient(&m_rectTotal);
	ScreenToClient(&m_rectHeader);
	ScreenToClient(&m_rectFooter);

	m_ctrlSpinInt.SetRange(1, 99);
	m_ctrlSpinCoda.SetRange(1, 99);

	CHeaderFooterSet setHF;

	setHF.SetOpenFilter("Tipo=1");
	setHF.SetSortRecord("Descrizione");
	if (setHF.OpenRecordset("CIntestazioneNewDlg::OnInitDialog"))
	{
		int nIndex = 0;

		while(!setHF.IsEOF())
		{
			m_ctrlComboHeader.InsertString(nIndex, setHF.m_sDescrizione);
			m_ctrlComboHeader.SetItemData(nIndex, setHF.m_lID);

			nIndex++;
			setHF.MoveNext();
		}

		if (nIndex == 0)
		{
			if (setHF.AddNewRecordset("CIntestazioneNewDlg::OnInitDialog"))
			{
				setHF.m_sDescrizione = "Default";
				setHF.m_lTipo = 1;
				setHF.m_lAltezza = 40;

				if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnInitDialog"))
				{
					m_ctrlComboHeader.InsertString(0, setHF.m_sDescrizione);
					m_ctrlComboHeader.SetItemData(0, setHF.GetLastAdd());
				}
			}
		}

		m_ctrlComboHeader.SetCurSel(0);

		setHF.CloseRecordset("CIntestazioneNewDlg::OnInitDialog");
	}

	setHF.SetOpenFilter("Tipo=2");
	setHF.SetSortRecord("Descrizione");
	if (setHF.OpenRecordset("CIntestazioneNewDlg::OnInitDialog"))
	{
		int nIndex = 0;

		while(!setHF.IsEOF())
		{
			m_ctrlComboFooter.InsertString(nIndex, setHF.m_sDescrizione);
			m_ctrlComboFooter.SetItemData(nIndex, setHF.m_lID);

			nIndex++;
			setHF.MoveNext();
		}

		if (nIndex == 0)
		{
			if (setHF.AddNewRecordset("CIntestazioneNewDlg::OnInitDialog"))
			{
				setHF.m_sDescrizione = "Default";
				setHF.m_lTipo = 2;
				setHF.m_lAltezza = 20;

				if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnInitDialog"))
				{
					m_ctrlComboFooter.InsertString(0, setHF.m_sDescrizione);
					m_ctrlComboFooter.SetItemData(0, setHF.GetLastAdd());
				}
			}
		}

		m_ctrlComboFooter.SetCurSel(0);

		setHF.CloseRecordset("CIntestazioneNewDlg::OnInitDialog");
	}

	theApp.LocalizeDialog(this, CIntestazioneNewDlg::IDD, "IntestazioneNewDlg");

	m_bInitializing = FALSE;

	OnCbnSelchangeComboDimensione();
	OnCbnSelchangeComboHeader();
	OnCbnSelchangeComboFooter();

	ModifyHeader(FALSE);
	ModifyFooter(FALSE);

	return bReturn;
}

void CIntestazioneNewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
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

	BOOL		bContinue = FALSE;

	// abilita il ridimensionamento di un oggetto anche se occupa tutto lo spazio
	CRect rectPlusHeader, rectPlusFooter;
	rectPlusHeader.top    = m_rectHeader.top - 10;
	rectPlusHeader.left   = m_rectHeader.left - 10;
	rectPlusHeader.bottom = m_rectHeader.bottom + 10;
	rectPlusHeader.right  = m_rectHeader.right + 10;

	rectPlusFooter.top    = m_rectFooter.top - 10;
	rectPlusFooter.left   = m_rectFooter.left - 10;
	rectPlusFooter.bottom = m_rectFooter.bottom + 10;
	rectPlusFooter.right  = m_rectFooter.right + 10;

	if (rectPlusHeader.PtInRect(point))
	{
		m_rectPage = m_rectHeader;
		bContinue  = TRUE;
	}

	if (rectPlusFooter.PtInRect(point))
	{
		m_rectPage = m_rectFooter;
		bContinue  = TRUE;
	}

	if (bContinue)
	{
		switch(m_nMode)
		{
			case CTRL_NOTHING:
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
			case CTRL_TEXT:
			{
				bAddObj	 = TRUE;
				strValue = "Testo";
				strType  = "Text";
				nParam	 = 0;
				nAlignment = 0;
				nRotation = 0;

				break;
			}
			case CTRL_BMP:
			{
				bAddObj	 = TRUE;
				strValue = "C:\\BITMAP.BMP";
				strType  = "Icon";
				nParam	 = 0;
				nAlignment = 0;
				nRotation = 0;

				szMin = CSize( 10,  10);
				szMax = CSize(420, 420);
				szNor = CSize( 10,  10);

				break;
			}
			case CTRL_LINE:
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
			case CTRL_FIELD:
			{
				bAddObj	 = TRUE;
				strValue = "Anagrafico.A";
				strType  = "Field";
				nParam	 = 0;
				nAlignment = 0;
				nRotation = 0;

				break;
			}
			case CTRL_PAGENUM:
			{
				bAddObj	 = TRUE;
				strValue = "PageNum";
				strType  = "PageNum";
				nParam	 = 0;
				nAlignment = 0;
				nRotation = 0;

				break;
			}
			case CTRL_PAGETOT:
			{
				bAddObj	 = TRUE;
				strValue = "PageTot";
				strType  = "PageTot";
				nParam	 = 0;
				nAlignment = 0;
				nRotation = 0;

				break;
			}
			case CTRL_PARAM:
			{
				bAddObj	 = TRUE;
				strValue = "szData";
				strType  = "Param";
				nParam	 = 0;
				nAlignment = 0;
				nRotation = 0;

				break;
			}
		}

		if (bAddObj)
		{
			CRect rectPage  = m_rectPage;
			CSize szInPixel = szNor;
			CSize szPage;

			if (m_rectHeader.PtInRect(point))
				szPage = m_szPageHeader;
			else
				szPage = m_szPageFooter;

			szInPixel.cx = (int)((double)m_rectPage.Width () * (double)szNor.cx / (double)szPage.cx);
			szInPixel.cy = (int)((double)m_rectPage.Height() * (double)szNor.cy / (double)szPage.cy);
			
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

					ptInMM.x = (int)(((double)szPage.cx * (double)ptInPixel.x) / (double)m_rectPage.Width ());
					ptInMM.y = (int)(((double)szPage.cy * (double)ptInPixel.y) / (double)m_rectPage.Height());

					RectInMM.left   = ptInMM.x - szNor.cx/2;
					RectInMM.right  = ptInMM.x + szNor.cx/2;
					RectInMM.top    = ptInMM.y - szNor.cy/2;
					RectInMM.bottom = ptInMM.y + szNor.cy/2;

					PosObj.SetParam (m_rectPage, CRect(CPoint(0,0), szPage), 1);
					PosObj.SetPosRectMM(RectInMM);
				
					double dRap = ((double)m_szPageHeader.cx / (double)m_rectHeader.Width()) * (double)1.05;

					pObj->SetObj(&PosObj, 5, szMin, szMax, dRap);
					pObj->m_strValue	= strValue;
					pObj->m_nAlignment	= nAlignment;
					pObj->m_nRotation	= nRotation;
					pObj->m_strType		= strType;
					pObj->m_bCheck		= TRUE;
					pObj->m_rgbColor	= RGB(0,0,0);
					pObj->m_nParam		= nParam;

					if (m_rectHeader.PtInRect(point))
						pObj->m_bHeader = TRUE;
					else
						pObj->m_bHeader = FALSE;

					Add(pObj);

					RedrawWindow();
				}
				
				m_nMode = CTRL_NOTHING;
				UpdateData(FALSE);
			}
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CIntestazioneNewDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDrawTool*	pObj = NULL;

	switch (m_nMode)
	{
		case CTRL_NOTHING:
		{
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
	}

	ReleaseCapture();
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CIntestazioneNewDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	BOOL bAddCursor = FALSE;
	CDrawTool* pObj = NULL;

	if (m_rectHeader.PtInRect(point))
		m_rectPage = m_rectHeader;

	if (m_rectFooter.PtInRect(point))
		m_rectPage = m_rectFooter;

	switch(m_nMode)
	{
		case CTRL_NOTHING:
		{
			if (GetCapture() == this)
			{
				pObj = GetSelect();
				
				if (pObj)
				{
					CRect rectDraw = m_rectPage;
					
					if (pObj->m_bIsEnable)
					{
						if ((m_rectHeader.PtInRect(point) && pObj->m_bHeader) || (m_rectFooter.PtInRect(point) && !pObj->m_bHeader))
						{	
							pObj->OnMouseMove(this, rectDraw, point);
							
							if (pObj->m_bHeader)
								ModifyHeader(TRUE);
							else
								ModifyFooter(TRUE);
						}	
					}
				}
			}
			break;
		}
		default:
		{
			if (GetCapture() == NULL && (m_rectHeader.PtInRect(point) || m_rectFooter.PtInRect(point)))
				bAddCursor = TRUE;

			break;
		}
	}

	if (bAddCursor)
		SetCursor(m_hCursorAdd);
	else
		SetCursor(m_hCursorArrow);

	CDialog::OnMouseMove(nFlags, point);
}

void CIntestazioneNewDlg::OnPaint() 
{
	POSITION pos;
	CPaintDC dc(this);

	CBrush total(RGB(255, 255, 255));

	CBrush page(HS_CROSS, RGB(220,220,220));
	dc.SetBkColor(RGB(255, 255, 255));
	
	dc.FillRect(m_rectTotal, &total);
	dc.FillRect(m_rectHeader, &page);
	dc.FillRect(m_rectFooter, &page);
	
	page.DeleteObject();

	// Header //
	pos = m_ObjectsHeader.GetHeadPosition();
	while (pos != NULL)
	{
		TrackerState nTrack	  = normal;
		CDrawTool*	 pObj 	  = m_ObjectsHeader.GetNext(pos);
		CString	strTitle = "";
		int nAlignment = 0;
		int nRotation = 0;

		if (pObj->m_strType == "Field")
		{
			CString strField  = "...";

			for(int i = 0; i < endox_report_field_num_total; i++)
			{
				if (CFieldDlg::m_strFieldEndox[i].sReport == pObj->m_strValue)
				{
					strField = CFieldDlg::m_strFieldEndox[i].sCombo;
					
					break;
				}
			}
			
			strTitle = "(F)" + strField;
			nAlignment = pObj->m_nAlignment;
			nRotation = pObj->m_nRotation;
		}
		else
		{
			strTitle = pObj->m_strValue;
			nAlignment = pObj->m_nAlignment;
			nRotation = pObj->m_nRotation;
		}

		if (IsSelected(pObj))
			nTrack = selected;

		pObj->Draw(&dc, strTitle, nAlignment, nRotation, nTrack, &pObj->m_lfFont);
	}

	// Footer //
	pos = m_ObjectsFooter.GetHeadPosition();
	while (pos != NULL)
	{
		TrackerState nTrack = normal;
		CDrawTool* pObj = m_ObjectsFooter.GetNext(pos);
		CString strTitle = "";
		int nAlignment = 0;
		int nRotation = 0;

		if (pObj->m_strType == "Field")
		{
			CString strField  = "...";

			for(int i = 0; i < endox_report_field_num_total; i++)
			{
				if (CFieldDlg::m_strFieldEndox[i].sReport == pObj->m_strValue)
				{
					strField = CFieldDlg::m_strFieldEndox[i].sCombo;
					
					break;
				}
			}
			
			strTitle = "(F)" + strField;
			nAlignment = pObj->m_nAlignment;
			nRotation = pObj->m_nRotation;
		}
		else
		{
			strTitle = pObj->m_strValue;
			nAlignment = pObj->m_nAlignment;
			nRotation = pObj->m_nRotation;
		}

		if (IsSelected(pObj))
			nTrack = selected;

		LOGFONT lfObj = pObj->m_lfFont;
		pObj->Draw(&dc, strTitle, nAlignment, nRotation, nTrack, &lfObj);
	}
}

void CIntestazioneNewDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CDrawTool* pObj = NULL;
	CRect rectPage;
	CSize szPage;

	switch(m_nMode)
	{
		case REPORT_NOTHING:
		{
			pObj = ObjectAt(point);
						
			if (pObj && pObj != GetSelect())
				Select(pObj, FALSE);

			if (pObj)
			{
				if (pObj->m_bHeader)
				{
					rectPage = m_rectHeader;
					szPage = m_szPageHeader;	
				}
				else
				{
					rectPage = m_rectFooter;
					szPage = m_szPageFooter;
				}
				
				CFieldDlg dlg(this, rectPage, pObj, szPage);

				if (dlg.DoModal() == IDOK)
				{
					pObj->Invalidate(this);

					if (pObj->m_bHeader)
						ModifyHeader(TRUE);
					else
						ModifyFooter(TRUE);
				}
			}
			break;
		}
	}
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CIntestazioneNewDlg::OnCbnSelchangeComboDimensione()
{
	if (!m_bInitializing)
	{
		UpdateData(TRUE);
		m_ctrlFrameTotal.SetWindowPos(NULL, 0, 0, (int)((float)GetCurrentWidth() * fMult), (int)((float)GetCurrentHeight() * fMult), SWP_NOMOVE | SWP_NOZORDER);
		m_ctrlFrameTotal.GetWindowRect(&m_rectTotal);
		ScreenToClient(&m_rectTotal);
		UpdateData(FALSE);

		m_szPageHeader = CSize(GetCurrentWidth(), m_nAltezzaHeader);
		m_szPageFooter = CSize(GetCurrentWidth(), m_nAltezzaFooter);

		RiposizionaOggettiHeader();
		RiposizionaOggettiFooter();
	}
}

void CIntestazioneNewDlg::OnCbnSelchangeComboHeader()
{
	if (!m_bInitializing)
	{
		if (m_bHeaderModified)
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVEHEADERFIRST), MB_YESNO) == IDYES)
				OnBnClickedSalvaInt();

		m_lIDHeader = m_ctrlComboHeader.GetItemData(m_ctrlComboHeader.GetCurSel());

		BOOL bError = FALSE;

		CString strFilter;

		LOGFONT	lfPrinterFont;
		lfPrinterFont.lfWidth		  = 0;
		lfPrinterFont.lfEscapement	  = 0;
		lfPrinterFont.lfOrientation	  = 0;
		lfPrinterFont.lfStrikeOut	  = 0;
		lfPrinterFont.lfCharSet		  = 0;
		lfPrinterFont.lfOutPrecision  = 1;
		lfPrinterFont.lfClipPrecision = 2;
		lfPrinterFont.lfQuality		  = 1;

		POSITION pos = m_ObjectsHeader.GetHeadPosition();
		while(pos != NULL)
			delete m_ObjectsHeader.GetNext(pos);
		m_ObjectsHeader.RemoveAll();

		CHeaderFooterSet setHF;
		strFilter.Format("ID=%li", m_lIDHeader);
		setHF.SetOpenFilter(strFilter);
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboHeader"))
		{
			if (!setHF.IsEOF())
			{
				UpdateData(TRUE);
				m_nAltezzaHeader = setHF.m_lAltezza;
				UpdateData(FALSE);

				m_szPageHeader = CSize(GetCurrentWidth(), m_nAltezzaHeader);
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboHeader");
		}

		CElemReportSet setTemp;
		strFilter.Format("IDHeaderFooter=%li", m_lIDHeader);

		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboHeader"))
		{
			while(!setTemp.IsEOF())
			{
				CDrawTool* pObj = new CDrawTool;

				if (pObj)
				{
					CRealRect	PosObj;
					CRect		RectInMM;
					CSize		szMin;
					CSize		szMax;
					
					RectInMM.left   = setTemp.m_nLeft;
					RectInMM.right  = setTemp.m_nRight;
					RectInMM.top    = setTemp.m_nTop;
					RectInMM.bottom = setTemp.m_nBottom;

					if (setTemp.m_strType == "Icon")
					{
						szMin = CSize( 10,  10);
						szMax = CSize(420, 420);
					}

					if (setTemp.m_strType == "Line")
					{
						szMin = CSize(1,   1);
						szMax = CSize(420, 420);
					}
				
					if (setTemp.m_strType == "Text")
					{
						szMin = CSize(5,   2);
						szMax = CSize(420, 420);
					}
					
					PosObj.SetParam(m_rectHeader, CRect(CPoint(0,0), m_szPageHeader), 1);
					PosObj.SetPosRectMM(RectInMM);

					lfPrinterFont.lfPitchAndFamily = (unsigned char)setTemp.m_nFontFamily;
					lfPrinterFont.lfHeight 		   = setTemp.m_nFontHeight;
					lfPrinterFont.lfWeight 		   = setTemp.m_nFontWeight;
					lfPrinterFont.lfItalic 		   = (unsigned char)setTemp.m_nFontItalic;
					lfPrinterFont.lfUnderline 	   = (unsigned char)setTemp.m_nFontUnder;
					strcpy_s(lfPrinterFont.lfFaceName, setTemp.m_strFontName);

					double dRap = ((double)m_szPageHeader.cx / (double)m_rectHeader.Width()) * (double)1.05;

					pObj->SetObj(&PosObj, 5, szMin, szMax, dRap);
					pObj->m_strValue	= setTemp.m_strValue;
					pObj->m_nAlignment  = setTemp.m_nAlignment;
					pObj->m_nRotation   = setTemp.m_nRotation;
					pObj->m_strType		= setTemp.m_strType;
					pObj->m_lfFont		= lfPrinterFont;
					pObj->m_bCheck		= setTemp.m_nCheck;
					pObj->m_rgbColor	= (COLORREF)setTemp.m_nColor;
					pObj->m_nParam		= setTemp.m_nParam;

					pObj->m_bHeader = TRUE;

					Add(pObj);
				}
			
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboHeader");
		}
	}

	ModifyHeader(FALSE);

	m_selection.RemoveAll();
	RedrawWindow();
}

void CIntestazioneNewDlg::OnCbnSelchangeComboFooter()
{
	if (!m_bInitializing)
	{
		if (m_bFooterModified)
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVEFOOTERFIRST), MB_YESNO) == IDYES)
				OnBnClickedSalvaCoda();

		m_lIDFooter = m_ctrlComboFooter.GetItemData(m_ctrlComboFooter.GetCurSel());

		BOOL bError = FALSE;

		CString strFilter;

		LOGFONT	lfPrinterFont;
		lfPrinterFont.lfWidth		  = 0;
		lfPrinterFont.lfEscapement	  = 0;
		lfPrinterFont.lfOrientation	  = 0;
		lfPrinterFont.lfStrikeOut	  = 0;
		lfPrinterFont.lfCharSet		  = 0;
		lfPrinterFont.lfOutPrecision  = 1;
		lfPrinterFont.lfClipPrecision = 2;
		lfPrinterFont.lfQuality		  = 1;

		POSITION pos = m_ObjectsFooter.GetHeadPosition();
		while(pos != NULL)
			delete m_ObjectsFooter.GetNext(pos);
		m_ObjectsFooter.RemoveAll();

		CHeaderFooterSet setHF;
		strFilter.Format("ID=%li", m_lIDFooter);
		setHF.SetOpenFilter(strFilter);
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboFooter"))
		{
			if (!setHF.IsEOF())
			{
				UpdateData(TRUE);
				m_nAltezzaFooter = setHF.m_lAltezza;
				UpdateData(FALSE);

				m_szPageFooter = CSize(GetCurrentWidth(), m_nAltezzaFooter);
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboFooter");
		}

		CElemReportSet setTemp;
		strFilter.Format("IDHeaderFooter=%li", m_lIDFooter);

		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboFooter"))
		{
			while(!setTemp.IsEOF())
			{
				CDrawTool* pObj = new CDrawTool;

				if (pObj)
				{
					CRealRect	PosObj;
					CRect		RectInMM;
					CSize		szMin;
					CSize		szMax;
					
					RectInMM.left   = setTemp.m_nLeft;
					RectInMM.right  = setTemp.m_nRight;
					RectInMM.top    = setTemp.m_nTop;
					RectInMM.bottom = setTemp.m_nBottom;

					if (setTemp.m_strType == "Icon")
					{
						szMin = CSize( 10,  10);
						szMax = CSize(420, 420);
					}

					if (setTemp.m_strType == "Line")
					{
						szMin = CSize(1,   1);
						szMax = CSize(420, 420);
					}
				
					if (setTemp.m_strType == "Text")
					{
						szMin = CSize(5,   2);
						szMax = CSize(420, 420);
					}
					
					PosObj.SetParam(m_rectFooter, CRect(CPoint(0,0), m_szPageFooter), 1);
					PosObj.SetPosRectMM(RectInMM);

					lfPrinterFont.lfPitchAndFamily = (unsigned char)setTemp.m_nFontFamily;
					lfPrinterFont.lfHeight 		   = setTemp.m_nFontHeight;
					lfPrinterFont.lfWeight 		   = setTemp.m_nFontWeight;
					lfPrinterFont.lfItalic 		   = (unsigned char)setTemp.m_nFontItalic;
					lfPrinterFont.lfUnderline 	   = (unsigned char)setTemp.m_nFontUnder;
					strcpy_s(lfPrinterFont.lfFaceName, setTemp.m_strFontName);

					double dRap = ((double)m_szPageFooter.cx / (double)m_rectFooter.Width()) * (double)1.05;

					pObj->SetObj(&PosObj, 5, szMin, szMax, dRap);
					pObj->m_strValue	= setTemp.m_strValue;
					pObj->m_nAlignment  = setTemp.m_nAlignment;
					pObj->m_nRotation   = setTemp.m_nRotation;
					pObj->m_strType		= setTemp.m_strType;
					pObj->m_lfFont		= lfPrinterFont;
					pObj->m_bCheck		= setTemp.m_nCheck;
					pObj->m_rgbColor	= (COLORREF)setTemp.m_nColor;
					pObj->m_nParam		= setTemp.m_nParam;

					pObj->m_bHeader = FALSE;

					Add(pObj);
				}
			
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CIntestazioneNewDlg::OnCbnSelchangeComboFooter");
		}
	}

	ModifyFooter(FALSE);

	m_selection.RemoveAll();
	RedrawWindow();
}

void CIntestazioneNewDlg::OnChangeAltezzaInt() 
{
	if (!m_bInitializing)
	{
		UpdateData(TRUE);

		m_szPageHeader = CSize(GetCurrentWidth(), m_nAltezzaHeader);
	
		RiposizionaOggettiHeader();

		ModifyHeader(TRUE);

		UpdateData(FALSE);
	}
}

void CIntestazioneNewDlg::OnBnClickedNuovoInt()
{
	if (m_bHeaderModified)
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVEHEADERFIRST), MB_YESNO) == IDYES)
			OnBnClickedSalvaInt();

	CEditStringDlg dlg(this, IDS_ADDNEWHEADER, "");
	if (dlg.DoModal() == IDOK)
	{
		CHeaderFooterSet setHF;
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedNuovoInt"))
		{
			if (setHF.AddNewRecordset("CIntestazioneNewDlg::OnBnClickedNuovoInt"))
			{
				setHF.m_sDescrizione = dlg.GetValue();
				setHF.m_lTipo = 1;
				setHF.m_lAltezza = 40;

				if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedNuovoInt"))
				{
					int nIndex = m_ctrlComboHeader.GetCount();

					m_ctrlComboHeader.InsertString(nIndex, setHF.m_sDescrizione);
					m_ctrlComboHeader.SetItemData(nIndex, setHF.GetLastAdd());

					m_ctrlComboHeader.SetCurSel(nIndex);
					ModifyHeader(FALSE);
					OnCbnSelchangeComboHeader();
				}
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedNuovoInt");
		}
	}
}

void CIntestazioneNewDlg::OnBnClickedModificaInt()
{
	if (m_bHeaderModified)
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVEHEADERFIRST), MB_YESNO) == IDYES)
			OnBnClickedSalvaInt();

	int nCurSel = m_ctrlComboHeader.GetCurSel();

	CString strTemp;
	m_ctrlComboHeader.GetLBText(nCurSel, strTemp);

	CEditStringDlg dlg(this, IDS_EDITHEADER, strTemp);
	if (dlg.DoModal() == IDOK)
	{
		strTemp.Format("ID=%li", (long)m_ctrlComboHeader.GetItemData(nCurSel));

		CHeaderFooterSet setHF;
		setHF.SetOpenFilter(strTemp);
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedModificaInt"))
		{
			if (!setHF.IsEOF())
			{
				if (setHF.EditRecordset("CIntestazioneNewDlg::OnBnClickedModificaInt"))
				{
					setHF.m_sDescrizione = dlg.GetValue();

					if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedModificaInt"))
					{
						int nIndex = m_ctrlComboHeader.GetCount() - 1;

						m_ctrlComboHeader.DeleteString(nCurSel);

						m_ctrlComboHeader.InsertString(nIndex, setHF.m_sDescrizione);
						m_ctrlComboHeader.SetItemData(nIndex, setHF.m_lID);

						m_ctrlComboHeader.SetCurSel(nIndex);
						ModifyHeader(FALSE);
						OnCbnSelchangeComboHeader();
					}
				}
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedModificaInt");
		}
	}
}

void CIntestazioneNewDlg::OnBnClickedEliminaInt()
{
	if (m_ctrlComboHeader.GetCount() <= 1)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CANNOTDELETEHEADER));
		return;
	}

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETEHEADER), MB_YESNO) == IDYES)
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lIDHeader);

		CHeaderFooterSet setHF;
		setHF.SetOpenFilter(strFilter);
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt"))
		{
			if (!setHF.IsEOF())
			{
				if (setHF.DeleteRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt"))
				{
					strFilter.Format("IDHeaderFooter=%li", m_lIDHeader);

					CElemReportSet setElem;
					setElem.SetOpenFilter(strFilter);
					if (setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt"))
					{
						while(!setElem.IsEOF())
						{
							setElem.DeleteRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt");
							setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt");
							setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt");
						}

						setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt");
					}

					m_ctrlComboHeader.DeleteString(m_ctrlComboHeader.GetCurSel());

					m_ctrlComboHeader.SetCurSel(0);
					ModifyHeader(FALSE);
					OnCbnSelchangeComboHeader();
				}
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedEliminaInt");
		}
	}
}

void CIntestazioneNewDlg::OnBnClickedSalvaInt()
{
	UpdateData(TRUE);

	CString strFilter;

	CHeaderFooterSet setHF;
	CElemReportSet setElem;

	strFilter.Format("ID=%li", m_lIDHeader);
	setHF.SetOpenFilter(strFilter);
	if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt"))
	{
		if (!setHF.IsEOF())
		{
			if (setHF.EditRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt"))
			{
				setHF.m_lAltezza = m_nAltezzaHeader;

				if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt"))
				{
					strFilter.Format("IDHeaderFooter=%li", m_lIDHeader);
					setElem.SetOpenFilter(strFilter);
					if (setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt"))
					{
						while(!setElem.IsEOF())
						{
							setElem.DeleteRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt");
							setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt");
							setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt");
						}

						POSITION pos = m_ObjectsHeader.GetHeadPosition();
						while(pos != NULL)
						{
							CDrawTool* pObj = m_ObjectsHeader.GetNext(pos);

							if (pObj != NULL)
							{
								CRect rect = pObj->GetRectInMM();

								if (setElem.AddNewRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt"))
								{
									setElem.m_lIDHeaderFooter = m_lIDHeader;
									setElem.m_strType = pObj->m_strType;
									setElem.m_strValue = pObj->m_strValue;

									setElem.m_nLeft     = rect.left;
									setElem.m_nRight    = rect.right;
									setElem.m_nTop      = rect.top;
									setElem.m_nBottom   = rect.bottom;

									setElem.m_nCheck    = pObj->m_bCheck;
									setElem.m_nColor    = pObj->m_rgbColor;
									setElem.m_nParam    = pObj->m_nParam;

									setElem.m_strFontName = pObj->m_lfFont.lfFaceName;
									setElem.m_nFontFamily = pObj->m_lfFont.lfPitchAndFamily;
									setElem.m_nFontHeight = pObj->m_lfFont.lfHeight;
									setElem.m_nFontWeight = pObj->m_lfFont.lfWeight;
									setElem.m_nFontUnder  = pObj->m_lfFont.lfUnderline;
									setElem.m_nFontItalic = pObj->m_lfFont.lfItalic;

									setElem.m_nAlignment = pObj->m_nAlignment;
									setElem.m_nRotation  = pObj->m_nRotation;

									setElem.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt");
								}
							}
						}

						setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt");
					}
				}
			}
		}

		setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedSalvaInt");
	}

	ModifyHeader(FALSE);
}

void CIntestazioneNewDlg::OnBnClickedAnnullaInt()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_CANCEL), MB_YESNO) == IDYES)
	{	
		ModifyHeader(FALSE);
		OnCbnSelchangeComboHeader();
	}
}

void CIntestazioneNewDlg::OnChangeAltezzaCoda() 
{
	if (!m_bInitializing)
	{
		UpdateData(TRUE);

		m_szPageFooter = CSize(GetCurrentWidth(), m_nAltezzaFooter);
	
		RiposizionaOggettiFooter();

		ModifyFooter(TRUE);

		UpdateData(FALSE);
	}
}

void CIntestazioneNewDlg::OnBnClickedNuovoCoda()
{
	if (m_bFooterModified)
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVEFOOTERFIRST), MB_YESNO) == IDYES)
			OnBnClickedSalvaCoda();

	CEditStringDlg dlg(this, IDS_ADDNEWFOOTER, "");
	if (dlg.DoModal() == IDOK)
	{
		CHeaderFooterSet setHF;
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedNuovoCoda"))
		{
			if (setHF.AddNewRecordset("CIntestazioneNewDlg::OnBnClickedNuovoCoda"))
			{
				setHF.m_sDescrizione = dlg.GetValue();
				setHF.m_lTipo = 2;
				setHF.m_lAltezza = 20;

				if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedNuovoCoda"))
				{
					int nIndex = m_ctrlComboFooter.GetCount();

					m_ctrlComboFooter.InsertString(nIndex, setHF.m_sDescrizione);
					m_ctrlComboFooter.SetItemData(nIndex, setHF.GetLastAdd());

					m_ctrlComboFooter.SetCurSel(nIndex);
					ModifyFooter(FALSE);
					OnCbnSelchangeComboFooter();
				}
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedNuovoCoda");
		}
	}
}

void CIntestazioneNewDlg::OnBnClickedModificaCoda()
{
	if (m_bFooterModified)
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVEFOOTERFIRST), MB_YESNO) == IDYES)
			OnBnClickedSalvaCoda();

	int nCurSel = m_ctrlComboFooter.GetCurSel();

	CString strTemp;
	m_ctrlComboFooter.GetLBText(nCurSel, strTemp);

	CEditStringDlg dlg(this, IDS_EDITFOOTER, strTemp);
	if (dlg.DoModal() == IDOK)
	{
		strTemp.Format("ID=%li", (long)m_ctrlComboFooter.GetItemData(nCurSel));

		CHeaderFooterSet setHF;
		setHF.SetOpenFilter(strTemp);
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedModificaCoda"))
		{
			if (!setHF.IsEOF())
			{
				if (setHF.EditRecordset("CIntestazioneNewDlg::OnBnClickedModificaCoda"))
				{
					setHF.m_sDescrizione = dlg.GetValue();

					if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedModificaCoda"))
					{
						int nIndex = m_ctrlComboFooter.GetCount() - 1;

						m_ctrlComboFooter.DeleteString(nCurSel);

						m_ctrlComboFooter.InsertString(nIndex, setHF.m_sDescrizione);
						m_ctrlComboFooter.SetItemData(nIndex, setHF.m_lID);

						m_ctrlComboFooter.SetCurSel(nIndex);
						ModifyFooter(FALSE);
						OnCbnSelchangeComboFooter();
					}
				}
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedModificaCoda");
		}
	}
}

void CIntestazioneNewDlg::OnBnClickedEliminaCoda()
{
	if (m_ctrlComboFooter.GetCount() <= 1)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CANNOTDELETEFOOTER));
		return;
	}

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETEFOOTER), MB_YESNO) == IDYES)
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lIDFooter);

		CHeaderFooterSet setHF;
		setHF.SetOpenFilter(strFilter);
		if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda"))
		{
			if (!setHF.IsEOF())
			{
				if (setHF.DeleteRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda"))
				{
					strFilter.Format("IDHeaderFooter=%li", m_lIDFooter);

					CElemReportSet setElem;
					setElem.SetOpenFilter(strFilter);
					if (setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda"))
					{
						while(!setElem.IsEOF())
						{
							setElem.DeleteRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda");
							setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda");
							setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda");
						}

						setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda");
					}

					m_ctrlComboFooter.DeleteString(m_ctrlComboFooter.GetCurSel());

					m_ctrlComboFooter.SetCurSel(0);
					ModifyFooter(FALSE);
					OnCbnSelchangeComboFooter();
				}
			}

			setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedEliminaCoda");
		}
	}
}

void CIntestazioneNewDlg::OnBnClickedSalvaCoda()
{
	UpdateData(TRUE);

	CString strFilter;

	CHeaderFooterSet setHF;
	CElemReportSet setElem;

	strFilter.Format("ID=%li", m_lIDFooter);
	setHF.SetOpenFilter(strFilter);
	if (setHF.OpenRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda"))
	{
		if (!setHF.IsEOF())
		{
			if (setHF.EditRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda"))
			{
				setHF.m_lAltezza = m_nAltezzaFooter;

				if (setHF.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda"))
				{
					strFilter.Format("IDHeaderFooter=%li", m_lIDFooter);
					setElem.SetOpenFilter(strFilter);
					if (setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda"))
					{
						while(!setElem.IsEOF())
						{
							setElem.DeleteRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda");
							setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda");
							setElem.OpenRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda");
						}

						POSITION pos = m_ObjectsFooter.GetHeadPosition();
						while(pos != NULL)
						{
							CDrawTool* pObj = m_ObjectsFooter.GetNext(pos);

							if (pObj != NULL)
							{
								CRect rect = pObj->GetRectInMM();

								if (setElem.AddNewRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda"))
								{
									setElem.m_lIDHeaderFooter = m_lIDFooter;
									setElem.m_strType = pObj->m_strType;
									setElem.m_strValue = pObj->m_strValue;

									setElem.m_nLeft     = rect.left;
									setElem.m_nRight    = rect.right;
									setElem.m_nTop      = rect.top;
									setElem.m_nBottom   = rect.bottom;

									setElem.m_nCheck    = pObj->m_bCheck;
									setElem.m_nColor    = pObj->m_rgbColor;
									setElem.m_nParam    = pObj->m_nParam;

									setElem.m_strFontName = pObj->m_lfFont.lfFaceName;
									setElem.m_nFontFamily = pObj->m_lfFont.lfPitchAndFamily;
									setElem.m_nFontHeight = pObj->m_lfFont.lfHeight;
									setElem.m_nFontWeight = pObj->m_lfFont.lfWeight;
									setElem.m_nFontUnder  = pObj->m_lfFont.lfUnderline;
									setElem.m_nFontItalic = pObj->m_lfFont.lfItalic;

									setElem.m_nAlignment = pObj->m_nAlignment;
									setElem.m_nRotation  = pObj->m_nRotation;

									setElem.UpdateRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda");
								}
							}
						}

						setElem.CloseRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda");
					}
				}
			}
		}

		setHF.CloseRecordset("CIntestazioneNewDlg::OnBnClickedSalvaCoda");
	}

	ModifyFooter(FALSE);
	RedrawWindow();
}

void CIntestazioneNewDlg::OnBnClickedAnnullaCoda()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_CANCEL), MB_YESNO) == IDYES)
	{	
		ModifyFooter(FALSE);
		OnCbnSelchangeComboFooter();
	}
}

void CIntestazioneNewDlg::OnClickControllo() 
{
	UpdateData(TRUE);	
}

void CIntestazioneNewDlg::OnRimuovi() 
{
	CDrawTool* pObj = GetSelect();

	if (pObj != NULL)
		Remove(pObj);

	RedrawWindow();
}

void CIntestazioneNewDlg::OnCentraH() 
{
	CDrawTool* pObj = GetSelect();

	if (pObj != NULL)
		CentraOrizz(pObj);

	RedrawWindow();
}

void CIntestazioneNewDlg::OnCentraV() 
{
	CDrawTool* pObj = GetSelect();

	if (pObj != NULL)
		CentraVert(pObj);

	RedrawWindow();
}

void CIntestazioneNewDlg::OnAnteprima()
{
	// se ci sono modifiche ad header o footer chiedo di salvare //
	CString strMessage = "";
	int nMode = 0;

	if (m_bHeaderModified && m_bFooterModified)
	{
		strMessage = theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_1);
		nMode = 3;
	}
	else if (m_bHeaderModified)
	{
		strMessage = theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_2);
		nMode = 1;
	}
	else if (m_bFooterModified)
	{
		strMessage = theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_3);
		nMode = 2;
	}

	if (nMode > 0)
	{
		if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO) == IDYES)
		{
			switch(nMode)
			{
				case 1:
				{
					OnBnClickedSalvaInt();
					break;
				}
				case 2:
				{
					OnBnClickedSalvaCoda();
					break;
				}
				case 3:
				{
					OnBnClickedSalvaInt();
					OnBnClickedSalvaCoda();
					break;
				}
			}
		}
	}

	// creo io un report temporaneo con il set minimo di informazioni necessarie per l'anteprima //

	CString strReportFile = theApp.m_sDirTemp + "\\temp.rpx";
	DeleteFile(strReportFile);

	WritePrivateProfileInt("Page", "IDHeader1", m_lIDHeader, strReportFile);
	WritePrivateProfileInt("Page", "IDFooter2", m_lIDFooter, strReportFile);
	WritePrivateProfileInt("Page", "Width", GetCurrentWidth(), strReportFile);
	WritePrivateProfileInt("Page", "Height", GetCurrentHeight(), strReportFile);
	WritePrivateProfileInt("List", "TotSection", 0, strReportFile);
 
	// lancio l'anteprima //
	long lPdfId = 0;
	m_pEsamiView->AnteprimaStampaReport(ANTEPRIMA, VERIFICA_NO, strReportFile, FALSE, 1, &lPdfId,"");
}

void CIntestazioneNewDlg::OnEsci()
{
	theApp.m_nFormatoPagina = m_nFormatoPagina;

	// salvo su DB il formato della pagina //

	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='Formato pagina'");
	if (setSetup.OpenRecordset("CIntestazioneNewDlg::OnEsci"))
	{
		if (setSetup.IsEOF())
		{
			if (setSetup.AddNewRecordset("CIntestazioneNewDlg::OnEsci"))
			{
				setSetup.m_sVoce = "Formato pagina";
				setSetup.m_sValore.Format("%d", theApp.m_nFormatoPagina);

				setSetup.UpdateRecordset("CIntestazioneNewDlg::OnEsci");
			}
		}
		else
		{
			if (setSetup.EditRecordset("CIntestazioneNewDlg::OnEsci"))
			{
				setSetup.m_sValore.Format("%d", theApp.m_nFormatoPagina);

				setSetup.UpdateRecordset("CIntestazioneNewDlg::OnEsci");
			}
		}

		setSetup.CloseRecordset("CIntestazioneNewDlg::OnEsci");
	}

	// - //

	CString strMessage = "";

	int nMode = 0;
	if (m_bHeaderModified && m_bFooterModified)
	{
		strMessage = theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_1);
		nMode = 3;
	}
	else if (m_bHeaderModified)
	{
		strMessage = theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_2);
		nMode = 1;
	}
	else if (m_bFooterModified)
	{
		strMessage = theApp.GetMessageString(IDS_INTESTAZIONENEWDLG_MOD_3);
		nMode = 2;
	}

	if (nMode > 0)
	{
		switch(theApp.AfxMessageBoxEndo(strMessage, MB_YESNOCANCEL))
		{
			case IDYES:
			{
				switch(nMode)
				{
					case 1:
					{
						OnBnClickedSalvaInt();
						break;
					}
					case 2:
					{
						OnBnClickedSalvaCoda();
						break;
					}
					case 3:
					{
						OnBnClickedSalvaInt();
						OnBnClickedSalvaCoda();
						break;
					}
				}
				break;
			}
			case IDNO:
			{
				break;
			}
			case IDCANCEL:
			{
				return;
			}
		}
	}
	
	CDialog::OnOK();
}

void CIntestazioneNewDlg::CentraOrizz(CDrawTool* pObj)
{
	CRect rectObj, rectPage, rectNew;

	rectObj = pObj->GetRectInPixel();
	
	if (pObj->m_bHeader)
		rectPage = m_rectHeader;
	else
		rectPage = m_rectFooter;

	rectNew = rectObj;
	rectNew.left = rectPage.left + (rectPage.Width() - rectObj.Width()) / 2;
	rectNew.right = rectNew.left + rectObj.Width();

	pObj->SetRectInPixel(this, rectNew);
}

void CIntestazioneNewDlg::CentraVert(CDrawTool* pObj)
{
	CRect rectObj, rectPage, rectNew;

	rectObj = pObj->GetRectInPixel();
	
	if (pObj->m_bHeader)
		rectPage = m_rectHeader;
	else
		rectPage = m_rectFooter;

	rectNew = rectObj;
	rectNew.top = rectPage.top + (rectPage.Height() - rectObj.Height()) / 2;
	rectNew.bottom = rectNew.top + rectObj.Height();

	pObj->SetRectInPixel(this, rectNew);
}

void CIntestazioneNewDlg::RiposizionaOggettiHeader()
{
	POSITION pos = m_ObjectsHeader.GetHeadPosition();
	while(pos != NULL)
	{
		CDrawTool* pObj = m_ObjectsHeader.GetNext(pos);

		if (pObj != NULL)
		{
			CRealRect* pRealRect = pObj->GetObj();

			if (pRealRect != NULL)
				pRealRect->SetParam(m_rectHeader, CRect(CPoint(0,0), m_szPageHeader), 1);
		}
	}
	
	RedrawWindow();
}

void CIntestazioneNewDlg::RiposizionaOggettiFooter()
{
	POSITION pos = m_ObjectsFooter.GetHeadPosition();
	while(pos != NULL)
	{
		CDrawTool* pObj = m_ObjectsFooter.GetNext(pos);

		if (pObj != NULL)
		{
			CRealRect* pRealRect = pObj->GetObj();

			if (pRealRect != NULL)
				pRealRect->SetParam (m_rectFooter, CRect(CPoint(0,0), m_szPageFooter), 1);
		}
	}
	
	RedrawWindow();
}

////////////////////////////////////////////////////////////
// Funzioni relative alla gestione degli oggetti DrawTool //
////////////////////////////////////////////////////////////

CDrawTool* CIntestazioneNewDlg::GetSelect()
{
	CDrawTool* pObj = NULL;

	POSITION posObj = m_selection.GetHeadPosition();

	if (posObj != NULL)
		pObj = m_selection.GetNext(posObj);

	return pObj;
}

void CIntestazioneNewDlg::Add(CDrawTool* pObj)
{
	if (pObj->m_bHeader)
	{
		UpdateData(TRUE);
		m_ObjectsHeader.AddTail(pObj);
		ModifyHeader(TRUE);
	}
	else
	{
		UpdateData(TRUE);
		m_ObjectsFooter.AddTail(pObj);
		ModifyFooter(TRUE);
	}

	pObj->m_bIsEnable = TRUE;

	Select(pObj, FALSE);
}

void CIntestazioneNewDlg::Remove(CDrawTool* pObj)
{
	POSITION pos;
	
	if (pObj->m_bHeader)
	{
		pos = m_ObjectsHeader.Find(pObj);
		
		if (pos != NULL)
		{
			UpdateData(TRUE);
			m_ObjectsHeader.RemoveAt(pos);
			ModifyHeader(TRUE);
		}
	}
	else
	{
		pos = m_ObjectsFooter.Find(pObj);
		
		if (pos != NULL)
		{
			UpdateData(TRUE);
			m_ObjectsFooter.RemoveAt(pos);
			ModifyFooter(TRUE);
		}
	}

	pos = m_selection.Find(pObj);
	if (pos != NULL)
		m_selection.RemoveAt(pos);

	delete pObj;
}

CDrawTool* CIntestazioneNewDlg::ObjectAt(const CPoint& point)
{
	CRect rect(point, CSize(1, 1));

	if (m_rectHeader.PtInRect(point))
	{
		POSITION pos = m_ObjectsHeader.GetTailPosition();

		while (pos != NULL)
		{
			CDrawTool* pObj = m_ObjectsHeader.GetPrev(pos);
			if (pObj->Intersects(rect))
				return pObj;
		}
	}
	else
	{
		POSITION pos = m_ObjectsFooter.GetTailPosition();

		while (pos != NULL)
		{
			CDrawTool* pObj = m_ObjectsFooter.GetPrev(pos);
			if (pObj->Intersects(rect))
				return pObj;
		}
	}

	return NULL;
}

BOOL CIntestazioneNewDlg::IsSelected(CDrawTool* pObj)
{
	if (m_selection.Find(pObj))
		return TRUE;
	
	return FALSE;
}

void CIntestazioneNewDlg::Select(CDrawTool* pObj, BOOL bAdd)
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

int CIntestazioneNewDlg::GetCurrentWidth()
{
	int nReturn;

	UpdateData(TRUE);

	switch(m_nFormatoPagina)
	{
		case FORMATO_REPORT_A4:
		{
			nReturn = m_szFoglioA4.cx;
			break;
		}
		case FORMATO_REPORT_LEGAL:
		{
			nReturn = m_szFoglioLegal.cx;
			break;
		}
		case FORMATO_REPORT_LETTER:
		{
			nReturn = m_szFoglioLetter.cx;
			break;
		}
		case FORMATO_REPORT_EXCLUSIVE:
		{
			nReturn = m_szFoglioExclusive.cx;
			break;
		}
		case FORMATO_REPORT_A4_LANDSCAPE: //Gabriel BUG 6303
		{
			nReturn = m_szFoglioA4Landscape.cx;
			break;
		}
	}

	return nReturn;
}

int CIntestazioneNewDlg::GetCurrentHeight()
{
	int nReturn;

	UpdateData(TRUE);

	switch(m_nFormatoPagina)
	{
		case FORMATO_REPORT_A4:
		{
			nReturn = m_szFoglioA4.cy;
			break;
		}
		case FORMATO_REPORT_LEGAL:
		{
			nReturn = m_szFoglioLegal.cy;
			break;
		}
		case FORMATO_REPORT_LETTER:
		{
			nReturn = m_szFoglioLetter.cy;
			break;
		}
		case FORMATO_REPORT_EXCLUSIVE:
		{
			nReturn = m_szFoglioExclusive.cy;
			break;
		}
		case FORMATO_REPORT_A4_LANDSCAPE: //Gabriel BUG 6303
		{
			nReturn = m_szFoglioA4Landscape.cy;
			break;
		}
	}

	return nReturn;
}

void CIntestazioneNewDlg::ModifyHeader(BOOL bHeaderModified)
{
	if (m_bHeaderModified != bHeaderModified)
	{
		m_bHeaderModified = bHeaderModified;
		m_ctrlButtonSaveInt.EnableWindow(bHeaderModified);
		m_ctrlButtonUndoInt.EnableWindow(bHeaderModified);
	}
}

void CIntestazioneNewDlg::ModifyFooter(BOOL bFooterModified)
{
	if (m_bFooterModified != bFooterModified)
	{
		m_bFooterModified = bFooterModified;
		m_ctrlButtonSaveCoda.EnableWindow(bFooterModified);
		m_ctrlButtonUndoCoda.EnableWindow(bFooterModified);
	}
}