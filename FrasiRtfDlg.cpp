#include "stdafx.h"
#include "Endox.h"
#include "FrasiRtfDlg.h"

#include "Common.h"
#include "FrasiRtfSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrasiRtfDlg, CDialog)

CFrasiRtfDlg::CFrasiRtfDlg(CWnd* pParent)
	: CDialog(CFrasiRtfDlg::IDD, pParent)
{
	m_bProcessOnEnChange = FALSE;	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
}
  
CFrasiRtfDlg::~CFrasiRtfDlg()
{
}

BEGIN_MESSAGE_MAP(CFrasiRtfDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_BTN_CHIUDI, OnBnClickedBtnChiudi)

	ON_COMMAND(IDC_RTF_TABLE, OnBnClickedBtnRtfNewTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, OnBnClickedBtnRtfMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, OnBnClickedBtnRtfMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, OnBnClickedBtnRtfMakeLower)

	ON_EN_CHANGE(IDC_EDIT_RTF_CODICE, OnEnChangeEditRtfCodiceFrase)
	ON_EN_CHANGE(IDC_EDIT_RTF_FRASE,  OnEnChangeEditRtfCodiceFrase)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FRASIRTF, OnLvnItemchangedListFrasiRtf)

	ON_EN_SETFOCUS(IDC_EDIT_RTF_CODICE, &CFrasiRtfDlg::OnEnSetfocusEditRtfCodice) // Marvel Carvalho - Bug 3457 (FIX) TEXTER
	ON_EN_SETFOCUS(IDC_EDIT_RTF_FRASE, &CFrasiRtfDlg::OnEnSetfocusEditRtfFrase)   // Marvel Carvalho - Bug 3457 (FIX) TEXTER
END_MESSAGE_MAP()

void CFrasiRtfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlBtnSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlBtnUndo);
	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlBtnChiudi);

	DDX_Control(pDX, IDC_EDIT_CODICE, m_ctrlEditCodice);
	DDX_Control(pDX, IDC_EDIT_RTF_CODICE, m_ctrlEditRtfCodice);
	DDX_Control(pDX, IDC_EDIT_RTF_FRASE, m_ctrlEditRtfFrase);

	DDX_Control(pDX, IDC_LIST_FRASIRTF, m_ctrlListFrasiRTF);

	DDX_Control(pDX, IDC_STATIC_CODICE, m_ctrlStaticCodice);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);
	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
}

void CFrasiRtfDlg::OnCancel()
{
}

BOOL CFrasiRtfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ctrlToolbar.Create(IDC_STATIC_FRAME, this);
	m_ctrlToolbar.ShowWindow(SW_HIDE);

	// tolgo i flag WS_CLIPCHILDREN e WS_CLIPSIBLINGS dallo stile della barra //
	::SetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetFontName(g_sReportFaceName);
	m_ctrlTextControl.SetFontSize(g_nReportSize);
	m_ctrlTextControl.SetFontBold(g_bReportBold);
	m_ctrlTextControl.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

	//

	m_ctrlTextControl.SetBackColor(GetSysColor(COLOR_3DFACE));
	m_ctrlTextControl.SetEditMode(1);

	//

	m_ctrlListFrasiRTF.SetExtendedStyle(m_ctrlListFrasiRTF.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListFrasiRTF.InsertColumn(0, "", LVCFMT_CENTER, 0);
	m_ctrlListFrasiRTF.InsertColumn(1, theApp.GetMessageString(IDS_CODICE), LVCFMT_LEFT, 133);
	m_ctrlListFrasiRTF.InsertColumn(2, theApp.GetMessageString(IDS_FRASE), LVCFMT_LEFT, 133);
	m_ctrlListFrasiRTF.InsertColumn(3, "", LVCFMT_CENTER, 0);

	//

	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	m_ctrlEditRtfFrase.SetWindowText(_T("pesquisar..."));  // Marvel Carvalho - Bug 3457 (FIX) TEXTER
	m_ctrlEditRtfCodice.SetWindowText(_T("pesquisar...")); // Marvel Carvalho - Bug 3457 (FIX) TEXTER

	theApp.LocalizeDialog(this, IDD_FRASI_RTF, "FrasiRtfDlg");
	return TRUE;
}

void CFrasiRtfDlg::OnOK()
{
}

void CFrasiRtfDlg::OnEnChangeEditRtfCodiceFrase()
{
	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	if (!m_bProcessOnEnChange)
		return;

	const int iMinLenCodice = 2;
	const int iMinLenFrase = 4;

	BeginWaitCursor();
	m_ctrlListFrasiRTF.SetRedraw(FALSE);
	m_ctrlListFrasiRTF.DeleteAllItems();

	CString sCodice;
	m_ctrlEditRtfCodice.GetWindowText(sCodice);
	sCodice.Trim();
	sCodice.Replace("'", "''");

	CString sFrase;
	m_ctrlEditRtfFrase.GetWindowText(sFrase);
	sFrase.Trim();
	sFrase.Replace("'", "''");

	if ((sCodice.GetLength() >= iMinLenCodice) || (sFrase.GetLength() >= iMinLenFrase))
	{
		CString sFilter = "";

		if (sCodice.GetLength() > 0)
		{
			if (!sFilter.IsEmpty())
				sFilter += " AND ";

			sFilter += "Codice LIKE '" + sCodice + "%%'";
		}

		if (sFrase.GetLength() > 0)
		{
			if (!sFilter.IsEmpty())
				sFilter += " AND ";

			sFilter += "TestoTXT LIKE '%%" + sFrase + "%%'";
		}

		CFrasiRtfSet setFrasi;
		setFrasi.SetOpenFilter(sFilter);
		if (setFrasi.OpenRecordset("CFrasiRtfDlg::OnEnChangeEditRtfCodiceFrase"))
		{
			int nItem = 0;

			while (!setFrasi.IsEOF())
			{
				m_ctrlListFrasiRTF.InsertItem(nItem, "");
				m_ctrlListFrasiRTF.SetItemData(nItem, setFrasi.m_lID);

				m_ctrlListFrasiRTF.SetItemText(nItem, 1, setFrasi.m_sCodice);
				m_ctrlListFrasiRTF.SetItemText(nItem, 2, setFrasi.m_sTestoTXT);

				nItem++;
				setFrasi.MoveNext();
			}

			setFrasi.CloseRecordset("CFrasiRtfDlg::OnEnChangeEditRtfCodiceFrase");
		}
	}

	if (m_ctrlListFrasiRTF.GetItemCount() > 0)
		m_ctrlListFrasiRTF.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	else
		m_ctrlListFrasiRTF.SetColumnWidth(2, 133);

	m_ctrlListFrasiRTF.SetRedraw(TRUE);
	EndWaitCursor();
}

void CFrasiRtfDlg::OnBnClickedBtnNew()
{
	m_ctrlEditRtfCodice.SetWindowText("");
	m_ctrlEditRtfFrase.SetWindowText("");
	m_ctrlListFrasiRTF.DeleteAllItems();
	OnLvnItemchangedListFrasiRtf(NULL, NULL);

	//

	SetEditState(TRUE);

	//

	m_ctrlEditCodice.SetFocus();
}

void CFrasiRtfDlg::OnBnClickedBtnEdt()
{
	SetEditState(TRUE);

	//

	m_ctrlEditCodice.SetFocus();
}

void CFrasiRtfDlg::OnBnClickedBtnDel()
{
	long lIDSelected = 0;

	POSITION pos = m_ctrlListFrasiRTF.GetFirstSelectedItemPosition();
	long lCurSel = -1;
	if (pos != NULL)
	{
		lCurSel = m_ctrlListFrasiRTF.GetNextSelectedItem(pos);

		if (lCurSel >= 0)
			lIDSelected = m_ctrlListFrasiRTF.GetItemData(lCurSel);
	}

	if (lIDSelected > 0)
	{
		m_ctrlBtnEdt.EnableWindow(TRUE);
		m_ctrlBtnDel.EnableWindow(TRUE);

		CString sFilter;
		sFilter.Format("ID=%li", lIDSelected);

		CFrasiRtfSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CFrasiRtfDlg::OnBnClickedBtnDel"))
		{
			if (!setTemp.IsEOF())
				if (theApp.AfxMessageBoxEndo(IDS_ELIMINARE_FRASE, MB_YESNO | MB_ICONSTOP) == IDYES)
					if (setTemp.DeleteRecordset("CFrasiRtfDlg::OnBnClickedBtnDel"))
						m_ctrlListFrasiRTF.DeleteItem(lCurSel);

			setTemp.CloseRecordset("CFrasiRtfDlg::OnBnClickedBtnDel");
		}
	}
}


void CFrasiRtfDlg::OnBnClickedBtnSave()
{
	const int iMinLenCodice = 2;
	const int iMinLenFrase = 4;

	//

	CString sCodice;
	m_ctrlEditCodice.GetWindowText(sCodice);
	sCodice.Trim();

	if (sCodice.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CODICE_OBBLIGATORIO));
		return;
	}

	if (sCodice.GetLength() < iMinLenCodice)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CODICE_TROPPOCORTO));
		return;
	}

	sCodice.MakeUpper();

	//

	CString sFraseTxt = m_ctrlTextControl.GetText();
	sFraseTxt.Trim();

	if (sFraseTxt.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FRASE_OBBLIGATORIA));
		return;
	}

	sFraseTxt.Replace('\n', ' ');

	int nReplaces = sFraseTxt.Replace("  ", " ");
	while (nReplaces > 0)
		nReplaces = sFraseTxt.Replace("  ", " ");

	//

	long lSelStart = m_ctrlTextControl.GetSelStart();
	long lSelLength = m_ctrlTextControl.GetSelLength();

	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	CString sFraseRtf = m_ctrlTextControl.GetRTFSelText();
	
	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	sFraseRtf = cleanFinalDoubleParInRTF(sFraseRtf);
	
	m_ctrlTextControl.SetSelStart(lSelStart);
	m_ctrlTextControl.SetSelLength(lSelLength);

	long lIDSelected = 0;

	POSITION pos = m_ctrlListFrasiRTF.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		long lCurSel = m_ctrlListFrasiRTF.GetNextSelectedItem(pos);

		if (lCurSel >= 0)
			lIDSelected = m_ctrlListFrasiRTF.GetItemData(lCurSel);
	}

	if (lIDSelected > 0)
	{
		// SIAMO IN EDIT //

		CString sCodiceSearch = sCodice;
		sCodiceSearch.Replace("'", "''");

		CString sFilter;
		sFilter.Format("ID<>%li AND Codice LIKE '%s'", lIDSelected, sCodiceSearch);

		CFrasiRtfSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CFrasiRtfDlg::OnBnClickedBtnSave"))
		{
			if (!setTemp.IsEOF())
			{
				// il codice inserito è già usato da un'altra frase //
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CODICE_GIAUSATO));
				setTemp.CloseRecordset("CFrasiRtfDlg::OnBnClickedBtnSave");
				return;
			}
			else
			{
				setTemp.CloseRecordset("CFrasiRtfDlg::OnBnClickedBtnSave");

				sFilter.Format("ID=%li", lIDSelected);
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CFrasiRtfDlg::OnBnClickedBtnSave"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CFrasiRtfDlg::OnBnClickedBtnSave"))
						{
							setTemp.m_sCodice = sCodice;
							setTemp.m_sTestoRTF = sFraseRtf;
							setTemp.m_sTestoTXT = sFraseTxt;

							setTemp.UpdateRecordset("CFrasiRtfDlg::OnBnClickedBtnSave");
						}
					}
				}
			}

			setTemp.CloseRecordset("CFrasiRtfDlg::OnBnClickedBtnSave");
		}
	}
	else
	{
		// SIAMO IN ADDNEW //

		CString sCodiceSearch = sCodice;
		sCodiceSearch.Replace("'", "''");

		CString sFilter;
		sFilter.Format("Codice LIKE '%s'", sCodiceSearch);

		CFrasiRtfSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CFrasiRtfDlg::OnBnClickedBtnSave"))
		{
			if (!setTemp.IsEOF())
			{
				// il codice inserito è già usato da un'altra frase //
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CODICE_GIAUSATO));
				setTemp.CloseRecordset("CFrasiRtfDlg::OnBnClickedBtnSave");
				return;
			}

			if (setTemp.AddNewRecordset("CFrasiRtfDlg::OnBnClickedBtnSave"))
			{
				setTemp.m_sCodice = sCodice;
				setTemp.m_sTestoRTF = sFraseRtf;
				setTemp.m_sTestoTXT = sFraseTxt;

				if (setTemp.UpdateRecordset("CFrasiRtfDlg::OnBnClickedBtnSave"))
					lIDSelected = setTemp.GetLastAdd();
			}

			setTemp.CloseRecordset("CFrasiRtfDlg::OnBnClickedBtnSave");
		}
	}

	//
	SetEditState(FALSE);

	//
	m_ctrlEditRtfCodice.SetWindowText(sCodice);

	//
	for (int i = 0; i < m_ctrlListFrasiRTF.GetItemCount(); i++)
	{
		if (m_ctrlListFrasiRTF.GetItemData(i) == lIDSelected)
		{
			m_ctrlListFrasiRTF.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			m_ctrlListFrasiRTF.EnsureVisible(i, FALSE);
			break;
		}
	}
}

void CFrasiRtfDlg::OnBnClickedBtnUndo()
{
	OnLvnItemchangedListFrasiRtf(NULL, NULL);
	SetEditState(FALSE);
}

void CFrasiRtfDlg::OnBnClickedBtnChiudi()
{
	if (m_ctrlBtnChiudi.IsWindowEnabled())
		CDialog::OnOK();
}

void CFrasiRtfDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl.RtfInsertNewTable(this);
}

void CFrasiRtfDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl.RtfSelectedTextMakeUpper();
}

void CFrasiRtfDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl.RtfSelectedTextMakeNormal();
}

void CFrasiRtfDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl.RtfSelectedTextMakeLower();
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CFrasiRtfDlg::updateEditableFields(CString p_sCodice, CString p_sTestoRTF)
{
	m_ctrlEditCodice.SetWindowText(p_sCodice);

	CString sFraseRtf = cleanFinalDoubleParInRTF(p_sTestoRTF);
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	m_ctrlTextControl.SetRTFSelText(sFraseRtf); //quando insiro o texto como rtf o TX Text Control sempre coloca um enter no final do texto o cleanFinalDoubleParInRTF() tira isso!
}


void CFrasiRtfDlg::OnLvnItemchangedListFrasiRtf(NMHDR *pNMHDR, LRESULT *pResult)
{
	//m_bRTFAlreadyBackspaced = FALSE;

	long lIDSelected = 0;

	POSITION pos = m_ctrlListFrasiRTF.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		long lCurSel = m_ctrlListFrasiRTF.GetNextSelectedItem(pos);

		if (lCurSel >= 0)
			lIDSelected = m_ctrlListFrasiRTF.GetItemData(lCurSel);
	}

	if (lIDSelected > 0)
	{
		m_ctrlBtnEdt.EnableWindow(TRUE);
		m_ctrlBtnDel.EnableWindow(TRUE);

		CString sFilter;
		sFilter.Format("ID=%li", lIDSelected);

		CFrasiRtfSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CFrasiRtfDlg::OnLvnItemchangedListFrasirtf"))
		{
			if (!setTemp.IsEOF())
			{
				updateEditableFields(setTemp.m_sCodice, setTemp.m_sTestoRTF);
			}
			setTemp.CloseRecordset("CFrasiRtfDlg::OnLvnItemchangedListFrasirtf");
		}
	}
	else
	{
		m_ctrlBtnEdt.EnableWindow(FALSE);
		m_ctrlBtnDel.EnableWindow(FALSE);

		m_ctrlEditCodice.SetWindowText("");
		m_ctrlTextControl.ResetContents();
	}
}

void CFrasiRtfDlg::SetEditState(BOOL bEditable)
{
	m_ctrlEditRtfCodice.EnableWindow(!bEditable);
	m_ctrlEditRtfFrase.EnableWindow(!bEditable);
	m_ctrlListFrasiRTF.EnableWindow(!bEditable);

	m_ctrlEditCodice.SetReadOnly(!bEditable);

	m_ctrlButtonBar.ShowWindow(bEditable ? SW_SHOW : SW_HIDE);

	m_ctrlTextControl.SetBackColor(bEditable ? RGB(255, 255, 255) : GetSysColor(COLOR_3DFACE));
	m_ctrlTextControl.SetEditMode(bEditable ? 0 : 1);

	m_ctrlToolbar.ShowWindow(bEditable ? SW_SHOW : SW_HIDE);

	m_ctrlBtnNew.ShowWindow(bEditable ? SW_HIDE : SW_SHOW);
	m_ctrlBtnEdt.ShowWindow(bEditable ? SW_HIDE : SW_SHOW);
	m_ctrlBtnDel.ShowWindow(bEditable ? SW_HIDE : SW_SHOW);
	m_ctrlBtnSave.ShowWindow(bEditable ? SW_SHOW : SW_HIDE);
	m_ctrlBtnUndo.ShowWindow(bEditable ? SW_SHOW : SW_HIDE);
	m_ctrlBtnChiudi.EnableWindow(!bEditable);
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CFrasiRtfDlg::OnEnSetfocusEditRtfCodice()
{
	cleanEditToStart();
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CFrasiRtfDlg::OnEnSetfocusEditRtfFrase()
{
	cleanEditToStart();
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CFrasiRtfDlg::cleanEditToStart()
{
	CString strFrase, strCodice;
	m_ctrlEditRtfFrase.GetWindowText(strFrase);
	m_ctrlEditRtfCodice.GetWindowText(strCodice);

	if (strFrase == _T("pesquisar...") || strFrase == _T("pesquisar...")) {
		m_bProcessOnEnChange = FALSE;
		m_ctrlEditRtfFrase.SetWindowText(_T(""));
		m_ctrlEditRtfCodice.SetWindowText(_T(""));
		m_bProcessOnEnChange = TRUE;
	}
}