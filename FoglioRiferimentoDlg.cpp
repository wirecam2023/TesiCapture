//Gabriel BUG 6225 - Lista DO
#include "stdafx.h"
#include "Endox.h"
#include "FoglioRiferimentoSet.h"
#include "FoglioRiferimentoDlg.h"
#include "CodificaRegionaleExSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFoglioRiferimentoDlg, CDialog)

CFoglioRiferimentoDlg::CFoglioRiferimentoDlg(CWnd* pParent)
: CDialog(CFoglioRiferimentoDlg::IDD, pParent)
{
	m_lIDSelected = -1;
}

CFoglioRiferimentoDlg::~CFoglioRiferimentoDlg()
{

}

BEGIN_MESSAGE_MAP(CFoglioRiferimentoDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_BTN_PATH, OnBnClickedBtnPath)
END_MESSAGE_MAP()

void CFoglioRiferimentoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_BTN_PATH, m_ctrlButtonPath);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);

	DDX_Control(pDX, IDC_COMBO, m_ctrlComboSigla);
}

BOOL CFoglioRiferimentoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 0);

	RiempiLista();
	RiempiComboCodicePrestazione();

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CFoglioRiferimentoDlg::IDD, "CFoglioRiferimentoDlg");
	return TRUE;
}

void CFoglioRiferimentoDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CFoglioRiferimentoDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CFoglioRiferimentoDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<long> listID;
	CFoglioRiferimentoSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CFoglioRiferimentoSet().GetCodicePrestazione(lID));
		m_ctrlList.SetItemText(nItem, 1, CFoglioRiferimentoSet().GetDescrizione(lID));
		m_ctrlList.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CFoglioRiferimentoDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_NOME, "");
	SetDlgItemText(IDC_CAMINHO, "");
	m_ctrlComboSigla.SetCurSel(-1);

	//

	SetDlgItemText(IDC_NOME, CFoglioRiferimentoSet().GetDescrizione(m_lIDSelected));
	SetDlgItemText(IDC_CAMINHO, CFoglioRiferimentoSet().GetPercorso(m_lIDSelected));
	long lIDPrestazione = CCodificaRegionaleExSet().GetContatore(CFoglioRiferimentoSet().GetCodicePrestazione(m_lIDSelected));

	for (int i = 0; i < m_ctrlComboSigla.GetCount(); i++)
	{
		if ((long)m_ctrlComboSigla.GetItemData(i) == lIDPrestazione)
		{
			m_ctrlComboSigla.SetCurSel(i);
			break;
		}
	}

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CFoglioRiferimentoDlg::UnselectAll()
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

void CFoglioRiferimentoDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_NOME, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_CAMINHO, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	GetDlgItem(IDC_BTN_PATH)->EnableWindow(bEdit);
	m_ctrlComboSigla.EnableWindow(bEdit);
	
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CFoglioRiferimentoDlg message handlers
void CFoglioRiferimentoDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CFoglioRiferimentoDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CFoglioRiferimentoDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (!CFoglioRiferimentoSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CFoglioRiferimentoDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CFoglioRiferimentoDlg::OnBnClickedBtnSave()
{
	if (!UpdateData(TRUE))
		return;

	CString strTemp;

	GetDlgItemText(IDC_NOME, strTemp);
	strTemp.Trim();

	if (!strTemp.IsEmpty())
	{
		if (m_lIDSelected <= 0)
		{
			// addnew //
			CFoglioRiferimentoSet set;
			set.SetOpenFilter("");
			if (set.OpenRecordset("CFoglioRiferimentoDlg::OnBnClickedBtnSave"))
			{
				if (set.AddNewRecordset("CFoglioRiferimentoDlg::OnBnClickedBtnSave"))
				{
					GetDlgItemText(IDC_NOME, set.m_sDescrizione);
					GetDlgItemText(IDC_CAMINHO, set.m_sPercorso);
					set.m_lUO = theApp.m_lUO;
					 m_ctrlComboSigla.GetLBText(m_ctrlComboSigla.GetCurSel(), set.m_sCodicePrestazione);
					set.m_bEliminato = FALSE;

					set.UpdateRecordset("CFoglioRiferimentoDlg::OnBnClickedBtnSave");
				}
				set.CloseRecordset("CFoglioRiferimentoDlg::OnBnClickedBtnSave");
			}
		}
		else
		{

			CString sDescrizione;
			GetDlgItemText(IDC_NOME, sDescrizione);
			CFoglioRiferimentoSet().SetDescrizione(m_lIDSelected, sDescrizione);
			
			//BUG #9571 Felipe
			CString sPercorso;
			GetDlgItemText(IDC_CAMINHO, sPercorso);
			CFoglioRiferimentoSet().SetPercorso(m_lIDSelected, sPercorso);

			CString sSigla;
			m_ctrlComboSigla.GetLBText(m_ctrlComboSigla.GetCurSel(), sSigla);
			CFoglioRiferimentoSet().SetCodicePrestazione(m_lIDSelected, sSigla);
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

void CFoglioRiferimentoDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CFoglioRiferimentoDlg::OnBnClickedBtnPath()
{
	CFileDialog dlgFile(TRUE, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, theApp.GetMessageString(IDS_DOCUMENTS_TYPES) + "|*.pdf;|PDF|*.pdf|", this, 0, FALSE);

	if (dlgFile.DoModal())
		SetDlgItemText(IDC_CAMINHO, dlgFile.GetPathName());
	else
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FILE_NON_SUPPORTATO));
}

void CFoglioRiferimentoDlg::RiempiComboCodicePrestazione()
{
	int nCurSelSede = -1;

	m_ctrlComboSigla.ResetContent();

	CCodificaRegionaleExSet setCodicePrestazione;
	
	CString sFilter;
	sFilter.Format("CODICEINTEGRAZIONE IS NOT NULL");

	setCodicePrestazione.SetSortRecord("CODICEINTEGRAZIONE");
	if (setCodicePrestazione.OpenRecordset("CFoglioRiferimentoDlg::RiempiComboCodicePrestazione"))
	{
		int nIndex = 0;

		while (!setCodicePrestazione.IsEOF())
		{
			m_ctrlComboSigla.InsertString(nIndex, setCodicePrestazione.m_sCodiceIntegrazione);
			m_ctrlComboSigla.SetItemData(nIndex, setCodicePrestazione.m_lContatore);

			nIndex++;
			setCodicePrestazione.MoveNext();
		}

		setCodicePrestazione.CloseRecordset("CFoglioRiferimentoDlg::RiempiComboCodicePrestazione");
	}

	if (nCurSelSede >= 0)
		m_ctrlComboSigla.SetCurSel(nCurSelSede);
}