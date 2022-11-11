#include "stdafx.h"
#include "Endox.h"
#include "NotesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNotesDlg, CXTResizeDialog)

CNotesDlg::CNotesDlg(CString* pString, CWnd* pParent)
: CXTResizeDialog(CNotesDlg::IDD, pParent)
{
	m_pNotes = pString;
}

CNotesDlg::~CNotesDlg()
{
}

void CNotesDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NOTES, *m_pNotes);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
}

BEGIN_MESSAGE_MAP(CNotesDlg, CXTResizeDialog)
END_MESSAGE_MAP()

// CNotesDlg message handlers

BOOL CNotesDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_NOTES, 0, 0, 1, 1);
	SetResize(IDOK, 1, 1, 1, 1);
	SetResize(IDCANCEL, 1, 1, 1, 1);

	theApp.LocalizeDialog(this, CNotesDlg::IDD, "NotesDlg");

	return TRUE;
}