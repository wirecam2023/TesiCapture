#include "stdafx.h"
#include "Endox.h"
#include "RefertoIntegratoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRefertoIntegratoSet, CBaseSet)

//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

CRefertoIntegratoSet::CRefertoIntegratoSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 8;
}

CString CRefertoIntegratoSet::GetDefaultSQL()
{
	return "referto_integrato";
}

void CRefertoIntegratoSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sRTFMacro = "";
	m_sRTFMacro = "";
	m_sSignature = "";
	m_lStatoImportazione = 0;
	m_bToClose = FALSE;
	m_bEliminato = FALSE;
}

void CRefertoIntegratoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);
		RFX_Text(pFX, "RTFMACRO", m_sRTFMacro, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "RTFDIAG", m_sRTFDiag, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "SIGNATURE", m_sSignature, 255);
		RFX_Bool(pFX, "TOCLOSE", m_bToClose);
		RFX_Long(pFX, "STATOIMPORTAZIONE", m_lStatoImportazione);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CBaseSet* CRefertoIntegratoSet::CreateNew()
{
	return (CBaseSet*)new CRefertoIntegratoSet;
}

void CRefertoIntegratoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CRefertoIntegratoSet* pSet = (CRefertoIntegratoSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRTFMacro) || bCopyAll)
		m_sRTFMacro = pSet->m_sRTFMacro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRTFDiag) || bCopyAll)
		m_sRTFDiag = pSet->m_sRTFDiag;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSignature) || bCopyAll)
		m_sSignature = pSet->m_sSignature;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bToClose) || bCopyAll)
		m_bToClose = pSet->m_bToClose;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lStatoImportazione) || bCopyAll)
		m_lStatoImportazione = pSet->m_lStatoImportazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CRefertoIntegratoSet::CopyFieldFrom(CRefertoIntegratoSet* pSet, BOOL bEmpty)
{
	if (bEmpty)
		SetEmpty();

	if (!pSet->IsOpen() || pSet->IsFieldNull(&pSet->m_lIDEsame))
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldNull(&pSet->m_sRTFMacro))
		m_sRTFMacro = pSet->m_sRTFMacro;
	if (!pSet->IsOpen() || pSet->IsFieldNull(&pSet->m_sRTFDiag))
		m_sRTFDiag = pSet->m_sRTFDiag;
	if (!pSet->IsOpen() || pSet->IsFieldNull(&pSet->m_sSignature))
		m_sSignature = pSet->m_sSignature;
	if (!pSet->IsOpen() || pSet->IsFieldNull(&pSet->m_bToClose))
		m_bToClose = pSet->m_bToClose;
	if (!pSet->IsOpen() || pSet->IsFieldNull(&pSet->m_lStatoImportazione))
		m_lStatoImportazione = pSet->m_lStatoImportazione;
	if (!pSet->IsOpen() || pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
	

	if (bEmpty && IsOpen())
	{
		SetFieldNull(NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

int CRefertoIntegratoSet::GetEditMode()
{
	return m_nEditMode;
}


void CRefertoIntegratoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CRefertoIntegratoSet* pOV = (CRefertoIntegratoSet*)pOldValues;
	CRefertoIntegratoSet* pNV = (CRefertoIntegratoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("RTFMACRO", pOV, &pOV->m_sRTFMacro, pNV, &pNV->m_sRTFMacro);
	sp.Execute("RTFDIAG", pOV, &pOV->m_sRTFDiag, pNV, &pNV->m_sRTFDiag);
	sp.Execute("SIGNATURE", pOV, &pOV->m_sSignature, pNV, &pNV->m_sSignature);
	sp.Execute("TOCLOSE", pOV, &pOV->m_bToClose, pNV, &pNV->m_bToClose);
	sp.Execute("STATOIMPORTAZIONE", pOV, &pOV->m_lStatoImportazione, pNV, &pNV->m_lStatoImportazione);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CRefertoIntegratoSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("::DeleteRecordset");
	}
	return bReturn;
}

CString CRefertoIntegratoSet::SetBaseFilter(const CString &strFilter)
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

BOOL CRefertoIntegratoSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}