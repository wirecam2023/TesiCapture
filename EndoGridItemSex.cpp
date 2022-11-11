#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemSex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoGridItemSex::CEndoGridItemSex(CString strCaption)
	: CEndoGridItemEdit(strCaption)
{
	GetConstraints()->AddConstraint(theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
	GetConstraints()->AddConstraint(theApp.GetMessageString(IDS_PAZIENTIDLG_MALE));
	GetConstraints()->AddConstraint(theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE));
	GetConstraints()->AddConstraint(theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS));
	GetConstraints()->AddConstraint(theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE));
	GetConstraints()->AddConstraint(theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER));

	SetConstraintEdit(TRUE);
	SetFlags(GetFlags() | xtpGridItemHasComboButton);
}

CEndoGridItemSex::~CEndoGridItemSex(void)
{
}

void CEndoGridItemSex::SetSex(long lSex)
{
	if (GetConstraints()->GetCount() > lSex)
		SetValue(GetConstraints()->GetAt(lSex));
	else if (GetConstraints()->GetCount() > 0)
		SetValue(GetConstraints()->GetAt(0));

	/* Davide - New Codejock
	POSITION pos = GetConstraints()->FindIndex(lSex);
	if (pos)
	SetValue(GetConstraints()->GetAt(pos));
	else
	SetValue(GetConstraints()->GetHead());
	*/
}

long CEndoGridItemSex::GetSex()
{
	/* Davide - New Codejock
	POSITION pos = GetConstraints()->GetHeadPosition();
	int iIndex = 0;

	while (pos)
	{
	if (GetConstraints()->GetNext(pos) == GetValue())
	return iIndex;
	iIndex++;
	}

	return 0;*/

	int iIndex = 0;
	for (int i = 0; i < GetConstraints()->GetCount(); i++)
	{
		if (GetConstraints()->GetAt(i) == GetValue())
		{
			iIndex = i;
			break;
		}
	}
	return iIndex;
}