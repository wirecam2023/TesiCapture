#include "stdafx.h"
#include "Endox.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipoEsameSet, CBaseSet)

CTipoEsameSet::CTipoEsameSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 16;
}

CString CTipoEsameSet::GetDefaultSQL()
{
	return "ETIPOESAME";
}

void CTipoEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "Sigla", m_sSigla, 50);
		RFX_Text(pFX, "SiglaPrenotazione", m_sSiglaPrenotazione, 50);
		RFX_Bool(pFX, "Privato", m_bPrivato);
		RFX_Long(pFX, "IDCronicita", m_lIDCronicita);
		RFX_Long(pFX, "ContatoreAnnuale", m_lContatoreAnnuale);
		RFX_Long(pFX, "Anno", m_lAnno);
		RFX_Text(pFX, "Stazione", m_sStazione, 1);
		RFX_Bool(pFX, "EsameScreening", m_bEsameScreening);
		RFX_Long(pFX, "Sfondo", m_lSfondo);
		RFX_Long(pFX, "EliminaCodeBack", m_lEliminaCodeBack);
		RFX_Long(pFX, "EliminaCodeFore", m_lEliminaCodeFore);
		RFX_Bool(pFX, "ErogaSoloPrestazioniPrincipali", m_bErogaSoloPrestazioniPrincipali);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CTipoEsameSet::SetEmpty()
{
	m_lContatore = 0;
	m_sDescrizione = "";
	m_sSigla = "";
	m_sSiglaPrenotazione = "";
	m_bPrivato = FALSE;
	m_lIDCronicita = 0;
	m_lContatoreAnnuale = 0;
	m_lAnno = 0;
	m_sStazione = "";
	m_bEsameScreening = FALSE;
	m_lSfondo = -1;
	m_lEliminaCodeBack = RGB(0, 0, 0);
	m_lEliminaCodeFore = RGB(255, 255, 255);
	m_bErogaSoloPrestazioniPrincipali = FALSE;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CString CTipoEsameSet::GetDescrizione(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(strFilter);
	if (OpenRecordset("CTipoEsameSet::GetDescrizione"))
	{
		if (!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CTipoEsameSet::GetDescrizione");
	}

	return strReturn;
}

CString CTipoEsameSet::GetSigla(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(strFilter);
	if (OpenRecordset("CTipoEsameSet::GetSigla"))
	{
		if (!IsEOF())
			strReturn = m_sSigla;

		CloseRecordset("CTipoEsameSet::GetSigla");
	}

	return strReturn;
}

CString CTipoEsameSet::GetSiglaPrenotazione(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(strFilter);
	if (OpenRecordset("CTipoEsameSet::GetSiglaPrenotazione"))
	{
		if (!IsEOF())
			strReturn = m_sSiglaPrenotazione;

		CloseRecordset("CTipoEsameSet::GetSiglaPrenotazione");
	}

	return strReturn;
}

BOOL CTipoEsameSet::IsPrivato(long lTipoEsame)
{
	BOOL bReturn = FALSE;

	if (lTipoEsame > 0)
	{
		CString strTemp;

		strTemp.Format("Contatore=%li", lTipoEsame);
		SetOpenFilter(strTemp);
		if (OpenRecordset("CTipoEsameSet::IsPrivato"))
		{
			if (!IsEOF())
				bReturn = m_bPrivato;

			CloseRecordset("CTipoEsameSet::IsPrivato");
		}
	}

	return bReturn;
}

long CTipoEsameSet::GetIDCronicita(long lTipoEsame)
{
	long lReturn = 0;

	if (lTipoEsame > 0)
	{
		CString strFilter;
		strFilter.Format("Contatore=%li", lTipoEsame);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CTipoEsameSet::GetIDCronicita"))
		{
			if (!IsEOF())
				lReturn = m_lIDCronicita;

			CloseRecordset("CTipoEsameSet::GetIDCronicita");
		}
	}

	return lReturn;
}

long CTipoEsameSet::GetSfondo(long lTipoEsame)
{
	long lReturn = GetSysColor(COLOR_BTNFACE);

	if (lTipoEsame > 0)
	{
		CString strFilter;
		strFilter.Format("Contatore=%li", lTipoEsame);

		SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		SetOpenFilter(strFilter);
		if (OpenRecordset("CTipoEsameSet::GetSfondo"))
		{
			if (!IsEOF())
				if (m_lSfondo >= 0)
					lReturn = m_lSfondo;

			CloseRecordset("CTipoEsameSet::GetSfondo");
		}
	}

	return lReturn;
}

void CTipoEsameSet::GetColoriEliminaCode(long lTipoEsame, long& lColoreBackR, long& lColoreBackG, long& lColoreBackB, long& lColoreForeR, long& lColoreForeG, long& lColoreForeB)
{
	lColoreBackR = 0;
	lColoreBackG = 0;
	lColoreBackB = 0;

	lColoreForeR = 255;
	lColoreForeG = 255;
	lColoreForeB = 255;

	if (lTipoEsame > 0)
	{
		CString strFilter;
		strFilter.Format("Contatore=%li", lTipoEsame);

		SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		SetOpenFilter(strFilter);
		if (OpenRecordset("CTipoEsameSet::GetColoriEliminaCode"))
		{
			if (!IsEOF())
			{
				lColoreBackR = GetRValue(m_lEliminaCodeBack);
				lColoreBackG = GetGValue(m_lEliminaCodeBack);
				lColoreBackB = GetBValue(m_lEliminaCodeBack);

				lColoreForeR = GetRValue(m_lEliminaCodeFore);
				lColoreForeG = GetGValue(m_lEliminaCodeFore);
				lColoreForeB = GetBValue(m_lEliminaCodeFore);
			}

			CloseRecordset("CTipoEsameSet::GetColoriEliminaCode");
		}
	}
}

long CTipoEsameSet::GetIdTipoEsameScreening()
{
	long lReturn = -1;

	CString strFilter;
	strFilter.Format("EsameScreening=1");

	SetBaseFilter("");
	SetOpenFilter(strFilter);
	if (OpenRecordset("CTipoEsameSet::GetIdTipoEsameScreening"))
	{
		if (!IsEOF())
			lReturn = m_lContatore;

		CloseRecordset("CTipoEsameSet::GetIdTipoEsameScreening");
	}

	return lReturn;
}

long CTipoEsameSet::FleuryTrans(CString sSigla, CString sDescrizione)
{
	long lReturn = 0;

	sSigla.Trim();
	sSigla.Replace("'", "''");

	sDescrizione.Trim();
	sDescrizione.Replace("'", "''");

	if ((!sSigla.IsEmpty()) && (!sDescrizione.IsEmpty()))
	{
		CString sFilter;
		sFilter.Format("SIGLA = '%s' AND DESCRIZIONE = '%s'", sSigla, sDescrizione);
		SetOpenFilter(sFilter);
		if (OpenRecordset("CTipoEsameSet::FleuryTrans"))
		{
			if (IsEOF())
			{
				if (AddNewRecordset("CTipoEsameSet::FleuryTrans"))
				{
					m_sSigla = sSigla;
					m_sDescrizione = sDescrizione;

					if (UpdateRecordset("CTipoEsameSet::FleuryTrans"))
						lReturn = GetLastAdd();
				}
			}
			else
			{
				lReturn = m_lContatore;
			}

			CloseRecordset("CTipoEsameSet::FleuryTrans");
		}
	}

	return lReturn;
}

CBaseSet* CTipoEsameSet::CreateNew()
{
	return (CBaseSet*)new CTipoEsameSet;
}

void CTipoEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipoEsameSet* pSet = (CTipoEsameSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSigla) || bCopyAll)
		m_sSigla = pSet->m_sSigla;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSiglaPrenotazione) || bCopyAll)
		m_sSiglaPrenotazione = pSet->m_sSiglaPrenotazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPrivato) || bCopyAll)
		m_bPrivato = pSet->m_bPrivato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCronicita) || bCopyAll)
		m_lIDCronicita = pSet->m_lIDCronicita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lContatoreAnnuale) || bCopyAll)
		m_lContatoreAnnuale = pSet->m_lContatoreAnnuale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lAnno) || bCopyAll)
		m_lAnno = pSet->m_lAnno;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sStazione) || bCopyAll)
		m_sStazione = pSet->m_sStazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEsameScreening) || bCopyAll)
		m_bEsameScreening = pSet->m_bEsameScreening;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lSfondo) || bCopyAll)
		m_lSfondo = pSet->m_lSfondo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEliminaCodeBack) || bCopyAll)
		m_lEliminaCodeBack = pSet->m_lEliminaCodeBack;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEliminaCodeFore) || bCopyAll)
		m_lEliminaCodeFore = pSet->m_lEliminaCodeFore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bErogaSoloPrestazioniPrincipali) || bCopyAll)
		m_bErogaSoloPrestazioniPrincipali = pSet->m_bErogaSoloPrestazioniPrincipali;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipoEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipoEsameSet* pOV = (CTipoEsameSet*)pOldValues;
	CTipoEsameSet* pNV = (CTipoEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Sigla", pOV, &pOV->m_sSigla, pNV, &pNV->m_sSigla);
	sp.Execute("SiglaPrenotazione", pOV, &pOV->m_sSiglaPrenotazione, pNV, &pNV->m_sSiglaPrenotazione);
	sp.Execute("Privato", pOV, &pOV->m_bPrivato, pNV, &pNV->m_bPrivato);
	sp.Execute("IDCronicita", pOV, &pOV->m_lIDCronicita, pNV, &pNV->m_lIDCronicita);
	// sp.Execute("ContatoreAnnuale", pOV, &pOV->m_lContatoreAnnuale, pNV, &pNV->m_lContatoreAnnuale);
	// sp.Execute("Anno", pOV, &pOV->m_lAnno, pNV, &pNV->m_lAnno);
	// sp.Execute("Stazione", pOV, &pOV->m_sStazione, pNV, &pNV->m_sStazione);
	sp.Execute("EsameScreening", pOV, &pOV->m_bEsameScreening, pNV, &pNV->m_bEsameScreening);
	sp.Execute("Sfondo", pOV, &pOV->m_lSfondo, pNV, &pNV->m_lSfondo);
	sp.Execute("EliminaCodeBack", pOV, &pOV->m_lEliminaCodeBack, pNV, &pNV->m_lEliminaCodeBack);
	sp.Execute("EliminaCodeFore", pOV, &pOV->m_lEliminaCodeFore, pNV, &pNV->m_lEliminaCodeFore);
	sp.Execute("ErogaSoloPrestazioniPrincipali", pOV, &pOV->m_bErogaSoloPrestazioniPrincipali, pNV, &pNV->m_bErogaSoloPrestazioniPrincipali);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipoEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipoEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipoEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTipoEsameSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CTipoEsameSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
