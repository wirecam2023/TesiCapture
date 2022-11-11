#include "stdafx.h"
#include "Endox.h"
#include "ComboTransConfigDlg.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComboTransConfigDlg::CComboTransConfigDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CComboTransSet* pComboTransSet, CString sTitolo)
	: CDialog(CComboTransConfigDlg::IDD, pParentWnd)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_pComboTransSet = pComboTransSet;

	m_bAddNew = FALSE;
	m_bModify = FALSE;

	m_lIdCurSel = 0;

	m_sTitolo = sTitolo;
}

CComboTransConfigDlg::~CComboTransConfigDlg()
{
}

BEGIN_MESSAGE_MAP(CComboTransConfigDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBtnUndo)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CComboTransConfigDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()

void CComboTransConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW,		m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT,		m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DEL,		m_ctrlButtonDel);
	DDX_Control(pDX, IDC_BTN_SAVE,		m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO,		m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK,				m_ctrlButtonOK);

	DDX_Control(pDX, IDC_DESCRIZIONE,	m_ctrlEditDescrizione);
	DDX_Control(pDX, IDC_EXTCODE,		m_ctrlEditExtCode);

	DDX_Control(pDX, IDC_LIST1,			m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1,		m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2,		m_ctrlStatic2);
}

void CComboTransConfigDlg::OnCancel()
{
}

BOOL CComboTransConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);

	m_ctrlLista.SetExtendedStyle(m_ctrlLista.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	CRect rect;
	m_ctrlLista.GetClientRect(&rect);
	m_ctrlLista.InsertColumn(0, "Descrizione", 0, (rect.Width() / 3) * 2);
	m_ctrlLista.InsertColumn(1, "Codice Esterno", 0, (rect.Width() / 3));
	
	RiempiLista();
	
	theApp.LocalizeDialog(this, CComboTransConfigDlg::IDD, "ComboTransConfigDlg");

	SetWindowText(m_sTitolo);
	return TRUE;
}

void CComboTransConfigDlg::OnOK()
{
	int nCurPos = -1;
	POSITION pos = m_ctrlLista.GetFirstSelectedItemPosition();
	if (pos)
	{
		nCurPos = m_ctrlLista.GetNextSelectedItem(pos);
		m_strRicerca.Format("%li", m_ctrlLista.GetItemData(nCurPos));
		m_ctrlEditDescrizione.GetWindowText(m_strRicercaView);
	}
	else
	{
		m_strRicerca = "";
		m_strRicercaView = "";

	}

	if (m_ctrlButtonOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CComboTransConfigDlg::RiempiLista()
{
	m_ctrlLista.DeleteAllItems();

	m_pComboTransSet->SetOpenFilter("");
	m_pComboTransSet->SetBaseFilter("");

	if (m_pComboTransSet->OpenRecordset("CComboTransConfigDlg::RiempiLista"))
	{
		int i = 0;
		while(!m_pComboTransSet->IsEOF())
		{
			int nItem = m_ctrlLista.InsertItem(i, m_pComboTransSet->m_sDescrizione);
			//int nItem = m_ctrlLista.AddString(m_pComboTransSet->m_sDescrizione + " - " + m_pComboTransSet->m_sExtCode);

			if (nItem >= 0)
			{
				m_ctrlLista.SetItemText(nItem, 1, m_pComboTransSet->m_sExtCode);
				m_ctrlLista.SetItemData(nItem, (DWORD)m_pComboTransSet->m_lID);
			}

			m_pComboTransSet->MoveNext();

			i++;
		}

		m_pComboTransSet->CloseRecordset("CComboTransConfigDlg::RiempiLista");
	}
	
	PostMessage(LVN_ITEMCHANGED);
}

void CComboTransConfigDlg::OnBtnNew() 
{
	m_ctrlLista.EnableWindow(FALSE);
	m_ctrlEditDescrizione.EnableWindow(TRUE);
	m_ctrlEditExtCode.EnableWindow(TRUE);
	
	m_ctrlButtonNew.EnableWindow(FALSE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(TRUE);
	m_ctrlButtonUndo.EnableWindow(TRUE);
	m_ctrlButtonOK.EnableWindow(FALSE);

	m_ctrlEditExtCode.SetWindowText("");
	m_ctrlEditDescrizione.SetWindowText("");
	m_ctrlEditDescrizione.SetFocus();

	m_bAddNew = TRUE;
}

void CComboTransConfigDlg::OnBtnEdt() 
{
	if (m_lIdCurSel > 0)
	{
		m_ctrlLista.EnableWindow(FALSE);
		m_ctrlEditDescrizione.EnableWindow(TRUE);
		m_ctrlEditExtCode.EnableWindow(TRUE);
		
		m_ctrlButtonNew.EnableWindow(FALSE);
		m_ctrlButtonEdt.EnableWindow(FALSE);
		m_ctrlButtonDel.EnableWindow(FALSE);
		m_ctrlButtonSave.EnableWindow(TRUE);
		m_ctrlButtonUndo.EnableWindow(TRUE);
		m_ctrlButtonOK.EnableWindow(FALSE);

		m_ctrlEditDescrizione.SetFocus();

		m_bModify = TRUE;
	}		
}


void CComboTransConfigDlg::OnBtnDel() 
{	
	if (m_lIdCurSel > 0)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
		{
			if (m_pComboTransSet->Del(m_lIdCurSel))
				RiempiLista();
		}
	}
}

void CComboTransConfigDlg::OnBtnSave() 
{
	CString sDesc, sCode;
	m_ctrlEditDescrizione.GetWindowText(sDesc);
	m_ctrlEditExtCode.GetWindowText(sCode);

	sDesc.Trim();
	sCode.Trim();
	if (sDesc.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		m_pComboTransSet->Add(sDesc, sCode);
	}
	else if (m_bModify)		
	{
		if (m_lIdCurSel > 0)
			m_pComboTransSet->Edt(m_lIdCurSel, sDesc, sCode);
	}

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	m_ctrlEditExtCode.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiLista();
	
	m_bModify = FALSE;
	m_bAddNew = FALSE;
}

void CComboTransConfigDlg::OnBtnUndo() 
{
	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	m_ctrlEditExtCode.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiLista();

	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

void CComboTransConfigDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurPos = -1;
	POSITION pos = m_ctrlLista.GetFirstSelectedItemPosition();
	if (pos)
		nCurPos = m_ctrlLista.GetNextSelectedItem(pos);

	m_ctrlButtonEdt.EnableWindow(nCurPos >= 0);
	m_ctrlButtonDel.EnableWindow(nCurPos >= 0);

	if (nCurPos >= 0)
	{
		CString sDesc = m_ctrlLista.GetItemText(nCurPos, 0);
		CString sCode = m_ctrlLista.GetItemText(nCurPos, 1);
		m_ctrlEditDescrizione.SetWindowText(sDesc);
		m_ctrlEditExtCode.SetWindowText(sCode);
		m_lIdCurSel = m_ctrlLista.GetItemData(nCurPos);
	}
	else
	{
		m_ctrlEditDescrizione.SetWindowText("");
		m_ctrlEditExtCode.SetWindowText("");
		m_lIdCurSel = 0;
	}
}
