#include "stdafx.h"
#include "Endox.h"
#include "EditCodificaRegionaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditCodificaRegionaleDlg, CDialog)

CEditCodificaRegionaleDlg::CEditCodificaRegionaleDlg(CWnd* pParent, long lIDProcedura, long lQuantita, const CString &sTestoLibero)
	: CDialog(CEditCodificaRegionaleDlg::IDD, pParent)
{
	m_lIDProcedura = lIDProcedura;
	m_lQuantita = lQuantita;
	m_sTestoLibero = sTestoLibero;
}

CEditCodificaRegionaleDlg::~CEditCodificaRegionaleDlg()
{
}

void CEditCodificaRegionaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);

	DDX_Control(pDX, IDC_LIST_VOCI, m_ctrlListVoci);
}

BEGIN_MESSAGE_MAP(CEditCodificaRegionaleDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_EN_CHANGE(IDC_EDIT_VOCI, OnEnChangeEditVoci)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VOCI, OnLvnItemchangedListVoci)

END_MESSAGE_MAP()

BOOL CEditCodificaRegionaleDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlListVoci.SetExtendedStyle(m_ctrlListVoci.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListVoci.InsertColumn(0, "");
	m_ctrlListVoci.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	RiempiListaVoci();

	for(int i = 0; i < m_ctrlListVoci.GetItemCount(); i++)
	{
		if ((long)m_ctrlListVoci.GetItemData(i) == m_lIDProcedura)
		{
			m_ctrlListVoci.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			m_ctrlListVoci.EnsureVisible(i, FALSE);
		}
		else
		{
			m_ctrlListVoci.SetItemState(i, 0, LVIS_SELECTED);
		}
	}

	//
	SetDlgItemInt(IDC_EDIT_QUANTITA, m_lQuantita);
	SetDlgItemText(IDC_EDIT_TESTOLIBERO, m_sTestoLibero);

	theApp.LocalizeDialog(this, CEditCodificaRegionaleDlg::IDD, "EditCodificaRegionaleDlg");
	SetWindowText((m_lIDProcedura <= 0) ? theApp.GetMessageString(IDS_CODIFICAREGIONALEGRUPPIRICDLG_TITLE3) : theApp.GetMessageString(IDS_CODIFICAREGIONALEGRUPPIRICDLG_TITLE4));

	return bReturn;
}

void CEditCodificaRegionaleDlg::OnBnClickedOk()
{
	m_lIDProcedura = 0;

	POSITION pos = m_ctrlListVoci.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListVoci.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
			m_lIDProcedura = (long)m_ctrlListVoci.GetItemData(nCurSel);
	}

	m_lQuantita = GetDlgItemInt(IDC_EDIT_QUANTITA);
	GetDlgItemText(IDC_EDIT_TESTOLIBERO, m_sTestoLibero);

	OnOK();
}

void CEditCodificaRegionaleDlg::OnEnChangeEditVoci()
{
	RiempiListaVoci();
}

void CEditCodificaRegionaleDlg::OnLvnItemchangedListVoci(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ctrlButtonOK.EnableWindow(m_ctrlListVoci.GetFirstSelectedItemPosition() != NULL);
}

long CEditCodificaRegionaleDlg::GetIDProcedura()
{
	return m_lIDProcedura;
}

long CEditCodificaRegionaleDlg::GetQuantita()
{
	if (m_lQuantita <= 0)
		m_lQuantita = 1;

	return m_lQuantita;
}

CString CEditCodificaRegionaleDlg::GetTestoLibero()
{
	return m_sTestoLibero;
}

void CEditCodificaRegionaleDlg::RiempiListaVoci()
{
	BeginWaitCursor();
	m_ctrlListVoci.SetRedraw(FALSE);
	m_ctrlListVoci.DeleteAllItems();

	CString strFiltro;
	GetDlgItemText(IDC_EDIT_VOCI, strFiltro);
	strFiltro.Trim();

	if (strFiltro.IsEmpty())
	{
		int nIndex = 0;

		POSITION pos = theApp.m_listVociPrestazioni.GetHeadPosition();
		while(pos != NULL)
		{
			tagRicettaElement tagTemp = theApp.m_listVociPrestazioni.GetAt(pos);
			m_ctrlListVoci.InsertItem(nIndex, tagTemp.m_sDescrizione);
			m_ctrlListVoci.SetItemData(nIndex, (long)tagTemp.m_lID);

			nIndex++;
			theApp.m_listVociPrestazioni.GetNext(pos);
		}
	}
	else
	{
		int nIndex = 0;

		POSITION pos = theApp.m_listVociPrestazioni.GetHeadPosition();
		while(pos != NULL)
		{
			tagRicettaElement tagTemp = theApp.m_listVociPrestazioni.GetAt(pos);
			if (tagTemp.m_sDescrizione.Find(strFiltro) >= 0)
			{
				m_ctrlListVoci.InsertItem(nIndex, tagTemp.m_sDescrizione);
				m_ctrlListVoci.SetItemData(nIndex, (long)tagTemp.m_lID);

				nIndex++;
			}
			theApp.m_listVociPrestazioni.GetNext(pos);
		}
	}

	m_ctrlListVoci.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVoci.SetRedraw(TRUE);
	EndWaitCursor();
}