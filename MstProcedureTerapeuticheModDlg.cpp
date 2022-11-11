#include "stdafx.h"
#include "Endox.h"
#include "MstProcedureTerapeuticheModDlg.h"
#include "EsamiView.h"

#include "MstProcedureTerapeuticheSet.h"
#include "EditStringDlg.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstProcedureTerapeuticheModDlg, CDialog)

CMstProcedureTerapeuticheModDlg::CMstProcedureTerapeuticheModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstProcedureTerapeuticheModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_lTipoEsame = -1;
}

CMstProcedureTerapeuticheModDlg::~CMstProcedureTerapeuticheModDlg()
{
}

BEGIN_MESSAGE_MAP(CMstProcedureTerapeuticheModDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_CBN_SELCHANGE(IDC_COMBO_TIPOESAME, OnCbnSelchangeComboTipoesame)
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

void CMstProcedureTerapeuticheModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_TIPOESAME, m_ctrlComboTipoEsame);
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

HBRUSH CMstProcedureTerapeuticheModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CMstProcedureTerapeuticheModDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_COMBO_TIPOESAME)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_LEVEL0)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL1)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL2)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL3)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL4)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL5)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_LEVEL6)->SetFont(&theApp.m_fontBold);

	RiempiComboTipoEsame();
	theApp.LocalizeDialog(this, CMstProcedureTerapeuticheModDlg::IDD, "MstProcedureTerapeuticheModDlg");

	return bReturn;
}

void CMstProcedureTerapeuticheModDlg::OnCbnSelchangeComboTipoesame()
{
	int iTemp = m_ctrlComboTipoEsame.GetCurSel();

	GetDlgItem(IDC_BTN_NEW0)->EnableWindow(iTemp >= 0);

	if (iTemp >= 0)
		m_lTipoEsame = (long)m_ctrlComboTipoEsame.GetItemData(iTemp);
	else
		m_lTipoEsame = -1;

	RiempiListLevel0();
	RiempiListSubLevels(-1);
}

void CMstProcedureTerapeuticheModDlg::OnLbnSelchangeListLevel0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(iTemp >= 0);

	if (iTemp >= 0)
		RiempiListSubLevels((long)m_ctrlListLevel0.GetItemData(iTemp));
	else
		RiempiListSubLevels(-1);
}

void CMstProcedureTerapeuticheModDlg::OnLbnSelchangeListLevel1()
{
	int iTemp = m_ctrlListLevel1.GetCurSel();

	GetDlgItem(IDC_BTN_EDT1)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL1)->EnableWindow(iTemp >= 0);
}

void CMstProcedureTerapeuticheModDlg::OnLbnSelchangeListLevel2()
{
	int iTemp = m_ctrlListLevel2.GetCurSel();

	GetDlgItem(IDC_BTN_EDT2)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL2)->EnableWindow(iTemp >= 0);
}

void CMstProcedureTerapeuticheModDlg::OnLbnSelchangeListLevel3()
{
	int iTemp = m_ctrlListLevel3.GetCurSel();

	GetDlgItem(IDC_BTN_EDT3)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL3)->EnableWindow(iTemp >= 0);
}

void CMstProcedureTerapeuticheModDlg::OnLbnSelchangeListLevel4()
{
	int iTemp = m_ctrlListLevel4.GetCurSel();

	GetDlgItem(IDC_BTN_EDT4)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL4)->EnableWindow(iTemp >= 0);
}

void CMstProcedureTerapeuticheModDlg::OnLbnSelchangeListLevel5()
{
	int iTemp = m_ctrlListLevel5.GetCurSel();

	GetDlgItem(IDC_BTN_EDT5)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL5)->EnableWindow(iTemp >= 0);
}

void CMstProcedureTerapeuticheModDlg::OnLbnSelchangeListLevel6()
{
	int iTemp = m_ctrlListLevel6.GetCurSel();

	GetDlgItem(IDC_BTN_EDT6)->EnableWindow(iTemp >= 0);
	GetDlgItem(IDC_BTN_DEL6)->EnableWindow(iTemp >= 0);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnNew0()
{
	NewString(0, 0);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnEdt0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel0.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnDel0()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel0.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnNew1()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 1);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnEdt1()
{
	int iTemp = m_ctrlListLevel1.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel1.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnDel1()
{
	int iTemp = m_ctrlListLevel1.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel1.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnNew2()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 2);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnEdt2()
{
	int iTemp = m_ctrlListLevel2.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel2.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnDel2()
{
	int iTemp = m_ctrlListLevel2.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel2.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnNew3()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 3);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnEdt3()
{
	int iTemp = m_ctrlListLevel3.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel3.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnDel3()
{
	int iTemp = m_ctrlListLevel3.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel3.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnNew4()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 4);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnEdt4()
{
	int iTemp = m_ctrlListLevel4.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel4.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnDel4()
{
	int iTemp = m_ctrlListLevel4.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel4.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnNew5()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 5);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnEdt5()
{
	int iTemp = m_ctrlListLevel5.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel5.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnDel5()
{
	int iTemp = m_ctrlListLevel5.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel5.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnNew6()
{
	int iTemp = m_ctrlListLevel0.GetCurSel();

	if (iTemp >= 0)
		NewString((long)m_ctrlListLevel0.GetItemData(iTemp), 6);
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnEdt6()
{
	int iTemp = m_ctrlListLevel6.GetCurSel();

	if (iTemp >= 0)
		EdtString((long)m_ctrlListLevel6.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::OnBnClickedBtnDel6()
{
	int iTemp = m_ctrlListLevel6.GetCurSel();

	if (iTemp >= 0)
		DelString((long)m_ctrlListLevel6.GetItemData(iTemp));
}

void CMstProcedureTerapeuticheModDlg::RiempiComboTipoEsame()
{
	int iTemp = 0;
	CTipoEsameSet setTemp;

	setTemp.SetSortRecord("Descrizione");
	//setTemp.SetOpenFilter("Visibile=1");

	if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::RiempiComboTipoEsame") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlComboTipoEsame.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlComboTipoEsame.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::RiempiComboTipoEsame");
	}
}

void CMstProcedureTerapeuticheModDlg::RiempiListLevel0()
{
	int iTemp = 0;
	CString strTemp;
	CMstProcedureTerapeuticheSet setTemp;

	strTemp.Format("TipoEsame=%li", m_lTipoEsame);
	setTemp.SetBaseFilter(strTemp);
	setTemp.SetOpenFilter("Padre=0 AND Livello=0");
	setTemp.SetSortRecord("Descrizione");

	m_ctrlListLevel0.ResetContent();
	GetDlgItem(IDC_BTN_EDT0)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL0)->EnableWindow(FALSE);

	if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::RiempiListLevel0") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);
			
			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::RiempiListLevel0");
	}
}

void CMstProcedureTerapeuticheModDlg::RiempiListSubLevels(long lPadre)
{
	UINT uiNewButtons[] = { IDC_BTN_NEW1, IDC_BTN_NEW2, IDC_BTN_NEW3, IDC_BTN_NEW4, IDC_BTN_NEW5, IDC_BTN_NEW6 };
	UINT uiEdtButtons[] = { IDC_BTN_EDT1, IDC_BTN_EDT2, IDC_BTN_EDT3, IDC_BTN_EDT4, IDC_BTN_EDT5, IDC_BTN_EDT6 };
	UINT uiDelButtons[] = { IDC_BTN_DEL1, IDC_BTN_DEL2, IDC_BTN_DEL3, IDC_BTN_DEL4, IDC_BTN_DEL5, IDC_BTN_DEL6 };
	CListBox* pListLevel[] = { &m_ctrlListLevel1, &m_ctrlListLevel2, &m_ctrlListLevel3, &m_ctrlListLevel4, &m_ctrlListLevel5, &m_ctrlListLevel6 };

	int iTemp;
	int nTemp;
	CString strTemp;
	CMstProcedureTerapeuticheSet setTemp;

	strTemp.Format("TipoEsame=%li", m_lTipoEsame);
	setTemp.SetBaseFilter(strTemp);
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

		if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::RiempiListSubLevels") == TRUE)
		{
			while(setTemp.IsEOF() == FALSE)
			{
				pListLevel[nTemp]->InsertString(iTemp, setTemp.m_sDescrizione);
				pListLevel[nTemp]->SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

				iTemp++;
				setTemp.MoveNext();
			}
		}
	}

	setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::RiempiListSubLevels");
}

void CMstProcedureTerapeuticheModDlg::NewString(long lPadre, long lLivello)
{
	CEditStringDlg dlg(this, IDS_MSTPROCEDURETER_TITLE_1, "");

	if (dlg.DoModal() == IDOK)
	{
		CMstProcedureTerapeuticheSet setTemp;

		if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::NewString") == TRUE)
		{
			if (setTemp.AddNewRecordset("CMstProcedureTerapeuticheModDlg::NewString") == TRUE)
			{
				setTemp.m_lTipoEsame = m_lTipoEsame;
				setTemp.m_lPadre = lPadre;
				setTemp.m_lLivello = lLivello;
				setTemp.m_sDescrizione = dlg.GetValue();

				setTemp.UpdateRecordset("CMstProcedureTerapeuticheModDlg::NewString");
			}

			setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::NewString");
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

void CMstProcedureTerapeuticheModDlg::EdtString(long lContatore)
{
	CString strTemp;
	long lLivello = 0;
	BOOL bEdited = FALSE;
	CMstProcedureTerapeuticheSet setTemp;

	strTemp.Format("Contatore=%li", lContatore);
	setTemp.SetOpenFilter(strTemp);

	if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::EdtString") == TRUE)
	{
		if (setTemp.IsEOF() == FALSE)
		{
			CEditStringDlg dlg(this, IDS_MSTPROCEDURETER_TITLE_2, setTemp.m_sDescrizione);

			if (dlg.DoModal() == IDOK)
			{
				lLivello = setTemp.m_lLivello;

				if (setTemp.EditRecordset("CMstProcedureTerapeuticheModDlg::EdtString") == TRUE)
				{
					bEdited = TRUE;

					setTemp.m_sDescrizione = dlg.GetValue();

					setTemp.UpdateRecordset("CMstProcedureTerapeuticheModDlg::EdtString");
				}
			}
		}

		setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::EdtString");
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

void CMstProcedureTerapeuticheModDlg::DelString(long lContatore)
{
	CString strTemp;
	long lLivello = 0;
	BOOL bDeleted = FALSE;
	CMstProcedureTerapeuticheSet setTemp;

	strTemp.Format("Contatore=%li", lContatore);
	setTemp.SetOpenFilter(strTemp);

	if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::EdtString") == TRUE)
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
			setTemp.DeleteRecordset("CMstProcedureTerapeuticheModDlg::EdtString");

		setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::EdtString");
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