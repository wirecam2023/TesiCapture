#include "stdafx.h"
#include "Endox.h"
#include "CodiciClassificazioneDiagnosticaDynForm.h"

#include "CodiciClassificazioneDiagnosticaSet.h"
#include "Common.h"
#include "EsamiCodiciClassDiagnostSet.h"
#include "EsamiView.h"
#include "NewEdtCCDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCodiciClassificazioneDiagnosticaDynForm::CCodiciClassificazioneDiagnosticaDynForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(CCodiciClassificazioneDiagnosticaDynForm::IDD, pParent, pEsamiView)
{
	m_bReadOnly = FALSE;
	m_iRadioSearch = 0;
}

CCodiciClassificazioneDiagnosticaDynForm::~CCodiciClassificazioneDiagnosticaDynForm()
{
}

BEGIN_MESSAGE_MAP(CCodiciClassificazioneDiagnosticaDynForm, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CCodiciClassificazioneDiagnosticaDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica] == NULL)
	{
		pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica] = new CCodiciClassificazioneDiagnosticaDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica] != NULL)
		{
			pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica]->CreateChildForm(CCodiciClassificazioneDiagnosticaDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CCodiciClassificazioneDiagnosticaDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	/*
	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_TEXT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
		case IDC_EDIT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}
	*/

	return hBrush;
}

void CCodiciClassificazioneDiagnosticaDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);

	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_TITLE, m_ctrlStaticTitle);

	DDX_Radio(pDX, IDC_RADIO1, m_iRadioSearch);
}

BOOL CCodiciClassificazioneDiagnosticaDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	m_ctrlStaticTitle.SetFont(&theApp.m_fontBold);

	AddAnchor(IDC_STATIC_TITLE, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_RADIO1, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_RADIO2, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_NEW, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_EDT, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_DEL, CSize(100, 100), CSize(100, 100));

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_CODICE));
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	theApp.LocalizeDialog(this, CCodiciClassificazioneDiagnosticaDynForm::IDD, "CodiciClassificazioneDiagnosticaDynForm");
	return TRUE;
}

LRESULT CCodiciClassificazioneDiagnosticaDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CCodiciClassificazioneDiagnosticaDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	m_ctrlList.DeleteAllItems();

	CString sFilter;
	sFilter.Format("IDESAME=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CEsamiCodiciClassDiagnostSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CCodiciClassificazioneDiagnosticaDynForm::OnFormLoad"))
	{
		while (!setTemp.IsEOF())
		{
			CString sCodice = "";
			CString sDescrizione = "";
			CCodiciClassificazioneDiagnostSet().GetStringCodiceDescrizione(setTemp.m_lIDCodiciClassificazioneDiag, sCodice, sDescrizione);

			int nIndex = m_ctrlList.GetItemCount();
			m_ctrlList.InsertItem(nIndex, sCodice);
			m_ctrlList.SetItemData(nIndex, setTemp.m_lIDCodiciClassificazioneDiag);

			m_ctrlList.SetItemText(nIndex, 1, sDescrizione);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CCodiciClassificazioneDiagnosticaDynForm::OnFormLoad");
	}

	return 1;
}

LRESULT CCodiciClassificazioneDiagnosticaDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_ctrlRadio1.ShowWindow(SW_SHOW);
		m_ctrlRadio2.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ctrlRadio1.ShowWindow(SW_HIDE);
		m_ctrlRadio2.ShowWindow(SW_HIDE);

		wParam = m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco) || (theApp.m_nProgramMode & ADD_RECORD_ESAMI);
	}

	m_bReadOnly = (BOOL)wParam;

	m_ctrlBtnNew.EnableWindow(!m_bReadOnly);
	m_ctrlBtnEdt.EnableWindow(!m_bReadOnly && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	m_ctrlBtnDel.EnableWindow(!m_bReadOnly && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));

	return 1;
}

LRESULT CCodiciClassificazioneDiagnosticaDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlList.DeleteAllItems();
	return 1;
}

LRESULT CCodiciClassificazioneDiagnosticaDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);

	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_iRadioSearch == 0)
	{
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
			ComponiRicercaNewLong(pStrFrom, pStrWhere, "ESAMICODICICLASSDIAGNOST", i, "IDESAME", "IDCODICICLASSIFICAZIONEDIAG", m_ctrlList.GetItemData(i), OPER_AND, MODE_UGUALE);
	}
	else
	{
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
			ComponiRicercaNewLong(pStrFrom, pStrWhere, "ESAMICODICICLASSDIAGNOST", i, "IDESAME", "IDCODICICLASSIFICAZIONEDIAG", m_ctrlList.GetItemData(i), OPER_OR, MODE_UGUALE);
	}

	return 1;
}

long CCodiciClassificazioneDiagnosticaDynForm::GetContenuto()
{
	return sub_codiciclassificazionediagnostica;
}

BOOL CCodiciClassificazioneDiagnosticaDynForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CCodiciClassificazioneDiagnosticaDynForm::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ctrlBtnEdt.EnableWindow(!m_bReadOnly && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	m_ctrlBtnDel.EnableWindow(!m_bReadOnly && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
}

void CCodiciClassificazioneDiagnosticaDynForm::OnBnClickedBtnNew()
{
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		CNewEdtCCDDlg dlg(this, IDS_EDT_CCD, 0, 0);
		if (dlg.DoModal() == IDOK)
		{
			int nItem = m_ctrlList.GetItemCount();

			CString sCodice = "";
			CString sDescrizione = "";
			CCodiciClassificazioneDiagnostSet().GetStringCodiceDescrizione(dlg.GetIDCurSelForSearch(), sCodice, sDescrizione);

			m_ctrlList.InsertItem(nItem, sCodice);
			m_ctrlList.SetItemData(nItem, dlg.GetIDCurSelForSearch());

			m_ctrlList.SetItemText(nItem, 1, sDescrizione);

			m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
			m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		}
	}
	else
	{
		if (CNewEdtCCDDlg(this, IDS_NEW_CCD, m_pEsamiView->m_pEsamiSet->m_lContatore, 0).DoModal() == IDOK)
			OnFormLoad(NULL, NULL);
	}
}

void CCodiciClassificazioneDiagnosticaDynForm::OnBnClickedBtnEdt()
{
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
			if (nCurSel >= 0)
			{
				CNewEdtCCDDlg dlg(this, IDS_EDT_CCD, 0, m_ctrlList.GetItemData(nCurSel));
				if (dlg.DoModal() == IDOK)
				{
					m_ctrlList.DeleteItem(nCurSel);

					int nItem = m_ctrlList.GetItemCount();

					CString sCodice = "";
					CString sDescrizione = "";
					CCodiciClassificazioneDiagnostSet().GetStringCodiceDescrizione(dlg.GetIDCurSelForSearch(), sCodice, sDescrizione);

					m_ctrlList.InsertItem(nItem, sCodice);
					m_ctrlList.SetItemData(nItem, dlg.GetIDCurSelForSearch());

					m_ctrlList.SetItemText(nItem, 1, sDescrizione);

					m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
					m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
				}
			}
		}
	}
	else
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
			if (nCurSel >= 0)
			{
				long lIDCurSel = m_ctrlList.GetItemData(nCurSel);
				if (lIDCurSel > 0)
				{
					if (CNewEdtCCDDlg(this, IDS_EDT_CCD, m_pEsamiView->m_pEsamiSet->m_lContatore, lIDCurSel).DoModal() == IDOK)
						OnFormLoad(NULL, NULL);
				}
			}
		}
	}
}

void CCodiciClassificazioneDiagnosticaDynForm::OnBnClickedBtnDel()
{
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
			if (nCurSel >= 0)
			{
				m_ctrlList.DeleteItem(nCurSel);
				m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
			}
		}
	}
	else
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
			if (nCurSel >= 0)
			{
				long lIDCurSel = m_ctrlList.GetItemData(nCurSel);
				if (lIDCurSel > 0)
				{
					if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CCD_DELETE_CONFIRM), MB_YESNO) == IDYES)
					{
						CEsamiCodiciClassDiagnostSet().DelRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, lIDCurSel);
						OnFormLoad(NULL, NULL);
					}
				}
			}
		}
	}
}
