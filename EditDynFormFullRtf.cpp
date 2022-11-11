#include "stdafx.h"
#include "Endox.h"
#include "EditDynFormFullRtf.h"

#include "CheckListSelDlg.h"
#include "CheckListSet.h"
#include "CheckListUseDlg.h"
#include "CustomDate.h"
#include "EsamiView.h"
#include "VistaCheckListSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSpellCheckerDlg CEditDynFormFullRtf::m_WSpellChecker[40];

CEditDynFormFullRtf::CEditDynFormFullRtf(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CEditDynFormFullRtf::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
	m_bReadOnly = TRUE;
}

CEditDynFormFullRtf::~CEditDynFormFullRtf()
{
}

BEGIN_MESSAGE_MAP(CEditDynFormFullRtf, CEndoxDynForm)

	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BTN_CHECKLIST, OnBnClickedBtnChecklist)
	ON_BN_CLICKED(IDC_BTN_DATA1, OnBnClickedBtnData)
	ON_BN_CLICKED(IDC_BTN_DATA2, OnBnClickedBtnData)

	ON_COMMAND(IDC_RTF_TABLE, OnBnClickedBtnRtfNewTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, OnBnClickedBtnRtfMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, OnBnClickedBtnRtfMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, OnBnClickedBtnRtfMakeLower)

END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CEditDynFormFullRtf, CEndoxDynForm) 
	ON_EVENT(CEditDynFormFullRtf, IDC_TEXTCONTROL, 1, OnChangeTextControlForWSpell, VTS_NONE)
	ON_EVENT(CEditDynFormFullRtf, IDC_TEXTCONTROL, DISPID_MOUSEDOWN, OnMouseDownTextControl, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

void CEditDynFormFullRtf::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEditDynFormFullRtf(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEditDynFormFullRtf::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEditDynFormFullRtf::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITLE:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
	}

	return hBrush;
}

void CEditDynFormFullRtf::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);
	DDX_Control(pDX, IDC_BTN_CHECKLIST, m_ctrlBtnCheckList);
	DDX_Control(pDX, IDC_BTN_DATA1, m_ctrlBtnData1);
	DDX_Control(pDX, IDC_BTN_DATA2, m_ctrlBtnData2);
	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	CString* p_sTestoTXT = NULL;
	CString* p_sTestoRTF = NULL;

	switch(m_lContenuto)
	{
		case edt_liberortf000:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt000;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf000;
			break;
		}
		case edt_liberortf001:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt001;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf001;
			break;
		}
		case edt_liberortf002:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt002;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf002;
			break;
		}
		case edt_liberortf003:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt003;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf003;
			break;
		}
		case edt_liberortf004:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt004;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf004;
			break;
		}
		case edt_liberortf005:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt005;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf005;
			break;
		}
		case edt_liberortf006:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt006;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf006;
			break;
		}
		case edt_liberortf007:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt007;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf007;
			break;
		}
		case edt_liberortf008:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt008;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf008;
			break;
		}
		case edt_liberortf009:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt009;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf009;
			break;
		}
		case edt_liberortf010:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt010;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf010;
			break;
		}
		case edt_liberortf011:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt011;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf011;
			break;
		}
		case edt_liberortf012:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt012;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf012;
			break;
		}
		case edt_liberortf013:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt013;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf013;
			break;
		}
		case edt_liberortf014:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt014;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf014;
			break;
		}
		case edt_liberortf015:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt015;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf015;
			break;
		}
		case edt_liberortf016:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt016;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf016;
			break;
		}
		case edt_liberortf017:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt017;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf017;
			break;
		}
		case edt_liberortf018:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt018;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf018;
			break;
		}
		case edt_liberortf019:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt019;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf019;
			break;
		}
		case edt_liberocl000:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt000;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf000;
			break;
		}
		case edt_liberocl001:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt001;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf001;
			break;
		}
		case edt_liberocl002:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt002;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf002;
			break;
		}
		case edt_liberocl003:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt003;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf003;
			break;
		}
		case edt_liberocl004:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt004;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf004;
			break;
		}
		case edt_liberocl005:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt005;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf005;
			break;
		}
		case edt_liberocl006:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt006;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf006;
			break;
		}
		case edt_liberocl007:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt007;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf007;
			break;
		}
		case edt_liberocl008:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt008;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf008;
			break;
		}
		case edt_liberocl009:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt009;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf009;
			break;
		}
		case edt_liberocl010:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt010;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf010;
			break;
		}
		case edt_liberocl011:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt011;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf011;
			break;
		}
		case edt_liberocl012:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt012;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf012;
			break;
		}
		case edt_liberocl013:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt013;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf013;
			break;
		}
		case edt_liberocl014:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt014;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf014;
			break;
		}
		case edt_liberocl015:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt015;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf015;
			break;
		}
		case edt_liberocl016:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt016;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf016;
			break;
		}
		case edt_liberocl017:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt017;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf017;
			break;
		}
		case edt_liberocl018:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt018;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf018;
			break;
		}
		case edt_liberocl019:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt019;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf019;
			break;
		}

		//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		case edt_refertointegrato_macro:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setRI.m_sRTFMacro;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setRI.m_sRTFMacro;
			break;
		}
		case edt_refertointegrato_diag:
		{
			p_sTestoTXT = &m_pEsamiView->m_pEsamiSet->m_setRI.m_sRTFDiag;
			p_sTestoRTF = &m_pEsamiView->m_pEsamiSet->m_setRI.m_sRTFDiag;
			break;
		}		
		//
	}

	if (pDX->m_bSaveAndValidate)
	{
		if ((p_sTestoTXT != NULL) && (p_sTestoRTF != NULL))
		{
			// Controllo dimensione..
			long lSelStart = m_ctrlTextControl.GetSelStart();
			long lSelLength = m_ctrlTextControl.GetSelLength();

			m_ctrlTextControl.SetRedraw(FALSE);
			m_ctrlTextControl.SetSelStart(0);
			m_ctrlTextControl.SetSelLength(-1);

			if (CSpellCheckerDlg* pWSpell = GetWSpell())
				pWSpell->DeleteUnderline();

			do
			{
				(*p_sTestoTXT) = m_ctrlTextControl.GetSelText();
				(*p_sTestoTXT).Replace("\n", "\r\n");
				(*p_sTestoRTF) = m_ctrlTextControl.GetRTFSelText();

				m_ctrlTextControl.SetSelLength(m_ctrlTextControl.GetSelLength() - 100);
			}
			while(p_sTestoRTF->GetLength() > _TEXT_CONTROL_FIELD_LIMIT);

			(*p_sTestoTXT) = p_sTestoTXT->Left(_TEXT_CONTROL_FIELD_LIMIT);
			(*p_sTestoRTF) = p_sTestoRTF->Left(_TEXT_CONTROL_FIELD_LIMIT);

			// Controllo interruzioni di pagina...
			TCHAR szBreak[2];
			szBreak[0] = TEXT('\x0c');
			szBreak[1] = TEXT('\0');
			CString strBreak(szBreak);

			m_ctrlTextControl.SetSelStart(0);
			m_ctrlTextControl.SetSelLength(-1);
			if (m_ctrlTextControl.GetCurrentPages() > 1)
			{
				for(int i = 1; i < m_ctrlTextControl.GetText().GetLength(); i++)
				{
					m_ctrlTextControl.SetSelStart(i - 1);
					m_ctrlTextControl.SetSelLength(1);

					CString strPrev = m_ctrlTextControl.GetSelText();

					m_ctrlTextControl.SetSelStart(i);
					m_ctrlTextControl.SetSelLength(1);

					CString strCurr = m_ctrlTextControl.GetSelText();

					if (strCurr == strBreak && strPrev != "\n")
					{
						m_ctrlTextControl.SetSelStart(i);
						m_ctrlTextControl.SetSelLength(0);
						m_ctrlTextControl.SetSelText("\r\n");
						i = i + 1;
					}
				}
			}

			m_ctrlTextControl.SetSelStart(lSelStart);
			m_ctrlTextControl.SetSelLength(lSelLength);
			m_ctrlTextControl.SetRedraw(TRUE);
		}
	}
	else
	{
		m_ctrlTextControl.ResetContents();

		m_ctrlTextControl.SetFontName(g_sReportFaceName);
		m_ctrlTextControl.SetFontSize(g_nReportSize);
		m_ctrlTextControl.SetFontBold(g_bReportBold);
		m_ctrlTextControl.SetFontItalic(g_bReportItalic);
		m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

		if ((p_sTestoRTF != NULL) && (p_sTestoTXT != NULL))
		{
			if (!(*p_sTestoRTF).IsEmpty())
			{
				try
				{
					m_ctrlTextControl.SetRTFSelText(*p_sTestoRTF);
				}
				catch (CException* pEx)
				{
					m_ctrlTextControl.SetText(*p_sTestoRTF);
					pEx->Delete();
				}
			}
			else
			{
				if (!(*p_sTestoTXT).IsEmpty())
					m_ctrlTextControl.SetSelText(*p_sTestoTXT);
			}
		}

		if (!m_bReadOnly)
		{
			if (CSpellCheckerDlg* pWSpell = GetWSpell())
				pWSpell->Recheck();
		}
	}
}

void CEditDynFormFullRtf::OnDestroy()
{
	if (CSpellCheckerDlg* pWSpell = GetWSpell())
		pWSpell->SetTextControl(NULL);

	CEndoxDynForm::OnDestroy();
}

BOOL CEditDynFormFullRtf::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();
	m_ctrlToolbar.Create(IDC_BUTTONBAR_PLACE_3, this);

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&theApp.m_fontBold);

	AddAnchor(IDC_STATIC1, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_STATIC_TITLE, CSize(0,0), CSize(100,0));
	AddAnchor(IDC_BUTTONBAR_PLACE_1, CSize(0,0), CSize(100,0));
	AddAnchor(IDC_BUTTONBAR_PLACE_2, CSize(0,0), CSize(100,0));
	AddAnchor(IDC_BUTTONBAR_PLACE_3, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_BTN_CHECKLIST, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_TEXTCONTROL_PLACE, CSize(0,0), CSize(100,100));

	// tolgo i flag WS_CLIPCHILDREN e WS_CLIPSIBLINGS dallo stile della barra //
	::SetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	theApp.LocalizeDialog(this, IDD_SUBFORM_EDITFULLRTF, "EditDynFormFullRtf");

	switch(m_lContenuto)
	{
		case edt_liberortf000:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[0]);
			break;
		}
		case edt_liberortf001:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[1]);
			break;
		}
		case edt_liberortf002:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[2]);
			break;
		}
		case edt_liberortf003:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[3]);
			break;
		}
		case edt_liberortf004:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[4]);
			break;
		}
		case edt_liberortf005:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[5]);
			break;
		}
		case edt_liberortf006:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[6]);
			break;
		}
		case edt_liberortf007:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[7]);
			break;
		}
		case edt_liberortf008:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[8]);
			break;
		}
		case edt_liberortf009:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[9]);
			break;
		}
		case edt_liberortf010:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[10]);
			break;
		}
		case edt_liberortf011:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[11]);
			break;
		}
		case edt_liberortf012:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[12]);
			break;
		}
		case edt_liberortf013:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[13]);
			break;
		}
		case edt_liberortf014:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[14]);
			break;
		}
		case edt_liberortf015:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[15]);
			break;
		}
		case edt_liberortf016:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[16]);
			break;
		}
		case edt_liberortf017:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[17]);
			break;
		}
		case edt_liberortf018:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[18]);
			break;
		}
		case edt_liberortf019:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextRtf[19]);
			break;
		}
		case edt_liberocl000:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[0]);
			break;
		}
		case edt_liberocl001:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[1]);
			break;
		}
		case edt_liberocl002:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[2]);
			break;
		}
		case edt_liberocl003:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[3]);
			break;
		}
		case edt_liberocl004:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[4]);
			break;
		}
		case edt_liberocl005:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[5]);
			break;
		}
		case edt_liberocl006:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[6]);
			break;
		}
		case edt_liberocl007:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[7]);
			break;
		}
		case edt_liberocl008:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[8]);
			break;
		}
		case edt_liberocl009:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[9]);
			break;
		}
		case edt_liberocl010:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[10]);
			break;
		}
		case edt_liberocl011:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[11]);
			break;
		}
		case edt_liberocl012:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[12]);
			break;
		}
		case edt_liberocl013:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[13]);
			break;
		}
		case edt_liberocl014:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[14]);
			break;
		}
		case edt_liberocl015:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[15]);
			break;
		}
		case edt_liberocl016:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[16]);
			break;
		}
		case edt_liberocl017:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[17]);
			break;
		}
		case edt_liberocl018:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[18]);
			break;
		}
		case edt_liberocl019:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.m_sLabelTextCL[19]);
			break;
		}
		//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		case edt_refertointegrato_macro:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_MACRO));
			break;
		}
		case edt_refertointegrato_diag:
		{
			SetDlgItemText(IDC_STATIC_TITLE, theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_DIAG));
			break;
		}
	}

	return bReturn;
}

LRESULT CEditDynFormFullRtf::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CEditDynFormFullRtf::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CEditDynFormFullRtf::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	m_bReadOnly = (BOOL)wParam;

	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_ctrlButtonBar.ShowWindow((BOOL)wParam ? SW_HIDE : SW_SHOW);

	switch(m_lContenuto)
	{
		case edt_liberortf000:
		case edt_liberortf001:
		case edt_liberortf002:
		case edt_liberortf003:
		case edt_liberortf004:
		case edt_liberortf005:
		case edt_liberortf006:
		case edt_liberortf007:
		case edt_liberortf008:
		case edt_liberortf009:
		case edt_liberortf010:
		case edt_liberortf011:
		case edt_liberortf012:
		case edt_liberortf013:
		case edt_liberortf014:
		case edt_liberortf015:
		case edt_liberortf016:
		case edt_liberortf017:
		case edt_liberortf018:
		case edt_liberortf019:
		case edt_refertointegrato_macro: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		case edt_refertointegrato_diag:  //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		{
			m_ctrlBtnCheckList.ShowWindow(SW_HIDE);
			m_ctrlBtnData1.ShowWindow(SW_HIDE);
			m_ctrlBtnData2.ShowWindow((BOOL)wParam ? SW_HIDE : SW_SHOW);
			break;
		}
		case edt_liberocl000:
		case edt_liberocl001:
		case edt_liberocl002:
		case edt_liberocl003:
		case edt_liberocl004:
		case edt_liberocl005:
		case edt_liberocl006:
		case edt_liberocl007:
		case edt_liberocl008:
		case edt_liberocl009:
		case edt_liberocl010:
		case edt_liberocl011:
		case edt_liberocl012:
		case edt_liberocl013:
		case edt_liberocl014:
		case edt_liberocl015:
		case edt_liberocl016:
		case edt_liberocl017:
		case edt_liberocl018:
		case edt_liberocl019:
		{
			m_ctrlBtnCheckList.ShowWindow((BOOL)wParam ? SW_HIDE : SW_SHOW);
			m_ctrlBtnData1.ShowWindow((BOOL)wParam ? SW_HIDE : SW_SHOW);
			m_ctrlBtnData2.ShowWindow(SW_HIDE);
			break;
		}
		default:
		{
			m_ctrlBtnCheckList.ShowWindow(SW_HIDE);
			m_ctrlBtnData1.ShowWindow(SW_HIDE);
			m_ctrlBtnData2.ShowWindow(SW_HIDE);
			break;
		}
	}

	m_ctrlToolbar.ShowWindow((BOOL)wParam ? SW_HIDE : SW_SHOW);

	m_ctrlTextControl.SetBackColor((BOOL)wParam ? GetSysColor(COLOR_3DFACE) : RGB(255, 255, 255));
	m_ctrlTextControl.SetEditMode((BOOL)wParam ? 1 : 0);

	return 1;
}

LRESULT CEditDynFormFullRtf::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CEditDynFormFullRtf::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CString strFilterCons;

	/////

	CString* p_sTesto = NULL;
	CString strTesto = "";
	
	/////

	switch(m_lContenuto)
	{
		case edt_liberortf000:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt000;
			strTesto = "EEsamiPersonalizzabili.TestoTxt000";

			break;
		}
		case edt_liberortf001:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt001;
			strTesto = "EEsamiPersonalizzabili.TestoTxt001";

			break;
		}
		case edt_liberortf002:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt002;
			strTesto = "EEsamiPersonalizzabili.TestoTxt002";

			break;
		}
		case edt_liberortf003:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt003;
			strTesto = "EEsamiPersonalizzabili.TestoTxt003";

			break;
		}
		case edt_liberortf004:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt004;
			strTesto = "EEsamiPersonalizzabili.TestoTxt004";

			break;
		}
		case edt_liberortf005:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt005;
			strTesto = "EEsamiPersonalizzabili.TestoTxt005";

			break;
		}
		case edt_liberortf006:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt006;
			strTesto = "EEsamiPersonalizzabili.TestoTxt006";

			break;
		}
		case edt_liberortf007:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt007;
			strTesto = "EEsamiPersonalizzabili.TestoTxt007";

			break;
		}
		case edt_liberortf008:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt008;
			strTesto = "EEsamiPersonalizzabili.TestoTxt008";

			break;
		}
		case edt_liberortf009:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt009;
			strTesto = "EEsamiPersonalizzabili.TestoTxt009";

			break;
		}
		case edt_liberortf010:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt010;
			strTesto = "EEsamiPersonalizzabili.TestoTxt010";

			break;
		}
		case edt_liberortf011:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt011;
			strTesto = "EEsamiPersonalizzabili.TestoTxt011";

			break;
		}
		case edt_liberortf012:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt012;
			strTesto = "EEsamiPersonalizzabili.TestoTxt012";

			break;
		}
		case edt_liberortf013:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt013;
			strTesto = "EEsamiPersonalizzabili.TestoTxt013";

			break;
		}
		case edt_liberortf014:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt014;
			strTesto = "EEsamiPersonalizzabili.TestoTxt014";

			break;
		}
		case edt_liberortf015:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt015;
			strTesto = "EEsamiPersonalizzabili.TestoTxt015";

			break;
		}
		case edt_liberortf016:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt016;
			strTesto = "EEsamiPersonalizzabili.TestoTxt016";

			break;
		}
		case edt_liberortf017:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt017;
			strTesto = "EEsamiPersonalizzabili.TestoTxt017";

			break;
		}
		case edt_liberortf018:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt018;
			strTesto = "EEsamiPersonalizzabili.TestoTxt018";

			break;
		}
		case edt_liberortf019:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoTxt019;
			strTesto = "EEsamiPersonalizzabili.TestoTxt019";

			break;
		}
		case edt_liberocl000:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt000;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt000";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl001:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt001;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt001";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl002:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt002;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt002";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl003:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt003;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt003";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl004:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt004;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt004";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl005:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt005;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt005";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl006:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt006;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt006";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl007:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt007;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt007";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl008:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt008;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt008";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl009:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt009;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt009";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl010:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt010;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt010";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl011:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt011;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt011";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl012:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt012;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt012";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl013:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt013;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt013";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl014:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt014;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt014";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl015:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt015;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt015";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl016:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt016;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt016";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl017:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt017;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt017";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl018:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt018;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt018";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
		case edt_liberocl019:
		{
			p_sTesto = &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt019;
			strTesto = "EEsamiPersonalizzabili.TestoCLTxt019";

			CString strTempWhere = "";

			POSITION pos = m_elementCLSearchList.GetHeadPosition();

			int i = 0;

			while(pos)
			{
				long itemTemp = m_elementCLSearchList.GetNext(pos);
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "CheckListCheckedElement", i, "IDEsame", "IDItem", itemTemp, 0, MODE_UGUALE);
				i++;
			}

			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!pStrWhere->IsEmpty())
					(*pStrWhere) += " AND ";

				(*pStrWhere) += "(" + strTempWhere + ")";
			}

			break;
		}
	}

	if ((p_sTesto != NULL) && (!strTesto.IsEmpty()))
		ComponiRicercaFromSpecialString(pStrWhere, *p_sTesto, strTesto, "AND");
	
	if (!strFilterCons.IsEmpty())
	{
		if (!pStrWhere->IsEmpty())
			(*pStrWhere) += " AND ";
		(*pStrWhere) += "(" + strFilterCons + ")";
	}

	return 1;
}

void CEditDynFormFullRtf::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);

	CWnd* pTextControlPlace = GetDlgItem(IDC_TEXTCONTROL_PLACE);
	if (pTextControlPlace && m_ctrlTextControl.GetSafeHwnd())
	{
		CRect rect;
		pTextControlPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlTextControl.SetWindowPos(GetDlgItem(IDC_TEXTCONTROL_PLACE), rect.left + 1, rect.top + 1, rect.Width() - 2, rect.Height() - 2, 0);
	}

	///

	switch(m_lContenuto)
	{
		case edt_liberortf000:
		case edt_liberortf001:
		case edt_liberortf002:
		case edt_liberortf003:
		case edt_liberortf004:
		case edt_liberortf005:
		case edt_liberortf006:
		case edt_liberortf007:
		case edt_liberortf008:
		case edt_liberortf009:
		case edt_liberortf010:
		case edt_liberortf011:
		case edt_liberortf012:
		case edt_liberortf013:
		case edt_liberortf014:
		case edt_liberortf015:
		case edt_liberortf016:
		case edt_liberortf017:
		case edt_liberortf018:
		case edt_liberortf019:
		case edt_refertointegrato_macro: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		case edt_refertointegrato_diag:  //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		{
			CWnd* pButtonBarPlace = GetDlgItem(IDC_BUTTONBAR_PLACE_2);

			if (pButtonBarPlace && m_ctrlButtonBar.GetSafeHwnd())
			{
				CRect rect;
				pButtonBarPlace->GetWindowRect(rect);
				ScreenToClient(&rect);
				m_ctrlButtonBar.SetWindowPos(GetDlgItem(IDC_BUTTONBAR_PLACE_2), rect.left, rect.top, rect.Width(), rect.Height(), 0);
			}

			break;
		}
		case edt_liberocl000:
		case edt_liberocl001:
		case edt_liberocl002:
		case edt_liberocl003:
		case edt_liberocl004:
		case edt_liberocl005:
		case edt_liberocl006:
		case edt_liberocl007:
		case edt_liberocl008:
		case edt_liberocl009:
		case edt_liberocl010:
		case edt_liberocl011:
		case edt_liberocl012:
		case edt_liberocl013:
		case edt_liberocl014:
		case edt_liberocl015:
		case edt_liberocl016:
		case edt_liberocl017:
		case edt_liberocl018:
		case edt_liberocl019:
		{
			CWnd* pButtonBarPlace = GetDlgItem(IDC_BUTTONBAR_PLACE_2);

			if (pButtonBarPlace && m_ctrlButtonBar.GetSafeHwnd())
			{
				CRect rect;
				pButtonBarPlace->GetWindowRect(rect);
				ScreenToClient(&rect);
				m_ctrlButtonBar.SetWindowPos(GetDlgItem(IDC_BUTTONBAR_PLACE_2), rect.left, rect.top, rect.Width(), rect.Height(), 0);
			}

			break;
		}
		default:
		{
			CWnd* pButtonBarPlace = GetDlgItem(IDC_BUTTONBAR_PLACE_1);

			if (pButtonBarPlace && m_ctrlButtonBar.GetSafeHwnd())
			{
				CRect rect;
				pButtonBarPlace->GetWindowRect(rect);
				ScreenToClient(&rect);
				m_ctrlButtonBar.SetWindowPos(GetDlgItem(IDC_BUTTONBAR_PLACE_1), rect.left, rect.top, rect.Width(), rect.Height(), 0);
			}

			break;
		}
	}

	///

	if (GetDlgItem(IDC_BUTTONBAR_PLACE_3) && m_ctrlToolbar.GetSafeHwnd())
	{
		m_ctrlToolbar.AttachEx(IDC_BUTTONBAR_PLACE_3, this);
		m_ctrlToolbar.ShowWindow(m_bReadOnly ? SW_HIDE : SW_SHOW);
	}
}

long CEditDynFormFullRtf::GetContenuto()
{
	return m_lContenuto;
}

BOOL CEditDynFormFullRtf::CampoObbligatorioValido()
{
	return !m_ctrlTextControl.GetText().Trim().IsEmpty();
}

void CEditDynFormFullRtf::OnBnClickedBtnChecklist()
{
	m_ctrlBtnCheckList.SetCheck(BST_UNCHECKED);

	long lCampo = -1;
	switch(m_lContenuto)
	{
		case edt_liberocl000:
		{
			lCampo = 0;
			break;
		}
		case edt_liberocl001:
		{
			lCampo = 1;
			break;
		}
		case edt_liberocl002:
		{
			lCampo = 2;
			break;
		}
		case edt_liberocl003:
		{
			lCampo = 3;
			break;
		}
		case edt_liberocl004:
		{
			lCampo = 4;
			break;
		}
		case edt_liberocl005:
		{
			lCampo = 5;
			break;
		}
		case edt_liberocl006:
		{
			lCampo = 6;
			break;
		}
		case edt_liberocl007:
		{
			lCampo = 7;
			break;
		}
		case edt_liberocl008:
		{
			lCampo = 8;
			break;
		}
		case edt_liberocl009:
		{
			lCampo = 9;
			break;
		}
		case edt_liberocl010:
		{
			lCampo = 10;
			break;
		}
		case edt_liberocl011:
		{
			lCampo = 11;
			break;
		}
		case edt_liberocl012:
		{
			lCampo = 12;
			break;
		}
		case edt_liberocl013:
		{
			lCampo = 13;
			break;
		}
		case edt_liberocl014:
		{
			lCampo = 14;
			break;
		}
		case edt_liberocl015:
		{
			lCampo = 15;
			break;
		}
		case edt_liberocl016:
		{
			lCampo = 16;
			break;
		}
		case edt_liberocl017:
		{
			lCampo = 17;
			break;
		}
		case edt_liberocl018:
		{
			lCampo = 18;
			break;
		}
		case edt_liberocl019:
		{
			lCampo = 19;
			break;
		}
	}

	if ((lCampo >=0) && (lCampo < NUM_LABEL_TESTO_CL))
	{
		CList<STRUCT_CHECKLIST> listChecklist;

		// --- //

		CString strFilter;

		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		{
			strFilter.Format("CampoCL=%li", lCampo);

			//Simone - in ricerca devo usare la tabella altrimenti mi ritrovo n checklist da selezionare, dove n è il numero di esami a cui è associata
			CCheckListSet clSet;
			clSet.SetOpenFilter(strFilter);
			if (clSet.OpenRecordset("CEditDynFormFullRtf::OnBnClickedBtnChecklist"))
			{
				while (!clSet.IsEOF())
				{
					STRUCT_CHECKLIST tagTemp;
					tagTemp.m_lID = clSet.m_lID;
					tagTemp.m_sCodice = clSet.m_sCodice;
					tagTemp.m_sDescrizione = clSet.m_sDescrizione;
					tagTemp.m_lIDTipoEsame = -1;
					tagTemp.m_lCampoCL = clSet.m_lCampoCL;
					tagTemp.m_lOrdine = clSet.m_lOrdine;
					listChecklist.AddTail(tagTemp);

					clSet.MoveNext();
				}

				clSet.CloseRecordset("CEditDynFormFullRtf::OnBnClickedBtnChecklist");
			}
		}
		else
		{
			strFilter.Format("IDTipoEsame=%li AND CampoCL=%li", m_pEsamiView->m_pEsamiSet->m_lIDEsame, lCampo);

			CVistaCheckListSet viewCL;
			viewCL.SetOpenFilter(strFilter);
			if (viewCL.OpenRecordset("CEditDynFormFullRtf::OnBnClickedBtnChecklist"))
			{
				while (!viewCL.IsEOF())
				{
					STRUCT_CHECKLIST tagTemp;
					tagTemp.m_lID = viewCL.m_lID;
					tagTemp.m_sCodice = viewCL.m_sCodice;
					tagTemp.m_sDescrizione = viewCL.m_sDescrizione;
					tagTemp.m_lIDTipoEsame = viewCL.m_lIDTipoEsame;
					tagTemp.m_lCampoCL = viewCL.m_lCampoCL;
					tagTemp.m_lOrdine = viewCL.m_lOrdine;
					listChecklist.AddTail(tagTemp);

					viewCL.MoveNext();
				}

				viewCL.CloseRecordset("CEditDynFormFullRtf::OnBnClickedBtnChecklist");
			}
		}		

		// --- //

		switch(listChecklist.GetCount())
		{
			case 0:
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_SEL_ERR));
				break;
			}
			case 1:
			{
				CCheckListUseDlg dlg(this, m_pEsamiView, &m_ctrlTextControl, listChecklist.GetHead().m_lID);
				dlg.DoModal();
				break;
			}
			default:
			{
				if (listChecklist.GetTail().m_lOrdine == 0)
				{
					// nessuna checklist ha un ordine --> alla vecchia maniera, faccio scegliere quale usare //

					CCheckListSelDlg dlg1(this, &listChecklist);
					if (dlg1.DoModal() == IDOK)
					{
						CCheckListUseDlg dlg2(this, m_pEsamiView, &m_ctrlTextControl, dlg1.GetIDCheckList());
						dlg2.DoModal();
					}
				}
				else
				{
					// almeno una checklist ha un ordine --> apro la form di utilizzo nella nuova modalità (possibilità di usare contemporaneamente più checklist) //

					CList<long> listIDs;

					POSITION pos = listChecklist.GetHeadPosition();
					while(pos != NULL)
					{
						STRUCT_CHECKLIST tagTemp = listChecklist.GetNext(pos);

						if (tagTemp.m_lOrdine > 0)
							listIDs.AddTail(tagTemp.m_lID);
					}

					CCheckListUseDlg dlg(this, m_pEsamiView, &m_ctrlTextControl, &listIDs, &m_elementCLSearchList);
					dlg.DoModal();
				}
				break;
			}
		}
	}
}

void CEditDynFormFullRtf::OnBnClickedBtnData()
{
	m_ctrlBtnData1.SetCheck(BST_UNCHECKED);
	m_ctrlBtnData2.SetCheck(BST_UNCHECKED);

	CString strData = "";
	if (m_ctrlTextControl.GetText().Trim().GetLength() <= 0)
		strData = CCustomDate(TRUE, TRUE).GetDate("%d/%m/%Y: ");
	else
		strData = CCustomDate(TRUE, TRUE).GetDate("\r\n%d/%m/%Y: ");

	m_ctrlTextControl.SetSelStart(m_ctrlTextControl.GetText().GetLength() + 1);
	m_ctrlTextControl.SetSelLength(-1);
	m_ctrlTextControl.SetSelText(strData);

	m_ctrlTextControl.SetFocus();
}

void CEditDynFormFullRtf::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl.RtfInsertNewTable(this);
}

void CEditDynFormFullRtf::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl.RtfSelectedTextMakeUpper();
}

void CEditDynFormFullRtf::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl.RtfSelectedTextMakeNormal();
}

void CEditDynFormFullRtf::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl.RtfSelectedTextMakeLower();
}

void CEditDynFormFullRtf::OnChangeTextControlForWSpell()
{
	if (m_ctrlTextControl.GetEditMode() == 0)
	{
		if (CSpellCheckerDlg* pWSpell = GetWSpell())
			pWSpell->Check();
	}
}

void CEditDynFormFullRtf::OnMouseDownTextControl(short Button, short Shift, long X, long Y)
{
	if (Button != 2)
		return;

	if (m_ctrlTextControl.GetEditMode() == 0)
	{
		if (CSpellCheckerDlg* pWSpell = GetWSpell())
			pWSpell->Menu(CPoint(X, Y));
	}
}

CSpellCheckerDlg* CEditDynFormFullRtf::GetWSpell()
{
	int iIndex = -1;

	switch(m_lContenuto)
	{
		case edt_liberortf000:
		{
			iIndex = 0;
			break;
		}
		case edt_liberortf001:
		{
			iIndex = 1;
			break;
		}
		case edt_liberortf002:
		{
			iIndex = 2;
			break;
		}
		case edt_liberortf003:
		{
			iIndex = 3;
			break;
		}
		case edt_liberortf004:
		{
			iIndex = 4;
			break;
		}
		case edt_liberortf005:
		{
			iIndex = 5;
			break;
		}
		case edt_liberortf006:
		{
			iIndex = 6;
			break;
		}
		case edt_liberortf007:
		{
			iIndex = 7;
			break;
		}
		case edt_liberortf008:
		{
			iIndex = 8;
			break;
		}
		case edt_liberortf009:
		{
			iIndex = 9;
			break;
		}
		case edt_liberortf010:
		{
			iIndex = 10;
			break;
		}
		case edt_liberortf011:
		{
			iIndex = 11;
			break;
		}
		case edt_liberortf012:
		{
			iIndex = 12;
			break;
		}
		case edt_liberortf013:
		{
			iIndex = 13;
			break;
		}
		case edt_liberortf014:
		{
			iIndex = 14;
			break;
		}
		case edt_liberortf015:
		{
			iIndex = 15;
			break;
		}
		case edt_liberortf016:
		{
			iIndex = 16;
			break;
		}
		case edt_liberortf017:
		{
			iIndex = 17;
			break;
		}
		case edt_liberortf018:
		{
			iIndex = 18;
			break;
		}
		case edt_liberortf019:
		{
			iIndex = 19;
			break;
		}
		case edt_liberocl000:
		{
			iIndex = 20;
			break;
		}
		case edt_liberocl001:
		{
			iIndex = 21;
			break;
		}
		case edt_liberocl002:
		{
			iIndex = 22;
			break;
		}
		case edt_liberocl003:
		{
			iIndex = 23;
			break;
		}
		case edt_liberocl004:
		{
			iIndex = 24;
			break;
		}
		case edt_liberocl005:
		{
			iIndex = 25;
			break;
		}
		case edt_liberocl006:
		{
			iIndex = 26;
			break;
		}
		case edt_liberocl007:
		{
			iIndex = 27;
			break;
		}
		case edt_liberocl008:
		{
			iIndex = 28;
			break;
		}
		case edt_liberocl009:
		{
			iIndex = 29;
			break;
		}
		case edt_liberocl010:
		{
			iIndex = 30;
			break;
		}
		case edt_liberocl011:
		{
			iIndex = 31;
			break;
		}
		case edt_liberocl012:
		{
			iIndex = 32;
			break;
		}
		case edt_liberocl013:
		{
			iIndex = 33;
			break;
		}
		case edt_liberocl014:
		{
			iIndex = 34;
			break;
		}
		case edt_liberocl015:
		{
			iIndex = 35;
			break;
		}
		case edt_liberocl016:
		{
			iIndex = 36;
			break;
		}
		case edt_liberocl017:
		{
			iIndex = 37;
			break;
		}
		case edt_liberocl018:
		{
			iIndex = 38;
			break;
		}
		case edt_liberocl019:
		{
			iIndex = 39;
			break;
		}
	}

	if (iIndex == -1)
		return NULL;

	if (!m_WSpellChecker[iIndex].Create(m_pEsamiView))
		return NULL;

	m_WSpellChecker[iIndex].SetTextControl(&m_ctrlTextControl);
	return &m_WSpellChecker[iIndex];
}

void CEditDynFormFullRtf::DestroyWSpell()
{
	for(int i = 0; i < _countof(m_WSpellChecker); i++)
		m_WSpellChecker[i].Destroy();
}

void CEditDynFormFullRtf::SetText(CString value)
{
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	m_ctrlTextControl.SetSelText(value);
}
