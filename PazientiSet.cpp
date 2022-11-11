#include "stdafx.h"
#include "Endox.h"
#include "PazientiSet.h"

#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define M_NFIELDS 59 //Julio - BUG 3285 - Adequação de laudos

IMPLEMENT_DYNAMIC(CPazientiSet, CBaseSet)

CPazientiSet::CPazientiSet()
: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = M_NFIELDS;
}

void CPazientiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "AssIden", m_sAssIden, 49);
		RFX_Text(pFX, "CodAlfa", m_sCodAlfa, 49);
		RFX_Text(pFX, "Cognome", m_sCognome, 255); // 49
		RFX_Text(pFX, "Nome", m_sNome, 255); // 49
		RFX_Long(pFX, "NatoIlCustom", m_lNatoIlCustom);
		RFX_Text(pFX, "NatoA", m_sNatoA, 49);
		RFX_Text(pFX, "Via", m_sVia, 255); // 149
		RFX_Text(pFX, "Citta", m_sCitta, 255); // 49
		RFX_Text(pFX, "CAP", m_sCAP, 50); // 5
		RFX_Text(pFX, "Provincia", m_sProvincia, 50);
		RFX_Text(pFX, "Telefono1", m_sTelefono1, 49);
		RFX_Text(pFX, "Telefono2", m_sTelefono2, 49);
		RFX_Text(pFX, "Fax", m_sFax, 49);
		RFX_Text(pFX, "Cellulare1", m_sCellulare1, 49);
		RFX_Text(pFX, "Cellulare2", m_sCellulare2, 49);
		RFX_Text(pFX, "eMail", m_sEmail, 49);
		RFX_Text(pFX, "CodFisc", m_sCodFisc, 16);
		RFX_Text(pFX, "CodSanit", m_sCodSanit, 20);
		RFX_Long(pFX, "Sesso", m_lSessoPaz);
		RFX_Long(pFX, "IdMedicoCurante", m_lMedicoCurante);
		RFX_Text(pFX, "MedicoCurante", m_sMedicoCurante, 255); // 49
		RFX_Text(pFX, "MedicoTel", m_sMedicoTel, 255); // 49
		RFX_Text(pFX, "MedicoIndirizzo", m_sMedicoIndirizzo, 255); // 49
		RFX_Text(pFX, "MedicoEmail", m_sMedicoEmail, 255); // 49
		RFX_Text(pFX, "Professione", m_sProfessione, 49);
		RFX_Text(pFX, "DenSegnalato", m_sDenSegnalato, 3999);
		RFX_Text(pFX, "Nazionalita", m_sNazionalita, 49);
		RFX_Long(pFX, "IDComune", m_lIDComune);
		RFX_Long(pFX, "IDComuneNascita", m_lIDComuneNascita);
		RFX_Text(pFX, "CodiceCliente", m_sCodiceCliente, 255);
		RFX_Text(pFX, "Cognome2", m_sCognome2, 255);
		RFX_Text(pFX, "NominativoPadre", m_sNominativoPadre, 255);
		RFX_Text(pFX, "NominativoMadre", m_sNominativoMadre, 255);
		RFX_Long(pFX, "DataUltimoEsame", m_lDataUltimoEsame);
		RFX_Long(pFX, "StatoAPC", m_lStatoAPC);
		RFX_Text(pFX, "Login", m_sLogin, 50);
		RFX_Bool(pFX, "SendEmail", m_bSendEmail);
		RFX_Bool(pFX, "SendSms", m_bSendSms);
		RFX_Text(pFX, "UlssResidenza", m_sUlssResidenza, 10);
		RFX_Bool(pFX, "PazienteDelDirettore", m_bPazienteDelDirettore);
		RFX_Long(pFX, "IDMalattiaCronica", m_lIDMalattiaCronica);
		RFX_Text(pFX, "DescrizioneMalattiaCronica", m_sDescrizioneMalattiaCronica, 3999);
		RFX_Bool(pFX, "CertificazioneMEF", m_bCertificazioneMEF);
		RFX_Bool(pFX, "CertificazioneSISS", m_bCertificazioneSISS);
		RFX_Text(pFX, "CodiceRicovero", m_sCodiceRicovero, 49);
		RFX_Text(pFX, "IdEpisodioRicovero", m_sIdEpisodioRicovero, 49);
		RFX_Long(pFX, "IdRepartoDegenza", m_lIdRepartoDegenza);
		RFX_Long(pFX, "DataRicoveroCustom", m_lDataRicoveroCustom);
		RFX_Long(pFX, "IDPazienteUnificato", m_lIDPazienteUnificato);
		RFX_Bool(pFX, "FlagDeceduto", m_bDeceduto);
		RFX_Long(pFX, "DataDecesso", m_lDataDecesso);
		RFX_Text(pFX, "CodiceSTP", m_sCodiceSTP, 50);
		RFX_Text(pFX, "CodiceIstAssicurativa", m_sCodiceIstAssicurativa, 50);
		RFX_Text(pFX, "CodiceTEAM", m_sCodiceTEAM, 50);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
		RFX_Text(pFX, "IDENTIFICAZIONEPASSAPORTO", m_sIdentificazionePassaporto, 50); // Julio - BUG 3285 - Adequação de laudos
		RFX_Text(pFX, "IDENTIFICAZIONEDOC_1", m_sIdentificazioneDoc1, 50);			  // Julio - BUG 3285 - Adequação de laudos
		RFX_Text(pFX, "IDENTIFICAZIONEDOC_2", m_sIdentificazioneDoc2, 50);			  // Julio - BUG 3285 - Adequação de laudos
	}
}

CString CPazientiSet::GetDefaultSQL()
{
	CString strTemp = theApp.m_sPazientiTabella;
	strTemp.MakeUpper();
	return strTemp;
}

void CPazientiSet::SetEmpty()
{
	m_lContatore = 0;
	m_sCodAlfa = "";
	m_sAssIden = "";
	m_sCognome = "";
	m_sNome = "";
	m_lNatoIlCustom = 0;
	// m_sNatoIlCustom = ""; // Sandro 23/07/2013 //
	m_sNatoA = "";
	m_sVia = "";
	m_sCitta = "";
	m_sCAP = "";
	m_sProvincia = "";
	m_sTelefono1 = "";
	m_sTelefono2 = "";
	m_sFax = "";
	m_sCellulare1 = "";
	m_sCellulare2 = "";
	m_sEmail = "";
	m_sCodFisc = "";
	m_sCodSanit = "";
	m_lSessoPaz = -1;
	m_lMedicoCurante = 0;
	m_sMedicoCurante = "";
	m_sMedicoTel = "";
	m_sMedicoIndirizzo = "";
	m_sMedicoEmail = "";
	m_sProfessione = "";
	m_sDenSegnalato = "";
	m_sNazionalita = "";
	m_lIDComune = 0;
	m_lIDComuneNascita = 0;
	m_sCodiceCliente = "";
	m_sCognome2 = "";
	m_sNominativoPadre = "";
	m_sNominativoMadre = "";
	m_lDataUltimoEsame = 0;
	m_lStatoAPC = 0;
	m_sLogin = "";
	m_bSendEmail = FALSE;
	m_bSendSms = FALSE;
	m_sUlssResidenza = "";
	m_bPazienteDelDirettore = FALSE;
	m_lIDMalattiaCronica = 0;
	m_sDescrizioneMalattiaCronica = "";
	m_bCertificazioneMEF = FALSE;
	m_bCertificazioneSISS = FALSE;
	m_sCodiceRicovero = "";
	m_sIdEpisodioRicovero = "";
	m_lIdRepartoDegenza = 0;
	m_lDataRicoveroCustom = 0;
	m_lIDPazienteUnificato = 0;
	m_bDeceduto = FALSE;
	m_lDataDecesso = 0;
	m_sCodiceSTP = "";
	m_sCodiceIstAssicurativa = "";
	m_sCodiceTEAM = "";
	m_bEliminato = FALSE;

	m_lTotEsami = 0;
	m_sFiltroExtra = "";
	m_sIdentificazionePassaporto = ""; // Julio - BUG 3285 - Adequação de laudos
	m_sIdentificazioneDoc1 = "";	   // Julio - BUG 3285 - Adequação de laudos
	m_sIdentificazioneDoc2 = "";	   // Julio - BUG 3285 - Adequação de laudos
}

void CPazientiSet::CopyFieldFrom(CPazientiSet* pSet)
{
	SetEmpty();

	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lContatore) == FALSE))
		m_lContatore = pSet->m_lContatore;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sAssIden) == FALSE))
		m_sAssIden = pSet->m_sAssIden;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodAlfa) == FALSE))
		m_sCodAlfa = pSet->m_sCodAlfa;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCognome) == FALSE))
		m_sCognome = pSet->m_sCognome;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sNome) == FALSE))
		m_sNome = pSet->m_sNome;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lNatoIlCustom) == FALSE))
		m_lNatoIlCustom = pSet->m_lNatoIlCustom;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sNatoA) == FALSE))
		m_sNatoA = pSet->m_sNatoA;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sVia) == FALSE))
		m_sVia = pSet->m_sVia;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCitta) == FALSE))
		m_sCitta = pSet->m_sCitta;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCAP) == FALSE))
		m_sCAP = pSet->m_sCAP;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sProvincia) == FALSE))
		m_sProvincia = pSet->m_sProvincia;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sTelefono1) == FALSE))
		m_sTelefono1 = pSet->m_sTelefono1;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sTelefono2) == FALSE))
		m_sTelefono2 = pSet->m_sTelefono2;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sFax) == FALSE))
		m_sFax = pSet->m_sFax;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCellulare1) == FALSE))
		m_sCellulare1 = pSet->m_sCellulare1;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCellulare2) == FALSE))
		m_sCellulare2 = pSet->m_sCellulare2;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sEmail) == FALSE))
		m_sEmail = pSet->m_sEmail;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodFisc) == FALSE))
		m_sCodFisc = pSet->m_sCodFisc;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodSanit) == FALSE))
		m_sCodSanit = pSet->m_sCodSanit;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lSessoPaz) == FALSE))
		m_lSessoPaz = pSet->m_lSessoPaz;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lMedicoCurante) == FALSE))
		m_lMedicoCurante = pSet->m_lMedicoCurante;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sMedicoCurante) == FALSE))
		m_sMedicoCurante = pSet->m_sMedicoCurante;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sMedicoTel) == FALSE))
		m_sMedicoTel = pSet->m_sMedicoTel;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sMedicoIndirizzo) == FALSE))
		m_sMedicoIndirizzo = pSet->m_sMedicoIndirizzo;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sMedicoEmail) == FALSE))
		m_sMedicoEmail = pSet->m_sMedicoEmail;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sProfessione) == FALSE))
		m_sProfessione = pSet->m_sProfessione;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sDenSegnalato) == FALSE))
		m_sDenSegnalato = pSet->m_sDenSegnalato;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sNazionalita) == FALSE))
		m_sNazionalita = pSet->m_sNazionalita;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lIDComune) == FALSE))
		m_lIDComune = pSet->m_lIDComune;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lIDComuneNascita) == FALSE))
		m_lIDComuneNascita = pSet->m_lIDComuneNascita;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodiceCliente) == FALSE))
		m_sCodiceCliente = pSet->m_sCodiceCliente;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCognome2) == FALSE))
		m_sCognome2 = pSet->m_sCognome2;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sNominativoPadre) == FALSE))
		m_sNominativoPadre = pSet->m_sNominativoPadre;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sNominativoMadre) == FALSE))
		m_sNominativoMadre = pSet->m_sNominativoMadre;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lDataUltimoEsame) == FALSE))
		m_lDataUltimoEsame = pSet->m_lDataUltimoEsame;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lStatoAPC) == FALSE))
		m_lStatoAPC = pSet->m_lStatoAPC;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sLogin) == FALSE))
		m_sLogin = pSet->m_sLogin;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_bSendEmail) == FALSE))
		m_bSendEmail = pSet->m_bSendEmail;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_bSendSms) == FALSE))
		m_bSendSms = pSet->m_bSendSms;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sUlssResidenza) == FALSE))
		m_sUlssResidenza = pSet->m_sUlssResidenza;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_bPazienteDelDirettore) == FALSE))
		m_bPazienteDelDirettore = pSet->m_bPazienteDelDirettore;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lIDMalattiaCronica) == FALSE))
		m_lIDMalattiaCronica = pSet->m_lIDMalattiaCronica;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sDescrizioneMalattiaCronica) == FALSE))
		m_sDescrizioneMalattiaCronica = pSet->m_sDescrizioneMalattiaCronica;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_bCertificazioneMEF) == FALSE))
		m_bCertificazioneMEF = pSet->m_bCertificazioneMEF;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_bCertificazioneSISS) == FALSE))
		m_bCertificazioneSISS = pSet->m_bCertificazioneSISS;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodiceRicovero) == FALSE))
		m_sCodiceRicovero = pSet->m_sCodiceRicovero;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sIdEpisodioRicovero) == FALSE))
		m_sIdEpisodioRicovero = pSet->m_sIdEpisodioRicovero;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lIdRepartoDegenza) == FALSE))
		m_lIdRepartoDegenza = pSet->m_lIdRepartoDegenza;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lDataRicoveroCustom) == FALSE))
		m_lDataRicoveroCustom = pSet->m_lDataRicoveroCustom;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lIDPazienteUnificato) == FALSE))
		m_lIDPazienteUnificato = pSet->m_lIDPazienteUnificato;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_bDeceduto) == FALSE))
		m_bDeceduto = pSet->m_bDeceduto;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_lDataDecesso) == FALSE))
		m_lDataDecesso = pSet->m_lDataDecesso;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodiceSTP) == FALSE))
		m_sCodiceSTP = pSet->m_sCodiceSTP;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodiceIstAssicurativa) == FALSE))
		m_sCodiceIstAssicurativa = pSet->m_sCodiceIstAssicurativa;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sCodiceTEAM) == FALSE))
		m_sCodiceTEAM = pSet->m_sCodiceTEAM;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_bEliminato) == FALSE))
		m_bEliminato = pSet->m_bEliminato;

	// Julio - BUG 3285 - Adequação de laudos
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sIdentificazionePassaporto) == FALSE))
		m_sIdentificazionePassaporto = pSet->m_sIdentificazionePassaporto;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sIdentificazioneDoc1) == FALSE))
		m_sIdentificazioneDoc1 = pSet->m_sIdentificazioneDoc1;
	if ((pSet->IsOpen() == FALSE) || (pSet->IsFieldNull(&pSet->m_sIdentificazioneDoc2) == FALSE))
		m_sIdentificazioneDoc2 = pSet->m_sIdentificazioneDoc2;

	if (IsOpen() == TRUE)
	{
		SetFieldNull(NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

CString CPazientiSet::GetCognomeNome(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CPazientiSet::GetCognomeNome"))
	{
		if (!IsEOF())
		{
			strReturn = m_sCognome + " " + m_sNome;
			strReturn.Trim();
		}

		CloseRecordset("CPazientiSet::GetCognomeNome");
	}

	return strReturn;
}

CString CPazientiSet::GetCognomeNomeDataNascita(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CPazientiSet::GetCognomeNomeDataNascita"))
	{
		if (!IsEOF())
		{
			strReturn = m_sCognome + " " + m_sNome + " " + CCustomDate(m_lNatoIlCustom).GetDate("%d/%m/%Y");
			strReturn.Trim();
		}

		CloseRecordset("CPazientiSet::GetCognomeNomeDataNascita");
	}

	return strReturn;
}

void CPazientiSet::UpdateDataUltimoEsame(const long lContatore)
{
	CString strQuery;
	strQuery.Format("SELECT MAX(DATA) AS DATA FROM EESAMI WHERE PAZIENTE = %li AND ELIMINATO = 0", lContatore);

	CRecordset set(m_pDatabase);

	try
	{
		set.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
		if (!set.IsEOF())
		{
			CString strData;
			set.GetFieldValue((short)0, strData);

			CString strFilter;
			strFilter.Format("CONTATORE = %li", lContatore);
			SetOpenFilter(strFilter);
			if (OpenRecordset("CEsamiSet::UpdateRecordset"))
			{
				if (!IsEOF())
				{
					EditRecordset("CEsamiSet::UpdateRecordset");
					m_lDataUltimoEsame = atol(strData);
					UpdateRecordset("CEsamiSet::UpdateRecordset");
				}

				CloseRecordset("CEsamiSet::UpdateRecordset");
			}
		}
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	if (set.IsOpen())
		set.Close();
}

CBaseSet* CPazientiSet::CreateNew()
{
	return (CBaseSet*)new CPazientiSet;
}

void CPazientiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPazientiSet* pPazientiSet = (CPazientiSet*)pOriginalSet;

	// Sandro 05/05/2015 // provo questa modifica per la Spagna, l'AssIden assegnato da stored procedure veniva "perso"... spero che non si verifichino "side effects"... //
	/*if (bCopyAll)
	{
	m_sAssIden = pPazientiSet->m_sAssIden;
	}
	else
	{
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sAssIden))
	if (m_sAssIden.IsEmpty())
	m_sAssIden = pPazientiSet->m_sAssIden;
	}*/

	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sAssIden) || bCopyAll)
		m_sAssIden = pPazientiSet->m_sAssIden;

	//
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodAlfa) || bCopyAll)
		m_sCodAlfa = pPazientiSet->m_sCodAlfa;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCognome) || bCopyAll)
		m_sCognome = pPazientiSet->m_sCognome;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sNome) || bCopyAll)
		m_sNome = pPazientiSet->m_sNome;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lNatoIlCustom) || bCopyAll)
		m_lNatoIlCustom = pPazientiSet->m_lNatoIlCustom;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sNatoA) || bCopyAll)
		m_sNatoA = pPazientiSet->m_sNatoA;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sVia) || bCopyAll)
		m_sVia = pPazientiSet->m_sVia;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCitta) || bCopyAll)
		m_sCitta = pPazientiSet->m_sCitta;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCAP) || bCopyAll)
		m_sCAP = pPazientiSet->m_sCAP;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sProvincia) || bCopyAll)
		m_sProvincia = pPazientiSet->m_sProvincia;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sTelefono1) || bCopyAll)
		m_sTelefono1 = pPazientiSet->m_sTelefono1;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sTelefono2) || bCopyAll)
		m_sTelefono2 = pPazientiSet->m_sTelefono2;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sFax) || bCopyAll)
		m_sFax = pPazientiSet->m_sFax;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCellulare1) || bCopyAll)
		m_sCellulare1 = pPazientiSet->m_sCellulare1;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCellulare2) || bCopyAll)
		m_sCellulare2 = pPazientiSet->m_sCellulare2;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sEmail) || bCopyAll)
		m_sEmail = pPazientiSet->m_sEmail;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodFisc) || bCopyAll)
		m_sCodFisc = pPazientiSet->m_sCodFisc;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodSanit) || bCopyAll)
		m_sCodSanit = pPazientiSet->m_sCodSanit;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lSessoPaz) || bCopyAll)
		m_lSessoPaz = pPazientiSet->m_lSessoPaz;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lMedicoCurante) || bCopyAll)
		m_lMedicoCurante = pPazientiSet->m_lMedicoCurante;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sMedicoCurante) || bCopyAll)
		m_sMedicoCurante = pPazientiSet->m_sMedicoCurante;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sMedicoTel) || bCopyAll)
		m_sMedicoTel = pPazientiSet->m_sMedicoTel;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sMedicoIndirizzo) || bCopyAll)
		m_sMedicoIndirizzo = pPazientiSet->m_sMedicoIndirizzo;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sMedicoEmail) || bCopyAll)
		m_sMedicoEmail = pPazientiSet->m_sMedicoEmail;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sProfessione) || bCopyAll)
		m_sProfessione = pPazientiSet->m_sProfessione;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sDenSegnalato) || bCopyAll)
		m_sDenSegnalato = pPazientiSet->m_sDenSegnalato;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sNazionalita) || bCopyAll)
		m_sNazionalita = pPazientiSet->m_sNazionalita;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lIDComune) || bCopyAll)
		m_lIDComune = pPazientiSet->m_lIDComune;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lIDComuneNascita) || bCopyAll)
		m_lIDComuneNascita = pPazientiSet->m_lIDComuneNascita;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodiceCliente) || bCopyAll)
		m_sCodiceCliente = pPazientiSet->m_sCodiceCliente;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCognome2) || bCopyAll)
		m_sCognome2 = pPazientiSet->m_sCognome2;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sNominativoPadre) || bCopyAll)
		m_sNominativoPadre = pPazientiSet->m_sNominativoPadre;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sNominativoMadre) || bCopyAll)
		m_sNominativoMadre = pPazientiSet->m_sNominativoMadre;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lDataUltimoEsame) || bCopyAll)
		m_lDataUltimoEsame = pPazientiSet->m_lDataUltimoEsame;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lStatoAPC) || bCopyAll)
		m_lStatoAPC = pPazientiSet->m_lStatoAPC;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sLogin) || bCopyAll)
		m_sLogin = pPazientiSet->m_sLogin;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bSendEmail) || bCopyAll)
		m_bSendEmail = pPazientiSet->m_bSendEmail;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bSendSms) || bCopyAll)
		m_bSendSms = pPazientiSet->m_bSendSms;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sUlssResidenza) || bCopyAll)
		m_sUlssResidenza = pPazientiSet->m_sUlssResidenza;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bPazienteDelDirettore) || bCopyAll)
		m_bPazienteDelDirettore = pPazientiSet->m_bPazienteDelDirettore;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lIDMalattiaCronica) || bCopyAll)
		m_lIDMalattiaCronica = pPazientiSet->m_lIDMalattiaCronica;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sDescrizioneMalattiaCronica) || bCopyAll)
		m_sDescrizioneMalattiaCronica = pPazientiSet->m_sDescrizioneMalattiaCronica;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bCertificazioneMEF) || bCopyAll)
		m_bCertificazioneMEF = pPazientiSet->m_bCertificazioneMEF;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bCertificazioneSISS) || bCopyAll)
		m_bCertificazioneSISS = pPazientiSet->m_bCertificazioneSISS;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodiceRicovero) || bCopyAll)
		m_sCodiceRicovero = pPazientiSet->m_sCodiceRicovero;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sIdEpisodioRicovero) || bCopyAll)
		m_sIdEpisodioRicovero = pPazientiSet->m_sIdEpisodioRicovero;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lIdRepartoDegenza) || bCopyAll)
		m_lIdRepartoDegenza = pPazientiSet->m_lIdRepartoDegenza;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lDataRicoveroCustom) || bCopyAll)
		m_lDataRicoveroCustom = pPazientiSet->m_lDataRicoveroCustom;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lIDPazienteUnificato) || bCopyAll)
		m_lIDPazienteUnificato = pPazientiSet->m_lIDPazienteUnificato;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bDeceduto) || bCopyAll)
		m_bDeceduto = pPazientiSet->m_bDeceduto;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lDataDecesso) || bCopyAll)
		m_lDataDecesso = pPazientiSet->m_lDataDecesso;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodiceSTP) || bCopyAll)
		m_sCodiceSTP = pPazientiSet->m_sCodiceSTP;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodiceIstAssicurativa) || bCopyAll)
		m_sCodiceIstAssicurativa = pPazientiSet->m_sCodiceIstAssicurativa;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sCodiceTEAM) || bCopyAll)
		m_sCodiceTEAM = pPazientiSet->m_sCodiceTEAM;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pPazientiSet->m_bEliminato;

	// Julio - BUG 3285 - Adequação de laudos
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sIdentificazionePassaporto) || bCopyAll)
		m_sIdentificazionePassaporto = pPazientiSet->m_sIdentificazionePassaporto;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sIdentificazioneDoc1) || bCopyAll)
		m_sIdentificazioneDoc1 = pPazientiSet->m_sIdentificazioneDoc1;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sIdentificazioneDoc2) || bCopyAll)
		m_sIdentificazioneDoc2 = pPazientiSet->m_sIdentificazioneDoc2;

}

void CPazientiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPazientiSet* pOV = (CPazientiSet*)pOldValues;
	CPazientiSet* pNV = (CPazientiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("AssIden", pOV, &pOV->m_sAssIden, pNV, &pNV->m_sAssIden);
	sp.Execute("CodAlfa", pOV, &pOV->m_sCodAlfa, pNV, &pNV->m_sCodAlfa);
	sp.Execute("Cognome", pOV, &pOV->m_sCognome, pNV, &pNV->m_sCognome);
	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("NatoIlCustom", pOV, &pOV->m_lNatoIlCustom, pNV, &pNV->m_lNatoIlCustom);
	sp.Execute("NatoA", pOV, &pOV->m_sNatoA, pNV, &pNV->m_sNatoA);
	sp.Execute("Via", pOV, &pOV->m_sVia, pNV, &pNV->m_sVia);
	sp.Execute("Citta", pOV, &pOV->m_sCitta, pNV, &pNV->m_sCitta);
	sp.Execute("CAP", pOV, &pOV->m_sCAP, pNV, &pNV->m_sCAP);
	sp.Execute("Provincia", pOV, &pOV->m_sProvincia, pNV, &pNV->m_sProvincia);
	sp.Execute("Telefono1", pOV, &pOV->m_sTelefono1, pNV, &pNV->m_sTelefono1);
	sp.Execute("Telefono2", pOV, &pOV->m_sTelefono2, pNV, &pNV->m_sTelefono2);
	sp.Execute("Fax", pOV, &pOV->m_sFax, pNV, &pNV->m_sFax);
	sp.Execute("Cellulare1", pOV, &pOV->m_sCellulare1, pNV, &pNV->m_sCellulare1);
	sp.Execute("Cellulare2", pOV, &pOV->m_sCellulare2, pNV, &pNV->m_sCellulare2);
	sp.Execute("eMail", pOV, &pOV->m_sEmail, pNV, &pNV->m_sEmail);
	sp.Execute("CodFisc", pOV, &pOV->m_sCodFisc, pNV, &pNV->m_sCodFisc);
	sp.Execute("CodSanit", pOV, &pOV->m_sCodSanit, pNV, &pNV->m_sCodSanit);
	sp.Execute("Sesso", pOV, &pOV->m_lSessoPaz, pNV, &pNV->m_lSessoPaz);
	sp.Execute("IdMedicoCurante", pOV, &pOV->m_lMedicoCurante, pNV, &pNV->m_lMedicoCurante);
	sp.Execute("MedicoCurante", pOV, &pOV->m_sMedicoCurante, pNV, &pNV->m_sMedicoCurante);
	sp.Execute("MedicoTel", pOV, &pOV->m_sMedicoTel, pNV, &pNV->m_sMedicoTel);
	sp.Execute("MedicoIndirizzo", pOV, &pOV->m_sMedicoIndirizzo, pNV, &pNV->m_sMedicoIndirizzo);
	sp.Execute("MedicoEmail", pOV, &pOV->m_sMedicoEmail, pNV, &pNV->m_sMedicoEmail);
	sp.Execute("Professione", pOV, &pOV->m_sProfessione, pNV, &pNV->m_sProfessione);
	sp.Execute("DenSegnalato", pOV, &pOV->m_sDenSegnalato, pNV, &pNV->m_sDenSegnalato);
	sp.Execute("Nazionalita", pOV, &pOV->m_sNazionalita, pNV, &pNV->m_sNazionalita);
	sp.Execute("IDComune", pOV, &pOV->m_lIDComune, pNV, &pNV->m_lIDComune);
	sp.Execute("IDComuneNascita", pOV, &pOV->m_lIDComuneNascita, pNV, &pNV->m_lIDComuneNascita);
	sp.Execute("CodiceCliente", pOV, &pOV->m_sCodiceCliente, pNV, &pNV->m_sCodiceCliente);
	sp.Execute("Cognome2", pOV, &pOV->m_sCognome2, pNV, &pNV->m_sCognome2);
	sp.Execute("NominativoPadre", pOV, &pOV->m_sNominativoPadre, pNV, &pNV->m_sNominativoPadre);
	sp.Execute("NominativoMadre", pOV, &pOV->m_sNominativoMadre, pNV, &pNV->m_sNominativoMadre);
	sp.Execute("DataUltimoEsame", pOV, &pOV->m_lDataUltimoEsame, pNV, &pNV->m_lDataUltimoEsame);
	sp.Execute("StatoAPC", pOV, &pOV->m_lStatoAPC, pNV, &pNV->m_lStatoAPC);
	sp.Execute("Login", pOV, &pOV->m_sLogin, pNV, &pNV->m_sLogin);
	sp.Execute("SendEmail", pOV, &pOV->m_bSendEmail, pNV, &pNV->m_bSendEmail);
	sp.Execute("SendSms", pOV, &pOV->m_bSendSms, pNV, &pNV->m_bSendSms);
	sp.Execute("UlssResidenza", pOV, &pOV->m_sUlssResidenza, pNV, &pNV->m_sUlssResidenza);
	sp.Execute("PazienteDelDirettore", pOV, &pOV->m_bPazienteDelDirettore, pNV, &pNV->m_bPazienteDelDirettore);
	sp.Execute("IDMalattiaCronica", pOV, &pOV->m_lIDMalattiaCronica, pNV, &pNV->m_lIDMalattiaCronica);
	sp.Execute("DescrizioneMalattiaCronica", pOV, &pOV->m_sDescrizioneMalattiaCronica, pNV, &pNV->m_sDescrizioneMalattiaCronica);
	sp.Execute("CertificazioneMEF", pOV, &pOV->m_bCertificazioneMEF, pNV, &pNV->m_bCertificazioneMEF);
	sp.Execute("CertificazioneSISS", pOV, &pOV->m_bCertificazioneSISS, pNV, &pNV->m_bCertificazioneSISS);
	sp.Execute("CodiceRicovero", pOV, &pOV->m_sCodiceRicovero, pNV, &pNV->m_sCodiceRicovero);
	sp.Execute("IdEpisodioRicovero", pOV, &pOV->m_sIdEpisodioRicovero, pNV, &pNV->m_sIdEpisodioRicovero);
	sp.Execute("IdRepartoDegenza", pOV, &pOV->m_lIdRepartoDegenza, pNV, &pNV->m_lIdRepartoDegenza);
	sp.Execute("DataRicoveroCustom", pOV, &pOV->m_lDataRicoveroCustom, pNV, &pNV->m_lDataRicoveroCustom);
	sp.Execute("IDPazienteUnificato", pOV, &pOV->m_lIDPazienteUnificato, pNV, &pNV->m_lIDPazienteUnificato);
	sp.Execute("FlagDeceduto", pOV, &pOV->m_bDeceduto, pNV, &pNV->m_bDeceduto);
	sp.Execute("DataDecesso", pOV, &pOV->m_lDataDecesso, pNV, &pNV->m_lDataDecesso);
	sp.Execute("CodiceSTP", pOV, &pOV->m_sCodiceSTP, pNV, &pNV->m_sCodiceSTP);
	sp.Execute("CodiceTEAM", pOV, &pOV->m_sCodiceTEAM, pNV, &pNV->m_sCodiceTEAM);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);

	// Julio - BUG 3285 - Adequação de laudos
	sp.Execute("IdentificazionePassaporto", pOV, &pOV->m_sIdentificazionePassaporto, pNV, &pNV->m_sIdentificazionePassaporto);
	sp.Execute("IdentificazioneDoc1", pOV, &pOV->m_sIdentificazioneDoc1, pNV, &pNV->m_sIdentificazioneDoc1);
	sp.Execute("IdentificazioneDoc2", pOV, &pOV->m_sIdentificazioneDoc2, pNV, &pNV->m_sIdentificazioneDoc2);
}

BOOL CPazientiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPazientiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CPazientiSet::DeleteRecordset");
	}
	return bReturn;
}

BOOL CPazientiSet::UndeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPazientiSet::UndeleteRecordset"))
	{
		m_bEliminato = FALSE;
		bReturn = UpdateRecordset("CPazientiSet::UndeleteRecordset");
	}
	return bReturn;
}

CString CPazientiSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

void CPazientiSet::SetFastSearch(BOOL bFast)
{
	m_nFields = (bFast ? 1 : M_NFIELDS);
}

