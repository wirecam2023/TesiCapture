#include "StdAfx.h"
#include "VistaEsamiConPrestazioniPrincipaliSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaEsamiConPrestazioniPrincipaliSet, CBaseSet)

CVistaEsamiConPrestazioniPrincipaliSet::CVistaEsamiConPrestazioniPrincipaliSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();

	m_nFields = 1;
}

CString CVistaEsamiConPrestazioniPrincipaliSet::GetDefaultSQL()
{
	return "VistaEsamiConPrestazioniPrinci";
}

void CVistaEsamiConPrestazioniPrincipaliSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Esame", m_lEsame);
}

void CVistaEsamiConPrestazioniPrincipaliSet::SetEmpty()
{
	m_lEsame = 0;
}

BOOL CVistaEsamiConPrestazioniPrincipaliSet::TrovaEsame(long lIDEsame)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("Esame=%li", lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CVistaEsamiConPrestazioniPrincipaliSet::TrovaEsame"))
	{
		bReturn = !IsEOF();
		CloseRecordset("CVistaEsamiConPrestazioniPrincipaliSet::TrovaEsame");
	}

	return bReturn;
}