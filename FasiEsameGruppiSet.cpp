#include "stdafx.h"
#include "Endox.h"
#include "FasiEsameGruppiSet.h"

#include "GruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFasiEsameGruppiSet, CBaseSet)

CFasiEsameGruppiSet::CFasiEsameGruppiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CFasiEsameGruppiSet::GetDefaultSQL()
{
	return "FASIESAME_GRUPPI";
}

void CFasiEsameGruppiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDFASE", m_lIDFase);
		RFX_Long(pFX, "IDGRUPPO", m_lIDGruppo);	
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CFasiEsameGruppiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDFase = 0;
	m_lIDGruppo = 0;	
	m_bEliminato = FALSE;
}

CBaseSet* CFasiEsameGruppiSet::CreateNew()
{
	return (CBaseSet*)new CFasiEsameGruppiSet;
}

void CFasiEsameGruppiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFasiEsameGruppiSet* pSet = (CFasiEsameGruppiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDFase) || bCopyAll)
		m_lIDFase = pSet->m_lIDFase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pSet->m_lIDGruppo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFasiEsameGruppiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFasiEsameGruppiSet* pOV = (CFasiEsameGruppiSet*)pOldValues;
	CFasiEsameGruppiSet* pNV = (CFasiEsameGruppiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDFASE", pOV, &pOV->m_lIDFase, pNV, &pNV->m_lIDFase);
	sp.Execute("IDGRUPPO", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFasiEsameGruppiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFasiEsameGruppiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFasiEsameGruppiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFasiEsameGruppiSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

CString CFasiEsameGruppiSet::GetGruppiListAsString(long idFase)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("IDFASE=%li", idFase);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CFasiEsameGruppiSet::GetGruppiListAsString"))
	{
		while (!IsEOF())
		{
			if (sReturn.IsEmpty())
				sReturn = CGruppiSet().GetDescrizione(m_lIDGruppo);
			else
				sReturn += "," + CGruppiSet().GetDescrizione(m_lIDGruppo);

			MoveNext();
		}

		CloseRecordset("CFasiEsameGruppiSet::GetGruppiListAsString");
	}

	return sReturn;
}

void CFasiEsameGruppiSet::GetGruppiList(long lIdFase, CList<long>* activeGroupList)
{
	activeGroupList->RemoveAll();

	CString sFilter;
	sFilter.Format("IDFASE=%li", lIdFase);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CFasiEsameGruppiSet::GetGruppiList"))
	{
		while (!IsEOF())
		{
			activeGroupList->AddTail(m_lIDGruppo);

			MoveNext();
		}

		CloseRecordset("CFasiEsameGruppiSet::GetGruppiList");
	}

}