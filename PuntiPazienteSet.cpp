#include "stdafx.h"
#include "Endox.h"
#include "PuntiPazienteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPuntiPazienteSet, CBaseSet)

CPuntiPazienteSet::CPuntiPazienteSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 63;
}

CString CPuntiPazienteSet::GetDefaultSQL()
{
	return "PuntiPaziente";
}

void CPuntiPazienteSet::SetEmpty()
{
	m_lID = 0;
	m_lIDPaziente = 0;
	m_lX = 0;
	m_lY = 0;
	m_sSede = "";
	m_lPattern = 0;
	m_bSemioticaA = FALSE;
	m_bSemioticaB = FALSE;
	m_bSemioticaC = FALSE;
	m_bSemioticaD = FALSE;
	m_bReticoloPigmentario = FALSE;
	m_lReticoloPigmentarioColore = 0;
	m_lReticoloPigmentarioDistanza = 0;
	m_lReticoloPigmentarioSpessore = 0;
	m_bVenatureRamificate = FALSE;
	m_bPigmentazioneDiffusa = FALSE;
	m_lPigmentazioneDiffusaDistrib = 0;
	m_bGlobuliMarroni = FALSE;
	m_lGlobuliMarroniForma = 0;
	m_lGlobuliMarroniSede = 0;
	m_bPuntiPigmentati = FALSE;
	m_bPuntiNeri = FALSE;
	m_lPuntiNeriDistribuzione = 0;
	m_lPuntiNeriSede = 0;
	m_lPuntiNeriCalibro = 0;
	m_bVeloBiancastro = FALSE;
	m_bDepigmentazione = FALSE;
	m_lDepigmentazioneDistribuzione = 0;
	m_lDepigmentazioneSede = 0;
	m_bDepigmentazioneReticolare = FALSE;
	m_bAreeDepigmentate = FALSE;
	m_bAreeGrigieBlu = FALSE;
	m_bFlussiRadiali = FALSE;
	m_bPseudopodi = FALSE;
	m_bBlocchiNeri = FALSE;
	m_bCistiMiliaLike = FALSE;
	m_bPeppering = FALSE;
	m_bAreaFogliaAcero = FALSE;
	m_bLaghiVascolari = FALSE;
	m_bAsportazione = FALSE;
	m_lDiagnosiIstologica = 0;
	m_sNotizieAccessorie = "";
	m_sDiagnosiEpimicroscopica = "";
	m_lTumoriMelanociticiBenigni1 = 0;
	m_lTumoriMelanociticiMaligni1 = 0;
	m_lTumoriNonMelanociticiEpitel1 = 0;
	m_lTumoriNonMelanociticiVascol1 = 0;
	m_sDiagnosiClinicaAltre = "";
	m_bEsameIstologico = FALSE;
	m_sRefertoNumero = "";
	m_sRefertoData = "";
	m_lTumoriMelanociticiBenigni2 = 0;
	m_sDiagnosiIstologicaAltro1 = "";
	m_lTumoriMelanociticiMaligni2 = 0;
	m_sSpessoreDiBreslow = "";
	m_lLivelloDiClark = 0;
	m_sDiagnosiIstologicaAltro2 = "";
	m_lTumoriNonMelanociticiEpitel2 = 0;
	m_lTumoriNonMelanociticiVascol2 = 0;
	m_sDiagnosiIstologicaAltro3 = "";
	m_lNumeroDermox = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CPuntiPazienteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
		RFX_Long(pFX, "X", m_lX);
		RFX_Long(pFX, "Y", m_lY);
		RFX_Text(pFX, "Sede", m_sSede, 255);
		RFX_Long(pFX, "Pattern", m_lPattern);
		RFX_Bool(pFX, "SemioticaA", m_bSemioticaA);
		RFX_Bool(pFX, "SemioticaB", m_bSemioticaB);
		RFX_Bool(pFX, "SemioticaC", m_bSemioticaC);
		RFX_Bool(pFX, "SemioticaD", m_bSemioticaD);
		RFX_Bool(pFX, "ReticoloPigmentario", m_bReticoloPigmentario);
		RFX_Long(pFX, "ReticoloPigmentarioColore", m_lReticoloPigmentarioColore);
		RFX_Long(pFX, "ReticoloPigmentarioDistanza", m_lReticoloPigmentarioDistanza);
		RFX_Long(pFX, "ReticoloPigmentarioSpessore", m_lReticoloPigmentarioSpessore);
		RFX_Bool(pFX, "VenatureRamificate", m_bVenatureRamificate);
		RFX_Bool(pFX, "PigmentazioneDiffusa", m_bPigmentazioneDiffusa);
		RFX_Long(pFX, "PigmentazioneDiffusaDistrib", m_lPigmentazioneDiffusaDistrib);
		RFX_Bool(pFX, "GlobuliMarroni", m_bGlobuliMarroni);
		RFX_Long(pFX, "GlobuliMarroniForma", m_lGlobuliMarroniForma);
		RFX_Long(pFX, "GlobuliMarroniSede", m_lGlobuliMarroniSede);
		RFX_Bool(pFX, "PuntiPigmentati", m_bPuntiPigmentati);
		RFX_Bool(pFX, "PuntiNeri", m_bPuntiNeri);
		RFX_Long(pFX, "PuntiNeriDistribuzione", m_lPuntiNeriDistribuzione);
		RFX_Long(pFX, "PuntiNeriSede", m_lPuntiNeriSede);
		RFX_Long(pFX, "PuntiNeriCalibro", m_lPuntiNeriCalibro);
		RFX_Bool(pFX, "VeloBiancastro", m_bVeloBiancastro);
		RFX_Bool(pFX, "Depigmentazione", m_bDepigmentazione);
		RFX_Long(pFX, "DepigmentazioneDistribuzione", m_lDepigmentazioneDistribuzione);
		RFX_Long(pFX, "DepigmentazioneSede", m_lDepigmentazioneSede);
		RFX_Bool(pFX, "DepigmentazioneReticolare", m_bDepigmentazioneReticolare);
		RFX_Bool(pFX, "AreeDepigmentate", m_bAreeDepigmentate);
		RFX_Bool(pFX, "AreeGrigieBlu", m_bAreeGrigieBlu);
		RFX_Bool(pFX, "FlussiRadiali", m_bFlussiRadiali);
		RFX_Bool(pFX, "Pseudopodi", m_bPseudopodi);
		RFX_Bool(pFX, "BlocchiNeri", m_bBlocchiNeri);
		RFX_Bool(pFX, "CistiMiliaLike", m_bCistiMiliaLike);
		RFX_Bool(pFX, "Peppering", m_bPeppering);
		RFX_Bool(pFX, "AreaFogliaAcero", m_bAreaFogliaAcero);
		RFX_Bool(pFX, "LaghiVascolari", m_bLaghiVascolari);
		RFX_Bool(pFX, "Asportazione", m_bAsportazione);
		RFX_Long(pFX, "DiagnosiIstologica", m_lDiagnosiIstologica);
		RFX_Text(pFX, "NotizieAccessorie", m_sNotizieAccessorie, 4000);
		RFX_Text(pFX, "DiagnosiEpimicroscopica", m_sDiagnosiEpimicroscopica, 4000);
		RFX_Long(pFX, "TumoriMelanociticiBenigni1", m_lTumoriMelanociticiBenigni1);
		RFX_Long(pFX, "TumoriMelanociticiMaligni1", m_lTumoriMelanociticiMaligni1);
		RFX_Long(pFX, "TumoriNonMelanociticiEpitel1", m_lTumoriNonMelanociticiEpitel1);
		RFX_Long(pFX, "TumoriNonMelanociticiVascol1", m_lTumoriNonMelanociticiVascol1);
		RFX_Text(pFX, "DiagnosiClinicaAltre", m_sDiagnosiClinicaAltre, 4000);
		RFX_Bool(pFX, "EsameIstologico", m_bEsameIstologico);
		RFX_Text(pFX, "RefertoNumero", m_sRefertoNumero, 50);
		RFX_Text(pFX, "RefertoData", m_sRefertoData, 50);
		RFX_Long(pFX, "TumoriMelanociticiBenigni2", m_lTumoriMelanociticiBenigni2);
		RFX_Text(pFX, "DiagnosiIstologicaAltro1", m_sDiagnosiIstologicaAltro1, 4000);
		RFX_Long(pFX, "TumoriMelanociticiMaligni2", m_lTumoriMelanociticiMaligni2);
		RFX_Text(pFX, "SpessoreDiBreslow", m_sSpessoreDiBreslow, 50);
		RFX_Long(pFX, "LivelloDiClark", m_lLivelloDiClark);
		RFX_Text(pFX, "DiagnosiIstologicaAltro2", m_sDiagnosiIstologicaAltro2, 4000);
		RFX_Long(pFX, "TumoriNonMelanociticiEpitel2", m_lTumoriNonMelanociticiEpitel2);
		RFX_Long(pFX, "TumoriNonMelanociticiVascol2", m_lTumoriNonMelanociticiVascol2);
		RFX_Text(pFX, "DiagnosiIstologicaAltro3", m_sDiagnosiIstologicaAltro3, 4000);
		RFX_Long(pFX, "NumeroDermox", m_lNumeroDermox);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CPuntiPazienteSet::CreateNew()
{
	return (CBaseSet*)new CPuntiPazienteSet;
}

void CPuntiPazienteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPuntiPazienteSet* pSet = (CPuntiPazienteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPaziente) || bCopyAll)
		m_lIDPaziente = pSet->m_lIDPaziente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lX) || bCopyAll)
		m_lX = pSet->m_lX;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lY) || bCopyAll)
		m_lY = pSet->m_lY;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSede) || bCopyAll)
		m_sSede = pSet->m_sSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPattern) || bCopyAll)
		m_lPattern = pSet->m_lPattern;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bSemioticaA) || bCopyAll)
		m_bSemioticaA = pSet->m_bSemioticaA;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bSemioticaB) || bCopyAll)
		m_bSemioticaB = pSet->m_bSemioticaB;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bSemioticaC) || bCopyAll)
		m_bSemioticaC = pSet->m_bSemioticaC;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bSemioticaD) || bCopyAll)
		m_bSemioticaD = pSet->m_bSemioticaD;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bReticoloPigmentario) || bCopyAll)
		m_bReticoloPigmentario = pSet->m_bReticoloPigmentario;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lReticoloPigmentarioColore) || bCopyAll)
		m_lReticoloPigmentarioColore = pSet->m_lReticoloPigmentarioColore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lReticoloPigmentarioDistanza) || bCopyAll)
		m_lReticoloPigmentarioDistanza = pSet->m_lReticoloPigmentarioDistanza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lReticoloPigmentarioSpessore) || bCopyAll)
		m_lReticoloPigmentarioSpessore = pSet->m_lReticoloPigmentarioSpessore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bVenatureRamificate) || bCopyAll)
		m_bVenatureRamificate = pSet->m_bVenatureRamificate;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPigmentazioneDiffusa) || bCopyAll)
		m_bPigmentazioneDiffusa = pSet->m_bPigmentazioneDiffusa;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPigmentazioneDiffusaDistrib) || bCopyAll)
		m_lPigmentazioneDiffusaDistrib = pSet->m_lPigmentazioneDiffusaDistrib;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bGlobuliMarroni) || bCopyAll)
		m_bGlobuliMarroni = pSet->m_bGlobuliMarroni;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lGlobuliMarroniForma) || bCopyAll)
		m_lGlobuliMarroniForma = pSet->m_lGlobuliMarroniForma;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lGlobuliMarroniSede) || bCopyAll)
		m_lGlobuliMarroniSede = pSet->m_lGlobuliMarroniSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPuntiPigmentati) || bCopyAll)
		m_bPuntiPigmentati = pSet->m_bPuntiPigmentati;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPuntiNeri) || bCopyAll)
		m_bPuntiNeri = pSet->m_bPuntiNeri;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPuntiNeriDistribuzione) || bCopyAll)
		m_lPuntiNeriDistribuzione = pSet->m_lPuntiNeriDistribuzione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPuntiNeriSede) || bCopyAll)
		m_lPuntiNeriSede = pSet->m_lPuntiNeriSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPuntiNeriCalibro) || bCopyAll)
		m_lPuntiNeriCalibro = pSet->m_lPuntiNeriCalibro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bVeloBiancastro) || bCopyAll)
		m_bVeloBiancastro = pSet->m_bVeloBiancastro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bDepigmentazione) || bCopyAll)
		m_bDepigmentazione = pSet->m_bDepigmentazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDepigmentazioneDistribuzione) || bCopyAll)
		m_lDepigmentazioneDistribuzione = pSet->m_lDepigmentazioneDistribuzione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDepigmentazioneSede) || bCopyAll)
		m_lDepigmentazioneSede = pSet->m_lDepigmentazioneSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bDepigmentazioneReticolare) || bCopyAll)
		m_bDepigmentazioneReticolare = pSet->m_bDepigmentazioneReticolare;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bAreeDepigmentate) || bCopyAll)
		m_bAreeDepigmentate = pSet->m_bAreeDepigmentate;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bAreeGrigieBlu) || bCopyAll)
		m_bAreeGrigieBlu = pSet->m_bAreeGrigieBlu;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bFlussiRadiali) || bCopyAll)
		m_bFlussiRadiali = pSet->m_bFlussiRadiali;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPseudopodi) || bCopyAll)
		m_bPseudopodi = pSet->m_bPseudopodi;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bBlocchiNeri) || bCopyAll)
		m_bBlocchiNeri = pSet->m_bBlocchiNeri;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bCistiMiliaLike) || bCopyAll)
		m_bCistiMiliaLike = pSet->m_bCistiMiliaLike;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPeppering) || bCopyAll)
		m_bPeppering = pSet->m_bPeppering;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bAreaFogliaAcero) || bCopyAll)
		m_bAreaFogliaAcero = pSet->m_bAreaFogliaAcero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bLaghiVascolari) || bCopyAll)
		m_bLaghiVascolari = pSet->m_bLaghiVascolari;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bAsportazione) || bCopyAll)
		m_bAsportazione = pSet->m_bAsportazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDiagnosiIstologica) || bCopyAll)
		m_lDiagnosiIstologica = pSet->m_lDiagnosiIstologica;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNotizieAccessorie) || bCopyAll)
		m_sNotizieAccessorie = pSet->m_sNotizieAccessorie;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDiagnosiEpimicroscopica) || bCopyAll)
		m_sDiagnosiEpimicroscopica = pSet->m_sDiagnosiEpimicroscopica;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriMelanociticiBenigni1) || bCopyAll)
		m_lTumoriMelanociticiBenigni1 = pSet->m_lTumoriMelanociticiBenigni1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriMelanociticiMaligni1) || bCopyAll)
		m_lTumoriMelanociticiMaligni1 = pSet->m_lTumoriMelanociticiMaligni1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriNonMelanociticiEpitel1) || bCopyAll)
		m_lTumoriNonMelanociticiEpitel1 = pSet->m_lTumoriNonMelanociticiEpitel1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriNonMelanociticiVascol1) || bCopyAll)
		m_lTumoriNonMelanociticiVascol1 = pSet->m_lTumoriNonMelanociticiVascol1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDiagnosiClinicaAltre) || bCopyAll)
		m_sDiagnosiClinicaAltre = pSet->m_sDiagnosiClinicaAltre;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEsameIstologico) || bCopyAll)
		m_bEsameIstologico = pSet->m_bEsameIstologico;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRefertoNumero) || bCopyAll)
		m_sRefertoNumero = pSet->m_sRefertoNumero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRefertoData) || bCopyAll)
		m_sRefertoData = pSet->m_sRefertoData;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriMelanociticiBenigni2) || bCopyAll)
		m_lTumoriMelanociticiBenigni2 = pSet->m_lTumoriMelanociticiBenigni2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDiagnosiIstologicaAltro1) || bCopyAll)
		m_sDiagnosiIstologicaAltro1 = pSet->m_sDiagnosiIstologicaAltro1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriMelanociticiMaligni2) || bCopyAll)
		m_lTumoriMelanociticiMaligni2 = pSet->m_lTumoriMelanociticiMaligni2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSpessoreDiBreslow) || bCopyAll)
		m_sSpessoreDiBreslow = pSet->m_sSpessoreDiBreslow;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lLivelloDiClark) || bCopyAll)
		m_lLivelloDiClark = pSet->m_lLivelloDiClark;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDiagnosiIstologicaAltro2) || bCopyAll)
		m_sDiagnosiIstologicaAltro2 = pSet->m_sDiagnosiIstologicaAltro2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriNonMelanociticiEpitel2) || bCopyAll)
		m_lTumoriNonMelanociticiEpitel2 = pSet->m_lTumoriNonMelanociticiEpitel2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTumoriNonMelanociticiVascol2) || bCopyAll)
		m_lTumoriNonMelanociticiVascol2 = pSet->m_lTumoriNonMelanociticiVascol2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDiagnosiIstologicaAltro3) || bCopyAll)
		m_sDiagnosiIstologicaAltro3 = pSet->m_sDiagnosiIstologicaAltro3;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lNumeroDermox) || bCopyAll)
		m_lNumeroDermox = pSet->m_lNumeroDermox;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CPuntiPazienteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPuntiPazienteSet* pOV = (CPuntiPazienteSet*)pOldValues;
	CPuntiPazienteSet* pNV = (CPuntiPazienteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDPaziente", pOV, &pOV->m_lIDPaziente, pNV, &pNV->m_lIDPaziente);
	sp.Execute("X", pOV, &pOV->m_lX, pNV, &pNV->m_lX);
	sp.Execute("Y", pOV, &pOV->m_lY, pNV, &pNV->m_lY);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Pattern", pOV, &pOV->m_lPattern, pNV, &pNV->m_lPattern);
	sp.Execute("SemioticaA", pOV, &pOV->m_bSemioticaA, pNV, &pNV->m_bSemioticaA);
	sp.Execute("SemioticaB", pOV, &pOV->m_bSemioticaB, pNV, &pNV->m_bSemioticaB);
	sp.Execute("SemioticaC", pOV, &pOV->m_bSemioticaC, pNV, &pNV->m_bSemioticaC);
	sp.Execute("SemioticaD", pOV, &pOV->m_bSemioticaD, pNV, &pNV->m_bSemioticaD);
	sp.Execute("ReticoloPigmentario", pOV, &pOV->m_bReticoloPigmentario, pNV, &pNV->m_bReticoloPigmentario);
	sp.Execute("ReticoloPigmentarioColore", pOV, &pOV->m_lReticoloPigmentarioColore, pNV, &pNV->m_lReticoloPigmentarioColore);
	sp.Execute("ReticoloPigmentarioDistanza", pOV, &pOV->m_lReticoloPigmentarioDistanza, pNV, &pNV->m_lReticoloPigmentarioDistanza);
	sp.Execute("ReticoloPigmentarioSpessore", pOV, &pOV->m_lReticoloPigmentarioSpessore, pNV, &pNV->m_lReticoloPigmentarioSpessore);
	sp.Execute("VenatureRamificate", pOV, &pOV->m_bVenatureRamificate, pNV, &pNV->m_bVenatureRamificate);
	sp.Execute("PigmentazioneDiffusa", pOV, &pOV->m_bPigmentazioneDiffusa, pNV, &pNV->m_bPigmentazioneDiffusa);
	sp.Execute("PigmentazioneDiffusaDistrib", pOV, &pOV->m_lPigmentazioneDiffusaDistrib, pNV, &pNV->m_lPigmentazioneDiffusaDistrib);
	sp.Execute("GlobuliMarroni", pOV, &pOV->m_bGlobuliMarroni, pNV, &pNV->m_bGlobuliMarroni);
	sp.Execute("GlobuliMarroniForma", pOV, &pOV->m_lGlobuliMarroniForma, pNV, &pNV->m_lGlobuliMarroniForma);
	sp.Execute("GlobuliMarroniSede", pOV, &pOV->m_lGlobuliMarroniSede, pNV, &pNV->m_lGlobuliMarroniSede);
	sp.Execute("PuntiPigmentati", pOV, &pOV->m_bPuntiPigmentati, pNV, &pNV->m_bPuntiPigmentati);
	sp.Execute("PuntiNeri", pOV, &pOV->m_bPuntiNeri, pNV, &pNV->m_bPuntiNeri);
	sp.Execute("PuntiNeriDistribuzione", pOV, &pOV->m_lPuntiNeriDistribuzione, pNV, &pNV->m_lPuntiNeriDistribuzione);
	sp.Execute("PuntiNeriSede", pOV, &pOV->m_lPuntiNeriSede, pNV, &pNV->m_lPuntiNeriSede);
	sp.Execute("PuntiNeriCalibro", pOV, &pOV->m_lPuntiNeriCalibro, pNV, &pNV->m_lPuntiNeriCalibro);
	sp.Execute("VeloBiancastro", pOV, &pOV->m_bVeloBiancastro, pNV, &pNV->m_bVeloBiancastro);
	sp.Execute("Depigmentazione", pOV, &pOV->m_bDepigmentazione, pNV, &pNV->m_bDepigmentazione);
	sp.Execute("DepigmentazioneDistribuzione", pOV, &pOV->m_lDepigmentazioneDistribuzione, pNV, &pNV->m_lDepigmentazioneDistribuzione);
	sp.Execute("DepigmentazioneSede", pOV, &pOV->m_lDepigmentazioneSede, pNV, &pNV->m_lDepigmentazioneSede);
	sp.Execute("DepigmentazioneReticolare", pOV, &pOV->m_bDepigmentazioneReticolare, pNV, &pNV->m_bDepigmentazioneReticolare);
	sp.Execute("AreeDepigmentate", pOV, &pOV->m_bAreeDepigmentate, pNV, &pNV->m_bAreeDepigmentate);
	sp.Execute("AreeGrigieBlu", pOV, &pOV->m_bAreeGrigieBlu, pNV, &pNV->m_bAreeGrigieBlu);
	sp.Execute("FlussiRadiali", pOV, &pOV->m_bFlussiRadiali, pNV, &pNV->m_bFlussiRadiali);
	sp.Execute("Pseudopodi", pOV, &pOV->m_bPseudopodi, pNV, &pNV->m_bPseudopodi);
	sp.Execute("BlocchiNeri", pOV, &pOV->m_bBlocchiNeri, pNV, &pNV->m_bBlocchiNeri);
	sp.Execute("CistiMiliaLike", pOV, &pOV->m_bCistiMiliaLike, pNV, &pNV->m_bCistiMiliaLike);
	sp.Execute("Peppering", pOV, &pOV->m_bPeppering, pNV, &pNV->m_bPeppering);
	sp.Execute("AreaFogliaAcero", pOV, &pOV->m_bAreaFogliaAcero, pNV, &pNV->m_bAreaFogliaAcero);
	sp.Execute("LaghiVascolari", pOV, &pOV->m_bLaghiVascolari, pNV, &pNV->m_bLaghiVascolari);
	sp.Execute("Asportazione", pOV, &pOV->m_bAsportazione, pNV, &pNV->m_bAsportazione);
	sp.Execute("DiagnosiIstologica", pOV, &pOV->m_lDiagnosiIstologica, pNV, &pNV->m_lDiagnosiIstologica);
	sp.Execute("NotizieAccessorie", pOV, &pOV->m_sNotizieAccessorie, pNV, &pNV->m_sNotizieAccessorie);
	sp.Execute("DiagnosiEpimicroscopica", pOV, &pOV->m_sDiagnosiEpimicroscopica, pNV, &pNV->m_sDiagnosiEpimicroscopica);
	sp.Execute("TumoriMelanociticiBenigni1", pOV, &pOV->m_lTumoriMelanociticiBenigni1, pNV, &pNV->m_lTumoriMelanociticiBenigni1);
	sp.Execute("TumoriMelanociticiMaligni1", pOV, &pOV->m_lTumoriMelanociticiMaligni1, pNV, &pNV->m_lTumoriMelanociticiMaligni1);
	sp.Execute("TumoriNonMelanociticiEpitel1", pOV, &pOV->m_lTumoriNonMelanociticiEpitel1, pNV, &pNV->m_lTumoriNonMelanociticiEpitel1);
	sp.Execute("TumoriNonMelanociticiVascol1", pOV, &pOV->m_lTumoriNonMelanociticiVascol1, pNV, &pNV->m_lTumoriNonMelanociticiVascol1);
	sp.Execute("DiagnosiClinicaAltre", pOV, &pOV->m_sDiagnosiClinicaAltre, pNV, &pNV->m_sDiagnosiClinicaAltre);
	sp.Execute("EsameIstologico", pOV, &pOV->m_bEsameIstologico, pNV, &pNV->m_bEsameIstologico);
	sp.Execute("RefertoNumero", pOV, &pOV->m_sRefertoNumero, pNV, &pNV->m_sRefertoNumero);
	sp.Execute("RefertoData", pOV, &pOV->m_sRefertoData, pNV, &pNV->m_sRefertoData);
	sp.Execute("TumoriMelanociticiBenigni2", pOV, &pOV->m_lTumoriMelanociticiBenigni2, pNV, &pNV->m_lTumoriMelanociticiBenigni2);
	sp.Execute("DiagnosiIstologicaAltro1", pOV, &pOV->m_sDiagnosiIstologicaAltro1, pNV, &pNV->m_sDiagnosiIstologicaAltro1);
	sp.Execute("TumoriMelanociticiMaligni2", pOV, &pOV->m_lTumoriMelanociticiMaligni2, pNV, &pNV->m_lTumoriMelanociticiMaligni2);
	sp.Execute("SpessoreDiBreslow", pOV, &pOV->m_sSpessoreDiBreslow, pNV, &pNV->m_sSpessoreDiBreslow);
	sp.Execute("LivelloDiClark", pOV, &pOV->m_lLivelloDiClark, pNV, &pNV->m_lLivelloDiClark);
	sp.Execute("DiagnosiIstologicaAltro2", pOV, &pOV->m_sDiagnosiIstologicaAltro2, pNV, &pNV->m_sDiagnosiIstologicaAltro2);
	sp.Execute("TumoriNonMelanociticiEpitel2", pOV, &pOV->m_lTumoriNonMelanociticiEpitel2, pNV, &pNV->m_lTumoriNonMelanociticiEpitel2);
	sp.Execute("TumoriNonMelanociticiVascol2", pOV, &pOV->m_lTumoriNonMelanociticiVascol2, pNV, &pNV->m_lTumoriNonMelanociticiVascol2);
	sp.Execute("DiagnosiIstologicaAltro3", pOV, &pOV->m_sDiagnosiIstologicaAltro3, pNV, &pNV->m_sDiagnosiIstologicaAltro3);
	sp.Execute("NumeroDermox", pOV, &pOV->m_lNumeroDermox, pNV, &pNV->m_lNumeroDermox);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CPuntiPazienteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPuntiPazienteSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CPuntiPazienteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CPuntiPazienteSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CPuntiPazienteSet::UpdateRecordset(const CString &strCommento)
{
	BOOL bReturn = FALSE;

	if (m_nEditMode == addnew)
	{
		m_lUO = theApp.m_lUO;
		bReturn = CBaseSet::UpdateRecordset(strCommento);

		if (bReturn)
		{
			CString strFilter;
			strFilter.Format("ID=%li", GetLastAdd());

			CPuntiPazienteSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset(strCommento))
			{
				if (!setTemp.IsEOF())
				{
					if (setTemp.EditRecordset(strCommento))
					{
						setTemp.m_lNumeroDermox = CPuntiPazienteSet().GetMaxNumeroDermox(setTemp.m_lIDPaziente) + 1;
						setTemp.UpdateRecordset(strCommento);
					}
				}

				setTemp.CloseRecordset(strCommento);
			}
		}
	}
	else
	{
		bReturn = CBaseSet::UpdateRecordset(strCommento);
	}
	
	return bReturn;
}

long CPuntiPazienteSet::GetMaxNumeroDermox(long lIDPaziente)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("IDPaziente=%li", lIDPaziente);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(strFilter);
	SetSortRecord("NumeroDermox DESC");
	if (OpenRecordset("CPuntiPazienteSet::GetMaxNumeroDermox"))
	{
		if (!IsEOF() && !IsFieldNull(&m_lNumeroDermox))
			lReturn = m_lNumeroDermox;

		CloseRecordset("CPuntiPazienteSet::GetMaxNumeroDermox");
	}

	return lReturn;
}

void CPuntiPazienteSet::GetSedeNumero(long lIDPunto, CString& sReturn, long& lReturn)
{
	sReturn = "";
	lReturn = -1;

	CString strFilter;
	strFilter.Format("ID=%li", lIDPunto);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CPuntiPazienteSet::GetSede"))
	{
		if (!IsEOF())
		{
			sReturn = m_sSede;
			lReturn = m_lNumeroDermox;
		}

		CloseRecordset("CPuntiPazienteSet::GetSede");
	}
}

void CPuntiPazienteSet::GetXYNumero(long lIDPunto, CPoint& ptReturn, long& lReturn)
{
	ptReturn = CPoint(-1, -1);
	lReturn = -1;

	CString strFilter;
	strFilter.Format("ID=%li", lIDPunto);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CPuntiPazienteSet::GetSede"))
	{
		if (!IsEOF())
		{
			ptReturn = CPoint(m_lX, m_lY);
			lReturn = m_lNumeroDermox;
		}

		CloseRecordset("CPuntiPazienteSet::GetSede");
	}
}