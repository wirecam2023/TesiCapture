#include "stdafx.h"
#include "Endox.h"
#include "TabellaStruttureSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTabellaStruttureSet, CBaseSet)

CTabellaStruttureSet::CTabellaStruttureSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CTabellaStruttureSet::GetDefaultSQL()
{
	return "TabellaStrutture";
}

void CTabellaStruttureSet::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoEsame = 0;
	m_lOrdine = 0;
	m_sStruttura = "";
	m_bEliminato = FALSE;
}

void CTabellaStruttureSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Text(pFX, "Struttura", m_sStruttura, 50);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CTabellaStruttureSet::CreateNew()
{
	return (CBaseSet*)new CTabellaStruttureSet;
}

void CTabellaStruttureSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTabellaStruttureSet* pSet = (CTabellaStruttureSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sStruttura) || bCopyAll)
		m_sStruttura = pSet->m_sStruttura;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

BOOL CTabellaStruttureSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTabellaStruttureSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTabellaStruttureSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTabellaStruttureSet::SetBaseFilter(const CString &strFilter)
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

void CTabellaStruttureSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTabellaStruttureSet* pOV = (CTabellaStruttureSet*)pOldValues;
	CTabellaStruttureSet* pNV = (CTabellaStruttureSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Struttura", pOV, &pOV->m_sStruttura, pNV, &pNV->m_sStruttura);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

long CTabellaStruttureSet::FleuryTrans(long lIDTipoEsame, CString sStruttura)
{
	long lReturn = 0;

	sStruttura.Trim();
	sStruttura.Replace("'", "''");

	if ((lIDTipoEsame > 0) && (!sStruttura.IsEmpty()))
	{
		CString sFilter;
		sFilter.Format("IDTIPOESAME = %li AND STRUTTURA = '%s'", lIDTipoEsame, sStruttura);
		SetOpenFilter(sFilter);
		if (OpenRecordset("CTabellaStruttureSet::FleuryTrans"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CTabellaStruttureSet::FleuryTrans");
		}
	}

	return lReturn;
}

long CTabellaStruttureSet::GetCount(long lIDTipoEsame)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("IDTipoEsame = %li", lIDTipoEsame);
	SetOpenFilter(strFilter);

	if (OpenRecordset("CTabellaStruttureSet::GetCount"))
	{
		while (!IsEOF())
		{
			lReturn++;
			MoveNext();
		}
		CloseRecordset("CTabellaStruttureSet::GetCount");
	}

	return lReturn;
}