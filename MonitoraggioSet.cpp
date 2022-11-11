#include "stdafx.h"
#include "Endox.h"
#include "MonitoraggioSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMonitoraggioSet, CBaseSet)

CMonitoraggioSet::CMonitoraggioSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 55;
	SetBaseFilter("");
}

void CMonitoraggioSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{		
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "Quando", m_lQuando);
		RFX_Text(pFX, "Ora", m_strOra, 10);
		RFX_Long(pFX, "Infermiere", m_lIdInfermiere);
		RFX_Text(pFX, "FC", m_strFC, 10);
		RFX_Long(pFX, "FC_POLSO", m_lFCPolso);
		RFX_Text(pFX, "PA", m_strPA, 10);
		RFX_Text(pFX, "SAT", m_strSat, 10);
		RFX_Text(pFX, "O2", m_strO2, 10);
		RFX_Text(pFX, "ETCO2", m_strETCO2, 10);
		RFX_Long(pFX, "INTUBAZIONE", m_lIntubazione);
		RFX_Long(pFX, "VENTILAZIONE", m_lVentilazione);
		RFX_Text(pFX, "VENTILAZIONE_VT", m_strVentilazioneVt, 10);
		RFX_Text(pFX, "VENTILAZIONE_FR", m_strVentilazioneFr, 10);
		RFX_Text(pFX, "Mida", m_strMida, 10);
		RFX_Text(pFX, "Peti", m_strPeti, 10);
		RFX_Text(pFX, "Atro", m_strAtro, 10);
		RFX_Text(pFX, "Nalo", m_strNalo, 10);
		RFX_Text(pFX, "Flum", m_strFlum, 10);
		RFX_Text(pFX, "Scop", m_strScop, 10);
		RFX_Text(pFX, "Gluc", m_strGluc, 10);
		RFX_Text(pFX, "Altri", m_strAltri, 255);
		RFX_Long(pFX, "DOLORE_SCALA", m_lDoloreScala);
		RFX_Long(pFX, "DOLORE", m_lDoloreVAS);
		RFX_Long(pFX, "DOLORENRS", m_lDoloreNRS);
		RFX_Long(pFX, "DOLOREWB", m_lDoloreWB);
		RFX_Long(pFX, "DOLORECCPO1", m_lDoloreCCPO1);
		RFX_Long(pFX, "DOLORECCPO2", m_lDoloreCCPO2);
		RFX_Long(pFX, "DOLORECCPO3", m_lDoloreCCPO3);
		RFX_Long(pFX, "DOLORECCPO4", m_lDoloreCCPO4);
		RFX_Long(pFX, "DOLORECCPO5", m_lDoloreCCPO5);
		RFX_Long(pFX, "DOLORE_LOCALIZZAZIONE", m_lDoloreLocalizzazione);
		RFX_Text(pFX, "DOLORE_LOCALIZZAZIONE_DETT", m_sDoloreLocalizzazioneDettaglio, 255);
		RFX_Long(pFX, "DOLORE_CARATTERISTICHE", m_lDoloreCaratteristiche);
		RFX_Long(pFX, "DOLORE_FREQUENZA", m_lDoloreFrequenza);
		RFX_Long(pFX, "DOLORE_DURATA", m_lDoloreDurata);
		RFX_Long(pFX, "RAMSAY", m_lRamsay);
		RFX_Long(pFX, "PuntiScore1", m_lPuntiScore1);
		RFX_Long(pFX, "PuntiScore2", m_lPuntiScore2);
		RFX_Long(pFX, "PuntiScore3", m_lPuntiScore3);
		RFX_Long(pFX, "PuntiScore4", m_lPuntiScore4);
		RFX_Long(pFX, "TotalScore", m_lTotalScore);
		RFX_Long(pFX, "PuntiScore1Glasgow", m_lPuntiScore1Glasgow);
		RFX_Long(pFX, "PuntiScore2Glasgow", m_lPuntiScore2Glasgow);
		RFX_Long(pFX, "PuntiScore3Glasgow", m_lPuntiScore3Glasgow);
		RFX_Long(pFX, "TotalScoreGlasgow", m_lTotalScoreGlasgow);
		RFX_Long(pFX, "IdPdf", m_lIdPdf);
		RFX_Text(pFX, "NotePdf", m_sNotePdf, 4000);
		RFX_Bool(pFX, "Terminato", m_bTerminato);
		RFX_Text(pFX, "IdSessione", m_sIdSessione, 255);
		RFX_Text(pFX, "NomeStazione", m_sNomeStazione, 255);
		RFX_Long(pFX, "IdDispositivo", m_lIdDispositivo);
		RFX_Text(pFX, "IDESTERNO", m_sIdEsterno, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CMonitoraggioSet::GetDefaultSQL()
{
	return "MONITORAGGIO";
}

void CMonitoraggioSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lQuando = 0;
	m_strOra = "";
	m_lIdInfermiere = 0;
	m_strFC = "";
	m_strPA = "";
	m_strSat = "";
	m_strO2 = "";
	m_strMida = "";
	m_strPeti = "";
	m_strAtro = "";
	m_strNalo = "";
	m_strFlum = "";
	m_strScop = "";
	m_strGluc = "";
	m_strAltri = "";
	m_lDoloreVAS = 0;
	m_lDoloreNRS = 0;
	m_lDoloreWB = 0;
	m_lDoloreCCPO1 = 0;
	m_lDoloreCCPO2 = 0;
	m_lDoloreCCPO3 = 0;
	m_lDoloreCCPO4 = 0;
	m_lDoloreCCPO5 = 0;
	m_lPuntiScore1 = 1;
	m_lPuntiScore2 = 0;
	m_lPuntiScore3 = 0;
	m_lPuntiScore4 = 0;
	m_lTotalScore = 0;
	m_lPuntiScore1Glasgow = 0;
	m_lPuntiScore2Glasgow = 0;
	m_lPuntiScore3Glasgow = 0;
	m_lTotalScoreGlasgow = 0;
	m_lIdPdf = 0;
	m_sNotePdf = "";
	m_bTerminato = FALSE;
	m_sIdSessione = "";
	m_sNomeStazione = "";
	m_lIdDispositivo = 0;
	m_bEliminato = FALSE;
	m_lFCPolso = 0;
	m_strETCO2 = "";
	m_lIntubazione = 0;
	m_lDoloreScala = 0;
	m_lVentilazione = 0;
	m_strVentilazioneVt = "";
	m_strVentilazioneFr = "";
	m_lDoloreLocalizzazione = 0;
	m_sDoloreLocalizzazioneDettaglio = "";
	m_lDoloreCaratteristiche = 0;
	m_lDoloreFrequenza = 0;
	m_lDoloreDurata = 0;
	m_lRamsay = 0;
	m_sIdEsterno = "";
}

CBaseSet* CMonitoraggioSet::CreateNew()
{
	return (CBaseSet*)new CMonitoraggioSet;
}

void CMonitoraggioSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMonitoraggioSet* pMonitoraggioSet = (CMonitoraggioSet*)pOriginalSet;

	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pMonitoraggioSet->m_lIDEsame;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lQuando) || bCopyAll)
		m_lQuando = pMonitoraggioSet->m_lQuando;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strOra) || bCopyAll)
		m_strOra = pMonitoraggioSet->m_strOra;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lIdInfermiere) || bCopyAll)
		m_lIdInfermiere = pMonitoraggioSet->m_lIdInfermiere;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strFC) || bCopyAll)
		m_strFC = pMonitoraggioSet->m_strFC;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strPA) || bCopyAll)
		m_strPA = pMonitoraggioSet->m_strPA;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strSat) || bCopyAll)
		m_strSat = pMonitoraggioSet->m_strSat;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strO2) || bCopyAll)
		m_strO2 = pMonitoraggioSet->m_strO2;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strMida) || bCopyAll)
		m_strMida = pMonitoraggioSet->m_strMida;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strPeti) || bCopyAll)
		m_strPeti = pMonitoraggioSet->m_strPeti;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strAtro) || bCopyAll)
		m_strAtro = pMonitoraggioSet->m_strAtro;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strNalo) || bCopyAll)
		m_strNalo = pMonitoraggioSet->m_strNalo;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strFlum) || bCopyAll)
		m_strFlum = pMonitoraggioSet->m_strFlum;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strScop) || bCopyAll)
		m_strScop = pMonitoraggioSet->m_strScop;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strGluc) || bCopyAll)
		m_strGluc = pMonitoraggioSet->m_strGluc;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strAltri) || bCopyAll)
		m_strAltri = pMonitoraggioSet->m_strAltri;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreVAS) || bCopyAll)
		m_lDoloreVAS = pMonitoraggioSet->m_lDoloreVAS;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreNRS) || bCopyAll)
		m_lDoloreNRS = pMonitoraggioSet->m_lDoloreNRS;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreWB) || bCopyAll)
		m_lDoloreWB = pMonitoraggioSet->m_lDoloreWB;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreCCPO1) || bCopyAll)
		m_lDoloreCCPO1 = pMonitoraggioSet->m_lDoloreCCPO1;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreCCPO2) || bCopyAll)
		m_lDoloreCCPO2 = pMonitoraggioSet->m_lDoloreCCPO2;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreCCPO3) || bCopyAll)
		m_lDoloreCCPO3 = pMonitoraggioSet->m_lDoloreCCPO3;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreCCPO4) || bCopyAll)
		m_lDoloreCCPO4 = pMonitoraggioSet->m_lDoloreCCPO4;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreCCPO5) || bCopyAll)
		m_lDoloreCCPO5 = pMonitoraggioSet->m_lDoloreCCPO5;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lPuntiScore1) || bCopyAll)
		m_lPuntiScore1 = pMonitoraggioSet->m_lPuntiScore1;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lPuntiScore2) || bCopyAll)
		m_lPuntiScore2 = pMonitoraggioSet->m_lPuntiScore2;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lPuntiScore3) || bCopyAll)
		m_lPuntiScore3 = pMonitoraggioSet->m_lPuntiScore3;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lPuntiScore4) || bCopyAll)
		m_lPuntiScore4 = pMonitoraggioSet->m_lPuntiScore4;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lTotalScore) || bCopyAll)
		m_lTotalScore = pMonitoraggioSet->m_lTotalScore;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lPuntiScore1Glasgow) || bCopyAll)
		m_lPuntiScore1Glasgow = pMonitoraggioSet->m_lPuntiScore1Glasgow;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lPuntiScore2Glasgow) || bCopyAll)
		m_lPuntiScore2Glasgow = pMonitoraggioSet->m_lPuntiScore2Glasgow;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lPuntiScore3Glasgow) || bCopyAll)
		m_lPuntiScore3Glasgow = pMonitoraggioSet->m_lPuntiScore3Glasgow;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lTotalScoreGlasgow) || bCopyAll)
		m_lTotalScoreGlasgow = pMonitoraggioSet->m_lTotalScoreGlasgow;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lIdPdf) || bCopyAll)
		m_lIdPdf = pMonitoraggioSet->m_lIdPdf;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_sNotePdf) || bCopyAll)
		m_sNotePdf = pMonitoraggioSet->m_sNotePdf;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_bTerminato) || bCopyAll)
		m_bTerminato = pMonitoraggioSet->m_bTerminato;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_sIdSessione) || bCopyAll)
		m_sIdSessione = pMonitoraggioSet->m_sIdSessione;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_sNomeStazione) || bCopyAll)
		m_sNomeStazione = pMonitoraggioSet->m_sNomeStazione;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lIdDispositivo) || bCopyAll)
		m_lIdDispositivo = pMonitoraggioSet->m_lIdDispositivo;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pMonitoraggioSet->m_bEliminato;

	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lFCPolso) || bCopyAll)
		m_lFCPolso = pMonitoraggioSet->m_lFCPolso;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strETCO2) || bCopyAll)
		m_strETCO2 = pMonitoraggioSet->m_strETCO2;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lIntubazione) || bCopyAll)
		m_lIntubazione = pMonitoraggioSet->m_lIntubazione;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreScala) || bCopyAll)
		m_lDoloreScala = pMonitoraggioSet->m_lDoloreScala;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lVentilazione) || bCopyAll)
		m_lVentilazione = pMonitoraggioSet->m_lVentilazione;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strVentilazioneVt) || bCopyAll)
		m_strVentilazioneVt = pMonitoraggioSet->m_strVentilazioneVt;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_strVentilazioneFr) || bCopyAll)
		m_strVentilazioneFr = pMonitoraggioSet->m_strVentilazioneFr;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreLocalizzazione) || bCopyAll)
		m_lDoloreLocalizzazione = pMonitoraggioSet->m_lDoloreLocalizzazione;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_sDoloreLocalizzazioneDettaglio) || bCopyAll)
		m_sDoloreLocalizzazioneDettaglio = pMonitoraggioSet->m_sDoloreLocalizzazioneDettaglio;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreCaratteristiche) || bCopyAll)
		m_lDoloreCaratteristiche = pMonitoraggioSet->m_lDoloreCaratteristiche;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreFrequenza) || bCopyAll)
		m_lDoloreFrequenza = pMonitoraggioSet->m_lDoloreFrequenza;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lDoloreDurata) || bCopyAll)
		m_lDoloreDurata = pMonitoraggioSet->m_lDoloreDurata;
	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_lRamsay) || bCopyAll)
		m_lRamsay = pMonitoraggioSet->m_lRamsay;

	if (!pMonitoraggioSet->IsOpen() || pMonitoraggioSet->IsFieldDirty(&pMonitoraggioSet->m_sIdEsterno) || bCopyAll)
		m_sIdEsterno = pMonitoraggioSet->m_sIdEsterno;
}

void CMonitoraggioSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMonitoraggioSet* pOV = (CMonitoraggioSet*)pOldValues;
	CMonitoraggioSet* pNV = (CMonitoraggioSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("Quando", pOV, &pOV->m_lQuando, pNV, &pNV->m_lQuando);
	sp.Execute("Ora", pOV, &pOV->m_strOra, pNV, &pNV->m_strOra);
	sp.Execute("Infermiere", pOV, &pOV->m_lIdInfermiere, pNV, &pNV->m_lIdInfermiere);
	sp.Execute("FC", pOV, &pOV->m_strFC, pNV, &pNV->m_strFC);
	sp.Execute("PA", pOV, &pOV->m_strPA, pNV, &pNV->m_strPA);
	sp.Execute("Sat", pOV, &pOV->m_strSat, pNV, &pNV->m_strSat);
	sp.Execute("O2", pOV, &pOV->m_strO2, pNV, &pNV->m_strO2);
	sp.Execute("Mida", pOV, &pOV->m_strMida, pNV, &pNV->m_strMida);
	sp.Execute("Peti", pOV, &pOV->m_strPeti, pNV, &pNV->m_strPeti);
	sp.Execute("Atro", pOV, &pOV->m_strAtro, pNV, &pNV->m_strAtro);
	sp.Execute("Nalo", pOV, &pOV->m_strNalo, pNV, &pNV->m_strNalo);
	sp.Execute("Flum", pOV, &pOV->m_strFlum, pNV, &pNV->m_strFlum);
	sp.Execute("Scop", pOV, &pOV->m_strScop, pNV, &pNV->m_strScop);
	sp.Execute("Gluc", pOV, &pOV->m_strGluc, pNV, &pNV->m_strGluc);
	sp.Execute("Altri", pOV, &pOV->m_strAltri, pNV, &pNV->m_strAltri);
	sp.Execute("Dolore", pOV, &pOV->m_lDoloreVAS, pNV, &pNV->m_lDoloreVAS);
	sp.Execute("DoloreNRS", pOV, &pOV->m_lDoloreNRS, pNV, &pNV->m_lDoloreNRS);
	sp.Execute("DoloreWB", pOV, &pOV->m_lDoloreWB, pNV, &pNV->m_lDoloreWB);
	sp.Execute("DoloreCCPO1", pOV, &pOV->m_lDoloreCCPO1, pNV, &pNV->m_lDoloreCCPO1);
	sp.Execute("DoloreCCPO2", pOV, &pOV->m_lDoloreCCPO2, pNV, &pNV->m_lDoloreCCPO2);
	sp.Execute("DoloreCCPO3", pOV, &pOV->m_lDoloreCCPO3, pNV, &pNV->m_lDoloreCCPO3);
	sp.Execute("DoloreCCPO4", pOV, &pOV->m_lDoloreCCPO4, pNV, &pNV->m_lDoloreCCPO4);
	sp.Execute("DoloreCCPO5", pOV, &pOV->m_lDoloreCCPO5, pNV, &pNV->m_lDoloreCCPO5);
	sp.Execute("PuntiScore1", pOV, &pOV->m_lPuntiScore1, pNV, &pNV->m_lPuntiScore1);
	sp.Execute("PuntiScore2", pOV, &pOV->m_lPuntiScore2, pNV, &pNV->m_lPuntiScore2);
	sp.Execute("PuntiScore3", pOV, &pOV->m_lPuntiScore3, pNV, &pNV->m_lPuntiScore3);
	sp.Execute("PuntiScore4", pOV, &pOV->m_lPuntiScore4, pNV, &pNV->m_lPuntiScore4);
	sp.Execute("TotalScore", pOV, &pOV->m_lTotalScore, pNV, &pNV->m_lTotalScore);
	sp.Execute("PuntiScore1Glasgow", pOV, &pOV->m_lPuntiScore1Glasgow, pNV, &pNV->m_lPuntiScore1Glasgow);
	sp.Execute("PuntiScore2Glasgow", pOV, &pOV->m_lPuntiScore2Glasgow, pNV, &pNV->m_lPuntiScore2Glasgow);
	sp.Execute("PuntiScore3Glasgow", pOV, &pOV->m_lPuntiScore3Glasgow, pNV, &pNV->m_lPuntiScore3Glasgow);
	sp.Execute("TotalScoreGlasgow", pOV, &pOV->m_lTotalScoreGlasgow, pNV, &pNV->m_lTotalScoreGlasgow);
	sp.Execute("IdPdf", pOV, &pOV->m_lIdPdf, pNV, &pNV->m_lIdPdf);
	sp.Execute("NotePdf", pOV, &pOV->m_sNotePdf, pNV, &pNV->m_sNotePdf);
	sp.Execute("Terminato", pOV, &pOV->m_bTerminato, pNV, &pNV->m_bTerminato);
	sp.Execute("IdSessione", pOV, &pOV->m_sIdSessione, pNV, &pNV->m_sIdSessione);
	sp.Execute("NomeStazione", pOV, &pOV->m_sNomeStazione, pNV, &pNV->m_sNomeStazione);
	sp.Execute("IdDispositivo", pOV, &pOV->m_lIdDispositivo, pNV, &pNV->m_lIdDispositivo);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);

	sp.Execute("FC_POLSO", pOV, &pOV->m_lFCPolso, pNV, &pNV->m_lFCPolso);
	sp.Execute("ETCO2", pOV, &pOV->m_strETCO2, pNV, &pNV->m_strETCO2);
	sp.Execute("INTUBAZIONE", pOV, &pOV->m_lIntubazione, pNV, &pNV->m_lIntubazione);
	sp.Execute("DOLORE_SCALA", pOV, &pOV->m_lDoloreScala, pNV, &pNV->m_lDoloreScala);
	sp.Execute("VENTILAZIONE", pOV, &pOV->m_lVentilazione, pNV, &pNV->m_lVentilazione);
	sp.Execute("VENTILAZIONE_VT", pOV, &pOV->m_strVentilazioneVt, pNV, &pNV->m_strVentilazioneVt);
	sp.Execute("VENTILAZIONE_FR", pOV, &pOV->m_strVentilazioneFr, pNV, &pNV->m_strVentilazioneFr);
	sp.Execute("DOLORE_LOCALIZZAZIONE", pOV, &pOV->m_lDoloreLocalizzazione, pNV, &pNV->m_lDoloreLocalizzazione);
	sp.Execute("DOLORE_LOCALIZZAZIONE_DETT", pOV, &pOV->m_sDoloreLocalizzazioneDettaglio, pNV, &pNV->m_sDoloreLocalizzazioneDettaglio);
	sp.Execute("DOLORE_CARATTERISTICHE", pOV, &pOV->m_lDoloreCaratteristiche, pNV, &pNV->m_lDoloreCaratteristiche);
	sp.Execute("DOLORE_FREQUENZA", pOV, &pOV->m_lDoloreFrequenza, pNV, &pNV->m_lDoloreFrequenza);
	sp.Execute("DOLORE_DURATA", pOV, &pOV->m_lDoloreDurata, pNV, &pNV->m_lDoloreDurata);
	sp.Execute("RAMSEY", pOV, &pOV->m_lRamsay, pNV, &pNV->m_lRamsay);	
	
	sp.Execute("IDESTERNO", pOV, &pOV->m_sIdEsterno, pNV, &pNV->m_sIdEsterno);
}

BOOL CMonitoraggioSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMonitoraggioSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMonitoraggioSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMonitoraggioSet::SetBaseFilter(const CString &strFilter)
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

long CMonitoraggioSet::GetIdEsame(long id)
{
	long lReturn = 0;

	CString filter;
	filter.Format("id=%li", id);

	SetOpenFilter(filter);

	if (OpenRecordset("CVitalSignDispositiviSet::GetDescrizione"))
	{
		if (!IsEOF())
			lReturn = m_lIDEsame;

		CloseRecordset("CVitalSignDispositiviSet::GetDescrizione");
	}

	return lReturn;
}

void CMonitoraggioSet::CopyFrom(CMonitoraggioSet* pSourceSet)
{
	long tempIdEsame = m_lIDEsame;
	CopyFields(pSourceSet, TRUE);
	m_lIDEsame = tempIdEsame;
	SetFieldNull(&m_sIdEsterno);
}