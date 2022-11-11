#include "stdafx.h"
#include "Endox.h"
#include "InterventiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInterventiSet, CBaseSet)

CInterventiSet::CInterventiSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore	= 0;
	m_lIdEsame		= 0;
	m_lData			= 0;
	m_lOraInizio	= 0;
	m_lOraFine		= 0;
	m_sOperatori	= "";	//  255
	m_sAnestesisti	= "";	//  255
	m_sStrumentisti	= "";	//  255
	m_sAnestesia	= "";	//  255
	m_sDiagnosi		= "";	// 3999
	m_sIntervento	= "";	// 3999
	m_bEliminato    = FALSE;

	m_nFields = 12;
	SetBaseFilter("");
}

CString CInterventiSet::GetDefaultSQL()
{
	return "EINTERVENTI";
}

void CInterventiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "IdEsame",		m_lIdEsame);
		RFX_Long (pFX, "Data",			m_lData);
		RFX_Long (pFX, "OraInizio",		m_lOraInizio);
		RFX_Long (pFX, "OraFine",		m_lOraFine);
		RFX_Text (pFX, "Operatori",		m_sOperatori,	 255);
		RFX_Text (pFX, "Anestesisti",	m_sAnestesisti,	 255);
		RFX_Text (pFX, "Strumentisti",	m_sStrumentisti, 255);
		RFX_Text (pFX, "Anestesia",		m_sAnestesia,	 255);
		RFX_Text (pFX, "Diagnosi",		m_sDiagnosi,	3999);
		RFX_Text (pFX, "Intervento",	m_sIntervento,	3999);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

void CInterventiSet::SetEmpty()
{
	m_lContatore	= 0;
	m_lIdEsame		= 0;
	m_lData			= 0;
	m_lOraInizio	= 0;
	m_lOraFine		= 0;
	m_sOperatori	= "";	//  255
	m_sAnestesisti	= "";	//  255
	m_sStrumentisti	= "";	//  255
	m_sAnestesia	= "";	//  255
	m_sDiagnosi		= "";	// 3999
	m_sIntervento	= "";	// 3999
	m_bEliminato    = FALSE;
}

CBaseSet* CInterventiSet::CreateNew()
{
	return (CBaseSet*)new CInterventiSet;
}

void CInterventiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CInterventiSet* pInterventiSet = (CInterventiSet*)pOriginalSet;

	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pInterventiSet->m_lIdEsame;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_lData) || bCopyAll)
		m_lData = pInterventiSet->m_lData;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_lOraInizio) || bCopyAll)
		m_lOraInizio = pInterventiSet->m_lOraInizio;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_lOraFine) || bCopyAll)
		m_lOraFine = pInterventiSet->m_lOraFine;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_sOperatori) || bCopyAll)
		m_sOperatori = pInterventiSet->m_sOperatori;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_sAnestesisti) || bCopyAll)
		m_sAnestesisti = pInterventiSet->m_sAnestesisti;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_sStrumentisti) || bCopyAll)
		m_sStrumentisti = pInterventiSet->m_sStrumentisti;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_sAnestesia) || bCopyAll)
		m_sAnestesia = pInterventiSet->m_sAnestesia;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_sDiagnosi) || bCopyAll)
		m_sDiagnosi = pInterventiSet->m_sDiagnosi;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_sIntervento) || bCopyAll)
		m_sIntervento = pInterventiSet->m_sIntervento;
	if (!pInterventiSet->IsOpen() || pInterventiSet->IsFieldDirty(&pInterventiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pInterventiSet->m_bEliminato;
}

void CInterventiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CInterventiSet* pOV = (CInterventiSet*)pOldValues;
	CInterventiSet* pNV = (CInterventiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("Data", pOV, &pOV->m_lData, pNV, &pNV->m_lData);
	sp.Execute("OraInizio", pOV, &pOV->m_lOraInizio, pNV, &pNV->m_lOraInizio);
	sp.Execute("OraFine", pOV, &pOV->m_lOraFine, pNV, &pNV->m_lOraFine);
	sp.Execute("Operatori", pOV, &pOV->m_sOperatori, pNV, &pNV->m_sOperatori);
	sp.Execute("Anestesisti", pOV, &pOV->m_sAnestesisti, pNV, &pNV->m_sAnestesisti);
	sp.Execute("Strumentisti", pOV, &pOV->m_sStrumentisti, pNV, &pNV->m_sStrumentisti);
	sp.Execute("Anestesia", pOV, &pOV->m_sAnestesia, pNV, &pNV->m_sAnestesia);
	sp.Execute("Diagnosi", pOV, &pOV->m_sDiagnosi, pNV, &pNV->m_sDiagnosi);
	sp.Execute("Intervento", pOV, &pOV->m_sIntervento, pNV, &pNV->m_sIntervento);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CInterventiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CInterventiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CInterventiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CInterventiSet::SetBaseFilter(const CString &strFilter)
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