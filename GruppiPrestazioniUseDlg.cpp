#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrestazioniUseDlg.h"

#include "Endox.h"
#include "EsamiView.h"
#include "GruppiPrestazioniSet.h"
#include "TipiEsamiGruppiPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrestazioniUseDlg, CDialog)

CGruppiPrestazioniUseDlg::CGruppiPrestazioniUseDlg(CWnd* pParent, CEsamiView* pEsamiView, long lTipoEsame)
	: CDialog(CGruppiPrestazioniUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lTipoEsame = lTipoEsame;
}

CGruppiPrestazioniUseDlg::~CGruppiPrestazioniUseDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiPrestazioniUseDlg, CDialog)
END_MESSAGE_MAP()

void CGruppiPrestazioniUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);
}

BOOL CGruppiPrestazioniUseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		// Sandro 18/11/2014 // RAS 20140046 //

		CGruppiPrestazioniSet setGruppi;
		setGruppi.SetSortRecord("Descrizione");
		if (setGruppi.OpenRecordset("CGruppiPrestazioniUseDlg::OnInitDialog"))
		{
			while(!setGruppi.IsEOF())
			{
				int nIndex = m_ctrlListaGruppi.AddString(setGruppi.m_sDescrizione);
				m_ctrlListaGruppi.SetItemData(nIndex, (DWORD)setGruppi.m_lID);

				setGruppi.MoveNext();
			}

			setGruppi.CloseRecordset("CGruppiPrestazioniUseDlg::OnInitDialog");
		}
	}
	else
	{
		CString strFilter = "";
		strFilter.Format("TipoEsame=%li", m_lTipoEsame);

		CTipiEsamiGruppiPrestazioniSet setLista;
		setLista.SetOpenFilter(strFilter);
		if (setLista.OpenRecordset("CGruppiPrestazioniUseDlg::OnInitDialog"))
		{
			while(!setLista.IsEOF())
			{
				strFilter.Format("ID=%li", setLista.m_lGruppo);

				CGruppiPrestazioniSet setGruppi;
				setGruppi.SetOpenFilter(strFilter);
				if (setGruppi.OpenRecordset("CGruppiPrestazioniUseDlg::OnInitDialog"))
				{
					if (!setGruppi.IsEOF())
					{
						int nIndex = m_ctrlListaGruppi.AddString(setGruppi.m_sDescrizione);
						m_ctrlListaGruppi.SetItemData(nIndex, (DWORD)setGruppi.m_lID);
					}

					setGruppi.CloseRecordset("CGruppiPrestazioniUseDlg::OnInitDialog");
				}

				setLista.MoveNext();
			}

			setLista.CloseRecordset("CGruppiPrestazioniUseDlg::OnInitDialog");
		}
	}

	return TRUE;
}

void CGruppiPrestazioniUseDlg::OnOK()
{
	int nIndex = m_ctrlListaGruppi.GetCurSel();

	if (nIndex < 0)
		m_lReturn = -1;
	else
		m_lReturn = (long)m_ctrlListaGruppi.GetItemData(nIndex);

	CDialog::OnOK();
}