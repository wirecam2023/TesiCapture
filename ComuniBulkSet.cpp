#include "stdafx.h"
#include "Endox.h"
#include "ComuniBulkSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComuniBulkSet, CBaseSet)

CComuniBulkSet::CComuniBulkSet()
	: CRecordset(&theApp.m_dbEndox)
{
	m_pID = 0;
	m_pComune = 0;
	m_pCAP = 0;
	m_pProvincia = 0;

	m_pIDLength = 0;
	m_pComuneLength = 0;
	m_pCAPLength = 0;
	m_pProvinciaLength = 0;

	m_nFields = 4;
}

CString CComuniBulkSet::GetDefaultSQL()
{
	return "Comuni";
}

void CComuniBulkSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long_Bulk(pFX, "ID", &m_pID, &m_pIDLength);
	RFX_Text_Bulk(pFX, "Comune", &m_pComune, &m_pComuneLength, 255+1);
	RFX_Text_Bulk(pFX, "CAP", &m_pCAP, &m_pCAPLength, 10+1);
	RFX_Text_Bulk(pFX, "Provincia", &m_pProvincia, &m_pProvinciaLength, 10+1);
}

void CComuniBulkSet::CaricaInMemoria()
{
	theApp.m_listComuni.RemoveAll();

	// m_strFilter.Format("UO=%li AND Eliminato=0", theApp.m_lUO);
	m_strSort = "Comune, Provincia, ID";

	try
	{
		Open(CRecordset::forwardOnly, NULL, CRecordset::readOnly | CRecordset::useMultiRowFetch);

		while(!IsEOF())
		{
			for(UINT i = 0; i < GetRowsFetched(); i++)
			{
				if (m_pIDLength[i] > 0)
				{
					tagCOMUNI tagTemp;
					tagTemp.m_lID = m_pID[i];
					tagTemp.m_sComune = GetTextField50(m_pComune, m_pComuneLength, i);
					tagTemp.m_sCAP = GetTextField10(m_pCAP, m_pCAPLength, i);
					tagTemp.m_sProvincia = GetTextField10(m_pProvincia, m_pProvinciaLength, i);

					theApp.m_listComuni.AddTail(tagTemp);
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

CString CComuniBulkSet::GetTextField10(LPTSTR szField, long* pFieldSize, int iIndex)
{
	CString strReturn;

	if (pFieldSize[iIndex] > 0)
		strReturn = szField + iIndex * (10+1);

	return strReturn;
}

CString CComuniBulkSet::GetTextField50(LPTSTR szField, long* pFieldSize, int iIndex)
{
	CString strReturn;

	if (pFieldSize[iIndex] > 0)
		strReturn = szField + iIndex * (50+1);

	return strReturn;
}