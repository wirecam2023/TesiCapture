#include "stdafx.h"
#include "Endox.h"
#include "ListaOsservazioniSet.h"

#include <MMSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CListaOsservazioniSet, CBaseSet)

CListaOsservazioniSet::CListaOsservazioniSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetSortRecord("CONTATORE");

	m_lContatore = 0;
	m_lData = 0;
	m_sTipoEsame = "";
	m_lOrgano = 0;
	m_sSede = "";
	m_sOsservazioni = "";

	m_nFields = 6;
}

CListaOsservazioniSet::~CListaOsservazioniSet()
{
}

void CListaOsservazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "CONTATORE",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "DATA",			m_lData);
		RFX_Text(pFX, "DESCRIZIONE",	m_sTipoEsame,		 255);
		RFX_Long(pFX, "ORGANO",			m_lOrgano);
		RFX_Text(pFX, "SEDE",			m_sSede,			 255);
		RFX_Text(pFX, "OSSERVAZIONI",	m_sOsservazioni,	3999);
	}
}

CString CListaOsservazioniSet::GetDefaultSQL()
{
	return("ELISTAOSSERVAZIONI");
}

BOOL CListaOsservazioniSet::OpenRecordset(const CString &strCommento)
{
	BOOL bReturn = FALSE;

#ifdef _DEBUG_DB
	TRACE0("-> -------------------------------------------------- ->\n");

	TRACE1("   OpenRecordset(%s)\n", strCommento);
	TRACE1("   SQL:        %s\n", GetDefaultSQL());
	TRACE1("   BASEFILTER: %s\n", m_strBaseFilter);
	TRACE1("   OPENFILTER: %s\n", m_strOpenFilter);
	TRACE1("   SORTRECORD: %s\n", m_strSort);

	DWORD timeDurata = timeGetTime();
#endif // _DEBUG_DB //

	try
	{
		if (IsOpen())
			Close();
		
		Open(CBaseSet::snapshot);

		bReturn = TRUE;
    }
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("OpenRecordset (%s)\n%d: %s\n\nSQL\n%s\n\nBASEFILTER\n%s\n\nOPENFILTER\n%s\n\nSORTRECORD\n%s\n", strCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);

 		e->Delete();
	}

#ifdef _DEBUG_DB
	timeDurata = timeGetTime() - timeDurata;

	TRACE1("   TEMPO ESEC: %li msec.\n", (long)timeDurata);

	TRACE0("<- -------------------------------------------------- <-\n");
#endif // _DEBUG_DB //

	return bReturn;
}

void CListaOsservazioniSet::SetEmpty()
{
	m_lContatore = 0;
	m_lData = 0;
	m_sTipoEsame = "";
	m_lOrgano = 0;
	m_sSede = "";
	m_sOsservazioni = "";
}