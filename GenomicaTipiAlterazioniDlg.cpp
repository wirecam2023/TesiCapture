#include "stdafx.h"
#include "Endox.h"
#include "GenomicaTipiAlterazioniDlg.h"
#include "TipiAlterazioniSet.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaTipiAlterazioniDlg, CDialog)

CGenomicaTipiAlterazioniDlg::CGenomicaTipiAlterazioniDlg(CWnd* pParent)
	: CDialog(CGenomicaTipiAlterazioniDlg::IDD, pParent)
{
	m_lIDSelected = -1;
}

CGenomicaTipiAlterazioniDlg::~CGenomicaTipiAlterazioniDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaTipiAlterazioniDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
END_MESSAGE_MAP()

void CGenomicaTipiAlterazioniDlg::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_OBB_HGVSC, m_ctrlButtonObbligatorioHGVSc);
	DDX_Control(pDX, IDC_OBB_HGVSP, m_ctrlButtonObbligatorioHGVSp);
}

BOOL CGenomicaTipiAlterazioniDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 0);

	RiempiLista();

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CGenomicaTipiAlterazioniDlg::IDD, "CGenomicaTipiAlterazioniDlg");
	return TRUE;
}

void CGenomicaTipiAlterazioniDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CGenomicaTipiAlterazioniDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaTipiAlterazioniDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<long> listID;
	CTipiAlterazioniSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CTipiAlterazioniSet().GetCodice(lID));
		m_ctrlList.SetItemText(nItem, 1, CTipiAlterazioniSet().GetDescrizione(lID));
		m_ctrlList.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGenomicaTipiAlterazioniDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_DESCRIZIONE, "");
	m_ctrlButtonObbligatorioHGVSc.SetCheck(BST_UNCHECKED);
	m_ctrlButtonObbligatorioHGVSp.SetCheck(BST_UNCHECKED);

	//

	SetDlgItemText(IDC_CODICE, CTipiAlterazioniSet().GetCodice(m_lIDSelected));
	SetDlgItemText(IDC_DESCRIZIONE, CTipiAlterazioniSet().GetDescrizione(m_lIDSelected));

	BOOL bHGVSc, bHGVSp = FALSE;
	CTipiAlterazioniSet().GetObbligatori(m_lIDSelected, bHGVSc, bHGVSp);

	m_ctrlButtonObbligatorioHGVSc.SetCheck(bHGVSc ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlButtonObbligatorioHGVSp.SetCheck(bHGVSp ? BST_CHECKED : BST_UNCHECKED);

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CGenomicaTipiAlterazioniDlg::UnselectAll()
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

void CGenomicaTipiAlterazioniDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_DESCRIZIONE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	GetDlgItem(IDC_OBB_HGVSC)->EnableWindow(bEdit);
	GetDlgItem(IDC_OBB_HGVSP)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CGenomicaPatogenicitaDlg message handlers
void CGenomicaTipiAlterazioniDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CGenomicaTipiAlterazioniDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGenomicaTipiAlterazioniDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (!CTipiAlterazioniSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CGenomicaTipiAlterazioniDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CGenomicaTipiAlterazioniDlg::OnBnClickedBtnSave()
{
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
			CTipiAlterazioniSet setPatogenita;
			setPatogenita.SetOpenFilter("");
			if (setPatogenita.OpenRecordset("CGenomicaTipiAlterazioniDlg::OnBnClickedBtnSave"))
			{
				if (setPatogenita.AddNewRecordset("CGenomicaTipiAlterazioniDlg::OnBnClickedBtnSave"))
				{
					GetDlgItemText(IDC_CODICE, setPatogenita.m_sCodice);
					GetDlgItemText(IDC_DESCRIZIONE, setPatogenita.m_sDescrizione);

					BOOL bHGVSc = (m_ctrlButtonObbligatorioHGVSc.GetCheck() == BST_CHECKED);
					BOOL bHGVSp = (m_ctrlButtonObbligatorioHGVSp.GetCheck() == BST_CHECKED);
					setPatogenita.m_bObbligatorioHGVSc = bHGVSc;
					setPatogenita.m_bObbligatorioHGVSp = bHGVSp;
					
					setPatogenita.m_bEliminato = FALSE;

					setPatogenita.UpdateRecordset("CGenomicaTipiAlterazioniDlg::OnBnClickedBtnSave");
				}
				setPatogenita.CloseRecordset("CGenomicaTipiAlterazioniDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			CString sCodice;
			GetDlgItemText(IDC_CODICE, sCodice);
			CTipiAlterazioniSet().SetCodice(m_lIDSelected, sCodice);

			CString sDescrizione;
			GetDlgItemText(IDC_DESCRIZIONE, sDescrizione);
			CTipiAlterazioniSet().SetDescrizione(m_lIDSelected, sDescrizione);

			BOOL bHGVSc = (m_ctrlButtonObbligatorioHGVSc.GetCheck() == BST_CHECKED);
			BOOL bHGVSp = (m_ctrlButtonObbligatorioHGVSp.GetCheck() == BST_CHECKED);
			CTipiAlterazioniSet().SetObbligatori(m_lIDSelected, bHGVSc, bHGVSp);
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

void CGenomicaTipiAlterazioniDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}