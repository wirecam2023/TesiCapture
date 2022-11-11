#include "stdafx.h"
#include "Endox.h"
#include "MediciCurantiInviantiBulkSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMediciCurantiInviantiBulkSet, CBaseSet)

CMediciCurantiInviantiBulkSet::CMediciCurantiInviantiBulkSet(long lCurantiInvianti)
	: CRecordset(&theApp.m_dbEndox)
{
	ASSERT((lCurantiInvianti == MEDICI_CURANTI) || (lCurantiInvianti == MEDICI_INVIANTI));
	m_lCurantiInvianti = lCurantiInvianti;

	m_pContatore = 0;
	m_pTitolo = 0;
	m_pCognome = 0;
	m_pNome = 0;

	m_pContatoreLength = 0;
	m_pTitoloLength = 0;
	m_pCognomeLength = 0;
	m_pNomeLength = 0;

	m_nFields = 4;
}

CString CMediciCurantiInviantiBulkSet::GetDefaultSQL()
{
	switch(m_lCurantiInvianti)
	{
		case MEDICI_CURANTI:
		{
			return "EMEDICICURANTI";
			break;
		}
		case MEDICI_INVIANTI:
		{
			return "EMEDICIINVIANTI";
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	return "";
}

void CMediciCurantiInviantiBulkSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long_Bulk(pFX, "Contatore", &m_pContatore, &m_pContatoreLength);
	RFX_Text_Bulk(pFX, "Titolo", &m_pTitolo, &m_pTitoloLength, 50+1);
	RFX_Text_Bulk(pFX, "Cognome", &m_pCognome, &m_pCognomeLength, 50+1);
	RFX_Text_Bulk(pFX, "Nome", &m_pNome, &m_pNomeLength, 50+1);
}

void CMediciCurantiInviantiBulkSet::CaricaInMemoria()
{
	switch (m_lCurantiInvianti)
	{
		case MEDICI_CURANTI:
		{
			theApp.m_listMediciCuranti.RemoveAll();
			break;
		}
		case MEDICI_INVIANTI:
		{
			theApp.m_listMediciInvianti.RemoveAll();
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	m_strFilter.Format("UO=%li AND Eliminato=0", theApp.m_lUO);

	m_strSort = "Cognome, Nome, Contatore";
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		m_strSort = "Nome, Cognome, Contatore";

	try
	{
		Open(CRecordset::forwardOnly, NULL, CRecordset::readOnly | CRecordset::useMultiRowFetch);

		while(!IsEOF())
		{
			for(UINT i = 0; i < GetRowsFetched(); i++)
			{
				if (m_pContatoreLength[i] > 0)
				{
					tagMEDICICURANTIINVIANTI tagTemp;
					tagTemp.m_lContatore = m_pContatore[i];
					tagTemp.m_sTitolo = GetTextField(m_pTitolo, m_pTitoloLength, i);
					tagTemp.m_sCognome = GetTextField(m_pCognome, m_pCognomeLength, i);
					tagTemp.m_sNome = GetTextField(m_pNome, m_pNomeLength, i);

					switch(m_lCurantiInvianti)
					{
						case MEDICI_CURANTI:
						{
							theApp.m_listMediciCuranti.AddTail(tagTemp);
							break;
						}
						case MEDICI_INVIANTI:
						{
							theApp.m_listMediciInvianti.AddTail(tagTemp);
							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}
				}
			}

			MoveNext();
		}

		if (IsOpen())
			Close();
	}
	catch(CDBException* e)
	{
		theApp.AfxMessageBoxEndo(GetDefaultSQL() + ":\n" + e->m_strError);
 		e->Delete();
	}
	catch(CMemoryException* e)
	{
		e->ReportError();
 		e->Delete();
	}
	catch(...)
	{
	}
}

CString CMediciCurantiInviantiBulkSet::GetTextField(LPTSTR szField, long* pFieldSize, int iIndex)
{
	CString strReturn;

	if (pFieldSize[iIndex] > 0)
		strReturn = szField + iIndex * (50+1);

	return strReturn;
}