#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemBool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridItemBool, CXTPPropertyGridItemBool)

CEndoGridItemBool::CEndoGridItemBool(UINT nID, BOOL bValue, BOOL* pBindBool)
: CXTPPropertyGridItemBool(nID, bValue, pBindBool)
{
	SetTrueFalseText(theApp.GetMessageString(IDS_YES),
		theApp.GetMessageString(IDS_NO));
}

CEndoGridItemBool::CEndoGridItemBool(CString strCaption, BOOL bValue, BOOL* pBindBool)
	: CXTPPropertyGridItemBool(strCaption, bValue, pBindBool)
{
	SetTrueFalseText(theApp.GetMessageString(IDS_YES),
		theApp.GetMessageString(IDS_NO));
}

CEndoGridItemBool::~CEndoGridItemBool(void)
{
}

void CEndoGridItemBool::OnValueChanged(CString strValue)
{
	CXTPPropertyGridItem::OnValueChanged(strValue);

	NotifyDirty();
}

void CEndoGridItemBool::NotifyDirty()
{
	if (m_pGrid)
		m_pGrid->GetParent()->PostMessage(EPM_ITEMDIRTY);
}