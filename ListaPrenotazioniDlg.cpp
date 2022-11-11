#include "stdafx.h"
#include "Endox.h"
#include "ListaPrenotazioniDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListaPrenotazioniDlg::CListaPrenotazioniDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CListaPrenotazioniDlg::IDD, pParent)
{
	m_pWorkListManager = CWorkListManager::Create(pEsamiView);
	ASSERT(m_pWorkListManager != NULL);
}

CListaPrenotazioniDlg::~CListaPrenotazioniDlg()
{
	if (m_pWorkListManager)
		delete m_pWorkListManager;
	m_pWorkListManager = NULL;
}

BEGIN_MESSAGE_MAP(CListaPrenotazioniDlg, CEndoxResizableDlg)

	ON_BN_CLICKED(IDC_AGGIORNA, OnAggiorna)

	ON_CBN_SELCHANGE(IDC_COMBO_SEDE, OnCbnSelchangeComboSede)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblClkList)

END_MESSAGE_MAP()

void CListaPrenotazioniDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1,      m_ctrlList);
	DDX_Control(pDX, IDC_COMBO_SEDE, m_ctrlComboSede);
	DDX_Control(pDX, IDC_AGGIORNA,   m_ctrlButtonRefresh);
	DDX_Control(pDX, IDOK,           m_ctrlButtonOK);
}

BOOL CListaPrenotazioniDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LIST1, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_AGGIORNA, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_ULTIMO_AGGIORNAMENTO, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	if (theApp.m_nApplication == PRG_DERMOX)
	{
		GetDlgItem(IDC_STATIC1)->SetFont(&theApp.m_fontBold);
		GetDlgItem(IDC_COMBO_SEDE)->SetFont(&theApp.m_fontBold);

		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_SEDE)->ShowWindow(SW_SHOW);

		CSediEsameSet setTemp;
		if (setTemp.OpenRecordset("CListaPrenotazioniDlg::OnInitDialog"))
		{
			int nCurr = m_ctrlComboSede.AddString("");
			m_ctrlComboSede.SetItemData(nCurr, 0);

			while(!setTemp.IsEOF())
			{
				int nCurr = m_ctrlComboSede.AddString(setTemp.m_sDescrizione);
				m_ctrlComboSede.SetItemData(nCurr, setTemp.m_lID);

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CListaPrenotazioniDlg::OnInitDialog");
		}
	}

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pWorkListManager->PrepareList(&m_ctrlList);

	CString strSede = CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, FALSE);
	m_ctrlComboSede.SetCurSel(m_ctrlComboSede.FindStringExact(-1, strSede));
	OnCbnSelchangeComboSede();

	// RiempiLista();

	theApp.LocalizeDialog(this, CListaPrenotazioniDlg::IDD, "ListaPrenotazioniDlg");
	return TRUE;
}

void CListaPrenotazioniDlg::OnOK() 
{
	CEndoxResizableDlg::OnOK();
}

void CListaPrenotazioniDlg::OnCbnSelchangeComboSede()
{
	RiempiLista();
}

void CListaPrenotazioniDlg::OnDblClkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
	{
		if (m_pWorkListManager->SelectEntry(&m_ctrlList, m_ctrlList.GetNextSelectedItem(pos)))
		{
			PostMessage(WM_COMMAND, IDOK);
		}
		else
		{
			theApp.AfxMessageBoxEndo("Errore in CListaPrenotazioniDlg::OnDblclkList");
		}
	}

	*pResult = 0;
}

void CListaPrenotazioniDlg::RiempiLista() 
{
	CString strAddFilter = "";
	if (theApp.m_nApplication == PRG_DERMOX)
	{
		int nComboSede = m_ctrlComboSede.GetCurSel();
		if (nComboSede >= 0)
		{
			long lIDSedeEsame = (long)m_ctrlComboSede.GetItemData(nComboSede);
			if (lIDSedeEsame > 0)
				strAddFilter.Format("DescrizioneSede='%s'", CSediEsameSet().GetDescrizione(lIDSedeEsame, TRUE));
		}
	}

	if (!m_pWorkListManager->FillList(&m_ctrlList, strAddFilter))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRENOTAZIONE_EMPTY));

		if (theApp.m_nApplication != PRG_DERMOX)
		{
			ShowWindow(SW_HIDE);
			PostMessage(WM_COMMAND, IDOK);
		}
		else
		{
			CTime agg_ora = CTime::GetCurrentTime();
			CString strTmp;
			strTmp.Format(theApp.GetMessageString(IDS_LISTACUP_AGGTABELLA), agg_ora.Format("%H:%M"), agg_ora.Format("%d-%m-%Y"));

			GetDlgItem(IDC_ULTIMO_AGGIORNAMENTO)->SetWindowText(strTmp);
		}
	}
	else
	{
		CTime agg_ora = CTime::GetCurrentTime();
		CString strTmp;
		strTmp.Format(theApp.GetMessageString(IDS_LISTACUP_AGGTABELLA), agg_ora.Format("%H:%M"), agg_ora.Format("%d-%m-%Y"));

		GetDlgItem(IDC_ULTIMO_AGGIORNAMENTO)->SetWindowText(strTmp);
	}
}

void CListaPrenotazioniDlg::OnAggiorna() 
{
	RiempiLista();
}