#include "stdafx.h"
#include "Endox.h"
#include "EditFarmacoDlg.h"

#include "FarmaciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditFarmacoDlg, CDialog)

CEditFarmacoDlg::CEditFarmacoDlg(CWnd* pParent, long lIDFarmaco, long lQuantita, const CString &sTestoLibero)
	: CDialog(CEditFarmacoDlg::IDD, pParent)
{
	m_lIDFarmaco = lIDFarmaco;
	m_lQuantita = lQuantita;
	m_sTestoLibero = sTestoLibero;
}

CEditFarmacoDlg::~CEditFarmacoDlg()
{
}

void CEditFarmacoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_LIST_VOCI, m_ctrlListVoci);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
}

BEGIN_MESSAGE_MAP(CEditFarmacoDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_EN_CHANGE(IDC_EDIT_VOCI, OnEnChangeEditVoci)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VOCI, OnLvnItemchangedListVoci)

END_MESSAGE_MAP()

BOOL CEditFarmacoDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlListVoci.SetExtendedStyle(m_ctrlListVoci.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListVoci.InsertColumn(0, "", LVCFMT_LEFT, 200);
	m_ctrlListVoci.InsertColumn(1, "", LVCFMT_LEFT, 250);
	m_ctrlListVoci.InsertColumn(2, "", LVCFMT_LEFT, 159);

	RiempiListaVoci();

	for(int i = 0; i < m_ctrlListVoci.GetItemCount(); i++)
	{
		if ((long)m_ctrlListVoci.GetItemData(i) == m_lIDFarmaco)
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

	theApp.LocalizeDialog(this, CEditFarmacoDlg::IDD, "EditFarmacoDlg");
	SetWindowText((m_lIDFarmaco <= 0) ? theApp.GetMessageString(IDS_FARMACIGRUPPIRICDLG_TITLE3) : theApp.GetMessageString(IDS_FARMACIGRUPPIRICDLG_TITLE4));

	return bReturn;
}

void CEditFarmacoDlg::OnBnClickedOk()
{
	m_lIDFarmaco = 0;

	POSITION pos = m_ctrlListVoci.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListVoci.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
			m_lIDFarmaco = (long)m_ctrlListVoci.GetItemData(nCurSel);
	}

	m_lQuantita = GetDlgItemInt(IDC_EDIT_QUANTITA);
	GetDlgItemText(IDC_EDIT_TESTOLIBERO, m_sTestoLibero);

	OnOK();
}

void CEditFarmacoDlg::OnEnChangeEditVoci()
{
	RiempiListaVoci();
}

void CEditFarmacoDlg::OnLvnItemchangedListVoci(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ctrlButtonOK.EnableWindow(m_ctrlListVoci.GetFirstSelectedItemPosition() != NULL);
}

long CEditFarmacoDlg::GetIDFarmaco()
{
	return m_lIDFarmaco;
}

long CEditFarmacoDlg::GetQuantita()
{
	if (m_lQuantita <= 0)
		m_lQuantita = 1;

	return m_lQuantita;
}

CString CEditFarmacoDlg::GetTestoLibero()
{
	return m_sTestoLibero;
}

void CEditFarmacoDlg::RiempiListaVoci()
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

		POSITION pos = theApp.m_listVociFarmaci.GetHeadPosition();
		while(pos != NULL)
		{
			tagRicettaFarmElement tagTemp = theApp.m_listVociFarmaci.GetAt(pos);

			m_ctrlListVoci.InsertItem(nIndex, tagTemp.m_sNome);
			m_ctrlListVoci.SetItemData(nIndex, (long)tagTemp.m_lID);

			m_ctrlListVoci.SetItemText(nIndex, 1, tagTemp.m_sPrincipioAttivo);

			m_ctrlListVoci.SetItemText(nIndex, 2, tagTemp.m_sDescrizione);

			nIndex++;
			theApp.m_listVociFarmaci.GetNext(pos);
		}
	}
	else
	{
		int nIndex = 0;

		POSITION pos = theApp.m_listVociFarmaci.GetHeadPosition();
		while(pos != NULL)
		{
			tagRicettaFarmElement tagTemp = theApp.m_listVociFarmaci.GetAt(pos);
			if ((tagTemp.m_sNome.Find(strFiltro) >= 0) || (tagTemp.m_sPrincipioAttivo.Find(strFiltro) >= 0))
			{
				m_ctrlListVoci.InsertItem(nIndex, tagTemp.m_sNome);
				m_ctrlListVoci.SetItemData(nIndex, (long)tagTemp.m_lID);

				m_ctrlListVoci.SetItemText(nIndex, 1, tagTemp.m_sPrincipioAttivo);

				m_ctrlListVoci.SetItemText(nIndex, 2, tagTemp.m_sDescrizione);

				nIndex++;
			}
			theApp.m_listVociFarmaci.GetNext(pos);
		}
	}

	m_ctrlListVoci.SetRedraw(TRUE);
	EndWaitCursor();
}
