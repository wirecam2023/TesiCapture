#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemNotes.h"
#include "NotesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridItemNotes, CEndoGridItemEdit)

CEndoGridItemNotes::CEndoGridItemNotes(UINT nID, LPCTSTR strValue, CString* pBindString, CAMBaseSet* pSet, long lComboTable/*, BOOL bCheckReadOnly*/)
: CEndoGridItemEdit(nID, strValue, pBindString, pSet, lComboTable/*, bCheckReadOnly*/)
{
	SetFlags(GetFlags() | xtpGridItemHasExpandButton);
}

CEndoGridItemNotes::CEndoGridItemNotes(CString strCaption, LPCTSTR strValue, CString* pBindString, CAMBaseSet* pSet, long lComboTable/*, BOOL bCheckReadOnly*/)
	: CEndoGridItemEdit(strCaption, strValue, pBindString, pSet, lComboTable/*, bCheckReadOnly*/)
{
	SetFlags(GetFlags() | xtpGridItemHasExpandButton);
}

CEndoGridItemNotes::~CEndoGridItemNotes()
{
}

void CEndoGridItemNotes::OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton)
{
	CString strValue;
	strValue = GetValue();
	CNotesDlg dlg(&strValue);
	if (dlg.DoModal() == IDOK)
	{
		OnValueChanged(strValue);
		SetValue(strValue);
	}

	GetGrid()->GetPropertyGrid()->RedrawControl();
}

void CEndoGridItemNotes::SetValue(CString strValue)
{
	strValue.Replace("\r\n", " - ");
	CEndoGridItemEdit::SetValue(strValue);
}

CString CEndoGridItemNotes::GetValue()
{
	CString strValue = CEndoGridItemEdit::GetValue();
	strValue.Replace(" - ", "\r\n");
	return strValue;
}

CString CEndoGridItemNotes::GetToolTipText()
{
	CString strValue = CEndoGridItemEdit::GetValue();
	strValue.Replace(" - ", "\n");
	return strValue;

	//return CEndoGridItemEdit::GetValue();
}
