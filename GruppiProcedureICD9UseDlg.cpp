#include "stdafx.h"
#include "Endox.h"
#include "GruppiProcedureICD9UseDlg.h"

#include "Endox.h"
#include "EsamiView.h"
#include "GruppiProcedureICD9Set.h"
#include "TipiEsameGruppiProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiProcedureICD9UseDlg, CDialog)

CGruppiProcedureICD9UseDlg::CGruppiProcedureICD9UseDlg(CWnd* pParent, CEsamiView* pEsamiView, long lTipoEsame)
	: CDialog(CGruppiProcedureICD9UseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lTipoEsame = lTipoEsame;
}

CGruppiProcedureICD9UseDlg::~CGruppiProcedureICD9UseDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiProcedureICD9UseDlg, CDialog)
END_MESSAGE_MAP()

void CGruppiProcedureICD9UseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);
}

BOOL CGruppiProcedureICD9UseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	CString strFilter;

	CTipiEsameGruppiProcedureICD9Set setLista;

	strFilter.Format("IdTipoEsame=%li", m_lTipoEsame);
	setLista.SetOpenFilter(strFilter);
	if (setLista.OpenRecordset("CGruppiProcedureICD9UseDlg::OnInitDialog"))
	{
		CGruppiProcedureICD9Set setGruppi;

		while(!setLista.IsEOF())
		{
			strFilter.Format("ID=%li", setLista.m_lIDGruppo);
			setGruppi.SetOpenFilter(strFilter);
			if (setGruppi.OpenRecordset("CGruppiProcedureICD9UseDlg::OnInitDialog"))
			{
				if (!setGruppi.IsEOF())
				{
					int nIndex = m_ctrlListaGruppi.AddString(setGruppi.m_sDescrizione);
					m_ctrlListaGruppi.SetItemData(nIndex, (DWORD)setGruppi.m_lID);
				}

				setGruppi.CloseRecordset("CGruppiProcedureICD9UseDlg::OnInitDialog");
			}

			setLista.MoveNext();
		}

		setLista.CloseRecordset("CGruppiProcedureICD9UseDlg::OnInitDialog");
	}

	return bReturn;
}

void CGruppiProcedureICD9UseDlg::OnOK()
{
	int nIndex = m_ctrlListaGruppi.GetCurSel();

	if (nIndex < 0)
		m_lReturn = -1;
	else
		m_lReturn = (long)m_ctrlListaGruppi.GetItemData(nIndex);

	CDialog::OnOK();
}