#include "stdafx.h"
#include "Endox.h"
#include "PuntiPazienteDynForm.h"

#include "AlbumForm.h"
#include "DermoxPuntiPazienteDlg.h"
#include "DermoxPuntiPazienteSimpleDlg.h"
#include "DiagnosiIstologicheSet.h"
#include "EsamiView.h"
#include "PuntiPazienteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPuntiPazienteDynForm::CPuntiPazienteDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CPuntiPazienteDynForm::IDD, pParent, pEsamiView)
{
}

CPuntiPazienteDynForm::~CPuntiPazienteDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CPuntiPazienteDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)
END_MESSAGE_MAP()

void CPuntiPazienteDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_puntipaziente] == NULL)
	{
		pEsamiView->m_pDynForm[sub_puntipaziente] = new CPuntiPazienteDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_puntipaziente] != NULL)
		{
			pEsamiView->m_pDynForm[sub_puntipaziente]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_puntipaziente]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_puntipaziente]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_puntipaziente]->CreateChildForm(CPuntiPazienteDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CPuntiPazienteDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_ctrlStaticTitle);
	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_COMBO, m_ctrlCombo);
}

HBRUSH CPuntiPazienteDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITLE:
		case IDC_STATIC_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	if (m_lColore >= 0)
		m_ctrlList.SetTextColor(theApp.m_color[m_lColore]);

	return hReturn;
}

BOOL CPuntiPazienteDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&theApp.m_fontBold);

	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_TITLE, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_00, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_COMBO, CSize(0, 0), CSize(100, 0));

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0); // empty //
	m_ctrlList.InsertColumn(1, "", LVCFMT_RIGHT, 0); // numero //
	m_ctrlList.InsertColumn(2, "Sede", LVCFMT_LEFT, 0); // sede //
	m_ctrlList.InsertColumn(3, "Pattern", LVCFMT_LEFT, 0); // pattern //
	m_ctrlList.InsertColumn(4, "Asportazione", LVCFMT_LEFT, 0); // asportazione //
	m_ctrlList.InsertColumn(5, "", LVCFMT_LEFT, 0); // empty //

	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

	//

	m_ctrlCombo.InsertString(0, "");
	m_ctrlCombo.SetItemData(0, 0);

	int nIndex = 1;

	CDiagnosiIstologicheSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CPuntiPazienteDynForm::OnInitDialog"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlCombo.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCombo.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CPuntiPazienteDynForm::OnInitDialog");
	}

	m_ctrlCombo.SetCurSel(0);

	//

	theApp.LocalizeDialog(this, CPuntiPazienteDynForm::IDD, "PuntiPazienteDynForm");
	return bReturn;
}

long CPuntiPazienteDynForm::GetContenuto()
{
	return sub_puntipaziente;
}

BOOL CPuntiPazienteDynForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CPuntiPazienteDynForm::RiempiLista()
{
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CString strFilter;
	strFilter.Format("IDPaziente=%li", m_pEsamiView->m_pPazientiSet->m_lContatore);

	CPuntiPazienteSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CPuntiPazienteDynForm::RiempiLista"))
	{
		int nItem = 0;

		while(!setTemp.IsEOF())
		{
			CString strTemp;

			m_ctrlList.InsertItem(nItem, "");
			m_ctrlList.SetItemData(nItem, (DWORD)setTemp.m_lID);

			strTemp.Format("%li", setTemp.m_lNumeroDermox);
			m_ctrlList.SetItemText(nItem, 1, strTemp);

			m_ctrlList.SetItemText(nItem, 2, setTemp.m_sSede);

			m_ctrlList.SetItemText(nItem, 3, GetTextPattern(setTemp.m_lPattern));

			m_ctrlList.SetItemText(nItem, 4, setTemp.m_bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CPuntiPazienteDynForm::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
}

LRESULT CPuntiPazienteDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	RiempiLista();

	return 1;
}

LRESULT CPuntiPazienteDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_ctrlList.ShowWindow(SW_HIDE);

		m_ctrlStatic00.ShowWindow(SW_SHOW);
		m_ctrlCombo.ShowWindow(SW_SHOW);
	}
	else 
	{
		m_ctrlList.ShowWindow(SW_SHOW);

		m_ctrlStatic00.ShowWindow(SW_HIDE);
		m_ctrlCombo.ShowWindow(SW_HIDE);
	}

	return 1;
}

LRESULT CPuntiPazienteDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlCombo.SetCurSel(0);

	return 1;
}

LRESULT CPuntiPazienteDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CPuntiPazienteDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_ctrlCombo.GetCurSel() > 0)
	{
		long lValue = m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel());

		// preparo la stringa del long che poi mi serve //

		CString strValue;
		strValue.Format("%li", lValue);

		//

		CString strTableNew = "PuntiPaziente";

		// preparo il FROM //

		(*pStrFrom) += "LEFT OUTER JOIN PuntiPaziente ON EEsami.Paziente=PuntiPaziente.IDPaziente ";

		// preparo il WHERE //

		if (!pStrWhere->IsEmpty())
			(*pStrWhere) += (" AND ");
					
		(*pStrWhere) += ("PuntiPaziente.DiagnosiIstologica=" + strValue + " AND PuntiPaziente.Eliminato=0");
	}

	return 1;
}

void CPuntiPazienteDynForm::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		if (theApp.m_bPersonalizzazioniBrasileCamargo){
			CDermoxPuntiPazienteSimpleDlg(this, m_pEsamiView, m_ctrlList.GetNextSelectedItem(pos)).DoModal();
		}
		else{
			CDermoxPuntiPazienteDlg(this, m_pEsamiView, m_ctrlList.GetNextSelectedItem(pos)).DoModal();
		}

		RiempiLista();

		if (m_pEsamiView->m_pFormImmagini)
			m_pEsamiView->m_pFormImmagini->AfterMoveEsame();
	}
}
