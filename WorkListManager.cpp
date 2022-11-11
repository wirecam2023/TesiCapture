#include "stdafx.h"
#include "Endox.h"
#include "WorkListManager.h"

#include "EsamiSet.h"
#include "PrenotazioneAccettataSP.h"
#include "WorkListDicom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWorkListManager, CBaseSet)

CWorkListManager::CWorkListManager(CEsamiView* pEsamiView)
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetBaseFilter("");
	SetSortRecord("COGNOME, NOME");

	m_pEsamiView = pEsamiView;
}

CWorkListManager::~CWorkListManager()
{
}

CWorkListManager* CWorkListManager::Create(CEsamiView* pEsamiView)
{
	CWorkListManager* pReturn = NULL;

	switch(theApp.m_nInterfacciaPrenotazione)
	{
		case CEndoxApp::prenotazioni_worklistdicom:
		case CEndoxApp::prenotazioni_cup_dicom:
		{
			pReturn = new CWorkListDicom(pEsamiView);
			break;
		}
		default:	
		{
			ASSERT(FALSE);
			break;
		}
	}

	return pReturn;
}

CString CWorkListManager::GetDefaultSQL()
{
	return "ListaPrenotazioni";
}

void CWorkListManager::UpdateWithExamID(long lIDPrenotazione, long lIDEsame)
{
	CString strQuery;
	strQuery.Format("UPDATE PRENOTAZIONI SET idesameins=%li WHERE id=%li", lIDEsame, lIDPrenotazione);

	try
	{
		theApp.m_dbEndox.ExecuteSQL(strQuery);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}

CString CWorkListManager::SetBaseFilter(const CString &strFilter)
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