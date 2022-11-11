#include "stdafx.h"
#include "Endox.h"
#include "ConiugazioneEsamiDlg.h"

#include "DLL_Imaging\h\AmLogin.h"

#include "CupWorkListManager.h"
#include "CustomDate.h"
#include "DiagnosiEsamiSet.h"
#include "DiagnosiICD9Set.h"
#include "DocManager.h"
#include "EsamiAccettatiSet.h"
#include "EsamiView.h"
#include "ExtMinPazDataSetSet.h"
#include "ExtOrdiniAllegatiSet.h"
#include "ExtOrdiniCampiAggiuntiviSet.h"
#include "ExtOrdiniDiagnosiICD9Set.h"
#include "ExtOrdiniOperatoriSet.h"
#include "ExtOrdiniProcedureICD9Set.h"
#include "ExtOrdiniSet.h"
#include "ExtTransUrgenzaSet.h"
#include "ListaPrenotazioniCupDlg.h"
#include "MediciSet.h"
#include "ProcedureEsamiSet.h"
#include "ProcedureICD9Set.h"
#include "RegioneSet.h"
#include "TipoEsameNew.h"
#include "VistaExtPrestazioniSet.h"
#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CConiugazioneEsamiDlg, CDialog)

CConiugazioneEsamiDlg::CConiugazioneEsamiDlg(CWnd* pParent, CEsamiView* pEsamiView, CList<STRUCT_FICHA_ITEM> *pListFichaItem, CString sActUO, CString sActFichaItem)
	: CDialog(CConiugazioneEsamiDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_pListFichaItem = pListFichaItem;
	m_sActUO = sActUO;
	m_sActFichaItem = sActFichaItem;
}

CConiugazioneEsamiDlg::~CConiugazioneEsamiDlg()
{	
	delete m_ctrlList;
}

BEGIN_MESSAGE_MAP(CConiugazioneEsamiDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_ESCI, OnBnClickedBtnEsci)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)

END_MESSAGE_MAP()

void CConiugazioneEsamiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_ESCI, m_ctrlBtnEsci);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

void CConiugazioneEsamiDlg::OnCancel()
{
}

BOOL CConiugazioneEsamiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_FICHAITEM));
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_CODICE));
	m_ctrlList.InsertColumn(2, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlList.InsertColumn(3, "");

	int nIndex = 0;
	POSITION pos = m_pListFichaItem->GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_FICHA_ITEM structFichaItemTemp = m_pListFichaItem->GetAt(pos);
		m_ctrlList.InsertItem(nIndex, structFichaItemTemp.szFichaItem);
		m_ctrlList.SetItemText(nIndex, 1, structFichaItemTemp.szCodice);
		m_ctrlList.SetItemText(nIndex, 2, structFichaItemTemp.szDescrizione);

		nIndex++;
		m_pListFichaItem->GetNext(pos);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(3, 0);

	//

	theApp.LocalizeDialog(this, CConiugazioneEsamiDlg::IDD, "ConiugazioneEsamiDlg");
	return TRUE;
}

void CConiugazioneEsamiDlg::OnOK()
{
}

void CConiugazioneEsamiDlg::OnBnClickedBtnEsci()
{
	CDialog::OnCancel();
}

void CConiugazioneEsamiDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Julio BUG 6385
	if (!FleuryIsUserADoctor())
		OnBnClickedBtnEsci();

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem >= 0)
	{
		CString sMessage;
		sMessage.Format(theApp.GetMessageString(IDS_CONIUGAZIONE_ESAMI_CONFERMA), m_ctrlList.GetItemText(pNMItemActivate->iItem, 1), m_ctrlList.GetItemText(pNMItemActivate->iItem, 0));

		if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO) == IDYES)
		{
			if (m_sActUO.CompareNoCase(m_ctrlList.GetItemText(pNMItemActivate->iItem, 1)) == 0)
			{
				///////////////
				// STESSA UO //
				///////////////

				long lIDPaziente = m_pEsamiView->m_pEsamiSet->m_lPaziente;
				long lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
				CString sSecondFichaItem = m_ctrlList.GetItemText(pNMItemActivate->iItem, 0);

				// se serve tiro dentro dalla worklist l'altro esame //

				long lIDExtOrdini = 0;
				long lIDEsameIns = 0;
				CExtOrdiniSet().GetDataFromFichaItem(sSecondFichaItem, lIDExtOrdini, lIDEsameIns);
				if ((lIDExtOrdini > 0) && (lIDEsameIns <= 0))
					SelectEntry(lIDExtOrdini, lIDPaziente);

				// flaggo entrambi gli esami come coniugati tra di loro //

				CEsamiSet().SetConiugatoPrincipaleSecondario(m_sActFichaItem, sSecondFichaItem, FALSE);

				// mi riposiziono sull'esame principale //

				BOOL bOK = m_pEsamiView->RicercaCodicePaziente(lIDPaziente, lIDEsame, FALSE, TRUE);
				m_pEsamiView->MovePazientiAndEsami(NULL, !bOK, TRUE);
			}
			else
			{
				///////////////////
				// UO differente //
				///////////////////

				long lIDPaziente = m_pEsamiView->m_pEsamiSet->m_lPaziente;
				long lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
				CString sFirstFichaItem = m_ctrlList.GetItemText(pNMItemActivate->iItem, 0);

				// se serve tiro dentro dalla worklist l'altro esame //

				long lIDExtOrdini = 0;
				long lIDEsameIns = 0;
				CExtOrdiniSet().GetDataFromFichaItem(sFirstFichaItem, lIDExtOrdini, lIDEsameIns);
				if ((lIDExtOrdini > 0) && (lIDEsameIns <= 0))
					SelectEntry(lIDExtOrdini, lIDPaziente);

				// flaggo entrambi gli esami come coniugati tra di loro //

				CEsamiSet().SetConiugatoPrincipaleSecondario(sFirstFichaItem, m_sActFichaItem, TRUE);

				// mi riposiziono sull'esame attuale //

				BOOL bOK = m_pEsamiView->RicercaCodicePaziente(lIDPaziente, lIDEsame, FALSE, TRUE);
				m_pEsamiView->MovePazientiAndEsami(NULL, !bOK, TRUE);
			}
		}

		CDialog::OnOK();
	}

	*pResult = 0;
}

void CConiugazioneEsamiDlg::SelectEntry(long lIDExtOrdini, long lIDPaziente)
{
	CString sFilter;
	sFilter.Format("ID=%li", lIDExtOrdini);

	CExtOrdiniSet setExtOrdini;
	setExtOrdini.SetBaseFilter("(UO='' OR UO<>'')");
	setExtOrdini.SetOpenFilter(sFilter);
	if (setExtOrdini.OpenRecordset("CConiugazioneEsamiDlg::SelectEntry"))
	{
		if (!setExtOrdini.IsEOF())
		{
			if (SelectEntryFasePreliminare(&setExtOrdini))
			{
				SelectEntryFaseImportazioneEsame(lIDExtOrdini, lIDPaziente, &setExtOrdini, CUOSet().GetUOFromCodiceIntegrazione(setExtOrdini.m_sUO));

				/* if (setExtOrdini.EditRecordset("CConiugazioneEsamiDlg::SelectEntry"))
				{
					setExtOrdini.m_bImporting = FALSE;
					setExtOrdini.UpdateRecordset("CConiugazioneEsamiDlg::SelectEntry");
				} */
			}
		}
		setExtOrdini.CloseRecordset("CConiugazioneEsamiDlg::SelectEntry");
	}
}

BOOL CConiugazioneEsamiDlg::SelectEntryFasePreliminare(CExtOrdiniSet* pSetExtOrdini)
{
	BOOL bReturn = FALSE;

	if (pSetExtOrdini->m_bTrasferito) // || pSetExtOrdini->m_bImporting)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_WL_TRASFERITO));
	}
	else
	{
		/* if (pSetExtOrdini->EditRecordset("CConiugazioneEsamiDlg::SelectEntryFasePreliminare"))
		{
			pSetExtOrdini->m_bImporting = TRUE;
			bReturn = pSetExtOrdini->UpdateRecordset("CConiugazioneEsamiDlg::SelectEntryFasePreliminare");
		} */

		bReturn = TRUE;
	}

	return bReturn;
}

/*
long CConiugazioneEsamiDlg::SelectEntryFaseImportazionePaziente(CString sAssIden)
{
	long lReturn = 0;

	CString sFilter = "";
	sFilter.Format("ASSIDEN='%s'", sAssIden);

	CPazientiSet setPazienti;
	setPazienti.SetOpenFilter(sFilter);
	if (setPazienti.OpenRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazionePaziente"))
	{
		if (!setPazienti.IsEOF())
			lReturn = setPazienti.m_lContatore;

		setPazienti.CloseRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazionePaziente");
	}

	return lReturn;
}
*/

void CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame(long lIDExtOrdini, long lIDPaziente, CExtOrdiniSet* pSetExtOrdini, long lUO)
{
	long lIDTipoEsame = 0;

	CString sFilter;
	sFilter.Format("IDORDINE=%li AND TIPOESAME IS NOT NULL", lIDExtOrdini);

	CString sTesto094 = "";
	CString sTesto095 = "";

	CVistaExtPrestazioniSet setVistaExtPrestazioni;
	setVistaExtPrestazioni.SetBaseFilter("(UO=0 OR UO>0)");
	setVistaExtPrestazioni.SetOpenFilter(sFilter);
	if (setVistaExtPrestazioni.OpenRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame"))
	{
		if (!setVistaExtPrestazioni.IsEOF())
		{
			lIDTipoEsame = setVistaExtPrestazioni.m_lIdTipoEsameEndox;
			sTesto094 = setVistaExtPrestazioni.m_sCodicePrestazione;
			sTesto095 = setVistaExtPrestazioni.m_sDescrizionePrestazione;
		}

		setVistaExtPrestazioni.CloseRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame");
	}

	if (lIDTipoEsame <= 0)
	{
		CTipoEsameNewDlg dlg(this, m_pEsamiView, FALSE, FALSE, lUO);
		dlg.DoModal();
		lIDTipoEsame = dlg.GetTipoEsame();
	}

	//

	CEsamiSet setEsami;
	setEsami.SetOpenFilter("Contatore=0");
	if (setEsami.OpenRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame"))
	{
		if (setEsami.AddNewRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame"))
		{
			///////////////////////
			// OnEsameNewAutoCup //
			///////////////////////

			setEsami.m_lPaziente = lIDPaziente;

			setEsami.m_lData = CCustomDate(TRUE, TRUE).GetDate();

			setEsami.m_lIDEsame = lIDTipoEsame;
			setEsami.m_lIDVersione = GetIDVersione(lIDTipoEsame);

			setEsami.m_lVersioneGridCL = theApp.m_lLastGridCLVersion;

			setEsami.m_lIDSedeEsame = theApp.m_lIDSedeEsameDefault;
			setEsami.m_sSalaEsame = theApp.m_sSalaEsameDefault;
			setEsami.m_sSalaEsame.MakeUpper();

			setEsami.m_lProvenienza = theApp.m_bPazienteInternoDefault ? 0 : 1;

			if (theApp.m_bPazienteInternoDefault == FALSE)
				setEsami.m_lProvenienza = ESTERNO;

			AMLogin_GetUserID(&setEsami.m_lIDUtenteInserimentoEsame);

			if (theApp.m_bUsaUtenteLoggatoComeMedicoDefault)
			{
				int lIDMedico = CMediciSet().GetContatoreFromUserID(setEsami.m_lIDUtenteInserimentoEsame);
				if (lIDMedico > 0)
					setEsami.m_lMedico = lIDMedico;
			}

			//////////////////////
			// OnEsameUpdateCup //
			//////////////////////

			// PROGRESSIVOANNO //
			setEsami.m_sProgressivoAnno = GetContatoreAnnuale(setEsami.m_lIDEsame);

			// CODICEPRENOTAZIONE //
			setEsami.m_sCodicePrenotazione = GetCodicePrenotazione(setEsami.m_lIDEsame);

			//

			setEsami.m_sCodEsame = pSetExtOrdini->m_sOrderNumber;

			setEsami.m_sRicovero = pSetExtOrdini->m_sNosologico;

			if (!pSetExtOrdini->IsFieldNull(&pSetExtOrdini->m_sMedicoInviante) && pSetExtOrdini->m_sMedicoInviante.Trim() != "")
				setEsami.m_sInvMedico = pSetExtOrdini->m_sMedicoInviante;
			
			//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
			if (!pSetExtOrdini->IsFieldNull(&pSetExtOrdini->m_sMedicoInviante2) && pSetExtOrdini->m_sMedicoInviante2.Trim() != "")
			setEsami.m_sInvMedico2 = pSetExtOrdini->m_sMedicoInviante2;

			if (!pSetExtOrdini->IsFieldNull(&pSetExtOrdini->m_sMedicoInviante3) && pSetExtOrdini->m_sMedicoInviante3.Trim() != "")
			setEsami.m_sInvMedico3 = pSetExtOrdini->m_sMedicoInviante3;

			if (!pSetExtOrdini->IsFieldNull(&pSetExtOrdini->m_sMedicoInviante4) && pSetExtOrdini->m_sMedicoInviante4.Trim() != "")
			setEsami.m_sInvMedico4 = pSetExtOrdini->m_sMedicoInviante4; 

			if (!pSetExtOrdini->IsFieldNull(&pSetExtOrdini->m_sNote) && pSetExtOrdini->m_sNote.Trim() != "")
				setEsami.m_sAppunti = pSetExtOrdini->m_sNote;

			if (theApp.m_sSalaEsameDefault.Trim().GetLength() > 0)
				setEsami.m_sSalaEsame = theApp.m_sSalaEsameDefault.Trim();

			setEsami.m_lLivelloUrgenza = CExtTransUrgenzaSet().GetPriorityFromCode(pSetExtOrdini->m_sUrgenza);

			setEsami.m_sQuesitoDiagnostico = pSetExtOrdini->m_sQuesitoDiagnostico;

			// Sandro 15/11/2016 //

			if (theApp.m_bPersonalizzazioniBrasileFleury)
			{
				setEsami.m_setEP.m_sTesto094 = sTesto094;
				setEsami.m_setEP.m_sTesto095 = sTesto095;
			}

			//

			CString strFilt;
			strFilt.Format("IDRICHIESTA=%li", lIDExtOrdini);

			CExtOrdiniOperatoriSet setExtOrdiniOperatori;
			setExtOrdiniOperatori.SetOpenFilter(strFilt);
			if (setExtOrdiniOperatori.OpenRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame"))
			{
				while (!setExtOrdiniOperatori.IsEOF())
				{
					long idOperatore = CMediciSet().GetContatoreFromCodice(setExtOrdiniOperatori.m_sCodice);
					if (idOperatore > 0)
					{
						if (setEsami.IsFieldNull(&setEsami.m_lMedico) || setEsami.m_lMedico <= 0)
							setEsami.m_lMedico = idOperatore;
						else if (setEsami.IsFieldNull(&setEsami.m_lAssistente) || setEsami.m_lAssistente <= 0)
							setEsami.m_lAssistente = idOperatore;
					}

					setExtOrdiniOperatori.MoveNext();
				}

				setExtOrdiniOperatori.CloseRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame");
			}

			////////////////////////////
			// UpdateDataFromWorklist //
			////////////////////////////

			UpdateDataFromWorklist(lIDExtOrdini, lIDPaziente, &setEsami);

			//

			if (setEsami.UpdateRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame"))
			{
				UpdateDatiEsame(lIDPaziente, setEsami.GetLastAdd(), lIDExtOrdini, pSetExtOrdini, lUO);
				UpdateWithExamID(setEsami.GetLastAdd(), pSetExtOrdini);
			}
		}

		setEsami.CloseRecordset("CConiugazioneEsamiDlg::SelectEntryFaseImportazioneEsame");
	}
}

BOOL CConiugazioneEsamiDlg::CampiObbligatoriValorizzati(long lIDExtOrdini)
{
	BOOL bReturn = TRUE;

	CString sFilter;
	if (lIDExtOrdini < 0)
		sFilter.Format("ID=%li", -lIDExtOrdini);
	else
		sFilter.Format("ID=%li", lIDExtOrdini);

	CExtOrdiniSet setExtOrdini;
	setExtOrdini.SetOpenFilter(sFilter);
	if (setExtOrdini.OpenRecordset("CConiugazioneEsamiDlg::CampiObbligatoriValorizzati"))
	{
		if (!setExtOrdini.IsEOF())
		{
			// controllo se i campi obbligatori sono valorizzati //

			CExtMinPazDataSetSet minPazDataSetSet;
			if (minPazDataSetSet.OpenRecordset("CConiugazioneEsamiDlg::CampiObbligatoriValorizzati"))
			{
				if (!minPazDataSetSet.IsEOF())
				{
					if (minPazDataSetSet.m_bCognome && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sCognome) || setExtOrdini.m_sCognome == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bCognome2 && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sCognome2) || setExtOrdini.m_sCognome2 == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bNome && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sNome) || setExtOrdini.m_sNome == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bDataNascita && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sDataNascita) || setExtOrdini.m_sDataNascita == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bIstatNascita && (setExtOrdini.IsFieldNull(&setExtOrdini.m_lIstatNascita) || setExtOrdini.m_lIstatNascita == 0))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bIndirizzoResidenza && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sIndirizzoResidenza) || setExtOrdini.m_sIndirizzoResidenza == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bIstatResidenza && (setExtOrdini.IsFieldNull(&setExtOrdini.m_lIstatResidenza) || setExtOrdini.m_lIstatResidenza == 0))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bCapResidenza && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sCapResidenza) || setExtOrdini.m_sCapResidenza == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bTelefono1 && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sTelefono1) || setExtOrdini.m_sTelefono1 == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bTelefono2 && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sTelefono2) || setExtOrdini.m_sTelefono2 == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bCellulare1 && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sCellulare1) || setExtOrdini.m_sCellulare1 == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bCellulare2 && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sCellulare2) || setExtOrdini.m_sCellulare2 == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bCodiceFiscale && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sCodiceFiscale) || setExtOrdini.m_sCodiceFiscale == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bCodiceSanitario && (setExtOrdini.IsFieldNull(&setExtOrdini.m_sCodiceSanitario) || setExtOrdini.m_sCodiceSanitario == ""))
						bReturn = FALSE;
					if (minPazDataSetSet.m_bSesso && (setExtOrdini.IsFieldNull(&setExtOrdini.m_lSesso)))
						bReturn = FALSE;
				}

				minPazDataSetSet.CloseRecordset("CConiugazioneEsamiDlg::CampiObbligatoriValorizzati");
			}
		}

		setExtOrdini.CloseRecordset("CConiugazioneEsamiDlg::CampiObbligatoriValorizzati");
	}

	return bReturn;
}

void CConiugazioneEsamiDlg::UpdateDataFromWorklist(long lIDExtOrdini, long lIDPaziente, CEsamiSet* pEsamiSet)
{
	CString strFilter;
	strFilter.Format("IDRichiesta=%li", lIDExtOrdini);

	CExtOrdiniCampiAggiuntiviSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CEsamiView::EsameNew"))
	{
		while (!setTemp.IsEOF())
		{
			setTemp.m_sTabella.MakeUpper();
			setTemp.m_sCampo.MakeUpper();

			if (setTemp.m_sTabella == "EESAMIPERSONALIZZABILI")
			{
				if (setTemp.m_sCampo == "TESTO000")
					pEsamiSet->m_setEP.m_sTesto000 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO001")
					pEsamiSet->m_setEP.m_sTesto001 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO002")
					pEsamiSet->m_setEP.m_sTesto002 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO003")
					pEsamiSet->m_setEP.m_sTesto003 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO004")
					pEsamiSet->m_setEP.m_sTesto004 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO005")
					pEsamiSet->m_setEP.m_sTesto005 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO006")
					pEsamiSet->m_setEP.m_sTesto006 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO007")
					pEsamiSet->m_setEP.m_sTesto007 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO008")
					pEsamiSet->m_setEP.m_sTesto008 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO009")
					pEsamiSet->m_setEP.m_sTesto009 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO010")
					pEsamiSet->m_setEP.m_sTesto010 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO011")
					pEsamiSet->m_setEP.m_sTesto011 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO012")
					pEsamiSet->m_setEP.m_sTesto012 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO013")
					pEsamiSet->m_setEP.m_sTesto013 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO014")
					pEsamiSet->m_setEP.m_sTesto014 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO015")
					pEsamiSet->m_setEP.m_sTesto015 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO016")
					pEsamiSet->m_setEP.m_sTesto016 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO017")
					pEsamiSet->m_setEP.m_sTesto017 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO018")
					pEsamiSet->m_setEP.m_sTesto018 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO019")
					pEsamiSet->m_setEP.m_sTesto019 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO020")
					pEsamiSet->m_setEP.m_sTesto020 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO021")
					pEsamiSet->m_setEP.m_sTesto021 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO022")
					pEsamiSet->m_setEP.m_sTesto022 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO023")
					pEsamiSet->m_setEP.m_sTesto023 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO024")
					pEsamiSet->m_setEP.m_sTesto024 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO025")
					pEsamiSet->m_setEP.m_sTesto025 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO026")
					pEsamiSet->m_setEP.m_sTesto026 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO027")
					pEsamiSet->m_setEP.m_sTesto027 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO028")
					pEsamiSet->m_setEP.m_sTesto028 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO029")
					pEsamiSet->m_setEP.m_sTesto029 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO030")
					pEsamiSet->m_setEP.m_sTesto030 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO031")
					pEsamiSet->m_setEP.m_sTesto031 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO032")
					pEsamiSet->m_setEP.m_sTesto032 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO033")
					pEsamiSet->m_setEP.m_sTesto033 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO034")
					pEsamiSet->m_setEP.m_sTesto034 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO035")
					pEsamiSet->m_setEP.m_sTesto035 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO036")
					pEsamiSet->m_setEP.m_sTesto036 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO037")
					pEsamiSet->m_setEP.m_sTesto037 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO038")
					pEsamiSet->m_setEP.m_sTesto038 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO039")
					pEsamiSet->m_setEP.m_sTesto039 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO040")
					pEsamiSet->m_setEP.m_sTesto040 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO041")
					pEsamiSet->m_setEP.m_sTesto041 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO042")
					pEsamiSet->m_setEP.m_sTesto042 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO043")
					pEsamiSet->m_setEP.m_sTesto043 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO044")
					pEsamiSet->m_setEP.m_sTesto044 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO045")
					pEsamiSet->m_setEP.m_sTesto045 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO046")
					pEsamiSet->m_setEP.m_sTesto046 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO047")
					pEsamiSet->m_setEP.m_sTesto047 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO048")
					pEsamiSet->m_setEP.m_sTesto048 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO049")
					pEsamiSet->m_setEP.m_sTesto049 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO050")
					pEsamiSet->m_setEP.m_sTesto050 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO051")
					pEsamiSet->m_setEP.m_sTesto051 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO052")
					pEsamiSet->m_setEP.m_sTesto052 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO053")
					pEsamiSet->m_setEP.m_sTesto053 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO054")
					pEsamiSet->m_setEP.m_sTesto054 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO055")
					pEsamiSet->m_setEP.m_sTesto055 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO056")
					pEsamiSet->m_setEP.m_sTesto056 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO057")
					pEsamiSet->m_setEP.m_sTesto057 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO058")
					pEsamiSet->m_setEP.m_sTesto058 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO059")
					pEsamiSet->m_setEP.m_sTesto059 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO060")
					pEsamiSet->m_setEP.m_sTesto060 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO061")
					pEsamiSet->m_setEP.m_sTesto061 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO062")
					pEsamiSet->m_setEP.m_sTesto062 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO063")
					pEsamiSet->m_setEP.m_sTesto063 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO064")
					pEsamiSet->m_setEP.m_sTesto064 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO065")
					pEsamiSet->m_setEP.m_sTesto065 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO066")
					pEsamiSet->m_setEP.m_sTesto066 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO067")
					pEsamiSet->m_setEP.m_sTesto067 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO068")
					pEsamiSet->m_setEP.m_sTesto068 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO069")
					pEsamiSet->m_setEP.m_sTesto069 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO070")
					pEsamiSet->m_setEP.m_sTesto070 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO071")
					pEsamiSet->m_setEP.m_sTesto071 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO072")
					pEsamiSet->m_setEP.m_sTesto072 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO073")
					pEsamiSet->m_setEP.m_sTesto073 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO074")
					pEsamiSet->m_setEP.m_sTesto074 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO075")
					pEsamiSet->m_setEP.m_sTesto075 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO076")
					pEsamiSet->m_setEP.m_sTesto076 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO077")
					pEsamiSet->m_setEP.m_sTesto077 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO078")
					pEsamiSet->m_setEP.m_sTesto078 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO079")
					pEsamiSet->m_setEP.m_sTesto079 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO080")
					pEsamiSet->m_setEP.m_sTesto080 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO081")
					pEsamiSet->m_setEP.m_sTesto081 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO082")
					pEsamiSet->m_setEP.m_sTesto082 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO083")
					pEsamiSet->m_setEP.m_sTesto083 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO084")
					pEsamiSet->m_setEP.m_sTesto084 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO085")
					pEsamiSet->m_setEP.m_sTesto085 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO086")
					pEsamiSet->m_setEP.m_sTesto086 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO087")
					pEsamiSet->m_setEP.m_sTesto087 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO088")
					pEsamiSet->m_setEP.m_sTesto088 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO089")
					pEsamiSet->m_setEP.m_sTesto089 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO090")
					pEsamiSet->m_setEP.m_sTesto090 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO091")
					pEsamiSet->m_setEP.m_sTesto091 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO092")
					pEsamiSet->m_setEP.m_sTesto092 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO093")
					pEsamiSet->m_setEP.m_sTesto093 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO094")
					pEsamiSet->m_setEP.m_sTesto094 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO095")
					pEsamiSet->m_setEP.m_sTesto095 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO096")
					pEsamiSet->m_setEP.m_sTesto096 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO097")
					pEsamiSet->m_setEP.m_sTesto097 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO098")
					pEsamiSet->m_setEP.m_sTesto098 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO099")
					pEsamiSet->m_setEP.m_sTesto099 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTORTF000")
					pEsamiSet->m_setEP.m_sTestoRtf000 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT000")
				{
					pEsamiSet->m_setEP.m_sTestoTxt000 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf000);
				}
				if (setTemp.m_sCampo == "TESTORTF001")
					pEsamiSet->m_setEP.m_sTestoRtf001 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT001")
				{
					pEsamiSet->m_setEP.m_sTestoTxt001 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf001);
				}
				if (setTemp.m_sCampo == "TESTORTF002")
					pEsamiSet->m_setEP.m_sTestoRtf002 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT002")
				{
					pEsamiSet->m_setEP.m_sTestoTxt002 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf002);
				}
				if (setTemp.m_sCampo == "TESTORTF003")
					pEsamiSet->m_setEP.m_sTestoRtf003 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT003")
				{
					pEsamiSet->m_setEP.m_sTestoTxt003 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf003);
				}
				if (setTemp.m_sCampo == "TESTORTF004")
					pEsamiSet->m_setEP.m_sTestoRtf004 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT004")
				{
					pEsamiSet->m_setEP.m_sTestoTxt004 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf004);
				}
				if (setTemp.m_sCampo == "TESTORTF005")
					pEsamiSet->m_setEP.m_sTestoRtf005 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT005")
				{
					pEsamiSet->m_setEP.m_sTestoTxt005 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf005);
				}
				if (setTemp.m_sCampo == "TESTORTF006")
					pEsamiSet->m_setEP.m_sTestoRtf006 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT006")
				{
					pEsamiSet->m_setEP.m_sTestoTxt006 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf006);
				}
				if (setTemp.m_sCampo == "TESTORTF007")
					pEsamiSet->m_setEP.m_sTestoRtf007 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT007")
				{
					pEsamiSet->m_setEP.m_sTestoTxt007 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf007);
				}
				if (setTemp.m_sCampo == "TESTORTF008")
					pEsamiSet->m_setEP.m_sTestoRtf008 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT008")
				{
					pEsamiSet->m_setEP.m_sTestoTxt008 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf008);
				}
				if (setTemp.m_sCampo == "TESTORTF009")
					pEsamiSet->m_setEP.m_sTestoRtf009 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT009")
				{
					pEsamiSet->m_setEP.m_sTestoTxt009 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf009);
				}
				if (setTemp.m_sCampo == "TESTORTF010")
					pEsamiSet->m_setEP.m_sTestoRtf009 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT010")
				{
					pEsamiSet->m_setEP.m_sTestoTxt010 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf010);
				}
				if (setTemp.m_sCampo == "TESTORTF011")
					pEsamiSet->m_setEP.m_sTestoRtf010 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT011")
				{
					pEsamiSet->m_setEP.m_sTestoTxt011 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf011);
				}
				if (setTemp.m_sCampo == "TESTORTF012")
					pEsamiSet->m_setEP.m_sTestoRtf011 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT012")
				{
					pEsamiSet->m_setEP.m_sTestoTxt012 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf012);
				}
				if (setTemp.m_sCampo == "TESTORTF013")
					pEsamiSet->m_setEP.m_sTestoRtf012 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT013")
				{
					pEsamiSet->m_setEP.m_sTestoTxt013 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf013);
				}
				if (setTemp.m_sCampo == "TESTORTF014")
					pEsamiSet->m_setEP.m_sTestoRtf013 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT014")
				{
					pEsamiSet->m_setEP.m_sTestoTxt014 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf014);
				}
				if (setTemp.m_sCampo == "TESTORTF015")
					pEsamiSet->m_setEP.m_sTestoRtf015 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT015")
				{
					pEsamiSet->m_setEP.m_sTestoTxt015 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf015);
				}
				if (setTemp.m_sCampo == "TESTORTF016")
					pEsamiSet->m_setEP.m_sTestoRtf016 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT016")
				{
					pEsamiSet->m_setEP.m_sTestoTxt016 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf016);
				}
				if (setTemp.m_sCampo == "TESTORTF017")
					pEsamiSet->m_setEP.m_sTestoRtf017 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT017")
				{
					pEsamiSet->m_setEP.m_sTestoTxt017 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf017);
				}
				if (setTemp.m_sCampo == "TESTORTF018")
					pEsamiSet->m_setEP.m_sTestoRtf018 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT018")
				{
					pEsamiSet->m_setEP.m_sTestoTxt018 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf018);
				}
				if (setTemp.m_sCampo == "TESTORTF019")
					pEsamiSet->m_setEP.m_sTestoRtf019 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT019")
				{
					pEsamiSet->m_setEP.m_sTestoTxt019 = setTemp.m_sValore;
					pEsamiSet->m_setEP.SetFieldNull(&pEsamiSet->m_setEP.m_sTestoRtf019);
				}
			}

			if (setTemp.m_sTabella == "EPAZIENTI")
			{
				CPazientiSet pazientiSet;
				CString filter;
				filter.Format("CONTATORE=%li", lIDPaziente);
				pazientiSet.SetOpenFilter(filter);
				if (pazientiSet.OpenRecordset("CEsamiView::EsameNew"))
				{
					if (pazientiSet.EditRecordset("CEsamiView::EsameNew"))
					{
						if (setTemp.m_sCampo == "MEDICOTEL")
							pazientiSet.m_sMedicoTel = setTemp.m_sValore;
						if (setTemp.m_sCampo == "CODICECLIENTE")
							pazientiSet.m_sCodiceCliente = setTemp.m_sValore;
						if (setTemp.m_sCampo == "ULSSRESIDENZA")
							pazientiSet.m_sUlssResidenza = setTemp.m_sValore;

						pazientiSet.UpdateRecordset("CEsamiView::EsameNew");
					}

					pazientiSet.CloseRecordset("CEsamiView::EsameNew");
				}
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CEsamiView::EsameNew");
	}
}

void CConiugazioneEsamiDlg::UpdateDatiEsame(long lIDPaziente, long lIDEsame, long lIDExtOrdini, CExtOrdiniSet* pSetExtOrdini, long lUO)
{
	CString strFilter;

	//

	strFilter.Format("CONTATORE=%li", lIDEsame);
	CEsamiSet setEsamiTemp;
	setEsamiTemp.SetBaseFilter("(UO=0 OR UO>0)");
	setEsamiTemp.SetOpenFilter(strFilter);
	if (setEsamiTemp.OpenRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame"))
	{
		if (!setEsamiTemp.IsEOF())
		{
			if (setEsamiTemp.EditRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame"))
			{
				setEsamiTemp.m_lUO = lUO;
				setEsamiTemp.UpdateRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame");
			}
		}

		setEsamiTemp.CloseRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame");
	}

	//

	CString sBaseFilter;
	CString sOpenFilter;

	sBaseFilter.Format("UO=%li", lUO);
	sOpenFilter.Format("IDORDINE=%li", lIDExtOrdini);

	CVistaExtPrestazioniSet extPrestazioniSet;
	extPrestazioniSet.SetBaseFilter(sBaseFilter);
	extPrestazioniSet.SetOpenFilter(sOpenFilter);
	if (extPrestazioniSet.OpenRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame"))
	{
		while (!extPrestazioniSet.IsEOF())
		{
			if (!extPrestazioniSet.IsFieldNull(&extPrestazioniSet.m_lIdPrestazioneEndox) && extPrestazioniSet.m_lIdPrestazioneEndox > 0)
			{
				CRegioneSet regioneSet;
				regioneSet.SetOpenFilter("Contatore = 0");
				if (regioneSet.OpenRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame"))
				{
					if (regioneSet.AddNewRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame"))
					{
						regioneSet.m_lEsame = lIDEsame;
						regioneSet.m_lCodice = extPrestazioniSet.m_lIdPrestazioneEndox;
						regioneSet.m_lQuantita = extPrestazioniSet.m_lQuantita;
						regioneSet.m_lIdExtPrestazione = extPrestazioniSet.m_lId;
						regioneSet.m_lStatoCUP = 0;

						regioneSet.UpdateRecordset("CConiugazioneEsamiDlg::SelectEntry");
					}

					regioneSet.CloseRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame");
				}
			}

			extPrestazioniSet.MoveNext();
		}

		extPrestazioniSet.CloseRecordset("CConiugazioneEsamiDlg::UpdateDatiEsame");
	}

	//

	strFilter.Format("IDRICHIESTA=%li AND GETONDEMAND=0", lIDExtOrdini);

	CExtOrdiniAllegatiSet allegatiSetTemp;
	allegatiSetTemp.SetOpenFilter(strFilter);
	if (allegatiSetTemp.OpenRecordset("CEsamiView::UpdateDatiEsame"))
	{
		while (!allegatiSetTemp.IsEOF())
		{
			CTime timeNow = CTime::GetCurrentTime();
			CMyDocManager().ImportDoc(lIDPaziente, lIDEsame, allegatiSetTemp.m_sDescrizione, timeNow.Format("%Y%m%d%H%M%S"), allegatiSetTemp.m_sPath, FALSE);

			::DeleteFile(allegatiSetTemp.m_sPath);

			allegatiSetTemp.MoveNext();
		}

		allegatiSetTemp.CloseRecordset("CEsamiView::UpdateDatiEsame");
	}

	// Diagnosi

	strFilter.Format("IDRICHIESTA=%li", lIDExtOrdini);

	CExtOrdiniDiagnosiICD9Set diagnosiSet;
	diagnosiSet.SetOpenFilter(strFilter);
	if (diagnosiSet.OpenRecordset("CEsamiView::UpdateDatiEsame"))
	{
		while (!diagnosiSet.IsEOF())
		{
			long idDiagnosi = CDiagnosiICD9Set().GetIdFromICD9(diagnosiSet.m_sCodiceICD9);
			if (idDiagnosi > 0)
				CDiagnosiEsamiSet().Add(lIDEsame, idDiagnosi);

			diagnosiSet.MoveNext();
		}

		diagnosiSet.CloseRecordset("CEsamiView::UpdateDatiEsame");
	}

	// Procedure

	strFilter.Format("IDRICHIESTA=%li", lIDExtOrdini);

	CExtOrdiniProcedureICD9Set procedureSet;
	procedureSet.SetOpenFilter(strFilter);
	if (procedureSet.OpenRecordset("CEsamiView::UpdateDatiEsame"))
	{
		while (!procedureSet.IsEOF())
		{
			long idProcedura = CProcedureICD9Set().GetIdFromICD9(procedureSet.m_sCodiceICD9);
			if (idProcedura > 0)
				CProcedureEsamiSet().Add(lIDEsame, idProcedura);

			procedureSet.MoveNext();
		}

		procedureSet.CloseRecordset("CEsamiView::UpdateDatiEsame");
	}
}

void CConiugazioneEsamiDlg::UpdateWithExamID(long lIDEsame, CExtOrdiniSet* pSetExtOrdini)
{
	if (pSetExtOrdini->EditRecordset("CConiugazioneEsamiDlg::UpdateWithExamID"))
	{
		pSetExtOrdini->m_bTrasferito = TRUE;
		pSetExtOrdini->m_lStatoAccettazione = LPC_STATO_INCORSO;
		pSetExtOrdini->m_lIDEsameIns = lIDEsame;
		pSetExtOrdini->UpdateRecordset("CConiugazioneEsamiDlg::UpdateWithExamID");

		// Aggiungo l'esame alla lista degli esami accettati
		long userId;
		AMLogin_GetUserID(&userId);
		CEsamiAccettatiSet().InserisciRecord(lIDEsame, userId);
	}
}
