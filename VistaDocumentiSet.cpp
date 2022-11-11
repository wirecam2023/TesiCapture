#include "stdafx.h"
#include "Endox.h"
#include "VistaDocumentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaDocumentiSet, CBaseSet)

CVistaDocumentiSet::CVistaDocumentiSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 2;
}

CString CVistaDocumentiSet::GetDefaultSQL()
{
	return "Documenti";
}

void CVistaDocumentiSet::SetEmpty()
{
	m_sDescrizione = "";
	m_sDataPersonalizzabile = "";
}

void CVistaDocumentiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	RFX_Text(pFX, "DataPersonalizzabile", m_sDataPersonalizzabile, 14);
}

CString CVistaDocumentiSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", lID);

		SetOpenFilter(sFilter);

		if (OpenRecordset("CVistaDocumentiSet::GetDescrizione"))
		{
			if (!IsEOF())
				sReturn = m_sDescrizione;

			CloseRecordset("CVistaDocumentiSet::GetDescrizione");
		}
	}

	return sReturn;
}

CString CVistaDocumentiSet::GetDataPersonalizzabile(long lID)
{
	CString sReturn = "";

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", lID);

		SetOpenFilter(sFilter);

		if (OpenRecordset("CVistaDocumentiSet::GetDescrizione"))
		{
			if (!IsEOF())
			{
				m_sDataPersonalizzabile.Trim();

				if (!m_sDataPersonalizzabile.IsEmpty())
					sReturn.Format("%s/%s/%s", m_sDataPersonalizzabile.Right(2), m_sDataPersonalizzabile.Mid(4,2), m_sDataPersonalizzabile.Left(4));
			}

			CloseRecordset("CVistaDocumentiSet::GetDescrizione");
		}
	}

	return sReturn;
}
