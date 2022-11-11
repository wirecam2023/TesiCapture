#ifndef _EXPORTPROGRESSDLG_H_
	#define _EXPORTPROGRESSDLG_H_

#include "StdAfx.h"

class CWaitBurnCDDlg;

#define FASE_1  100
#define FASE_2  110
#define FASE_31 120 // tutto apposto //
#define FASE_32 130 // problemi o interruzione //

class CExportProgressDiscDlg : public CDialog
{

	DECLARE_DYNAMIC(CExportProgressDiscDlg)

public:

	CExportProgressDiscDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp, int iDiscType);
	~CExportProgressDiscDlg();

	enum { IDD = IDD_EXPORT_PROGRESS_CD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnInterrompi();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnBurnNotification(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserNotification(WPARAM wParam, LPARAM lParam);

	//

	void ImpostaFase(int nFase);

	CProgressCtrl m_ctrlProgress1;

	BOOL m_bInterrompi;
	CString m_strPath;

	CEsamiView* m_pEsamiView;

private:

	virtual BOOL ExportImmagini() = 0;

	//

	void MasterizzaSupporto();

	//

	CButtonLocalize m_ctrlBtnInterrompi;

	CListCtrl m_ctrlListEvents;

	CProgressCtrl m_ctrlProgress2;
	CProgressCtrl m_ctrlProgress3;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;

	//

	int m_iNumExp;
	int m_iDiscType;

	//

	CImageList* m_pImageList;
	CWaitBurnCDDlg* m_pWaitCDDlg;

};

#endif /*_EXPORTPROGRESSDLG_H_ */