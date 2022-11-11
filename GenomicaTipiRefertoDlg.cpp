#include "stdafx.h"
#include "Endox.h"
#include "Common.h"
#include "GenomicaTipiRefertoDlg.h"
#include "TipiRefertoSet.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaTipiRefertoDlg, CDialog)

enum
{
	id_rtf1,
	id_rtf2,
	id_rtf3,
	id_rtf4,
	id_rtf5,
	id_rtf6,
	id_rtf7,
	id_rtf8,
	id_rtf9,
	id_rtf10,
	id_ENDLOOP
};

CGenomicaTipiRefertoDlg::CGenomicaTipiRefertoDlg(CWnd* pParent)
	: CDialog(CGenomicaTipiRefertoDlg::IDD, pParent)
{
	m_lIDSelected = -1;			
	m_lFamiglia = 0;
	
	ResetMemoryRtfs();
}

CGenomicaTipiRefertoDlg::~CGenomicaTipiRefertoDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaTipiRefertoDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
	ON_NOTIFY(TCN_SELCHANGE, IDC_FAMIGLIA, OnSelchangeFamiglia)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

	ON_COMMAND(IDC_RTF_TABLE, OnBnClickedBtnRtfNewTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, OnBnClickedBtnRtfMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, OnBnClickedBtnRtfMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, OnBnClickedBtnRtfMakeLower)
	ON_COMMAND(IDC_RTF_FONT, OnBnClickedBtnRtfFont) //Julio - BUG 4392 Edicao de texto
END_MESSAGE_MAP()

void CGenomicaTipiRefertoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);	
	DDX_Control(pDX, IDC_FAMIGLIA, m_ctrlFamiglia);
	
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);	

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);
	DDX_Control(pDX, IDC_BUTTONBAR_TAB, m_ctrlButtonBarTab);

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	DDX_Control(pDX, IDC_TEXTCONTROL2, m_ctrlTextControlTab);
	m_ctrlTextControlTab.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
}

BOOL CGenomicaTipiRefertoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);

	RiempiLista();

	m_ctrlToolbarTab.Create(IDC_BUTTONBAR_PLACE, this);
	m_ctrlToolbarTab.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowLong(m_ctrlButtonBarTab.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBarTab.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	//
	m_ctrlTextControlTab.SetButtonBarHandle((long)m_ctrlButtonBarTab.GetSafeHwnd());
	m_ctrlTextControlTab.SetFontName(g_sReportFaceName);
	m_ctrlTextControlTab.SetFontSize(g_nReportSize);
	m_ctrlTextControlTab.SetFontBold(g_bReportBold);
	m_ctrlTextControlTab.SetFontItalic(g_bReportItalic);
	m_ctrlTextControlTab.SetFontUnderline(g_bReportUnderline);

	m_ctrlToolbarTab.EnableWindow(FALSE);
	m_ctrlButtonBarTab.EnableWindow(FALSE);
	m_ctrlTextControlTab.EnableWindow(FALSE);
	//

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetFontName(g_sReportFaceName);
	m_ctrlTextControl.SetFontSize(g_nReportSize);
	m_ctrlTextControl.SetFontBold(g_bReportBold);
	m_ctrlTextControl.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

	m_ctrlTextControl.EnableWindow(FALSE);
	m_ctrlButtonBar.EnableWindow(FALSE);

	SetupCtrlFamiglia();

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CGenomicaTipiRefertoDlg::IDD, "CGenomicaTipiRefertoDlg");
	return TRUE;
}

void CGenomicaTipiRefertoDlg::SetupCtrlFamiglia()
{
	//Populating the tab control	
	int nItem = 0;
	CString sTextTemp;
	TC_ITEM TabCtrlItem;

	sTextTemp = "1";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf1;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "2";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf2;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "3";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf3;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "4";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf4;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "5";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf5;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "6";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf6;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "7";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf7;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "8";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf8;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "9";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf9;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	sTextTemp = "10";
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_rtf10;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	m_ctrlFamiglia.EnableWindow(FALSE);
	//
}

void CGenomicaTipiRefertoDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CGenomicaTipiRefertoDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaTipiRefertoDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<long> listID;
	CTipiRefertoSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CTipiRefertoSet().GetCodice(lID));
		m_ctrlList.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGenomicaTipiRefertoDlg::CaricaDati()
{
	m_ctrlFamiglia.SetCurSel(0);
	m_lFamiglia = 0;

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_CODICE, "");	
	m_ctrlTextControl.ResetContents();
	m_ctrlTextControlTab.ResetContents();

	//

	SetDlgItemText(IDC_CODICE, CTipiRefertoSet().GetCodice(m_lIDSelected));	
	m_ctrlTextControl.SetRTFSelText(CTipiRefertoSet().GetTitolo(m_lIDSelected));
	m_ctrlTextControlTab.SetRTFSelText(CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 1));

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CGenomicaTipiRefertoDlg::UnselectAll()
{
	if (m_ctrlList.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
			m_ctrlList.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedList(NULL, NULL);
	}
			
	ResetMemoryRtfs();

}

void CGenomicaTipiRefertoDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);	
	
	m_ctrlTextControl.EnableWindow(bEdit);	
	m_ctrlButtonBar.EnableWindow(bEdit);
	
	m_ctrlTextControlTab.EnableWindow(bEdit);	
	m_ctrlButtonBarTab.EnableWindow(bEdit);
	m_ctrlToolbarTab.EnableWindow(bEdit);

	m_ctrlFamiglia.EnableWindow(bEdit);
	
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);	
}


// CGenomicaTipiVariantiDlg message handlers
void CGenomicaTipiRefertoDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (!CTipiRefertoSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnSave()
{
	if (!UpdateData(TRUE))
		return;

	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);

	for (int i = 0; i < id_ENDLOOP; i++)
	{
		m_ctrlFamiglia.SetCurSel(i);
		OnSelchangeFamiglia(NULL, NULL);
	}


	CString strTemp;

	GetDlgItemText(IDC_CODICE, strTemp);
	strTemp.Trim();

	if (!strTemp.IsEmpty())
	{
		if (m_lIDSelected <= 0)
		{
			// addnew //
			CTipiRefertoSet setTemp;
			setTemp.SetOpenFilter("");
			if (setTemp.OpenRecordset("CGenomicaTipiRefertoDlg::OnBnClickedBtnSave"))
			{
				if (setTemp.AddNewRecordset("CGenomicaTipiRefertoDlg::OnBnClickedBtnSave"))
				{
					GetDlgItemText(IDC_CODICE, setTemp.m_sCodice);
					
					setTemp.m_sTitoloRtf = m_ctrlTextControl.GetRTFSelText();
					setTemp.m_sTestoRtf001 = m_sTestoRtf1;
					setTemp.m_sTestoRtf002 = m_sTestoRtf2;
					setTemp.m_sTestoRtf003 = m_sTestoRtf3;
					setTemp.m_sTestoRtf004 = m_sTestoRtf4;
					setTemp.m_sTestoRtf005 = m_sTestoRtf5;
					setTemp.m_sTestoRtf006 = m_sTestoRtf6;
					setTemp.m_sTestoRtf007 = m_sTestoRtf7;
					setTemp.m_sTestoRtf008 = m_sTestoRtf8;
					setTemp.m_sTestoRtf009 = m_sTestoRtf9;
					setTemp.m_sTestoRtf010 = m_sTestoRtf10;
					setTemp.m_bEliminato = FALSE;

					setTemp.UpdateRecordset("CGenomicaTipiRefertoDlg::OnBnClickedBtnSave");
				}
				setTemp.CloseRecordset("CGenomicaTipiRefertoDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			CString sCodice;
			GetDlgItemText(IDC_CODICE, sCodice);
			CTipiRefertoSet().SetCodice(m_lIDSelected, sCodice);

			CTipiRefertoSet().SetTitolo(m_lIDSelected, m_ctrlTextControl.GetRTFSelText());

			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 1, m_sTestoRtf1);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 2, m_sTestoRtf2);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 3, m_sTestoRtf3);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 4, m_sTestoRtf4);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 5, m_sTestoRtf5);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 6, m_sTestoRtf6);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 7, m_sTestoRtf7);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 8, m_sTestoRtf8);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 9, m_sTestoRtf9);
			CTipiRefertoSet().SetTestoRtf(m_lIDSelected, 10, m_sTestoRtf10);
		}

		UnselectAll();
		RiempiLista();
		EditDialog(FALSE);
	}
	else
	{
		AfxMessageBox(theApp.GetMessageString(IDS_INSERT_DESCRIPTION_BEFORE_CONTINUE), MB_ICONSTOP);
	}
}

void CGenomicaTipiRefertoDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControlTab.RtfInsertNewTable(this);
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControlTab.RtfSelectedTextMakeUpper();
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControlTab.RtfSelectedTextMakeNormal();
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControlTab.RtfSelectedTextMakeLower();
}

void CGenomicaTipiRefertoDlg::OnBnClickedBtnRtfFont() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlTextControl.RtfSetFontProperties();
}

void CGenomicaTipiRefertoDlg::OnSelchangeFamiglia(NMHDR* pNMHDR, LRESULT* pResult)
{
	SaveRtfsToMemory();

	CString sValue;

	int nCurSel = m_ctrlFamiglia.GetCurSel();
	if (nCurSel >= 0)
	{
		TCITEM tcTemp;
		tcTemp.mask = TCIF_PARAM;
		m_ctrlFamiglia.GetItem(nCurSel, &tcTemp);

		m_lFamiglia = tcTemp.lParam;
		switch (m_lFamiglia)
		{
		case id_rtf1:
		{	
			sValue = m_sTestoRtf1.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 1)
				: m_sTestoRtf1;
			
			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf1);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf1);
			break;
		}
		case id_rtf2:
		{
			sValue = m_sTestoRtf2.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 2)
				: m_sTestoRtf2;			
			
			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf2);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf2);
			break;
		}
		case id_rtf3:
		{
			sValue = m_sTestoRtf3.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 3)
				: m_sTestoRtf3;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf3);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf3);
			break;
		}
		case id_rtf4:
		{
			sValue = m_sTestoRtf4.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 4)
				: m_sTestoRtf4;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf4);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf4);
			break;
		}
		case id_rtf5:
		{
			sValue = m_sTestoRtf5.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 5)
				: m_sTestoRtf5;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf5);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf5);
			break;
		}
		case id_rtf6:
		{
			sValue = m_sTestoRtf6.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 6)
				: m_sTestoRtf6;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf6);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf6);
			break;
		}
		case id_rtf7:
		{
			sValue = m_sTestoRtf7.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 7)
				: m_sTestoRtf7;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf7);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf7);
			break;
		}
		case id_rtf8:
		{
			sValue = m_sTestoRtf8.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 8)
				: m_sTestoRtf8;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf8);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf8);
			break;
		}
		case id_rtf9:
		{
			sValue = m_sTestoRtf9.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 9)
				: m_sTestoRtf9;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf9);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf9);
			break;
		}
		case id_rtf10:
		{
			sValue = m_sTestoRtf10.IsEmpty()
				? CTipiRefertoSet().GetTestoRtf(m_lIDSelected, 10)
				: m_sTestoRtf10;

			m_ctrlTextControlTab.SetFontName(m_sFontNameRtf10);
			m_ctrlTextControlTab.SetFontSize(m_nFontSizeRtf10);
			break;
		}
		default:		
			break;		
		}

		if (sValue.IsEmpty()) m_ctrlTextControlTab.ResetContents();
		else m_ctrlTextControlTab.SetRTFSelText(sValue);
	}
}

void CGenomicaTipiRefertoDlg::SaveRtfsToMemory()
{
	m_ctrlTextControlTab.SetSelStart(0);
	m_ctrlTextControlTab.SetSelLength(-1);

	if (m_lFamiglia == id_rtf1)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf1 = m_ctrlTextControlTab.GetRTFSelText();
		
		m_sFontNameRtf1 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf1 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf2)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf2 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf2 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf2 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf3)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf3 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf3 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf3 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf4)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf4 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf4 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf4 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf5)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf5 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf5 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf5 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf6)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf6 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf6 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf6 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf7)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf7 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf7 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf7 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf8)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf8 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf8 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf8 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf9)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf9 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf9 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf9 = m_ctrlTextControlTab.GetFontSize();
	}
	if (m_lFamiglia == id_rtf10)
	{
		if (!m_ctrlTextControlTab.GetSelText().IsEmpty())
			m_sTestoRtf10 = m_ctrlTextControlTab.GetRTFSelText();

		m_sFontNameRtf10 = m_ctrlTextControlTab.GetFontName();
		m_nFontSizeRtf10 = m_ctrlTextControlTab.GetFontSize();
	}

}

void CGenomicaTipiRefertoDlg::ResetMemoryRtfs()
{
	m_sFontNameRtf1 = m_sFontNameRtf2 = m_sFontNameRtf3 = m_sFontNameRtf4 =
		m_sFontNameRtf5 = m_sFontNameRtf6 = m_sFontNameRtf7 =
		m_sFontNameRtf8 = m_sFontNameRtf9 = m_sFontNameRtf10 = g_sReportFaceName;

	m_nFontSizeRtf1 = m_nFontSizeRtf2 = m_nFontSizeRtf3 = m_nFontSizeRtf4 =
		m_nFontSizeRtf5 = m_nFontSizeRtf6 = m_nFontSizeRtf7 =
		m_nFontSizeRtf8 = m_nFontSizeRtf9 = m_nFontSizeRtf10 = g_nReportSize;

	m_sTestoRtf1 = m_sTestoRtf2 = m_sTestoRtf3 = m_sTestoRtf4 =
		m_sTestoRtf5 = m_sTestoRtf6 = m_sTestoRtf7 =
		m_sTestoRtf8 = m_sTestoRtf9 = m_sTestoRtf10 = "";
}