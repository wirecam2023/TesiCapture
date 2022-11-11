#include "stdafx.h"
#include "Endox.h"
#include "EditCommentoImmagineDlg.h"

#include "CommentiImmaginiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditCommentoImmagineDlg, CEndoxResizableDlg)

CEditCommentoImmagineDlg::CEditCommentoImmagineDlg(CWnd* pParent, UINT idTitle, const CString &sValue, long lIDTipoEsame, CRect rectLocation)
	: CEndoxResizableDlg(CEditCommentoImmagineDlg::IDD, pParent)
{
	m_sTitle = theApp.GetMessageString(idTitle);
	m_sValue = sValue;
	m_lIDTipoEsame = lIDTipoEsame;
	m_rectLocation = rectLocation;
}

CEditCommentoImmagineDlg::~CEditCommentoImmagineDlg()
{
}

void CEditCommentoImmagineDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_LIST_COMMENTI, m_ctrlListCommenti);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_ctrlEditCommento);
}

BEGIN_MESSAGE_MAP(CEditCommentoImmagineDlg, CEndoxResizableDlg)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_EN_CHANGE(IDC_EDIT_VALUE, OnEnChangeEditValue)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMMENTI, OnNMDblclkListCommenti)

END_MESSAGE_MAP()

BOOL CEditCommentoImmagineDlg::OnInitDialog()
{   
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	//

	AddAnchor(IDC_LIST_COMMENTI, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_LINE, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_EDIT_VALUE, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));

	//

	SetWindowPos(NULL, m_rectLocation.left, m_rectLocation.top, m_rectLocation.Width(), m_rectLocation.Height(), SWP_NOZORDER);

	//

	m_ctrlListCommenti.SetExtendedStyle(m_ctrlListCommenti.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListCommenti.InsertColumn(0, "");
	m_ctrlListCommenti.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	RiempiListaCommenti(m_lIDTipoEsame);

	//

	theApp.LocalizeDialog(this, CEditCommentoImmagineDlg::IDD, "EditCommentoImmagineDlg");

	SetWindowText(m_sTitle);
	SetDlgItemText(IDC_EDIT_VALUE, m_sValue);

	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //
	//Simone 03/02/2016 // No, altrimenti non posso cancellare il commento
	//m_ctrlButtonOK.EnableWindow(!m_sValue.IsEmpty());

	if (theApp.m_bAlbumImmaginiCommentoNonEditabile)
		m_ctrlEditCommento.SetReadOnly();

	//
	return bReturn;
}

void CEditCommentoImmagineDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_VALUE, m_sValue);

	OnOK();
}

CString CEditCommentoImmagineDlg::GetValue()
{
	return m_sValue;
}

void CEditCommentoImmagineDlg::OnEnChangeEditValue()
{
	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //

	CString sTemp;
	GetDlgItemText(IDC_EDIT_VALUE, sTemp);
	sTemp.Trim();

	m_ctrlButtonOK.EnableWindow(!sTemp.IsEmpty());
}

void CEditCommentoImmagineDlg::OnNMDblclkListCommenti(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	POSITION pos = m_ctrlListCommenti.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListCommenti.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			SetDlgItemText(IDC_EDIT_VALUE, m_ctrlListCommenti.GetItemText(nCurSel, 0));
			m_ctrlListCommenti.SetItemState(nCurSel, 0, LVIS_SELECTED);
		}
	}

	*pResult = 0;
}

void CEditCommentoImmagineDlg::RiempiListaCommenti(long lIDTipoEsame)
{
	CString sFilter;
	sFilter.Format("IDTipoEsame=%li", lIDTipoEsame);

	m_ctrlListCommenti.SetRedraw(FALSE);
	m_ctrlListCommenti.DeleteAllItems();

	CCommentiImmaginiSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord("Commento");
	if (setTemp.OpenRecordset("CEditCommentoImmagineDlg::RiempiListaCommenti"))
	{
		int nIndex = 0;
		while (!setTemp.IsEOF())
		{
			m_ctrlListCommenti.InsertItem(nIndex, setTemp.m_sCommento);
			m_ctrlListCommenti.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CEditCommentoImmagineDlg::RiempiListaCommenti");
	}

	m_ctrlListCommenti.SetRedraw(TRUE);
}
