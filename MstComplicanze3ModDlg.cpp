#include "stdafx.h"
#include "Endox.h"
#include "MstComplicanze3ModDlg.h"

#include "EditStringDlg.h"
#include "EsamiView.h"
#include "MstComplicanze3Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstComplicanze3ModDlg, CDialog)

CMstComplicanze3ModDlg::CMstComplicanze3ModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstComplicanze3ModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CMstComplicanze3ModDlg::~CMstComplicanze3ModDlg()
{
}

BEGIN_MESSAGE_MAP(CMstComplicanze3ModDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LIST_LEVEL0, OnLbnSelchangeListLevel0)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL1, OnLbnSelchangeListLevel1)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL2, OnLbnSelchangeListLevel2)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL3, OnLbnSelchangeListLevel3)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL4, OnLbnSelchangeListLevel4)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL5, OnLbnSelchangeListLevel5)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL6, OnLbnSelchangeListLevel6)

	ON_BN_CLICKED(IDC_BTN_NEW0, OnBnClickedBtnNew0)
	ON_BN_CLICKED(IDC_BTN_EDT0, OnBnClickedBtnEdt0)
	ON_BN_CLICKED(IDC_BTN_DEL0, OnBnClickedBtnDel0)
	ON_BN_CLICKED(IDC_BTN_NEW1, OnBnClickedBtnNew1)
	ON_BN_CLICKED(IDC_BTN_EDT1, OnBnClickedBtnEdt1)
	ON_BN_CLICKED(IDC_BTN_DEL1, OnBnClickedBtnDel1)
	ON_BN_CLICKED(IDC_BTN_NEW2, OnBnClickedBtnNew2)
	ON_BN_CLICKED(IDC_BTN_EDT2, OnBnClickedBtnEdt2)
	ON_BN_CLICKED(IDC_BTN_DEL2, OnBnClickedBtnDel2)
	ON_BN_CLICKED(IDC_BTN_NEW3, OnBnClickedBtnNew3)
	ON_BN_CLICKED(IDC_BTN_EDT3, OnBnClickedBtnEdt3)
	ON_BN_CLICKED(IDC_BTN_DEL3, OnBnClickedBtnDel3)
	ON_BN_CLICKED(IDC_BTN_NEW4, OnBnClickedBtnNew4)
	ON_BN_CLICKED(IDC_BTN_EDT4, OnBnClickedBtnEdt4)
	ON_BN_CLICKED(IDC_BTN_DEL4, OnBnClickedBtnDel4)
	ON_BN_CLICKED(IDC_BTN_NEW5, OnBnClickedBtnNew5)
	ON_BN_CLICKED(IDC_BTN_EDT5, OnBnClickedBtnEdt5)
	ON_BN_CLICKED(IDC_BTN_DEL5, OnBnClickedBtnDel5)
	ON_BN_CLICKED(IDC_BTN_NEW6, OnBnClickedBtnNew6)
	ON_BN_CLICKED(IDC_BTN_EDT6, OnBnClickedBtnEdt6)
	ON_BN_CLICKED(IDC_BTN_DEL6, OnBnClickedBtnDel6)
END_MESSAGE_MAP()

void CMstComplicanze3ModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_LEVEL0, m_ctrlListLevel0);
	DDX_Control(pDX, IDC_LIST_LEVEL1, m_ctrlListLevel1);
	DDX_Control(pDX, IDC_LIST_LEVEL2, m_ctrlListLevel2);
	DDX_Control(pDX, IDC_LIST_LEVEL3, m_ctrlListLevel3);
	DDX_Control(pDX, IDC_LIST_LEVEL4, m_ctrlListLevel4);
	DDX_Control(pDX, IDC_LIST_LEVEL5, m_ctrlListLevel5);
	DDX_Control(pDX, IDC_LIST_LEVEL6, m_ctrlListLevel6);

	DDX_Control(pDX, IDC_STATIC_LEVEL0, m_ctrlStaticLevel0);
	DDX_Control(pDX, IDC_STATIC_LEVEL1, m_ctrlStaticLevel1);
	DDX_Control(pDX, IDC_STATIC_LEVEL2, m_ctrlStaticLevel2);
	DDX_Control(pDX, IDC_STATIC_LEVEL3, m_ctrlStaticLevel3);
	DDX_Control(pDX, IDC_STATIC_LEVEL4, m_ctrlStaticLevel4);
	DDX_Control(pDX, IDC_STATIC_LEVEL5, m_ctrlStaticLevel5);
	DDX_Control(pDX, IDC_STATIC_LEVEL6, m_ctrlStaticLevel6);
	DDX_Control(pDX, IDC_BTN_NEW0,      m_ctrlButtonNew0);
	DDX_Control(pDX, IDC_BTN_NEW1,      m_ctrlButtonNew1);
	DDX_Control(pDX, IDC_BTN_NEW2,      m_ctrlButtonNew2);
	DDX_Control(pDX, IDC_BTN_NEW3,      m_ctrlButtonNew3);
	DDX_Control(pDX, IDC_BTN_NEW4,      m_ctrlButtonNew4);
	DDX_Control(pDX, IDC_BTN_NEW5,      m_ctrlButtonNew5);
	DDX_Control(pDX, IDC_BTN_NEW6,      m_ctrlButtonNew6);
	DDX_Control(pDX, IDC_BTN_EDT0,      m_ctrlButtonEdt0);
	DDX_Control(pDX, IDC_BTN_EDT1,      m_ctrlButtonEdt1);
	DDX_Control(pDX, IDC_BTN_EDT2,      m_ctrlButtonEdt2);
	DDX_Control(pDX, IDC_BTN_EDT3,      m_ctrlButtonEdt3);
	DDX_Control(pDX, IDC_BTN_EDT4,      m_ctrlButtonEdt4);
	DDX_Control(pDX, IDC_BTN_EDT5,      m_ctrlButtonEdt5);
	DDX_Control(pDX, IDC_BTN_EDT6,      m_ctrlButtonEdt6);
	DDX_Control(pDX, IDC_BTN_DEL0,      m_ctrlButtonDel0);
	DDX_Control(pDX, IDC_BTN_DEL1,      m_ctrlButtonDel1);
	DDX_Control(pDX, IDC_BTN_DEL2,      m_ctrlButtonDel2);
	DDX_Control(pDX, IDC_BTN_DEL3,      m_ctrlButtonDel3);
	DDX_Control(pDX, IDC_BTN_DEL4,      m_ctrlButtonDel4);
	DDX_Control(pDX, IDC_BTN_DEL5,      m_ctrlButtonDel5);
	DDX_Control(pDX, IDC_BTN_DEL6,      m_ctrlButtonDel6);
	DDX_Control(pDX, IDCANCEL,          m_ctrlButtonCancel);
}

HBRUSH CMstComplicanze3ModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_LEVEL0:
		case IDC_LIST_LEVEL0:
//			pDC->SetTextColor(CEsamiView::m_color1);
			break;

		case IDC_STATIC_LEVEL1:
		case IDC_LIST_LEVEL1:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_STATIC_LEVEL2:
		case IDC_LIST_LEVEL2:
			pDC->SetTextColor(theApp.m_color[1]);
			break;

		case IDC_STATIC_LEVEL3:
		case IDC_LIST_LEVEL3:
			pDC->SetTextColor(theApp.m_color[2]);
			break;

		case IDC_STATIC_LEVEL4:
		case IDC_LIST_LEVEL4:
			pDC->SetTextColor(theApp.m_color[3]);
			break;

		case IDC_STATIC_LEVEL5:
		case IDC_LIST_LEVEL5:
			pDC->SetTextColor(theApp.m_color[4]);
			break;

		case IDC_STATIC_LEVEL6:
		case IDC_LIST_LEVEL6:
			pDC->SetTextColor(theApp.m_color[5]);
			break;
	}

	return hBrush;
}

BOOL CMstComplicanze3ModDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_LEVEL0)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL1)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL2)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL3)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL4)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL5)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL6)->SetFont(&theApp.m_fontBold);

	RiempiListLevel0();

	theApp.LocalizeDialog(this, CMstComplicanze3ModDlg::IDD, "MstComplicanze3ModDlg");
	return bReturn;
}

void CMstComplicanze3ModDlg::OnLbnSelchangeListLevel0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(iTemp >= 0);

	if (iTemp >= 0)
		RiempiListSubLevels((long)m_ctrlListLevel0.GetItemData(iTemp));
	else
		RiempiListSubLevels(-1);
}

void CMstComplicanze3ModDlg::OnLbnSelchangeListLevel1()
{
	int iTemp = m_ctrlListLevel1.GetCurSel();

	GetDlgItem(IDC_BTN_EDT1)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL1)->EnableWindow(iTemp >= 0);
}

void CMstComplicanze3ModDlg::OnLbnSelchangeListLevel2()
{
	int iTemp = m_ctrlListLevel2.GetCurSel();

	GetDlgItem(IDC_BTN_EDT2)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL2)->EnableWindow(iTemp >= 0);
}

void CMstComplicanze3ModDlg::OnLbnSelchangeListLevel3()
{
	int iTemp = m_ctrlListLevel3.GetCurSel();

	GetDlgItem(IDC_BTN_EDT3)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL3)->EnableWindow(iTemp >= 0);
}

void CMstComplicanze3ModDlg::OnLbnSelchangeListLevel4()
{
	int iTemp = m_ctrlListLevel4.GetCurSel();

	GetDlgItem(IDC_BTN_EDT4)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL4)->EnableWindow(iTemp >= 0);
}

void CMstComplicanze3ModDlg::OnLbnSelchangeListLevel5()
{
	int iTemp = m_ctrlListLevel5.GetCurSel();

	GetDlgItem(IDC_BTN_EDT5)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL5)->EnableWindow(iTemp >= 0);
}

void CMstComplicanze3ModDlg::OnLbnSelchangeListLevel6()
{
	int iTemp = m_ctrlListLevel6.GetCurSel();

	GetDlgItem(IDC_BTN_EDT6)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL6)->EnableWindow(iTemp >= 0);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnNew0()
{
	NewString(0, 0);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnEdt0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel0.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnDel0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel0.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnNew1()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 1);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnEdt1()
{
	int iTemp = m_ctrlListLevel1.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel1.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnDel1()
{
	int iTemp = m_ctrlListLevel1.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel1.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnNew2()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 2);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnEdt2()
{
	int iTemp = m_ctrlListLevel2.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel2.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnDel2()
{
	int iTemp = m_ctrlListLevel2.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel2.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnNew3()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 3);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnEdt3()
{
	int iTemp = m_ctrlListLevel3.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel3.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnDel3()
{
	int iTemp = m_ctrlListLevel3.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel3.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnNew4()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 4);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnEdt4()
{
	int iTemp = m_ctrlListLevel4.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel4.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnDel4()
{
	int iTemp = m_ctrlListLevel4.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel4.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnNew5()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 5);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnEdt5()
{
	int iTemp = m_ctrlListLevel5.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel5.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnDel5()
{
	int iTemp = m_ctrlListLevel5.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel5.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnNew6()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 6);
}

void CMstComplicanze3ModDlg::OnBnClickedBtnEdt6()
{
	int iTemp = m_ctrlListLevel6.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel6.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::OnBnClickedBtnDel6()
{
	int iTemp = m_ctrlListLevel6.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel6.GetItemData(iTemp));
}

void CMstComplicanze3ModDlg::RiempiListLevel0()
{
	int iTemp = 0;
	CMstComplicanze3Set setTemp;

	setTemp.SetOpenFilter("Padre=0 AND Livello=0");
	setTemp.SetSortRecord("Descrizione");

	m_ctrlListLevel0.ResetContent();
	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(FALSE);

	if (setTemp.OpenRecordset("CMstComplicanze3ModDlg::RiempiListLevel0") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lID);
			
			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstComplicanze3ModDlg::RiempiListLevel0");
	}
}

void CMstComplicanze3ModDlg::RiempiListSubLevels(long lPadre)
{
	UINT uiNewButtons[] = { IDC_BTN_NEW1, IDC_BTN_NEW2, IDC_BTN_NEW3, IDC_BTN_NEW4, IDC_BTN_NEW5, IDC_BTN_NEW6 };
	UINT uiEdtButtons[] = { IDC_BTN_EDT1, IDC_BTN_EDT2, IDC_BTN_EDT3, IDC_BTN_EDT4, IDC_BTN_EDT5, IDC_BTN_EDT6 };
	UINT uiDelButtons[] = { IDC_BTN_DEL1, IDC_BTN_DEL2, IDC_BTN_DEL3, IDC_BTN_DEL4, IDC_BTN_DEL5, IDC_BTN_DEL6 };
	CListBox* pListLevel[] = { &m_ctrlListLevel1, &m_ctrlListLevel2, &m_ctrlListLevel3, &m_ctrlListLevel4, &m_ctrlListLevel5, &m_ctrlListLevel6 };

	int iTemp;
	int nTemp;
	CString strTemp;
	CMstComplicanze3Set setTemp;

	setTemp.SetSortRecord("Descrizione");

	for(nTemp = 0; nTemp < 6; nTemp++)
	{
		iTemp = 0;

		GetDlgItem(uiNewButtons[nTemp])->EnableWindow(lPadre >= 0);
		GetDlgItem(uiEdtButtons[nTemp])->EnableWindow(FALSE);
		GetDlgItem(uiDelButtons[nTemp])->EnableWindow(FALSE);

		pListLevel[nTemp]->ResetContent();

		strTemp.Format("Padre=%li AND Livello=%d", lPadre, nTemp + 1);
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstComplicanze3ModDlg::RiempiListSubLevels") == TRUE)
		{
			while(setTemp.IsEOF() == FALSE)
			{
				pListLevel[nTemp]->InsertString(iTemp, setTemp.m_sDescrizione);
				pListLevel[nTemp]->SetItemData(iTemp, (DWORD)setTemp.m_lID);

				iTemp++;
				setTemp.MoveNext();
			}
		}
	}

	setTemp.CloseRecordset("CMstComplicanze3ModDlg::RiempiListSubLevels");
}

void CMstComplicanze3ModDlg::NewString(long lPadre, long lLivello)
{
	CEditStringDlg dlg(this, IDS_MSTPROCEDURETER_TITLE_1, "");

	if (dlg.DoModal() == IDOK)
	{
		CMstComplicanze3Set setTemp;

		if (setTemp.OpenRecordset("CMstComplicanze3ModDlg::NewString") == TRUE)
		{
			if (setTemp.AddNewRecordset("CMstComplicanze3ModDlg::NewString") == TRUE)
			{
				setTemp.m_lPadre = lPadre;
				setTemp.m_lLivello = lLivello;
				setTemp.m_sDescrizione = dlg.GetValue();

				setTemp.UpdateRecordset("CMstComplicanze3ModDlg::NewString");
			}

			setTemp.CloseRecordset("CMstComplicanze3ModDlg::NewString");
		}

		if (lLivello == 0)
		{
			RiempiListLevel0();
			RiempiListSubLevels(-1);
		}
		else
		{
			int iTemp = m_ctrlListLevel0.GetCurSel();

			if (iTemp >= 0)
				RiempiListSubLevels((long)m_ctrlListLevel0.GetItemData(iTemp));
			else
				RiempiListSubLevels(-1);
		}
	}
}

void CMstComplicanze3ModDlg::EdtString(long lID)
{
	CString strTemp;
	long lLivello = 0;
	BOOL bEdited = FALSE;
	CMstComplicanze3Set setTemp;

	strTemp.Format("ID=%li", lID);
	setTemp.SetOpenFilter(strTemp);

	if (setTemp.OpenRecordset("CMstComplicanze3ModDlg::EdtString") == TRUE)
	{
		if (setTemp.IsEOF() == FALSE)
		{
			CEditStringDlg dlg(this, IDS_MSTPROCEDURETER_TITLE_2, setTemp.m_sDescrizione);

			if (dlg.DoModal() == IDOK)
			{
				lLivello = setTemp.m_lLivello;

				if (setTemp.EditRecordset("CMstComplicanze3ModDlg::EdtString") == TRUE)
				{
					bEdited = TRUE;

					setTemp.m_sDescrizione = dlg.GetValue();

					setTemp.UpdateRecordset("CMstComplicanze3ModDlg::EdtString");
				}
			}
		}

		setTemp.CloseRecordset("CMstComplicanze3ModDlg::EdtString");
	}

	if (bEdited == TRUE)
	{
		if (lLivello == 0)
		{
			RiempiListLevel0();
			RiempiListSubLevels(-1);
		}
		else
		{
			int iTemp = m_ctrlListLevel0.GetCurSel();

			if (iTemp >= 0)
				RiempiListSubLevels((long)m_ctrlListLevel0.GetItemData(iTemp));
			else
				RiempiListSubLevels(-1);
		}
	}
}

void CMstComplicanze3ModDlg::DelString(long lID)
{
	CString strTemp;
	long lLivello = 0;
	BOOL bDeleted = FALSE;
	CMstComplicanze3Set setTemp;

	strTemp.Format("ID=%li", lID);
	setTemp.SetOpenFilter(strTemp);

	if (setTemp.OpenRecordset("CMstComplicanze3ModDlg::EdtString") == TRUE)
	{
		if (setTemp.IsEOF() == FALSE)
		{
			lLivello = setTemp.m_lLivello;

			CString strTmp;
			strTmp.Format(theApp.GetMessageString(IDS_MSTDIAGNOSI_CONFIRM_DEL),
				          setTemp.m_sDescrizione);
			if (theApp.AfxMessageBoxEndo(strTmp, MB_YESNO) == IDYES)
			{
				if (lLivello == 0)
				{
					if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MSTDIAGNOSI_CONFIRM_DEL_2), MB_YESNO | MB_ICONSTOP) == IDNO)
						bDeleted = TRUE;
				}
				else
				{
					bDeleted = TRUE;
				}
			}
		}
		if (bDeleted == TRUE)
			setTemp.DeleteRecordset("CMstComplicanze3ModDlg::EdtString");

		setTemp.CloseRecordset("CMstComplicanze3ModDlg::EdtString");
	}

	if (bDeleted == TRUE)
	{
		if (lLivello == 0)
		{
			RiempiListLevel0();
			RiempiListSubLevels(-1);
		}
		else
		{
			int iTemp = m_ctrlListLevel0.GetCurSel();

			if (iTemp >= 0)
				RiempiListSubLevels((long)m_ctrlListLevel0.GetItemData(iTemp));
			else
				RiempiListSubLevels(-1);
		}
	}
}