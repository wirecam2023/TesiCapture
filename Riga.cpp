#include "stdafx.h"
#include "Endox.h"
#include "Riga.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CRiga, CObject)

CRiga::CRiga()
{   
	m_nEsame		= 0;
	m_nPage			= 0;
	m_nDiapoPerEsame = NUM_MOSAIC_MAX;
}