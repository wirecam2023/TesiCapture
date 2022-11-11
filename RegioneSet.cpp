#include "stdafx.h"
#include "Endox.h"
#include "RegioneSet.h"
#include "CodificaRegionaleExSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRegioneSet, CBaseSet)

CRegioneSet::CRegioneSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 11;
}

CString CRegioneSet::GetDefaultSQL()
{
	return "EREGIONE";
}

void CRegioneSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lCodice = 0;
	m_lIdExtPrestazione = 0;
	m_lQuantita = 0;
	m_lStatoCUP = 0;
	m_sTipoAccesso = "";
	m_sNotaPrescrizione = "";
	m_sNotaPrestazione = "";
	m_bPrescrizionePinzataSuOriginale = FALSE;
	m_bEliminato = FALSE;
}

void CRegioneSet::CopyFieldFrom(CRegioneSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore	= pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame	= pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lCodice))
		m_lCodice	= pSet->m_lCodice;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIdExtPrestazione))
		m_lIdExtPrestazione	= pSet->m_lIdExtPrestazione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lQuantita))
		m_lQuantita	= pSet->m_lQuantita;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lStatoCUP))
		m_lStatoCUP	= pSet->m_lStatoCUP;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTipoAccesso))
		m_sTipoAccesso = pSet->m_sTipoAccesso;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNotaPrescrizione))
		m_sNotaPrescrizione = pSet->m_sNotaPrescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNotaPrestazione))
		m_sNotaPrestazione = pSet->m_sNotaPrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPrescrizionePinzataSuOriginale))
		m_bPrescrizionePinzataSuOriginale = pSet->m_bPrescrizionePinzataSuOriginale;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
		
	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CRegioneSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Esame", m_lEsame);
		RFX_Long(pFX, "Codice", m_lCodice);
		RFX_Long(pFX, "Quantita", m_lQuantita);
		RFX_Long(pFX, "IdExtPrestazione", m_lIdExtPrestazione);
		RFX_Long(pFX, "StatoCUP", m_lStatoCUP);
		RFX_Text(pFX, "TipoAccesso", m_sTipoAccesso, 50);
		RFX_Text(pFX, "NOTAPRESCRIZIONE", m_sNotaPrescrizione, 3999);
		RFX_Text(pFX, "NOTAPRESTAZIONE", m_sNotaPrestazione, 3999);
		RFX_Bool(pFX, "PRESCPINZATASUORIGINALE", m_bPrescrizionePinzataSuOriginale);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CRegioneSet::GetFieldText(long lEsame)
{
	CString strReturn = "";

	CCodificaRegionaleExSet setTemp;

	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::GetFieldText"))
	{
		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetFieldText(m_lCodice);

			MoveNext();
		}
		CloseRecordset("CRegioneSet::GetFieldText");
	}

	return strReturn;
}

CString CRegioneSet::GetStringDescrizioni(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::GetStringDescrizioni"))
	{
		CCodificaRegionaleExSet setTemp;

		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetStringDescrizione(m_lCodice);

			MoveNext();
		}
		CloseRecordset("CRegioneSet::GetStringDescrizioni");
	}

	return strReturn;
}

CString CRegioneSet::GetStringDescrizioniGrande(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::GetStringDescrizioniGrande"))
	{
		while(!IsEOF())
		{
			strFilter.Format("Contatore=%li", m_lCodice);

			CCodificaRegionaleExSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("CRegioneSet::GetStringDescrizioniGrande"))
			{
				if (!setTemp.IsEOF())
				{
					CString strRow;
					strRow.Format("%li x %s %s", m_lQuantita, setTemp.m_sCodiceNazionale, setTemp.m_sDescrizione);

					if (!strReturn.IsEmpty())
						strReturn += "\n";

					strReturn += strRow;
				}

				setTemp.CloseRecordset("CRegioneSet::GetStringDescrizioniGrande");
			}

			MoveNext();
		}
		CloseRecordset("CRegioneSet::GetStringDescrizioniGrande");
	}

	return strReturn;
}

BOOL CRegioneSet::ExamHasPrestazioniNonNormate(long lEsame)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::ExamHasPrestazioni"))
	{
		while (!IsEOF())
		{
			if (!CCodificaRegionaleExSet().IsNormata(m_lCodice))
			{
				bReturn = TRUE;
				break;
			}

			MoveNext();
		}

		CloseRecordset("CRegioneSet::ExamHasPrestazioni");
	}

	return bReturn;
}

BOOL CRegioneSet::ExamHasNotNormedServicesWithoutPrescription(long lEsame)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Esame=%li and NRE is null and RUR is null and IUP is null", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::ExamHasServicesWithoutNRE"))
	{
		while (!IsEOF())
		{
			if (!CCodificaRegionaleExSet().IsNormata(m_lCodice))
			{
				//Se ne trovo una senza prescrizione e non normata, torno TRUE
				bReturn = TRUE;
				break;
			}

			MoveNext();
		}

		CloseRecordset("CRegioneSet::ExamHasServicesWithoutNRE");
	}

	return bReturn;
}

long CRegioneSet::GetIdExt(long lIdPrestazione)
{
	long lReturn = -1;

	CString strFilter;
	strFilter.Format("contatore=%li", lIdPrestazione);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::GetIdExt"))
	{
		lReturn = m_lIdExtPrestazione;

		CloseRecordset("CRegioneSet::GetIdExt");
	}

	return lReturn;
}

BOOL CRegioneSet::ExamHasOriginalRURPrescription(long lIDEsame)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Esame=%li and RUR IS NOT NULL AND IDEXTPRESTAZIONE IS NOT NULL and IDEXTPRESTAZIONE > 0", lIDEsame);

	SetBaseFilter("(ELIMINATO=0 or ELIMINATO=1)"); //cerco anche tra le eliminate
	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::ExamHasOriginalRURPrescription"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;			
		}

		CloseRecordset("CRegioneSet::ExamHasOriginalRURPrescription");
	}

	return bReturn;
}

CString CRegioneSet::GetPrestazioniWithoutPrescriptionListAsString(long lIDEsame)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li and NRE is null and RUR is null and IUP is null", lIDEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::GetPrestazioniListAsString"))
	{
		while (!IsEOF())
		{
			if (sReturn.IsEmpty())
				sReturn = CCodificaRegionaleExSet().GetStringCodiceSiss(m_lCodice) + " - " + CCodificaRegionaleExSet().GetStringDescrizione(m_lCodice);
			else
					sReturn += "\r\n" + CCodificaRegionaleExSet().GetStringCodiceSiss(m_lCodice) + " - " + CCodificaRegionaleExSet().GetStringDescrizione(m_lCodice);

			MoveNext();
		}

		CloseRecordset("CRegioneSet::GetPrestazioniListAsString");
	}

	return sReturn;
}

/*void CRegioneSet::SetCosto(long lContatore, CString sCosto)
{
	long lReturn = -1;

	CString strFilter;
	strFilter.Format("contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CRegioneSet::SetCosto"))
	{
		if (EditRecordset("CRegioneSet::SetCosto"))
		{
			m_sCosto = sCosto;
			UpdateRecordset("CRegioneSet::SetCosto");
		}

		CloseRecordset("CRegioneSet::SetCosto");
	}
}*/

CBaseSet* CRegioneSet::CreateNew()
{
	return (CBaseSet*)new CRegioneSet;
}

void CRegioneSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CRegioneSet* pTemparioSet = (CRegioneSet*)pOriginalSet;

	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_lEsame) || bCopyAll)
		m_lEsame = pTemparioSet->m_lEsame;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_lCodice) || bCopyAll)
		m_lCodice = pTemparioSet->m_lCodice;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_lIdExtPrestazione) || bCopyAll)
		m_lIdExtPrestazione = pTemparioSet->m_lIdExtPrestazione;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_lQuantita) || bCopyAll)
		m_lQuantita = pTemparioSet->m_lQuantita;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_lStatoCUP) || bCopyAll)
		m_lStatoCUP	= pTemparioSet->m_lStatoCUP;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_sTipoAccesso) || bCopyAll)
		m_sTipoAccesso = pTemparioSet->m_sTipoAccesso;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_sNotaPrescrizione) || bCopyAll)
		m_sNotaPrescrizione = pTemparioSet->m_sNotaPrescrizione;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_sNotaPrestazione) || bCopyAll)
		m_sNotaPrestazione = pTemparioSet->m_sNotaPrestazione;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_bPrescrizionePinzataSuOriginale) || bCopyAll)
		m_bPrescrizionePinzataSuOriginale = pTemparioSet->m_bPrescrizionePinzataSuOriginale;
	if (!pTemparioSet->IsOpen() || pTemparioSet->IsFieldDirty(&pTemparioSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pTemparioSet->m_bEliminato;
}

void CRegioneSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CRegioneSet* pOV = (CRegioneSet*)pOldValues;
	CRegioneSet* pNV = (CRegioneSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Codice", pOV, &pOV->m_lCodice, pNV, &pNV->m_lCodice);
	sp.Execute("IdExtPrestazione", pOV, &pOV->m_lIdExtPrestazione, pNV, &pNV->m_lIdExtPrestazione);
	sp.Execute("Quantita", pOV, &pOV->m_lQuantita, pNV, &pNV->m_lQuantita);
	sp.Execute("StatoCUP", pOV, &pOV->m_lStatoCUP, pNV, &pNV->m_lStatoCUP);
	sp.Execute("TipoAccesso", pOV, &pOV->m_sTipoAccesso, pNV, &pNV->m_sTipoAccesso);
	sp.Execute("NOTAPRESCRIZIONE", pOV, &pOV->m_sNotaPrescrizione, pNV, &pNV->m_sNotaPrescrizione);
	sp.Execute("NOTAPRESTAZIONE", pOV, &pOV->m_sNotaPrestazione, pNV, &pNV->m_sNotaPrestazione);
	sp.Execute("PRESCPINZATASUORIGINALE", pOV, &pOV->m_bPrescrizionePinzataSuOriginale, pNV, &pNV->m_bPrescrizionePinzataSuOriginale);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CRegioneSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CRegioneSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CRegioneSet::DeleteRecordset");
	}
	return bReturn;
}

CString CRegioneSet::SetBaseFilter(const CString &strFilter)
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