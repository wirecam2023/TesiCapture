#include "stdafx.h"
#include "Endox.h"
#include "ListaPrenotazioniDMSDlg.h"
#include "ListaPrenotazioniCupDettaglioDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListaPrenotazioniDMSDlg::CListaPrenotazioniDMSDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CListaPrenotazioniDMSDlg::IDD, pParent)
{
	m_pWorkListManager = new CDMSWorkListManager(pEsamiView);
	ASSERT(m_pWorkListManager != NULL);
}

CListaPrenotazioniDMSDlg::~CListaPrenotazioniDMSDlg()
{
	if (m_pWorkListManager)
		delete m_pWorkListManager;
	m_pWorkListManager = NULL;
}

BEGIN_MESSAGE_MAP(CListaPrenotazioniDMSDlg, CEndoxResizableDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblClkList)
END_MESSAGE_MAP()

void CListaPrenotazioniDMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1,    m_ctrlList);
}

void CListaPrenotazioniDMSDlg::OnCancel()
{
	CEndoxResizableDlg::OnCancel();
}

BOOL CListaPrenotazioniDMSDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LIST1, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pWorkListManager->PrepareList(&m_ctrlList);

	RiempiLista("");

	theApp.LocalizeDialog(this, CListaPrenotazioniDMSDlg::IDD, "ListaPrenotazioniDMSDlg");

	return TRUE;
}

void CListaPrenotazioniDMSDlg::OnOK()
{
	CString strCodVet;
	GetDlgItemText(IDC_EDIT_CODICEVETRINO, strCodVet);

	RiempiLista(strCodVet);
}

void CListaPrenotazioniDMSDlg::OnDblClkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
	{
		if (m_pWorkListManager->SelectEntry(&m_ctrlList, m_ctrlList.GetNextSelectedItem(pos)))
			PostMessage(WM_COMMAND, IDCANCEL);
	}

	*pResult = 0;
}

void CListaPrenotazioniDMSDlg::RiempiLista(CString sCodVet)
{
	if (!m_pWorkListManager->FillList(&m_ctrlList, sCodVet))
	{
		ShowWindow(SW_HIDE);
		PostMessage(WM_COMMAND, IDCANCEL);
	}
}