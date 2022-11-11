#include "stdafx.h"
#include "Endox.h"
#include "RaoDynForm.h"

#include "ComboRAOSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRaoDynForm::CRaoDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	m_bReadOnly = TRUE;
}

CRaoDynForm::~CRaoDynForm()
{
}

BEGIN_MESSAGE_MAP(CRaoDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_CHECK_CONCORDANZA, OnChangeCheckConcordanza)
	ON_BN_CLICKED(IDC_CHECK_RICERCA, OnChangeCheckRicerca)
	ON_CBN_SELCHANGE(IDC_COMBO_RAO, OnCbnSelchangeComboRao)
	ON_CBN_SELCHANGE(IDC_COMBO_RAOSPEC, OnCbnSelchangeComboRaoSpec)
END_MESSAGE_MAP()

void CRaoDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_rao] == NULL)
	{
		pEsamiView->m_pDynForm[sub_rao] = new CRaoDynForm(CRaoDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_rao] != NULL)
		{
			pEsamiView->m_pDynForm[sub_rao]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_rao]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_rao]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_rao]->CreateChildForm(CRaoDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CRaoDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_RAO:
		case IDC_STATIC_CONCORDANZA:
		case IDC_STATIC_RAOSPEC:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
		case IDC_COMBO_RAO:
		case IDC_COMBO_RAOSPEC:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CRaoDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_RICERCA, m_ctrlChkRicerca);
	DDX_Control(pDX, IDC_COMBO_RAO, m_cmbRao);
	DDX_Control(pDX, IDC_COMBO_RAOSPEC, m_cmbRaoSpec);

	DDX_FieldCheck(pDX, IDC_CHECK_CONCORDANZA, m_pEsamiView->m_pEsamiSet->m_bConcordanza, m_pEsamiView->m_pEsamiSet->GetRecordset());

	if (pDX->m_bSaveAndValidate)
	{
		int nItem = m_cmbRao.GetCurSel();
		if (nItem >= 0)
		{
			m_pEsamiView->m_pEsamiSet->m_nCodiceRAO = (long)m_cmbRao.GetItemData(nItem);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_nCodiceRAO, FALSE);
		}

		if (m_pEsamiView->m_pEsamiSet->m_bConcordanza == 0)
		{
			nItem = m_cmbRaoSpec.GetCurSel();
			if (nItem >= 0)
			{
				m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec = (long)m_cmbRaoSpec.GetItemData(nItem);

				if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
					m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec, FALSE);
			}
		}
		else
		{
			m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec = 0;
		}
	}
	else
	{
		m_cmbRao.SetCurSel(-1);
		m_cmbRaoSpec.SetCurSel(-1);

		if (m_pEsamiView->m_pEsamiSet->m_nCodiceRAO > 0)
		{
			for(int i = 0; i < m_cmbRao.GetCount(); i++)
			{
				if (m_cmbRao.GetItemData(i) == m_pEsamiView->m_pEsamiSet->m_nCodiceRAO)
				{
					m_cmbRao.SetCurSel(i);
					break;
				}
			}
		}
		if (m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec > 0)
		{
			for(int i = 0; i < m_cmbRaoSpec.GetCount(); i++)
			{
				if (m_cmbRaoSpec.GetItemData(i) == m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec)
				{
					m_cmbRaoSpec.SetCurSel(i);
					break;
				}
			}
		}
	}

	/*
	if (pDX->m_bSaveAndValidate)
	{
		m_cmbRao.GetWindowText(m_pEsamiView->m_pEsamiSet->m_sCodiceRAO);
		m_cmbRaoSpec.GetWindowText(m_pEsamiView->m_pEsamiSet->m_sCodiceRAOSpec);
	}
	else
	{
		if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_sCodiceRAO) || (m_pEsamiView->m_pEsamiSet->m_sCodiceRAO.GetLength() <= 0))
		{
			m_cmbRao.SetCurSel(0);
		}
		else
		{
			int nFind;
			
			nFind = m_cmbRao.FindStringExact(-1, m_pEsamiView->m_pEsamiSet->m_sCodiceRAO);
			nFind = max(0, nFind);
			m_cmbRao.SetCurSel(nFind);

			nFind = m_cmbRao.FindStringExact(-1, m_pEsamiView->m_pEsamiSet->m_sCodiceRAOSpec);
			nFind = max(0, nFind);
			m_cmbRaoSpec.SetCurSel(nFind);
		}
	}
	*/
}

BOOL CRaoDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_RAO, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_COMBO_RAO, CSize(50,50), CSize(100,50));
	AddAnchor(IDC_STATIC_CONCORDANZA, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_CHECK_CONCORDANZA, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_CHECK_RICERCA, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_STATIC_RAOSPEC, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_COMBO_RAOSPEC, CSize(50,50), CSize(100,50));

	m_cmbRao.ResetContent();
	m_cmbRaoSpec.ResetContent();

	CComboRAOSet setRao;
	setRao.SetSortRecord("DescrizioneRAO");
	if (setRao.OpenRecordset("CRaoDynForm::OnInitDialog"))
	{
		int nItem = m_cmbRao.AddString("");
		if (nItem >= 0)
			m_cmbRao.SetItemData(nItem, 0);

		while(!setRao.IsEOF())
		{
			nItem = m_cmbRao.AddString(setRao.m_sDescrizione);
			if (nItem >= 0)
				m_cmbRao.SetItemData(nItem, (DWORD)setRao.m_lID);

			nItem = m_cmbRaoSpec.AddString(setRao.m_sDescrizione);
			if (nItem >= 0)
				m_cmbRaoSpec.SetItemData(nItem, (DWORD)setRao.m_lID);

			setRao.MoveNext();
		}

		setRao.CloseRecordset("CRaoDynForm::OnInitDialog");
	}

	return TRUE;
}

void CRaoDynForm::OnChangeCheckConcordanza()
{
	UpdateData(TRUE);

	OnFormReadOnly((WPARAM)m_bReadOnly, (LPARAM)0);
}

void CRaoDynForm::OnChangeCheckRicerca()
{
	UpdateData(TRUE);
}

LRESULT CRaoDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CRaoDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		GetDlgItem(IDC_COMBO_RAO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_CONCORDANZA)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_RICERCA)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RAOSPEC)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_CONCORDANZA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_CONCORDANZA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_RICERCA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_RAOSPEC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_RAOSPEC)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_COMBO_RAO)->EnableWindow(!(BOOL)wParam);
		GetDlgItem(IDC_CHECK_CONCORDANZA)->EnableWindow(!(BOOL)wParam);
		GetDlgItem(IDC_CHECK_RICERCA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_RAOSPEC)->EnableWindow(!(BOOL)wParam);

		if (m_pEsamiView->m_pEsamiSet->m_nCodiceRAO > 0)
		{
			GetDlgItem(IDC_STATIC_CONCORDANZA)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECK_CONCORDANZA)->ShowWindow(SW_SHOW);

			if (m_pEsamiView->m_pEsamiSet->m_bConcordanza)
			{
				GetDlgItem(IDC_STATIC_RAOSPEC)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_RAOSPEC)->ShowWindow(SW_HIDE);
			}
			else
			{
				GetDlgItem(IDC_STATIC_RAOSPEC)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_COMBO_RAOSPEC)->ShowWindow(SW_SHOW);
			}
		}
		else
		{
			GetDlgItem(IDC_STATIC_CONCORDANZA)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECK_CONCORDANZA)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_RAOSPEC)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_RAOSPEC)->ShowWindow(SW_HIDE);
		}
	}

	return 1;
}

LRESULT CRaoDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlChkRicerca.SetCheck(BST_INDETERMINATE);

	return 1;
}

LRESULT CRaoDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CRaoDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_nCodiceRAO))
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_nCodiceRAO, "EEsami.CodiceRAO", 0, "AND");

	if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec))
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec, "EEsami.CodiceRAOSpec", 0, "AND");

	// Sandro 07/12/2010 // RAS 20100228 // aggiungo anche il controllo del check //
	switch(m_ctrlChkRicerca.GetCheck())
	{
		case BST_CHECKED:
		{
			if (!pStrWhere->IsEmpty())
				*pStrWhere += " AND ";

			*pStrWhere += "EEsami.Concordanza = 1";

			break;
		}
		case BST_UNCHECKED:
		{
			if (!pStrWhere->IsEmpty())
				*pStrWhere += " AND ";

			*pStrWhere += "EEsami.Concordanza = 0";

			break;
		}
	}
	//

	return 1;
}

long CRaoDynForm::GetContenuto()
{
	return sub_rao;
}

BOOL CRaoDynForm::CampoObbligatorioValido()
{
	if (m_pEsamiView->m_pEsamiSet->m_nCodiceRAO <= 0)
		return FALSE;

	if ((!m_pEsamiView->m_pEsamiSet->m_bConcordanza) && (m_pEsamiView->m_pEsamiSet->m_nCodiceRAOSpec <= 0))
		return FALSE;

	return(TRUE);
}

void CRaoDynForm::OnCbnSelchangeComboRao()
{
	UpdateData(TRUE);
	OnFormReadOnly((WPARAM)m_bReadOnly, (LPARAM)0);
}

void CRaoDynForm::OnCbnSelchangeComboRaoSpec()
{
	UpdateData(TRUE);
}