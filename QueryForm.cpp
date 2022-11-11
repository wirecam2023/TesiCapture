#include "stdafx.h"
#include "Endox.h"
#include "QueryForm.h"

#include "QueryFormListDlg.h"
#include "StoreableCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CQueryForm, CEndoxResizableDlg)

CQueryForm::CQueryForm(BOOL bMultiSelect, BOOL bFreeFieldAccepted)
	: CEndoxResizableDlg(bMultiSelect ? CQueryForm::IDD : CQueryForm::IDD_SINGLE, NULL)
{
	m_bChangingCode = m_bChangingDescription = FALSE;
	m_bMultiSelect = bMultiSelect;
	m_bFreeFieldAccepted = bFreeFieldAccepted;
	m_bNotifyParentWnd = TRUE;

	m_lItemSelected = 0;
	m_strItemSelected = "";
	m_bItemSelectedFree = FALSE;

	m_lFiltro1ID = 0;
	m_lFiltro2ID = 0;
}

void CQueryForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_BUTTON_CODICE, m_ctrlButtonCodice);
	DDX_Control(pDX, IDC_BUTTON_DESCRIZIONE, m_ctrlButtonDescrizione);

	if (m_bMultiSelect)
	{
		DDX_Control(pDX, IDC_CHECK_TUTTI, m_ctrlCheckTutti);
		DDX_Control(pDX, IDC_CHECK_ESCLUDI, m_ctrlCheckEscludi);
		DDX_Control(pDX, IDC_LIST, m_ctrlList);
	}
}

BEGIN_MESSAGE_MAP(CQueryForm, CEndoxResizableDlg)
	ON_MESSAGE(WM_NOTIFY_DELETE_STRING_LISTBOX, OnNotifyDeleteStringListBox)
	ON_MESSAGE(WM_NOTIFY_EMPTY_LISTBOX,         OnNotifyEmptyListBox)

	ON_BN_CLICKED(IDC_CHECK_TUTTI,        OnCheckButtonTutti)
	ON_BN_CLICKED(IDC_CHECK_ESCLUDI,      OnCheckButtonEscludi)
	ON_BN_CLICKED(IDC_BUTTON_DESCRIZIONE, OnButtonDescrizione)
	ON_BN_CLICKED(IDC_BUTTON_CODICE,      OnButtonCodice)

	ON_EN_CHANGE(IDC_EDIT_CODICE,      OnEnChangeCode)
	ON_EN_CHANGE(IDC_EDIT_DESCRIZIONE, OnEnChangeDescription)
END_MESSAGE_MAP()

BOOL CQueryForm::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	theApp.LocalizeDialog(this, CQueryForm::IDD, "QueryForm");

	AddAnchor(IDC_EDIT_CODICE,        CSize(  0, 0), CSize(  0, 0));
	AddAnchor(IDC_BUTTON_CODICE,      CSize(  0, 0), CSize(  0, 0));
	AddAnchor(IDC_EDIT_DESCRIZIONE,   CSize(  0, 0), CSize(100, 0));
	AddAnchor(IDC_BUTTON_DESCRIZIONE, CSize(100, 0), CSize(100, 0));

	/*
	if(theApp.m_bMilano)
	{
		GetDlgItem(IDC_EDIT_CODICE)->ModifyStyle(0, ES_UPPERCASE);
		GetDlgItem(IDC_EDIT_DESCRIZIONE)->ModifyStyle(0, ES_UPPERCASE);
	}
	*/

	if(m_bMultiSelect)
	{
		AddAnchor(IDC_CHECK_TUTTI,        CSize(  0, 0), CSize(  0, 0));
		AddAnchor(IDC_LIST,               CSize(  0, 0), CSize(100, 100));
		AddAnchor(IDC_FRAME,              CSize(  0, 0), CSize(100, 100));

		CStoreableCtrl::Get()->Bind(m_ctrlList.GetSafeHwnd(), m_strTitle + " list");
		CStoreableCtrl::Get()->Bind(m_ctrlCheckTutti.GetSafeHwnd(), m_strTitle + " check");
		CStoreableCtrl::Get()->Bind(m_ctrlCheckEscludi.GetSafeHwnd(), m_strTitle + " check2");

		SetDlgItemText(IDC_FRAME, m_strTitle);
		m_ctrlCheckTutti.SetCheck(BST_CHECKED);
		m_ctrlCheckEscludi.EnableWindow(FALSE);
	}

	return TRUE;
}

void CQueryForm::OnCheckButtonTutti()
{
	ASSERT(m_bMultiSelect);

	if (m_ctrlCheckTutti.GetCheck() == BST_CHECKED)
	{
		SetDlgItemText(IDC_EDIT_DESCRIZIONE, "");
		SetDlgItemText(IDC_EDIT_CODICE, "");
		m_ctrlList.ResetContent();

		m_ctrlCheckEscludi.SetCheck(BST_UNCHECKED);
	}
	else
	{
		if (m_ctrlList.GetCount() == 0)
			m_ctrlCheckTutti.SetCheck(BST_CHECKED);
	}

	m_ctrlCheckEscludi.EnableWindow(m_ctrlCheckTutti.GetCheck() == BST_UNCHECKED);

	if (m_bNotifyParentWnd)
		GetParent()->PostMessage(WM_QUERY_FORM_CHANGED, (WPARAM)GetSafeHwnd());
}

void CQueryForm::OnCheckButtonEscludi()
{
}

void CQueryForm::OnEnChangeDescription()
{
	if (m_bMultiSelect || m_bChangingDescription || m_bItemSelectedFree)
		return;

	if (m_lItemSelected > 0)
		GetParent()->PostMessage(WM_QUERY_FORM_RESET, (WPARAM)GetSafeHwnd());

	m_lItemSelected = 0;
	m_strItemSelected = "";
	m_bItemSelectedFree = FALSE;

	m_bChangingCode = TRUE;
	SetDlgItemText(IDC_EDIT_CODICE, "");
	m_bChangingCode = FALSE;
}

void CQueryForm::OnEnChangeCode()
{
	if (m_bMultiSelect || m_bChangingCode)
		return;

	if (m_lItemSelected > 0)
		GetParent()->PostMessage(WM_QUERY_FORM_RESET, (WPARAM)GetSafeHwnd());

	m_lItemSelected = 0;
	m_strItemSelected = "";
	m_bItemSelectedFree = FALSE;

	m_bChangingDescription = TRUE;
	SetDlgItemText(IDC_EDIT_DESCRIZIONE, "");
	m_bChangingDescription = FALSE;
}

void CQueryForm::OnButtonDescrizione()
{
	TRACE("--> CQueryForm::OnButtonDescrizione\n");

	m_ctrlButtonDescrizione.SetCheck(BST_UNCHECKED);

	SearchByDescription();

	if(!m_bMultiSelect)
		GetDlgItem(IDC_EDIT_DESCRIZIONE)->SetFocus();
}

void CQueryForm::OnButtonCodice()
{
	TRACE("--> CQueryForm::OnButtonCodice\n");

	m_ctrlButtonCodice.SetCheck(BST_UNCHECKED);

	SearchByCode();

	if(!m_bMultiSelect)
		GetDlgItem(IDC_EDIT_CODICE)->SetFocus();
}

void CQueryForm::OnOK()
{
	TRACE("--> CQueryForm::OnOK\n");

	if(GetFocus() == GetDlgItem(IDC_EDIT_CODICE))
	{
		if(SearchByCode())
			GetParent()->PostMessage(WM_QUERY_FORM_OK, (WPARAM)GetSafeHwnd());
	}
	else if(GetFocus() == GetDlgItem(IDC_EDIT_DESCRIZIONE))
	{
		if(SearchByDescription())
			GetParent()->PostMessage(WM_QUERY_FORM_OK, (WPARAM)GetSafeHwnd());
	}
}

LRESULT CQueryForm::OnNotifyDeleteStringListBox(WPARAM wParam, LPARAM lParam)
{
	if (m_bNotifyParentWnd)
		GetParent()->PostMessage(WM_QUERY_FORM_CHANGED, (WPARAM)GetSafeHwnd());
	return 1;
}

LRESULT CQueryForm::OnNotifyEmptyListBox(WPARAM wParam, LPARAM lParam)
{
	if (m_ctrlList.GetSafeHwnd() == (HWND)wParam)
	{
		m_ctrlCheckTutti.SetCheck(BST_CHECKED);
		m_ctrlCheckEscludi.SetCheck(BST_UNCHECKED);
		m_ctrlCheckEscludi.EnableWindow(FALSE);
	}
	return 0;
}

void CQueryForm::GetItemSelected(CList<long>* pList)
{
	ASSERT(m_bMultiSelect && GetSafeHwnd());

	pList->RemoveAll();
	for (int i = 0; i < m_ctrlList.GetCount(); i++)
		pList->AddTail((long)m_ctrlList.GetItemData(i));
}

void CQueryForm::SetItemSelected(const CList<long>* pList)
{
	ASSERT(m_bMultiSelect && GetSafeHwnd());

	Empty();
	for (POSITION pos = pList->GetHeadPosition(); pos;)
		SetItemSelectedID(pList->GetNext(pos));
}

void CQueryForm::StoreData(CQueryFormRemember* pObj)
{
	ASSERT(m_bMultiSelect && GetSafeHwnd());

	GetItemSelected(&pObj->m_listSelected);
	pObj->m_bEscludi = (m_ctrlCheckEscludi.GetCheck() == BST_CHECKED);
}

void CQueryForm::LoadData(CQueryFormRemember* pObj)
{
	ASSERT(m_bMultiSelect && GetSafeHwnd());

	for (POSITION pos = pObj->m_listSelected.GetHeadPosition(); pos;)
		SetItemSelectedID(pObj->m_listSelected.GetNext(pos));
	m_ctrlCheckEscludi.SetCheck(pObj->m_bEscludi ? BST_CHECKED : BST_UNCHECKED);
}

long CQueryForm::GetItemSelectedID()
{
	ASSERT(!m_bMultiSelect);
	return m_lItemSelected;
}

BOOL CQueryForm::GetItemSelectedFree()
{
	ASSERT(!m_bMultiSelect);
	return m_bItemSelectedFree;
}

void CQueryForm::SetItemSelectedID(long lID)
{
	if (m_strQuery.IsEmpty())
		return;

	CString strQueryEqual;
	if (m_strQuery.Left(6) == "SELECT")
	{
		if (m_strQuery.Find("WHERE") > 0)
		{
			strQueryEqual.Format("%s AND ID = %li", m_strQuery, lID);
		}
		else
		{
			strQueryEqual.Format("%s WHERE ID = %li", m_strQuery, lID);
		}
	}
	else
	{
		if (m_bFreeFieldAccepted)
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO FROM %s WHERE ID = %li AND ELIMINATO = 0", m_strQuery, lID);
		else
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO FROM %s WHERE ID = %li AND ELIMINATO = 0", m_strQuery, lID);
	}

	ExecuteSearch(strQueryEqual, "");
}

CString CQueryForm::GetItemSelectedCode()
{
	ASSERT(!m_bMultiSelect);

	CString str;
	if (m_lItemSelected > 0)
		GetDlgItem(IDC_EDIT_CODICE)->GetWindowText(str);
	return str;
}

void CQueryForm::SetItemSelectedDesc(CString str)
{
	ASSERT(!m_bMultiSelect);
	ASSERT(m_bItemSelectedFree);

	GetDlgItem(IDC_EDIT_DESCRIZIONE)->SetWindowText(str);
}

CString CQueryForm::GetItemSelectedDesc()
{
	CString strReturn;
	if (m_bMultiSelect)
	{
		for (int i = 0; i < m_ctrlList.GetCount(); i++)
		{
			if (!strReturn.IsEmpty())
				strReturn += " - ";
			
			CString str;
			m_ctrlList.GetText(i, str);
			strReturn += str;
		}
	}
	else if (m_bItemSelectedFree)
	{
		if (m_lItemSelected > 0)
			GetDlgItem(IDC_EDIT_DESCRIZIONE)->GetWindowText(strReturn);
	}
	else
	{
		if (m_lItemSelected > 0)
		{
			CString strDescription;
			GetDlgItem(IDC_EDIT_DESCRIZIONE)->GetWindowText(strDescription);
			strReturn = strDescription;
		}
	}

	return strReturn;
}

void CQueryForm::GetDescriptionForPrint(CString* pDescription)
{
	CString strDescription;
	if (m_bMultiSelect)
	{
		for (int i = 0; i < m_ctrlList.GetCount(); i++)
		{
			if (!strDescription.IsEmpty())
				strDescription += ";";
			
			CString str;
			m_ctrlList.GetText(i, str);
			
			int iFind = str.Find(" - ");
			if (iFind > 0)
				str = str.Mid(iFind + 3);
			strDescription += str;
		}
	}
	else if (m_lItemSelected > 0)
		GetDlgItem(IDC_EDIT_DESCRIZIONE)->GetWindowText(strDescription);

	if (strDescription.IsEmpty())
		return;

	if (!pDescription->IsEmpty())
		pDescription->Append(" - ");

	CString strTitle;
	GetDlgItemText(IDC_FRAME, strTitle);
	strTitle += ": ";
	pDescription->Append(strTitle);
	pDescription->Append(strDescription);
}

CString CQueryForm::GetItemSelectedDesc2()
{
	CString strReturn;
	if (m_bMultiSelect)
	{
		for (int i = 0; i < m_ctrlList.GetCount(); i++)
		{
			if (!strReturn.IsEmpty())
				strReturn += " - ";
			
			CString str;
			m_ctrlList.GetText(i, str);
			strReturn += str;
		}
	}
	else if (m_bItemSelectedFree)
	{
		if (m_lItemSelected > 0)
			GetDlgItem(IDC_EDIT_DESCRIZIONE)->GetWindowText(strReturn);
	}
	else
	{
		if (m_lItemSelected > 0)
		{
			CString strCode, strDescription;
			if (GetDlgItem(IDC_EDIT_CODICE))
				GetDlgItem(IDC_EDIT_CODICE)->GetWindowText(strCode);
			if (GetDlgItem(IDC_EDIT_DESCRIZIONE))
				GetDlgItem(IDC_EDIT_DESCRIZIONE)->GetWindowText(strDescription);
			strReturn = strCode + " - " + strDescription;
		}
	}

	return strReturn;
}

void CQueryForm::SetMultiSelect(BOOL bMultiSelect, BOOL bFreeFieldAccepted)
{
	ASSERT(GetSafeHwnd() == NULL);

	m_lpszTemplateName = MAKEINTRESOURCE(bMultiSelect ? CQueryForm::IDD : CQueryForm::IDD_SINGLE);
	m_bMultiSelect = bMultiSelect;
	m_bFreeFieldAccepted = bFreeFieldAccepted;
}

void CQueryForm::SetFiltro(long lFiltro1ID, long lFiltro2ID, CString strName)
{
	m_lFiltro1ID = lFiltro1ID;
	m_lFiltro2ID = lFiltro2ID;
	m_strName = strName;
}

BOOL CQueryForm::CreateForm(UINT iPlace, CWnd* pParentWnd, CString strTitle)
{
	m_strTitle = strTitle;

	CRect rect;
	pParentWnd->GetDlgItem(iPlace)->ShowWindow(SW_HIDE);
	pParentWnd->GetDlgItem(iPlace)->GetWindowRect(&rect);
	pParentWnd->ScreenToClient(&rect);

	if (!CEndoxResizableDlg::Create(m_lpszTemplateName, pParentWnd))
		return FALSE;

	SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	return TRUE;
}

void CQueryForm::SetQuery(CString strQuery)
{
	m_strQuery = strQuery;
	m_strQuery.MakeUpper();
}

void CQueryForm::GetFilterString(CString* pFilter, CString strDatabaseField)
{
	ASSERT(m_bMultiSelect);
	GetListboxFilter(pFilter, strDatabaseField, this, IDC_LIST, m_ctrlCheckEscludi.GetCheck() == BST_CHECKED);
}

void CQueryForm::GetFilterStringText(CString* pFilter, CString strDatabaseField)
{
	ASSERT(m_bMultiSelect);
	GetListboxFilterText(pFilter, strDatabaseField, this, IDC_LIST, m_ctrlCheckEscludi.GetCheck() == BST_CHECKED);
}

void CQueryForm::Enable(BOOL bEnable)
{
	((CEdit*)GetDlgItem(IDC_EDIT_CODICE))->SetReadOnly(!bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_DESCRIZIONE))->SetReadOnly(!bEnable);
	
	GetDlgItem(IDC_BUTTON_DESCRIZIONE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_CODICE)->EnableWindow(bEnable);

	if (GetDlgItem(IDC_CHECK_TUTTI))
		GetDlgItem(IDC_CHECK_TUTTI)->EnableWindow(bEnable);
	
	if (GetDlgItem(IDC_CHECK_ESCLUDI))
		GetDlgItem(IDC_CHECK_ESCLUDI)->EnableWindow(bEnable);

	if (GetDlgItem(IDC_LIST))
		GetDlgItem(IDC_LIST)->EnableWindow(bEnable);
}

void CQueryForm::Empty()
{
	if (m_bMultiSelect)
	{
		m_ctrlCheckTutti.SetCheck(BST_CHECKED);
		m_ctrlCheckEscludi.SetCheck(BST_UNCHECKED);
		m_ctrlCheckEscludi.EnableWindow(FALSE);
		m_ctrlList.ResetContent();
	}

	m_bChangingCode = TRUE;
	SetDlgItemText(IDC_EDIT_CODICE, "");
	m_bChangingCode = FALSE;

	m_bChangingDescription = TRUE;
	SetDlgItemText(IDC_EDIT_DESCRIZIONE, "");
	m_bChangingDescription = FALSE;

	m_lItemSelected = 0;
	m_strItemSelected = "";
	m_bItemSelectedFree = FALSE;
}

HWND CQueryForm::GetSafeHwnd()
{
	return CEndoxResizableDlg::GetSafeHwnd();
}

CWnd* CQueryForm::GetCWnd()
{
	return (CWnd*)this;
}

BOOL CQueryForm::SearchByCode()
{
	if(m_strQuery.IsEmpty())
		return FALSE;

	CString str;
	GetDlgItemText(IDC_EDIT_CODICE, str);
	str.MakeUpper();
	str.Replace("'", "''");

	CString strFiltro;
	if (m_lFiltro1ID > 0)
		strFiltro += ", FILTRO1";
	if (m_lFiltro2ID > 0)
		strFiltro += ", FILTRO2";

	CString strQueryEqual, strQueryLike;
	if(m_strQuery.Left(6) == "SELECT")
	{
		if (m_bFreeFieldAccepted)
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM (%s) A WHERE UPPER(CODICE)='%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);

			if (str.Find("%") >= 0)
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM (%s) A WHERE UPPER(CODICE) LIKE '%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
			else
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM (%s) A WHERE UPPER(CODICE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
		}
		else
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM (%s) A WHERE UPPER(CODICE)='%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);

			if (str.Find("%") >= 0)
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM (%s) A WHERE UPPER(CODICE) LIKE '%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
			else
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM (%s) A WHERE UPPER(CODICE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
		}
	}
	else
	{
		if (m_bFreeFieldAccepted)
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM %s WHERE UPPER(CODICE)='%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);

			if (str.Find("%") >= 0)
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM %s WHERE UPPER(CODICE) LIKE '%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
			else
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM %s WHERE UPPER(CODICE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
		}
		else
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM %s WHERE UPPER(CODICE)='%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);

			if (str.Find("%") >= 0)
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM %s WHERE UPPER(CODICE) LIKE '%s' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
			else
				strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM %s WHERE UPPER(CODICE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY CODICE", strFiltro, m_strQuery, str);
		}
	}

	BOOL bReturn = ExecuteSearch(strQueryEqual, strQueryLike);
	if(!bReturn)
	{
		CString strError;
		strError.Format("Nessuna corrispondenza trovata per il codice '%s'!", str);
		AfxMessageBox(strError, MB_ICONSTOP);
	}

	return bReturn;
}

BOOL CQueryForm::SearchByDescription()
{
	if(m_strQuery.IsEmpty())
		return FALSE;

	CString str;
	GetDlgItemText(IDC_EDIT_DESCRIZIONE, str);
	str.MakeUpper();
	str.Replace("'", "''");

	CString strFiltro;
	if (m_lFiltro1ID > 0)
		strFiltro += ", FILTRO1";
	if (m_lFiltro2ID > 0)
		strFiltro += ", FILTRO2";

	CString strQueryEqual, strQueryLike;
	if(m_strQuery.Left(6) == "SELECT")
	{
		if (m_bFreeFieldAccepted)
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM (%s) A WHERE UPPER(DESCRIZIONE)='%s' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
			strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM (%s) A WHERE UPPER(DESCRIZIONE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
		}
		else
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM (%s) A WHERE UPPER(DESCRIZIONE)='%s' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
			strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM (%s) A WHERE UPPER(DESCRIZIONE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
		}
	}
	else
	{
		if (m_bFreeFieldAccepted)
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM %s WHERE UPPER(DESCRIZIONE)='%s' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
			strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, LIBERO%s FROM %s WHERE UPPER(DESCRIZIONE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
		}
		else
		{
			strQueryEqual.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM %s WHERE UPPER(DESCRIZIONE)='%s' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
			strQueryLike.Format("SELECT ID, CODICE, DESCRIZIONE, 0 AS LIBERO%s FROM %s WHERE UPPER(DESCRIZIONE) LIKE '%%%s%%' AND ELIMINATO=0 ORDER BY DESCRIZIONE", strFiltro, m_strQuery, str);
		}
	}

	BOOL bReturn = ExecuteSearch(strQueryEqual, strQueryLike);
	if(!bReturn)
	{
		CString strError;
		strError.Format("Nessuna corrispondenza trovata per '%s'!", str);
		AfxMessageBox(strError, MB_ICONSTOP);
	}

	return bReturn;
}

BOOL CQueryForm::IsItemPresent(long lID)
{
	ASSERT(m_bMultiSelect);

	BOOL bFound = FALSE;
	for (int i = 0; i < m_ctrlList.GetCount(); i++)
	{
		if (m_ctrlList.GetItemData(i) == lID)
		{
			bFound = TRUE;
			break;
		}
	}

	return bFound;
}

BOOL CQueryForm::ExecuteSearch(CString strQueryEqual, CString strQueryLike)
{
	ASSERT(!strQueryEqual.IsEmpty());
	BOOL bReturn = TRUE;

	CTableSet set(m_lFiltro1ID > 0, m_lFiltro2ID > 0);

	try
	{
		BeginWaitCursor();
		set.Open(CRecordset::snapshot, strQueryEqual, CRecordset::readOnly | CRecordset::useMultiRowFetch);
		if(!set.IsEOF())
		{
			if(m_bMultiSelect)
			{
				if(!IsItemPresent(set.GetID(0)))
				{
					int iIndex = m_ctrlList.InsertString(m_ctrlList.GetCount(), set.GetCodice(0) + " - " + set.GetDescrizione(0));
					m_ctrlList.SetItemData(iIndex, set.GetID(0));
				}

				SetDlgItemText(IDC_EDIT_CODICE, "");
				SetDlgItemText(IDC_EDIT_DESCRIZIONE, "");
				
				m_ctrlCheckTutti.SetCheck(BST_UNCHECKED);
				m_ctrlCheckEscludi.EnableWindow(TRUE);

				if (m_bNotifyParentWnd)
					GetParent()->PostMessage(WM_QUERY_FORM_CHANGED, (WPARAM)GetSafeHwnd());
			}
			else
			{
				/* Davide 20151210
				m_lItemSelected = set.GetID(0);
				m_strItemSelected = set.GetDescrizione(0);
				m_bItemSelectedFree = set.GetLibero(0);
				*/

				// Provo a dare la precedenza ad un elemento specifico...
				CList<CQueryFormListDlg::tagITEM> listItems;
				while(!set.IsEOF())
				{
					for(DWORD i = 0; i < set.GetRowsFetched(); i++)
					{
						CQueryFormListDlg::tagITEM item;
						item.lContatore = set.GetID(i);
						strcpy_s(item.szCodice, set.GetCodice(i));
						strcpy_s(item.szDescrizione, set.GetDescrizione(i));
						item.bLibero = set.GetLibero(i);
						
						listItems.AddTail(item);
					}

					set.MoveNext();
				}

				int iIndex = 0;

				m_lItemSelected = listItems.GetAt(listItems.FindIndex(iIndex)).lContatore;
				m_strItemSelected = listItems.GetAt(listItems.FindIndex(iIndex)).szDescrizione;
				m_bItemSelectedFree = listItems.GetAt(listItems.FindIndex(iIndex)).bLibero;

				m_bChangingCode = TRUE;
				SetDlgItemText(IDC_EDIT_CODICE, listItems.GetAt(listItems.FindIndex(iIndex)).szCodice);
				m_bChangingCode = FALSE;

				m_bChangingDescription = TRUE;
				SetDlgItemText(IDC_EDIT_DESCRIZIONE, listItems.GetAt(listItems.FindIndex(iIndex)).szDescrizione);
				m_bChangingDescription = FALSE;

				if (m_bNotifyParentWnd)
					GetParent()->PostMessage(WM_QUERY_FORM_CHANGED, (WPARAM)GetSafeHwnd());
			}
		}
		else if(!strQueryLike.IsEmpty())
		{
			set.Close();
			set.Open(CRecordset::snapshot, strQueryLike, CRecordset::readOnly | CRecordset::useMultiRowFetch);
			if(!set.IsEOF())
			{
				CList<CQueryFormListDlg::tagITEM> listItems;
				while(!set.IsEOF())
				{
					for(DWORD i = 0; i < set.GetRowsFetched(); i++)
					{
						CQueryFormListDlg::tagITEM item;
						item.lContatore = set.GetID(i);
						strcpy_s(item.szCodice, set.GetCodice(i));
						strcpy_s(item.szDescrizione, set.GetDescrizione(i));
						item.bLibero = set.GetLibero(i);
						
						listItems.AddTail(item);
					}

					set.MoveNext();
				}

				CRect rectEdit;
				GetDlgItem(IDC_EDIT_CODICE)->GetWindowRect(&rectEdit);
				CQueryFormListDlg dlg(this, CPoint(rectEdit.left, rectEdit.bottom), &listItems, -1, m_bMultiSelect);
				if(dlg.DoModal() == IDOK)
				{
					BeginWaitCursor();
					if(m_bMultiSelect)
					{
						CList<CQueryFormListDlg::tagITEM> listSelected;
						dlg.GetItemsSelected(&listSelected);

						for (POSITION pos = listSelected.GetHeadPosition(); pos;)
						{
							CQueryFormListDlg::tagITEM item = listSelected.GetNext(pos);
							if(!IsItemPresent(item.lContatore))
							{
								int iIndex = m_ctrlList.InsertString(m_ctrlList.GetCount(), CString(item.szCodice) + " - " + CString(item.szDescrizione));
								m_ctrlList.SetItemData(iIndex, item.lContatore);
							}
						}

						SetDlgItemText(IDC_EDIT_CODICE, "");
						SetDlgItemText(IDC_EDIT_DESCRIZIONE, "");
						
						m_ctrlCheckTutti.SetCheck(BST_UNCHECKED);
						m_ctrlCheckEscludi.EnableWindow(TRUE);

						if (m_bNotifyParentWnd)
							GetParent()->PostMessage(WM_QUERY_FORM_CHANGED, (WPARAM)GetSafeHwnd());
					}
					else
					{
						m_lItemSelected = dlg.GetItemSelected().lContatore;
						m_strItemSelected = dlg.GetItemSelected().szDescrizione;
						m_bItemSelectedFree = dlg.GetItemSelected().bLibero;

						m_bChangingCode = TRUE;
						SetDlgItemText(IDC_EDIT_CODICE, dlg.GetItemSelected().szCodice);
						m_bChangingCode = FALSE;

						m_bChangingDescription = TRUE;
						SetDlgItemText(IDC_EDIT_DESCRIZIONE, dlg.GetItemSelected().szDescrizione);
						m_bChangingDescription = FALSE;

						if (m_bNotifyParentWnd)
							GetParent()->PostMessage(WM_QUERY_FORM_CHANGED, (WPARAM)GetSafeHwnd());
					}
					EndWaitCursor();
				}
			}
			else
			{
				bReturn = FALSE;
			}
		}
		else
		{
			bReturn = FALSE;
		}
	}
	catch(CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	catch(CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	if(set.IsOpen())
		set.Close();

	EndWaitCursor();

	return bReturn;
}

BOOL CQueryForm::ShowWindow(int nCmdShow)
{
	return CWnd::ShowWindow(nCmdShow);
}

//
//
//


CQueryForm::CTableSet::CTableSet(BOOL bAddFilter1, BOOL bAddFilter2)
	: CAMBaseSet(&theApp.m_dbEndox)
{
	m_pID = 0;
	m_pCodice = 0;
	m_pDescrizione = 0;
	m_pLibero = 0;
	m_pFilter1ID = 0;
	m_pFilter2ID = 0;

	m_pIDLength = 0;
	m_pCodiceLength = 0;
	m_pDescrizioneLength = 0;
	m_pLiberoLength = 0;
	m_pFilter1IDLength = 0;
	m_pFilter2IDLength = 0;

	m_nFields = 4;
	if (bAddFilter1)
		m_nFields++;
	if (bAddFilter2)
		m_nFields++;

	m_bAddFilter1 = bAddFilter1;
	m_bAddFilter2 = bAddFilter2;
}

void CQueryForm::CTableSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long_Bulk(pFX, "ID", &m_pID, &m_pIDLength);
	RFX_Text_Bulk(pFX, "Codice", &m_pCodice, &m_pCodiceLength, 255);
	RFX_Text_Bulk(pFX, "Descrizione", &m_pDescrizione, &m_pDescrizioneLength, 1024);
	RFX_Bool_Bulk(pFX, "Libero", &m_pLibero, &m_pLiberoLength);

	if (m_bAddFilter1)
		RFX_Long_Bulk(pFX, "Filtro1", &m_pFilter1ID, &m_pFilter1IDLength);
	if (m_bAddFilter2)
		RFX_Long_Bulk(pFX, "Filtro2", &m_pFilter2ID, &m_pFilter2IDLength);
}

long CQueryForm::CTableSet::GetID(DWORD dwIndex)
{
	return m_pID[dwIndex];
}

CString CQueryForm::CTableSet::GetCodice(DWORD dwIndex)
{
	return m_pCodiceLength[dwIndex] > 0 ? m_pCodice + dwIndex * 255 : "";
}

CString CQueryForm::CTableSet::GetDescrizione(DWORD dwIndex)
{
	return m_pDescrizioneLength[dwIndex] > 0 ? m_pDescrizione + dwIndex * 1024 : "";
}

BOOL CQueryForm::CTableSet::GetLibero(DWORD dwIndex)
{
	return (m_pLiberoLength[dwIndex] > 0) ? m_pLibero[dwIndex] : FALSE;
}

long CQueryForm::CTableSet::GetFiltro1(DWORD dwIndex)
{
	return (m_pFilter1IDLength[dwIndex] > 0) ? m_pFilter1ID[dwIndex] : 0;
}

long CQueryForm::CTableSet::GetFiltro2(DWORD dwIndex)
{
	return (m_pFilter2IDLength[dwIndex] > 0) ? m_pFilter2ID[dwIndex] : 0;
}