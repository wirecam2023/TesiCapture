#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridItemNumber, CXTPPropertyGridItemNumber)

CEndoGridItemNumber::CEndoGridItemNumber(CString strCaption, long nValue, long* pBindNumber)
: CXTPPropertyGridItemNumber(strCaption, (nValue != 0xFFFFFFFF) ? nValue : 0, pBindNumber)
{
}

CEndoGridItemNumber::CEndoGridItemNumber(UINT nID, long nValue, long* pBindNumber)
	: CXTPPropertyGridItemNumber(nID, (nValue != 0xFFFFFFFF) ? nValue : 0, pBindNumber)
{
}

CEndoGridItemNumber::~CEndoGridItemNumber()
{
}

void CEndoGridItemNumber::OnValueChanged(CString strValue)
{
	CXTPPropertyGridItemNumber::OnValueChanged(strValue);
}