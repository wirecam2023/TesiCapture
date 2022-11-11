#include "stdafx.h"
#include "Endox.h"
#include "Common.h"
#include "GenomicaTipiVariantiDlg.h"
#include "TipiVariantiGeneticheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CGenomicaTipiVariantiDlg, CDialog)

CGenomicaTipiVariantiDlg::CGenomicaTipiVariantiDlg(CWnd* pParent)
: CDialog(CGenomicaTipiVariantiDlg::IDD, pParent)
{
	m_lIDSelected = -1;
}

CGenomicaTipiVariantiDlg::~CGenomicaTipiVariantiDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaTipiVariantiDlg, CDialog)
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


void CGenomicaTipiVariantiDlg::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_OBB_CODVAR, m_ctrlButtonObbligatorioCodice);
	DDX_Control(pDX, IDC_OBB_TIPALT, m_ctrlButtonObbligatorioAlterazione);
	DDX_Control(pDX, IDC_OBB_TRASCRIZIONE, m_ctrlButtonObbligatorioTrascrizione);
	DDX_Control(pDX, IDC_FRASE_REMOVIBILE, m_ctrlButtonFraseRisultatoRemovibile);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
}

BOOL CGenomicaTipiVariantiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 0);

	RiempiLista();

	m_ctrlToolbar.Create(IDC_BUTTONBAR_PLACE, this);
	m_ctrlToolbar.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	// tolgo i flag WS_CLIPCHILDREN e WS_CLIPSIBLINGS dallo stile della barra //
	::SetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetFontName(g_sReportFaceName);
	m_ctrlTextControl.SetFontSize(g_nReportSize);
	m_ctrlTextControl.SetFontBold(g_bReportBold);
	m_ctrlTextControl.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

	m_ctrlTextControl.EnableWindow(FALSE);
	m_ctrlToolbar.EnableWindow(FALSE);
	m_ctrlButtonBar.EnableWindow(FALSE);

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CGenomicaTipiVariantiDlg::IDD, "CGenomicaTipiVariantiDlg");
	return TRUE;
}

void CGenomicaTipiVariantiDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CGenomicaTipiVariantiDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaTipiVariantiDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<long> listID;
	CTipiVariantiGeneticheSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CTipiVariantiGeneticheSet().GetCodice(lID));
		m_ctrlList.SetItemText(nItem, 1, CTipiVariantiGeneticheSet().GetDescrizione(lID));
		m_ctrlList.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGenomicaTipiVariantiDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_DESCRIZIONE, "");
	m_ctrlButtonObbligatorioCodice.SetCheck(BST_UNCHECKED);
	m_ctrlButtonObbligatorioAlterazione.SetCheck(BST_UNCHECKED);
	m_ctrlButtonObbligatorioTrascrizione.SetCheck(BST_UNCHECKED);
	m_ctrlButtonFraseRisultatoRemovibile.SetCheck(BST_UNCHECKED);
	m_ctrlTextControl.ResetContents();	

	//

	SetDlgItemText(IDC_CODICE, CTipiVariantiGeneticheSet().GetCodice(m_lIDSelected));
	SetDlgItemText(IDC_DESCRIZIONE, CTipiVariantiGeneticheSet().GetDescrizione(m_lIDSelected));

	BOOL bCodice, bAlterazione, bTrascrizione = FALSE;
	CTipiVariantiGeneticheSet().GetObbligatori(m_lIDSelected, bCodice, bAlterazione, bTrascrizione);

	m_ctrlButtonObbligatorioCodice.SetCheck(bCodice ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlButtonObbligatorioAlterazione.SetCheck(bAlterazione ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlButtonObbligatorioTrascrizione.SetCheck(bTrascrizione ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlButtonFraseRisultatoRemovibile.SetCheck(CTipiVariantiGeneticheSet().GetFraseRemovibile(m_lIDSelected) ? BST_CHECKED : BST_UNCHECKED);

	m_ctrlTextControl.SetRTFSelText(CTipiVariantiGeneticheSet().GetTestoRtf(m_lIDSelected, 1));

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CGenomicaTipiVariantiDlg::UnselectAll()
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

void CGenomicaTipiVariantiDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_DESCRIZIONE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	GetDlgItem(IDC_OBB_CODVAR)->EnableWindow(bEdit);
	GetDlgItem(IDC_OBB_TIPALT)->EnableWindow(bEdit);
	GetDlgItem(IDC_OBB_TRASCRIZIONE)->EnableWindow(bEdit);
	GetDlgItem(IDC_FRASE_REMOVIBILE)->EnableWindow(bEdit);
	m_ctrlTextControl.EnableWindow(bEdit);
	m_ctrlToolbar.EnableWindow(bEdit);
	m_ctrlButtonBar.EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CGenomicaTipiVariantiDlg message handlers
void CGenomicaTipiVariantiDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (!CTipiVariantiGeneticheSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnSave()
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
			CTipiVariantiGeneticheSet setTipi;
			setTipi.SetOpenFilter("");
			if (setTipi.OpenRecordset("CGenomicaTipiVariantiDlg::OnBnClickedBtnSave"))
			{
				if (setTipi.AddNewRecordset("CGenomicaTipiVariantiDlg::OnBnClickedBtnSave"))
				{
					long lid = setTipi.GetLastAdd();

					GetDlgItemText(IDC_CODICE, setTipi.m_sCodice);
					GetDlgItemText(IDC_DESCRIZIONE, setTipi.m_sDescrizione);
					setTipi.m_bObbligatorioCodiceVariante = (m_ctrlButtonObbligatorioCodice.GetCheck() == BST_CHECKED);
					setTipi.m_bObbligatorioTipoAlterazione = (m_ctrlButtonObbligatorioAlterazione.GetCheck() == BST_CHECKED);
					setTipi.m_bObbligatorioTrascrizione = (m_ctrlButtonObbligatorioTrascrizione.GetCheck() == BST_CHECKED);
					setTipi.m_bFraseRemovibile = (m_ctrlButtonFraseRisultatoRemovibile.GetCheck() == BST_CHECKED);
					setTipi.m_sTestoRtf001 = m_ctrlTextControl.GetRTFSelText();
					setTipi.m_bEliminato = FALSE;

					setTipi.UpdateRecordset("CGenomicaTipiVariantiDlg::OnBnClickedBtnSave");
				}
				setTipi.CloseRecordset("CGenomicaTipiVariantiDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			CString sCodice;
			GetDlgItemText(IDC_CODICE, sCodice);
			CTipiVariantiGeneticheSet().SetCodice(m_lIDSelected, sCodice);

			CString sDescrizione;
			GetDlgItemText(IDC_DESCRIZIONE, sDescrizione);
			CTipiVariantiGeneticheSet().SetDescrizione(m_lIDSelected, sDescrizione);

			BOOL bCodice = (m_ctrlButtonObbligatorioCodice.GetCheck() == BST_CHECKED);
			BOOL bAlterazione = (m_ctrlButtonObbligatorioAlterazione.GetCheck() == BST_CHECKED);
			BOOL bTrascrizione = (m_ctrlButtonObbligatorioTrascrizione.GetCheck() == BST_CHECKED);
			CTipiVariantiGeneticheSet().SetObbligatori(m_lIDSelected, bCodice, bAlterazione, bTrascrizione);

			BOOL bFrase = (m_ctrlButtonFraseRisultatoRemovibile.GetCheck() == BST_CHECKED);
			CTipiVariantiGeneticheSet().SetFraseRemovibile(m_lIDSelected, bFrase);

			CTipiVariantiGeneticheSet().SetTestoRtf(m_lIDSelected, 1, m_ctrlTextControl.GetRTFSelText());
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

void CGenomicaTipiVariantiDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl.RtfInsertNewTable(this);
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl.RtfSelectedTextMakeUpper();
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl.RtfSelectedTextMakeNormal();
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl.RtfSelectedTextMakeLower();
}

void CGenomicaTipiVariantiDlg::OnBnClickedBtnRtfFont() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlTextControl.RtfSetFontProperties();
}