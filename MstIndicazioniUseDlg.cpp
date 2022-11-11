#include "stdafx.h"
#include "Endox.h"
#include "MstIndicazioniUseDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "MstIndicazioniSet.h"
#include "RicercaIndicazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstIndicazioniUseDlg, CDialog)

CMstIndicazioniUseDlg::CMstIndicazioniUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstIndicazioniUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;
}

CMstIndicazioniUseDlg::~CMstIndicazioniUseDlg()
{
}

BEGIN_MESSAGE_MAP(CMstIndicazioniUseDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDOK,    OnBnClickedOk)

	ON_LBN_SELCHANGE(IDC_LIST_LEVEL0, OnLbnSelchangeListLevel0)
END_MESSAGE_MAP()

void CMstIndicazioniUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_LEVEL0, m_ctrlListLevel0);
	DDX_Control(pDX, IDC_LIST_LEVEL1, m_ctrlListLevel1);
	DDX_Control(pDX, IDC_ADD,  m_ctrlButtonAdd);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,     m_ctrlButtonOK);
}

BOOL CMstIndicazioniUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);

	SetDlgItemText(IDC_RICERCA, m_strValue);

	RiempiLevel0(m_pEsamiView->m_pEsamiSet->m_lIDEsame);

	BOOL bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;
	if (!bRicercaAttivata)
	{
		GetDlgItem(IDC_BTN_OR)->ShowWindow(SW_HIDE);

		CRect rectBtn, rectBtnAdd;
		CPoint pointBr, pointUl;

		GetDlgItem(IDC_ADD)->GetWindowRect(&rectBtnAdd);
		GetDlgItem(IDC_BTN_OR)->GetWindowRect(&rectBtn);

		pointUl = rectBtnAdd.TopLeft();
		pointBr = rectBtn.BottomRight();
		
		GetDlgItem(IDC_ADD)->SetWindowPos(&wndTop, 0, 0, pointBr.x - pointUl.x, rectBtn.Height(), SWP_NOMOVE);
	}

	theApp.LocalizeDialog(this, CMstIndicazioniUseDlg::IDD, "MstIndicazioniUseDlg");

	return bReturn;
}

void CMstIndicazioniUseDlg::RiempiLevel0(long lTipoEsame)
{
	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
	{
		// modalità normale //

		CMstIndicazioniSet setTemp;
		CString strTemp;

		strTemp.Format("TipoEsame=%li AND Padre=0", lTipoEsame);

		setTemp.SetSortRecord("Descrizione");
		setTemp.SetOpenFilter(strTemp);

		m_ctrlListLevel0.ResetContent();

		if (setTemp.OpenRecordset("CMstIndicazioniUseDlg::RiempiLevel0"))
		{
			int iTemp = 0;

			while(!setTemp.IsEOF())
			{
				m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
				m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

				iTemp++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstIndicazioniUseDlg::RiempiLevel0");
		}

		if (m_ctrlListLevel0.GetCount() == 0)
		{
			GetDlgItem(IDC_LIST_LEVEL0)->EnableWindow(FALSE);
			GetDlgItem(IDC_LIST_LEVEL1)->EnableWindow(FALSE);
		}
	}
	else
	{
		// modalità ricerca //

		CRicercaIndicazioniSet setTemp;

		m_ctrlListLevel0.ResetContent();

		if (setTemp.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListLevel0"))
		{
			//CString strPrev = "";

			while(!setTemp.IsEOF())
			{
				//Simone 16/06/2013 - in questo modo alcuni termini di primo livello si ripetevano se avevano più termini di secondo livello. Nel nuovo modo funziona.

				/*if (strPrev != setTemp.m_sDescr1)
				{
					strPrev = setTemp.m_sDescr1;

					m_ctrlListLevel0.AddString(setTemp.m_sDescr1);
				}*/

				if (m_ctrlListLevel0.FindString(-1, setTemp.m_sDescr1) == LB_ERR)
				{
					m_ctrlListLevel0.AddString(setTemp.m_sDescr1);
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListLevel0");
		}
	}
}

void CMstIndicazioniUseDlg::RiempiLevel1(long lPadre)
{
	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
	{
		// modalità normale //

		CMstIndicazioniSet setTemp;
		CString strTemp;

		m_ctrlListLevel1.ResetContent();

		strTemp.Format("Padre=%li", lPadre);

		setTemp.SetSortRecord("Descrizione");
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstIndicazioniUseDlg::RiempiLevel1"))
		{
			while(!setTemp.IsEOF())
			{
				m_ctrlListLevel1.AddString(setTemp.m_sDescrizione);

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstIndicazioniUseDlg::RiempiLevel1");
		}
	}
	else
	{
		// modalità ricerca //

		int nCurSel = m_ctrlListLevel0.GetCurSel();

		m_ctrlListLevel1.ResetContent();

		if (nCurSel >= 0)
		{
			CRicercaIndicazioniSet setTemp;

			CString strTemp;
			m_ctrlListLevel0.GetText(nCurSel, strTemp);
			strTemp.Replace("'", "''");

			setTemp.SetOpenFilter("DESCR1='" + strTemp + "'");
			if (setTemp.OpenRecordset("CMstIndicazioniUseDlg::RiempiListSubLevels"))
			{
				while(!setTemp.IsEOF())
				{
					m_ctrlListLevel1.AddString(setTemp.m_sDescr2);

					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CMstIndicazioniUseDlg::RiempiListSubLevels");
			}
		}
	}
}

CString CMstIndicazioniUseDlg::GetValue()
{
	return m_strValue;
}

void CMstIndicazioniUseDlg::SetValue(CString sValue)
{
	m_strValue = sValue;
}

void CMstIndicazioniUseDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_RICERCA, m_strValue);

	OnOK();
}

void CMstIndicazioniUseDlg::OnLbnSelchangeListLevel0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		RiempiLevel1((long)m_ctrlListLevel0.GetItemData(iTemp));
	else
		RiempiLevel1(-1);
}

void CMstIndicazioniUseDlg::OnBnClickedAdd()
{
	int iTemp;

	CString strCurValue;
	GetDlgItemText(IDC_RICERCA, strCurValue);

	CString strAddValue;
	CString strAddValueLevel0;
	CString strAddValueLevel1;

	iTemp = m_ctrlListLevel0.GetCurSel();
	if (iTemp >= 0)
	{
		m_ctrlListLevel0.GetText(iTemp, strAddValueLevel0);

		iTemp = m_ctrlListLevel1.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel1.GetText(iTemp, strAddValueLevel1);

			strAddValue = strAddValueLevel0 + " " + strAddValueLevel1;
		}
		else
		{
			strAddValue = strAddValueLevel0;
		}

		if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
		{
			// modalità normale //

			if (strCurValue.Find(strAddValue, 0) < 0)
			{
				if (strCurValue.GetLength() > 0)
					strCurValue = strCurValue + "\r\n";

				SetDlgItemText(IDC_RICERCA, strCurValue + strAddValue);

				m_ctrlListLevel0.SetCurSel(-1);
				RiempiLevel1(-1);
			}
		}
		else
		{
			// modalità ricerca //

			SetDlgItemText(IDC_RICERCA, strAddValue);

			m_ctrlListLevel0.SetCurSel(-1);
			RiempiLevel1(-1);
		}
	}
}
