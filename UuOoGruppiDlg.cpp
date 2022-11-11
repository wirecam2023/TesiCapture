#include "stdafx.h"
#include "Endox.h"
#include "UuOoGruppiDlg.h"

#include "GruppiSet.h"
#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUuOoGruppiDlg, CDialog)

CUuOoGruppiDlg::CUuOoGruppiDlg(CWnd* pParent)
	: CDialog(CUuOoGruppiDlg::IDD, pParent)
{
	m_lIDGruppo = 0;
}

CUuOoGruppiDlg::~CUuOoGruppiDlg()
{
}

BEGIN_MESSAGE_MAP(CUuOoGruppiDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ESCI, OnBnClickedBtnEsci)

	ON_LBN_SELCHANGE(IDC_LIST_GRUPPI, OnLbnSelchangeListGruppi)
	ON_LBN_SELCHANGE(IDC_LIST_UNITAOPERATIVE, OnLbnSelchangeListUnitaOperative)
END_MESSAGE_MAP()

void CUuOoGruppiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_ESCI, m_ctrlBtnEsci);

	DDX_Control(pDX, IDC_LIST_GRUPPI, m_ctrlListGruppi);
	DDX_Control(pDX, IDC_LIST_UNITAOPERATIVE, m_ctrlListUnitaOperative);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
}

void CUuOoGruppiDlg::OnCancel()
{
}

BOOL CUuOoGruppiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);

	RiempiListaGruppi();
	RiempiListaUnitaOperative();

	theApp.LocalizeDialog(this, CUuOoGruppiDlg::IDD, "UuOoGruppiDlg");
	return TRUE;
}

void CUuOoGruppiDlg::OnOK()
{
}

void CUuOoGruppiDlg::OnBnClickedBtnEsci()
{
	CDialog::OnOK();
}

void CUuOoGruppiDlg::OnLbnSelchangeListGruppi()
{
	BOOL bEnableListUnitaOperative = FALSE;
	m_lIDGruppo = 0;

	int nCurSel = m_ctrlListGruppi.GetCurSel();
	if (nCurSel >= 0)
	{
		m_lIDGruppo = (long)m_ctrlListGruppi.GetItemData(nCurSel);
		bEnableListUnitaOperative = (m_lIDGruppo > 0);

		SelezionaUnitaOperativa();
	}

	m_ctrlListUnitaOperative.EnableWindow(bEnableListUnitaOperative);
}

void CUuOoGruppiDlg::OnLbnSelchangeListUnitaOperative()
{
	long lUO = 0;

	// cerco l'elemento selezionato o deselezionato //

	for(int i = 0; i < m_ctrlListUnitaOperative.GetCount(); i ++)
	{
		if (m_ctrlListUnitaOperative.GetSel(i) > 0)
		{
			lUO = (long)m_ctrlListUnitaOperative.GetItemData(i);
			break;
		}
	}

	//

	CGruppiSet().SetUO(m_lIDGruppo, lUO);
}

void CUuOoGruppiDlg::RiempiListaGruppi()
{
	BeginWaitCursor();
	m_ctrlListGruppi.SetRedraw(FALSE);
	m_ctrlListGruppi.ResetContent();

	CGruppiSet setTemp;
	setTemp.SetOpenFilter("Eliminato=0");
	setTemp.SetSortRecord("Nome");
	if (setTemp.OpenRecordset("CUuOoGruppiDlg::RiempiListaGruppi"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListGruppi.InsertString(nIndex, setTemp.m_sNome);
			m_ctrlListGruppi.SetItemData(nIndex, (DWORD)setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CUuOoGruppiDlg::RiempiListaGruppi");
	}

	m_ctrlListGruppi.SetRedraw(TRUE);
	EndWaitCursor();
}

void CUuOoGruppiDlg::RiempiListaUnitaOperative()
{
	BeginWaitCursor();
	m_ctrlListUnitaOperative.SetRedraw(FALSE);
	m_ctrlListUnitaOperative.ResetContent();

	CUOSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CUuOoGruppiDlg::RiempiListaUnitaOperative"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListUnitaOperative.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlListUnitaOperative.SetItemData(nIndex, (DWORD)setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CUuOoGruppiDlg::RiempiListaUnitaOperative");
	}

	m_ctrlListUnitaOperative.SetRedraw(TRUE);
	EndWaitCursor();
}

void CUuOoGruppiDlg::SelezionaUnitaOperativa()
{
	// inizio
	BeginWaitCursor();
	// m_ctrlListUnitaOperative.SetRedraw(FALSE);

	// deseleziono tutti gli elementi //
	m_ctrlListUnitaOperative.SetCurSel(-1); // .SelItemRange(FALSE, 0, m_ctrlListUnitaOperative.GetCount() - 1);

	// seleziono l'unità operativa di questo gruppo //
	long lUO = CGruppiSet().GetUO(m_lIDGruppo);

	for(int i = 0; i < m_ctrlListUnitaOperative.GetCount(); i++)
	{
		if (m_ctrlListUnitaOperative.GetItemData(i) == lUO)
		{
			m_ctrlListUnitaOperative.SetCurSel(i); // Sel(i, TRUE);
			break;
		}
	}

	// riscrollo la lista all'inizio //
	m_ctrlListUnitaOperative.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// fine
	// m_ctrlListUnitaOperative.SetRedraw(TRUE);
	EndWaitCursor();
}