#include "stdafx.h"
#include "Endox.h"
#include "ListaPrenotazioniCupDettaglioDlg.h"
#include "ExtOrdiniCampiAggiuntiviSet.h"
#include "ExtTransUrgenzaSet.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListaPrenotazioniCupDettaglioDlg::CListaPrenotazioniCupDettaglioDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIdOrdine)
	: CEndoxResizableDlg(CListaPrenotazioniCupDettaglioDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;
	m_lIdOrdine = lIdOrdine;
}

CListaPrenotazioniCupDettaglioDlg::~CListaPrenotazioniCupDettaglioDlg()
{
}

BEGIN_MESSAGE_MAP(CListaPrenotazioniCupDettaglioDlg, CEndoxResizableDlg)
END_MESSAGE_MAP()

void CListaPrenotazioniCupDettaglioDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ORDINE,		m_ctrlListOrdini);
	DDX_Control(pDX, IDC_LIST_PRESTAZIONI,	m_ctrlListPrestazioni);
	DDX_Control(pDX, IDC_STATIC_PRESTAZIONI, m_ctrlStaticPrestazioni);
	DDX_Control(pDX, IDOK,					m_ctrlButtonOK);
}

BOOL CListaPrenotazioniCupDettaglioDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LIST_ORDINE, CSize(0, 0), CSize(30, 100));
	AddAnchor(IDC_LIST_PRESTAZIONI, CSize(30, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_PRESTAZIONI, CSize(30, 0), CSize(30, 0));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));
	
	RiempiDatiOrdine();
	RiempiPrestazioni();

	theApp.LocalizeDialog(this, CListaPrenotazioniCupDettaglioDlg::IDD, "ListaPrenotazioniCupDettaglioDlg");

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	return TRUE;
}

void CListaPrenotazioniCupDettaglioDlg::OnOK() 
{
	CEndoxResizableDlg::OnOK();
}

void CListaPrenotazioniCupDettaglioDlg::RiempiDatiOrdine()
{
	CString strFilter;
	CCupWorkListManager workListSet(m_pEsamiView);
	strFilter.Format("id = %li", m_lIdOrdine);
	workListSet.SetOpenFilter(strFilter);

	m_ctrlListOrdini.InsertColumn(0, "",	LVCFMT_LEFT);
	m_ctrlListOrdini.InsertColumn(1, "Valore pervenuto",		LVCFMT_LEFT);
	m_ctrlListOrdini.InsertColumn(2, "Valore transcodificato",	LVCFMT_LEFT);

	int i = 0;

	if (workListSet.OpenRecordset("CListaPrenotazioniCupDettaglioDlg::RiempiDatiOrdine"))
	{
		if (!workListSet.IsEOF())
		{
			CString temp;

			//
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_DATIORDINE));
			i++;

			//
			m_ctrlListOrdini.InsertItem(i, "");
			i++;

			//Order number
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_NUMEROORDINE));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sOrderNumber);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Data Esame
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_DATAESAME));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sDataEsame.Mid(6,2) + '-' + workListSet.m_sDataEsame.Mid(4,2) + 
										'-' + workListSet.m_sDataEsame.Left(4) + ' ' + workListSet.m_sDataEsame.Mid(8,2) + ':' + workListSet.m_sDataEsame.Mid(10,2));
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Provenienza
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_PROVENIENZA));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sProvenienza);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sDescrizioneProvenienzaNew);
			i++;

			//Agenda
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_SALAESAME));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCodiceAgenda);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sDescrizioneSala);
			i++;

			//Note
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_NOTE));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sNote);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Reparto Inviante
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_REPINVIANTE));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCodiceRepartoInviante + " - " + workListSet.m_sRepartoInviante);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sDescrizioneReparto);
			i++;

			//Medico Inviante
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_MEDINVIANTE));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCodiceMedicoInviante + " - " + workListSet.m_sDescrizioneMedicoInvianteEst);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sMedicoInviante);
			i++;

			//Nosologico
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_NOSOLOGICO));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sNosologico);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Urgenza
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_URGENZA));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sUrgenza);
			temp.Format("%li", CExtTransUrgenzaSet().GetPriorityFromCode(workListSet.m_sUrgenza));
			m_ctrlListOrdini.SetItemText(i, 2, temp);
			i++;

			//
			m_ctrlListOrdini.InsertItem(i, "");
			i++;

			//DATI PAZ
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_DATIPAZIENTE));
			i++;

			//
			m_ctrlListOrdini.InsertItem(i, "");
			i++;

			//Assiden paziente
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_ID));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sAssiden);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Cognome
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_COGNOME));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCognome);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Cognome 2
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_COGNOME2));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCognome2);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Nome
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_NOME));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sNome);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Data Nascita
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_DATANASCITA));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sDataNascita);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Comune Nascita
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_COMUNENASCITA));
			if (!workListSet.IsFieldNull(&workListSet.m_lISTATNascita))
				temp.Format("%li", workListSet.m_lISTATNascita);
			else
				temp = "0";
			m_ctrlListOrdini.SetItemText(i, 1, temp + " - " + workListSet.m_sDescrizioneComuneNascitaEst);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sComuneNascita);
			i++;

			//Indirizzo
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_INDIRIZZO));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sIndirizzoResidenza);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Comune Residenza
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_COMUNERES));
			if (!workListSet.IsFieldNull(&workListSet.m_lISTATResidenza))
				temp.Format("%li", workListSet.m_lISTATResidenza);
			else
				temp = "0";
			m_ctrlListOrdini.SetItemText(i, 1, temp + " - " + workListSet.m_sDescrizioneComuneResidenzaEst);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sComuneResidenza);
			i++;

			//Cap
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_CAP));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCapResidenza);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Telefono 1
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_TELEFONO1));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sTelefono1);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Telefono 2
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_TELEFONO2));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sTelefono2);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Cellullare 1
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_CELLULARE1));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCellulare1);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Cellulare 2
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_CELLULARE2));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCellulare2);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Codice Fiscale
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_CODICEFISCALE));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCodiceFiscale);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Codice Sanitario
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_CODICESANITARIO));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCodiceSanitario);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Sesso
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_SESSO));
			if (workListSet.IsFieldNull(&workListSet.m_lSesso))
				temp = "";
			else
				temp.Format("%li", workListSet.m_lSesso);
			m_ctrlListOrdini.SetItemText(i, 1, temp);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Ulss residenza
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_ASL));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sUlssResidenza);
			m_ctrlListOrdini.SetItemText(i, 2, "-");
			i++;

			//Medico Curante
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_MEDICOCURANTE));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sCodiceMedicoCurante + " - " + workListSet.m_sDescrizioneMedicoCuranteEst);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sMedicoCurante);
			i++;

			//Cittadinanza
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_CITTADINANZA));
			m_ctrlListOrdini.SetItemText(i, 1, workListSet.m_sDescrizioneCittadinanzaEst);
			m_ctrlListOrdini.SetItemText(i, 2, workListSet.m_sCittadinanza);
			i++;

			//
			m_ctrlListOrdini.InsertItem(i, "");
			i++;

			//DATI AGGIUNTIVI
			m_ctrlListOrdini.InsertItem(i, theApp.GetMessageString(IDS_DETTORD_DATIAGGIUNTIVI));
			i++;

			//
			m_ctrlListOrdini.InsertItem(i, "");
			i++;

			CString strFilter;
			strFilter.Format("IDRichiesta=%li", workListSet.m_lId);

			CExtOrdiniCampiAggiuntiviSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CListaPrenotazioniCupDettaglioDlg::RiempiDatiOrdine"))
			{
				while(!setTemp.IsEOF())
				{
					m_ctrlListOrdini.InsertItem(i, setTemp.m_sTabella + "." + setTemp.m_sCampo);
					m_ctrlListOrdini.SetItemText(i, 1, setTemp.m_sValore);
					i++;
					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CListaPrenotazioniCupDettaglioDlg::RiempiDatiOrdine");
			}

		}

		m_ctrlListOrdini.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListOrdini.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListOrdini.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

		workListSet.CloseRecordset("CListaPrenotazioniCupDettaglioDlg::RiempiDatiOrdine");
	}
}

void CListaPrenotazioniCupDettaglioDlg::RiempiPrestazioni()
{
	CString strFilter;
	CVistaExtPrestazioniSet prestazioniSet;
	strFilter.Format("idOrdine = %li", m_lIdOrdine);
	prestazioniSet.SetOpenFilter(strFilter);

	m_ctrlListPrestazioni.InsertColumn(0, "Codice Prestazione",				LVCFMT_LEFT);
	m_ctrlListPrestazioni.InsertColumn(1, "Descrizione Prestazione",		LVCFMT_LEFT);
	m_ctrlListPrestazioni.InsertColumn(2, "Quantita",						LVCFMT_LEFT);
	m_ctrlListPrestazioni.InsertColumn(3, "Note",							LVCFMT_LEFT);
	m_ctrlListPrestazioni.InsertColumn(4, "Descrizione Prestazione Endox",	LVCFMT_LEFT);
	m_ctrlListPrestazioni.InsertColumn(5, "Tipo Esame Generato",			LVCFMT_LEFT);

	if (prestazioniSet.OpenRecordset("CListaPrenotazioniCupDettaglioDlg::RiempiPrestazioni"))
	{
		int i = 0;

		while(!prestazioniSet.IsEOF())
		{
			m_ctrlListPrestazioni.InsertItem(i, prestazioniSet.m_sCodicePrestazione);
			m_ctrlListPrestazioni.SetItemText(i, 1, prestazioniSet.m_sDescrizionePrestazione);
			CString temp;
			temp.Format("%li", prestazioniSet.m_lQuantita);
			m_ctrlListPrestazioni.SetItemText(i, 2, temp);
			m_ctrlListPrestazioni.SetItemText(i, 3, prestazioniSet.m_sNote);
			m_ctrlListPrestazioni.SetItemText(i, 4, prestazioniSet.m_sDescrizioneEndox);
			m_ctrlListPrestazioni.SetItemText(i, 5, prestazioniSet.m_sTipoEsame);

			i++;
			prestazioniSet.MoveNext();
		}

		m_ctrlListPrestazioni.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPrestazioni.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPrestazioni.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPrestazioni.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPrestazioni.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPrestazioni.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);

		prestazioniSet.CloseRecordset("CListaPrenotazioniCupDettaglioDlg::RiempiPrestazioni");
	}
}