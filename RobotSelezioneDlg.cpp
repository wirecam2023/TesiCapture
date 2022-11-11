#include "stdafx.h"
#include "Endox.h"
#include "RobotSelezioneDlg.h"

#include "EsamiView.h"
#include "RobotSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRobotSelezioneDlg::CRobotSelezioneDlg(CWnd* pParent)
	: CDialog(CRobotSelezioneDlg::IDD, pParent)
{
	m_lIdDispositivo = -1;
	m_sDescription = "";
	m_lType = CRobotSet::Type::Rimage;
	m_sHost = "";
	m_lPort = 0;
	m_sBackupLabelPath = "";
	m_sPatientLabelPath = "";
	m_sMergeDirectoryPath = "";
	m_sTempDirectoryPath = "";
	m_bSimulationMode = FALSE;
}

BEGIN_MESSAGE_MAP(CRobotSelezioneDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CONTINUA, OnBnClickedContinua)
END_MESSAGE_MAP()

void CRobotSelezioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_CMB_DISPOSITIVO, m_ctrlCmbDispositivo);
	DDX_Control(pDX, IDC_BTN_CONTINUA, m_ctrlBtnContinua);

}

BOOL CRobotSelezioneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBig, TRUE);

	CRobotSet set;

	if (set.OpenRecordset("CRobotSelezioneDlg::OnInitDialog"))
	{
		while (!set.IsEOF())
		{
			int index = m_ctrlCmbDispositivo.AddString(set.m_sDescription);
			m_ctrlCmbDispositivo.SetItemData(index, set.m_lID);

			if (set.m_lID == theApp.m_lIdRobotDefault)
				m_ctrlCmbDispositivo.SetCurSel(index);

			set.MoveNext();
		}

		set.CloseRecordset("CRobotSelezioneDlg::OnInitDialog");
	}

	if (m_ctrlCmbDispositivo.GetCurSel() < 0)
		m_ctrlCmbDispositivo.SetCurSel(0);

	theApp.LocalizeDialog(this, CRobotSelezioneDlg::IDD, "RobotSelezioneDlg");

	if (m_ctrlCmbDispositivo.GetCount() == 1)
		OnBnClickedContinua();

	return TRUE;
}


void CRobotSelezioneDlg::OnBnClickedContinua()
{
	int index = m_ctrlCmbDispositivo.GetCurSel();
	m_lIdDispositivo = m_ctrlCmbDispositivo.GetItemData(index);

	CRobotSet set;
	CString filter;
	filter.Format("ID=%li", m_lIdDispositivo);
	set.SetOpenFilter(filter);

	if (set.OpenRecordset("CRobotSelezioneDlg::OnInitDialog"))
	{
		if (!set.IsEOF())
		{
			m_sDescription = set.m_sDescription;
			m_lType = (CRobotSet::Type) set.m_lType;
			m_sHost = set.m_sHost;
			m_lPort = set.m_lPort;
			m_sBackupLabelPath = set.m_sBackupLabelPath;
			m_sPatientLabelPath = set.m_sPatientLabelPath;
			m_sMergeDirectoryPath = set.m_sMergeDirectoryPath;
			m_sTempDirectoryPath = set.m_sTempDirectoryPath;
			m_bSimulationMode = set.m_bSimulationMode;

			set.MoveNext();
		}

		set.CloseRecordset("CRobotSelezioneDlg::OnInitDialog");
	}

	CDialog::OnOK();
}

void CRobotSelezioneDlg::OnCancel()
{

}

void CRobotSelezioneDlg::OnOK()
{
}

