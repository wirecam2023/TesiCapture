#include "stdafx.h"
#include "MyResizableDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMyResizableDialog::CMyResizableDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CResizableDialog(nIDTemplate, pParentWnd)
{}
