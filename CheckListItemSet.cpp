#include "stdafx.h"
#include "Endox.h"
#include "CheckListItemSet.h"

#include "CodiciClassificazioneDiagnosticaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListItemSet, CBaseSet)

CCheckListItemSet::CCheckListItemSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 12;
}

CString CCheckListItemSet::GetDefaultSQL()
{
	return "CheckListItem";
}

void CCheckListItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDCheckList", m_lIDCheckList);
		RFX_Long(pFX, "IDPadre", m_lIDPadre);
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Text(pFX, "Titolo", m_sTitolo, 255);
		RFX_Text(pFX, "TestoRTF", m_sTestoRTF, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTXT", m_sTestoTXT, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Long(pFX, "TestoNumeroVariabili", m_lTestoNumeroVariabili);
		RFX_Bool(pFX, "ItemAlmenoUno", m_bItemAlmenoUno);
		RFX_Bool(pFX, "ItemPiuDiUno", m_bItemPiuDiUno);
		RFX_Long(pFX, "ClassificazioneDiagnosi", m_lClassificazioneDiagnosi);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCheckListItemSet::SetEmpty()
{
	m_lID = 0;
	m_lIDCheckList = 0;
	m_lIDPadre = 0;
	m_lOrdine = 0;
	m_sTitolo = "";
	m_sTestoRTF = "";
	m_sTestoTXT = "";
	m_lTestoNumeroVariabili = 0;
	m_bItemAlmenoUno = FALSE;
	m_bItemPiuDiUno = FALSE;
	m_lClassificazioneDiagnosi = 0;
	m_bEliminato = FALSE;
}

/*
BOOL CCheckListItemSet::GetSceltaMultipla(long lID)
{
	BOOL bReturn = TRUE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListItemSet::GetSceltaMultipla"))
	{
		if (!IsEOF())
			bReturn = m_bItemPiuDiUno;

		CloseRecordset("CCheckListItemSet::GetSceltaMultipla");
	}

	return bReturn;
}
*/

/*
void CCheckListItemSet::GetTesti(long lID, CString& strRTF, CString& strTXT, long& lNumeroVariabili, long& lIDDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	strRTF.Empty();
	strTXT.Empty();
	lNumeroVariabili = 0;
	lIDDiagnosi = 0;
	sDiagnosiCodice.Empty();
	sDiagnosiDescrizione.Empty();

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListItemSet::GetTesti"))
	{
		if (!IsEOF())
		{
			strRTF = m_sTestoRTF;
			strTXT = m_sTestoTXT;
			lNumeroVariabili = m_lTestoNumeroVariabili;

			lIDDiagnosi = m_lClassificazioneDiagnosi;
			CCodiciClassificazioneDiagnostSet().GetStringCodiceDescrizione(m_lClassificazioneDiagnosi, sDiagnosiCodice, sDiagnosiDescrizione);
		}

		CloseRecordset("CCheckListItemSet::GetTesti");
	}
}
*/

/*
CString CCheckListItemSet::GetTestoVariabili(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListItemSet::GetTestoVariabili"))
	{
		if (!IsEOF())
		{
			if (m_lTestoNumeroVariabili > 0)
				sReturn = m_sTestoTXT;
		}

		CloseRecordset("CCheckListItemSet::GetTestoVariabili");
	}

	return sReturn;
}
*/

CBaseSet* CCheckListItemSet::CreateNew()
{
	CCheckListItemSet* pNewSet = new CCheckListItemSet;

	return (CBaseSet*)pNewSet;
}

void CCheckListItemSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCheckListItemSet* pSet = (CCheckListItemSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCheckList) || bCopyAll)
		m_lIDCheckList = pSet->m_lIDCheckList;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPadre) || bCopyAll)
		m_lIDPadre = pSet->m_lIDPadre;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pSet->m_sTitolo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRTF) || bCopyAll)
		m_sTestoRTF = pSet->m_sTestoRTF;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoTXT) || bCopyAll)
		m_sTestoTXT = pSet->m_sTestoTXT;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTestoNumeroVariabili) || bCopyAll)
		m_lTestoNumeroVariabili = pSet->m_lTestoNumeroVariabili;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bItemAlmenoUno) || bCopyAll)
		m_bItemAlmenoUno = pSet->m_bItemAlmenoUno;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bItemPiuDiUno) || bCopyAll)
		m_bItemPiuDiUno = pSet->m_bItemPiuDiUno;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lClassificazioneDiagnosi) || bCopyAll)
		m_lClassificazioneDiagnosi = pSet->m_lClassificazioneDiagnosi;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCheckListItemSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCheckListItemSet* pOV = (CCheckListItemSet*)pOldValues;
	CCheckListItemSet* pNV = (CCheckListItemSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDCheckList", pOV, &pOV->m_lIDCheckList, pNV, &pNV->m_lIDCheckList);
	sp.Execute("IDPadre", pOV, &pOV->m_lIDPadre, pNV, &pNV->m_lIDPadre);
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("TestoRTF", pOV, &pOV->m_sTestoRTF, pNV, &pNV->m_sTestoRTF);
	sp.Execute("TestoTXT", pOV, &pOV->m_sTestoTXT, pNV, &pNV->m_sTestoTXT);
	sp.Execute("TestoNumeroVariabili", pOV, &pOV->m_lTestoNumeroVariabili, pNV, &pNV->m_lTestoNumeroVariabili);
	sp.Execute("ItemAlmenoUno", pOV, &pOV->m_bItemAlmenoUno, pNV, &pNV->m_bItemAlmenoUno);
	sp.Execute("ItemPiuDiUno", pOV, &pOV->m_bItemPiuDiUno, pNV, &pNV->m_bItemPiuDiUno);
	sp.Execute("ClassificazioneDiagnosi", pOV, &pOV->m_lClassificazioneDiagnosi, pNV, &pNV->m_lClassificazioneDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCheckListItemSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCheckListItemSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCheckListItemSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCheckListItemSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}