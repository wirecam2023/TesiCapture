#include "stdafx.h"
#include "Endox.h"
#include "UOUtenteDlg.h"

#include "UOSet.h"
#include "UOUtenteSet.h"
#include "UtentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUOUtenteDlg, CDialog)

CUOUtenteDlg::CUOUtenteDlg(CWnd* pParent, long lIDUtente)
	: CDialog(CUOUtenteDlg::IDD, pParent)
{
	m_lIDUtente = lIDUtente;
	m_lUOAttuale = theApp.m_lUO;

	theApp.m_lUO = -1;
}

CUOUtenteDlg::~CUOUtenteDlg()
{
}

BEGIN_MESSAGE_MAP(CUOUtenteDlg, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBO_1, OnCbnSelchangeCombo1)

	ON_WM_TIMER()

END_MESSAGE_MAP()

void CUOUtenteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_1, m_ctrlCombo1);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOk);
}

BOOL CUOUtenteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Sandro 26/11/2014 //

	CString sUtenteTemp = CUtentiSet().GetUsername(m_lIDUtente);
	if ((sUtenteTemp.CompareNoCase("administrator") == 0) || (sUtenteTemp.CompareNoCase("sat") == 0))
		CUOUtenteSet().VerificaUODefault(m_lIDUtente);

	//

	CStringList listTemp;

	CString strFilter;
	strFilter.Format("IDUtente=%li", m_lIDUtente);

	CUOUtenteSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	setTemp.SetSortRecord("IDUO");
	if (setTemp.OpenRecordset("CUOUtenteDlg::OnInitDialog"))
	{
		while(!setTemp.IsEOF())
		{
			// Sandro 13/10/2015 // non visualizzo la UO in cui sono attualmente //
			if (setTemp.m_lIDUO != m_lUOAttuale)
			{
				CString strDescrizione = CUOSet().GetDescrizione(setTemp.m_lIDUO);
				if (!strDescrizione.IsEmpty())
				{
					if (listTemp.Find(strDescrizione) == NULL)
					{
						listTemp.AddTail(strDescrizione);

						int nIndex = m_ctrlCombo1.AddString(strDescrizione);
						m_ctrlCombo1.SetItemData(nIndex, (DWORD)setTemp.m_lIDUO);
					}
				}
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CUOUtenteDlg::OnInitDialog");
	}

	theApp.LocalizeDialog(this, CUOUtenteDlg::IDD, "UOUtenteDlg");

	if (m_ctrlCombo1.GetCount() <= 0)
	{
		OnCancel();
	}
	else if (m_ctrlCombo1.GetCount() == 1)
	{
		// c'è solo una UO e quindi non chiedo nemmeno di selezionarla //

		m_ctrlCombo1.SetCurSel(0);
		OnOK();
	}
	else
	{
		SetTimer(0xaaa, 100, NULL);
	}

	return TRUE;
}

void CUOUtenteDlg::OnOK()
{
	int nIndex = m_ctrlCombo1.GetCurSel();

	if (nIndex >= 0)
		theApp.m_lUO = (long)m_ctrlCombo1.GetItemData(nIndex);

	CDialog::OnOK();
}

void CUOUtenteDlg::OnCbnSelchangeCombo1()
{
	m_ctrlBtnOk.EnableWindow(m_ctrlCombo1.GetCurSel() >= 0);
}

void CUOUtenteDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0xaaa)
	{
		KillTimer(nIDEvent);
		// Marvel Carvalho - Bug 4445 Omissão da Seta do Mouse na Seleção Inicial de UO
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		GotoDlgCtrl(GetDlgItem(IDC_COMBO_1));
		m_ctrlCombo1.SetFocus();
		m_ctrlCombo1.ShowDropDown();
	}
}
