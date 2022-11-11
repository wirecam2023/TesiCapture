// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#include "stdafx.h"
#include "Endox.h"
#include "EesamiCodeesameSiglaVistaSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEesamiCodeesameSiglaVistaSet, CBaseSet)

CEesamiCodeesameSiglaVistaSet::CEesamiCodeesameSiglaVistaSet()
//: CBaseSet(&m_lCONTATORE, "CONTATORE")
: CBaseSet(NULL, "VIEW")
{
	//SetBaseFilter("ELIMINATO=0");
	SetEmpty();

	m_nFields = 4;
}

CString CEesamiCodeesameSiglaVistaSet::GetDefaultSQL()
{
	return "VISTA_EESAMI_CODESAME_SIGLA";
}

void CEesamiCodeesameSiglaVistaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "CONTATORE", m_lCONTATORE);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "UO"      , m_lUO);
		RFX_Text(pFX, "CODESAME", m_sCODESAME, 50);
		RFX_Text(pFX, "SIGLA"   , m_sSIGLA, 50);
	}
}

void CEesamiCodeesameSiglaVistaSet::SetEmpty()
{
	m_lUO = 0;
	m_sCODESAME = "";
	m_sSIGLA = "";
}

CBaseSet* CEesamiCodeesameSiglaVistaSet::CreateNew()
{
	return (CBaseSet*)new CEesamiCodeesameSiglaVistaSet;
}

void CEesamiCodeesameSiglaVistaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEesamiCodeesameSiglaVistaSet* pSet = (CEesamiCodeesameSiglaVistaSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCODESAME) || bCopyAll)
		m_sCODESAME = pSet->m_sCODESAME;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSIGLA) || bCopyAll)
		m_sSIGLA = pSet->m_sSIGLA;
}

void CEesamiCodeesameSiglaVistaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEesamiCodeesameSiglaVistaSet* pOV = (CEesamiCodeesameSiglaVistaSet*)pOldValues;
	CEesamiCodeesameSiglaVistaSet* pNV = (CEesamiCodeesameSiglaVistaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("UO"        , pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("CODESAME"  , pOV, &pOV->m_sCODESAME, pNV, &pNV->m_sCODESAME);
	sp.Execute("SIGLA"     , pOV, &pOV->m_sSIGLA, pNV, &pNV->m_sSIGLA);
}

BOOL CEesamiCodeesameSiglaVistaSet::DeleteRecordset(const CString &strCommento)
{
	// não se implementa delete numa VIEW
	/*
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset(strCommento))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset(strCommento);
	}
	return bReturn;
	*/
	return FALSE;
}


CString CEesamiCodeesameSiglaVistaSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO;
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CEesamiCodeesameSiglaVistaSet::UpdateRecordset(const CString &strCommento)
{
	//if (m_nEditMode == addnew)
	//	m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}



BOOL CEesamiCodeesameSiglaVistaSet::Find(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("UO=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CEesamiCodeesameSiglaVistaSet::Find"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;
			//DoFieldExchange();
		}
		CloseRecordset("CEesamiCodeesameSiglaVistaSet::Find");
	}
	return bReturn;
}
