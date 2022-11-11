#include "stdafx.h"
#include "Endox.h"
#include "MediciCurantiInviantiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMediciCurantiInviantiSet, CBaseSet)

CMediciCurantiInviantiSet::CMediciCurantiInviantiSet(long lCurantiInvianti)
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	ASSERT((lCurantiInvianti == MEDICI_CURANTI) || (lCurantiInvianti == MEDICI_INVIANTI));

	SetBaseFilter("");
	SetEmpty();

	m_lCurantiInvianti = lCurantiInvianti;

	m_nFields = 19;
}

void CMediciCurantiInviantiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Cognome", m_sCognome, 50);
		RFX_Text(pFX, "Nome", m_sNome, 50);
		RFX_Text(pFX, "Titolo", m_sTitolo, 50);
		RFX_Text(pFX, "CodiceFiscale", m_sCodiceFiscale, 16);
		RFX_Long(pFX, "ASL", m_lASL);
		RFX_Text(pFX, "Sede", m_sSede, 50);
		RFX_Text(pFX, "Via", m_sVia, 50);
		RFX_Text(pFX, "Citta", m_sCitta, 50);
		RFX_Text(pFX, "CAP", m_sCAP, 5);
		RFX_Text(pFX, "Provincia", m_sProvincia, 5);
		RFX_Text(pFX, "Telefono", m_sTelefono, 50);
		RFX_Text(pFX, "Fax", m_sFax, 50);
		RFX_Text(pFX, "Email", m_sEmail, 50);
		RFX_Text(pFX, "Login", m_sLogin, 50);
		RFX_Text(pFX, "CodiceIntegrazione", m_sCodiceIntegrazione, 50);
		RFX_Bool(pFX, "Speciale", m_bSpeciale);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CMediciCurantiInviantiSet::GetDefaultSQL()
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

void CMediciCurantiInviantiSet::SetEmpty()
{
	m_lContatore = 0;
	m_sCognome = "";
	m_sNome = "";
	m_sTitolo = "";
	m_sCodiceFiscale = "";
	m_lASL = 0;
	m_sSede = "";
	m_sVia = "";
	m_sCitta = "";
	m_sCAP = "";
	m_sProvincia = "";
	m_sTelefono = "";
	m_sFax = "";
	m_sEmail = "";
	m_sLogin = "";
	m_sCodiceIntegrazione = "";
	m_bSpeciale = FALSE;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CString CMediciCurantiInviantiSet::GetFieldText(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	OpenRecordset("CMediciCurantiInviantiSet::GetFieldText");
	if (IsEOF() == FALSE)
		strReturn = m_sTitolo + " " + m_sNome + " " + m_sCognome;
	CloseRecordset("CMediciCurantiInviantiSet::GetFieldText");

	strReturn.TrimLeft();

	return strReturn;
}

CString CMediciCurantiInviantiSet::GetLogin(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	OpenRecordset("CMediciCurantiInviantiSet::GetLogin");
	if (IsEOF() == FALSE)
		strReturn = m_sLogin;
	CloseRecordset("CMediciCurantiInviantiSet::GetLogin");

	strReturn.TrimLeft();

	return strReturn;
}

CBaseSet* CMediciCurantiInviantiSet::CreateNew()
{
	CMediciCurantiInviantiSet* pNewSet = new CMediciCurantiInviantiSet(m_lCurantiInvianti);

	return (CBaseSet*)pNewSet;
}

void CMediciCurantiInviantiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMediciCurantiInviantiSet* pSet = (CMediciCurantiInviantiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCognome) || bCopyAll)
		m_sCognome = pSet->m_sCognome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pSet->m_sTitolo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceFiscale) || bCopyAll)
		m_sCodiceFiscale = pSet->m_sCodiceFiscale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lASL) || bCopyAll)
		m_lASL = pSet->m_lASL;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSede) || bCopyAll)
		m_sSede = pSet->m_sSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sVia) || bCopyAll)
		m_sVia = pSet->m_sVia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCitta) || bCopyAll)
		m_sCitta = pSet->m_sCitta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCAP) || bCopyAll)
		m_sCAP = pSet->m_sCAP;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sProvincia) || bCopyAll)
		m_sProvincia = pSet->m_sProvincia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTelefono) || bCopyAll)
		m_sTelefono = pSet->m_sTelefono;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFax) || bCopyAll)
		m_sFax = pSet->m_sFax;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEmail) || bCopyAll)
		m_sEmail = pSet->m_sEmail;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sLogin) || bCopyAll)
		m_sLogin = pSet->m_sLogin;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIntegrazione) || bCopyAll)
		m_sCodiceIntegrazione = pSet->m_sCodiceIntegrazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bSpeciale) || bCopyAll)
		m_bSpeciale = pSet->m_bSpeciale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMediciCurantiInviantiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMediciCurantiInviantiSet* pOV = (CMediciCurantiInviantiSet*)pOldValues;
	CMediciCurantiInviantiSet* pNV = (CMediciCurantiInviantiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Cognome", pOV, &pOV->m_sCognome, pNV, &pNV->m_sCognome);
	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("CodiceFiscale", pOV, &pOV->m_sCodiceFiscale, pNV, &pNV->m_sCodiceFiscale);
	sp.Execute("ASL", pOV, &pOV->m_lASL, pNV, &pNV->m_lASL);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Via", pOV, &pOV->m_sVia, pNV, &pNV->m_sVia);
	sp.Execute("Citta", pOV, &pOV->m_sCitta, pNV, &pNV->m_sCitta);
	sp.Execute("CAP", pOV, &pOV->m_sCAP, pNV, &pNV->m_sCAP);
	sp.Execute("Provincia", pOV, &pOV->m_sProvincia, pNV, &pNV->m_sProvincia);
	sp.Execute("Telefono", pOV, &pOV->m_sTelefono, pNV, &pNV->m_sTelefono);
	sp.Execute("Fax", pOV, &pOV->m_sFax, pNV, &pNV->m_sFax);
	sp.Execute("Email", pOV, &pOV->m_sEmail, pNV, &pNV->m_sEmail);
	sp.Execute("Login", pOV, &pOV->m_sLogin, pNV, &pNV->m_sLogin);
	sp.Execute("CodiceIntegrazione", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("Speciale", pOV, &pOV->m_bSpeciale, pNV, &pNV->m_bSpeciale);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMediciCurantiInviantiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMediciCurantiInviantiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMediciCurantiInviantiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMediciCurantiInviantiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CMediciCurantiInviantiSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
