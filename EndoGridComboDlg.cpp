#include "stdafx.h"
#include "Endox.h"
#include "EndoGridComboDlg.h"

#include "EndoGridCLComboSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridComboDlg, CXTResizeDialog)


CEndoGridComboDlg::CEndoGridComboDlg(long lParentItemID, CString strText, BOOL bAllowMultiSelect, CWnd* pParentWnd)
	: CXTResizeDialog(CEndoGridComboDlg::IDD, pParentWnd)
{
	m_bAllowMultiSelect = bAllowMultiSelect;
	m_lComboTable = lParentItemID;
	m_strEdit = strText;
}

CEndoGridComboDlg::~CEndoGridComboDlg()
{
}

void CEndoGridComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RESET, m_ctrlButtonReset);
	DDX_Control(pDX, IDC_ADD, m_ctrlButtonAdd);
	DDX_Control(pDX, IDC_REMOVE, m_ctrlButtonRemove);
	DDX_Control(pDX, IDC_DETAIL, m_ctrlButtonDetail);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_LIST, *GetListBox());
	DDX_Text(pDX, IDC_EDIT, m_strEdit);
}

BEGIN_MESSAGE_MAP(CEndoGridComboDlg, CXTResizeDialog)
	ON_LBN_SELCHANGE(IDC_LIST, OnLbnSelchangeList)
	ON_LBN_DBLCLK(IDC_LIST, OnLbnDblclkList)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_DETAIL, OnDetail)
	ON_EN_CHANGE(IDC_EDIT, OnEnChangeEdit)
END_MESSAGE_MAP()

BOOL CEndoGridComboDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_LIST, 0, 0, 1, 1);
	SetResize(IDC_RESET, 1, 0, 1, 0);
	SetResize(IDC_ADD, 1, 0, 1, 0);
	SetResize(IDC_REMOVE, 1, 0, 1, 0);
	SetResize(IDC_DETAIL, 1, 0, 1, 0);
	SetResize(IDC_EDIT, 0, 0, 1, 0);
	SetResize(IDCANCEL, 1, 1, 1, 1);
	SetResize(IDOK, 1, 1, 1, 1);

	FillList();

	if (!m_bAllowMultiSelect || m_strEdit.Find(" + ") == -1)
		SelectFromList();

	//
	EnlargeWndFromText();

	CString str = m_strEdit;
	((CEdit*)GetDlgItem(IDC_EDIT))->SetWindowText("");
	m_strEdit = str;
	UpdateData(FALSE);
	//

	theApp.LocalizeDialog(this, CEndoGridComboDlg::IDD, "EndoGridComboDlg");

	GetDlgItem(IDC_EDIT)->SetFocus();

	return FALSE;
}

void CEndoGridComboDlg::OnLbnSelchangeList()
{
	int iSel = GetListBox()->GetCurSel();
	if (iSel == LB_ERR)
		return;

	UpdateData(TRUE);

	if (m_bAllowMultiSelect)
	{
		CString str;
		GetListBox()->GetText(iSel, str);

		if (m_strEdit != str &&
			m_strEdit.Find(str + _T(" + ")) < 0 &&
			m_strEdit.Find(_T(" + ") + str) < 0)
		{
			if (!m_strEdit.IsEmpty())
				m_strEdit += _T(" + ");
			m_strEdit += str;
		}
	}
	else
		GetListBox()->GetText(iSel, m_strEdit);

	UpdateData(FALSE);
	EnlargeWndFromText();


	if (m_listRule.Find(GetListBox()->GetItemData(iSel)))
	{
		((CEdit*)GetDlgItem(IDC_EDIT))->SetReadOnly(TRUE);
		GetDlgItem(IDC_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_REMOVE)->EnableWindow(FALSE);
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT))->SetReadOnly(FALSE);		
	}
}

void CEndoGridComboDlg::OnLbnDblclkList()
{
	int iSel = GetListBox()->GetCurSel();
	if (iSel == LB_ERR)
		return;

	UpdateData(TRUE);
	GetListBox()->GetText(iSel, m_strEdit);
	UpdateData(FALSE);

	OnOK();
}

void CEndoGridComboDlg::OnEnChangeEdit()
{
	SelectFromList();
	EnlargeWndFromText();
}

void CEndoGridComboDlg::OnReset()
{
	m_strEdit.Empty();
	UpdateData(FALSE);
	SelectFromList();
}

void CEndoGridComboDlg::OnAdd()
{
	UpdateData(TRUE);

	if (m_strEdit.IsEmpty())
		return;

	CEndoGridCLComboSet set;

	try
	{
		if (set.OpenRecordset("CEndoGridComboDlg::OnAdd"))
		{
			if (set.AddNewRecordset("CEndoGridComboDlg::OnAdd"))
			{
				set.m_lIdparametro = m_lComboTable;
				set.m_sDescrizione = m_strEdit.Left(255);

				set.UpdateRecordset("CEndoGridComboDlg::OnAdd");
			}

			set.CloseRecordset("CEndoGridComboDlg::OnAdd");
		}

		FillList();
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	SelectFromList();


	GetDlgItem(IDC_EDIT)->SetWindowText("");
	GetDlgItem(IDC_EDIT)->SetFocus();

}

void CEndoGridComboDlg::OnRemove()
{
	int iSel = GetListBox()->GetCurSel();
	if (iSel == LB_ERR)
		return;

	m_strEdit.Empty();
	UpdateData(FALSE);

	CString strFilter;
	strFilter.Format("id = %li", GetListBox()->GetItemData(iSel));

	CEndoGridCLComboSet set;
	set.SetOpenFilter(strFilter);

	try
	{
		if (set.OpenRecordset("CEndoGridComboDlg::OnRemove"))
		{
			if (!set.IsEOF() && !set.IsBOF())
				set.DeleteRecordset("CEndoGridComboDlg::OnRemove");

			set.CloseRecordset("CEndoGridComboDlg::OnRemove");
		}

		GetListBox()->DeleteString(iSel);

	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	SelectFromList();
}

void CEndoGridComboDlg::FillList()
{
	CString strFilter;

	strFilter.Format("idparametro = %li", m_lComboTable);

	CEndoGridCLComboSet set;
	set.SetOpenFilter(strFilter);
	set.SetSortRecord("descrizione");
	GetListBox()->ResetContent();
	m_listRule.RemoveAll();

	try
	{
		if (set.OpenRecordset("CEndoGridComboDlg::FillList"))
		{
			while (!set.IsEOF())
			{
				int iInserted = GetListBox()->AddString(set.m_sDescrizione);
				GetListBox()->SetItemData(iInserted, (long)set.m_lId);				

				set.MoveNext();
			}

			set.CloseRecordset("CEndoGridComboDlg::FillList");
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}

void CEndoGridComboDlg::SelectFromList()
{
	UpdateData(TRUE);
	if (m_strEdit.IsEmpty())
	{
		GetListBox()->SetCurSel(-1);
		return;
	}

	CString strTmp;
	for (int i = 0; i < GetListBox()->GetCount(); i++)
	{
		GetListBox()->GetText(i, strTmp);
		if (m_strEdit.CompareNoCase(strTmp.Left(m_strEdit.GetLength())) == 0)
		{
			GetListBox()->SetCurSel(i);
			break;
		}
	}
}

void CEndoGridComboDlg::EnlargeWndFromText()
{
	CRect rectText(0, 0, 0, 0);
	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(GetFont());
	pDC->DrawText(m_strEdit + "AAA", &rectText, DT_CALCRECT | DT_LEFT);
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	CRect rectWnd, rectWndScreen;
	GetWindowRect(&rectWndScreen);
	rectWnd = rectWndScreen;
	ScreenToClient(&rectWnd);

	CRect rectEdit;
	GetDlgItem(IDC_EDIT)->GetWindowRect(&rectEdit);
	ScreenToClient(&rectEdit);

	CRect rectEditClient;
	GetDlgItem(IDC_EDIT)->GetClientRect(&rectEditClient);

	if (rectText.Width() > rectEdit.Width())
	{
		int iNewWidth = min(rectText.Width() + rectWnd.Width() - rectEdit.Width() + (rectEdit.Width() - rectEditClient.Width()),
			GetSystemMetrics(SM_CXSCREEN) - rectWndScreen.left);
		SetWindowPos(NULL,
			0,
			0,
			iNewWidth,
			rectWnd.Height(),
			SWP_NOZORDER | SWP_NOMOVE);
	}
}