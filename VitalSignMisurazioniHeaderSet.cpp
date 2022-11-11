#include "stdafx.h"
#include "Endox.h"
#include "VitalSignMisurazioniHeaderSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVitalSignMisurazioniHeaderSet, CBaseSet)

CVitalSignMisurazioniHeaderSet::CVitalSignMisurazioniHeaderSet()
: CBaseSet(&m_lID, "ID")
{
	SetEmpty();
	SetSortRecord("ID");
	SetBaseFilter("");

	m_nFields = 14;
}

CString CVitalSignMisurazioniHeaderSet::GetDefaultSQL()
{
	return "VITALSIGN_MISURAZIONI_HEADER";
}

void CVitalSignMisurazioniHeaderSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Long(pFX, "IDESAME", m_lIDEsame);
	RFX_Text(pFX, "IDSESSIONEVITALSIGN", m_sIDSessioneVitalSign, 255);
	RFX_Long(pFX, "FASE", (long&) m_lFase);
	RFX_Text(pFX, "ORA", m_sOra, 8);
	RFX_Text(pFX, "FC_MEDIA", m_sFCMedia);
	RFX_Text(pFX, "PA_MEDIA", m_sPAMedia);
	RFX_Text(pFX, "SAT_MEDIA", m_sSatMedia);
	RFX_Long(pFX, "IDPDF", m_lIDPdf);
	RFX_Text(pFX, "NOTE", m_sNote, 1000000);
	RFX_Bool(pFX, "TERMINATO", m_bTerminato);
	RFX_Text(pFX, "NOMESTAZIONE", m_sNomeStazione);
	RFX_Long(pFX, "IDDISPOSITIVO", m_lIDDispositivo);
	RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
}

void CVitalSignMisurazioniHeaderSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sIDSessioneVitalSign = "";
	m_lFase = MonitoringPhase::pre;
	m_sOra = "";
	m_sFCMedia = "";
	m_sPAMedia = "";
	m_sSatMedia = "";
	m_lIDPdf = 0;
	m_sNote = "";
	m_bTerminato = FALSE;
	m_sNomeStazione = "";
	m_lIDDispositivo = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CVitalSignMisurazioniHeaderSet::CreateNew()
{
	return (CBaseSet*)new CVitalSignMisurazioniHeaderSet;
}

void CVitalSignMisurazioniHeaderSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CVitalSignMisurazioniHeaderSet* pSet = (CVitalSignMisurazioniHeaderSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIDSessioneVitalSign) || bCopyAll)
		m_sIDSessioneVitalSign = pSet->m_sIDSessioneVitalSign;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lFase) || bCopyAll)
		m_lFase = pSet->m_lFase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sOra) || bCopyAll)
		m_sOra = pSet->m_sOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFCMedia) || bCopyAll)
		m_sFCMedia = pSet->m_sFCMedia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPAMedia) || bCopyAll)
		m_sPAMedia = pSet->m_sPAMedia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSatMedia) || bCopyAll)
		m_sSatMedia = pSet->m_sSatMedia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPdf) || bCopyAll)
		m_lIDPdf = pSet->m_lIDPdf;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNote) || bCopyAll)
		m_sNote = pSet->m_sNote;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bTerminato) || bCopyAll)
		m_bTerminato = pSet->m_bTerminato;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNomeStazione) || bCopyAll)
		m_sNomeStazione = pSet->m_sNomeStazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDDispositivo) || bCopyAll)
		m_lIDDispositivo = pSet->m_lIDDispositivo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CVitalSignMisurazioniHeaderSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CVitalSignMisurazioniHeaderSet* pOV = (CVitalSignMisurazioniHeaderSet*)pOldValues;
	CVitalSignMisurazioniHeaderSet* pNV = (CVitalSignMisurazioniHeaderSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDSESSIONEVITALSIGN", pOV, &pOV->m_sIDSessioneVitalSign, pNV, &pNV->m_sIDSessioneVitalSign);
	sp.Execute("FASE", pOV, (long*) &pOV->m_lFase, pNV, (long*) &pNV->m_lFase);
	sp.Execute("ORA", pOV, &pOV->m_sOra, pNV, &pNV->m_sOra);
	sp.Execute("FC_MEDIA", pOV, &pOV->m_sFCMedia, pNV, &pNV->m_sFCMedia);
	sp.Execute("PA_MEDIA", pOV, &pOV->m_sPAMedia, pNV, &pNV->m_sPAMedia);
	sp.Execute("SAT_MEDIA", pOV, &pOV->m_sSatMedia, pNV, &pNV->m_sSatMedia);
	sp.Execute("IDPDF", pOV, &pOV->m_lIDPdf, pNV, &pNV->m_lIDPdf);
	sp.Execute("NOTE", pOV, &pOV->m_sNote, pNV, &pNV->m_sNote);
	sp.Execute("TERMINATO", pOV, &pOV->m_bTerminato, pNV, &pNV->m_bTerminato);
	sp.Execute("NOMESTAZIONE", pOV, &pOV->m_sNomeStazione, pNV, &pNV->m_sNomeStazione);
	sp.Execute("IDDISPOSITIVO", pOV, &pOV->m_lIDDispositivo, pNV, &pNV->m_lIDDispositivo);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CVitalSignMisurazioniHeaderSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CVitalSignMisurazioniHeaderSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CVitalSignMisurazioniHeaderSet::DeleteRecordset");
	}
	return bReturn;
}

CString CVitalSignMisurazioniHeaderSet::SetBaseFilter(const CString &strFilter)
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

long CVitalSignMisurazioniHeaderSet::GetIdEsame(long id)
{
	long lReturn = 0;

	CString filter;
	filter.Format("ID=%li", id);

	SetOpenFilter(filter);

	if (OpenRecordset("CVitalSignMisurazioniHeaderSet::GetDescrizione"))
	{
		if (!IsEOF())
			lReturn = m_lIDEsame;

		CloseRecordset("CVitalSignDispositiviSet::GetDescrizione");
	}

	return lReturn;
}