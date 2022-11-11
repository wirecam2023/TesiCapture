#include "Common.h"

#ifndef _DATEDLG_H_
	#define _DATEDLG_H_

class CDateDlg : public CDialog
{

public:

	CDateDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_DATE };

	CComboBox	m_ctrlOperatore;
	CDateTimeCtrl	m_ctrlDate2;
	CDateTimeCtrl	m_ctrlDate1;

	CString m_strRicerca;
	CString	m_strRicercaView;
	int m_iRicercaOutputMode;

	void SetRicercaOutputMode(int nModalita);
	
protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnSelchangeCombotipo();
	afx_msg void OnDate1Change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDate2Change(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonCancel, m_ctrlButtonOK;
	CStaticLocalize m_ctrlStaticFrom, m_ctrlStaticOperator, m_ctrlStaticTo;

private:

	void SetDlgMember();
};

#endif /*_DATEDLG_H_ */