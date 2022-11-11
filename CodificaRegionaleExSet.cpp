#include "stdafx.h"
#include "Endox.h"
#include "CodificaRegionaleExSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCodificaRegionaleExSet, CBaseSet)

CCodificaRegionaleExSet::CCodificaRegionaleExSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 42;
}

CString CCodificaRegionaleExSet::GetDefaultSQL()
{
	return "ECODIFICAREGIONALEEX";
}

void CCodificaRegionaleExSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "CodiceNazionale", m_sCodiceNazionale, 50);
		RFX_Text(pFX, "CodiceRegionale", m_sCodiceRegionale, 50);
		RFX_Text(pFX, "CodiceSiss", m_sCodiceSiss, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);

		RFX_Single(pFX, "EndoscopistaNumero", m_fEndoscopistaNumero);
		RFX_Single(pFX, "EndoscopistaMinuti", m_fEndoscopistaMinuti);
		RFX_Single(pFX, "EndoscopistaCosto", m_fEndoscopistaCosto);
		RFX_Single(pFX, "AnestesistaNumero", m_fAnestesistaNumero);
		RFX_Single(pFX, "AnestesistaMinuti", m_fAnestesistaMinuti);
		RFX_Single(pFX, "AnestesistaCosto", m_fAnestesistaCosto);
		RFX_Single(pFX, "RadiologoNumero", m_fRadiologoNumero);
		RFX_Single(pFX, "RadiologoMinuti", m_fRadiologoMinuti);
		RFX_Single(pFX, "RadiologoCosto", m_fRadiologoCosto);
		RFX_Single(pFX, "InfermiereNumero", m_fInfermiereNumero);
		RFX_Single(pFX, "InfermiereMinuti", m_fInfermiereMinuti);
		RFX_Single(pFX, "InfermiereCosto", m_fInfermiereCosto);
		RFX_Single(pFX, "OtaaNumero", m_fOtaaNumero);
		RFX_Single(pFX, "OtaaMinuti", m_fOtaaMinuti);
		RFX_Single(pFX, "OtaaCosto", m_fOtaaCosto);
		RFX_Single(pFX, "AmministrativoNumero", m_fAmministrativoNumero);
		RFX_Single(pFX, "AmministrativoMinuti", m_fAmministrativoMinuti);
		RFX_Single(pFX, "AmministrativoCosto", m_fAmministrativoCosto);
		RFX_Single(pFX, "TotaleCostoPersonale", m_fTotaleCostoPersonale);

		RFX_Single(pFX, "TotaleCostoMateriali", m_fTotaleCostoMateriali);

		RFX_Single(pFX, "ManutenzioneDedicata", m_fManutenzioneDedicata);
		RFX_Single(pFX, "ManutenzioneBase", m_fManutenzioneBase);
		RFX_Single(pFX, "TotaleCostoManutenzione", m_fTotaleCostoManutenzione);

		RFX_Single(pFX, "AmmortamentoDedicata", m_fAmmortamentoDedicata);
		RFX_Single(pFX, "AmmortamentoBase", m_fAmmortamentoBase);
		RFX_Single(pFX, "TotaleCostoAmmortamento", m_fTotaleCostoAmmortamento);

		RFX_Single(pFX, "TotaleCostiGenerali", m_fTotaleCostiGenerali);

		RFX_Single(pFX, "TotaleGlobale", m_fTotaleGlobale);

		RFX_Single(pFX, "RimborsoRegionale", m_fRimborsoRegionale);

		RFX_Text(pFX, "CodiceIntegrazione", m_sCodiceIntegrazione, 50);
		RFX_Text(pFX, "CodiceDicom", m_sCodiceDicom, 255);
		RFX_Long(pFX, "IDTipoEsameEndox", m_lIDTipoEsameEndox);
		RFX_Bool(pFX, "PrestazionePrincipale", m_bPrestazionePrincipale);

		RFX_Bool(pFX, "Normata", m_bNormata);
		RFX_Bool(pFX, "PNGLA", m_bPNGLA);

		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCodificaRegionaleExSet::SetEmpty()
{
	m_lContatore = 0;

	m_sCodiceNazionale = "";
	m_sCodiceRegionale = "";
	m_sCodiceSiss = "";
	m_sDescrizione = "";

	m_fEndoscopistaNumero = 0.0f;
	m_fEndoscopistaMinuti = 0.0f;
	m_fEndoscopistaCosto = 0.0f;
	m_fAnestesistaNumero = 0.0f;
	m_fAnestesistaMinuti = 0.0f;
	m_fAnestesistaCosto = 0.0f;
	m_fRadiologoNumero = 0.0f;
	m_fRadiologoMinuti = 0.0f;
	m_fRadiologoCosto = 0.0f;
	m_fInfermiereNumero = 0.0f;
	m_fInfermiereMinuti = 0.0f;
	m_fInfermiereCosto = 0.0f;
	m_fOtaaNumero = 0.0f;
	m_fOtaaMinuti = 0.0f;
	m_fOtaaCosto = 0.0f;
	m_fAmministrativoNumero = 0.0f;
	m_fAmministrativoMinuti = 0.0f;
	m_fAmministrativoCosto = 0.0f;
	m_fTotaleCostoPersonale = 0.0f;

	m_fTotaleCostoMateriali = 0.0f;

	m_fManutenzioneDedicata = 0.0f;
	m_fManutenzioneBase = 0.0f;
	m_fTotaleCostoManutenzione = 0.0f;

	m_fAmmortamentoDedicata = 0.0f;
	m_fAmmortamentoBase = 0.0f;
	m_fTotaleCostoAmmortamento = 0.0f;

	m_fTotaleCostiGenerali = 0.0f;

	m_fTotaleGlobale = 0.0f;

	m_fRimborsoRegionale = 0.0f;

	m_sCodiceIntegrazione = "";
	m_sCodiceDicom = "";
	m_lIDTipoEsameEndox = 0;
	m_bPrestazionePrincipale = TRUE;

	m_bNormata = FALSE;
	m_bPNGLA = FALSE;

	m_lUO = 0;
	m_bEliminato = FALSE;
}

CString CCodificaRegionaleExSet::GetFieldText(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::GetFieldText"))
	{
		if (!IsEOF())
			strReturn = m_sCodiceNazionale + " " + m_sDescrizione;
		strReturn.Trim();

		CloseRecordset("CCodificaRegionaleExSet::GetFieldText");
	}

	return strReturn;
}

CString CCodificaRegionaleExSet::GetStringCodiceNazionale(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::GetStringCodiceNazionale"))
	{
		if (!IsEOF())
			strReturn = m_sCodiceNazionale;

		CloseRecordset("CCodificaRegionaleExSet::GetStringCodiceNazionale");
	}

	return strReturn;
}

CString CCodificaRegionaleExSet::GetStringCodiceRegionale(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::GetStringCodiceRegionale"))
	{
		if (!IsEOF())
			strReturn = m_sCodiceRegionale;

		CloseRecordset("CCodificaRegionaleExSet::GetStringCodiceRegionale");
	}

	return strReturn;
}

CString CCodificaRegionaleExSet::GetStringCodiceSiss(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::GetStringCodiceSiss"))
	{
		if (!IsEOF())
			strReturn = m_sCodiceSiss;

		CloseRecordset("CCodificaRegionaleExSet::GetStringCodiceSiss");
	}

	return strReturn;
}

CString CCodificaRegionaleExSet::GetStringCodiceIntegrazione(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::GetStringCodiceIntegrazione"))
	{
		if (!IsEOF())
			strReturn = m_sCodiceIntegrazione;

		CloseRecordset("CCodificaRegionaleExSet::GetStringCodiceIntegrazione");
	}

	return strReturn;
}

CString CCodificaRegionaleExSet::GetStringDescrizione(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::GetStringDescrizione"))
	{
		if (!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CCodificaRegionaleExSet::GetStringDescrizione");
	}

	return strReturn;
}

BOOL CCodificaRegionaleExSet::IsNormata(long lCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Contatore=%li", lCodice);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::IsNormata"))
	{
		if (!IsEOF())
			bReturn = m_bNormata;

		CloseRecordset("CCodificaRegionaleExSet::IsNormata");
	}

	return bReturn;
}

CBaseSet* CCodificaRegionaleExSet::CreateNew()
{
	return (CBaseSet*)new CCodificaRegionaleExSet;
}

void CCodificaRegionaleExSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCodificaRegionaleExSet* pSet = (CCodificaRegionaleExSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceNazionale) || bCopyAll)
		m_sCodiceNazionale = pSet->m_sCodiceNazionale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceRegionale) || bCopyAll)
		m_sCodiceRegionale = pSet->m_sCodiceRegionale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceSiss) || bCopyAll)
		m_sCodiceSiss = pSet->m_sCodiceSiss;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fEndoscopistaNumero) || bCopyAll)
		m_fEndoscopistaNumero = pSet->m_fEndoscopistaNumero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fEndoscopistaMinuti) || bCopyAll)
		m_fEndoscopistaMinuti = pSet->m_fEndoscopistaMinuti;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fEndoscopistaCosto) || bCopyAll)
		m_fEndoscopistaCosto = pSet->m_fEndoscopistaCosto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAnestesistaNumero) || bCopyAll)
		m_fAnestesistaNumero = pSet->m_fAnestesistaNumero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAnestesistaMinuti) || bCopyAll)
		m_fAnestesistaMinuti = pSet->m_fAnestesistaMinuti;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAnestesistaCosto) || bCopyAll)
		m_fAnestesistaCosto = pSet->m_fAnestesistaCosto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRadiologoNumero) || bCopyAll)
		m_fRadiologoNumero = pSet->m_fRadiologoNumero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRadiologoMinuti) || bCopyAll)
		m_fRadiologoMinuti = pSet->m_fRadiologoMinuti;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRadiologoCosto) || bCopyAll)
		m_fRadiologoCosto = pSet->m_fRadiologoCosto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fInfermiereNumero) || bCopyAll)
		m_fInfermiereNumero = pSet->m_fInfermiereNumero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fInfermiereMinuti) || bCopyAll)
		m_fInfermiereMinuti = pSet->m_fInfermiereMinuti;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fInfermiereCosto) || bCopyAll)
		m_fInfermiereCosto = pSet->m_fInfermiereCosto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fOtaaNumero) || bCopyAll)
		m_fOtaaNumero = pSet->m_fOtaaNumero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fOtaaMinuti) || bCopyAll)
		m_fOtaaMinuti = pSet->m_fOtaaMinuti;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fOtaaCosto) || bCopyAll)
		m_fOtaaCosto = pSet->m_fOtaaCosto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAmministrativoNumero) || bCopyAll)
		m_fAmministrativoNumero = pSet->m_fAmministrativoNumero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAmministrativoMinuti) || bCopyAll)
		m_fAmministrativoMinuti = pSet->m_fAmministrativoMinuti;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAmministrativoCosto) || bCopyAll)
		m_fAmministrativoCosto = pSet->m_fAmministrativoCosto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fTotaleCostoPersonale) || bCopyAll)
		m_fTotaleCostoPersonale = pSet->m_fTotaleCostoPersonale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fTotaleCostoMateriali) || bCopyAll)
		m_fTotaleCostoMateriali = pSet->m_fTotaleCostoMateriali;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fManutenzioneDedicata) || bCopyAll)
		m_fManutenzioneDedicata = pSet->m_fManutenzioneDedicata;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fManutenzioneBase) || bCopyAll)
		m_fManutenzioneBase = pSet->m_fManutenzioneBase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fTotaleCostoManutenzione) || bCopyAll)
		m_fTotaleCostoManutenzione = pSet->m_fTotaleCostoManutenzione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAmmortamentoDedicata) || bCopyAll)
		m_fAmmortamentoDedicata = pSet->m_fAmmortamentoDedicata;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fAmmortamentoBase) || bCopyAll)
		m_fAmmortamentoBase = pSet->m_fAmmortamentoBase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fTotaleCostoAmmortamento) || bCopyAll)
		m_fTotaleCostoAmmortamento = pSet->m_fTotaleCostoAmmortamento;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fTotaleCostiGenerali) || bCopyAll)
		m_fTotaleCostiGenerali = pSet->m_fTotaleCostiGenerali;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fTotaleGlobale) || bCopyAll)
		m_fTotaleGlobale = pSet->m_fTotaleGlobale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRimborsoRegionale) || bCopyAll)
		m_fRimborsoRegionale = pSet->m_fRimborsoRegionale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIntegrazione) || bCopyAll)
		m_sCodiceIntegrazione = pSet->m_sCodiceIntegrazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceDicom) || bCopyAll)
		m_sCodiceDicom = pSet->m_sCodiceDicom;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsameEndox) || bCopyAll)
		m_lIDTipoEsameEndox = pSet->m_lIDTipoEsameEndox;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPrestazionePrincipale) || bCopyAll)
		m_bPrestazionePrincipale = pSet->m_bPrestazionePrincipale;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bNormata) || bCopyAll)
		m_bNormata = pSet->m_bNormata;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPNGLA) || bCopyAll)
		m_bPNGLA = pSet->m_bPNGLA;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCodificaRegionaleExSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCodificaRegionaleExSet* pOV = (CCodificaRegionaleExSet*)pOldValues;
	CCodificaRegionaleExSet* pNV = (CCodificaRegionaleExSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("CodiceNazionale", pOV, &pOV->m_sCodiceNazionale, pNV, &pNV->m_sCodiceNazionale);
	sp.Execute("CodiceRegionale", pOV, &pOV->m_sCodiceRegionale, pNV, &pNV->m_sCodiceRegionale);
	sp.Execute("CodiceSiss", pOV, &pOV->m_sCodiceSiss, pNV, &pNV->m_sCodiceSiss);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("EndoscopistaNumero", pOV, &pOV->m_fEndoscopistaNumero, pNV, &pNV->m_fEndoscopistaNumero);
	sp.Execute("EndoscopistaMinuti", pOV, &pOV->m_fEndoscopistaMinuti, pNV, &pNV->m_fEndoscopistaMinuti);
	sp.Execute("EndoscopistaCosto", pOV, &pOV->m_fEndoscopistaCosto, pNV, &pNV->m_fEndoscopistaCosto);
	sp.Execute("AnestesistaNumero", pOV, &pOV->m_fAnestesistaNumero, pNV, &pNV->m_fAnestesistaNumero);
	sp.Execute("AnestesistaMinuti", pOV, &pOV->m_fAnestesistaMinuti, pNV, &pNV->m_fAnestesistaMinuti);
	sp.Execute("AnestesistaCosto", pOV, &pOV->m_fAnestesistaCosto, pNV, &pNV->m_fAnestesistaCosto);
	sp.Execute("RadiologoNumero", pOV, &pOV->m_fRadiologoNumero, pNV, &pNV->m_fRadiologoNumero);
	sp.Execute("RadiologoMinuti", pOV, &pOV->m_fRadiologoMinuti, pNV, &pNV->m_fRadiologoMinuti);
	sp.Execute("RadiologoCosto", pOV, &pOV->m_fRadiologoCosto, pNV, &pNV->m_fRadiologoCosto);
	sp.Execute("InfermiereNumero", pOV, &pOV->m_fInfermiereNumero, pNV, &pNV->m_fInfermiereNumero);
	sp.Execute("InfermiereMinuti", pOV, &pOV->m_fInfermiereMinuti, pNV, &pNV->m_fInfermiereMinuti);
	sp.Execute("InfermiereCosto", pOV, &pOV->m_fInfermiereCosto, pNV, &pNV->m_fInfermiereCosto);
	sp.Execute("OtaaNumero", pOV, &pOV->m_fOtaaNumero, pNV, &pNV->m_fOtaaNumero);
	sp.Execute("OtaaMinuti", pOV, &pOV->m_fOtaaMinuti, pNV, &pNV->m_fOtaaMinuti);
	sp.Execute("OtaaCosto", pOV, &pOV->m_fOtaaCosto, pNV, &pNV->m_fOtaaCosto);
	sp.Execute("AmministrativoNumero", pOV, &pOV->m_fAmministrativoNumero, pNV, &pNV->m_fAmministrativoNumero);
	sp.Execute("AmministrativoMinuti", pOV, &pOV->m_fAmministrativoMinuti, pNV, &pNV->m_fAmministrativoMinuti);
	sp.Execute("AmministrativoCosto", pOV, &pOV->m_fAmministrativoCosto, pNV, &pNV->m_fAmministrativoCosto);
	sp.Execute("TotaleCostoPersonale", pOV, &pOV->m_fTotaleCostoPersonale, pNV, &pNV->m_fTotaleCostoPersonale);
	sp.Execute("TotaleCostoMateriali", pOV, &pOV->m_fTotaleCostoMateriali, pNV, &pNV->m_fTotaleCostoMateriali);
	sp.Execute("ManutenzioneDedicata", pOV, &pOV->m_fManutenzioneDedicata, pNV, &pNV->m_fManutenzioneDedicata);
	sp.Execute("ManutenzioneBase", pOV, &pOV->m_fManutenzioneBase, pNV, &pNV->m_fManutenzioneBase);
	sp.Execute("TotaleCostoManutenzione", pOV, &pOV->m_fTotaleCostoManutenzione, pNV, &pNV->m_fTotaleCostoManutenzione);
	sp.Execute("AmmortamentoDedicata", pOV, &pOV->m_fAmmortamentoDedicata, pNV, &pNV->m_fAmmortamentoDedicata);
	sp.Execute("AmmortamentoBase", pOV, &pOV->m_fAmmortamentoBase, pNV, &pNV->m_fAmmortamentoBase);
	sp.Execute("TotaleCostoAmmortamento", pOV, &pOV->m_fTotaleCostoAmmortamento, pNV, &pNV->m_fTotaleCostoAmmortamento);
	sp.Execute("TotaleCostiGenerali", pOV, &pOV->m_fTotaleCostiGenerali, pNV, &pNV->m_fTotaleCostiGenerali);
	sp.Execute("TotaleGlobale", pOV, &pOV->m_fTotaleGlobale, pNV, &pNV->m_fTotaleGlobale);
	sp.Execute("RimborsoRegionale", pOV, &pOV->m_fRimborsoRegionale, pNV, &pNV->m_fRimborsoRegionale);
	sp.Execute("CodiceIntegrazione", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("CodiceDicom", pOV, &pOV->m_sCodiceDicom, pNV, &pNV->m_sCodiceDicom);
	sp.Execute("IDTipoEsameEndox", pOV, &pOV->m_lIDTipoEsameEndox, pNV, &pNV->m_lIDTipoEsameEndox);
	sp.Execute("PrestazionePrincipale", pOV, &pOV->m_bPrestazionePrincipale, pNV, &pNV->m_bPrestazionePrincipale);
	sp.Execute("Normata", pOV, &pOV->m_bNormata, pNV, &pNV->m_bNormata);
	sp.Execute("PNGLA", pOV, &pOV->m_bPNGLA, pNV, &pNV->m_bPNGLA);

	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCodificaRegionaleExSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCodificaRegionaleExSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCodificaRegionaleExSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCodificaRegionaleExSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CCodificaRegionaleExSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

//Gabriel BUG 6225 - Lista DO
void CCodificaRegionaleExSet::GetListaCodice(CList<CString>& pLista)
{
	CString strFilter;

	SetOpenFilter(strFilter);

	if (OpenRecordset("CCodificaRegionaleExSet::GetListaCodice"))
	{
		while (!IsEOF())
		{
			pLista.AddTail(m_sCodiceIntegrazione);
			MoveNext();
		}

		CloseRecordset("CCodificaRegionaleExSet::GetListaCodice");
	}
}

//Gabriel BUG 6225 - Lista DO
long CCodificaRegionaleExSet::GetContatore(CString sCodiceIntegrazione)
{
	long lReturn = -1;

	CString strFilter;
	strFilter.Format("CodiceIntegrazione='%s'", sCodiceIntegrazione);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleExSet::GetContatore"))
	{
		if (!IsEOF())
			lReturn = m_lContatore;

		CloseRecordset("CCodificaRegionaleExSet::GetContatore");
	}

	return lReturn;
}