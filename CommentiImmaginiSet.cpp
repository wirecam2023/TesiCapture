#include "stdafx.h"
#include "Endox.h"
#include "CommentiImmaginiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCommentiImmaginiSet, CBaseSet)

CCommentiImmaginiSet::CCommentiImmaginiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

void CCommentiImmaginiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Text(pFX, "Commento", m_sCommento, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CCommentiImmaginiSet::GetDefaultSQL()
{
	return "CommentiImmagini";
}

void CCommentiImmaginiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoEsame = 0;
	m_sCommento = "";
	m_bEliminato = FALSE;
}

CBaseSet* CCommentiImmaginiSet::CreateNew()
{
	return (CBaseSet*)new CCommentiImmaginiSet;
}

void CCommentiImmaginiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCommentiImmaginiSet* pSet = (CCommentiImmaginiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCommento) || bCopyAll)
		m_sCommento = pSet->m_sCommento;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCommentiImmaginiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCommentiImmaginiSet* pOV = (CCommentiImmaginiSet*)pOldValues;
	CCommentiImmaginiSet* pNV = (CCommentiImmaginiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("Commento", pOV, &pOV->m_sCommento, pNV, &pNV->m_sCommento);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCommentiImmaginiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCommentiImmaginiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCommentiImmaginiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCommentiImmaginiSet::SetBaseFilter(const CString &strFilter)
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

long CCommentiImmaginiSet::AddRow(long lIDTipoEsame, const CString &sCommentoImmagine)
{
	long lReturn = 0;

	SetOpenFilter("ID=0");
	if (OpenRecordset("CCommentiImmaginiSet::AddRow"))
	{
		if (AddNewRecordset("CCommentiImmaginiSet::AddRow"))
		{
			m_lIDTipoEsame = lIDTipoEsame;
			m_sCommento = sCommentoImmagine;

			if (UpdateRecordset("CCommentiImmaginiSet::AddRow"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CCommentiImmaginiSet::AddRow");
	}

	return lReturn;
}

BOOL CCommentiImmaginiSet::EdtRow(long lIDDaModificare, const CString &sCommentoImmagine)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("ID=%li", lIDDaModificare);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CCommentiImmaginiSet::EdtRow"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CCommentiImmaginiSet::EdtRow"))
			{
				m_sCommento = sCommentoImmagine;

				bReturn = UpdateRecordset("CCommentiImmaginiSet::EdtRow");
			}
		}

		CloseRecordset("CCommentiImmaginiSet::EdtRow");
	}

	return bReturn;
}

BOOL CCommentiImmaginiSet::DelRow(long lIDDaEliminare)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("ID=%li", lIDDaEliminare);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CCommentiImmaginiSet::DelRow"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CCommentiImmaginiSet::DelRow");

		CloseRecordset("CCommentiImmaginiSet::DelRow");
	}

	return bReturn;
}