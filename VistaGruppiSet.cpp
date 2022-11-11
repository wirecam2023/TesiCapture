#include "stdafx.h"
#include "Endox.h"
#include "VistaGruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaGruppiSet, CBaseSet)

CVistaGruppiSet::CVistaGruppiSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("Nome, UO");

	m_nFields = 3;
}

CString CVistaGruppiSet::GetDefaultSQL()
{
	return "GRUPPI";
}

void CVistaGruppiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "Nome", m_sNome, 50);
	RFX_Long(pFX, "Permessi", m_lPermessi);
	RFX_Long(pFX, "UO", m_lUO);
}

void CVistaGruppiSet::SetEmpty()
{
	m_sNome = "";
	m_lPermessi = 0;
	m_lUO = 0;
}

long CVistaGruppiSet::GetUO(CString sNome)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("Nome='%s'", sNome);

	SetOpenFilter(strFilter);

	if (OpenRecordset("CVistaGruppiSet::GetUO"))
	{
		if (!IsEOF())
			lReturn = m_lUO;

		CloseRecordset("CVistaGruppiSet::GetUO");
	}

	return lReturn;
}
