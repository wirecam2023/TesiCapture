#include "stdafx.h"
#include "Endox.h"
#include "EsamiVariantiSelezionateSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiVariantiSelezionateSet, CBaseSet)

CEsamiVariantiSelezionateSet::CEsamiVariantiSelezionateSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 8;
}
CString CEsamiVariantiSelezionateSet::GetDefaultSQL()
{
	return "EsamiVariantiSelezionate";
}

void CEsamiVariantiSelezionateSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDVariante = 0;
	m_lOrdine = 0;
	m_lGruppo = 0;
	m_sUtenteRefertazione = "";
	m_sDataOraRefertazione = "";
	m_bEliminato = FALSE;
}
void CEsamiVariantiSelezionateSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDVariante", m_lIDVariante);
		RFX_Long(pFX, "Ordine", m_lOrdine);		
		RFX_Long(pFX, "Gruppo", m_lGruppo);		
		RFX_Text(pFX, "UtenteRefertazione", m_sUtenteRefertazione, 50);
		RFX_Text(pFX, "DataOraRefertazione", m_sDataOraRefertazione, 14);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);		
	}
}

CBaseSet* CEsamiVariantiSelezionateSet::CreateNew()
{
	return (CBaseSet*)new CEsamiVariantiSelezionateSet;
}
void CEsamiVariantiSelezionateSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiVariantiSelezionateSet* pSet = (CEsamiVariantiSelezionateSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDVariante) || bCopyAll)
		m_lIDVariante = pSet->m_lIDVariante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lGruppo) || bCopyAll)
		m_lGruppo = pSet->m_lGruppo;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUtenteRefertazione) || bCopyAll)
		m_sUtenteRefertazione = pSet->m_sUtenteRefertazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOraRefertazione) || bCopyAll)
		m_sDataOraRefertazione = pSet->m_sDataOraRefertazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}
void CEsamiVariantiSelezionateSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiVariantiSelezionateSet* pOV = (CEsamiVariantiSelezionateSet*)pOldValues;
	CEsamiVariantiSelezionateSet* pNV = (CEsamiVariantiSelezionateSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDVariante", pOV, &pOV->m_lIDVariante, pNV, &pNV->m_lIDVariante);
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Gruppo", pOV, &pOV->m_lGruppo, pNV, &pNV->m_lGruppo);
	sp.Execute("UtenteRefertazione", pOV, &pOV->m_sUtenteRefertazione, pNV, &pNV->m_sUtenteRefertazione);
	sp.Execute("DataOraRefertazione", pOV, &pOV->m_sDataOraRefertazione, pNV, &pNV->m_sDataOraRefertazione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiVariantiSelezionateSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiVariantiSelezionateSet::SetBaseFilter(const CString &strFilter)
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

BOOL CEsamiVariantiSelezionateSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}


BOOL CEsamiVariantiSelezionateSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CEsamiVariantiSelezionateSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiVariantiSelezionateSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CEsamiVariantiSelezionateSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CEsamiVariantiSelezionateSet::SetEliminato");
	}

	return bReturn;
}

BOOL CEsamiVariantiSelezionateSet::SetNewSelection(long lIDEsame, long lIDVariante, long lOrdine, BOOL bDeleteGroup)
{
	BOOL bReturn = FALSE;

	long lGruppoOLD, lGruppoNEW;

	CString sFilter;
	sFilter.Format("IDEsame = %li", lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiVariantiSelezionateSet::SetNewSelection"))
	{
		if (!IsEOF())
		{
			lGruppoOLD = m_lGruppo;
			lGruppoNEW = lGruppoOLD + 1;
		}
		else
		{ 
			lGruppoOLD = 0;
			lGruppoNEW = 1;
		}
				
		CloseRecordset("CEsamiVariantiSelezionateSet::SetNewSelection");
	}

	BOOL bContinue = !bDeleteGroup;
	if (bDeleteGroup)
		bContinue = DeleteGroup(lIDEsame, lGruppoOLD);

	if (bContinue)
	{
		sFilter.Format("IDEsame = %li", lIDEsame);
		SetOpenFilter(sFilter);

		if (OpenRecordset("CEsamiVariantiSelezionateSet::SetNewSelection"))
		{
			if (AddNewRecordset("CEsamiVariantiSelezionateSet::SetNewSelection"))
			{
				m_lIDEsame = lIDEsame;
				m_lIDVariante = lIDVariante;
				m_lOrdine = lOrdine;
				m_sUtenteRefertazione = theApp.m_sUtenteLoggato;

				CTime now = CTime::GetCurrentTime();
				m_sDataOraRefertazione = now.Format("%Y%m%d%H%M%S");

				if (UpdateRecordset("CEsamiVariantiSelezionateSet::SetNewSelection"))
					bReturn = TRUE;
			}

			CloseRecordset("CEsamiVariantiSelezionateSet::SetNewSelection");
		}
	}
	return bReturn;
}

BOOL CEsamiVariantiSelezionateSet::DeleteGroup(long lIDEsame, long lGruppo)
{
	BOOL bReturn = TRUE;

	CString sFilter;
	sFilter.Format("IDEsame = %li AND GRUPPO = %li", lIDEsame, lGruppo);
	
	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiVariantiSelezionateSet::DeleteGroup"))
	{
		while (!IsEOF())
		{
			if (EditRecordset("CEsamiVariantiSelezionateSet::DeleteGroup"))
			{
				m_bEliminato = TRUE;
				bReturn = bReturn && UpdateRecordset("CEsamiVariantiSelezionateSet::DeleteGroup");
			}
			MoveNext();
		}
	}
	
	return bReturn;
}

void CEsamiVariantiSelezionateSet::GetSelectionList(long lIDEsame, CList<long>& listIDVariante)
{
	CString sFilter;
	sFilter.Format("IDEsame = %li", lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiVariantiSelezionateSet::GetSelectionList"))
	{
		while (!IsEOF())
		{
			listIDVariante.AddTail(m_lIDVariante);
			MoveNext();
		}
	}	
}