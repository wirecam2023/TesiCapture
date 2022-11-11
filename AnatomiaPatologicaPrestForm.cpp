#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaPrestForm.h"

#include "EsamiView.h"
#include "Common.h"
#include "EsamiSet.h"
#include "AnatomiaPatologicaPrestSet.h"
#include "AnatomiaPatologicaEsamiPrestSet.h"
#include "AnatomiaPatologicaPrestNewEdtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAnatomiaPatologicaPrestForm::CAnatomiaPatologicaPrestForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	m_wpReadOnly = (WPARAM)TRUE;
	m_bEsameOK = FALSE;
}

CAnatomiaPatologicaPrestForm::~CAnatomiaPatologicaPrestForm()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaPrestForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemChangedList)
END_MESSAGE_MAP()

void CAnatomiaPatologicaPrestForm::CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_anatomiapatologicaprest] == NULL)
	{
		pEsamiView->m_pDynForm[sub_anatomiapatologicaprest] = new CAnatomiaPatologicaPrestForm(nID, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_anatomiapatologicaprest] != NULL)
		{
			pEsamiView->m_pDynForm[sub_anatomiapatologicaprest]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_anatomiapatologicaprest]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_anatomiapatologicaprest]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_anatomiapatologicaprest]->CreateChildForm(nID, pParent, rectFrame);
		}
	}
}

BOOL CAnatomiaPatologicaPrestForm::CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CAnatomiaPatologicaPrestForm** pForm)
{
	BOOL bResult = FALSE;

	if ((*pForm) == NULL)
	{
		(*pForm) = new CAnatomiaPatologicaPrestForm(nID, NULL, pEsamiView);
		if ((*pForm) != NULL)
		{
			(*pForm)->m_pParentFrame = pParentFrame;
			(*pForm)->m_lColore = -1;
			(*pForm)->m_lIDFaseBlocco = 2;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pParent->ScreenToClient(&rectFrame); // Sandro 19/10/2015 //
			bResult = (*pForm)->CreateChildForm(nID, pParent, rectFrame);
		}
	}
	
	return bResult;
}

void CAnatomiaPatologicaPrestForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDel);

	if (!pDX->m_bSaveAndValidate)
	{
		m_bEsameOK = (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore)) && (m_pEsamiView->m_pEsamiSet->m_lContatore > 0);
		OnFormReadOnly(m_wpReadOnly, 0);
	}
}

HBRUSH CAnatomiaPatologicaPrestForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LIST:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CAnatomiaPatologicaPrestForm::OnInitDialog() 
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LIST, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_BTN_NEW, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_BTN_EDT, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_BTN_DEL, CSize(0,100), CSize(0,100));

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "", LVCFMT_RIGHT, 30);
	m_ctrlList.InsertColumn(2, "Prestazione", LVCFMT_LEFT, 330);
	m_ctrlList.InsertColumn(3, "", LVCFMT_LEFT, 0);

	theApp.LocalizeDialog(this, IDD_SUBFORM_ANATOMIAPATOLOGICA_PREST, "AnatomiaPatologicaForm");

	RiempiLista();

	return bReturn;
}

long CAnatomiaPatologicaPrestForm::GetContenuto()
{
	return sub_anatomiapatologicaprest;
}

BOOL CAnatomiaPatologicaPrestForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CAnatomiaPatologicaPrestForm::OnBnClickedBtnNew()
{
	m_ctrlButtonNew.SetCheck(BST_UNCHECKED);

	CAnatomiaPatologicaPrestNewEdtDlg dlg(this, m_pEsamiView, -1);
	if (dlg.DoModal() == IDOK)
	{
		RiempiLista();
		OnLvnItemChangedList(NULL, NULL);
	}
}

void CAnatomiaPatologicaPrestForm::OnBnClickedBtnEdt()
{
	m_ctrlButtonEdt.SetCheck(BST_UNCHECKED);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		CAnatomiaPatologicaPrestNewEdtDlg dlg(this, m_pEsamiView, m_ctrlList.GetItemData(iCurSel));
		if (dlg.DoModal() == IDOK)
			RiempiLista();
	}
}

void CAnatomiaPatologicaPrestForm::OnBnClickedBtnDel()
{
	m_ctrlButtonDel.SetCheck(BST_UNCHECKED);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATOMIAPATOLOGIAPREST_DELETERECORD), MB_YESNO | MB_ICONSTOP) == IDYES)
		{
			CString strFilter;
			strFilter.Format("ID=%li", m_ctrlList.GetItemData(iCurSel));

			CAnatomiaPatologicaEsamiPrestSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("CAnatomiaPatologicaPrestForm::OnBnClickedBtnDel"))
			{
				if (!setTemp.IsEOF())
					setTemp.DeleteRecordset("CAnatomiaPatologicaPrestForm::OnBnClickedBtnDel");

				setTemp.CloseRecordset("CAnatomiaPatologicaPrestForm::OnBnClickedBtnDel");
			}
			
			RiempiLista();
			OnLvnItemChangedList(NULL, NULL);
		}
	}
}

void CAnatomiaPatologicaPrestForm::RiempiLista()
{
	int nItem = 0;

	CAnatomiaPatologicaEsamiPrestSet setEsamiPrest;
	CAnatomiaPatologicaPrestSet setPrest;

	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_ctrlList.ShowWindow(SW_HIDE);
	m_ctrlList.DeleteAllItems();

	setEsamiPrest.SetOpenFilter(strFilter);
	setEsamiPrest.SetSortRecord("ID");
	if (setEsamiPrest.OpenRecordset("CAnatomiaPatologicaPrestForm::RiempiLista"))
	{
		while(!setEsamiPrest.IsEOF())
		{
			m_ctrlList.InsertItem(nItem, "", -1);
			m_ctrlList.SetItemData(nItem, (DWORD)setEsamiPrest.m_lID);

			CString strTemp;

			strTemp.Format("%li", nItem + 1);
			m_ctrlList.SetItemText(nItem, 1, strTemp);
			m_ctrlList.SetItemText(nItem, 2, setPrest.GetFieldText(setEsamiPrest.m_lIDPrestazione));

			nItem++;
			setEsamiPrest.MoveNext();
		}

		setEsamiPrest.CloseRecordset("CAnatomiaPatologicaPrestForm::RiempiLista");
	}

	for(int i = 1; i < 3; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.ShowWindow(SW_SHOW);
}

void CAnatomiaPatologicaPrestForm::OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_bEsameOK = (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore)) && (m_pEsamiView->m_pEsamiSet->m_lContatore > 0);
	OnFormReadOnly(m_wpReadOnly, 0);

	if (pResult != NULL)
		*pResult = 0;
}

LRESULT CAnatomiaPatologicaPrestForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	RiempiLista();

	return 1;
}

LRESULT CAnatomiaPatologicaPrestForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_wpReadOnly = wParam;

	m_ctrlList.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_BTN_NEW)->EnableWindow((!(BOOL)m_wpReadOnly) && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy));
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!(BOOL)m_wpReadOnly) && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!(BOOL)m_wpReadOnly) && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));

	return 1;
}
