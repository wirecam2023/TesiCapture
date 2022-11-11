#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiICD9Dlg.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "MyPrintDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDiagnosiICD9Dlg, CDialog)

CDiagnosiICD9Dlg::CDiagnosiICD9Dlg(CWnd* pParent)
	: CDialog(CDiagnosiICD9Dlg::IDD, pParent)
{
	m_iModalita = CORE_VISUA;
}

CDiagnosiICD9Dlg::~CDiagnosiICD9Dlg()
{
	m_setDiagnosiICD9.CloseRecordset("CDiagnosiICD9Dlg::~CDiagnosiICD9Dlg");
}

void CDiagnosiICD9Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_00, m_ctrlList00);

	DDX_Control(pDX, IDOK,          m_ctrlButtonOK);
	DDX_Control(pDX, IDC_BTN_SAV,   m_ctrlButtonSav);
	DDX_Control(pDX, IDC_BTN_UND,   m_ctrlButtonUnd);
	DDX_Control(pDX, IDC_BTN_PRI,   m_ctrlButtonPri);
	DDX_Control(pDX, IDC_BTN_NEW,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT,   m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DLT,   m_ctrlButtonDlt);

	DDX_Control(pDX, IDC_FRAME_00, m_ctrlFrame00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
}

BEGIN_MESSAGE_MAP(CDiagnosiICD9Dlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_LIST_00, OnLbnSelchangeList00)
	ON_BN_CLICKED(IDC_BTN_SAV, OnBnClickedBtnSav)
	ON_BN_CLICKED(IDC_BTN_UND, OnBnClickedBtnUnd)
	ON_BN_CLICKED(IDC_BTN_PRI, OnBnClickedBtnPri)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DLT, OnBnClickedBtnDlt)
END_MESSAGE_MAP()

HBRUSH CDiagnosiICD9Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	/*switch(pWnd->GetDlgCtrlID())
	{
		case IDC_EDIT_01:
		case IDC_EDIT_02:
		case IDC_EDIT_03:
		case IDC_STATIC_01:
		case IDC_STATIC_02:
		case IDC_STATIC_03:
		case IDC_STATIC_04:
		{
			pDC->SetTextColor(theApp.m_color[0]);
		}
	}*/

	return hBrush;
}

BOOL CDiagnosiICD9Dlg::OnInitDialog() 
{
	BOOL bReturn = CDialog::OnInitDialog();
	
	GetDlgItem(IDC_EDIT_01)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_02)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_03)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_04)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_01)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_02)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_03)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_04)->SetFont(&theApp.m_fontBold);

	// -->
	int iIndex = 0;

	m_setDiagnosiICD9.SetSortRecord("Descrizione");
	if (m_setDiagnosiICD9.OpenRecordset("CDiagnosiICD9Dlg::OnInitDialog") == FALSE)
		return FALSE;

	while(m_setDiagnosiICD9.IsEOF() == FALSE)
	{
		m_ctrlList00.InsertString(iIndex, m_setDiagnosiICD9.m_sDescrizione);
		m_ctrlList00.SetItemData(iIndex, m_setDiagnosiICD9.m_lID);

		iIndex++;
		m_setDiagnosiICD9.MoveNext();
	}

	m_setDiagnosiICD9.SetSortRecord("ID");

	if (m_ctrlList00.GetCount() > 0)
	{
		m_ctrlList00.SetCurSel(0);
		OnLbnSelchangeList00();
	}
	// <--
	
	theApp.LocalizeDialog(this, CDiagnosiICD9Dlg::IDD, "DiagnosiICD9Dlg");
	return bReturn;
}

void CDiagnosiICD9Dlg::OnLbnSelchangeList00()
{
	int nCurSel = m_ctrlList00.GetCurSel();
	long lID = 0;

	if (nCurSel != LB_ERR)
	{
		CString strTemp;

		GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_DLT)->EnableWindow(TRUE);

		lID = m_ctrlList00.GetItemData(nCurSel);
		strTemp.Format("ID=%li", lID);
		m_setDiagnosiICD9.SetOpenFilter(strTemp);
		m_setDiagnosiICD9.OpenRecordset("CDiagnosiICD9Dlg::OnLbnSelchangeList00");

		VisualizzaDati();
	}
	else
	{
		GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DLT)->EnableWindow(FALSE);

		SvuotaDialog();
	}
}

void CDiagnosiICD9Dlg::CambiaModalita(int iNuovaModalita)
{
	GetDlgItem(IDC_LIST_00)->EnableWindow(iNuovaModalita == CORE_VISUA);
	GetDlgItem(IDC_BTN_PRI)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_NEW)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_EDT)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_DLT)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_SAV)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_BTN_UND)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_HIDE : SW_SHOW);

	SendDlgItemMessage(IDC_EDIT_01, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_02, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_03, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_04, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);

	m_iModalita = iNuovaModalita;
}

void CDiagnosiICD9Dlg::SvuotaDialog()
{
	SetDlgItemText(IDC_EDIT_01, "");
	SetDlgItemText(IDC_EDIT_02, "");
	SetDlgItemText(IDC_EDIT_03, "");
	SetDlgItemText(IDC_EDIT_04, "");
}

void CDiagnosiICD9Dlg::VisualizzaDati()
{
	if ((m_setDiagnosiICD9.IsOpen() == TRUE) && (m_setDiagnosiICD9.IsBOF() == FALSE) && (m_setDiagnosiICD9.IsEOF() == FALSE))
	{
		CString strTemp;

		SetDlgItemText(IDC_EDIT_01, m_setDiagnosiICD9.m_sDescrizione);
		SetDlgItemText(IDC_EDIT_02, m_setDiagnosiICD9.m_sCodificaInterna);
		SetDlgItemText(IDC_EDIT_03, m_setDiagnosiICD9.m_sCodificaICD9Interni);
		SetDlgItemText(IDC_EDIT_04, m_setDiagnosiICD9.m_sCodificaICD9Esterni);
	}
	else
	{
		SvuotaDialog();
	}
}

void CDiagnosiICD9Dlg::OnBnClickedBtnNew()
{
	SvuotaDialog();
	CambiaModalita(CORE_NUOVO);

	GetDlgItem(IDC_EDIT_01)->SetFocus();
}

void CDiagnosiICD9Dlg::OnBnClickedBtnEdt()
{
	CambiaModalita(CORE_MODIF);
}

void CDiagnosiICD9Dlg::OnBnClickedBtnDlt()
{
	int iTemp;
	CString strTmp1, strTmp2;

	iTemp = m_ctrlList00.GetCurSel();
	if (iTemp != LB_ERR)
	{
		m_ctrlList00.GetText(iTemp, strTmp1);
		strTmp2.Format(theApp.GetMessageString(IDS_CODREG_DELETE_CONFIRM), strTmp1);
		if (theApp.AfxMessageBoxEndo(strTmp2, MB_YESNO) == IDYES)
		{
			strTmp1.Format("ID=%li", m_ctrlList00.GetItemData(iTemp));
			m_setDiagnosiICD9.SetOpenFilter(strTmp1);

			m_setDiagnosiICD9.DeleteRecordset("CDiagnosiICD9Dlg::OnBnClickedBtnDlt");

			m_ctrlList00.DeleteString(iTemp);

			OnLbnSelchangeList00();
		}
	}
}

void CDiagnosiICD9Dlg::OnBnClickedBtnSav()
{
	CString strTemp;
	int iTemp;

	GetDlgItemText(IDC_EDIT_04, strTemp);
	if (strTemp.GetLength() < 1)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CODREG_ERR_DESC));
		return;
	}

	switch(m_iModalita)
	{
		case CORE_NUOVO:
		{
			m_setDiagnosiICD9.AddNewRecordset("CDiagnosiICD9Dlg::OnBnClickedBtnSav");

			break;
		}

		case CORE_MODIF:
		{
			m_setDiagnosiICD9.EditRecordset("CDiagnosiICD9Dlg::OnBnClickedBtnSav");

			break;
		}
	}

	GetDlgItemText(IDC_EDIT_01, m_setDiagnosiICD9.m_sDescrizione);
	GetDlgItemText(IDC_EDIT_02, m_setDiagnosiICD9.m_sCodificaInterna);
	GetDlgItemText(IDC_EDIT_03, m_setDiagnosiICD9.m_sCodificaICD9Interni);
	GetDlgItemText(IDC_EDIT_04, m_setDiagnosiICD9.m_sCodificaICD9Esterni);

	m_setDiagnosiICD9.UpdateRecordset("CDiagnosiICD9Dlg::OnBnClickedBtnSav");

	switch(m_iModalita)
	{
		case CORE_NUOVO:
		{
			m_setDiagnosiICD9.SetOpenFilter("");
			m_setDiagnosiICD9.OpenRecordset("CDiagnosiICD9Dlg::OnBnClickedBtnSav");
			m_setDiagnosiICD9.MoveLast();

			iTemp = m_ctrlList00.GetCount();
			GetDlgItemText(IDC_EDIT_01, strTemp);
			m_ctrlList00.InsertString(iTemp, strTemp);
			m_ctrlList00.SetItemData(iTemp, m_setDiagnosiICD9.m_lID);

			m_ctrlList00.SetCurSel(iTemp);
			OnLbnSelchangeList00();

			break;
		}

		case CORE_MODIF:
		{
			iTemp = m_ctrlList00.GetCurSel();
			m_ctrlList00.DeleteString(iTemp);

			m_ctrlList00.InsertString(iTemp, m_setDiagnosiICD9.m_sDescrizione);
			m_ctrlList00.SetItemData(iTemp, m_setDiagnosiICD9.m_lID);

			m_ctrlList00.SetCurSel(iTemp);
			OnLbnSelchangeList00();

			break;
		}
	}

	CambiaModalita(CORE_VISUA);
}

void CDiagnosiICD9Dlg::OnBnClickedBtnUnd()
{
	CambiaModalita(CORE_VISUA);
	VisualizzaDati();
}

void CDiagnosiICD9Dlg::OnBnClickedBtnPri()
{
	//Font grafico di default
	LOGFONT lfPrinterFont;
	
	memset(&lfPrinterFont, 0, sizeof(lfPrinterFont));
	lfPrinterFont.lfHeight 			= -10;
	lfPrinterFont.lfWeight 			= 400;
	lfPrinterFont.lfEscapement		= 0;   // orizzontale
	lfPrinterFont.lfOrientation		= 0;
	lfPrinterFont.lfWidth			= 0;
	lfPrinterFont.lfStrikeOut		= 0;
	lfPrinterFont.lfCharSet			= 0;
	lfPrinterFont.lfItalic			= 0;
	lfPrinterFont.lfUnderline		= 0;
	lfPrinterFont.lfOutPrecision	= 1;
	lfPrinterFont.lfClipPrecision	= 2;
	lfPrinterFont.lfQuality			= 1;
	lfPrinterFont.lfPitchAndFamily 	= 34;
	strcpy_s(lfPrinterFont.lfFaceName, "Arial");

//	if (m_pSet == NULL)
//		return;

	int nCounter = m_ctrlList00.GetCount();
			
	if (nCounter == LB_ERR)
		return;
	
	CMyPrintDialog printdlg (FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS |
								  PD_HIDEPRINTTOFILE | PD_NOSELECTION, this);

	if (printdlg.DoModal()==IDOK)
	{
		CDC 		prnDC ;   
		DOCINFO 	docInfo;
		CRect 		rectPage;
		TEXTMETRIC 	tm;
		CFont*		pFontOld;
		CFont		PrinterFont;
		CString		strTitle;
		CString		strValue;
		
		CCustomDate date(TRUE, TRUE);

		docInfo.cbSize			= sizeof (DOCINFO);
		docInfo.lpszDocName		= theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_387);
		docInfo.lpszOutput		= NULL;                       
		docInfo.lpszDatatype	= NULL;
		docInfo.fwType			= 0;
			
		prnDC.Attach(printdlg.GetPrinterDC());
        prnDC.StartDoc(&docInfo);
	        
		rectPage.SetRect(150, 0, prnDC.GetDeviceCaps(HORZRES), prnDC.GetDeviceCaps(VERTRES));
		prnDC.DPtoLP(&rectPage);
			    
		// create new font.
		int 	rapXP = prnDC.GetDeviceCaps(LOGPIXELSX);
		int 	rapYP = prnDC.GetDeviceCaps(LOGPIXELSY);
	
		//CClientDC	dcForm(this);
    	int 	rapXV = 72; //dcForm.GetDeviceCaps(LOGPIXELSX);
		int		rapYV = 72; //dcForm.GetDeviceCaps(LOGPIXELSY);

		// calcola il font per la stampante
		lfPrinterFont.lfHeight = ::MulDiv(lfPrinterFont.lfHeight, rapYP, rapYV);
		lfPrinterFont.lfWidth  = ::MulDiv(lfPrinterFont.lfWidth,  rapXP, rapXV);

		PrinterFont.CreateFontIndirect(&lfPrinterFont);

		pFontOld = prnDC.SelectObject(&PrinterFont);
	
		prnDC.GetTextMetrics(&tm);

		int nCYChar			= tm.tmHeight + tm.tmExternalLeading;
		int nLinesPerPage	= (prnDC.GetDeviceCaps(VERTRES) / nCYChar) - 2;
		int nPage			= (nCounter-1) / nLinesPerPage + 1;
		int	nL				= 0;
		
		while (nL<nCounter)
		{
			for(int nP=1; nP<=nPage; nP++)
			{
				int		nLine = 0;
				CRect	rect  = CRect(rectPage.left, nLine * nCYChar, rectPage.right, (nLine+1) * nCYChar);

				prnDC.StartPage();
		
				prnDC.SetTextAlign(TA_LEFT);
				prnDC.TextOut (rect.left, rect.top, date.GetDate("%d/%m/%Y %H:%M"));
				prnDC.SetTextAlign(TA_CENTER);
				prnDC.TextOut ((rect.left + rectPage.right)/2, rect.top, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_387));
					
				nLine++;
				prnDC.MoveTo(rectPage.left, nLine * nCYChar + (nCYChar / 2));
				prnDC.LineTo(rectPage.right, nLine * nCYChar + (nCYChar / 2));
			
				while (nL<nCounter && nL<(nP*nLinesPerPage))
				{
					m_ctrlList00.GetText(nL, strValue);
					nL++;
				
					if (strValue != "")
					{
						nLine++;
			
						rect = CRect(rectPage.left, nLine * nCYChar, rectPage.right, (nLine+1) * nCYChar);
					
						prnDC.SetTextAlign(TA_LEFT);
						prnDC.TextOut (rect.left, rect.top, strValue);
					}
					
				}
			
				prnDC.EndPage();
			}
		}
	    
		prnDC.EndDoc();  
		        
		prnDC.SelectObject(pFontOld);
	    prnDC.DeleteDC();
		        
		::GlobalFree (printdlg.m_pd.hDevMode);
		::GlobalFree (printdlg.m_pd.hDevNames);
	}
}
