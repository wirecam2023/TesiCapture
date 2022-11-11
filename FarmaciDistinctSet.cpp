#include "stdafx.h"
#include "Endox.h"
#include "FarmaciDistinctSet.h"

#include <MMSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFarmaciDistinctSet, CBaseSet)

CFarmaciDistinctSet::CFarmaciDistinctSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetSortRecord("NOME");

	m_sNome = "";
	m_sPrincipioAttivo = "";

	m_nFields = 2;
}

CString CFarmaciDistinctSet::GetDefaultSQL()
{
	return "FARMACIDISTINCT";
}

void CFarmaciDistinctSet::SetEmpty()
{
	m_sNome = "";
	m_sPrincipioAttivo = "";
}

void CFarmaciDistinctSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "Nome", m_sNome, 255);
	RFX_Text(pFX, "PrincipioAttivo", m_sPrincipioAttivo, 255);
}

BOOL CFarmaciDistinctSet::OpenRecordset(const CString &strCommento)
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