#include "stdafx.h"
#include "Endox.h"
#include "VistaMonitoraggioFarmaciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaMonitoraggioFarmaciSet, CBaseSet)

CVistaMonitoraggioFarmaciSet::CVistaMonitoraggioFarmaciSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("IDEsame");

	m_nFields = 3;
}

CString CVistaMonitoraggioFarmaciSet::GetDefaultSQL()
{
	return "VistaMonitoraggioFarmaci";
}

void CVistaMonitoraggioFarmaciSet::SetEmpty()
{
	m_lIDEsame = 0;
	m_sNomeFarmaco = "";
	m_sDoseFarmaco = "";
}

void CVistaMonitoraggioFarmaciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "NomeFarmaco", m_sNomeFarmaco, 255);
	RFX_Text(pFX, "DoseFarmaco", m_sDoseFarmaco, 255);
}

CString CVistaMonitoraggioFarmaciSet::GetFarmaci(long lIDEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("IDEsame=%li", lIDEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CVistaMonitoraggioFarmaciSet::GetFarmaci"))
	{
		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += theApp.m_sTestiConcatenatiSeparatore;

			strReturn += m_sNomeFarmaco + " " + m_sDoseFarmaco;

			MoveNext();
		}

		CloseRecordset("CVistaMonitoraggioFarmaciSet::GetFarmaci");
	}

	return strReturn;
}