#ifndef _PRONTFARMMODDLG_H_
	#define _PRONTFARMMODDLG_H_

#include "afxwin.h"
#include "afxcmn.h"

class CProntFarmModDlg : public CDialog
{
	DECLARE_DYNAMIC(CProntFarmModDlg)

public:

	CProntFarmModDlg(CWnd* pParent);
	virtual ~CProntFarmModDlg();

	enum { IDD = IDD_PRONTFARMMOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnLbnSelchangeList00();

	DECLARE_MESSAGE_MAP()

private:

	CListBox m_ctrlList00;
	CListCtrlLocalize m_ctrlList02;

	CButtonLocalize m_ctrlBtnOK;

	CStaticLocalize m_ctrlStatic08;
	CStaticLocalize m_ctrlStatic09;

};

#endif /* _PRONTFARMMODDLG_H_ */