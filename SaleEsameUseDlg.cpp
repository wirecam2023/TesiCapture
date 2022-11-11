#include "stdafx.h"
#include "Endox.h"
#include "SaleEsameUseDlg.h"

#include "EsamiView.h"
#include "SaleEsameSet.h"
#include ".\saleesameusedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSaleEsameUseDlg, CDialog)

CSaleEsameUseDlg::CSaleEsameUseDlg(CWnd* pParent, CEsamiView* pEsamiView, long idSedeSel)
	: CDialog(CSaleEsameUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lIdSedeSel = idSedeSel;

	m_strSala = "";
}

BEGIN_MESSAGE_MAP(CSaleEsameUseDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_LBN_DBLCLK(IDC_LIST_SALE, OnLbnDblclkListSale)
END_MESSAGE_MAP()

void CSaleEsameUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SALE, m_ctrlListSale);
}

BOOL CSaleEsameUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	RiempiListSale();

	return bReturn;
}

void CSaleEsameUseDlg::OnBnClickedOk()
{
	int nItem = m_ctrlListSale.GetCurSel();

	if (nItem >= 0)
		m_ctrlListSale.GetText(nItem, m_strSala);
	else
		m_strSala = "";

	OnOK();
}

void CSaleEsameUseDlg::RiempiListSale()
{
	CSaleEsameSet setSale;

	int nIndex;
	int nFind = -1;

	m_ctrlListSale.ResetContent();

	CString filter;
	filter.Format("idSede=%li", m_lIdSedeSel);
	setSale.SetOpenFilter(filter);

	setSale.SetSortRecord("Descrizione");
	if (setSale.OpenRecordset("CSaleEsameUseDlg::RiempiListSedi"))
	{
		while(!setSale.IsEOF())
		{
			nIndex = m_ctrlListSale.AddString(setSale.m_sDescrizione);
			m_ctrlListSale.SetItemData(nIndex, (DWORD)setSale.m_lID);

			if ((!m_strSala.IsEmpty()) && (m_strSala == setSale.m_sDescrizione))
				nFind = nIndex;

			setSale.MoveNext();
		}

		setSale.CloseRecordset("CSaleEsameUseDlg::RiempiListSedi");
	}

	m_ctrlListSale.SetCurSel(nFind);
}

CString CSaleEsameUseDlg::GetSala()
{
	return m_strSala;
}

void CSaleEsameUseDlg::SetSala(CString strSala)
{
	m_strSala = strSala;
}

void CSaleEsameUseDlg::OnLbnDblclkListSale()
{
	int nItem = m_ctrlListSale.GetCurSel();

	if (nItem >= 0)
		OnBnClickedOk();
}
