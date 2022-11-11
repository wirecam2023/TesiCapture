#include "stdafx.h"
#include "Endox.h"
#include "MenuDiagnosiICD9Dlg.h"

#include "DiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_GO 0x655

CMenuDiagnosiICD9Dlg::CMenuDiagnosiICD9Dlg(CWnd* pParent, long lInit, CString strInit, int nProgramMode, CRect rect, CString* sQuery, CString* sQueryView)
	: CDialog(CMenuDiagnosiICD9Dlg::IDD, pParent)
{
	if (nProgramMode & FILTER_RECORD_ESAMI)
		m_bModalitaRicerca = TRUE;
	else
		m_bModalitaRicerca = FALSE;
	
	m_bOrPressed = FALSE;

	m_nItemCount = 0;
	m_nItemPressed = 0;

	m_lContatore = 0;

	m_rect = rect;

	m_lRicerca = lInit;
	m_strRicerca = strInit;

	//	

	m_pStrQuery = sQuery;
	m_pStrQueryView = sQueryView;

	m_bTastoCliccato = FALSE;

}

CMenuDiagnosiICD9Dlg::~CMenuDiagnosiICD9Dlg()
{
}

void CMenuDiagnosiICD9Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RICERCA, m_ctrlRicerca);
	DDX_Control(pDX, IDC_LISTA, m_ctrLista);

	DDX_Control(pDX, IDC_RESET, m_ctrlButtonReset);
	DDX_Control(pDX, IDC_CLOSE, m_ctrlButtonClose);

	DDX_Control(pDX, IDC_QUERY, m_ctrlQuery);

}

BEGIN_MESSAGE_MAP(CMenuDiagnosiICD9Dlg, CDialog)

	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_RESET, OnReset)

	ON_BN_CLICKED(IDC_AND, OnBtnAnd)
	ON_BN_CLICKED(IDC_OR, OnBtnOr)

	ON_EN_CHANGE(IDC_RICERCA, OnChangeRicerca)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTA, &CMenuDiagnosiICD9Dlg::OnLvnItemchangedLista)

	ON_WM_TIMER()

END_MESSAGE_MAP()


BOOL CMenuDiagnosiICD9Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lContatore = 0;

	GetDlgItem(IDC_RESET)->EnableWindow(TRUE);	

	OnChangeRicerca();

	if (m_strRicerca.IsEmpty())
	{
		GetDlgItem(IDC_AND)->EnableWindow(FALSE);
		GetDlgItem(IDC_OR)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_AND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OR)->ShowWindow(SW_HIDE);
	m_ctrlQuery.ShowWindow(SW_HIDE);

	if (m_bModalitaRicerca)
	{
		GetDlgItem(IDC_OR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_AND)->ShowWindow(SW_SHOW);

		m_ctrlQuery.ShowWindow(SW_SHOW);
	}

	m_nItemCount = m_ctrLista.GetItemCount();

	m_ctrLista.DeleteAllItems();
	m_ctrLista.InsertColumn(0, theApp.GetMessageString(IDS_CODICE));
	m_ctrLista.InsertColumn(1, theApp.GetMessageString(IDS_DESCRIZIONE));

	//Se sono in modifica, setto i valori
	if (m_lRicerca > 0)
	{
		m_ctrlRicerca.SetWindowText(m_strRicerca);
		m_lContatore = m_lRicerca;

		CString descrizione = CDiagnosiICD9Set().GetStringDescrizione(m_lContatore);

		FillDiagnosiList(descrizione);
	}

	/*CRect rectWnd, rectDesk;
	GetWindowRect(&rectWnd);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);

	SetWindowPos(NULL, min(m_rect.left, rectDesk.right - rectWnd.Width()), min(m_rect.bottom, rectDesk.bottom - rectWnd.Height()), 0, 0, SWP_NOSIZE | SWP_NOZORDER);*/

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	theApp.LocalizeDialog(this, CMenuDiagnosiICD9Dlg::IDD, "MenuDiagnosiICD9Dlg");
	return TRUE;
}

void CMenuDiagnosiICD9Dlg::OnOK()
{	
}

void CMenuDiagnosiICD9Dlg::OnClose()
{
	POSITION pos = m_ctrLista.GetFirstSelectedItemPosition();

	if (pos)
	{
		int index = m_ctrLista.GetNextSelectedItem(pos);

		if (index >= 0)
			m_lContatore = m_ctrLista.GetItemData(index);
	}

	CDialog::OnOK();
}

void CMenuDiagnosiICD9Dlg::OnReset()
{
	GetDlgItem(IDC_RICERCA)->SetWindowText("");

	m_lContatore = 0;

	m_ctrlQuery.SetWindowText("");
	*m_pStrQuery = "";
	*m_pStrQueryView = "";
}

void CMenuDiagnosiICD9Dlg::OnBtnAnd()
{
	BOOL bAddParentesi = FALSE;

	CString strRicerca;
	m_ctrlQuery.GetWindowText(strRicerca);

	if (strRicerca.Find("OR ") != -1)
		bAddParentesi = TRUE;

	if (bAddParentesi)
		strRicerca = "(" + strRicerca + ")";

	strRicerca += " AND";

	
	if (bAddParentesi)
		*m_pStrQuery = "(" + *m_pStrQuery + ")";

	*m_pStrQuery += " AND";	

	GetDlgItem(IDC_AND)->EnableWindow(FALSE);
	GetDlgItem(IDC_OR)->EnableWindow(FALSE);

	m_ctrlQuery.SetWindowText(strRicerca);

	m_bOrPressed = TRUE;
}

void CMenuDiagnosiICD9Dlg::OnBtnOr()
{
	BOOL bAddParentesi = FALSE;

	CString strRicerca;
	m_ctrlQuery.GetWindowText(strRicerca);

	if (strRicerca.Find("AND ") != -1)
		bAddParentesi = TRUE;

	if (bAddParentesi)
		strRicerca = "(" + strRicerca + ")";

	strRicerca += " OR";

	
	if (bAddParentesi)
		*m_pStrQuery = "(" + *m_pStrQuery + ")";

	*m_pStrQuery += " OR";	

	GetDlgItem(IDC_AND)->EnableWindow(FALSE);
	GetDlgItem(IDC_OR)->EnableWindow(FALSE);

	m_ctrlQuery.SetWindowText(strRicerca);

	m_bOrPressed = TRUE;
}

void CMenuDiagnosiICD9Dlg::OnChangeRicerca()
{
	m_bTastoCliccato = TRUE;

	CString text;
	m_ctrlRicerca.GetWindowText(text);
	if (text.GetLength() >= 3)
	{
		m_bTastoCliccato = FALSE;
		SetTimer(TIMER_GO, 1000, NULL);		
	}
}

void CMenuDiagnosiICD9Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	switch (nIDEvent)
	{
		case TIMER_GO:
		{
			KillTimer(TIMER_GO);

			if (!m_bTastoCliccato)
			{
				CString text;
				m_ctrlRicerca.GetWindowText(text);

				m_ctrLista.DeleteAllItems();
				FillDiagnosiList(text);
			}

			break;
		}
		
	}
}

void CMenuDiagnosiICD9Dlg::FillDiagnosiList(CString filter)
{
	m_ctrLista.DeleteAllItems();

	CDiagnosiICD9Set set;
	CString strFilter;
	strFilter.Format("UPPER(DESCRIZIONE) like '%%%s%%'", filter.MakeUpper());

	set.SetOpenFilter(strFilter);
	set.SetSortRecord("DESCRIZIONE");

	if (set.OpenRecordset("CMenuDiagnosiICD9Dlg::FillDiagnosiList"))
	{
		while (!set.IsEOF())
		{
			int index = m_ctrLista.InsertItem(m_ctrLista.GetItemCount(), set.m_sCodificaICD9Esterni);
			m_ctrLista.SetItemText(index, 1, set.m_sDescrizione);

			m_ctrLista.SetItemData(index, set.m_lID);

			//Aggiungo gli elementi con stesso codice che non rientrano nella descrizione
			strFilter.Format("ID <> %li AND CODIFICAICD9ESTERNI = '%s'", set.m_lID, set.m_sCodificaICD9Esterni);
			CDiagnosiICD9Set setEx;
			setEx.SetOpenFilter(strFilter);
			setEx.SetSortRecord("DESCRIZIONE");

			if (setEx.OpenRecordset("CMenuDiagnosiICD9Dlg::FillDiagnosiList"))
			{
				while (!setEx.IsEOF())
				{
					index = m_ctrLista.InsertItem(m_ctrLista.GetItemCount(), "");
					m_ctrLista.SetItemText(index, 1, setEx.m_sDescrizione);

					m_ctrLista.SetItemData(index, setEx.m_lID);

					setEx.MoveNext();
				}

				setEx.CloseRecordset("CMenuDiagnosiICD9Dlg::FillDiagnosiList");
			}

			set.MoveNext();
		}

		set.CloseRecordset("CMenuDiagnosiICD9Dlg::FillDiagnosiList");
	}

	for (int h = 0; h<2; h++)
		m_ctrLista.SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrLista.SetExtendedStyle(m_ctrLista.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
}

void CMenuDiagnosiICD9Dlg::OnLvnItemchangedLista(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if (m_bModalitaRicerca)
	{
		POSITION pos = m_ctrLista.GetFirstSelectedItemPosition();

		if (pos && pNMLV->uNewState == 3)
		{
			GetDlgItem(IDC_AND)->EnableWindow(TRUE);
			GetDlgItem(IDC_OR)->EnableWindow(TRUE);

			int index = m_ctrLista.GetNextSelectedItem(pos);

			if (index >= 0)
			{
				int id = m_ctrLista.GetItemData(index);
				CString desc = m_ctrLista.GetItemText(index, 1);

				if (m_bOrPressed)
				{
					CString temp;
					m_ctrlQuery.GetWindowText(temp);

					temp += " " + desc;
					m_ctrlQuery.SetWindowText(temp);
					m_ctrlQuery.GetWindowText(*m_pStrQueryView);

					m_pStrQuery->AppendFormat(" %li", id);

					m_bOrPressed = FALSE;

				}
				else
				{
					m_ctrlQuery.SetWindowText(desc);
					m_ctrlQuery.GetWindowText(*m_pStrQueryView);

					m_pStrQuery->Format("%li", id);
				}

			}
		}		
		else
		{
			GetDlgItem(IDC_AND)->EnableWindow(FALSE);
			GetDlgItem(IDC_OR)->EnableWindow(FALSE);
		}
	}
	
	*pResult = 0;
}
