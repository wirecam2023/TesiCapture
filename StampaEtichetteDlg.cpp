#include "stdafx.h"
#include "Endox.h"
#include "StampaEtichetteDlg.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "MyPrintDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CStampaEtichetteDlg, CDialog)

CStampaEtichetteDlg::CStampaEtichetteDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CStampaEtichetteDlg::IDD, pParent)
{
}

CStampaEtichetteDlg::~CStampaEtichetteDlg()
{
}

BEGIN_MESSAGE_MAP(CStampaEtichetteDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD_3, OnBnClickedBtnAdd3)
	ON_BN_CLICKED(IDC_BTN_REM_3, OnBnClickedBtnRem3)
	ON_BN_CLICKED(IDC_BTN_ADD_6, OnBnClickedBtnAdd6)
	ON_BN_CLICKED(IDC_BTN_REM_6, OnBnClickedBtnRem6)
	ON_BN_CLICKED(IDC_BTN_ADD_9, OnBnClickedBtnAdd9)
	ON_BN_CLICKED(IDC_BTN_REM_9, OnBnClickedBtnRem9)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

void CStampaEtichetteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK,     m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_LIST_PAZIENTI, m_ctrlListPazienti);
	DDX_Control(pDX, IDC_LIST_STAMPA_3, m_ctrlListStampa3);
	DDX_Control(pDX, IDC_LIST_STAMPA_6, m_ctrlListStampa6);
	DDX_Control(pDX, IDC_LIST_STAMPA_9, m_ctrlListStampa9);
}

BOOL CStampaEtichetteDlg::OnInitDialog() 
{
	int nIndex = 0;
	CString strTemp;
	CCustomDate dateTemp;

	CDialog::OnInitDialog();

	m_ctrlListPazienti.SetExtendedStyle(m_ctrlListPazienti.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlListStampa3.SetExtendedStyle(m_ctrlListStampa3.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlListStampa6.SetExtendedStyle(m_ctrlListStampa6.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlListStampa9.SetExtendedStyle(m_ctrlListStampa9.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);

	m_ctrlListPazienti.InsertColumn(0, "Lista dei pazienti", LVCFMT_LEFT, 242);
	m_ctrlListStampa3.InsertColumn(0, "3 etichette", LVCFMT_LEFT, 242);
	m_ctrlListStampa6.InsertColumn(0, "6 etichette", LVCFMT_LEFT, 242);
	m_ctrlListStampa9.InsertColumn(0, "9 etichette", LVCFMT_LEFT, 242);

	m_setPazienti.SetSortRecord("Cognome, Nome, NatoIlCustom");
	m_setPazienti.OpenRecordset("CStampaEtichetteDlg::OnInitDialog");

	BeginWaitCursor();
	while(m_setPazienti.IsEOF() == FALSE)
	{
		strTemp = "";

		if (m_setPazienti.IsFieldNull(&m_setPazienti.m_lNatoIlCustom) == FALSE)
			dateTemp.SetDate(m_setPazienti.m_lNatoIlCustom);
		else
			dateTemp.SetDate(0L);

		if (m_setPazienti.IsFieldNull(&m_setPazienti.m_sCognome) == FALSE)
			strTemp = m_setPazienti.m_sCognome;
		if (strTemp.IsEmpty() == FALSE)
			strTemp += " ";
		if (m_setPazienti.IsFieldNull(&m_setPazienti.m_sNome) == FALSE)
			strTemp = strTemp + m_setPazienti.m_sNome;

//		strTemp.TrimLeft(); // Sandro Gallina - 10/06/2004 //
//		strTemp.TrimRight(); // Sandro Gallina - 07/07/2004 //
		if (strTemp.IsEmpty() == FALSE)
		{
			m_ctrlListPazienti.InsertItem(nIndex, strTemp + " " + dateTemp.GetDate("%d/%m/%Y"));
			m_ctrlListPazienti.SetItemData(nIndex, (DWORD)m_setPazienti.m_lContatore);

			nIndex++;
		}

		m_setPazienti.MoveNext();
	}
	EndWaitCursor();

	m_setPazienti.CloseRecordset("CStampaEtichetteDlg::OnInitDialog");
	theApp.LocalizeDialog(this, CStampaEtichetteDlg::IDD, "StampaEtichetteDlg");

	return TRUE;
}

void CStampaEtichetteDlg::OnBnClickedBtnAdd3()
{
	POSITION pos = m_ctrlListPazienti.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nSelItem = m_ctrlListPazienti.GetNextSelectedItem(pos);
		int nInsItem = m_ctrlListStampa3.GetItemCount();

		m_ctrlListStampa3.InsertItem(nInsItem, m_ctrlListPazienti.GetItemText(nSelItem, 0));
		m_ctrlListStampa3.SetItemData(nInsItem, m_ctrlListPazienti.GetItemData(nSelItem));
	}
}

void CStampaEtichetteDlg::OnBnClickedBtnRem3()
{
	POSITION pos = m_ctrlListStampa3.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nSelItem = m_ctrlListStampa3.GetNextSelectedItem(pos);

		m_ctrlListStampa3.DeleteItem(nSelItem);
	}
}

void CStampaEtichetteDlg::OnBnClickedBtnAdd6()
{
	POSITION pos = m_ctrlListPazienti.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nSelItem = m_ctrlListPazienti.GetNextSelectedItem(pos);
		int nInsItem = m_ctrlListStampa6.GetItemCount();

		m_ctrlListStampa6.InsertItem(nInsItem, m_ctrlListPazienti.GetItemText(nSelItem, 0));
		m_ctrlListStampa6.SetItemData(nInsItem, m_ctrlListPazienti.GetItemData(nSelItem));
	}
}

void CStampaEtichetteDlg::OnBnClickedBtnRem6()
{
	POSITION pos = m_ctrlListStampa6.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nSelItem = m_ctrlListStampa6.GetNextSelectedItem(pos);

		m_ctrlListStampa6.DeleteItem(nSelItem);
	}
}

void CStampaEtichetteDlg::OnBnClickedBtnAdd9()
{
	POSITION pos = m_ctrlListPazienti.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nSelItem = m_ctrlListPazienti.GetNextSelectedItem(pos);
		int nInsItem = m_ctrlListStampa9.GetItemCount();

		m_ctrlListStampa9.InsertItem(nInsItem, m_ctrlListPazienti.GetItemText(nSelItem, 0));
		m_ctrlListStampa9.SetItemData(nInsItem, m_ctrlListPazienti.GetItemData(nSelItem));
	}
}

void CStampaEtichetteDlg::OnBnClickedBtnRem9()
{
	POSITION pos = m_ctrlListStampa9.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nSelItem = m_ctrlListStampa9.GetNextSelectedItem(pos);

		m_ctrlListStampa9.DeleteItem(nSelItem);
	}
}
void CStampaEtichetteDlg::OnBnClickedOk()
{
	int nRighe = m_ctrlListStampa3.GetItemCount() + (m_ctrlListStampa6.GetItemCount() * 2) + (m_ctrlListStampa9.GetItemCount() * 3);
	int nFogli = nRighe / 8;
	CString strTemp;
	BOOL bResult = FALSE;

	if (nRighe % 8 != 0)
		nFogli++;

	if (nRighe > 0)
	{
		strTemp.Format(theApp.GetMessageString(IDS_STAMPAETICHETTEDLG_SHEET_NUM), nFogli);
		if (theApp.AfxMessageBoxEndo(strTemp, MB_OKCANCEL) == IDOK)
			bResult = StampaEtichette();
	}
	
	if (bResult == TRUE)
		OnOK();
}

BOOL CStampaEtichetteDlg::StampaEtichette()
{
    CMyPrintDialog printDlg(FALSE);
	CDC dc;

    if (printDlg.DoModal() != IDOK)
        return FALSE;

    dc.Attach(printDlg.GetPrinterDC());
    dc.m_bPrinting = TRUE;

	DOCINFO di;
	memset(&di, 0, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = theApp.m_sNomeProgramma + " - Stampa etichette";
    BOOL bPrintingOK = dc.StartDoc(&di);

	CClientDC dcForm(this);
	int rapXP = dc.GetDeviceCaps(LOGPIXELSX);
	int rapYP = dc.GetDeviceCaps(LOGPIXELSY);
	int rapXV = dcForm.GetDeviceCaps(LOGPIXELSX);
	int	rapYV = dcForm.GetDeviceCaps(LOGPIXELSY);

	CFont fontNormal;
	LOGFONT lfFont;

	lfFont.lfWidth		    = 0;
	lfFont.lfEscapement	    = 0;
	lfFont.lfOrientation	= 0;
	lfFont.lfStrikeOut	    = FALSE;
	lfFont.lfCharSet		= DEFAULT_CHARSET;
	lfFont.lfOutPrecision   = OUT_DEFAULT_PRECIS;
	lfFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
	lfFont.lfQuality		= DEFAULT_QUALITY;
	lfFont.lfPitchAndFamily = DEFAULT_PITCH + FF_DONTCARE;
	lfFont.lfHeight 		= 14;
	lfFont.lfWeight 		= FW_NORMAL;
	lfFont.lfItalic 		= FALSE;
	lfFont.lfUnderline 	    = FALSE;
	strcpy_s(lfFont.lfFaceName, "Tahoma");

	lfFont.lfHeight = (int)(((float)lfFont.lfHeight * (float)rapYP) / (float)rapYV);

	fontNormal.CreateFontIndirect(&lfFont);

	int nRiga = 0, i, j;
	POINT ptTemp;
	SIZE szTemp;
	CString strTemp;
	CCustomDate dateTemp;

	/////////////////
	// 3 etichette //
	/////////////////

	for(i = 0; i < m_ctrlListStampa3.GetItemCount(); i++)
	{
		strTemp.Format("Contatore=%li", (long)m_ctrlListStampa3.GetItemData(i));
		m_setPazienti.SetOpenFilter(strTemp);
		m_setPazienti.OpenRecordset("CStampaEtichetteDlg::StampaEtichette");
		if (m_setPazienti.IsEOF() == FALSE)
		{
			for(j = 0; j < 3; j++)
			{
				if (m_setPazienti.IsFieldNull(&m_setPazienti.m_lNatoIlCustom) == FALSE)
					dateTemp.SetDate(m_setPazienti.m_lNatoIlCustom);
				else
					dateTemp.SetDate(0L);

				szTemp.cx = (long)(((3.5f * theApp.m_fEtichette02) / 2.54f) * (float)rapXP);
				szTemp.cy = (long)(((0.45f * theApp.m_fEtichette03) / 2.54f) * (float)rapYP);

				// Stampa codice sanitario //
				ptTemp.x = (long)((((7.0f * theApp.m_fEtichette02 * (float)j) + theApp.m_fEtichette00) / 2.54f) * (float)rapXP);
				ptTemp.y = (long)((((3.6f * theApp.m_fEtichette03 * (float)(nRiga % 8)) + theApp.m_fEtichette01) / 2.54f) * (float)rapYP);
				dc.DrawText(m_setPazienti.m_sCodSanit, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);
				
				// Stampa data di nascita //
				ptTemp.x += szTemp.cx;
				dc.DrawText(dateTemp.GetDate("%d/%m/%Y"), CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Setto la larghezza intera per le scritte //
				szTemp.cx = (long)(((7.0f * theApp.m_fEtichette02) / 2.54f) * (float)rapXP);
				ptTemp.x = (long)((((7.0f * theApp.m_fEtichette02 * (float)j) + theApp.m_fEtichette00) / 2.54f) * (float)rapXP);

				// Stampa codice fiscale //
				ptTemp.y += szTemp.cy;
				dc.DrawText(m_setPazienti.m_sCodFisc, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa di cognome e nome //
				ptTemp.y += (szTemp.cy * 2);
				dc.DrawText(m_setPazienti.m_sCognome + " " + m_setPazienti.m_sNome, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa della via //
				ptTemp.y += szTemp.cy;
				dc.DrawText("VIA " + m_setPazienti.m_sVia, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa di CAP + città + provincia // 
				CString strTemp = m_setPazienti.m_sCAP + " " + m_setPazienti.m_sCitta;
				strTemp.Trim();
				if (m_setPazienti.m_sProvincia.GetLength() > 0)
					strTemp += " (" + m_setPazienti.m_sProvincia + ")";
				strTemp.Trim();
				ptTemp.y += szTemp.cy;
				dc.DrawText(strTemp, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);
			}
		}
		m_setPazienti.CloseRecordset("CStampaEtichetteDlg::StampaEtichette");

		nRiga++;

		if (nRiga % 8 == 0)
		{
			dc.EndPage();
			dc.StartPage();
		}
	}

	/////////////////
	// 6 etichette //
	/////////////////

	for(i = 0; i < m_ctrlListStampa6.GetItemCount() * 2; i++)
	{
		strTemp.Format("Contatore=%li", (long)m_ctrlListStampa6.GetItemData(i / 2));
		m_setPazienti.SetOpenFilter(strTemp);
		m_setPazienti.OpenRecordset("CStampaEtichetteDlg::StampaEtichette");
		if (m_setPazienti.IsEOF() == FALSE)
		{
			for(j = 0; j < 3; j++)
			{
				if (m_setPazienti.IsFieldNull(&m_setPazienti.m_lNatoIlCustom) == FALSE)
					dateTemp.SetDate(m_setPazienti.m_lNatoIlCustom);
				else
					dateTemp.SetDate(0L);

				szTemp.cx = (long)(((3.5f * theApp.m_fEtichette02) / 2.54f) * (float)rapXP);
				szTemp.cy = (long)(((0.45f * theApp.m_fEtichette03) / 2.54f) * (float)rapYP);

				// Stampa codice sanitario //
				ptTemp.x = (long)((((7.0f * theApp.m_fEtichette02 * (float)j) + theApp.m_fEtichette00) / 2.54f) * (float)rapXP);
				ptTemp.y = (long)((((3.6f * theApp.m_fEtichette03 * (float)(nRiga % 8)) + theApp.m_fEtichette01) / 2.54f) * (float)rapYP);
				dc.DrawText(m_setPazienti.m_sCodSanit, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);
				
				// Stampa data di nascita //
				ptTemp.x += szTemp.cx;
				dc.DrawText(dateTemp.GetDate("%d/%m/%Y"), CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Setto la larghezza intera per le scritte //
				szTemp.cx = (long)(((7.0f * theApp.m_fEtichette02) / 2.54f) * (float)rapXP);
				ptTemp.x = (long)((((7.0f * theApp.m_fEtichette02 * (float)j) + theApp.m_fEtichette00) / 2.54f) * (float)rapXP);

				// Stampa codice fiscale //
				ptTemp.y += szTemp.cy;
				dc.DrawText(m_setPazienti.m_sCodFisc, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa di cognome e nome //
				ptTemp.y += (szTemp.cy * 2);
				dc.DrawText(m_setPazienti.m_sCognome + " " + m_setPazienti.m_sNome, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa della via //
				ptTemp.y += szTemp.cy;
				dc.DrawText("VIA " + m_setPazienti.m_sVia, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa di CAP + città + provincia // 
				CString strTemp = m_setPazienti.m_sCAP + " " + m_setPazienti.m_sCitta;
				strTemp.Trim();
				if (m_setPazienti.m_sProvincia.GetLength() > 0)
					strTemp += " (" + m_setPazienti.m_sProvincia + ")";
				strTemp.Trim();
				ptTemp.y += szTemp.cy;
				dc.DrawText(strTemp, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);
			}
		}
		m_setPazienti.CloseRecordset("CStampaEtichetteDlg::StampaEtichette");

		nRiga++;

		if (nRiga % 8 == 0)
		{
			dc.EndPage();
			dc.StartPage();
		}
	}

	/////////////////
	// 9 etichette //
	/////////////////

	for(i = 0; i < m_ctrlListStampa9.GetItemCount() * 3; i++)
	{
		strTemp.Format("Contatore=%li", (long)m_ctrlListStampa9.GetItemData(i / 3));
		m_setPazienti.SetOpenFilter(strTemp);
		m_setPazienti.OpenRecordset("CStampaEtichetteDlg::StampaEtichette");
		if (m_setPazienti.IsEOF() == FALSE)
		{
			for(j = 0; j < 3; j++)
			{
				if (m_setPazienti.IsFieldNull(&m_setPazienti.m_lNatoIlCustom) == FALSE)
					dateTemp.SetDate(m_setPazienti.m_lNatoIlCustom);
				else
					dateTemp.SetDate(0L);

				szTemp.cx = (long)(((3.5f * theApp.m_fEtichette02) / 2.54f) * (float)rapXP);
				szTemp.cy = (long)(((0.45f * theApp.m_fEtichette03) / 2.54f) * (float)rapYP);

				// Stampa codice sanitario //
				ptTemp.x = (long)((((7.0f * theApp.m_fEtichette02 * (float)j) + theApp.m_fEtichette00) / 2.54f) * (float)rapXP);
				ptTemp.y = (long)((((3.6f * theApp.m_fEtichette03 * (float)(nRiga % 8)) + theApp.m_fEtichette01) / 2.54f) * (float)rapYP);
				dc.DrawText(m_setPazienti.m_sCodSanit, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);
				
				// Stampa data di nascita //
				ptTemp.x += szTemp.cx;
				dc.DrawText(dateTemp.GetDate("%d/%m/%Y"), CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Setto la larghezza intera per le scritte //
				szTemp.cx = (long)(((7.0f * theApp.m_fEtichette02) / 2.54f) * (float)rapXP);
				ptTemp.x = (long)((((7.0f * theApp.m_fEtichette02 * (float)j) + theApp.m_fEtichette00) / 2.54f) * (float)rapXP);

				// Stampa codice fiscale //
				ptTemp.y += szTemp.cy;
				dc.DrawText(m_setPazienti.m_sCodFisc, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa di cognome e nome //
				ptTemp.y += (szTemp.cy * 2);
				dc.DrawText(m_setPazienti.m_sCognome + " " + m_setPazienti.m_sNome, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa della via //
				ptTemp.y += szTemp.cy;
				dc.DrawText("VIA " + m_setPazienti.m_sVia, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);

				// Stampa di CAP + città + provincia // 
				CString strTemp = m_setPazienti.m_sCAP + " " + m_setPazienti.m_sCitta;
				strTemp.Trim();
				if (m_setPazienti.m_sProvincia.GetLength() > 0)
					strTemp += " (" + m_setPazienti.m_sProvincia + ")";
				strTemp.Trim();
				ptTemp.y += szTemp.cy;
				dc.DrawText(strTemp, CRect(ptTemp, szTemp), DT_EXPANDTABS|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);
			}
		}
		m_setPazienti.CloseRecordset("CStampaEtichetteDlg::StampaEtichette");

		nRiga++;

		if (nRiga % 8 == 0)
		{
			dc.EndPage();
			dc.StartPage();
		}
	}

    if (bPrintingOK)
        dc.EndDoc();
    else
        dc.AbortDoc();

    dc.Detach();

	return TRUE;
}