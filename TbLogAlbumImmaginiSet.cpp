#include "stdafx.h"
#include "Endox.h"
#include "TbLogAlbumImmaginiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTbLogAlbumImmaginiSet, CBaseSet)

CTbLogAlbumImmaginiSet::CTbLogAlbumImmaginiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 8;
}

CString CTbLogAlbumImmaginiSet::GetDefaultSQL()
{
	return "tb_LogAlbumImmagini";
}

void CTbLogAlbumImmaginiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDImmagine", m_lIDImmagine);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Text(pFX, "Utente", m_sUtente, 50);
		RFX_Text(pFX, "Stazione", m_sStazione, 50);
		RFX_Long(pFX, "Operazione", m_lOperazione);
	}
}

void CTbLogAlbumImmaginiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_lIDImmagine = 0;
	m_sDataOra = "";
	m_sUtente = "";
	m_sStazione = "";
	m_lOperazione = 0;
}

BOOL CTbLogAlbumImmaginiSet::HasRigheDopoDataOra(long lIDEsame, CString sDataOra)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("IDEsame = %li AND DataOra >= '%s'", lIDEsame, sDataOra);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CTbLogAlbumImmaginiSet::HasRigheDopoDataOra"))
	{
		bReturn = !IsEOF();
		CloseRecordset("CTbLogAlbumImmaginiSet::HasRigheDopoDataOra");
	}

	return bReturn;
}