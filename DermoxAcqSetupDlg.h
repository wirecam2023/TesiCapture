#ifndef _DERMOXACQSETUPDLG_H_
	#define _DERMOXACQSETUPDLG_H_

#include "LibCap\xcapCOMCommon.h"

class CDermoxAcqSetupDlg : public CDialog
{
	DECLARE_DYNAMIC(CDermoxAcqSetupDlg)

public:

	CDermoxAcqSetupDlg(CWnd* pParent = NULL);
	virtual ~CDermoxAcqSetupDlg();

	enum { IDD = IDD_DERMOX_ACQ_SETUP };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	void OnPaint();
	void OnTimer(UINT nIDEvent);
	void CheckFieldsToEnable();

	DECLARE_MESSAGE_MAP()

	LRESULT OnPressPedal1(WPARAM wParam, LPARAM lParam);
	LRESULT OnPressPedal2(WPARAM wParam, LPARAM lParam);

private:

	void InitComPort();
	void InvalidateComRegion();
	void OnChangeCom();

	// --- //

	CButton m_ctrlBtnCom1;
	CButton m_ctrlBtnCom2;
	CButton m_ctrlBtnCom3;
	CButton m_ctrlBtnCom4;
	CButton m_ctrlBtnPhotoAcqNav;

	CButtonLocalize m_ctrlBtnCom0;
	CButtonLocalize m_ctrlBtnComInverti;
	CButtonLocalize m_ctrlChkPhotoAcq;

	CComboBox m_ctrlCombo0[10];
	CComboBox m_ctrlCombo1[10];

	CEdit m_ctrlEdit0;
	CEdit m_ctrlEdit1;
	CEdit m_ctrlEdit2;
	CEdit m_ctrlEdit3;
	CEdit m_ctrlEdit4;
	CEdit m_ctrlEdit5;
	CEdit m_ctrlEdit6;
	CEdit m_ctrlEdit7;
	CEdit m_ctrlEdit8;
	CEdit m_ctrlEdit9;	
	CEdit m_ctrlEditPhotoAcqDir;

	CStatic m_ctrlStatic0;
	CStatic m_ctrlStatic1;
	CStatic m_ctrlStatic2;
	CStatic m_ctrlStatic3;
	CStatic m_ctrlStatic4;
	CStatic m_ctrlStatic5;
	CStatic m_ctrlStatic6;
	CStatic m_ctrlStatic7;
	CStatic m_ctrlStatic8;
	CStatic m_ctrlStatic9;
	CStatic m_ctrlStaticPhotoAcqDir;

	CStaticLocalize m_ctrlStaticCom;

	// --- //

	xcapCOMStartListen_PTR xcapCOMStartListen;
	xcapCOMStopListen_PTR xcapCOMStopListen;
	HMODULE m_hModuleCOM;

	int m_iComPort;
	BOOL m_bComPortInv;

	BOOL m_bSx;
	BOOL m_bDx;

	CString m_sAcqPhotoDirectory;
	BOOL m_bPhotoAcq;

public:
	afx_msg void OnBnClickedCheckPhotoacq();
	afx_msg void OnBnClickedBtnAcqNav();
};

#endif /* _DERMOXACQSETUPDLG_H_ */