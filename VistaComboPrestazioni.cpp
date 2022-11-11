//Julio - BUG 3365 - MAMOGUS
#include "stdafx.h"
#include "Endox.h"
#include "VistaComboPrestazioni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaComboPrestazioni, CBaseSet)


CVistaComboPrestazioni::CVistaComboPrestazioni() 
: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetBaseFilter("");
	SetSortRecord("IDORDINE");

	SetEmpty();

	m_nFields = 7;
}


CString CVistaComboPrestazioni::GetDefaultSQL()
{
	return "VISTA_COMBOPRESTAZIONI";
}

void CVistaComboPrestazioni::SetEmpty()
{
	m_lIDOrdine = 0;
	m_sNosologico = "";
	m_sAssiden = "";
	m_sCodicePrestazione = "";
	m_sDescrizionePrestazione = "";
	m_lStatoAccettazione = 0;
	m_lIDEsameIns = 0;
}

void CVistaComboPrestazioni::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);
	
	RFX_Long(pFX, "IDORDINE", m_lIDOrdine);
	RFX_Text(pFX, "NOSOLOGICO", m_sNosologico);
	RFX_Text(pFX, "ASSIDEN", m_sAssiden);
	RFX_Text(pFX, "CODICEPRESTAZIONE", m_sCodicePrestazione);
	RFX_Text(pFX, "DESCRIZIONEPRESTAZIONE", m_sDescrizionePrestazione);
	RFX_Long(pFX, "STATOACCETTAZIONE", m_lStatoAccettazione);
	RFX_Long(pFX, "IDESAMEINS", m_lIDEsameIns);
}

CString CVistaComboPrestazioni::SetBaseFilter(const CString &strFilter)
{
	return CBaseSet::SetBaseFilter(strFilter);
}

CString CVistaComboPrestazioni::GetCodicePrestazione(CString sNosologico)
{
	CString sReturn;

	CString sFilter;
	sFilter.Format("NOSOLOGICO='%s'", sNosologico);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CVistaComboPrestazioni::GetCodicePrestazione"))
	{
		if (!IsEOF())
			sReturn = m_sCodicePrestazione;

		CloseRecordset("CVistaComboPrestazioni::GetCodicePrestazione");
	}

	return sReturn;
}

CString CVistaComboPrestazioni::GetCodicePrestazione(long lIDOrdine)
{
	CString sReturn;

	CString sFilter;
	sFilter.Format("IDORDINE=%li", lIDOrdine);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CVistaComboPrestazioni::GetCodicePrestazione"))
	{
		if (!IsEOF())
			sReturn = m_sCodicePrestazione;

		CloseRecordset("CVistaComboPrestazioni::GetCodicePrestazione");
	}

	return sReturn;
}

CString CVistaComboPrestazioni::GetNosologico(long lIDOrdine)
{
	CString sReturn;

	CString sFilter;
	sFilter.Format("IDORDINE=%li", lIDOrdine);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CVistaComboPrestazioni::GetCodicePrestazione"))
	{
		if (!IsEOF())
			sReturn = m_sNosologico;

		CloseRecordset("CVistaComboPrestazioni::GetCodicePrestazione");
	}

	return sReturn;
}

long CVistaComboPrestazioni::GetIDEsameIns(long lIDOrdine)
{
	long lReturn;

	CString sFilter;
	sFilter.Format("IDORDINE=%li", lIDOrdine);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CVistaComboPrestazioni::GetCodicePrestazione"))
	{
		if (!IsEOF())
			lReturn = m_lIDEsameIns;

		CloseRecordset("CVistaComboPrestazioni::GetCodicePrestazione");
	}

	return lReturn;
}
BOOL CVistaComboPrestazioni::ExamHasCombo(CString sNosologico, CString sCodiceToFind)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("NOSOLOGICO='%s' AND CODICEPRESTAZIONE='%s'", sNosologico, sCodiceToFind);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CVistaComboPrestazioni::GetCodicePrestazione"))
	{
		if (!IsEOF())
			bReturn = TRUE;

		CloseRecordset("CVistaComboPrestazioni::GetCodicePrestazione");
	}

	return bReturn;
}