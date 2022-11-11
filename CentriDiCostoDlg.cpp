#include "stdafx.h"
#include "Endox.h"
#include "CentriDiCostoDlg.h"
#include "EsamiView.h"

#include "EditStringDlg.h"
#include "CentriDiCostoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCentriDiCostoDlg, CDialog)

CCentriDiCostoDlg::CCentriDiCostoDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CCentriDiCostoDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CCentriDiCostoDlg::~CCentriDiCostoDlg()
{
}

BEGIN_MESSAGE_MAP(CCentriDiCostoDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LIST, OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BTN_NUOVO, OnBnClickedBtnNuovo)
	ON_BN_CLICKED(IDC_BTN_MODIFICA, OnBnClickedBtnModifica)
	ON_BN_CLICKED(IDC_BTN_ELIMINA, OnBnClickedBtnElimina)

END_MESSAGE_MAP()

void CCentriDiCostoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	
	DDX_Control(pDX, IDC_STATIC_CENTRIDICOSTO, m_ctrlStatic);

	DDX_Control(pDX, IDCANCEL,                m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_BTN_NUOVO,    m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_MODIFICA, m_ctrlButtonMod);
	DDX_Control(pDX, IDC_BTN_ELIMINA,  m_ctrlButtonDel);

}

HBRUSH CCentriDiCostoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC:
		case IDC_LIST:
			pDC->SetTextColor(theApp.m_color[0]);
			break;
	}

	return hBrush;
}

BOOL CCentriDiCostoDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);

	RiempiList();
	theApp.LocalizeDialog(this, CCentriDiCostoDlg::IDD, "CentriDiCostoDlg");

	return bReturn;
}

void CCentriDiCostoDlg::RiempiList()
{
	int iIndex = 0;
	CCentriDiCostoSet setTemp;
	
	m_ctrlList.ResetContent();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CCentriDiCostoDlg::RiempiLista") == FALSE)
		return;

	while(setTemp.IsEOF() == FALSE)
	{
		m_ctrlList.InsertString(iIndex, setTemp.m_sDescrizione);
		m_ctrlList.SetItemData(iIndex, setTemp.m_lContatore);

		iIndex++;
		setTemp.MoveNext();
	}

	setTemp.CloseRecordset("CCentriDiCostoDlg::RiempiLista");

	m_ctrlButtonMod.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
}

void CCentriDiCostoDlg::OnLbnSelchangeList()
{
	static int iPrevSel = LB_ERR;
	int iCurrSel = m_ctrlList.GetCurSel();

	if (iCurrSel == iPrevSel)
		return;

	TRACE1("-> OnLbnSelchangeListOrgani(%d)\n", iCurrSel);

	iPrevSel = iCurrSel;

	GetDlgItem(IDC_BTN_MODIFICA)->EnableWindow(iCurrSel >= 0);
	GetDlgItem(IDC_BTN_ELIMINA)->EnableWindow(iCurrSel >= 0);
}

void CCentriDiCostoDlg::OnBnClickedBtnNuovo()
{
	CEditStringDlg dlg(this, IDS_CENTRIDICOSTO_TITLE_1, "");

	if (dlg.DoModal() == IDOK)
	{
		CCentriDiCostoSet setTemp;

		if (setTemp.OpenRecordset("CCentriDiCostoDlg::OnBnClickedBtnNuovo") == TRUE)
		{
			if (setTemp.AddNewRecordset("CCentriDiCostoDlg::OnBnClickedBtnNuovo") == TRUE)
			{
				setTemp.m_sDescrizione = dlg.GetValue();

				setTemp.UpdateRecordset("CCentriDiCostoDlg::OnBnClickedBtnNuovo");
			}

			setTemp.CloseRecordset("CCentriDiCostoDlg::OnBnClickedBtnNuovo");
		}

		RiempiList();
	}
}

void CCentriDiCostoDlg::OnBnClickedBtnModifica()
{
	CString strTemp;
	m_ctrlList.GetText(m_ctrlList.GetCurSel(), strTemp);

	CEditStringDlg dlg(this, IDS_CENTRIDICOSTO_TITLE_2, strTemp);

	if (dlg.DoModal() == IDOK)
	{
		CCentriDiCostoSet setTemp;

		strTemp.Format("Contatore=%d", (int)m_ctrlList.GetItemData(m_ctrlList.GetCurSel()));
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CCentriDiCostoDlg::OnBnClickedBtnModifica") == TRUE)
		{
			if (setTemp.IsEOF() == FALSE)
			{
				if (setTemp.EditRecordset("CCentriDiCostoDlg::OnBnClickedBtnModifica") == TRUE)
				{
					setTemp.m_sDescrizione = dlg.GetValue();

					setTemp.UpdateRecordset("CCentriDiCostoDlg::OnBnClickedBtnModifica");
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CENTRIDICOSTODLG_ERR_1));
			}

			setTemp.CloseRecordset("CCentriDiCostoDlg::OnBnClickedBtnModifica");
		}

		RiempiList();
	}
}

void CCentriDiCostoDlg::OnBnClickedBtnElimina()
{
	CString strTemp, strTmp;
	m_ctrlList.GetText(m_ctrlList.GetCurSel(), strTemp);

	strTmp.Format(theApp.GetMessageString(IDS_CENTRIDICOSTODLG_CONFIRM_DEL),
		          strTemp);
	if (theApp.AfxMessageBoxEndo(strTmp, MB_YESNO) == IDNO)
		return;

	CCentriDiCostoSet setTemp;

	strTemp.Format("Contatore = %d", (int)m_ctrlList.GetItemData(m_ctrlList.GetCurSel()));
	setTemp.SetOpenFilter(strTemp);

	if (setTemp.OpenRecordset("CCentriDiCostoDlg::OnBnClickedBtnElimina") == TRUE)
	{
		if (setTemp.IsEOF() == FALSE)
		{
			if (setTemp.DeleteRecordset("CCentriDiCostoDlg::OnBnClickedBtnElimina") == FALSE)
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CENTRIDICOSTODLG_CANNOT_DELETE));
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CENTRIDICOSTODLG_CANNOT_DELETE_2));
		}

		setTemp.CloseRecordset("CCentriDiCostoDlg::OnBnClickedBtnElimina");
	}

	RiempiList();
}
