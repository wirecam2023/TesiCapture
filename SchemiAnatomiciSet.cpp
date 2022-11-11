// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#include "stdafx.h"
#include "Endox.h"
#include "SchemiAnatomiciSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSchemiAnatomiciSet, CBaseSet)

CSchemiAnatomiciSet::CSchemiAnatomiciSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("ELIMINATO=0");
	SetEmpty();

	m_nFields = 9;
}

CString CSchemiAnatomiciSet::GetDefaultSQL()
{
	return "SCHEMI_ANATOMICI";
}

void CSchemiAnatomiciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Text(pFX, "CODICEPRESTAZIONEPREVISTA", m_sCodicePrestazionePrevista);
		RFX_Text(pFX, "IMMAGINE_FULLPATH", m_sImmagine_FullPath);
		RFX_Long(pFX, "IMMAGINE_LARGHEZZA", m_lImmagine_Larghezza);
		RFX_Long(pFX, "IMMAGINE_ALTEZZA", m_lImmagine_Altezza);
		RFX_Double(pFX, "ZOOM_FACTOR", m_dZoom_Factor);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);

		m_pSchemiAnatomici.m_lID = m_lID;
		m_pSchemiAnatomici.m_sDescrizione = m_sDescrizione;
		m_pSchemiAnatomici.m_lUO = m_lUO;
		m_pSchemiAnatomici.m_sCodicePrestazionePrevista = m_sCodicePrestazionePrevista;
		m_pSchemiAnatomici.m_sImmagine_FullPath = m_sImmagine_FullPath;
		m_pSchemiAnatomici.m_lImmagine_Larghezza = m_lImmagine_Larghezza;
		m_pSchemiAnatomici.m_lImmagine_Altezza = m_lImmagine_Altezza;
		m_pSchemiAnatomici.m_dZoom_Factor = m_dZoom_Factor;
		m_pSchemiAnatomici.m_bEliminato = m_bEliminato;

		//	ID	int
		//	DESCRIZIONE	varchar(50)
		//	UO	int
		//	CODICEPRESTAZIONEPREVISTA	[varchar](50)
		//	IMMAGINE_FULLPATH	[varchar](255)
		//	IMMAGINE_LARGHEZZA	int
		//	IMMAGINE_ALTEZZA	int
		//	ELIMINATO	bool

	}
}

void CSchemiAnatomiciSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_sCodicePrestazionePrevista = "";
	m_sImmagine_FullPath = "";
	m_lImmagine_Larghezza = 0;
	m_lImmagine_Altezza = 0;
	m_dZoom_Factor = 0;
	m_bEliminato = FALSE;

	m_pSchemiAnatomici.m_lID = 0;
	m_pSchemiAnatomici.m_sDescrizione = "";
	m_pSchemiAnatomici.m_lUO = 0;
	m_pSchemiAnatomici.m_sCodicePrestazionePrevista = "";
	m_pSchemiAnatomici.m_sImmagine_FullPath = "";
	m_pSchemiAnatomici.m_lImmagine_Larghezza = 0;
	m_pSchemiAnatomici.m_lImmagine_Altezza = 0;
	m_pSchemiAnatomici.m_dZoom_Factor = 0;
	m_pSchemiAnatomici.m_bEliminato = FALSE;
}

CBaseSet* CSchemiAnatomiciSet::CreateNew()
{
	return (CBaseSet*)new CSchemiAnatomiciSet;
}

void CSchemiAnatomiciSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSchemiAnatomiciSet* pSet = (CSchemiAnatomiciSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePrestazionePrevista) || bCopyAll)
		m_sCodicePrestazionePrevista = pSet->m_sCodicePrestazionePrevista;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sImmagine_FullPath) || bCopyAll)
		m_sImmagine_FullPath = pSet->m_sImmagine_FullPath;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lImmagine_Larghezza) || bCopyAll)
		m_lImmagine_Larghezza = pSet->m_lImmagine_Larghezza;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lImmagine_Altezza) || bCopyAll)
		m_lImmagine_Altezza = pSet->m_lImmagine_Altezza;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_dZoom_Factor) || bCopyAll)
		m_dZoom_Factor = pSet->m_dZoom_Factor;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CSchemiAnatomiciSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSchemiAnatomiciSet* pOV = (CSchemiAnatomiciSet*)pOldValues;
	CSchemiAnatomiciSet* pNV = (CSchemiAnatomiciSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("IDESAME", pOV, &pOV->m_sCodicePrestazionePrevista, pNV, &pNV->m_sCodicePrestazionePrevista);
	sp.Execute("IMMAGINE", pOV, &pOV->m_sImmagine_FullPath, pNV, &pNV->m_sImmagine_FullPath);
	sp.Execute("IMMAGINE_LARGHEZZA", pOV, &pOV->m_lImmagine_Larghezza, pNV, &pNV->m_lImmagine_Larghezza);
	sp.Execute("IMMAGINE_ALTEZZA", pOV, &pOV->m_lImmagine_Altezza, pNV, &pNV->m_lImmagine_Altezza);
	sp.Execute("ZOOM_FACTOR", pOV, &pOV->m_dZoom_Factor, pNV, &pNV->m_dZoom_Factor);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CSchemiAnatomiciSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset(strCommento))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset(strCommento);
	}
	return bReturn;
}


CString CSchemiAnatomiciSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	//CString strUO;
	//strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		//strNewFilter = strUO + " AND ELIMINATO=0";
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		//if (strNewFilter.Find("UO=") < 0)
		//	strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CSchemiAnatomiciSet::UpdateRecordset(const CString &strCommento)
{
	//if (m_nEditMode == addnew)
	//	m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

/*
CSchemiAnatomici CSchemiAnatomiciSet::getObjSchemiAnatomici(long p_lID)
{
	SetEmpty();
	if (p_lID <= 0) // NEW ONE - VOID ONE
	{
		Find(p_lID);
	}
	return m_pSchemiAnatomici;
}
*/

//BOOL CSchemiAnatomiciSet::SoftRefreshData(CSchemiAnatomici* p_pSchemiAnatomici)
//{
//	if (p_pSchemiAnatomici == NULL || !IsOpen())
//		return FALSE;
//
//	p_pSchemiAnatomici->m_lID = m_pSchemiAnatomici.m_lID;
//	p_pSchemiAnatomici->m_sDescrizione = m_pSchemiAnatomici.m_sDescrizione;
//	p_pSchemiAnatomici->m_lUO = m_pSchemiAnatomici.m_lUO;
//	p_pSchemiAnatomici->m_sCodicePrestazionePrevista = m_pSchemiAnatomici.m_sCodicePrestazionePrevista;
//	p_pSchemiAnatomici->m_sImmagine_FullPath = m_pSchemiAnatomici.m_sImmagine_FullPath;
//	p_pSchemiAnatomici->m_lImmagine_Larghezza = m_pSchemiAnatomici.m_lImmagine_Larghezza;
//	p_pSchemiAnatomici->m_lImmagine_Altezza = m_pSchemiAnatomici.m_lImmagine_Altezza;
//	p_pSchemiAnatomici->m_dZoom_Factor = m_pSchemiAnatomici.m_dZoom_Factor;
//	p_pSchemiAnatomici->m_bEliminato = m_pSchemiAnatomici.m_bEliminato;
//	return TRUE;
//}

BOOL CSchemiAnatomiciSet::Find(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CSchemiAnatomiciSet::Find"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;
			//DoFieldExchange();
		}
		CloseRecordset("CSchemiAnatomiciSet::Find");
	}
	return bReturn;
}

/* Sugestão do Julio 24/03/2020
BOOL CSchemiAnatomiciSet::Insert(long lID)
{

	CString sFilter;
	sFilter.Format("IDESAME=%li AND TIPO='%s'", GetTipoAsString(Tipo::StatusChange));

	SetOpenFilter(sFilter);
	if (OpenRecordset("CExtComboPrestazioni::Insert"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CExtComboPrestazioni::Insert"))
			{
				m_lIDEsame = lIDEsame;
				m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
				AMLogin_GetUserID(&m_lIDUtente);
				m_lEseguito = 0;
				m_sEsito = "";
				m_lIDEsameChiuso = lIDEsameChiuso;
				m_sTipo = GetTipoAsString(Tipo::StatusChange);

				UpdateRecordset("CExtComboPrestazioni::Insert");
			}

			CloseRecordset("CExtComboPrestazioni::Insert");
		}
	}
	
}
*/