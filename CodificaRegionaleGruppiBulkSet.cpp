#include "stdafx.h"
#include "Endox.h"
#include "CodificaRegionaleGruppiBulkSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCodificaRegionaleGruppiBulkSet, CBaseSet)

CCodificaRegionaleGruppiBulkSet::CCodificaRegionaleGruppiBulkSet()
	: CRecordset(&theApp.m_dbEndox)
{
	m_pID = 0;
	m_pDescrizione = 0;

	m_pIDLength = 0;
	m_pDescrizioneLength = 0;

	m_nFields = 2;
}

CString CCodificaRegionaleGruppiBulkSet::GetDefaultSQL()
{
	return "ECodificaRegionaleGruppi";
}

void CCodificaRegionaleGruppiBulkSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long_Bulk(pFX, "ID", &m_pID, &m_pIDLength);
	RFX_Text_Bulk(pFX, "Descrizione", &m_pDescrizione, &m_pDescrizioneLength, 255+1);
}

void CCodificaRegionaleGruppiBulkSet::CaricaInMemoria()
{
	theApp.m_listGruppiPrestazioni.RemoveAll();

	m_strFilter.Format("UO=%li AND Eliminato=0", theApp.m_lUO);
	m_strSort = "Descrizione";

	try
	{
		Open(CRecordset::forwardOnly, NULL, CRecordset::readOnly | CRecordset::useMultiRowFetch);

		while(!IsEOF())
		{
			for(UINT i = 0; i < GetRowsFetched(); i++)
			{
				if (m_pIDLength[i] > 0)
				{
					tagRicettaElement tagTemp;
					tagTemp.m_lID = m_pID[i];
					tagTemp.m_sDescrizione = GetTextField(m_pDescrizione, m_pDescrizioneLength, i);
					tagTemp.m_sDescrizione.MakeUpper();

					theApp.m_listGruppiPrestazioni.AddTail(tagTemp);
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

CString CCodificaRegionaleGruppiBulkSet::GetTextField(LPTSTR szField, long* pFieldSize, int iIndex)
{
	CString strReturn;

	if (pFieldSize[iIndex] > 0)
		strReturn = szField + iIndex * (255+1);

	return strReturn;
}
