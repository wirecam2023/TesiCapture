#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaDlg.h"

#include "AnatomiaPatologicaSet.h"
#include "AnatomiaPatologicaNewEdtDlg.h"
#include "EsamiView.h"
#include "EsamiSet.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaDlg, CDialog)

CAnatomiaPatologicaDlg::CAnatomiaPatologicaDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CAnatomiaPatologicaDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_ctrlList.m_pEsamiView = pEsamiView;
}

CAnatomiaPatologicaDlg::~CAnatomiaPatologicaDlg()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_NEW, OnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_STAMPATUTTI, OnClickedBtnStampaTutti)
END_MESSAGE_MAP()

void CAnatomiaPatologicaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

HBRUSH CAnatomiaPatologicaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LIST:
		case IDC_STATIC_NOTE:
		case IDC_EDIT_NOTE:
			pDC->SetTextColor(theApp.m_color[2]);
			break;
	}

	return hBrush;
}

BOOL CAnatomiaPatologicaDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CAnatomiaPatologicaDlg::IDD, "AnatomiaPatologicaDlg");

	m_ctrlImageList.Create(62, 22, ILC_COLOR32, 2, 0);
	m_ctrlImageList.Add(AfxGetApp()->LoadIcon(IDI_BTN_STAMPA));
	m_ctrlImageList.Add(AfxGetApp()->LoadIcon(IDI_BTN_STAMPA_DIS));

	m_ctrlList.m_pStampaRigaFunction = StampaRiga;
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList.SetImageList(&m_ctrlImageList, LVSIL_SMALL);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "", LVCFMT_RIGHT, 30);
	m_ctrlList.InsertColumn(2, "ID Campione", LVCFMT_CENTER, 90);
	m_ctrlList.InsertColumn(3, "Tipo", LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(4, "Intervento", LVCFMT_LEFT, 330);
	m_ctrlList.InsertColumn(5, "Prelievi", LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(6, "Commento", LVCFMT_LEFT, 301);
	m_ctrlList.InsertColumn(7, "", LVCFMT_LEFT, 62);

	// SetDlgItemText(IDC_EDIT_NOTE, m_pEsamiView->m_pEsamiSet->m_sNoteAnatomiaPatologica);

	RiempiLista();

	return bReturn;
}

void CAnatomiaPatologicaDlg::OnOK()
{
	/*if (m_pEsamiView->m_pEsamiSet->GetEditMode() == 0) // noMode //
	{
		if (m_pEsamiView->m_pEsamiSet->EditRecordset("CAnatomiaPatologicaDlg::OnOK"))
		{
			// GetDlgItemText(IDC_EDIT_NOTE, m_pEsamiView->m_pEsamiSet->m_sNoteAnatomiaPatologica);
			m_pEsamiView->m_pEsamiSet->UpdateRecordset("CAnatomiaPatologicaDlg::OnOK");
		}
	}
	else // edit o addnew //
	{
		GetDlgItemText(IDC_EDIT_NOTE, m_pEsamiView->m_pEsamiSet->m_sNoteAnatomiaPatologica);
	}*/

	CDialog::OnOK();
}

void CAnatomiaPatologicaDlg::RiempiLista()
{
	int nItem = 0;

	CAnatomiaPatologicaSet setTemp;

	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_ctrlList.DeleteAllItems();

	setTemp.SetOpenFilter(strFilter);
	setTemp.SetSortRecord("ID");
	if (setTemp.OpenRecordset("CAnatomiaPatologicaDlg::RiempiLista"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlList.InsertItem(nItem, "", -1);
			m_ctrlList.SetItemData(nItem, (DWORD)setTemp.m_lID);

			CString strTemp;

			strTemp.Format("%li", nItem + 1);
			m_ctrlList.SetItemText(nItem, 1, strTemp);
			m_ctrlList.SetItemText(nItem, 2, setTemp.m_sIDCampione);
			m_ctrlList.SetItemText(nItem, 3, setTemp.m_sTipo);
			m_ctrlList.SetItemText(nItem, 4, setTemp.m_sIntervCodice + ": " + setTemp.m_sIntervProcedura);
			if (!setTemp.IsFieldNull(&setTemp.m_lPrelievi))
			{
				strTemp.Format("%li", setTemp.m_lPrelievi);
				m_ctrlList.SetItemText(nItem, 5, strTemp);
			}
			else
			{
				m_ctrlList.SetItemText(nItem, 5, "0");
			}
			m_ctrlList.SetItemText(nItem, 6, setTemp.m_sDescrizione);
			m_ctrlList.SetItem(nItem, 7, LVIF_IMAGE, NULL, 0, 0, 0, 0);

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAnatomiaPatologicaDlg::RiempiLista");
	}
}

void CAnatomiaPatologicaDlg::OnClickedBtnNew()
{
	CAnatomiaPatologicaNewEdtDlg dlg(this, m_pEsamiView, -1);
	if (dlg.DoModal() == IDOK)
		RiempiLista();
}

void CAnatomiaPatologicaDlg::OnClickedBtnEdt()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		CAnatomiaPatologicaNewEdtDlg dlg(this, m_pEsamiView, m_ctrlList.GetItemData(iCurSel));
		if (dlg.DoModal() == IDOK)
			RiempiLista();
	}
}

void CAnatomiaPatologicaDlg::OnClickedBtnDel()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATOMIAPATOLOGIA_DELETERECORD), MB_YESNO | MB_ICONSTOP) == IDYES)
		{
			CString strFilter;
			strFilter.Format("ID=%li", m_ctrlList.GetItemData(iCurSel));

			CAnatomiaPatologicaSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("CAnatomiaPatologicaDlg::OnBnClickedBtnDel"))
			{
				if (!setTemp.IsEOF())
					setTemp.DeleteRecordset("CAnatomiaPatologicaDlg::OnBnClickedBtnDel");

				setTemp.CloseRecordset("CAnatomiaPatologicaDlg::OnBnClickedBtnDel");
			}
			
			RiempiLista();
		}
	}
}

void CAnatomiaPatologicaDlg::OnClickedBtnStampaTutti()
{
	for(int i = 0; i < m_ctrlList.GetItemCount(); i++)
		StampaRiga((long)m_ctrlList.GetItemData(i), m_pEsamiView);
}

void CAnatomiaPatologicaDlg::StampaRiga(long lRecord, CEsamiView* pEsamiView)
{
	// implementare RGL //
}
