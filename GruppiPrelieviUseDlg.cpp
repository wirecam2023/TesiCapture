#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviUseDlg.h"

#include "EsamiView.h"
#include "GruppiPrelieviSet.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviUseDlg, CDialog)

CGruppiPrelieviUseDlg::CGruppiPrelieviUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CGruppiPrelieviUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CGruppiPrelieviUseDlg::~CGruppiPrelieviUseDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiPrelieviUseDlg, CDialog)

	ON_LBN_DBLCLK(IDC_LISTA_GRUPPI, OnLbnDblclkListaGruppi)

END_MESSAGE_MAP()

void CGruppiPrelieviUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

BOOL CGruppiPrelieviUseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strFilter;
	strFilter.Format("APSede='%s'", CSediEsameSet().GetAPSede(m_pEsamiView->m_pEsamiSet->m_lIDSedeEsame));

	CGruppiPrelieviSet setGruppi;
	setGruppi.SetOpenFilter(strFilter);
	if (setGruppi.OpenRecordset("CGruppiPrelieviUseDlg::OnInitDialog"))
	{
		while(!setGruppi.IsEOF())
		{
			int nIndex = m_ctrlListaGruppi.AddString(setGruppi.m_sDescrizione);
			m_ctrlListaGruppi.SetItemData(nIndex, (DWORD)setGruppi.m_lID);

			setGruppi.MoveNext();
		}

		setGruppi.CloseRecordset("CGruppiPrelieviUseDlg::OnInitDialog");
	}

	theApp.LocalizeDialog(this, CGruppiPrelieviUseDlg::IDD, "GruppiPrelieviUseDlg");
	return TRUE;
}

void CGruppiPrelieviUseDlg::OnOK()
{
	int nIndex = m_ctrlListaGruppi.GetCurSel();

	if (nIndex < 0)
		m_lReturn = -1;
	else
		m_lReturn = (long)m_ctrlListaGruppi.GetItemData(nIndex);

	CDialog::OnOK();
}

void CGruppiPrelieviUseDlg::OnLbnDblclkListaGruppi()
{
	if (m_ctrlListaGruppi.GetCurSel() >= 0)
		OnOK();
}
