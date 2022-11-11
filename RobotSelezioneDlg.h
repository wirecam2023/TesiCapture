#pragma once

#include "RobotSet.h"

class CRobotSelezioneDlg : public CDialog
{

public:

	CRobotSelezioneDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_ROBOTSELEZIONE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedContinua();

	long m_lIdDispositivo;
	CString	m_sDescription;
	CRobotSet::Type	m_lType;
	CString m_sHost;
	long	m_lPort;
	CString m_sBackupLabelPath;
	CString m_sPatientLabelPath;
	CString m_sMergeDirectoryPath;
	CString m_sTempDirectoryPath;
	BOOL	m_bSimulationMode;

private:
	CStaticLocalize m_ctrlStatic1;
	CComboBox m_ctrlCmbDispositivo;
	CButtonLocalize m_ctrlBtnContinua;

};
