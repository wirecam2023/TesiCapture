#include "stdafx.h"
#include "Endox.h"
#include "VisualizzatoreLogIntegrazioniDlg.h"

#include "EndoxMenu.h"
#include "EsamiView.h"
#include "InputMessageSet.h"
//#include "msxml6.tlh"
#include "PazientiSet.h"
#include "UtentiSet.h"
#include "VistaEsamiChiusiSet.h"
#include "VistaInputMessageWarningSet.h"
#include "VistaOutputMessageSet.h"
#include "XmlViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _inputMessageList 0
#define _refertiList 1


IMPLEMENT_DYNAMIC(CVisualizzatoreLogIntegrazioniDlg, CEndoxResizableDlg)

CVisualizzatoreLogIntegrazioniDlg::CVisualizzatoreLogIntegrazioniDlg(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxResizableDlg(CVisualizzatoreLogIntegrazioniDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_iColumn = 0;

	m_sPreviousFilter = "";
	m_lPreviousComboValue = -1;
}

CVisualizzatoreLogIntegrazioniDlg::~CVisualizzatoreLogIntegrazioniDlg()
{	
}

BEGIN_MESSAGE_MAP(CVisualizzatoreLogIntegrazioniDlg, CEndoxResizableDlg)
	ON_WM_CTLCOLOR()

	ON_CBN_SELCHANGE(IDC_COMBO_LIST, &CVisualizzatoreLogIntegrazioniDlg::OnCbnSelchangeComboList)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_FROM, &CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeDateFrom)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_FROM, &CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeTimeFrom)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_TO, &CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeDateTo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_TO, &CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeTimeTo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MESSAGES, &CVisualizzatoreLogIntegrazioniDlg::OnNMRClickListMessages)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_MESSAGES, &CVisualizzatoreLogIntegrazioniDlg::OnNMCustomdrawList)

	ON_COMMAND(ID_RIPROCESSAMESSAGGIO, RiprocessaMessaggio)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MESSAGES, &CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages)
	ON_BN_CLICKED(IDC_CLOSE, &CVisualizzatoreLogIntegrazioniDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_REFRESH, &CVisualizzatoreLogIntegrazioniDlg::OnBnClickedRefresh)
END_MESSAGE_MAP()

void CVisualizzatoreLogIntegrazioniDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_COMPLETATI, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_ERRORE, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_ELABORAZIONE, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_AVVERTIMENTI, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_NON_ELABORATI, m_ctrlStatic9);	

	DDX_Control(pDX, IDC_CLOSE, m_ctrlBtnChiudi);
	DDX_Control(pDX, IDC_LIST_MESSAGES, m_ctrlListIntegrazioni);
	DDX_Control(pDX, IDC_COMBO_LIST, m_ctrlMsgType);
	DDX_Control(pDX, IDC_DATE_FROM, m_ctrlDateFrom);
	DDX_Control(pDX, IDC_TIME_FROM, m_ctrlTimeFrom);
	DDX_Control(pDX, IDC_DATE_TO, m_ctrlDateTo);
	DDX_Control(pDX, IDC_TIME_TO, m_ctrlTimeTo);

	DDX_Control(pDX, IDC_EDIT_FILTER, m_ctrlEditFilter);
}

BOOL CVisualizzatoreLogIntegrazioniDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_2, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_DATE_FROM, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_TIME_FROM, CSize(0, 0), CSize(0, 0));	
	AddAnchor(IDC_STATIC_3, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_DATE_TO, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_TIME_TO, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_4, CSize(0, 0), CSize(0, 0));			
	AddAnchor(IDC_EDIT_FILTER, CSize(0, 0), CSize(80, 0));
	AddAnchor(IDC_COMBO_LIST, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_LIST_MESSAGES, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_CLOSE, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_REFRESH, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_STATIC_COMPLETATI, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_ERRORE, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_ELABORAZIONE, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_AVVERTIMENTI, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_NON_ELABORATI, CSize(50, 100), CSize(50, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	int i = m_ctrlMsgType.InsertString(0, "Input");
	m_ctrlMsgType.SetItemData(i, _inputMessageList);
	i = m_ctrlMsgType.InsertString(1, "Referti");
	m_ctrlMsgType.SetItemData(i, _refertiList);
	m_ctrlMsgType.SetCurSel(1);

	//Sistemo filtro ora
	int anno = CDate().GetYear();
	int mese = CDate().GetMonth();
	int giorno = CDate().GetDay();
	CTime timeFrom(anno,mese,giorno,0,0,0);
	m_ctrlTimeFrom.SetTime(&timeFrom);
	CTime timeTo(anno, mese, giorno, 23, 59, 59);
	m_ctrlTimeTo.SetTime(&timeTo);

	RiempiLista();

	theApp.LocalizeDialog(this, CVisualizzatoreLogIntegrazioniDlg::IDD, "VisualizzatoreLogIntegrazioniDlg");
	return TRUE;
}

HBRUSH CVisualizzatoreLogIntegrazioniDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{	
		case IDC_STATIC_COMPLETATI:
		{
			pDC->SetBkColor(RGB(119, 235, 99));

			break;
		}
		case IDC_STATIC_ERRORE:
		{
			pDC->SetBkColor(RGB(255, 127, 127));

			break;
		}
		case IDC_STATIC_ELABORAZIONE:
		{
			pDC->SetBkColor(RGB(185, 255, 253));

			break;
		}
		case IDC_STATIC_AVVERTIMENTI:
		{
			pDC->SetBkColor(RGB(241, 238, 92));

			break;
		}
		case IDC_STATIC_NON_ELABORATI:
		{
			pDC->SetBkColor(RGB(255, 255, 255));

			break;
		}
	}

	return hBrush;
}

void CVisualizzatoreLogIntegrazioniDlg::RiempiLista(BOOL changedCombo)
{
	m_ctrlListIntegrazioni.SetRedraw(FALSE);

	RemoveAll(changedCombo);

	CheckComboTipo();

	m_ctrlListIntegrazioni.SetExtendedStyle(m_ctrlListIntegrazioni.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	m_ctrlListIntegrazioni.SetRedraw(TRUE);
}

BOOL CVisualizzatoreLogIntegrazioniDlg::IsOracleConnection()
{
	CString strConnect = theApp.m_dbEndox.GetDecryptedConnectionString();
	strConnect.MakeUpper();
	return strConnect.Find("ORACLE") > 0;
}

void CVisualizzatoreLogIntegrazioniDlg::RiempiListaInput()
{
	m_iColumn = 0;
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_DATAEORA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_APPLICAZIONE), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_MESSAGGIO), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_RISPOSTA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);

	m_ctrlListIntegrazioni.SetExtendedStyle(m_ctrlListIntegrazioni.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//Recupero data e ora
	CString strDateFrom = GetDataOraFrom();
	CString strDateTo = GetDataOraTo();

	CString strFilter;
	strFilter.Format("StoreTime >= '%s' and StoreTime <= '%s'", strDateFrom, strDateTo);

	if (m_sPreviousFilter != "")
	{
		if (IsOracleConnection())
		{
			CString temp = m_sPreviousFilter;
			temp.MakeUpper();
			strFilter.AppendFormat(" and upper(encodedMessage) like '%%%s%%'", temp);
		}
		else
		{
			strFilter.AppendFormat(" and encodedMessage like '%%%s%%'", m_sPreviousFilter);
		}
	}
	
	CInputMessageSet iMsgSet;
	iMsgSet.SetOpenFilter(strFilter);
	iMsgSet.OpenRecordset("CVisualizzatoreLogIntegrazioniDlg::RiempiListaInput");

	while (!iMsgSet.IsEOF())
	{
		COleDateTime date = COleDateTime(atoi(iMsgSet.m_sStoreTime.Mid(0, 4)), atoi(iMsgSet.m_sStoreTime.Mid(4, 2)), atoi(iMsgSet.m_sStoreTime.Mid(6, 2)), atoi(iMsgSet.m_sStoreTime.Mid(8, 2)), atoi(iMsgSet.m_sStoreTime.Mid(10, 2)), atoi(iMsgSet.m_sStoreTime.Mid(12, 2)));
		int iItemInserted = m_ctrlListIntegrazioni.InsertItem(m_ctrlListIntegrazioni.GetItemCount(), date.Format());
		m_ctrlListIntegrazioni.SetItemData(iItemInserted, iMsgSet.m_lId);
		m_ctrlListIntegrazioni.SetItemText(iItemInserted, 1, iMsgSet.m_sAppSender);

		CString temp;
		if (iMsgSet.m_sEncodedMessage.GetLength() == 0)
			temp = "";
		else 
			temp = iMsgSet.m_sEncodedMessage;
		m_ctrlListIntegrazioni.SetItemText(iItemInserted, 2, RimuoviDoppiSpazi(temp));

		if (iMsgSet.m_sSynchronousMessage.GetLength() == 0)
			temp = "";
		else 
			temp = iMsgSet.m_sSynchronousMessage;
		m_ctrlListIntegrazioni.SetItemText(iItemInserted, 3, RimuoviDoppiSpazi(temp));

		if (iMsgSet.m_bErrored)
		{
			m_listErrored.AddTail(iMsgSet.m_lId);
		}
		else
		{
			CVistaInputMessageWarningSet warningSet;
			strFilter.Format("id=%li", iMsgSet.m_lId);
			warningSet.SetOpenFilter(strFilter);
			if (warningSet.OpenRecordset("CVisualizzatoreLogIntegrazioniDlg::RiempiListaInput"))
			{
				if (!warningSet.IsEOF())
				{					
					m_listWarned.AddTail(iMsgSet.m_lId);
				}
				else
				{
					m_listSent.AddTail(iMsgSet.m_lId);
				}

				warningSet.CloseRecordset("CVisualizzatoreLogIntegrazioniDlg::RiempiListaInput");
			}
		}

		iMsgSet.MoveNext();
	}

	iMsgSet.CloseRecordset("CVisualizzatoreLogIntegrazioniDlg::RiempiListaInput");

	CRect rect;
	m_ctrlListIntegrazioni.GetWindowRect(&rect);
	int space = rect.Width() - 150 - 100;

	m_ctrlListIntegrazioni.SetColumnWidth(0, 150);
	m_ctrlListIntegrazioni.SetColumnWidth(1, 100);
	m_ctrlListIntegrazioni.SetColumnWidth(2, (space/100)*50);
	m_ctrlListIntegrazioni.SetColumnWidth(3, (space / 100) * 50);

}

void CVisualizzatoreLogIntegrazioniDlg::RiempiListaReferti()
{
	m_iColumn = 0;
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_DATAEORA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_TIPORICHIESTA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_UTENTE), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_IDRICHIESTA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_TIPOREFERTO), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_PAZIENTE), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlListIntegrazioni.InsertColumn(m_iColumn++, theApp.GetMessageString(IDS_RISPOSTA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);

	m_ctrlListIntegrazioni.SetExtendedStyle(m_ctrlListIntegrazioni.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//Recupero data e ora
	CString strDateFrom = GetDataOraFrom();
	CString strDateTo = GetDataOraTo();

	CString strFilter;
	strFilter.Format("DataOra >= '%s' and DataOra <= '%s'", strDateFrom, strDateTo);

	if (m_sPreviousFilter != "")
	{
		if (IsOracleConnection())
		{
			CString temp = m_sPreviousFilter;
			temp.MakeUpper();
			strFilter.AppendFormat(" and (upper(cognome || ' ' || nome) like '%%%s%%' or codesame like '%%%s%%')", temp, temp);
		}
		else
		{
			strFilter.AppendFormat(" and (cognome + ' ' + nome like '%%%s%%' or codesame like '%%%s%%')", m_sPreviousFilter, m_sPreviousFilter);
		}
	}

	CVistaEsamiChiusiSet closedExamSet;
	closedExamSet.SetOpenFilter(strFilter);
	closedExamSet.OpenRecordset("CVisualizzatoreLogIntegrazioniDlg::RiempiListaReferti");

	while (!closedExamSet.IsEOF())
	{
		COleDateTime date = COleDateTime(atoi(closedExamSet.m_sDataOra.Mid(0, 4)), atoi(closedExamSet.m_sDataOra.Mid(4, 2)), atoi(closedExamSet.m_sDataOra.Mid(6, 2)), atoi(closedExamSet.m_sDataOra.Mid(8, 2)), atoi(closedExamSet.m_sDataOra.Mid(10, 2)), atoi(closedExamSet.m_sDataOra.Mid(12, 2)));
		int iItemInserted = m_ctrlListIntegrazioni.InsertItem(m_ctrlListIntegrazioni.GetItemCount(), date.Format());
		m_ctrlListIntegrazioni.SetItemData(iItemInserted, closedExamSet.m_lIdChiusura);

		if (closedExamSet.m_lTipologiaWorklist == 1)
			m_ctrlListIntegrazioni.SetItemText(iItemInserted, 1, theApp.GetMessageString(IDS_DICOM));
		else if (closedExamSet.m_lTipologiaWorklist == 0)
		{
			if (closedExamSet.m_sCodEsame.Left(5) == "ENDOX")
				m_ctrlListIntegrazioni.SetItemText(iItemInserted, 1, theApp.GetMessageString(IDS_DIRETTA));
			else
				m_ctrlListIntegrazioni.SetItemText(iItemInserted, 1, theApp.GetMessageString(IDS_HL7));
		}

		m_ctrlListIntegrazioni.SetItemText(iItemInserted, 2, CUtentiSet().GetUsername(closedExamSet.m_lIdUtente));
		m_ctrlListIntegrazioni.SetItemText(iItemInserted, 3, closedExamSet.m_sCodEsame);
		if (closedExamSet.m_sTipologia == "NW")
			m_ctrlListIntegrazioni.SetItemText(iItemInserted, 4, theApp.GetMessageString(IDS_NUOVOREFERTO));
		else
			m_ctrlListIntegrazioni.SetItemText(iItemInserted, 4, theApp.GetMessageString(IDS_REFERTOANNULLATIVO));
		m_ctrlListIntegrazioni.SetItemText(iItemInserted, 5, CPazientiSet().GetCognomeNomeDataNascita(closedExamSet.m_lIdPaziente));
		m_ctrlListIntegrazioni.SetItemText(iItemInserted, 6, closedExamSet.m_sEsito);

		if (closedExamSet.m_lEseguito == IntegrationSendStatus::errored)
		{
			m_listErrored.AddTail(closedExamSet.m_lIdChiusura);
		}
		else if (closedExamSet.m_lEseguito == IntegrationSendStatus::filtered)
		{
			m_listWarned.AddTail(closedExamSet.m_lIdChiusura);
		}
		else if (closedExamSet.m_lEseguito == IntegrationSendStatus::inProgress)
		{
			m_listInProgress.AddTail(closedExamSet.m_lIdChiusura);
		}
		else if (closedExamSet.m_lEseguito == IntegrationSendStatus::sent)
		{
			m_listSent.AddTail(closedExamSet.m_lIdChiusura);
		}		

		closedExamSet.MoveNext();
	}

	closedExamSet.CloseRecordset("CVisualizzatoreLogIntegrazioniDlg::RiempiListaReferti");

	CRect rect;
	m_ctrlListIntegrazioni.GetWindowRect(&rect);	

	m_ctrlListIntegrazioni.SetColumnWidth(0, 150);
	m_ctrlListIntegrazioni.SetColumnWidth(1, 100);
	m_ctrlListIntegrazioni.SetColumnWidth(2, 100);
	m_ctrlListIntegrazioni.SetColumnWidth(3, 150);
	m_ctrlListIntegrazioni.SetColumnWidth(4, 100);
	m_ctrlListIntegrazioni.SetColumnWidth(5, 200);

	int space = rect.Width();

	for (int i = 0; i < 6; i++)
		space -= m_ctrlListIntegrazioni.GetColumnWidth(i);

	m_ctrlListIntegrazioni.SetColumnWidth(6, (space / 100) * 100);

}

void CVisualizzatoreLogIntegrazioniDlg::OnCbnSelchangeComboList()
{
	//Riempio la lista solo se il valore della combo è effettivamente cambiato
	if (m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel()) != m_lPreviousComboValue)
	{
		RiempiLista(TRUE);

		//Mantengo la riga attualmente selezionata
		m_lPreviousComboValue = m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel());
	}
}

void CVisualizzatoreLogIntegrazioniDlg::CheckComboTipo()
{
	switch (m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel()))
	{
		case _inputMessageList:
			RiempiListaInput();
			break;
		case _refertiList:
			RiempiListaReferti();
		default:
			break;
	}
}

void CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeDateFrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	RiempiLista();
	*pResult = 0;
}


void CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeTimeFrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	RiempiLista();
	*pResult = 0;
}


void CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeDateTo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	RiempiLista();
	*pResult = 0;
}


void CVisualizzatoreLogIntegrazioniDlg::OnDtnDatetimechangeTimeTo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	RiempiLista();
	*pResult = 0;
}

CString CVisualizzatoreLogIntegrazioniDlg::RimuoviDoppiSpazi(CString input)
{
	CString temp = input;

	while (input.Find("  ") > -1)
		input.Replace("  ", " ");

	return input.Trim();
}

CString CVisualizzatoreLogIntegrazioniDlg::GetDataOraFrom()
{
	CTime dateFrom, timeFrom;
	m_ctrlDateFrom.GetTime(dateFrom);
	m_ctrlTimeFrom.GetTime(timeFrom);
	
	CString strDateFrom;
	strDateFrom.Format("%s%s", dateFrom.Format("%Y%m%d"), timeFrom.Format("%H%M%S"));

	return strDateFrom;
}

CString CVisualizzatoreLogIntegrazioniDlg::GetDataOraTo()
{
	CTime dateTo, timeTo;
	m_ctrlDateTo.GetTime(dateTo);
	m_ctrlTimeTo.GetTime(timeTo);

	CString strDateTo;
	strDateTo.Format("%s%s", dateTo.Format("%Y%m%d"), timeTo.Format("%H%M%S"));

	return strDateTo;
}

void CVisualizzatoreLogIntegrazioniDlg::OnNMRClickListMessages(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	ShowMenu();
	*pResult = 0;
}

void CVisualizzatoreLogIntegrazioniDlg::ShowMenu()
{
	if (POSITION pos = m_ctrlListIntegrazioni.GetFirstSelectedItemPosition())
	{
		int item = m_ctrlListIntegrazioni.GetNextSelectedItem(pos);
		int idRecord = m_ctrlListIntegrazioni.GetItemData(item);
		if (idRecord > -1)
		{
			CPoint point;
			GetCursorPos(&point);

			CEndoxMenu menu;
			menu.LoadMenu(IDR_MENU_LOG);			

			CEndoxMenu* pMenu = (CEndoxMenu*)menu.GetSubMenu(0);
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
	}
}

void CVisualizzatoreLogIntegrazioniDlg::RiprocessaMessaggio()
{	
	if ((m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel()) == _refertiList && theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIPROCESSAREMSGSEL2), MB_YESNO) == IDYES) ||
		(m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel()) == _inputMessageList && theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIPROCESSAREMSGSEL2), MB_YESNO) == IDYES))
	{
		POSITION pos = m_ctrlListIntegrazioni.GetFirstSelectedItemPosition();

		while (pos)
		{
			int item = m_ctrlListIntegrazioni.GetNextSelectedItem(pos);

			if (item > -1)
			{
				switch (m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel()))
				{					
					case _inputMessageList:
					{
						long id = (long)m_ctrlListIntegrazioni.GetItemData(item);
						CString strQuery;
						strQuery.Format("UPDATE ext_inputmsg SET processed = 0 WHERE id=%li", id);
						theApp.m_dbEndox.ExecuteSQL(strQuery);

						break;
					}
					case _refertiList:
					{
						long id = (long)m_ctrlListIntegrazioni.GetItemData(item);
						CString strQuery;
						strQuery.Format("UPDATE ext_esami_chiusi SET eseguito = %li, esito = null WHERE id=%li", IntegrationSendStatus::notSent, id);
						theApp.m_dbEndox.ExecuteSQL(strQuery);

						break;
					}
					default:
						break;
				}
			}
		}

		RiempiLista();
	}
}

void CVisualizzatoreLogIntegrazioniDlg::RemoveAll(BOOL changedCombo)
{
	//Cancello la memoria solo se l'elenco precedente era quello dei messaggi di output oppure se ho refreshato i messaggi di output stessi
	/*if ((changedCombo && m_lPreviousComboValue == _outputMessageList) || !changedCombo && m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel()) == _outputMessageList))
	{
		for (int i = 0; i < m_ctrlListIntegrazioni.GetItemCount(); i++)
		{
			CString *temp = (CString*)m_ctrlListIntegrazioni.GetItemData(i);
			delete(temp);
		}
	}*/

	//Svuoto la griglia
	m_ctrlListIntegrazioni.DeleteAllItems();
	for (int i = m_iColumn - 1; i >= 0; i--)
		m_ctrlListIntegrazioni.DeleteColumn(i);

	//Svuoto le liste di errori e warning
	m_listErrored.RemoveAll();
	m_listWarned.RemoveAll();
	m_listInProgress.RemoveAll();
	m_listSent.RemoveAll();
}

void CVisualizzatoreLogIntegrazioniDlg::OnBnClickedCancel()
{
	RemoveAll();
	CResizableDialog::OnCancel();
}


void CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);	

	POSITION pos = m_ctrlListIntegrazioni.GetFirstSelectedItemPosition();

	if (pos)
	{
		int item = m_ctrlListIntegrazioni.GetNextSelectedItem(pos);

		if (item > -1)
		{
			switch (m_ctrlMsgType.GetItemData(m_ctrlMsgType.GetCurSel()))
			{
				case _inputMessageList:
				{
					long messageId = (long)m_ctrlListIntegrazioni.GetItemData(item);

					CString strFilter;
					strFilter.Format("id=%li", messageId);

					CInputMessageSet iMsgSet;
					iMsgSet.SetOpenFilter(strFilter);
					iMsgSet.OpenRecordset("CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages");

					if (!iMsgSet.IsEOF())
					{
						CStringList warningList;
						CVistaInputMessageWarningSet warningSet;
						strFilter.Format("id=%li", iMsgSet.m_lId);
						warningSet.SetOpenFilter(strFilter);
						if (warningSet.OpenRecordset("CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages"))
						{
							while (!warningSet.IsEOF())
							{
								warningList.AddTail(warningSet.m_sWarningMessage);

								warningSet.MoveNext();
							}

							warningSet.CloseRecordset("CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages");
						}

						CXmlViewerDlg dlg(this, iMsgSet.m_sEncodedMessage, iMsgSet.m_sErrorMessage, warningList);
						dlg.DoModal();
					}

					iMsgSet.CloseRecordset("CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages");
				}
				case _refertiList:
				{
					long messageId = (long)m_ctrlListIntegrazioni.GetItemData(item);

					CString strFilter;
					strFilter.Format("idchiusura=%li", messageId);

					CVistaEsamiChiusiSet esamiChiusiSet;
					esamiChiusiSet.SetOpenFilter(strFilter);
					esamiChiusiSet.OpenRecordset("CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages");

					if (!esamiChiusiSet.IsEOF())
					{
						CStringList warningList;

						CXmlViewerDlg dlg(this, "", esamiChiusiSet.m_sEsito, warningList);
						dlg.DoModal();
					}

					esamiChiusiSet.CloseRecordset("CVisualizzatoreLogIntegrazioniDlg::OnNMDblclkListMessages");
				}
				default:
					break;
			}
			
		}
	}

	*pResult = 0;
}

void CVisualizzatoreLogIntegrazioniDlg::OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	switch (pLVCD->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		}
		case CDDS_ITEMPREPAINT:
		{
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;
		}
		case (CDDS_ITEMPREPAINT | CDDS_SUBITEM) :
		{
			if (pLVCD->iSubItem == 0)
			{
				long id = (long) pLVCD->nmcd.lItemlParam;
		
				if (m_listErrored.Find(id) != NULL)
				{
					pLVCD->clrTextBk = RGB(255, 127, 127);
				}
				else if (m_listWarned.Find(id) != NULL)
				{
					pLVCD->clrTextBk = RGB(241, 238, 92);				
				}
				else if (m_listInProgress.Find(id) != NULL)
				{				
					pLVCD->clrTextBk = RGB(185, 255, 253);
				}
				else if (m_listSent.Find(id) != NULL)
				{
					//OK
					pLVCD->clrTextBk = RGB(119, 235, 99);
				}		
			}

			break;
		}
	}
}

void CVisualizzatoreLogIntegrazioniDlg::OnCancel()
{
}

void CVisualizzatoreLogIntegrazioniDlg::OnOK()
{
	CString filter;
	m_ctrlEditFilter.GetWindowText(filter);

	if (filter != m_sPreviousFilter)
	{
		m_sPreviousFilter = filter;

		RiempiLista();
	}
}

void CVisualizzatoreLogIntegrazioniDlg::OnBnClickedClose()
{
	CEndoxResizableDlg::OnOK();
}

void CVisualizzatoreLogIntegrazioniDlg::OnBnClickedRefresh()
{
	RiempiLista();
}
