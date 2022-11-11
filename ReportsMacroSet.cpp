#include "stdafx.h"
#include "Endox.h"
#include "ReportsMacroSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CReportsMacroSet, CBaseSet)

CReportsMacroSet::CReportsMacroSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 8;
}

CString CReportsMacroSet::GetDefaultSQL()
{
	return "ReportsMacro";
}

void CReportsMacroSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_lImmaginiCopie = -1;					// no stampa immagini //
	m_lEtichetteIstopatologiaCopie = -1;	// no stampa etichette //
	m_sReportDaFirmare = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CReportsMacroSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID",	m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "ImmaginiCopie", m_lImmaginiCopie);
		RFX_Long(pFX, "EtichetteIstopatologiaCopie", m_lEtichetteIstopatologiaCopie);
		RFX_Text(pFX, "ReportDaFirmare", m_sReportDaFirmare, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CReportsMacroSet::CreateNew()
{
	return (CBaseSet*)new CReportsMacroSet;
}

void CReportsMacroSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CReportsMacroSet* pSet = (CReportsMacroSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lImmaginiCopie) || bCopyAll)
		m_lImmaginiCopie = pSet->m_lImmaginiCopie;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEtichetteIstopatologiaCopie) || bCopyAll)
		m_lEtichetteIstopatologiaCopie = pSet->m_lEtichetteIstopatologiaCopie;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sReportDaFirmare) || bCopyAll)
		m_sReportDaFirmare = pSet->m_sReportDaFirmare;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CReportsMacroSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CReportsMacroSet* pOV = (CReportsMacroSet*)pOldValues;
	CReportsMacroSet* pNV = (CReportsMacroSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("ImmaginiCopie", pOV, &pOV->m_lImmaginiCopie, pNV, &pNV->m_lImmaginiCopie);
	sp.Execute("EtichetteIstopatologiaCopie", pOV, &pOV->m_lEtichetteIstopatologiaCopie, pNV, &pNV->m_lEtichetteIstopatologiaCopie);
	sp.Execute("ReportDaFirmare", pOV, &pOV->m_sReportDaFirmare, pNV, &pNV->m_sReportDaFirmare);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CReportsMacroSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CReportsMacroSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CReportsMacroSet::DeleteRecordset");
	}
	return bReturn;
}

CString CReportsMacroSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CReportsMacroSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

// se ritorna negativo niente stampa
// se ritorna 0 chiede quante copie stampare //
// se ritorna positivo è già il numero di copie da stampare //
long CReportsMacroSet::GetImmaginiCopie(long lID)
{
	long lReturn = -1;

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CReportsMacroSet::GetImmaginiCopie"))
	{
		if (!IsEOF())
			lReturn = m_lImmaginiCopie;

		CloseRecordset("CReportsMacroSet::GetImmaginiCopie");
	}

	return lReturn;
}

// se ritorna negativo niente stampa
// se ritorna 0 chiede quante copie stampare //
// se ritorna positivo è già il numero di copie da stampare //
long CReportsMacroSet::GetEtichetteIstopatologiaCopie(long lID)
{
	long lReturn = -1;

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CReportsMacroSet::GetEtichetteIstopatologiaCopie"))
	{
		if (!IsEOF())
			lReturn = m_lEtichetteIstopatologiaCopie;

		CloseRecordset("CReportsMacroSet::GetEtichetteIstopatologiaCopie");
	}

	return lReturn;
}

CString CReportsMacroSet::GetReportDaFirmare(long lID)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CReportsMacroSet::GetReportDaFirmare"))
	{
		if (!IsEOF())
			sReturn = m_sReportDaFirmare;

		CloseRecordset("CReportsMacroSet::GetReportDaFirmare");
	}

	return sReturn;
}

void CReportsMacroSet::SetReportDaFirmare(long lID, CString sReportDaFirmare)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CReportsMacroSet::SetReportDaFirmare"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CReportsMacroSet::SetReportDaFirmare"))
			{
				m_sReportDaFirmare = sReportDaFirmare;
				UpdateRecordset("CReportsMacroSet::SetReportDaFirmare");
			}
		}

		CloseRecordset("CReportsMacroSet::SetReportDaFirmare");
	}
}