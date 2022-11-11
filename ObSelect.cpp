#include "stdafx.h"
#include "Endox.h"
#include "ObSelect.h"

#include "FileBmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CObSelect, CObject)

CObSelect::CObSelect()
{
	m_lID = 0;
	m_bIsGlobal = FALSE;
	m_iType = -1;

	m_strDescription = "";

	m_lPaziente = 0;
	m_lEsame = 0;
	m_bConfirmed = FALSE;
	m_strDvdLabel = "";

	m_bCI = FALSE;
}

CObSelect::CObSelect(CFileBmp* pFileBmp)
{
	if (pFileBmp)
	{
		m_lID = pFileBmp->m_lID;
		m_bIsGlobal = pFileBmp->m_bIsAlbumGlobal;
		m_iType = pFileBmp->m_iType;

		m_strDescription = "";

		m_lPaziente = pFileBmp->m_lPaziente;
		m_lEsame = pFileBmp->m_lEsame;
		m_bConfirmed = pFileBmp->m_bConfirmed;
		m_strDvdLabel = pFileBmp->m_strDvdLabel;

		m_bCI = pFileBmp->m_bCI;
	}
	else
	{
		m_lID = 0;
		m_bIsGlobal = FALSE;
		m_iType = -1;

		m_strDescription = "";

		m_lPaziente = 0;
		m_lEsame = 0;
		m_bConfirmed = FALSE;
		m_strDvdLabel = "";

		m_bCI = FALSE;
	}
}

CObSelect::CObSelect(long lID, BOOL bIsGlobal, int iType, const CString &strDescription, long lPaziente, long lEsame, BOOL bConfirmed, const CString &strDvdLabel, BOOL bCI)
{
	m_lID = lID;
	m_bIsGlobal = bIsGlobal;
	m_iType = iType;

	m_strDescription = strDescription;

	m_lPaziente = lPaziente;
	m_lEsame = lEsame;
	m_bConfirmed = bConfirmed;
	m_strDvdLabel = strDvdLabel;

	m_bCI = bCI;
}