#include "stdafx.h"
#include "Endox.h"
#include "VistaUtentiMediciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaUtentiMediciSet, CBaseSet)

CVistaUtentiMediciSet::CVistaUtentiMediciSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 5;
}

CString CVistaUtentiMediciSet::GetDefaultSQL()
{
	return "VistaUtentiMedici";
}

void CVistaUtentiMediciSet::SetEmpty()
{
	m_lID = 0;
	m_sUsername = "";
	m_sTitolo = "";
	m_sCognome = "";
	m_sNome = "";
}

void CVistaUtentiMediciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Text(pFX, "Username", m_sUsername, 50);
	RFX_Text(pFX, "Titolo", m_sTitolo, 50);
	RFX_Text(pFX, "Cognome", m_sCognome, 50);
	RFX_Text(pFX, "Nome", m_sNome, 50);
}

CString CVistaUtentiMediciSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CVistaUtentiMediciSet::GetDescrizione"))
	{
		if (!IsEOF())
		{
			m_sUsername.Trim();
			m_sTitolo.Trim();
			m_sCognome.Trim();
			m_sNome.Trim();

			if (!m_sTitolo.IsEmpty())
				sReturn = m_sTitolo;

			if (!m_sCognome.IsEmpty())
			{
				if (!sReturn.IsEmpty())
					sReturn += " ";

				sReturn += m_sCognome;
			}

			if (!m_sNome.IsEmpty())
			{
				if (!sReturn.IsEmpty())
					sReturn += " ";

				sReturn += m_sNome;
			}

			if (!m_sUsername.IsEmpty())
			{
				if (!sReturn.IsEmpty())
					sReturn += " ";

				sReturn += "(" + m_sUsername + ")";
			}
		}

		CloseRecordset("CVistaUtentiMediciSet::GetDescrizione");
	}

	return sReturn;
}
