#pragma once

#include "EndoGridItem.h"
#include "EndoGridItemEdit.h"
#include "EndoGridItemBool.h"
#include "EndoGridItemDate.h"
#include "EndoGridItemSex.h"
#include "EndoGridItemNumber.h"
#include "EndoGridItemDouble.h"
#include "EndoGridItemCheck.h"
#include "EndoGridItemNotes.h"
#include "EndoGridItemEnum.h"
#include "EndoGridItemEdit.h"
#include "EndoGridItemEditDate.h"

//Standard data grid exchange functions
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemEdit*   pItem, CString& value, CAMBaseSet* pRecordset);
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemBool*   pItem, BOOL& value, CAMBaseSet* pRecordset);
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemEnum*   pItem, long& value, CAMBaseSet* pRecordset);
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemCheck*   pItem, BOOL& value, CAMBaseSet* pRecordset);
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemDate*   pItem, CString& value, CAMBaseSet* pRecordset);
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemSex*    pItem, long& value, CAMBaseSet* pRecordset);
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemDouble* pItem, float& value, CAMBaseSet* pRecordset);
extern void AFXAPI DDX_GridItem(CDataExchange* pDX, CEndoGridItemNumber* pItem, long& value, CAMBaseSet* pRecordset);
