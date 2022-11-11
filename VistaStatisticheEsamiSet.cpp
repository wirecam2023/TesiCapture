#include "stdafx.h"
#include "Endox.h"
#include "VistaStatisticheEsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaStatisticheEsamiSet, CBaseSet)

CVistaStatisticheEsamiSet::CVistaStatisticheEsamiSet(BOOL bStatisticaEsamiChiusi)
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 3;

	//

	m_bStatisticaEsamiChiusi = bStatisticaEsamiChiusi;
}

CString CVistaStatisticheEsamiSet::GetDefaultSQL()
{
	if (m_bStatisticaEsamiChiusi)
		return "VistaStatisticheEsamiChiusi";

	return "VistaStatisticheEsami";
}

void CVistaStatisticheEsamiSet::SetEmpty()
{
	m_lIDEsame = 0;
	m_lData = 0;
	m_lMedico = 0;
}

void CVistaStatisticheEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Long(pFX, "Data", m_lData);
	RFX_Long(pFX, "Medico", m_lMedico);
}

CString CVistaStatisticheEsamiSet::SetBaseFilter(const CString &strFilter)
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
