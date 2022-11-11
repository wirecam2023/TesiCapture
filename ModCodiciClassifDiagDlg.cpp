#include "stdafx.h"
#include "Endox.h"
#include "ModCodiciClassifDiagDlg.h"

#include "CodiciClassificazioneDiagnosticaSet.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CModCodiciClassifDiagDlg, CDialog)

CModCodiciClassifDiagDlg::CModCodiciClassifDiagDlg(CWnd* pParent)
	: CDialog(CModCodiciClassifDiagDlg::IDD, pParent)
{
	m_fScore = 0.0;
	m_lID = -1;
}

CModCodiciClassifDiagDlg::~CModCodiciClassifDiagDlg()
{
}

BEGIN_MESSAGE_MAP(CModCodiciClassifDiagDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
END_MESSAGE_MAP()

void CModCodiciClassifDiagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW,  m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT,  m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL,  m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK,         m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_POSITIVITA, m_ctrlButtonPositivita);

	DDX_Control(pDX, IDC_CLASSIFICAZIONE, m_ctrlComboClassificazione);
	DDX_Control(pDX, IDC_COMBO_TIPOESAME, m_ctrlComboTipoEsame);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);

	DDX_Text(pDX, IDC_SCORE, m_fScore);
}

void CModCodiciClassifDiagDlg::OnCancel()
{
	if(GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

BOOL CModCodiciClassifDiagDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 0);

	RiempiCombos();
	RiempiLista();
	SetDlgItemText(IDC_SCORE, "0");

	theApp.LocalizeDialog(this, CModCodiciClassifDiagDlg::IDD, "ModCodiciClassifDiagDlg");
	return TRUE;
}

void CModCodiciClassifDiagDlg::OnOK()
{
	if(GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CModCodiciClassifDiagDlg::CaricaDati()
{
	CCodiciClassificazioneDiagnostSet setTemp;

	CString strTemp;
	strTemp.Format("ID=%li", m_lID);

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_DESCRIZIONE, "");
	SetDlgItemText(IDC_SCORE, "0");
	m_ctrlComboClassificazione.SetCurSel(0);
	m_ctrlButtonPositivita.SetCheck(BST_UNCHECKED);
	m_ctrlComboTipoEsame.SetCurSel(0);

	setTemp.SetOpenFilter(strTemp);
	if(setTemp.OpenRecordset("CModCodiciClassifDiagDlg::CaricaDati"))
	{
		if(!setTemp.IsEOF())
		{
			SetDlgItemText(IDC_CODICE, setTemp.m_sCodice);
			SetDlgItemText(IDC_DESCRIZIONE, setTemp.m_sDescrizione);
			m_ctrlComboClassificazione.SetCurSel(setTemp.m_lClassificazione);
			if(setTemp.m_bPositivita)
				m_ctrlButtonPositivita.SetCheck(BST_CHECKED);

			for(int i = 0; i < m_ctrlComboTipoEsame.GetCount(); i++)
			{
				if((long)m_ctrlComboTipoEsame.GetItemData(i) == setTemp.m_lIDTipoEsame)
				{
					m_ctrlComboTipoEsame.SetCurSel(i);
					break;
				}
			}

			m_fScore = setTemp.m_fScore;
			UpdateData(FALSE);

			GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
		}

		setTemp.CloseRecordset("CModCodiciClassifDiagDlg::CaricaDati");
	}
}

void CModCodiciClassifDiagDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_DESCRIZIONE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_SCORE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	m_ctrlComboClassificazione.EnableWindow(bEdit);
	GetDlgItem(IDC_POSITIVITA)->EnableWindow(bEdit);
	m_ctrlComboTipoEsame.EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
	// GetDlgItem(IDOK)->EnableWindow(!bEdit);
}

void CModCodiciClassifDiagDlg::RiempiCombos()
{
	m_ctrlComboClassificazione.ResetContent();
	m_ctrlComboClassificazione.InsertString(0, "");
	m_ctrlComboClassificazione.InsertString(1, theApp.GetMessageString(IDS_CLASSIFICAZIONEDIAGNOSI_NEGATIVO));
	m_ctrlComboClassificazione.InsertString(2, theApp.GetMessageString(IDS_CLASSIFICAZIONEDIAGNOSI_PREMALIGNO));
	m_ctrlComboClassificazione.InsertString(3, theApp.GetMessageString(IDS_CLASSIFICAZIONEDIAGNOSI_MALIGNO));
	m_ctrlComboClassificazione.SetCurSel(0);

	///

	m_ctrlComboTipoEsame.ResetContent();
	m_ctrlComboTipoEsame.InsertString(0, theApp.GetMessageString(IDS_TUTTI));
	m_ctrlComboTipoEsame.SetItemData(0, (DWORD)0);

	CTipoEsameSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if(setTemp.OpenRecordset("CModCodiciClassifDiagDlg::RiempiCombos"))
	{
		int nIndex = 1;

		while(!setTemp.IsEOF())
		{
			m_ctrlComboTipoEsame.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlComboTipoEsame.SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CModCodiciClassifDiagDlg::RiempiCombos");
	}
}

void CModCodiciClassifDiagDlg::RiempiLista()
{
	CCodiciClassificazioneDiagnostSet setTemp;

	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	setTemp.SetSortRecord("Descrizione");
	if(setTemp.OpenRecordset("CModCodiciClassifDiagDlg::RiempiLista"))
	{
		while(!setTemp.IsEOF())
		{
			int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), setTemp.m_sCodice);
			m_ctrlList.SetItemText(nItem, 1, setTemp.m_sDescrizione);
			m_ctrlList.SetItemData(nItem, (DWORD)setTemp.m_lID);
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CModCodiciClassifDiagDlg::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CModCodiciClassifDiagDlg::UnselectAll()
{
	if(m_ctrlList.GetItemCount() > 0)
	{
		for(int i = 0; i < m_ctrlList.GetItemCount(); i++)
			m_ctrlList.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedList(NULL, NULL);
	}
}

void CModCodiciClassifDiagDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lID = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if(pos != NULL)
		m_lID = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CModCodiciClassifDiagDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CModCodiciClassifDiagDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CModCodiciClassifDiagDlg::OnBnClickedBtnDel()
{
	if(AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if(m_lID > 0)
		{
			CString strFilter;
			strFilter.Format("ID=%li", m_lID);

			CCodiciClassificazioneDiagnostSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if(setTemp.OpenRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnDel"))
			{
				if(!setTemp.IsEOF())
				{
					if(setTemp.EditRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnDel"))
					{
						setTemp.m_bEliminato = TRUE;

						setTemp.UpdateRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnDel");
					}
				}

				setTemp.CloseRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnDel");
			}
		}

		UnselectAll();
		RiempiLista();
	}
}

void CModCodiciClassifDiagDlg::OnBnClickedBtnSave()
{
	if(!UpdateData(TRUE))
		return;

	CString strTemp;

	GetDlgItemText(IDC_DESCRIZIONE, strTemp);
	strTemp.Trim();

	if(!strTemp.IsEmpty())
	{
		CCodiciClassificazioneDiagnostSet setTemp;

		if(m_lID <= 0)
		{
			// addnew //

			if(setTemp.OpenRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave"))
			{
				if(setTemp.AddNewRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave"))
				{
					GetDlgItemText(IDC_CODICE, setTemp.m_sCodice);
					GetDlgItemText(IDC_DESCRIZIONE, setTemp.m_sDescrizione);
					setTemp.m_lClassificazione = m_ctrlComboClassificazione.GetCurSel();
					setTemp.m_bPositivita = (m_ctrlButtonPositivita.GetCheck() == BST_CHECKED);
					setTemp.m_fScore = m_fScore;
					setTemp.m_lIDTipoEsame = (long)m_ctrlComboTipoEsame.GetItemData(m_ctrlComboTipoEsame.GetCurSel());
					setTemp.m_bEliminato = FALSE;

					setTemp.UpdateRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave");
				}

				setTemp.CloseRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			// edit //

			CString strFilter;
			strFilter.Format("ID=%li", m_lID);

			setTemp.SetOpenFilter(strFilter);

			if(setTemp.OpenRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave"))
			{
				if(!setTemp.IsEOF())
				{
					if(setTemp.EditRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave"))
					{
						GetDlgItemText(IDC_CODICE, setTemp.m_sCodice);
						GetDlgItemText(IDC_DESCRIZIONE, setTemp.m_sDescrizione);
						setTemp.m_lClassificazione = m_ctrlComboClassificazione.GetCurSel();
						setTemp.m_bPositivita = (m_ctrlButtonPositivita.GetCheck() == BST_CHECKED);
						setTemp.m_fScore = m_fScore;
						setTemp.m_lIDTipoEsame = (long)m_ctrlComboTipoEsame.GetItemData(m_ctrlComboTipoEsame.GetCurSel());

						setTemp.UpdateRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave");
					}
				}

				setTemp.CloseRecordset("CModCodiciClassifDiagDlg::OnBnClickedBtnSave");
			}
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

void CModCodiciClassifDiagDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}