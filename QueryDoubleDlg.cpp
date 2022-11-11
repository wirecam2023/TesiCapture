#include "stdafx.h"
#include "Endox.h"
#include "QueryDoubleDlg.h"

#include "./DLL_Imaging/h/amremote.h" 
#include "CustomDate.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CQueryDoubleDlg, CDialog)

CQueryDoubleDlg::CQueryDoubleDlg(CWnd* pParent, CString sCognome, CString sNome, CString sDataNascita, CString sSesso, CString sCodiceFiscale)
	: CResizableDialog(CQueryDoubleDlg::IDD, pParent)
{
	//ASSERT(!sCognome.IsEmpty() || !sNome.IsEmpty());

	m_sCognome = sCognome;
	m_sNome = sNome;
	m_sDataNascita = sDataNascita;
	m_sSesso = sSesso;
	m_sCodiceFiscale = sCodiceFiscale;

	m_lOperationToDo = OP_ANNULLA;
	m_lContatoreEndox = 0;
	m_lEsameSelezionato = 0;
}

CQueryDoubleDlg::~CQueryDoubleDlg()
{
}

BEGIN_MESSAGE_MAP(CQueryDoubleDlg, CResizableDialog)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_1, OnLvnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_2, OnLvnItemchangedList2)
	ON_BN_CLICKED(IDC_BTN_NUOVO, &CQueryDoubleDlg::OnBnClickedBtnNuovo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_1, &CQueryDoubleDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_2, &CQueryDoubleDlg::OnNMDblclkList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DETT_1, &CQueryDoubleDlg::OnNMDblclkListDett1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DETT_1, &CQueryDoubleDlg::OnLvnItemchangedListDett1)
END_MESSAGE_MAP()

void CQueryDoubleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST_DETT_1, m_ctrlListDett1);
	DDX_Control(pDX, IDC_LIST_2, m_ctrlList2);
	DDX_Control(pDX, IDC_LIST_DETT_2, m_ctrlListDett2);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);

	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlUndo);

	m_ctrlSave.EnableWindow((m_ctrlList1.GetFirstSelectedItemPosition() != NULL) && (m_ctrlList2.GetFirstSelectedItemPosition() != NULL));
}

BOOL CQueryDoubleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStatic1.SetFont(&theApp.m_fontBig);
	m_ctrlStatic2.SetFont(&theApp.m_fontBig);

	m_ctrlList1.SetExtendedStyle(m_ctrlList1.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList1.InsertColumn(0, "Cognome", LVCFMT_LEFT, 200);
	m_ctrlList1.InsertColumn(1, "Nome", LVCFMT_LEFT, 200);
	m_ctrlList1.InsertColumn(2, "Data di nascita", LVCFMT_CENTER, 100);

	m_ctrlListDett1.SetExtendedStyle(m_ctrlListDett1.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListDett1.InsertColumn(0, "Campo", LVCFMT_LEFT, 200);
	m_ctrlListDett1.InsertColumn(1, "Valore", LVCFMT_LEFT, 200);

	m_ctrlList2.SetExtendedStyle(m_ctrlList2.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList2.InsertColumn(0, "Cognome", LVCFMT_LEFT, 200);
	m_ctrlList2.InsertColumn(1, "Nome", LVCFMT_LEFT, 200);
	m_ctrlList2.InsertColumn(2, "Data di nascita", LVCFMT_CENTER, 100);

	m_ctrlListDett2.SetExtendedStyle(m_ctrlListDett2.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListDett2.InsertColumn(0, "Campo", LVCFMT_LEFT, 200);
	m_ctrlListDett2.InsertColumn(1, "Valore", LVCFMT_LEFT, 200);

	int lElementiInseriti1 = RiempiLista1();
	int lElementiInseriti2 = RiempiLista2();

	if ((lElementiInseriti1 == 0) && (lElementiInseriti2 == 0))
	{
		// paziente non trovato nè in locale nè in provinciale //
		InserisciPazienteNuovo();
	}

	m_ctrlListDett1.DeleteAllItems();
	m_ctrlListDett2.DeleteAllItems();

	theApp.LocalizeDialog(this, CQueryDoubleDlg::IDD, "QueryDoubleDlg");

	AddAnchor(IDC_STATIC_1, CSize(0,0), CSize(100, 0));
	AddAnchor(IDC_LIST_1, CSize(0,0), CSize(50, 50));
	AddAnchor(IDC_LIST_DETT_1, CSize(50,0), CSize(100, 50));

	AddAnchor(IDC_STATIC_2, CSize(0,50), CSize(100, 50));
	AddAnchor(IDC_LIST_2, CSize(0,50), CSize(50, 100));
	AddAnchor(IDC_LIST_DETT_2, CSize(50,50), CSize(100, 100));

	AddAnchor(IDC_BTN_NUOVO, CSize(0,100), CSize(0, 100));
	AddAnchor(IDC_BTN_SAVE, CSize(100,100), CSize(100, 100));
	AddAnchor(IDC_BTN_UNDO, CSize(100,100), CSize(100, 100));

	ShowWindow(SW_MAXIMIZE);
	RedrawWindow();

	return TRUE;
}

void CQueryDoubleDlg::OnBnClickedBtnSave()
{
	if (m_ctrlList1.GetSelectedCount() > 1 || m_ctrlList2.GetSelectedCount() > 1)
	{
		
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_QUERYDOUBLE_ERR1));
		return;
	}

	if (m_ctrlList1.GetSelectedCount() == 1 && m_ctrlList2.GetSelectedCount() == 1)
	{
		//Doppio-invertito messaggio di conferma
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MERGE_QUESTION1), MB_YESNO) == IDNO)
			return;

		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MERGE_QUESTION2), MB_YESNO) == IDYES)
			return;

		m_lOperationToDo = OP_MERGE;
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_QUERYDOUBLE_ERR2));
		return;
	}

	CDialog::OnOK();
}

void CQueryDoubleDlg::OnBnClickedBtnUndo()
{
	CDialog::OnCancel();
}

void CQueryDoubleDlg::InserisciPazienteNuovo()
{
	CString strMessage;
	strMessage.Format(theApp.GetMessageString(IDS_QUERYDOUBLEDLG_MESSAGE1), m_sCognome, m_sNome);
	if (theApp.MessageBoxEndo(strMessage, theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		m_lOperationToDo = OP_INSERISCINUOVO;
		CDialog::OnOK();
	}
}

int CQueryDoubleDlg::RiempiLista1()
{
	BeginWaitCursor();
	m_ctrlList1.SetRedraw(FALSE);

	m_ctrlList1.DeleteAllItems();

	int nIndex = 0;

	CString strFilter;

	if (!m_sCodiceFiscale.IsEmpty())
	{
		if (strFilter == "")
				strFilter.Format("CODFISC LIKE '%s'", m_sCodiceFiscale);
		else
		{
			CString temp;
			temp.Format(" AND CODFISC LIKE '%s'", m_sCodiceFiscale);
			strFilter += temp;
		}
	}
	else
	{
		if (m_sCognome != "")
		{
			if (strFilter == "")
				strFilter.Format("Cognome LIKE '%s%%'", m_sCognome);
			else
			{
				CString temp;
				temp.Format(" AND Cognome LIKE '%s%%'", m_sCognome);
				strFilter += temp;
			}
		}

		if (m_sNome != "")
		{
			if (strFilter == "")
				strFilter.Format("Nome LIKE '%s%%'", m_sNome);
			else
			{
				CString temp;
				temp.Format(" AND Nome LIKE '%s%%'", m_sNome);
				strFilter += temp;
			}
		}

		if (m_sDataNascita != "")
		{
			long lDate = CCustomDate().SetDate(m_sDataNascita.Right(2) + "/" + m_sDataNascita.Mid(4,2) + "/" + m_sDataNascita.Left(4));
			if (strFilter == "")
				strFilter.Format("NatoIlCustom = %li", lDate);
			else
			{
				CString temp;
				temp.Format(" AND NatoIlCustom = %li", lDate);
				strFilter += temp;
			}
		}

		if (m_sSesso != "")
		{
			long iSesso = -1;

			if (m_sSesso == "U")
				iSesso = -1;
			else if (m_sSesso == "M")
				iSesso = 0;
			else if (m_sSesso == "F")
				iSesso = 1;
			else if (m_sSesso == "A")
				iSesso = 2;
			else if (m_sSesso == "N")
				iSesso = 3;
			else if (m_sSesso == "O")
				iSesso = 4;

			if (strFilter == "")
				strFilter.Format("Sesso = %li", iSesso);
			else
			{
				CString temp;
				temp.Format(" AND Sesso = %li", iSesso);
				strFilter += temp;
			}
		}
	}
	

#ifdef _DEBUG
	theApp.AfxMessageBoxEndo(strFilter);
#endif

	CPazientiSet setPazienti;
	setPazienti.SetOpenFilter(strFilter);
	setPazienti.SetSortRecord("Cognome, Nome, NatoIlCustom");
	if (setPazienti.OpenRecordset("CQueryDoubleDlg::RiempiLista1"))
	{
		while(!setPazienti.IsEOF())
		{
			if (setPazienti.m_sAssIden != "")
				m_ctrlList1.InsertItem(nIndex, "* " + setPazienti.m_sCognome);
			else
				m_ctrlList1.InsertItem(nIndex, setPazienti.m_sCognome);

			m_ctrlList1.SetItemData(nIndex, (DWORD)setPazienti.m_lContatore);

			m_ctrlList1.SetItemText(nIndex, 1, setPazienti.m_sNome);

			if (!setPazienti.IsFieldNull(&setPazienti.m_lNatoIlCustom) && (setPazienti.m_lNatoIlCustom > 0))
				m_ctrlList1.SetItemText(nIndex, 2, CCustomDate(setPazienti.m_lNatoIlCustom).GetDate("%d/%m/%Y"));

			nIndex++;
			setPazienti.MoveNext();
		}

		setPazienti.CloseRecordset("CQueryDoubleDlg::RiempiLista1");
	}

	m_ctrlList1.SetRedraw(TRUE);
	RiempiLista1Dettaglio(setPazienti.m_lContatore);
	EndWaitCursor();

	return nIndex;
}

int CQueryDoubleDlg::RiempiLista2()
{
	BeginWaitCursor();
	m_ctrlList2.SetRedraw(FALSE);

	m_ctrlList2.DeleteAllItems();

	int campiSelezionati = 0;

	//E' stata modificata la libreria NHAPI in modo da accettare più di 2 parametri
	/*if (m_sCognome != "")
		campiSelezionati++;
	if (m_sNome != "")
		campiSelezionati++;
	if (m_sDataNascita != "")
		campiSelezionati++;
	if (m_sSesso != "")
		campiSelezionati++;

	//QPD non può avere più di 2 valori di ricerca
	if (campiSelezionati > 2)
	{
		m_ctrlList2.InsertItem(0, "Impossibile effettuare una ricerca sull'anagrafe centrale con più di DUE valori!");
		m_ctrlList2.SetRedraw(TRUE);
		m_ctrlList2.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		EndWaitCursor();

		return 1;
	}*/

	int nIndex = 0;

	CString strFilter;
	CRemotePatientData filterPazienti;

	if (!m_sCodiceFiscale.IsEmpty())
	{
		strFilter.Format("%s", m_sCodiceFiscale);
		strcpy_s(filterPazienti.m_szFiscalCode, strFilter);
	}
	else
	{
		if (m_sCognome != "")
			strFilter.Format("%s%%", m_sCognome);
		else
			strFilter = "";
		strcpy_s(filterPazienti.m_szLastName, strFilter);

		if (m_sNome != "")
			strFilter.Format("%s%%", m_sNome);
		else
			strFilter = "";
		strcpy_s(filterPazienti.m_szFirstName, strFilter);

		if (m_sDataNascita != "")
			strcpy_s(filterPazienti.m_szBornDate, m_sDataNascita);

		if (m_sSesso != "")
			strcpy_s(filterPazienti.m_szSex, m_sSesso);
	}


	// la richiesta è del tipo lista assistiti //
	strcpy_s(filterPazienti.m_szRequestType, "Ricerca");

	CRemotePatientRecordset setPazienti(theApp.m_sTesiAtdNetIndirizzo, theApp.m_nTesiAtdNetPorta);
	setPazienti.SetFilter(&filterPazienti);

	if (setPazienti.Open() == _AMREMOTE_NOERROR)
	{	
		//Controllo se la ricerca mi ha restituito troppi record
		if (!setPazienti.IsEOF())
		{
			if (strcmp(setPazienti.m_szCode, "TN") == 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TOO_MUCH_ROWS));
				return -1;
			}
		}

		while(!setPazienti.IsEOF())
		{
			m_ctrlList2.InsertItem(nIndex, setPazienti.m_szLastName);
			m_ctrlList2.SetItemData(nIndex, (DWORD)nIndex);

			m_ctrlList2.SetItemText(nIndex, 1, setPazienti.m_szFirstName);

			CString sDataNascita = CString(setPazienti.m_szBornDate);
			if (sDataNascita.GetLength() >= 8)
				m_ctrlList2.SetItemText(nIndex, 2, sDataNascita.Mid(6, 2) + "/" + sDataNascita.Mid(4, 2) + "/" + sDataNascita.Left(4));

			// Riempio la lista di pazienti
			PazienteCentrale tempPaziente;
			// tempPaziente.sAsl.Format("%s", setPazientiPavia.m_szAsl);
			tempPaziente.sAssiden.Format("%s", setPazienti.m_szCode);
			tempPaziente.sNome.Format("%s", setPazienti.m_szFirstName);
			tempPaziente.sCognome.Format("%s", setPazienti.m_szLastName);
			tempPaziente.sDataNascita.Format("%s", setPazienti.m_szBornDate);
			tempPaziente.sIstatNascita.Format("%s", setPazienti.m_szBornPlaceCode);
			tempPaziente.sCittaNascita.Format("%s", setPazienti.m_szBornPlace);
			tempPaziente.sIndirizzo.Format("%s", setPazienti.m_szAddress);
			tempPaziente.sIstat.Format("%s", setPazienti.m_szCityCode);
			tempPaziente.sCitta.Format("%s", setPazienti.m_szCity);
			tempPaziente.sCap.Format("%s", setPazienti.m_szZip);
			tempPaziente.sTelefono1.Format("%s", setPazienti.m_szTelephone1);
			tempPaziente.sTelefono2.Format("%s", setPazienti.m_szTelephone2);
			tempPaziente.sCellulare1.Format("%s", setPazienti.m_szMobile1);
			tempPaziente.sCellulare2.Format("%s", setPazienti.m_szMobile2);
			tempPaziente.sEmail.Format("%s", setPazienti.m_szEmail);
			tempPaziente.sSesso.Format("%s", setPazienti.m_szSex);
			tempPaziente.sCodFiscale.Format("%s", setPazienti.m_szFiscalCode);
			// tempPaziente.sCittadinanza.Format("%s", setPazientiPavia.m_szNationality);
			tempPaziente.sCodiceSanitario.Format("%s", setPazienti.m_szSanitaryCode);
			
			m_pazientiCentrale.AddTail(tempPaziente);

			nIndex++;
			setPazienti.MoveNext();
		}

		setPazienti.Close();
	}
	else
	{
		// c'è stato un errore durante la generazione del messaggio HL7 //
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_QUERYDOUBLE_ERR3));
	}

	m_ctrlList2.SetRedraw(TRUE);
	EndWaitCursor();

	return nIndex;
}

void CQueryDoubleDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Qui devo cambiare i dati del paziente nella griglia di dettaglio
	POSITION pos = m_ctrlList1.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlList1.GetNextSelectedItem(pos);
		m_lContatoreEndox = m_ctrlList1.GetItemData(index);
		RiempiLista1Dettaglio(m_ctrlList1.GetItemData(index));
	}
	UpdateData(TRUE);
}

void CQueryDoubleDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList2.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlList2.GetNextSelectedItem(pos);
		RiempiLista2Dettaglio(m_ctrlList2.GetItemData(index));
	}
	UpdateData(TRUE);
}

void CQueryDoubleDlg::OnBnClickedBtnNuovo()
{
	InserisciPazienteNuovo();
}

void CQueryDoubleDlg::RiempiLista1Dettaglio(long contatorePaziente)
{
	m_ctrlListDett1.DeleteAllItems();
	int index = 0;

	CPazientiSet setPazienti;
	CString filter;
	filter.Format("CONTATORE = %li", contatorePaziente);
	setPazienti.SetOpenFilter(filter);
	if (setPazienti.OpenRecordset("CQueryDoubleDlg::RiempiLista1Dettaglio"))
	{
		if (!setPazienti.IsEOF())
		{
			m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_QUERYDOUBLE_FIELD1));
			m_ctrlListDett1.SetItemData(index, 0);
			m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sAssIden);
			m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
			index++;

			if (setPazienti.m_sCognome != "")
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_01));
				m_ctrlListDett1.SetItemData(index, 0);
				m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sCognome);
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

			if (setPazienti.m_sNome != "")
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_02));
				m_ctrlListDett1.SetItemData(index, 0);
				m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sNome);
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

			if (setPazienti.m_lNatoIlCustom > 0)
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_EDT_DATAPAZIENTE));
				m_ctrlListDett1.SetItemData(index, 0);
				if (!setPazienti.IsFieldNull(&setPazienti.m_lNatoIlCustom) && (setPazienti.m_lNatoIlCustom > 0))
					m_ctrlListDett1.SetItemText(index, 1, CCustomDate(setPazienti.m_lNatoIlCustom).GetDate("%d/%m/%Y"));
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

			if (setPazienti.m_sNatoA != "")
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_51));
				m_ctrlListDett1.SetItemData(index, 0);
				m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sNatoA);
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

			if (setPazienti.m_sCodFisc != "")
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_09));
				m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sCodFisc);
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

			if (setPazienti.m_sCitta != "")
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_06));
				m_ctrlListDett1.SetItemData(index, 0);
				m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sCitta);
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

			if (setPazienti.m_sVia != "")
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_04));
				m_ctrlListDett1.SetItemData(index, 0);
				m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sVia);
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

			if (setPazienti.m_sTelefono1 != "")
			{
				m_ctrlListDett1.InsertItem(index, theApp.GetMessageString(IDS_QUERYDOUBLE_FIELD2));
				m_ctrlListDett1.SetItemData(index, 0);
				m_ctrlListDett1.SetItemText(index, 1, setPazienti.m_sTelefono1);
				m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
				index++;
			}

		}

		setPazienti.CloseRecordset("CQueryDoubleDlg::RiempiLista1Dettaglio");
	}

	CEsamiSet tempEsamiSet;
	filter.Format("PAZIENTE = %li", contatorePaziente);
	tempEsamiSet.SetOpenFilter(filter);
	tempEsamiSet.SetSortRecord("DATA DESC");
	if (tempEsamiSet.OpenRecordset("CQueryDoubleDlg::RiempiLista1Dettaglio"))
	{
		if (!tempEsamiSet.IsEOF())
		{
			m_ctrlListDett1.InsertItem(index, "");
			m_ctrlListDett1.SetItemData(index, 0);
			m_ctrlListDett1.SetItemText(index, 1, "");
			m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(192,192,192));
			index++;
		}

		while(!tempEsamiSet.IsEOF())
		{
			m_ctrlListDett1.InsertItem(index, CCustomDate(tempEsamiSet.m_lData).GetDate("%d/%m/%Y"));
			m_ctrlListDett1.SetItemData(index, tempEsamiSet.m_lContatore);
			m_ctrlListDett1.SetItemText(index, 1, CTipoEsameSet().GetDescrizione(tempEsamiSet.m_lIDEsame));
			m_ctrlListDett1.SetSubItemBkColor(index, -1, RGB(255,255,255));
			index++;

			tempEsamiSet.MoveNext();
		}

		tempEsamiSet.CloseRecordset("CQueryDoubleDlg::RiempiLista1Dettaglio");
	}
	

}

void CQueryDoubleDlg::RiempiLista2Dettaglio(long indice)
{
	m_ctrlListDett2.DeleteAllItems();

	POSITION pos = m_pazientiCentrale.FindIndex(indice);

	if (pos)
	{
		m_pazienteCentraleSelezionato = m_pazientiCentrale.GetAt(pos);

		int index = 0;

		m_ctrlListDett2.InsertItem(index, "Id assistito: ");
		m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sAssiden);
		index++;

		if (m_pazienteCentraleSelezionato.sCognome != "")
		{
			m_ctrlListDett2.InsertItem(index, "Cognome: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sCognome);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sNome != "")
		{
			m_ctrlListDett2.InsertItem(index, "Nome: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sNome);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sDataNascita != "")
		{
			m_ctrlListDett2.InsertItem(index, "Nato il: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sDataNascita.Mid(6,2) + "/" + m_pazienteCentraleSelezionato.sDataNascita.Mid(4,2) + "/" + m_pazienteCentraleSelezionato.sDataNascita.Left(4));
			index++;
		}

		if (m_pazienteCentraleSelezionato.sCittaNascita != "")
		{
			m_ctrlListDett2.InsertItem(index, "Nato a: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sCittaNascita);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sCodFiscale != "")
		{
			m_ctrlListDett2.InsertItem(index, "Cod. fiscale: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sCodFiscale);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sCitta != "")
		{
			m_ctrlListDett2.InsertItem(index, "Residente a: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sCitta);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sIndirizzo != "")
		{
			m_ctrlListDett2.InsertItem(index, "Indirizzo: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sIndirizzo);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sTelefono1 != "")
		{
			m_ctrlListDett2.InsertItem(index, "Telefono: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sTelefono1);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sTelefono2 != "")
		{
			m_ctrlListDett2.InsertItem(index, "Telefono: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sTelefono2);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sCellulare1 != "")
		{
			m_ctrlListDett2.InsertItem(index, "Cellulare: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sCellulare1);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sCellulare2 != "")
		{
			m_ctrlListDett2.InsertItem(index, "Cellulare: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sCellulare2);
			index++;
		}

		if (m_pazienteCentraleSelezionato.sEmail != "")
		{
			m_ctrlListDett2.InsertItem(index, "Email: ");
			m_ctrlListDett2.SetItemText(index, 1, m_pazienteCentraleSelezionato.sEmail);
			index++;
		}

	}
}

void CQueryDoubleDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lOperationToDo = OP_SOLOENDOX;

	*pResult = 0;

	CDialog::OnOK();
}

void CQueryDoubleDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lOperationToDo = OP_SOLOCENTRALE;

	*pResult = 0;

	CDialog::OnOK();
}

void CQueryDoubleDlg::OnNMDblclkListDett1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lOperationToDo = OP_SOLOENDOX;

	*pResult = 0;

	if (m_lEsameSelezionato != 0)
		CDialog::OnOK();
}

void CQueryDoubleDlg::OnLvnItemchangedListDett1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	POSITION pos = m_ctrlListDett1.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlList1.GetNextSelectedItem(pos);
		m_lEsameSelezionato = m_ctrlListDett1.GetItemData(index);
	}
	UpdateData(TRUE);

	*pResult = 0;
}
