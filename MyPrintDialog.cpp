#include "stdafx.h"
#include "Endox.h"
#include "MyPrintDialog.h"
#include ".\myprintdialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMyPrintDialog, CPrintDialog)

CMyPrintDialog::CMyPrintDialog(BOOL bPrintSetupOnly, DWORD dwFlags, CWnd* pParentWnd) :
	CPrintDialog(bPrintSetupOnly, dwFlags, pParentWnd)
{
}

CMyPrintDialog::~CMyPrintDialog()
{
}

BEGIN_MESSAGE_MAP(CMyPrintDialog, CPrintDialog)
END_MESSAGE_MAP()

BOOL CMyPrintDialog::OnInitDialog()
{
	BOOL bReturn = CPrintDialog::OnInitDialog();

	

	return bReturn;
}

void CMyPrintDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO: aggiungere qui il codice specifico e/o chiamare la classe base

	CPrintDialog::DoDataExchange(pDX);
}
