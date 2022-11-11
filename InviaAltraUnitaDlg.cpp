#include "stdafx.h"
#include "Endox.h"
#include "InviaAltraUnitaDlg.h"
#include "CustomDate.h"
#include "EsamiView.h"
#include "UnitaTCPSet.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CInviaAltraUnitaDlg dialog

IMPLEMENT_DYNAMIC(CInviaAltraUnitaDlg, CDialog)

CInviaAltraUnitaDlg::CInviaAltraUnitaDlg(CEsamiView* pEsamiView)
: CDialog(CInviaAltraUnitaDlg::IDD, (CWnd*)pEsamiView)
{
	m_pEsamiView = pEsamiView;

	m_lID = 0;

	m_lSavedPosition = -1;

	m_bCleanContent = FALSE;

	m_lSelectedUnita = 0;
}

CInviaAltraUnitaDlg::~CInviaAltraUnitaDlg()
{
}

void CInviaAltraUnitaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_UNITA_CLEAR, m_ctrlButtonClean);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonEsc);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	DDX_Text(pDX, IDC_EDIT_SEARCHUNITA, m_sUnitaSearch);
}


BEGIN_MESSAGE_MAP(CInviaAltraUnitaDlg, CDialog)
	ON_BN_CLICKED(IDC_UNITA_CLEAR, OnUnitaClean)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOK)
	ON_BN_CLICKED(IDC_CLEAN_SEARCHUNITA, OnBnClickedCleanSearchUnita)

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)

	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()

	ON_EN_CHANGE(IDC_EDIT_SEARCHUNITA, OnEnChangeEditSearchUnita)
END_MESSAGE_MAP()

BOOL CInviaAltraUnitaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);

	RiempiListaUnita("");
	//	GetDlgItem(IDC_EDIT_SEARCHUNITA)->SetWindowText(m_strRicercaView);

	m_nItemPressed = 0;
	m_nItemCount = m_ctrlLista.GetCount();

	theApp.LocalizeDialog(this, CInviaAltraUnitaDlg::IDD, "InviaAltraUnitaDlg");

	return TRUE;
}

void CInviaAltraUnitaDlg::OnOK()
{
	UpdateData(FALSE);

	CDialog::OnOK();
}

void CInviaAltraUnitaDlg::OnUnitaClean()
{
	m_bCleanContent = TRUE;

	CDialog::OnOK();
}

void CInviaAltraUnitaDlg::OnDestroy()
{
	CDialog::OnDestroy();

}

void CInviaAltraUnitaDlg::OnLbnDblclkLista()
{
	if (m_bMenu == FALSE)
		OnOK();
}

void CInviaAltraUnitaDlg::OnMediciRefresh()
{
	m_ctrlLista.EnableWindow(TRUE);

	if (m_lSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_lSavedPosition;
		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;

		m_lSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}

	RedrawWindow();
}


void CInviaAltraUnitaDlg::RiempiListaUnita(CString sFilter)
{
	m_ctrlLista.SetTabStops(100);

	CUnitaTCPSet setUnita;

	setUnita.SetBaseFilter("ELIMINATO=0");

	if (!sFilter.IsEmpty())
	{
		CString sFilt = "(DESCRIZIONE LIKE '%" + sFilter + "%')";
		setUnita.SetOpenFilter(sFilt);
	}

	setUnita.SetSortRecord("DESCRIZIONE");
	setUnita.SetSortRecord("DESCRIZIONE");

	m_ctrlLista.ResetContent();
	if (setUnita.OpenRecordset("CInviaAltraUnitaDlg::RiempiListaUnita"))
	{
		while (!setUnita.IsEOF())
		{
			int posiz = m_ctrlLista.AddString(setUnita.m_sDescrizione);

			if (posiz >= 0)
				m_ctrlLista.SetItemData(posiz, (DWORD)setUnita.m_lID);

			setUnita.MoveNext();
		}

		setUnita.CloseRecordset("CInviaAltraUnitaDlg::RiempiListaUnita");
	}

	OnSelchangeLista();
}

void CInviaAltraUnitaDlg::OnSelchangeLista()
{
	if (m_bCleanContent)
	{
		m_lID = 0;
		m_strRicerca = "0";
		m_nItemPressed = 1;
		m_lSavedPosition = -1;
		return;
	}
	if (!m_bCleanContent) {
		if (m_ctrlLista.GetCount() > 0)
		{
			if (m_ctrlLista.GetCount() == 1)
			{
				m_ctrlLista.SetCurSel(0);
			}

			if (m_ctrlLista.GetCurSel() >= 0)
			{
				SetUnitaSelected();
			}
		}
	}
}

void CInviaAltraUnitaDlg::SetUnitaSelected()
{
	long lIDUnita = 0;

	if (m_ctrlLista.GetCount() > 0)
	{
		int nCurSel = m_ctrlLista.GetCurSel();
		if (nCurSel >= 0)
		{
			lIDUnita = (long)m_ctrlLista.GetItemData(nCurSel);
			if (lIDUnita > 0)
			{
				CString sFilter;
				sFilter.Format("ID=%li", lIDUnita);

				CUnitaTCPSet setUnita;
				setUnita.SetOpenFilter(sFilter);
				if (setUnita.OpenRecordset("CInviaAltraUnitaDlg::SetUnitaSelected"))
				{
					if (!setUnita.IsEOF())
					{
						m_lID = setUnita.m_lID;
						m_sDescrizione = setUnita.m_sDescrizione;

						m_lSelectedUnita = setUnita.m_lUnita;
					}

					setUnita.CloseRecordset("CInviaAltraUnitaDlg::SetUnitaSelected");
				}

				UpdateData(FALSE);
			}
		}
	}
}

void CInviaAltraUnitaDlg::OnEnChangeEditSearchUnita()
{
	GetDlgItem(IDC_EDIT_SEARCHUNITA)->GetWindowText(m_sUnitaSearch);

	RiempiListaUnita(m_sUnitaSearch);

}

void CInviaAltraUnitaDlg::OnBnClickedOK()
{
	CDialog::OnOK();
}

void CInviaAltraUnitaDlg::OnBnClickedCancel()
{
	CDialog::OnOK();
}

void CInviaAltraUnitaDlg::OnBnClickedCleanSearchUnita()
{
	CEdit * pAuxEdit;
	pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_SEARCHUNITA);
	if (pAuxEdit != NULL){
		GetDlgItem(IDC_EDIT_SEARCHUNITA)->SetWindowText(" ");
		pAuxEdit->UpdateWindow();// force it update
		pAuxEdit->SetFocus();    // Set  focus to the component
	}

	GetDlgItem(IDC_EDIT_SEARCHUNITA)->SetWindowText("");
}

long CInviaAltraUnitaDlg::GetSelectedUnita()
{
	/*
	long m_lIDSelected = -1;
	//int iCurSel = m_ctrlLista.GetNextSelectedItem(pos);
	int nCount = m_ctrlLista.GetCount();

	if (nCount > 0)
	{
	int nCurPos = m_ctrlLista.GetCurSel();

	if (nCurPos >= 0)
	{
	DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);
	if (dwCode >= 0)
	{
	m_lIDSelected = (long)dwCode;
	m_lSelectedUnita = CUnitaTCPSet().GetUnita(m_lIDSelected);
	}
	}
	}
	*/
	return m_lSelectedUnita;
}
