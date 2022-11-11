#include "stdafx.h"
#include "Endox.h"
#include "ListaPrenotazioniCupDicomDlg.h"

#include "CupWorkListManager.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListaPrenotazioniCupDicomDlg::CListaPrenotazioniCupDicomDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CListaPrenotazioniCupDicomDlg::IDD, pParent)
{
	m_pWorkListManagerCup = new CCupWorkListManager(pEsamiView);
	m_pWorkListManagerDicom = CWorkListManager::Create(pEsamiView);
	ASSERT(m_pWorkListManagerCup != NULL);
	ASSERT(m_pWorkListManagerDicom != NULL);
}

CListaPrenotazioniCupDicomDlg::~CListaPrenotazioniCupDicomDlg()
{
	if (m_pWorkListManagerCup)
		delete m_pWorkListManagerCup;
	m_pWorkListManagerCup = NULL;

	if (m_pWorkListManagerDicom)
		delete m_pWorkListManagerDicom;
	m_pWorkListManagerDicom = NULL;
}

BEGIN_MESSAGE_MAP(CListaPrenotazioniCupDicomDlg, CEndoxResizableDlg)

	ON_BN_CLICKED(IDC_AGGIORNA, OnBnClickedAggiorna)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CUP, OnNMDblclkListCup)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DICOM, OnNMDblclkListDicom)

END_MESSAGE_MAP()

void CListaPrenotazioniCupDicomDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_CUP,    m_ctrlListCup);
	DDX_Control(pDX, IDC_LIST_DICOM,    m_ctrlListDicom);
}

BOOL CListaPrenotazioniCupDicomDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LIST_CUP, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_CUP, CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_LIST_DICOM, CSize(50, 0), CSize(100, 100));
	AddAnchor(IDC_DICOM, CSize(50, 0), CSize(100, 0));
	AddAnchor(IDC_AGGIORNA, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_ULTIMO_AGGIORNAMENTO, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	m_ctrlListCup.SetExtendedStyle(m_ctrlListCup.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListDicom.SetExtendedStyle(m_ctrlListDicom.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pWorkListManagerCup->PrepareList(&m_ctrlListCup);
	m_pWorkListManagerDicom->PrepareList(&m_ctrlListDicom);
	RiempiListe();

	theApp.LocalizeDialog(this, CListaPrenotazioniCupDicomDlg::IDD, "ListaPrenotazioniCupDicomDlg");
	return TRUE;
}

void CListaPrenotazioniCupDicomDlg::OnOK() 
{
	CEndoxResizableDlg::OnOK();
}

void CListaPrenotazioniCupDicomDlg::RiempiListe()
{
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);

	CString sData;
	sData.Format("%04d%02d%02d", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);

	m_pWorkListManagerCup->FillList(&m_ctrlListCup, "", sData);
	m_pWorkListManagerDicom->FillList(&m_ctrlListDicom);
	
	CTime agg_ora = CTime::GetCurrentTime();
	CString strTmp;
	strTmp.Format(theApp.GetMessageString(IDS_LISTACUP_AGGTABELLA), agg_ora.Format("%H:%M"), agg_ora.Format("%d-%m-%Y"));

	GetDlgItem(IDC_ULTIMO_AGGIORNAMENTO)->SetWindowText(strTmp);
}


void CListaPrenotazioniCupDicomDlg::OnNMDblclkListCup(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (POSITION pos = m_ctrlListCup.GetFirstSelectedItemPosition())
	{
		if (m_pWorkListManagerCup->SelectEntry(&m_ctrlListCup, m_ctrlListCup.GetNextSelectedItem(pos)))
		{
			PostMessage(WM_COMMAND, IDCANCEL);
		}
		else
		{
			theApp.AfxMessageBoxEndo("Errore in CListaPrenotazioniCupDicomDlg::OnDblclkList");
		}
	}

	*pResult = 0;
}

void CListaPrenotazioniCupDicomDlg::OnNMDblclkListDicom(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (POSITION pos = m_ctrlListDicom.GetFirstSelectedItemPosition())
	{
		if (m_pWorkListManagerDicom->SelectEntry(&m_ctrlListDicom, m_ctrlListDicom.GetNextSelectedItem(pos)))
		{
			PostMessage(WM_COMMAND, IDCANCEL);
		}
		else
		{
			theApp.AfxMessageBoxEndo("Errore in CListaPrenotazioniCupDicomDlg::OnDblclkList");
		}
	}

	*pResult = 0;
}

void CListaPrenotazioniCupDicomDlg::OnBnClickedAggiorna()
{
	RiempiListe();
}
