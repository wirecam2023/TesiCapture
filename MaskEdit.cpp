#include "stdafx.h"
#include "Endox.h"
#include "MaskEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMaskEdit, CXTMaskEditTEndox<CEdit>);

CMaskEdit::CMaskEdit()
{
}

BEGIN_MESSAGE_MAP(CMaskEdit, CXTMaskEditTEndox<CEdit>)
	ON_MASKEDIT_REFLECT()
END_MESSAGE_MAP()