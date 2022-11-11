#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemDouble.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridItemDouble, CXTPPropertyGridItemDouble)

CEndoGridItemDouble::CEndoGridItemDouble(UINT nID, double dValue, double* pBindNumber, LPCTSTR strFormat)
: CXTPPropertyGridItemDouble(nID, (dValue != float(0xFFFFFFFFFFFFFFFF)) ? dValue : 0, strFormat, pBindNumber)
{
}

CEndoGridItemDouble::CEndoGridItemDouble(CString strCaption, double dValue, double* pBindNumber, LPCTSTR strFormat)
	: CXTPPropertyGridItemDouble(strCaption, (dValue != float(0xFFFFFFFFFFFFFFFF)) ? dValue : 0, strFormat, pBindNumber)
{
}

CEndoGridItemDouble::~CEndoGridItemDouble()
{
}

void CEndoGridItemDouble::OnValueChanged(CString strValue)
{
	CXTPPropertyGridItemDouble::OnValueChanged(strValue);
}