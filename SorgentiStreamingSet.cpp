#include "stdafx.h"
#include "Endox.h"
#include "SorgentiStreamingSet.h"

#include "CustomDate.h"
#include "EsamiSet.h"
#include "PazientiSet.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSorgentiStreamingSet, CBaseSet)

CSorgentiStreamingSet::CSorgentiStreamingSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();
	
	m_nFields = 7;
}

CString CSorgentiStreamingSet::GetDefaultSQL()
{
	return "SorgentiStreaming";
}

void CSorgentiStreamingSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sIndirizzoCompleto = "";
	m_sNomeComputerSala = "";
	m_sPazienteEsame = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CSorgentiStreamingSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "IndirizzoCompleto", m_sIndirizzoCompleto, 255);
		RFX_Text(pFX, "NomeComputerSala", m_sNomeComputerSala, 255);
		RFX_Text(pFX, "PazienteEsame", m_sPazienteEsame, 4000);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CSorgentiStreamingSet::CreateNew()
{
	return (CBaseSet*)new CSorgentiStreamingSet;
}

void CSorgentiStreamingSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSorgentiStreamingSet* pSet = (CSorgentiStreamingSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIndirizzoCompleto) || bCopyAll)
		m_sIndirizzoCompleto = pSet->m_sIndirizzoCompleto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNomeComputerSala) || bCopyAll)
		m_sNomeComputerSala = pSet->m_sNomeComputerSala;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPazienteEsame) || bCopyAll)
		m_sPazienteEsame = pSet->m_sPazienteEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CSorgentiStreamingSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSorgentiStreamingSet* pOV = (CSorgentiStreamingSet*)pOldValues;
	CSorgentiStreamingSet* pNV = (CSorgentiStreamingSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("IndirizzoCompleto", pOV, &pOV->m_sIndirizzoCompleto, pNV, &pNV->m_sIndirizzoCompleto);
	sp.Execute("NomeComputerSala", pOV, &pOV->m_sNomeComputerSala, pNV, &pNV->m_sNomeComputerSala);
	sp.Execute("PazienteEsame", pOV, &pOV->m_sPazienteEsame, pNV, &pNV->m_sPazienteEsame);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CSorgentiStreamingSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CSorgentiStreamingSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CSorgentiStreamingSet::DeleteRecordset");
	}
	return bReturn;
}

CString CSorgentiStreamingSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CSorgentiStreamingSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CSorgentiStreamingSet::ResetPazienteEsame()
{
	CString sComputer = theApp.m_sNomeComputer;
	sComputer.Replace("'", "''");

	CString sFilter;
	sFilter.Format("NomeComputerSala='%s'", sComputer);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CSorgentiStreamingSet::ResetPazienteEsame"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSorgentiStreamingSet::ResetPazienteEsame"))
			{
				m_sPazienteEsame = "";
				UpdateRecordset("CSorgentiStreamingSet::ResetPazienteEsame");
			}
		}

		CloseRecordset("CSorgentiStreamingSet::ResetPazienteEsame");
	}
}

void CSorgentiStreamingSet::SetPazienteEsame(CPazientiSet* pPazientiSet, CEsamiSet* pEsamiSet)
{
	CString sComputer = theApp.m_sNomeComputer;
	sComputer.Replace("'", "''");

	CString sFilter;
	sFilter.Format("NomeComputerSala='%s'", sComputer);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CSorgentiStreamingSet::ResetPazienteEsame"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSorgentiStreamingSet::ResetPazienteEsame"))
			{
				CString sDataNascita = "";
				if ((!pPazientiSet->IsFieldNull(&pPazientiSet->m_lNatoIlCustom)) && (pPazientiSet->m_lNatoIlCustom > 0))
					sDataNascita = CCustomDate(pPazientiSet->m_lNatoIlCustom).GetDate("%d/%m/%Y");

				CString sDataEsame = "";
				if ((!pEsamiSet->IsFieldNull(&pEsamiSet->m_lData)) && (pEsamiSet->m_lData > 0))
					sDataEsame = CCustomDate(pEsamiSet->m_lData).GetDate("%d/%m/%Y");

				//

				m_sPazienteEsame = pPazientiSet->m_sCognome + " " + pPazientiSet->m_sNome + " ";

				if (!sDataNascita.IsEmpty())
					m_sPazienteEsame += "(" + sDataNascita + ")";

				m_sPazienteEsame += "\n";

				if (!pPazientiSet->m_sAssIden.IsEmpty())
					m_sPazienteEsame += pPazientiSet->m_sAssIden + "\n";

				m_sPazienteEsame += "\n";

				m_sPazienteEsame += CTipoEsameSet().GetDescrizione(pEsamiSet->m_lIDEsame) + " ";

				if (!sDataEsame.IsEmpty())
					m_sPazienteEsame += "(" + sDataEsame + ")";

				m_sPazienteEsame += "\n";

				if (!pEsamiSet->m_sCodEsame.IsEmpty())
					m_sPazienteEsame += pEsamiSet->m_sCodEsame;

				//

				UpdateRecordset("CSorgentiStreamingSet::ResetPazienteEsame");
			}
		}

		CloseRecordset("CSorgentiStreamingSet::ResetPazienteEsame");
	}
}

long CSorgentiStreamingSet::Add(CString sDescrizione, CString sIndirizzo, CString sComputer)
{
	long lReturn = 0;

	if (OpenRecordset("CSorgentiStreamingSet::Add"))
	{
		if (AddNewRecordset("CSorgentiStreamingSet::Add"))
		{
			m_sDescrizione = sDescrizione;
			m_sIndirizzoCompleto = sIndirizzo;
			m_sNomeComputerSala = sComputer;

			if (UpdateRecordset("CSorgentiStreamingSet::Add"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CSorgentiStreamingSet::Add");
	}

	return lReturn;
}

void CSorgentiStreamingSet::Edt(long lID, CString sDescrizione, CString sIndirizzo, CString sComputer)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CSorgentiStreamingSet::Edt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSorgentiStreamingSet::Edt"))
			{
				m_sDescrizione = sDescrizione;
				m_sIndirizzoCompleto = sIndirizzo;
				m_sNomeComputerSala = sComputer;
				UpdateRecordset("CSorgentiStreamingSet::Edt");
			}
		}

		CloseRecordset("CComboRAOSet::EdtPrestazione");
	}
}

BOOL CSorgentiStreamingSet::Del(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CSorgentiStreamingSet::Del"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CSorgentiStreamingSet::Del");

		CloseRecordset("CSorgentiStreamingSet::Del");
	}

	return bReturn;
}