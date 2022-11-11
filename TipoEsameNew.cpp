#include "stdafx.h"
#include "Endox.h"
#include "TipoEsameNew.h"

#include "EsamiView.h"
#include "TipoEsameSet.h"
#include "VistaTipiEsamiNoUOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipoEsameNewDlg, CDialog)

CTipoEsameNewDlg::CTipoEsameNewDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bDisegnaReport, BOOL bCanCancel, long lForcedUO)
	: CDialog(CTipoEsameNewDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_lReturn = -1;
	m_lUO = -1;

	m_pEsamiView = pEsamiView;
	m_bDisegnaReport = bDisegnaReport;
	m_bCanCancel = bCanCancel;
	m_lForcedUO = lForcedUO;
}

CTipoEsameNewDlg::~CTipoEsameNewDlg()
{
}

BEGIN_MESSAGE_MAP(CTipoEsameNewDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ALTREUO, OnBnClickedAltreUO)
	ON_CBN_SELCHANGE(IDC_COMBO_1, OnCbnSelchangeCombo1)

	ON_MESSAGE(WM_SHOWDROPDOWN, OnShowDropDown)
END_MESSAGE_MAP()

void CTipoEsameNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic);
	DDX_Control(pDX, IDC_COMBO_1, m_ctrlCombo1);
	DDX_Control(pDX, IDC_BTN_ALTREUO, m_ctrlBtnAltreUO);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

BOOL CTipoEsameNewDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();
	int nIndex = 0;

	if (m_bDisegnaReport)
	{
		m_ctrlCombo1.InsertString(nIndex, theApp.GetMessageString(IDS_RICERCA));
		m_ctrlCombo1.SetItemData(nIndex, (DWORD)VAL_RICERCA);
		nIndex++;

		m_ctrlBtnAltreUO.ShowWindow(SW_SHOW);
	}

	CTipoEsameSet setTemp;

	if (m_lForcedUO > 0)
	{
		CString sBaseFilter;
		sBaseFilter.Format("UO=%li", m_lForcedUO);
		setTemp.SetBaseFilter(sBaseFilter);
	}

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CTipoEsameNewDlg::OnInitDialog"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlCombo1.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCombo1.SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CTipoEsameNewDlg::OnInitDialog");
	}

	theApp.LocalizeDialog(this, CTipoEsameNewDlg::IDD, "TipoEsameNew");

	if (m_bDisegnaReport)
	{
		SetWindowText(theApp.GetMessageString(IDS_TIPOESAMENEW_1));
		m_ctrlStatic.SetWindowText(theApp.GetMessageString(IDS_TIPOESAMENEW_2));
		m_ctrlStatic.SetFont(&theApp.m_fontBold);
	}
	if (!m_bCanCancel)
		m_ctrlBtnCancel.ShowWindow(SW_HIDE);

	if (nIndex == 1)
	{
		// c'è solo un tipo d'esame inserito e quindi non chiedo nemmeno di selezionarlo //

		m_ctrlCombo1.SetCurSel(0);
		OnOK();
	}
	else
	{
		if (m_pEsamiView->m_lIDTipoEsameAutoInsert > 0)
		{
			for(nIndex = 0; nIndex < m_ctrlCombo1.GetCount(); nIndex++)
			{
				if ((long)m_ctrlCombo1.GetItemData(nIndex) == m_pEsamiView->m_lIDTipoEsameAutoInsert)
				{
					m_ctrlCombo1.SetCurSel(nIndex);
					OnOK();
					break;
				}
			}
		}
		else
		{
			PostMessage(WM_SHOWDROPDOWN);			
		}
	}

	return bReturn;
}

long CTipoEsameNewDlg::GetTipoEsame()
{
	return m_lReturn;
}

long CTipoEsameNewDlg::GetUO()
{
	return m_lUO;
}

void CTipoEsameNewDlg::SetTipoEsame(long lReturn)
{
	m_lReturn = lReturn;
}

void CTipoEsameNewDlg::OnCancel()
{
	if (m_ctrlBtnCancel.IsWindowVisible())
		CDialog::OnCancel();
}

void CTipoEsameNewDlg::OnOK()
{
	int nIndex = m_ctrlCombo1.GetCurSel();

	if (nIndex >= 0)
	{
		m_lReturn = (long)m_ctrlCombo1.GetItemData(nIndex);

		if (m_bDisegnaReport)
		{
			CString strFilter;
			strFilter.Format("Contatore=%li", m_lReturn);

			CVistaTipiEsamiNoUOSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CTipoEsameNewDlg::OnOK"))
			{
				if (!setTemp.IsEOF())
					m_lUO = setTemp.m_lUO;

				setTemp.CloseRecordset("CTipoEsameNewDlg::OnOK");
			}
		}
	}

	CDialog::OnOK();
}

void CTipoEsameNewDlg::OnBnClickedAltreUO()
{
	m_ctrlCombo1.ResetContent();

	int nIndex = 0;

	if (m_bDisegnaReport)
	{
		m_ctrlCombo1.InsertString(nIndex, theApp.GetMessageString(IDS_RICERCA));
		m_ctrlCombo1.SetItemData(nIndex, (DWORD)VAL_RICERCA);
		nIndex++;
	}

	CVistaTipiEsamiNoUOSet setTemp;
	if (setTemp.OpenRecordset("CTipoEsameNewDlg::OnBnClickedAltreUO"))
	{
		while(!setTemp.IsEOF())
		{
			CString strTemp = "";

			setTemp.m_sDescrizioneUO.Trim();
			setTemp.m_sDescrizioneTipoEsame.Trim();

			strTemp = setTemp.m_sDescrizioneUO;

			if (!setTemp.m_sDescrizioneTipoEsame.IsEmpty())
			{
				if (!strTemp.IsEmpty())
					strTemp += " - ";

				strTemp += setTemp.m_sDescrizioneTipoEsame;
			}

			m_ctrlCombo1.InsertString(nIndex, strTemp);
			m_ctrlCombo1.SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CTipoEsameNewDlg::OnBnClickedAltreUO");
	}

	m_ctrlCombo1.ShowDropDown();
}

void CTipoEsameNewDlg::OnCbnSelchangeCombo1()
{
	m_ctrlBtnOK.EnableWindow(m_ctrlCombo1.GetCurSel() >= 0);
}

LRESULT CTipoEsameNewDlg::OnShowDropDown(WPARAM wparam, LPARAM lparam)
{
	m_ctrlCombo1.ShowDropDown();

	return 0;
}