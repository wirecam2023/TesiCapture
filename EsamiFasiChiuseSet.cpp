#include "stdafx.h"
#include "Endox.h"
#include "EsamiFasiChiuseSet.h"
#include "EsamiSet.h"

#include "CustomDate.h"
#include "DLL_Imaging\h\AmLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiFasiChiuseSet, CBaseSet)

CEsamiFasiChiuseSet::CEsamiFasiChiuseSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 8; // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
}

CString CEsamiFasiChiuseSet::GetDefaultSQL()
{
	return "ESAMIFASICHIUSE";
}

void CEsamiFasiChiuseSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);
		RFX_Long(pFX, "IDFASE", m_lIDFase);
		RFX_Long(pFX, "IDPDF", m_lIDPdf);
		RFX_Text(pFX, "DATAORA", m_sDataOra, 14);
		RFX_Long(pFX, "IDUTENTE", m_lIDUtente);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
		RFX_Text(pFX, "MOTIVO", m_sMotivo); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	}
}

void CEsamiFasiChiuseSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDFase = 0;
	m_lIDPdf = 0;
	m_sDataOra = "";
	m_lIDUtente = 0;
	m_bEliminato = FALSE;
	m_sMotivo = ""; // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
}

CBaseSet* CEsamiFasiChiuseSet::CreateNew()
{
	return (CBaseSet*)new CEsamiFasiChiuseSet;
}

void CEsamiFasiChiuseSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiFasiChiuseSet* pSet = (CEsamiFasiChiuseSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDFase) || bCopyAll)
		m_lIDFase = pSet->m_lIDFase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPdf) || bCopyAll)
		m_lIDPdf = pSet->m_lIDPdf;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOra) || bCopyAll)
		m_sDataOra = pSet->m_sDataOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pSet->m_lIDUtente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMotivo) || bCopyAll)// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		m_sMotivo = pSet->m_sMotivo;
}

void CEsamiFasiChiuseSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiFasiChiuseSet* pOV = (CEsamiFasiChiuseSet*)pOldValues;
	CEsamiFasiChiuseSet* pNV = (CEsamiFasiChiuseSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDFASE", pOV, &pOV->m_lIDFase, pNV, &pNV->m_lIDFase);
	sp.Execute("IDPDF", pOV, &pOV->m_lIDPdf, pNV, &pNV->m_lIDPdf);
	sp.Execute("DATAORA", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IDUTENTE", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
	sp.Execute("MOTIVO", pOV, &pOV->m_sMotivo, pNV, &pNV->m_sMotivo); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
}

BOOL CEsamiFasiChiuseSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiFasiChiuseSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiFasiChiuseSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiFasiChiuseSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

long CEsamiFasiChiuseSet::Insert(long lIDEsame, long lIDFase, long lIDPdf)
{
	long lReturn = 0;

	if (OpenRecordset("CEsamiFasiChiuseSet::Insert"))
	{
		if (AddNewRecordset("CEsamiFasiChiuseSet::Insert"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDFase = lIDFase;
			m_lIDPdf = lIDPdf;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_sMotivo = ""; // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
			AMLogin_GetUserID(&m_lIDUtente);

			if (UpdateRecordset("CEsamiFasiChiuseSet::Insert"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CEsamiFasiChiuseSet::Insert");
	}

	return lReturn;
}

// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
long CEsamiFasiChiuseSet::DelecaoLogicaComMotivo(long lIDEsame, long lIDFase, CString sMotivo)
{
	ASSERT(lIDEsame > 0 && lIDFase > 0 && sMotivo != "");

	long lRetorno = 0;
	CString filter;
	filter.Format("IDEsame=%li AND IDFase=%li AND ELIMINATO = 0", lIDEsame, lIDFase);

	CEsamiFasiChiuseSet set;
	set.SetOpenFilter(filter);

	try
	{
		if (set.OpenRecordset("CEsamiFasiChiuseSet::DelecaoLogicaComMotivo"))
		{
			if (!set.IsEOF())
			{
				if (set.EditRecordset("CEsamiFasiChiuseSet::DelecaoLogicaComMotivo"))
				{
					lRetorno = set.m_lID;
					AMLogin_GetUserID(&m_lIDUtente);
					set.m_sMotivo = sMotivo;
					set.m_bEliminato = TRUE;
					set.UpdateRecordset("CEsamiFasiChiuseSet::DelecaoLogicaComMotivo");
				}
			}
			CloseRecordset("CEsamiFasiChiuseSet::DelecaoLogicaComMotivo");
		}
	}
	catch (...)
	{
		theApp.AfxMessageBoxEndo("Erro ao anular Liberação de Laudo.");
	}
	return lRetorno;
}

BOOL CEsamiFasiChiuseSet::FaseAbertaExame(long lIDEsame, long lIDFase)
{
	ASSERT(lIDEsame > 0 && lIDFase > 0);

	BOOL bRetorno = FALSE;
	CString filter;
	filter.Format("IDEsame=%li AND IDFase=%li AND ELIMINATO = 0", lIDEsame, lIDFase);

	CEsamiFasiChiuseSet set;
	set.SetOpenFilter(filter);

	try
	{
		if (set.OpenRecordset("CEsamiFasiChiuseSet::FaseAbertaExame"))
		{
			if (!set.IsEOF())
			{
				bRetorno = TRUE;
			}
			set.CloseRecordset("CEsamiFasiChiuseSet::FaseAbertaExame");
		}
	}
	catch (...)
	{
		theApp.AfxMessageBoxEndo("Erro na busca de fase de laudo a anular.");
	}
	return bRetorno;
}