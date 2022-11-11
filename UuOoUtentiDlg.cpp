#include "stdafx.h"
#include "Endox.h"
#include "UuOoUtentiDlg.h"

#include "UOSet.h"
#include "UOUtenteSet.h"
#include "UtentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUuOoUtentiDlg, CDialog)

CUuOoUtentiDlg::CUuOoUtentiDlg(CWnd* pParent)
	: CDialog(CUuOoUtentiDlg::IDD, pParent)
{
	m_lIDUtente = 0;
}

CUuOoUtentiDlg::~CUuOoUtentiDlg()
{
}

BEGIN_MESSAGE_MAP(CUuOoUtentiDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ESCI, OnBnClickedBtnEsci)

	ON_LBN_SELCHANGE(IDC_LIST_UTENTI, OnLbnSelchangeListUtenti)
	ON_LBN_SELCHANGE(IDC_LIST_UNITAOPERATIVE, OnLbnSelchangeListUnitaOperative)
END_MESSAGE_MAP()

void CUuOoUtentiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_ESCI, m_ctrlBtnEsci);

	DDX_Control(pDX, IDC_LIST_UTENTI, m_ctrlListUtenti);
	DDX_Control(pDX, IDC_LIST_UNITAOPERATIVE, m_ctrlListUnitaOperative);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
}

void CUuOoUtentiDlg::OnCancel()
{
}

BOOL CUuOoUtentiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);

	RiempiListaUtenti();
	RiempiListaUnitaOperative();

	theApp.LocalizeDialog(this, CUuOoUtentiDlg::IDD, "UuOoUtentiDlg");
	return TRUE;
}

void CUuOoUtentiDlg::OnOK()
{
}

void CUuOoUtentiDlg::OnBnClickedBtnEsci()
{
	CDialog::OnOK();
}

void CUuOoUtentiDlg::OnLbnSelchangeListUtenti()
{
	BOOL bEnableListUnitaOperative = FALSE;
	m_lIDUtente = 0;

	int nCurSel = m_ctrlListUtenti.GetCurSel();
	if (nCurSel >= 0)
	{
		m_lIDUtente = (long)m_ctrlListUtenti.GetItemData(nCurSel);
		bEnableListUnitaOperative = (m_lIDUtente > 0);

		SelezionaUnitaOperative();
	}

	m_ctrlListUnitaOperative.EnableWindow(bEnableListUnitaOperative);
}

void CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative()
{
	// cerco l'elemento selezionato o deselezionato //

	for(int i = 0; i < m_ctrlListUnitaOperative.GetCount(); i ++)
	{
		long lIDUO = (long)m_ctrlListUnitaOperative.GetItemData(i);

		if (m_ctrlListUnitaOperative.GetSel(i) == 0)
		{
			// se l'elemento è attualmente DESELEZIONATO controllo che prima non fosse selezionato //

			POSITION pos = m_listIDUOSelezionate.Find(lIDUO);
			if (pos != NULL)
			{
				///////////////////////////
				// è stato deselezionato //
				///////////////////////////

				// lo rimuovo dal recordset //
				CString sFilter;
				sFilter.Format("IDUO=%li AND IDUtente=%li", lIDUO, m_lIDUtente);

				CUOUtenteSet setTemp;
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative"))
				{
					while(!setTemp.IsEOF())
					{
						setTemp.DeleteRecordset("CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative");
						setTemp.MoveNext();
					}

					setTemp.CloseRecordset("CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative");
				}

				// lo rimuovo dalla lista degli ID selezionati //
				m_listIDUOSelezionate.RemoveAt(pos);
			}
		}
		else if (m_ctrlListUnitaOperative.GetSel(i) > 0)
		{
			// se l'elemento è attualmente SELEZIONATO controllo che prima non fosse deselezionato //

			POSITION pos = m_listIDUOSelezionate.Find(lIDUO);
			if (pos == NULL)
			{
				///////////////////////////
				// è stato deselezionato //
				///////////////////////////

				// lo aggiungo al recordset //
				CUOUtenteSet setTemp;
				setTemp.SetOpenFilter("ID=0");
				if (setTemp.OpenRecordset("CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative"))
				{
					if (setTemp.AddNewRecordset("CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative"))
					{
						setTemp.m_lIDUO = lIDUO;
						setTemp.m_lIDUtente = m_lIDUtente;

						setTemp.UpdateRecordset("CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative");
					}

					setTemp.CloseRecordset("CUuOoUtentiDlg::OnLbnSelchangeListUnitaOperative");
				}

				// lo aggiungo alla lista degli ID selezionati //
				m_listIDUOSelezionate.AddTail(lIDUO);
			}
		}
	}
}

void CUuOoUtentiDlg::RiempiListaUtenti()
{
	BeginWaitCursor();
	m_ctrlListUtenti.SetRedraw(FALSE);
	m_ctrlListUtenti.ResetContent();

	CUtentiSet setTemp;
	setTemp.SetOpenFilter("Eliminato=0");
	setTemp.SetSortRecord("Username");
	if (setTemp.OpenRecordset("CUuOoUtentiDlg::RiempiListaUtenti"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListUtenti.InsertString(nIndex, setTemp.m_sUsername);
			m_ctrlListUtenti.SetItemData(nIndex, (DWORD)setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CUuOoUtentiDlg::RiempiListaUtenti");
	}

	m_ctrlListUtenti.SetRedraw(TRUE);
	EndWaitCursor();
}

void CUuOoUtentiDlg::RiempiListaUnitaOperative()
{
	BeginWaitCursor();
	m_ctrlListUnitaOperative.SetRedraw(FALSE);
	m_ctrlListUnitaOperative.ResetContent();

	CUOSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CUuOoUtentiDlg::RiempiListaUnitaOperative"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListUnitaOperative.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlListUnitaOperative.SetItemData(nIndex, (DWORD)setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CUuOoUtentiDlg::RiempiListaUnitaOperative");
	}

	m_ctrlListUnitaOperative.SetRedraw(TRUE);
	EndWaitCursor();
}

void CUuOoUtentiDlg::SelezionaUnitaOperative()
{
	// inizio
	BeginWaitCursor();
	m_ctrlListUnitaOperative.SetRedraw(FALSE);

	// deseleziono tutti gli elementi //
	m_ctrlListUnitaOperative.SelItemRange(FALSE, 0, m_ctrlListUnitaOperative.GetCount() - 1);
	m_listIDUOSelezionate.RemoveAll();

	// seleziono le unità operative di questo utente //
	CString sFilter;
	sFilter.Format("IDUtente=%li", m_lIDUtente);

	CUOUtenteSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CUuOoUtentiDlg::SelezionaUnitaOperative"))
	{
		while(!setTemp.IsEOF())
		{
			for(int i = 0; i < m_ctrlListUnitaOperative.GetCount(); i++)
			{
				if (m_ctrlListUnitaOperative.GetItemData(i) == setTemp.m_lIDUO)
				{
					m_ctrlListUnitaOperative.SetSel(i, TRUE);
					m_listIDUOSelezionate.AddTail(setTemp.m_lIDUO);
					break;
				}
			}

			//
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CUuOoUtentiDlg::SelezionaUnitaOperative");
	}

	// riscrollo la lista all'inizio //
	m_ctrlListUnitaOperative.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// fine
	m_ctrlListUnitaOperative.SetRedraw(TRUE);
	EndWaitCursor();
}