#include "stdafx.h"
#include "Endox.h"
#include "SediEsameUseDlg.h"
#include "SediEsameSet.h"
#include "EsamiView.h"
#include ".\sediesameusedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSediEsameUseDlg, CDialog)

CSediEsameUseDlg::CSediEsameUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CSediEsameUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_lIDSede = 0;
}

BEGIN_MESSAGE_MAP(CSediEsameUseDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_LBN_DBLCLK(IDC_LIST_SEDI, OnLbnDblclkListSedi)
END_MESSAGE_MAP()

void CSediEsameUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SEDI, m_ctrlListSedi);
}

BOOL CSediEsameUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	RiempiListSedi();

	return bReturn;
}

void CSediEsameUseDlg::OnBnClickedOk()
{
	int nItem = m_ctrlListSedi.GetCurSel();

	if (nItem >= 0)
		m_lIDSede = (long)m_ctrlListSedi.GetItemData(nItem);
	else
		m_lIDSede = 0;

	OnOK();
}

void CSediEsameUseDlg::RiempiListSedi()
{
	CSediEsameSet setSediEsame;

	int nIndex;
	int nFind = -1;

	m_ctrlListSedi.ResetContent();

	setSediEsame.SetSortRecord("Descrizione");
	if (setSediEsame.OpenRecordset("CSediEsameUseDlg::RiempiListComuni"))
	{
		while(!setSediEsame.IsEOF())
		{
			nIndex = m_ctrlListSedi.AddString(setSediEsame.m_sDescrizione);
			m_ctrlListSedi.SetItemData(nIndex, (DWORD)setSediEsame.m_lID);

			if ((m_lIDSede > 0) && (m_lIDSede == setSediEsame.m_lID))
				nFind = nIndex;

			setSediEsame.MoveNext();
		}

		setSediEsame.CloseRecordset("CSediEsameUseDlg::RiempiListComuni");
	}

	m_ctrlListSedi.SetCurSel(nFind);
}

long CSediEsameUseDlg::GetSede()
{
	return m_lIDSede;
}

void CSediEsameUseDlg::SetSede(long lIDSede)
{
	m_lIDSede = lIDSede;
}

void CSediEsameUseDlg::OnLbnDblclkListSedi()
{
	int nItem = m_ctrlListSedi.GetCurSel();

	if (nItem >= 0)
		OnBnClickedOk();
}
