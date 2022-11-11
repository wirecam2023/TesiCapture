#include "stdafx.h"
#include "Endox.h"
#include "Common.h"
#include "GenomicaTipiMaterialiDlg.h"
#include "TipiMaterialiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaTipiMaterialiDlg, CDialog)

CGenomicaTipiMaterialiDlg::CGenomicaTipiMaterialiDlg(CWnd* pParent)
	: CDialog(CGenomicaTipiMaterialiDlg::IDD, pParent)
{
	m_lIDSelected = -1;
}

CGenomicaTipiMaterialiDlg::~CGenomicaTipiMaterialiDlg()
{
}
BEGIN_MESSAGE_MAP(CGenomicaTipiMaterialiDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

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

void CGenomicaTipiMaterialiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);	

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
}

BOOL CGenomicaTipiMaterialiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 0);

	RiempiLista();

	m_ctrlToolbar.Create(IDC_BUTTONBAR_PLACE, this);
	m_ctrlToolbar.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetFontName(g_sReportFaceName);
	m_ctrlTextControl.SetFontSize(g_nReportSize);
	m_ctrlTextControl.SetFontBold(g_bReportBold);
	m_ctrlTextControl.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

	m_ctrlTextControl.EnableWindow(FALSE);
	m_ctrlButtonBar.EnableWindow(FALSE);
	m_ctrlToolbar.EnableWindow(FALSE);

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CGenomicaTipiMaterialiDlg::IDD, "CGenomicaTipiMaterialiDlg");
	return TRUE;
}

void CGenomicaTipiMaterialiDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CGenomicaTipiMaterialiDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaTipiMaterialiDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<long> listID;
	CTipiMaterialiSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CTipiMaterialiSet().GetCodice(lID));
		m_ctrlList.SetItemText(nItem, 1, CTipiMaterialiSet().GetDescrizione(lID));
		m_ctrlList.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGenomicaTipiMaterialiDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_DESCRIZIONE, "");
	m_ctrlTextControl.ResetContents();	

	//

	SetDlgItemText(IDC_CODICE, CTipiMaterialiSet().GetCodice(m_lIDSelected));	
	SetDlgItemText(IDC_DESCRIZIONE, CTipiMaterialiSet().GetDescrizione(m_lIDSelected));
	m_ctrlTextControl.SetRTFSelText(CTipiMaterialiSet().GetTestoRtf(m_lIDSelected, 1));

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CGenomicaTipiMaterialiDlg::UnselectAll()
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
}

void CGenomicaTipiMaterialiDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_DESCRIZIONE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	m_ctrlTextControl.EnableWindow(bEdit);	
	m_ctrlButtonBar.EnableWindow(bEdit);
	m_ctrlTextControl.EnableWindow(bEdit);
	m_ctrlToolbar.EnableWindow(bEdit);	
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CGenomicaTipiVariantiDlg message handlers
void CGenomicaTipiMaterialiDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (!CTipiMaterialiSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnSave()
{
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);

	if (!UpdateData(TRUE))
		return;

	CString strTemp;

	GetDlgItemText(IDC_CODICE, strTemp);
	strTemp.Trim();

	if (!strTemp.IsEmpty())
	{
		if (m_lIDSelected <= 0)
		{
			// addnew //
			CTipiMaterialiSet setTemp;
			setTemp.SetOpenFilter("");
			if (setTemp.OpenRecordset("CGenomicaTipiMaterialiDlg::OnBnClickedBtnSave"))
			{
				if (setTemp.AddNewRecordset("CGenomicaTipiMaterialiDlg::OnBnClickedBtnSave"))
				{
					GetDlgItemText(IDC_CODICE, setTemp.m_sCodice);					
					GetDlgItemText(IDC_DESCRIZIONE, setTemp.m_sDescrizione);										
					setTemp.m_sTestoRtf001 = m_ctrlTextControl.GetRTFSelText();
					setTemp.m_bEliminato = FALSE;

					setTemp.UpdateRecordset("CGenomicaTipiMaterialiDlg::OnBnClickedBtnSave");
				}
				setTemp.CloseRecordset("CGenomicaTipiMaterialiDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			CString sCodice;
			GetDlgItemText(IDC_CODICE, sCodice);
			CTipiMaterialiSet().SetCodice(m_lIDSelected, sCodice);

			CString sDescrizione;
			GetDlgItemText(IDC_DESCRIZIONE, sDescrizione);
			CTipiMaterialiSet().SetDescrizione(m_lIDSelected, sDescrizione);			

			CTipiMaterialiSet().SetTestoRtf(m_lIDSelected, 1, m_ctrlTextControl.GetRTFSelText());
		}

		UnselectAll();
		RiempiLista();
		EditDialog(FALSE);
	}
	else
	{
		AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO4), MB_ICONSTOP);
	}
}

void CGenomicaTipiMaterialiDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl.RtfInsertNewTable(this);
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl.RtfSelectedTextMakeUpper();
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl.RtfSelectedTextMakeNormal();
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl.RtfSelectedTextMakeLower();
}

void CGenomicaTipiMaterialiDlg::OnBnClickedBtnRtfFont() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlTextControl.RtfSetFontProperties();
}