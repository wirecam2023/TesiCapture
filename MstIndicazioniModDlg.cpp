#include "stdafx.h"
#include "Endox.h"
#include "MstIndicazioniModDlg.h"
#include "EsamiView.h"

#include "MstIndicazioniSet.h"
#include "EditStringDlg.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstIndicazioniModDlg, CDialog)

CMstIndicazioniModDlg::CMstIndicazioniModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstIndicazioniModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CMstIndicazioniModDlg::~CMstIndicazioniModDlg()
{
}

BEGIN_MESSAGE_MAP(CMstIndicazioniModDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_CBN_SELCHANGE(IDC_COMBO_ESAME, OnCbnSelchangeComboEsame)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL0, OnLbnSelchangeListLevel0)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL1, OnLbnSelchangeListLevel1)

	ON_BN_CLICKED(IDC_BTN_NEW0, OnBnClickedBtnNew0)
	ON_BN_CLICKED(IDC_BTN_EDT0, OnBnClickedBtnEdt0)
	ON_BN_CLICKED(IDC_BTN_DEL0, OnBnClickedBtnDel0)
	ON_BN_CLICKED(IDC_BTN_NEW1, OnBnClickedBtnNew1)
	ON_BN_CLICKED(IDC_BTN_EDT1, OnBnClickedBtnEdt1)
	ON_BN_CLICKED(IDC_BTN_DEL1, OnBnClickedBtnDel1)
END_MESSAGE_MAP()

void CMstIndicazioniModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_ESAME, m_ctrlComboEsame);
	DDX_Control(pDX, IDC_LIST_LEVEL0, m_ctrlListLevel0);
	DDX_Control(pDX, IDC_LIST_LEVEL1, m_ctrlListLevel1);

	DDX_Control(pDX, IDC_BTN_NEW0, m_ctrlButtonNew1);
	DDX_Control(pDX, IDC_BTN_EDT0, m_ctrlButtonEdit1);
	DDX_Control(pDX, IDC_BTN_DEL0, m_ctrlButtonDelete1);
	DDX_Control(pDX, IDC_BTN_NEW1, m_ctrlButtonNew2);
	DDX_Control(pDX, IDC_BTN_EDT1, m_ctrlButtonEdit2);
	DDX_Control(pDX, IDC_BTN_DEL1, m_ctrlButtonDelete2);
	DDX_Control(pDX, IDCANCEL,     m_ctrlButtonCancel);
}

HBRUSH CMstIndicazioniModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LIST_LEVEL0:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_LIST_LEVEL1:
			pDC->SetTextColor(theApp.m_color[1]);
			break;
	}

	return hBrush;
}

BOOL CMstIndicazioniModDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_COMBO_ESAME)->SetFont(&theApp.m_fontBold);

	RiempiComboEsame();

	theApp.LocalizeDialog(this, CMstIndicazioniModDlg::IDD, "MstIndicazioniModDlg");
	return TRUE;
}

void CMstIndicazioniModDlg::RiempiComboEsame()
{
	CTipoEsameSet setTemp;
	int iTemp = 0;

	setTemp.SetSortRecord("Descrizione");
	//setTemp.SetOpenFilter("Visibile=1");
	if (setTemp.OpenRecordset("CMstIndicazioniModDlg::RiempiComboEsame") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlComboEsame.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlComboEsame.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstIndicazioniModDlg::RiempiComboEsame");
	}
}

void CMstIndicazioniModDlg::RiempiLevel0(long lContatore)
{
	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEW1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_EDT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL1)->EnableWindow(FALSE);

	m_ctrlListLevel0.ResetContent();
	m_ctrlListLevel1.ResetContent();

	if (lContatore >= 0)
	{
		CString strTemp;
		CMstIndicazioniSet setTemp;

		setTemp.SetSortRecord("Descrizione");
		setTemp.SetBaseFilter("Padre=0");

		strTemp.Format("TipoEsame=%li", lContatore);
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstIndicazioniModDlg::RiempiLevel0") == TRUE)
		{
			int iTemp = 0;
			while(setTemp.IsEOF() == FALSE)
			{
				m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
				m_ctrlListLevel0.SetItemData(iTemp, setTemp.m_lContatore);

				iTemp++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstIndicazioniModDlg::RiempiLevel0");
		}
	}
}

void CMstIndicazioniModDlg::RiempiLevel1(long lContatore)
{
	GetDlgItem(IDC_BTN_EDT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL1)->EnableWindow(FALSE);

	m_ctrlListLevel1.ResetContent();

	if (lContatore >= 0)
	{
		CString strTemp;
		CMstIndicazioniSet setTemp;

		setTemp.SetSortRecord("Descrizione");

		strTemp.Format("Padre=%li", lContatore);
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstIndicazioniModDlg::RiempiLevel1") == TRUE)
		{
			int iTemp = 0;
			while(setTemp.IsEOF() == FALSE)
			{
				m_ctrlListLevel1.InsertString(iTemp, setTemp.m_sDescrizione);
				m_ctrlListLevel1.SetItemData(iTemp, setTemp.m_lContatore);

				iTemp++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstIndicazioniModDlg::RiempiLevel1");
		}
	}
}

void CMstIndicazioniModDlg::OnCbnSelchangeComboEsame()
{
	int iTemp = m_ctrlComboEsame.GetCurSel();

	GetDlgItem(IDC_BTN_NEW0)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEW1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_EDT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL1)->EnableWindow(FALSE);

	if (iTemp >= 0)
	{
		long lTemp = (long)m_ctrlComboEsame.GetItemData(iTemp);

		RiempiLevel0(lTemp);
	}
	else
	{
		RiempiLevel0(-1);
	}
}

void CMstIndicazioniModDlg::OnLbnSelchangeListLevel0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	GetDlgItem(IDC_BTN_NEW0)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_NEW1)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_EDT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL1)->EnableWindow(FALSE);

	if (iTemp >= 0)
	{
		long lTemp = (long)m_ctrlListLevel0.GetItemData(iTemp);

		RiempiLevel1(lTemp);
	}
	else
	{
		RiempiLevel1(-1);
	}
}

void CMstIndicazioniModDlg::OnLbnSelchangeListLevel1()
{
	int iTemp = m_ctrlListLevel1.GetCurSel();

	GetDlgItem(IDC_BTN_NEW0)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_NEW1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_EDT1)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL1)->EnableWindow(iTemp >= 0);
}

void CMstIndicazioniModDlg::OnBnClickedBtnNew0()
{
	long lTemp = m_ctrlComboEsame.GetCurSel();

	if (lTemp >= 0)
	{
		CEditStringDlg dlg(this, IDS_MSTINDIC_TITLE_1, "");

		if (dlg.DoModal() == IDOK)
		{
			CMstIndicazioniSet setTemp;

			if (setTemp.OpenRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew0") == TRUE)
			{
				if (setTemp.AddNewRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew0") == TRUE)
				{
					setTemp.m_lTipoEsame = (long)m_ctrlComboEsame.GetItemData(lTemp);
					setTemp.m_lPadre = 0;
					setTemp.m_sDescrizione = dlg.GetValue();

					setTemp.UpdateRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew0");
				}

				setTemp.CloseRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew0");
			}

			RiempiLevel0((long)m_ctrlComboEsame.GetItemData(lTemp));
		}
	}
}

void CMstIndicazioniModDlg::OnBnClickedBtnEdt0()
{
	long lTemp = m_ctrlListLevel0.GetCurSel();

	if (lTemp >= 0)
	{
		CString strTemp;
		m_ctrlListLevel0.GetText(lTemp, strTemp);

		CEditStringDlg dlg(this, IDS_MSTINDIC_TITLE_2, strTemp);

		if (dlg.DoModal() == IDOK)
		{
			CMstIndicazioniSet setTemp;

			strTemp.Format("Contatore=%li", (long)m_ctrlListLevel0.GetItemData(lTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt0") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					if (setTemp.EditRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt0") == TRUE)
					{
						setTemp.m_sDescrizione = dlg.GetValue();

						setTemp.UpdateRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt0");
					}
				}

				setTemp.CloseRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt0");
			}

			RiempiLevel0((long)m_ctrlComboEsame.GetItemData(m_ctrlComboEsame.GetCurSel()));
		}
	}
}

void CMstIndicazioniModDlg::OnBnClickedBtnDel0()
{
	long lTemp = m_ctrlListLevel0.GetCurSel();

	if (lTemp >= 0)
	{
		CString strTemp;
		m_ctrlListLevel0.GetText(lTemp, strTemp);

		CString strTmp;
		strTmp.Format(theApp.GetMessageString(IDS_MSTINDICAZIONI_CONFIRM_DEL),
			          strTemp);
		if (theApp.AfxMessageBoxEndo(strTmp, MB_YESNO) == IDNO)
			return;

		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MSTINDICAZIONI_CONFIRM_DEL_2), MB_YESNO | MB_ICONSTOP) == IDYES)
			return;

		CMstIndicazioniSet setTemp;

		strTemp.Format("Contatore=%li", (long)m_ctrlListLevel0.GetItemData(lTemp));
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstIndicazioniModDlg::OnBnClickedBtnDel0") == TRUE)
		{
			if (setTemp.IsEOF() == FALSE)
				setTemp.DeleteRecordset("CMstIndicazioniModDlg::OnBnClickedBtnDel0");

			setTemp.CloseRecordset("CMstIndicazioniModDlg::OnBnClickedBtnDel0");
		}

		RiempiLevel0((long)m_ctrlComboEsame.GetItemData(m_ctrlComboEsame.GetCurSel()));
	}
}

void CMstIndicazioniModDlg::OnBnClickedBtnNew1()
{
	long lEsame = m_ctrlComboEsame.GetCurSel();
	long lPadre = m_ctrlListLevel0.GetCurSel();

	if ((lEsame >= 0) && (lPadre >= 0))
	{
		CEditStringDlg dlg(this, IDS_MSTINDIC_TITLE_1, "");

		if (dlg.DoModal() == IDOK)
		{
			CMstIndicazioniSet setTemp;

			if (setTemp.OpenRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew1") == TRUE)
			{
				if (setTemp.AddNewRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew1") == TRUE)
				{
					setTemp.m_lTipoEsame = (long)m_ctrlComboEsame.GetItemData(lEsame);
					setTemp.m_lPadre = (long)m_ctrlListLevel0.GetItemData(lPadre);
					setTemp.m_sDescrizione = dlg.GetValue();

					setTemp.UpdateRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew1");
				}

				setTemp.CloseRecordset("CMstIndicazioniModDlg::OnBnClickedBtnNew1");
			}

			RiempiLevel1((long)m_ctrlListLevel0.GetItemData(lPadre));
		}
	}
}

void CMstIndicazioniModDlg::OnBnClickedBtnEdt1()
{
	long lTemp = m_ctrlListLevel1.GetCurSel();

	if (lTemp >= 0)
	{
		CString strTemp;
		m_ctrlListLevel1.GetText(lTemp, strTemp);

		CEditStringDlg dlg(this, IDS_MSTINDIC_TITLE_2, strTemp);

		if (dlg.DoModal() == IDOK)
		{
			CMstIndicazioniSet setTemp;

			strTemp.Format("Contatore=%li", (long)m_ctrlListLevel1.GetItemData(lTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt1") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					if (setTemp.EditRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt1") == TRUE)
					{
						setTemp.m_sDescrizione = dlg.GetValue();

						setTemp.UpdateRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt1");
					}
				}

				setTemp.CloseRecordset("CMstIndicazioniModDlg::OnBnClickedBtnEdt1");
			}

			RiempiLevel1((long)m_ctrlListLevel0.GetItemData(m_ctrlListLevel0.GetCurSel()));
		}
	}
}

void CMstIndicazioniModDlg::OnBnClickedBtnDel1()
{
	long lTemp = m_ctrlListLevel1.GetCurSel();

	if (lTemp >= 0)
	{
		CString strTemp;
		m_ctrlListLevel1.GetText(lTemp, strTemp);

		CString strTmp;
		strTmp.Format(theApp.GetMessageString(IDS_MSTINDICAZIONI_CONFIRM_DEL),
			          strTemp);
		if (theApp.AfxMessageBoxEndo(strTmp, MB_YESNO) == IDNO)
			return;

		CMstIndicazioniSet setTemp;

		strTemp.Format("Contatore=%li", (long)m_ctrlListLevel1.GetItemData(lTemp));
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstIndicazioniModDlg::OnBnClickedBtnDel1") == TRUE)
		{
			if (setTemp.IsEOF() == FALSE)
				setTemp.DeleteRecordset("CMstIndicazioniModDlg::OnBnClickedBtnDel1");

			setTemp.CloseRecordset("CMstIndicazioniModDlg::OnBnClickedBtnDel1");
		}

		RiempiLevel1((long)m_ctrlListLevel0.GetItemData(m_ctrlListLevel0.GetCurSel()));
	}
}
