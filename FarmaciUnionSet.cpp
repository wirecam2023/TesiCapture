#include "stdafx.h"
#include "Endox.h"
#include "FarmaciUnionSet.h"

#include <MMSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFarmaciUnionSet, CBaseSet)

CFarmaciUnionSet::CFarmaciUnionSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetSortRecord("ID");

	SetEmpty();

	m_nFields = 4;
}

CString CFarmaciUnionSet::GetDefaultSQL()
{
	return "FARMACIUNION";
}

void CFarmaciUnionSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sDescrizioneMedia = "";
	m_sDescrizioneMassima = "";
}

void CFarmaciUnionSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 3999);
		RFX_Text(pFX, "DescrizioneMedia", m_sDescrizioneMedia, 3999);
		RFX_Text(pFX, "DescrizioneMassima", m_sDescrizioneMassima, 3999);
	}
}

BOOL CFarmaciUnionSet::OpenRecordset(const CString &strCommento)
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