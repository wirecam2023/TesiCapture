#include "stdafx.h"
#include "Endox.h"
#include "EsameIntegratoDlg.h"

#include "EsamiIntegratiSet.h"
#include "EsamiView.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsameIntegratoDlg, CDialog)

CEsameIntegratoDlg::CEsameIntegratoDlg(CWnd* pParent, CEsamiView* pEsamiView)
: CDialog(CEsameIntegratoDlg::IDD, pParent), m_ctrlList(TRUE, FALSE, FALSE)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CEsameIntegratoDlg::~CEsameIntegratoDlg()
{
}

BEGIN_MESSAGE_MAP(CEsameIntegratoDlg, CDialog)
END_MESSAGE_MAP()

void CEsameIntegratoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CEsameIntegratoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "Paziente", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(2, "Tipo esame", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(3, "Descrizione esame", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(4, "Codice richiesta", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(5, "", LVCFMT_LEFT, 0);

	RiempiLista();

	theApp.LocalizeDialog(this, CEsameIntegratoDlg::IDD, "EsameIntegratoDlg");
	return TRUE;
}

void CEsameIntegratoDlg::OnOK()
{
	for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
	{
		if (m_ctrlList.GetSubItemData(i, 0) > 0)
			CEsamiIntegratiSet().AddRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlList.GetItemData(i));
		else
			CEsamiIntegratiSet().DelRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlList.GetItemData(i));
	}

	CDialog::OnOK();
}

void CEsameIntegratoDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);

	m_ctrlList.DeleteAllItems();

	m_pEsamiView->m_pEsamiSet->m_sRicovero.Replace("'", "''");

	CString sFilter;
	sFilter.Format("Ricovero='%s' AND Contatore<>%li AND Locked=0 AND SuperLocked=0", m_pEsamiView->m_pEsamiSet->m_sRicovero, m_pEsamiView->m_pEsamiSet->m_lContatore);

	CEsamiSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord("Data, Contatore");

	if (setTemp.OpenRecordset("CEsameIntegratoDlg::RiempiLista"))
	{
		int nItem = 0;
		while (!setTemp.IsEOF())
		{
			m_ctrlList.InsertItem(nItem, "");
			m_ctrlList.SetItemData(nItem, setTemp.m_lContatore);

			m_ctrlList.SetSubItemCheck(nItem, 0);
			m_ctrlList.SetSubItemData(nItem, 0, CEsamiIntegratiSet().ExistsRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, setTemp.m_lContatore));

			m_ctrlList.SetItemText(nItem, 1, CPazientiSet().GetCognomeNomeDataNascita(setTemp.m_lPaziente));

			m_ctrlList.SetItemText(nItem, 2, CTipoEsameSet().GetDescrizione(setTemp.m_lIDEsame));

			m_ctrlList.SetItemText(nItem, 3, setTemp.m_setEP.m_sTesto001);

			m_ctrlList.SetItemText(nItem, 4, setTemp.m_sCodEsame + "00");

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CEsameIntegratoDlg::RiempiLista");
	}

	for(int i = 0; i < 5; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}