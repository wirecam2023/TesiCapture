#include "stdafx.h"
#include "CustomDate.h"
#include "Endox.h"
#include "ExtComboPrestazioni.h"

#include "DLL_Imaging\h\AmLogin.h"
#include "VistaExtPrestazioniSet.h"//Julio - BUG 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// Luiz - 12/08/2019 - P4 - Permite envio de exames MAMOGUS de acordo com opção do usuário
IMPLEMENT_DYNAMIC(CExtComboPrestazioni, CBaseSet)

CExtComboPrestazioni::CExtComboPrestazioni()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 8; //Julio - BUG 3365 - MAMOGUS
}

CString CExtComboPrestazioni::GetDefaultSQL()
{
	return "EXT_COMBOPRESTAZIONI";
}

void CExtComboPrestazioni::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);
		RFX_Long(pFX, "IDESAMECHIUSO", m_lIDEsameChiuso);
		RFX_Text(pFX, "TIPO", m_sTipo, 2); //Julio - BUG 3365 - MAMOGUS (NW ou SC)
		RFX_Text(pFX, "DATAORA", m_sDataOra, 14);
		RFX_Long(pFX, "IDUTENTE", m_lIDUtente);
		RFX_Long(pFX, "ESEGUITO", m_lEseguito);
		RFX_Text(pFX, "ESITO", m_sEsito, 2000000);
	}
}

void CExtComboPrestazioni::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDEsameChiuso = 0;
	m_lIDUtente = 0;
	m_lEseguito = 0;
	m_sEsito = "";
	m_sDataOra = "";
	m_sTipo = ""; //Julio - BUG 3365 - MAMOGUS
}

CBaseSet* CExtComboPrestazioni::CreateNew()
{
	return (CBaseSet*)new CExtComboPrestazioni;
}

void CExtComboPrestazioni::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtComboPrestazioni* pSet = (CExtComboPrestazioni*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pSet->m_lIDUtente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOra) || bCopyAll)
		m_sDataOra = pSet->m_sDataOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEseguito) || bCopyAll)
		m_lEseguito = pSet->m_lEseguito;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEsito) || bCopyAll)
		m_sEsito = pSet->m_sEsito;
	
	//Julio - BUG 3365 - MAMOGUS
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTipo) || bCopyAll)
		m_sTipo = pSet->m_sTipo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsameChiuso) || bCopyAll)
		m_lIDEsameChiuso = pSet->m_lIDEsameChiuso;
}

void CExtComboPrestazioni::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtComboPrestazioni* pOV = (CExtComboPrestazioni*)pOldValues;
	CExtComboPrestazioni* pNV = (CExtComboPrestazioni*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDUTENTE", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("ESEGUITO", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("DATAORA", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("ESITO", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);

	//Julio - BUG 3365 - MAMOGUS
	sp.Execute("TIPO", pOV, &pOV->m_sTipo, pNV, &pNV->m_sTipo);
	sp.Execute("IDESAMECHIUSO", pOV, &pOV->m_lIDEsameChiuso, pNV, &pNV->m_lIDEsameChiuso);
}

BOOL CExtComboPrestazioni::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

CString CExtComboPrestazioni::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

//Julio - BUG 3365 - MAMOGUS
long CExtComboPrestazioni::Insert(long lIDEsame, Tipo eTipo, long lIDEsameChiuso)
{
	long lReturn = 0;
			
	//Caso um RE esteja sendo inserido e um SC nao foi previamente enviado, envio um SC antes de enviar o RE
	if (eTipo == Tipo::Report)
	{
		CString sFilter;
		CString sStatus = GetTipoAsString(Tipo::StatusChange);
		sFilter.Format("IDESAME=%li AND TIPO='%s'", lIDEsame, sStatus);
		
		SetOpenFilter(sFilter);
		if (OpenRecordset("CExtComboPrestazioni::Insert"))
		{
			if (!IsEOF())
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
	//

	SetOpenFilter("");
	if (OpenRecordset("CExtComboPrestazioni::Insert"))
	{
		if (AddNewRecordset("CExtComboPrestazioni::Insert"))
		{
			m_lIDEsame = lIDEsame;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			AMLogin_GetUserID(&m_lIDUtente);
			m_lEseguito = 0;
			m_sEsito = ""; 
			m_lIDEsameChiuso = lIDEsameChiuso;
			m_sTipo = GetTipoAsString(eTipo);

			if (UpdateRecordset("CExtComboPrestazioni::Insert"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CExtComboPrestazioni::Insert");
	}
	return lReturn;
}

CString CExtComboPrestazioni::GetTipoAsString(Tipo eTipo)
{
	CString sTipo = "";
	switch (eTipo)
	{
	case Tipo::Report:
		sTipo = "RE";
		break;
	case Tipo::StatusChange:
		sTipo = "SC";
		break;
	default:
		break;
	}

	return sTipo;
}

