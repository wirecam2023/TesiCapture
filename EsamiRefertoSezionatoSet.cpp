#include "stdafx.h"
#include "Endox.h"
#include "EsamiRefertoSezionatoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiRefertoSezionatoSet, CBaseSet)

CEsamiRefertoSezionatoSet::CEsamiRefertoSezionatoSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}
CString CEsamiRefertoSezionatoSet::GetDefaultSQL()
{
	return "EsamiRefertoSezionato";
}

void CEsamiRefertoSezionatoSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDTipoReferto = 0;
	m_lIDTipoMateriale = 0;
	m_sBasiTotali = "";
	m_sCoperturaMedia = "";
	m_sCoperturaPercentuale = "";
	m_sUtenteRefertazione = "";
	m_sDataOraRefertazione = "";
	m_bEliminato = FALSE;
}

void CEsamiRefertoSezionatoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDTipoReferto", m_lIDTipoReferto);
		RFX_Long(pFX, "IDTipoMateriale", m_lIDTipoMateriale);
		RFX_Text(pFX, "BasiTotali", m_sBasiTotali, 50);
		RFX_Text(pFX, "CoperturaMedia", m_sCoperturaMedia, 50);
		RFX_Text(pFX, "CoperturaPercentuale", m_sCoperturaPercentuale, 50);
		RFX_Text(pFX, "UtenteRefertazione", m_sUtenteRefertazione, 50);
		RFX_Text(pFX, "DataOraRefertazione", m_sDataOraRefertazione, 14);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CEsamiRefertoSezionatoSet::CreateNew()
{
	return (CBaseSet*)new CEsamiRefertoSezionatoSet;
}
void CEsamiRefertoSezionatoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiRefertoSezionatoSet* pSet = (CEsamiRefertoSezionatoSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoReferto) || bCopyAll)
		m_lIDTipoReferto = pSet->m_lIDTipoReferto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoMateriale) || bCopyAll)
		m_lIDTipoMateriale = pSet->m_lIDTipoMateriale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sBasiTotali) || bCopyAll)
		m_sBasiTotali = pSet->m_sBasiTotali;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCoperturaMedia) || bCopyAll)
		m_sCoperturaMedia = pSet->m_sCoperturaMedia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCoperturaPercentuale) || bCopyAll)
		m_sCoperturaPercentuale = pSet->m_sCoperturaPercentuale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUtenteRefertazione) || bCopyAll)
		m_sUtenteRefertazione = pSet->m_sUtenteRefertazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOraRefertazione) || bCopyAll)
		m_sDataOraRefertazione = pSet->m_sDataOraRefertazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEsamiRefertoSezionatoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiRefertoSezionatoSet* pOV = (CEsamiRefertoSezionatoSet*)pOldValues;
	CEsamiRefertoSezionatoSet* pNV = (CEsamiRefertoSezionatoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDTipoReferto", pOV, &pOV->m_lIDTipoReferto, pNV, &pNV->m_lIDTipoReferto);
	sp.Execute("IDTipoMateriale", pOV, &pOV->m_lIDTipoMateriale, pNV, &pNV->m_lIDTipoMateriale);
	sp.Execute("BasiTotali", pOV, &pOV->m_sBasiTotali, pNV, &pNV->m_sBasiTotali);
	sp.Execute("CoperturaMedia", pOV, &pOV->m_sCoperturaMedia, pNV, &pNV->m_sCoperturaMedia);
	sp.Execute("CoperturaPercentuale", pOV, &pOV->m_sCoperturaPercentuale, pNV, &pNV->m_sCoperturaPercentuale);
	sp.Execute("UtenteRefertazione", pOV, &pOV->m_sUtenteRefertazione, pNV, &pNV->m_sUtenteRefertazione);
	sp.Execute("DataOraRefertazione", pOV, &pOV->m_sDataOraRefertazione, pNV, &pNV->m_sDataOraRefertazione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiRefertoSezionatoSet::DeleteRecordset(const CString &strCommento)
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

CString CEsamiRefertoSezionatoSet::SetBaseFilter(const CString &strFilter)
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

BOOL CEsamiRefertoSezionatoSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}
// Public Methods

BOOL CEsamiRefertoSezionatoSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CEsamiRefertoSezionatoSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiRefertoSezionatoSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CEsamiRefertoSezionatoSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CEsamiRefertoSezionatoSet::SetEliminato");
	}

	return bReturn;
}

BOOL CEsamiRefertoSezionatoSet::SetNewReferto(long lIDEsame, long lIDTipoReferto, long lIDTipoMateriale,
	CString sBasiTotali, CString sCoperturaMedia, CString sCoperturaPercentuale)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("IDEsame = %li", lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiRefertoSezionatoSet::SetNewReferto"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiRefertoSezionatoSet::SetNewReferto"))
			{
				m_bEliminato = TRUE;
				UpdateRecordset("CEsamiRefertoSezionatoSet::SetNewReferto");
			}
		}

		if (AddNewRecordset("CEsamiRefertoSezionatoSet::SetNewReferto"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDTipoReferto = lIDTipoReferto;
			m_lIDTipoMateriale = lIDTipoMateriale;
			m_sBasiTotali = sBasiTotali;
			m_sCoperturaMedia = sCoperturaMedia;
			m_sCoperturaPercentuale = sCoperturaPercentuale;
			m_sUtenteRefertazione = theApp.m_sUtenteLoggato;

			CTime now = CTime::GetCurrentTime();
			m_sDataOraRefertazione = now.Format("%Y%m%d%H%M%S");

			if (UpdateRecordset("CEsamiRefertoSezionatoSet::SetNewReferto"))
				bReturn = TRUE;
		}

		CloseRecordset("CEsamiRefertoSezionatoSet::SetNewReferto");
	}

	return bReturn;
}

void CEsamiRefertoSezionatoSet::GetLastReferto(long lIDEsame, long& lIDTipoReferto, long& lIDTipoMateriale,
	CString& sBasiTotali, CString& sCoperturaMedia, CString& sCoperturaPercentuale)
{
	
	lIDTipoReferto = -1;
	lIDTipoMateriale = -1;
	sBasiTotali = "";
	sCoperturaMedia = "";
	sCoperturaPercentuale = "";

	CString sFilter;
	sFilter.Format("IDEsame = %li", lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiRefertoSezionatoSet::GetLastReferto"))
	{
		if (!IsEOF())
		{
			lIDTipoReferto = m_lIDTipoReferto;
			lIDTipoMateriale = m_lIDTipoMateriale;
			sBasiTotali = m_sBasiTotali;
			sCoperturaMedia = m_sCoperturaMedia;
			sCoperturaPercentuale = m_sCoperturaPercentuale;
		}		
		CloseRecordset("CEsamiRefertoSezionatoSet::GetLastReferto");
	}	
}
