#include "stdafx.h"
#include "Endox.h"
#include "CalibDlg.h"

#include "Calib.h"
#include "CalibList.h"
#include "CalibNameDlg.h"
#include "CalibPicDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCalibDlg::CCalibDlg(CWnd* pParent, CEsamiView* pEsamiView, CCalibList* pCalibList)
	: CDialog(CCalibDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;
	m_pCalibList = pCalibList;
}

BEGIN_MESSAGE_MAP(CCalibDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)

	ON_LBN_SELCHANGE(IDC_LISTA_MISURE, OnSelChangeListaMisure)
END_MESSAGE_MAP()

void CCalibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_SCREEN, m_ctrlStaticScreen);
	DDX_Control(pDX, IDC_STATIC_REAL, m_ctrlStaticReal);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_LISTA_MISURE, m_ctrlCalib);
}

void CCalibDlg::OnCancel()
{
	// devo ricaricare la calibrazioni dal file (così da perdere tutte le modifiche fatte in memoria) //
	// m_pCalibList->WriteDisk();
	
	CDialog::OnCancel();
}

BOOL CCalibDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	int nIndex = 0;
	POSITION pos = m_pCalibList->GetFirstCalibPos();
	while(pos != NULL)
	{
		CCalib* pCalib = m_pCalibList->GetNextCalib(pos);

		m_ctrlCalib.InsertString(nIndex, pCalib->m_strName);
		m_ctrlCalib.SetItemDataPtr(nIndex, pCalib);

		nIndex++;
	}

	theApp.LocalizeDialog(this, CCalibDlg::IDD, "CalibDlg");
	return TRUE;                    
} 

void CCalibDlg::OnOK()
{
	m_pCalibList->WriteDisk();
	
	CDialog::OnOK();
}

void CCalibDlg::OnBtnNew()
{
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, "Tutti i file|*.*|Bitmap (*.bmp)|*.bmp|JPEG (*.jpg;*.jpeg)|*.jpg; *.jpeg|JPEG 2000 (*.jp2)|*.jp2|Tagged Image File Format (*.tif;*.tiff)|*.tif; *.tiff|CompuServe Graphics Interchange (*.gif)|*.gif|", this, 0, FALSE);
	if (dlgFile.DoModal() == IDOK)
	{
		CCalibPicDlg dlgPic(this, m_pEsamiView, dlgFile.GetPathName());
		if (dlgPic.DoModal() == IDOK)
		{
			CCalibNameDlg dlgName(this);
			if (dlgName.DoModal() == IDOK)
			{
				CCalib* pCalib = m_pCalibList->NewCalib();

				pCalib->SetConvRatio(dlgPic.GetUser(), dlgPic.GetScreen());
				pCalib->m_strName = dlgName.m_strName;

				int nIndex = m_ctrlCalib.GetCount();
				m_ctrlCalib.InsertString(nIndex, pCalib->m_strName);
				m_ctrlCalib.SetItemDataPtr(nIndex, pCalib);
			}
		}
	}	
}

void CCalibDlg::OnBtnEdt()
{
	int nIndex = m_ctrlCalib.GetCurSel();

	if (nIndex >= 0)
	{
		CCalib* pCalib = (CCalib*)m_ctrlCalib.GetItemDataPtr(nIndex);

		CCalibNameDlg dlg(this);
		dlg.m_strName = pCalib->m_strName;
		if (dlg.DoModal() == IDOK)
		{
			pCalib->m_strName = dlg.m_strName;

			m_ctrlCalib.DeleteString(nIndex);

			m_ctrlCalib.InsertString(nIndex, pCalib->m_strName);
			m_ctrlCalib.SetItemDataPtr(nIndex, pCalib);
		}
	}
}

void CCalibDlg::OnBtnDel()
{
	int nIndex = m_ctrlCalib.GetCurSel();

	if (nIndex >= 0)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CALIBRATION_DELETE), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CCalib* pCalib = (CCalib*)m_ctrlCalib.GetItemDataPtr(nIndex);

			m_pCalibList->RemoveCalib(pCalib);
			if (m_pCalibList->IsEmpty())
				m_pCalibList->NewCalib();
				
		    m_ctrlCalib.ResetContent();

			int nIndex = 0;
			POSITION pos = m_pCalibList->GetFirstCalibPos();
			while(pos != NULL)
			{
				CCalib* pCalib = m_pCalibList->GetNextCalib(pos);

				m_ctrlCalib.InsertString(nIndex, pCalib->m_strName);
				m_ctrlCalib.SetItemDataPtr(nIndex, pCalib);

				nIndex++;
			}
		}
	}
}

void CCalibDlg::OnSelChangeListaMisure()
{
	int nCurSel = m_ctrlCalib.GetCurSel();

	if (nCurSel < 0)
	{
		SetDlgItemText(IDC_REALE, "");
		SetDlgItemText(IDC_SCHERMO, "");
	}
	else
	{
		CCalib* pCalib = (CCalib*)m_ctrlCalib.GetItemDataPtr(nCurSel);
		
		SetDlgItemText(IDC_REALE, pCalib->m_strUserMisura);
		SetDlgItemText(IDC_SCHERMO, pCalib->m_strScreenMisura);
	}

	UpdateData(FALSE);
}