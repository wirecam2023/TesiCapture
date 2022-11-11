#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemEditDate.h"
#include "EndoGridMonthCalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridItemEditDate, CEndoGridItemEdit)

CEndoGridItemEditDate::CEndoGridItemEditDate(CString strCaption)
: CEndoGridItemEdit(strCaption)
{
	SetFlags(GetFlags() | xtpGridItemHasExpandButton);
	m_strFormat = _T("%d/%m/%Y");
}

CEndoGridItemEditDate::~CEndoGridItemEditDate(void)
{
}

void CEndoGridItemEditDate::OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton)
{
	CRect rect = GetItemRect();
	//Davide - new Codejock
	m_pGrid->GetPropertyGrid()->ClientToScreen(&rect);

	int iOffsetY = rect.Height();
	rect.top += iOffsetY;
	rect.bottom += iOffsetY;

	CEndoGridMonthCalDlg dlg(theApp.GetServerDate(), rect, m_strFormat);
	if (dlg.DoModal() == IDOK)
	{
		SetValue(dlg.m_strDate + " ");
		NotifyDirty();
	}

	if (m_wndEdit.GetSafeHwnd() && m_wndEdit.IsWindowVisible())
	{
		m_wndEdit.SetSel(GetValue().GetLength(), GetValue().GetLength(), TRUE);
		m_wndEdit.SetFocus();
	}
}