//Gabriel BUG 6225 - Lista DO
#include "stdafx.h"
#include "Endox.h"
#include "RiconvocazioneSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRiconvocazioneSet, CBaseSet)

CRiconvocazioneSet::CRiconvocazioneSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 23;
}

CString CRiconvocazioneSet::GetDefaultSQL()
{
	return "RICONVOCAZIONE";
}

void CRiconvocazioneSet::SetEmpty()
{
	m_lId = -1;
	m_lIdEsame = 0;
	m_sFicha = "";
	m_sDataOraEsame = "";
	m_sDataOraRiconvocazione = "";
	m_sUtente = "";
	m_sUnita = "";
	m_sMarca = "";
	m_sUnitaRiconvocazione = "";
	m_lIdMedicoRiconvocazione = 0;
	m_sCodicePrestazioneRiconvocazione = "";
	m_sCodicePrestazione = "";
	m_sPreparazione = "";
	m_lIdMotivo = -1;
	m_sDescrizioneMotivo = "";
	m_sMotivoAnnullamento = "";
	m_bBloccaEsame = FALSE;
	m_bPassivoDeReferto = FALSE;
	m_sCorpoEmail = "";
	m_sInviatoA = "";
	m_bEseguito = FALSE;
	m_sEsito = "";
	m_bEliminato = FALSE;
}

void CRiconvocazioneSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Id", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IdEsame", m_lIdEsame);
		RFX_Text(pFX, "Ficha", m_sFicha, 50);
		RFX_Text(pFX, "DataOraEsame", m_sDataOraEsame, 14);
		RFX_Text(pFX, "DataOraRiconvocazione", m_sDataOraRiconvocazione, 14);
		RFX_Text(pFX, "Utente", m_sUtente, 50);
		RFX_Text(pFX, "Unita", m_sUnita);
		RFX_Text(pFX, "Marca", m_sMarca, 200);
		RFX_Text(pFX, "UnitaRiconvocazione", m_sUnitaRiconvocazione);
		RFX_Long(pFX, "IdMedicoRiconvocazione", m_lIdMedicoRiconvocazione);
		RFX_Text(pFX, "CodicePrestazione", m_sCodicePrestazione, 50);
		RFX_Text(pFX, "CodicePrestazioneRiconvocazione", m_sCodicePrestazioneRiconvocazione, 50);
		RFX_Text(pFX, "Preparazione", m_sPreparazione, 200);
		RFX_Long(pFX, "IdMotivo", m_lIdMotivo);
		RFX_Text(pFX, "DescrizioneMotivo", m_sDescrizioneMotivo, 200);
		RFX_Text(pFX, "MotivoAnnullamento", m_sMotivoAnnullamento, 200);
		RFX_Bool(pFX, "BloccaEsame", m_bBloccaEsame);
		RFX_Bool(pFX, "PassivoDeReferto", m_bPassivoDeReferto);
		RFX_Text(pFX, "CorpoEmail", m_sCorpoEmail, 5000);
		RFX_Text(pFX, "InviatoA", m_sInviatoA, 2000);
		RFX_Bool(pFX, "Eseguito", m_bEseguito);
		RFX_Text(pFX, "Esito", m_sEsito);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CRiconvocazioneSet::CreateNew()
{
	return (CBaseSet*)new CRiconvocazioneSet;
}

void CRiconvocazioneSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CRiconvocazioneSet* pSet = (CRiconvocazioneSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pSet->m_lIdEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFicha) || bCopyAll)
		m_sFicha = pSet->m_sFicha;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOraEsame) || bCopyAll)
		m_sDataOraEsame = pSet->m_sDataOraEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOraRiconvocazione) || bCopyAll)
		m_sDataOraRiconvocazione = pSet->m_sDataOraRiconvocazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUtente) || bCopyAll)
		m_sUtente = pSet->m_sUtente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUnita) || bCopyAll)
		m_sUnita = pSet->m_sUnita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMarca) || bCopyAll)
		m_sMarca = pSet->m_sMarca;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUnitaRiconvocazione) || bCopyAll)
		m_sUnitaRiconvocazione = pSet->m_sUnitaRiconvocazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdMedicoRiconvocazione) || bCopyAll)
		m_lIdMedicoRiconvocazione = pSet->m_lIdMedicoRiconvocazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePrestazioneRiconvocazione) || bCopyAll)
		m_sCodicePrestazioneRiconvocazione = pSet->m_sCodicePrestazioneRiconvocazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePrestazione) || bCopyAll)
		m_sCodicePrestazione = pSet->m_sCodicePrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPreparazione) || bCopyAll)
		m_sPreparazione = pSet->m_sPreparazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdMotivo) || bCopyAll)
		m_lIdMotivo = pSet->m_lIdMotivo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizioneMotivo) || bCopyAll)
		m_sDescrizioneMotivo = pSet->m_sDescrizioneMotivo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMotivoAnnullamento) || bCopyAll)
		m_sMotivoAnnullamento = pSet->m_sMotivoAnnullamento;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bBloccaEsame) || bCopyAll)
		m_bBloccaEsame = pSet->m_bBloccaEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPassivoDeReferto) || bCopyAll)
		m_bPassivoDeReferto = pSet->m_bPassivoDeReferto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCorpoEmail) || bCopyAll)
		m_sCorpoEmail = pSet->m_sCorpoEmail;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sInviatoA) || bCopyAll)
		m_sInviatoA = pSet->m_sInviatoA;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEseguito) || bCopyAll)
		m_bEseguito = pSet->m_bEseguito;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEsito) || bCopyAll)
		m_sEsito = pSet->m_sEsito;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CRiconvocazioneSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CRiconvocazioneSet* pOV = (CRiconvocazioneSet*)pOldValues;
	CRiconvocazioneSet* pNV = (CRiconvocazioneSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("Ficha", pOV, &pOV->m_sFicha, pNV, &pNV->m_sFicha);
	sp.Execute("DataOraEsame", pOV, &pOV->m_sDataOraEsame, pNV, &pNV->m_sDataOraEsame);
	sp.Execute("DataOraRiconvocazione", pOV, &pOV->m_sDataOraRiconvocazione, pNV, &pNV->m_sDataOraRiconvocazione);
	sp.Execute("Utente", pOV, &pOV->m_sUtente, pNV, &pNV->m_sUtente);
	sp.Execute("Unita", pOV, &pOV->m_sUnita, pNV, &pNV->m_sUnita);
	sp.Execute("Marca", pOV, &pOV->m_sMarca, pNV, &pNV->m_sMarca);
	sp.Execute("UnitaRiconvocazione", pOV, &pOV->m_sUnitaRiconvocazione, pNV, &pNV->m_sUnitaRiconvocazione);
	sp.Execute("IdMedicoRiconvocazione", pOV, &pOV->m_lIdMedicoRiconvocazione, pNV, &pNV->m_lIdMedicoRiconvocazione);
	sp.Execute("CodicePrestazioneRiconvocazione", pOV, &pOV->m_sCodicePrestazioneRiconvocazione, pNV, &pNV->m_sCodicePrestazioneRiconvocazione);
	sp.Execute("CodicePrestazione", pOV, &pOV->m_sCodicePrestazione, pNV, &pNV->m_sCodicePrestazione);	
	sp.Execute("Preparazione", pOV, &pOV->m_sPreparazione, pNV, &pNV->m_sPreparazione);
	sp.Execute("IdMotivo", pOV, &pOV->m_lIdMotivo, pNV, &pNV->m_lIdMotivo);
	sp.Execute("DescrizioneMotivo", pOV, &pOV->m_sDescrizioneMotivo, pNV, &pNV->m_sDescrizioneMotivo);
	sp.Execute("MotivoAnnullamento", pOV, &pOV->m_sMotivoAnnullamento, pNV, &pNV->m_sMotivoAnnullamento);
	sp.Execute("BloccaEsame", pOV, &pOV->m_bBloccaEsame, pNV, &pNV->m_bBloccaEsame);
	sp.Execute("PassivoDeReferto", pOV, &pOV->m_bPassivoDeReferto, pNV, &pNV->m_bPassivoDeReferto);
	sp.Execute("CorpoEmail", pOV, &pOV->m_sCorpoEmail, pNV, &pNV->m_sCorpoEmail);
	sp.Execute("InviatoA", pOV, &pOV->m_sInviatoA, pNV, &pNV->m_sInviatoA);
	sp.Execute("Eseguito", pOV, &pOV->m_bEseguito, pNV, &pNV->m_bEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CRiconvocazioneSet::DeleteRecordset(const CString &strCommento)
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

CString CRiconvocazioneSet::SetBaseFilter(const CString &strFilter)
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

BOOL CRiconvocazioneSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

BOOL CRiconvocazioneSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Id=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("Id");
	if (OpenRecordset("CRiconvocazioneSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CRiconvocazioneSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CRiconvocazioneSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CRiconvocazioneSet::SetEliminato");
	}

	return bReturn;
}

BOOL CRiconvocazioneSet::SetMotivoAnnullamento(long lID, CString sMotivo)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Id=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("Id");
	if (OpenRecordset("CRiconvocazioneSet::SetMotivoAnnullamento"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CRiconvocazioneSet::SetMotivoAnnullamento"))
			{
				m_sMotivoAnnullamento = sMotivo;
				if (UpdateRecordset("CRiconvocazioneSet::SetMotivoAnnullamento"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CRiconvocazioneSet::SetEliminato");
	}

	return bReturn;
}

long CRiconvocazioneSet::GetIdFromIdEsame(long lIdEsame)
{
	long lReturn = -1;

	CString strFilter;
	strFilter.Format("IdEsame=%li AND ELIMINATO = 0", lIdEsame);

	SetOpenFilter(strFilter);

	if (OpenRecordset("CRiconvocazioneSet::GetIdFromIdEsame"))
	{
		if (!IsEOF())
		{
			lReturn = m_lId;
		}

		CloseRecordset("CRiconvocazioneSet::GetIdFromIdEsame");
	}

	return lReturn;
}