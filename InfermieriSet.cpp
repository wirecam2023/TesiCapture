#include "stdafx.h"
#include "Endox.h"
#include "InfermieriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInfermieriSet, CBaseSet)

CInfermieriSet::CInfermieriSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 17;
}

void CInfermieriSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Cognome", m_sCognome, 50);
		RFX_Text(pFX, "Nome", m_sNome, 50);
		RFX_Text(pFX, "Titolo", m_sTitolo, 50);
		RFX_Text(pFX, "Matricola", m_sMatricola, 50);
		RFX_Long(pFX, "ASL", m_lASL);
		RFX_Text(pFX, "Sede", m_sSede, 50);
		RFX_Text(pFX, "Via", m_sVia, 50);
		RFX_Text(pFX, "Citta", m_sCitta, 50);
		RFX_Text(pFX, "CAP", m_sCAP, 5);
		RFX_Text(pFX, "Provincia", m_sProvincia, 5);
		RFX_Text(pFX, "Telefono", m_sTelefono, 50);
		RFX_Text(pFX, "Fax", m_sFax, 50);
		RFX_Text(pFX, "Email", m_sEmail, 50);
		RFX_Long(pFX, "IDUtenteEndox", m_lIDUserEndox);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CInfermieriSet::GetDefaultSQL()
{
	return "EINFERMIERI";
}

void CInfermieriSet::SetEmpty()
{
	m_lContatore = 0;
	m_sCognome = "";
	m_sNome = "";
	m_sTitolo = "";
	m_sMatricola = "";
	m_lASL = 0;
	m_sSede = "";
	m_sVia = "";
	m_sCitta = "";
	m_sCAP = "";
	m_sProvincia = "";
	m_sTelefono = "";
	m_sFax = "";
	m_sEmail = "";
	m_lIDUserEndox = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CString CInfermieriSet::GetFieldText(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	OpenRecordset("CInfermieriSet::GetText");
	if (IsEOF() == FALSE)
		strReturn = m_sTitolo + " " + m_sNome + " " + m_sCognome;
	CloseRecordset("CInfermieriSet::GetText");

	strReturn.TrimLeft();

	return strReturn;
}

CString CInfermieriSet::GetMatricola(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CInfermieriSet::GetMatricola"))
	{
		if (!IsEOF())
			strReturn = m_sMatricola;

		CloseRecordset("CInfermieriSet::GetMatricola");
	}

	return strReturn;
}

CBaseSet* CInfermieriSet::CreateNew()
{
	return (CBaseSet*)new CInfermieriSet;
}

void CInfermieriSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CInfermieriSet* pSet = (CInfermieriSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCognome) || bCopyAll)
		m_sCognome = pSet->m_sCognome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pSet->m_sTitolo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMatricola) || bCopyAll)
		m_sMatricola = pSet->m_sMatricola;
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
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUserEndox) || bCopyAll)
		m_lIDUserEndox = pSet->m_lIDUserEndox;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CInfermieriSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CInfermieriSet* pOV = (CInfermieriSet*)pOldValues;
	CInfermieriSet* pNV = (CInfermieriSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Cognome", pOV, &pOV->m_sCognome, pNV, &pNV->m_sCognome);
	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("Matricola", pOV, &pOV->m_sMatricola, pNV, &pNV->m_sMatricola);
	sp.Execute("ASL", pOV, &pOV->m_lASL, pNV, &pNV->m_lASL);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Via", pOV, &pOV->m_sVia, pNV, &pNV->m_sVia);
	sp.Execute("Citta", pOV, &pOV->m_sCitta, pNV, &pNV->m_sCitta);
	sp.Execute("CAP", pOV, &pOV->m_sCAP, pNV, &pNV->m_sCAP);
	sp.Execute("Provincia", pOV, &pOV->m_sProvincia, pNV, &pNV->m_sProvincia);
	sp.Execute("Telefono", pOV, &pOV->m_sTelefono, pNV, &pNV->m_sTelefono);
	sp.Execute("Fax", pOV, &pOV->m_sFax, pNV, &pNV->m_sFax);
	sp.Execute("Email", pOV, &pOV->m_sEmail, pNV, &pNV->m_sEmail);
	sp.Execute("IDUtenteEndox", pOV, &pOV->m_lIDUserEndox, pNV, &pNV->m_lIDUserEndox);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CInfermieriSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CInfermieriSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CInfermieriSet::DeleteRecordset");
	}
	return bReturn;
}

CString CInfermieriSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CInfermieriSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

long CInfermieriSet::GetContatoreFromUserID(long lUserID)
{
	long lReturn = 0;

	if (lUserID > 0)
	{
		CString sFilter;
		sFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CInfermieriSet::GetContatoreFromUserID"))
		{
			if (!IsEOF())
				lReturn = m_lContatore;

			CloseRecordset("CInfermieriSet::GetContatoreFromUserID");
		}
	}

	return lReturn;
}