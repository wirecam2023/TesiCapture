#ifndef _MESSAGEBOXTIMERDLG_H_
	#define _MESSAGEBOXTIMERDLG_H_
#include "afxwin.h"

class CMessageBoxTimerDlg : public CDialog
{
	DECLARE_DYNAMIC(CMessageBoxTimerDlg)

public:

	CMessageBoxTimerDlg(CWnd* pParent, CString sMainMessage, UINT uidTitleMessage, UINT uidBtnOKMessage, UINT uidBtnCancelMessage, long lTimerPartenza);
	virtual ~CMessageBoxTimerDlg();

	enum { IDD = IDD_MESSAGEBOX_TIMER };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:

	CButton m_ctrlBtnCancel;
	CButton m_ctrlBtnOK;

	CStatic m_ctrlStaticMainMessage;

	//

	CString m_sMainMessage;
	UINT m_uidTitleMessage;
	UINT m_uidBtnOKMessage;
	UINT m_uidBtnCancelMessage;
	long m_lTimerPartenza;

};

#endif /* _MESSAGEBOXTIMERDLG_H_ */