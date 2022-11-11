#include "stdafx.h"
#include "Endox.h"
#include "Path.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPath::CPath()
{ 
	m_lPaziente = 0;
	m_lEsame = 0;
	m_lID = 0;
	m_pImgListOrgani = NULL;
	m_lIndex = -1;
	m_bConfirmed = FALSE;
	m_strDvdLabel = "";
	m_szDesc[0] = '\0';
}

void CPath::SetParameter(long lPaziente, long lEsame, long lID, CImgListOrgani *pImgListOrgani, long lIndex, BOOL bConfirmed, CString strDvdLabel, CString strPaziente, long lDataEsame)
{ 
	CCustomDate date(lDataEsame);
	CString strTemp = strPaziente + date.GetDate(" %d.%m.%Y");
	memcpy(m_szDesc, strTemp.GetBuffer(), min(strTemp.GetLength() + 1, 1024));

	m_lPaziente = lPaziente;
	m_lEsame = lEsame;
	m_lID = lID;
	m_pImgListOrgani = pImgListOrgani;
	m_lIndex = lIndex;
	m_bConfirmed = bConfirmed;
	m_strDvdLabel = strDvdLabel;
}