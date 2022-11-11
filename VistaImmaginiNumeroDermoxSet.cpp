#include "stdafx.h"
#include "Endox.h"
#include "VistaImmaginiNumeroDermoxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaImmaginiNumeroDermoxSet, CBaseSet)

CVistaImmaginiNumeroDermoxSet::CVistaImmaginiNumeroDermoxSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 3;
}

CString CVistaImmaginiNumeroDermoxSet::GetDefaultSQL()
{
	return "VistaImmaginiNumeroDermox";
}

void CVistaImmaginiNumeroDermoxSet::SetEmpty()
{
	m_lID = 0;
	m_lNumeroDermox = 0;
	m_sSede = "";
}

void CVistaImmaginiNumeroDermoxSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Long(pFX, "NumeroDermox", m_lNumeroDermox);
	RFX_Text(pFX, "Sede", m_sSede, 255);
}

long CVistaImmaginiNumeroDermoxSet::GetNumeroDermox(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CVistaImmaginiNumeroDermoxSet::GetNumeroDermox"))
	{
		if (!IsEOF())
			lReturn = m_lNumeroDermox;

		CloseRecordset("CVistaImmaginiNumeroDermoxSet::GetNumeroDermox");
	}

	return lReturn;
}

void CVistaImmaginiNumeroDermoxSet::GetNumeroDermoxSede(long lID, long& lReturn, CString& sReturn)
{
	lReturn = 0;
	sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CVistaImmaginiNumeroDermoxSet::GetNumeroDermox"))
	{
		if (!IsEOF())
		{
			lReturn = m_lNumeroDermox;
			sReturn = m_sSede;
		}

		CloseRecordset("CVistaImmaginiNumeroDermoxSet::GetNumeroDermox");
	}
}
