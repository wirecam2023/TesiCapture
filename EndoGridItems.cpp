#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItems.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemEdit* pItem, CString& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate)
	{
		value = pItem->GetValue();
		if (value.IsEmpty())
		{
			if (pRecordset && pRecordset->IsOpen() && pRecordset->IsFieldNullable(&value))
				pRecordset->SetFieldNull(&value, TRUE);
		}
		else
		{
			if (pRecordset)
			{
				int iIndex = pRecordset->GetBoundFieldIndex(&value) - 1;
				if (iIndex > 0)
				{
					CODBCFieldInfo info;
					pRecordset->GetODBCFieldInfo(iIndex, info);
					value = value.Left(info.m_nPrecision);
				}
			}

			pRecordset->SetFieldDirty(&value, TRUE);
			pRecordset->SetFieldNull(&value, FALSE);
		}
	}
	else
	{
		pItem->SetValue((pRecordset && pRecordset->IsOpen()) ? value : _T(""));
	}
}

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemBool* pItem, BOOL& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate && pRecordset && pRecordset->IsOpen())
	{
		pRecordset->SetFieldDirty(&value, TRUE);
		pRecordset->SetFieldNull(&value, FALSE);
		value = pItem->GetBool();
	}
	else if (!pDX->m_bSaveAndValidate)
	{
		pItem->SetBool((pRecordset &&
			pRecordset->IsOpen() &&
			!pRecordset->IsEOF() &&
			!pRecordset->IsBOF() &&
			!pRecordset->IsFieldNull(&value)) ? value : FALSE);
	}
}

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemEnum* pItem, long& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate && pRecordset && pRecordset->IsOpen())
	{
		pRecordset->SetFieldDirty(&value, TRUE);
		pRecordset->SetFieldNull(&value, FALSE);
		value = pItem->GetEnumValue();
	}
	else if (!pDX->m_bSaveAndValidate)
	{
		pItem->SetEnumValue((pRecordset &&
			pRecordset->IsOpen() &&
			!pRecordset->IsEOF() &&
			!pRecordset->IsBOF() &&
			!pRecordset->IsFieldNull(&value)) ? value : FALSE);
	}
}

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemCheck* pItem, BOOL& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate && pRecordset && pRecordset->IsOpen())
	{
		pRecordset->SetFieldDirty(&value, TRUE);
		pRecordset->SetFieldNull(&value, FALSE);
		value = pItem->GetBool();
	}
	else if (!pDX->m_bSaveAndValidate)
	{
		pItem->SetBool((pRecordset &&
			pRecordset->IsOpen() &&
			!pRecordset->IsEOF() &&
			!pRecordset->IsBOF() &&
			!pRecordset->IsFieldNull(&value)) ? value : FALSE);
	}
}

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemDate* pItem, CString& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate)
	{
		if (pItem->IsValidDate())
		{
			value = pItem->GetDate();
			pRecordset->SetFieldDirty(&value, TRUE);
			pRecordset->SetFieldNull(&value, FALSE);

		}
		else
		{
			if (pRecordset && pRecordset->IsOpen() && pRecordset->IsFieldNullable(&value))
				pRecordset->SetFieldNull(&value, TRUE);

			if (pItem->GetValue() != pItem->GetLiteral())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DATE_FORMAT_INVALID), MB_ICONSTOP);
				pItem->SetDate("");
			}
		}
	}
	else
	{
		pItem->SetDate((value.GetLength() == 14 && (!pRecordset || !pRecordset->IsFieldNull(&value))) ? value : "");
	}
}

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemSex* pItem, long& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate)
	{
		pRecordset->SetFieldDirty(&value, TRUE);
		pRecordset->SetFieldNull(&value, FALSE);
		value = pItem->GetSex();
	}
	else
	{
		if (!pRecordset->IsFieldNull(&value))
			pItem->SetSex(value);
		else
			pItem->SetSex(2);
	}
}

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemDouble* pItem, float& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate)
	{
		pRecordset->SetFieldDirty(&value, TRUE);
		pRecordset->SetFieldNull(&value, FALSE);
		value = (float)pItem->GetDouble();
	}
	else
	{
		if (pRecordset && !pRecordset->IsFieldNull(&value))
			pItem->SetDouble(value);
		else
			pItem->CXTPPropertyGridItem::SetValue("");
	}
}

void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemNumber* pItem, long& value, CAMBaseSet* pRecordset)
{
	if (!pItem)
		return;

	if (pDX->m_bSaveAndValidate && pRecordset && pRecordset->IsOpen())
	{
		pRecordset->SetFieldDirty(&value, TRUE);
		pRecordset->SetFieldNull(&value, FALSE);
		value = pItem->GetNumber();
	}
	else if (!pDX->m_bSaveAndValidate)
	{
		//If field is null set 0 as default value
		if (pRecordset && !pRecordset->IsFieldNull(&value))
			pItem->SetNumber(value);
		else
			pItem->SetNumber(0);
	}
}

