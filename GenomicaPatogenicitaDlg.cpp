#include "stdafx.h"
#include "Endox.h"
#include "GenomicaPatogenicitaDlg.h"
#include "PatogenicitaSet.h"
#include "TipiVariantiGeneticheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaPatogenicitaDlg, CDialog)

CGenomicaPatogenicitaDlg::CGenomicaPatogenicitaDlg(CWnd* pParent)
	: CDialog(CGenomicaPatogenicitaDlg::IDD, pParent)
{
	m_lIDSelected = -1;
}

CGenomicaPatogenicitaDlg::~CGenomicaPatogenicitaDlg()
{

}

BEGIN_MESSAGE_MAP(CGenomicaPatogenicitaDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_BN_CLICKED(IDC_BTN_NEW,	OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT,	OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL,	OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
END_MESSAGE_MAP()

void CGenomicaPatogenicitaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW,	m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT,	m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL,	m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE,	m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO,	m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK,			m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_LIST,		m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_1,	m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2,	m_ctrlStatic2);

	DDX_Control(pDX, IDC_POSITIVITA,m_ctrlButtonPositivita);
}

BOOL CGenomicaPatogenicitaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 0);
	
	RiempiLista();

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CGenomicaPatogenicitaDlg::IDD, "GenomicaPatogenicitaDlg");	
	return TRUE;
}

void CGenomicaPatogenicitaDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CGenomicaPatogenicitaDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaPatogenicitaDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<long> listID;
	CPatogenicitaSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CPatogenicitaSet().GetCodice(lID));
		m_ctrlList.SetItemText(nItem, 1, CPatogenicitaSet().GetDescrizione(lID));
		m_ctrlList.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGenomicaPatogenicitaDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_DESCRIZIONE, "");
	m_ctrlButtonPositivita.SetCheck(BST_UNCHECKED);	
	
	//
	
	SetDlgItemText(IDC_CODICE, CPatogenicitaSet().GetCodice(m_lIDSelected));
	SetDlgItemText(IDC_DESCRIZIONE, CPatogenicitaSet().GetDescrizione(m_lIDSelected));
	m_ctrlButtonPositivita.SetCheck(CPatogenicitaSet().GetPositivita(m_lIDSelected) ? BST_CHECKED : BST_UNCHECKED);

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CGenomicaPatogenicitaDlg::UnselectAll()
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

void CGenomicaPatogenicitaDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_DESCRIZIONE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);	
	GetDlgItem(IDC_POSITIVITA)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);	
}


// CGenomicaPatogenicitaDlg message handlers
void CGenomicaPatogenicitaDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CGenomicaPatogenicitaDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGenomicaPatogenicitaDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{		
			if (!CPatogenicitaSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CGenomicaPatogenicitaDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CGenomicaPatogenicitaDlg::OnBnClickedBtnSave()
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
			CPatogenicitaSet setPatogenita;
			setPatogenita.SetOpenFilter("");
			if (setPatogenita.OpenRecordset("CGenomicaPatogenicitaDlg::OnBnClickedBtnSave"))
			{
				if (setPatogenita.AddNewRecordset("CGenomicaPatogenicitaDlg::OnBnClickedBtnSave"))
				{										
					GetDlgItemText(IDC_CODICE, setPatogenita.m_sCodice);
					GetDlgItemText(IDC_DESCRIZIONE, setPatogenita.m_sDescrizione);
					setPatogenita.m_bPositivita = (m_ctrlButtonPositivita.GetCheck() == BST_CHECKED);
					setPatogenita.m_bEliminato = FALSE;

					setPatogenita.UpdateRecordset("CGenomicaPatogenicitaDlg::OnBnClickedBtnSave");
				}
				setPatogenita.CloseRecordset("CGenomicaPatogenicitaDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			CString sCodice;
			GetDlgItemText(IDC_CODICE, sCodice);
			CPatogenicitaSet().SetCodice(m_lIDSelected, sCodice);
			
			CString sDescrizione;
			GetDlgItemText(IDC_DESCRIZIONE, sDescrizione);
			CPatogenicitaSet().SetDescrizione(m_lIDSelected, sDescrizione);
			
			BOOL bPositivita = (m_ctrlButtonPositivita.GetCheck() == BST_CHECKED);
			CPatogenicitaSet().SetPositivita(m_lIDSelected, bPositivita);			
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

void CGenomicaPatogenicitaDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}