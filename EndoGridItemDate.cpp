#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemDate.h"
#include "EndoGridMonthCalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//CEndoGridItemDate
//////////////////////////////////////////////////////////////////////////////////////////

CEndoGridItemDate::CEndoGridItemDate(UINT nID, CString* pBindDate, BOOL bToday)
	: CEndoGridMaskEdit(nID)
{
	Init(pBindDate, bToday);
}

CEndoGridItemDate::CEndoGridItemDate(CString strCaption, CString* pBindDate, BOOL bToday)
	: CEndoGridMaskEdit(strCaption)
{
	Init(pBindDate, bToday);
}

void CEndoGridItemDate::OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton)
{
	CRect rect = GetItemRect();
	m_pGrid->GetPropertyGrid()->ClientToScreen(&rect);

	int iOffsetY = rect.Height();
	rect.top += iOffsetY;
	rect.bottom += iOffsetY;

	CString strValue;
	if (IsValidDate())
		strValue = GetDate();
	else
		strValue = theApp.GetServerDate();

	CEndoGridMonthCalDlg dlg(strValue, rect, m_strFormat);
	if (dlg.DoModal() == IDOK)
	{
		SetValue(dlg.m_strDate);
		NotifyDirty();
	}
}

void CEndoGridItemDate::Init(CString* pBindDate, BOOL bToday)
{
	m_nFlags = xtpGridItemHasComboButton | xtpGridItemHasEdit;
	m_strFormat = _T("%d/%m/%Y");

	m_strEditMask = _T("00/00/0000");
	m_strLiteral = _T("__/__/____");

	m_strValue = _T("__/__/____");
	if (pBindDate && pBindDate->GetLength() == 14)
		m_strValue.Format("%s/%s/%s", pBindDate->Mid(6, 2), pBindDate->Mid(4, 2), pBindDate->Left(4));

	if (bToday)
	{
		COleDateTime time = COleDateTime::GetCurrentTime();
		if (pBindDate)
			*pBindDate = time.Format("%Y%m%d000000");
	}
}

void CEndoGridItemDate::NotifyDirty()
{
	if (m_pGrid)
		m_pGrid->GetParent()->PostMessage(EPM_ITEMDIRTY);
}

void CEndoGridItemDate::OnDeselect()
{
	if (GetLiteral() != GetValue() && !IsValidDate())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DATE_FORMAT_INVALID), MB_ICONSTOP);
		SetValue(GetLiteral());
	}

	CEndoGridMaskEdit::OnDeselect();
}

BOOL CEndoGridItemDate::IsValidDate()
{
	CString strLiteral = GetLiteral();
	CString str = GetValue();
	BOOL bDateValid = FALSE;

	if (str.GetLength() == strLiteral.GetLength())
	{
		CString d = str.Mid(0, 2);
		CString m = str.Mid(3, 2);
		CString Y = str.Mid(6, 4);

		if (str != strLiteral)
		{
			// Date is complete
			if (d != strLiteral.Mid(0, 2) && m != strLiteral.Mid(3, 2) && Y != strLiteral.Mid(6, 4) &&
				d.Find("_") == -1 && m.Find("_") == -1 && Y.Find("_") == -1)
			{
				int iDay = atoi(d);
				int iMonth = atoi(m);
				int iYear = atoi(Y);

				switch (iMonth)
				{
				case 1:   // January
				case 3:   // March
				case 5:   // May
				case 7:   // July
				case 8:   // August
				case 10:  // October
				case 12:  // December
					bDateValid = (iDay > 0 && iDay <= 31);
					break;

				case 2:   //February
					if (iYear % 4 == 0)
						bDateValid = (iDay > 0 && iDay <= 29);
					else
						bDateValid = (iDay > 0 && iDay <= 28);
					break;

				case 4:   //April
				case 6:   //June
				case 9:   //September
				case 11:  //November
					bDateValid = (iDay > 0 && iDay <= 30);
					break;

				default:
					break;
				}

				if (iYear < 1900 || iYear > 2100)
					bDateValid = FALSE;
			}
		}
	}

	return bDateValid;
}

void CEndoGridItemDate::SetDate(CString strDate)
{
	if (strDate.GetLength() == 14)
	{
		CString str;
		str.Format("%s/%s/%s",
			strDate.Mid(6, 2),
			strDate.Mid(4, 2),
			strDate.Left(4));
		SetValue(str);
	}
	else
		SetValue(GetLiteral());
}

CString CEndoGridItemDate::GetDate()
{
	ASSERT(IsValidDate());

	CString str, strDate = GetValue();
	str.Format("%s%s%s000000",
		strDate.Right(4),
		strDate.Mid(3, 2),
		strDate.Left(2));
	return str;
}

CString CEndoGridItemDate::GetValueEx()
{
	if (IsValidDate())
		return GetDate();

	return m_strLiteral;
}