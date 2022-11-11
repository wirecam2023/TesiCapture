#include "stdafx.h"
#include "Endox.h"
#include "VistaAttivazioneSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaAttivazioneSet, CBaseSet)

CVistaAttivazioneSet::CVistaAttivazioneSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("STAZIONE, SOFTWARE");

	m_nFields = 3;
}

CString CVistaAttivazioneSet::GetDefaultSQL()
{
	return "ATTIVAZIONE";
}

void CVistaAttivazioneSet::SetEmpty()
{
	m_sStazione = "";
	m_sSoftware = "";
	m_sDescrizione = "";
}

void CVistaAttivazioneSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "Stazione", m_sStazione);
	RFX_Text(pFX, "Software", m_sSoftware);
	RFX_Text(pFX, "Descrizione", m_sDescrizione);
}

CString CVistaAttivazioneSet::GetDescrizione(CString sStazione)
{
	CString sReturn = "";

	sStazione.Replace("'", "''");

	CString sFilter;
	sFilter.Format("STAZIONE='%s' AND SOFTWARE='ENDOX'", sStazione);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CVistaAttivazioneSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CVistaAttivazioneSet::GetDescrizione");
	}

	return sReturn;
}