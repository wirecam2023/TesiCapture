#ifndef _WORKLISTLAYOUTDLG_H_
	#define _WORKLISTLAYOUTDLG_H_

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

class m_pEsamiView;

class CWorklistLayoutDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorklistLayoutDlg)

public:

	CWorklistLayoutDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CWorklistLayoutDlg();

	enum { IDD = IDD_WORKLIST_LAYOUT };

	CEsamiView* m_pEsamiView;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()		

private:

	CStaticLocalize m_ctrlStaticOn, m_ctrlStaticOff;
	CAMEditComboListCtrl m_ctrlListOn;
	CListCtrlLocalize m_ctrlListOff;
	CButtonLocalize m_ctrlBtnOn, m_ctrlBtnOff, m_ctrlBtnSave, m_ctrlBtnAbort, m_ctrlBtnUp, m_ctrlBtnDown;

	void  RiempiListaOff();
	void  RiempiListaOn();

public:
	afx_msg void OnLvnItemchangedListOn(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListOff(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnOn();
	afx_msg void OnBnClickedBtnOff();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedOk();
};

#endif /* _WORKLISTLAYOUTDLG_H_ */