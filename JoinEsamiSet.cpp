#include "stdafx.h"
#include "Endox.h"
#include "JoinEsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CJoinEsamiSet, CBaseSet)

CJoinEsamiSet::CJoinEsamiSet()
	: CBaseSet(NULL, "") // è una vista //
{
	SetEmpty();
	SetFromWhere("", "");
	SetSelect("");

	m_nFields = 3;
}

void CJoinEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "EEsami.Contatore",	m_lEsame);
	RFX_Long(pFX, "EEsami.Paziente",	m_lPaziente);
	RFX_Long(pFX, "EEsami.Data",		m_lData);
}

CString CJoinEsamiSet::GetDefaultSQL()
{
	CString sRet;
	
	if (m_sSelect.IsEmpty())
		sRet = "SELECT DISTINCT EEsami.Contatore, EEsami.Paziente, EEsami.Data FROM ";
	else
		sRet = "SELECT DISTINCT EEsami.Contatore, EEsami.Paziente, EEsami.Data, " + m_sSelect + " FROM ";

	sRet +=	"EEsami " \
			"LEFT OUTER JOIN EEsamiPersonalizzabili ON EEsami.Contatore=EEsamiPersonalizzabili.IDEsame " \
			"LEFT OUTER JOIN ETerapie ON EEsami.Contatore=ETerapie.Esame " \
			"LEFT OUTER JOIN EDiagnosi ON EEsami.Contatore=EDiagnosi.Esame " \
			"LEFT OUTER JOIN EMalattie ON EEsami.Contatore=EMalattie.Esame " \
			"LEFT OUTER JOIN EIstologia ON EEsami.Contatore=EIstologia.Esame " \
			"LEFT OUTER JOIN EFamiliarita ON EEsami.Paziente=EFamiliarita.Paziente " \
			"LEFT OUTER JOIN EOsservazioni ON EEsami.Contatore=EOsservazioni.Esame " \
			"LEFT OUTER JOIN EsamiPregressi ON EEsami.Contatore=EsamiPregressi.Esame " \
			"LEFT OUTER JOIN EIndaginiPregresse ON EEsami.Contatore=EIndaginiPregresse.Esame " \
			"LEFT OUTER JOIN EInterventiChirurgici ON EEsami.Contatore=EInterventiChirurgici.Esame " \
			"LEFT OUTER JOIN EInterventiEndoscopici ON EEsami.Contatore=EInterventiEndoscopici.Esame";

	if (!m_sFrom.IsEmpty())
		sRet += " " + m_sFrom;

	return sRet;
}

void CJoinEsamiSet::SetEmpty()
{
	m_lPaziente	= 0;
	m_lEsame	= 0;
	m_lData		= 0;
}

void CJoinEsamiSet::SetFromWhere(const CString &strFrom, const CString &strWhere)
{
	// salvo il FROM //
	m_sFrom = strFrom;

	// compongo il WHERE //
    CString strNewWhere = strWhere;
	strNewWhere.Trim();
	if (strNewWhere.IsEmpty() || strNewWhere.Find("EESAMI.ELIMINATO") == -1)
		CBaseSet::SetBaseFilter("EESAMI.ELIMINATO=0");
	else
		CBaseSet::SetBaseFilter("");
	CBaseSet::SetOpenFilter(strNewWhere);
}

void CJoinEsamiSet::SetSelect(const CString &strSelect)
{
	// salvo il SELECT //
	m_sSelect = strSelect;
}
