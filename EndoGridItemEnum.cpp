#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemEnum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridItemEnum, CXTPPropertyGridItem)

CEndoGridItemEnum::CEndoGridItemEnum(CString strCaption)
: CXTPPropertyGridItem(strCaption)
{
	m_nFlags = xtpGridItemHasComboButton | xtpGridItemHasEdit;
	SetConstraintEdit(TRUE);
}

CEndoGridItemEnum::~CEndoGridItemEnum(void)
{
}

void CEndoGridItemEnum::SetEnumValue(long lValue)
{
	CString str;
	for (POSITION pos = m_list.GetHeadPosition(); pos;)
	{
		tagVALUE tv = m_list.GetNext(pos);
		if (tv.lID == lValue)
			str = tv.szValue;
	}
	CXTPPropertyGridItem::SetValue(str);
}

long CEndoGridItemEnum::GetEnumValue()
{
	CString str = CXTPPropertyGridItem::GetValue();
	long lReturn = -1;
	for (POSITION pos = m_list.GetHeadPosition(); pos;)
	{
		tagVALUE tv = m_list.GetNext(pos);
		if (strcmp(tv.szValue, str) == 0)
			lReturn = tv.lID;
	}
	return lReturn;
}

void CEndoGridItemEnum::AddEnumValue(long lID, CString strValue)
{
	GetConstraints()->AddConstraint(strValue);

	tagVALUE tv;
	tv.lID = lID;
	strcpy_s(tv.szValue, strValue);
	m_list.AddTail(tv);
}

void CEndoGridItemEnum::OnValueChanged(CString strValue)
{
	CXTPPropertyGridItem::OnValueChanged(strValue);

	if (m_pGrid)
		m_pGrid->GetParent()->PostMessage(EPM_ITEMDIRTY);
}
