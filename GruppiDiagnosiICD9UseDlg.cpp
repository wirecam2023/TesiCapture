#include "stdafx.h"
#include "Endox.h"
#include "GruppiDiagnosiICD9UseDlg.h"

#include "Endox.h"
#include "EsamiView.h"
#include "GruppiDiagnosiICD9Set.h"
#include "TipiEsameGruppiDiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiDiagnosiICD9UseDlg, CDialog)

CGruppiDiagnosiICD9UseDlg::CGruppiDiagnosiICD9UseDlg(CWnd* pParent, CEsamiView* pEsamiView, long lTipoEsame)
	: CDialog(CGruppiDiagnosiICD9UseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lTipoEsame = lTipoEsame;
}

CGruppiDiagnosiICD9UseDlg::~CGruppiDiagnosiICD9UseDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiDiagnosiICD9UseDlg, CDialog)
END_MESSAGE_MAP()

void CGruppiDiagnosiICD9UseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);
}

BOOL CGruppiDiagnosiICD9UseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	CString strFilter;

	CTipiEsameGruppiDiagnosiICD9Set setLista;

	strFilter.Format("IdTipoEsame=%li", m_lTipoEsame);
	setLista.SetOpenFilter(strFilter);
	if (setLista.OpenRecordset("CGruppiDiagnosiICD9UseDlg::OnInitDialog"))
	{
		CGruppiDiagnosiICD9Set setGruppi;

		while(!setLista.IsEOF())
		{
			strFilter.Format("ID=%li", setLista.m_lIDGruppo);
			setGruppi.SetOpenFilter(strFilter);
			if (setGruppi.OpenRecordset("CGruppiDiagnosiICD9UseDlg::OnInitDialog"))
			{
				if (!setGruppi.IsEOF())
				{
					int nIndex = m_ctrlListaGruppi.AddString(setGruppi.m_sDescrizione);
					m_ctrlListaGruppi.SetItemData(nIndex, (DWORD)setGruppi.m_lID);
				}

				setGruppi.CloseRecordset("CGruppiDiagnosiICD9UseDlg::OnInitDialog");
			}

			setLista.MoveNext();
		}

		setLista.CloseRecordset("CGruppiDiagnosiICD9UseDlg::OnInitDialog");
	}

	return bReturn;
}

void CGruppiDiagnosiICD9UseDlg::OnOK()
{
	int nIndex = m_ctrlListaGruppi.GetCurSel();

	if (nIndex < 0)
		m_lReturn = -1;
	else
		m_lReturn = (long)m_ctrlListaGruppi.GetItemData(nIndex);

	CDialog::OnOK();
}