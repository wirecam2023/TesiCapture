#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviOldUseDlg.h"

#include "GruppiPrelieviOldSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviOldUseDlg, CDialog)

CGruppiPrelieviOldUseDlg::CGruppiPrelieviOldUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CGruppiPrelieviOldUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CGruppiPrelieviOldUseDlg::~CGruppiPrelieviOldUseDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiPrelieviOldUseDlg, CDialog)

	ON_LBN_DBLCLK(IDC_LISTA_GRUPPI, OnLbnDblclkListaGruppi)

END_MESSAGE_MAP()

void CGruppiPrelieviOldUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

BOOL CGruppiPrelieviOldUseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CGruppiPrelieviOldSet setGruppi;
	if (setGruppi.OpenRecordset("CGruppiPrelieviOldUseDlg::OnInitDialog"))
	{
		while(!setGruppi.IsEOF())
		{
			int nIndex = m_ctrlListaGruppi.AddString(setGruppi.m_sDescrizione);
			m_ctrlListaGruppi.SetItemData(nIndex, (DWORD)setGruppi.m_lID);

			setGruppi.MoveNext();
		}

		setGruppi.CloseRecordset("CGruppiPrelieviOldUseDlg::OnInitDialog");
	}

	theApp.LocalizeDialog(this, CGruppiPrelieviOldUseDlg::IDD, "CGruppiPrelieviOldUseDlg");
	return TRUE;
}

void CGruppiPrelieviOldUseDlg::OnOK()
{
	int nIndex = m_ctrlListaGruppi.GetCurSel();

	if (nIndex < 0)
		m_lReturn = -1;
	else
		m_lReturn = (long)m_ctrlListaGruppi.GetItemData(nIndex);

	CDialog::OnOK();
}

void CGruppiPrelieviOldUseDlg::OnLbnDblclkListaGruppi()
{
	if (m_ctrlListaGruppi.GetCurSel() >= 0)
		OnOK();
}
