#ifndef _PROTOCOLLIMODDLG_H_
	#define _PROTOCOLLIMODDLG_H_

#include "DLL_Imaging\h\AMListCtrl.h"

class CProtocolliModDlg : public CDialog
{
	DECLARE_DYNAMIC(CProtocolliModDlg)

public:

	CProtocolliModDlg(CWnd* pParent);
	virtual ~CProtocolliModDlg();

	enum { IDD = IDD_PROTOCOLLI_MOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtn01New();
	afx_msg void OnBnClickedBtn01Edt();
	afx_msg void OnBnClickedBtn01Del();
	afx_msg void OnBnClickedBtn02New();
	afx_msg void OnBnClickedBtn02Edt();
	afx_msg void OnBnClickedBtn02Del();
	afx_msg void OnBnClickedBtn03New();
	afx_msg void OnBnClickedBtn03Del();
	afx_msg void OnBnClickedBtnEsci();

	afx_msg void OnLvnItemchangedList01(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList02(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList03(NMHDR *pNMHDR, LRESULT *pResult);

	LRESULT OnList03SubitemChanged(WPARAM wParam, LPARAM lParam);

private:

	void RiempiList01(long lIDToSel);
	void RiempiList02(long lIDToSel);
	void RiempiList03();

	void CalcolaTempi();

	//

	CButtonLocalize m_ctrlBtn01New;
	CButtonLocalize m_ctrlBtn01Edt;
	CButtonLocalize m_ctrlBtn01Del;
	CButtonLocalize m_ctrlBtn02New;
	CButtonLocalize m_ctrlBtn02Edt;
	CButtonLocalize m_ctrlBtn02Del;
	CButtonLocalize m_ctrlBtn03New;
	CButtonLocalize m_ctrlBtn03Del;
	CButtonLocalize m_ctrlBtnEsci;

	CListCtrl m_ctrlList01;
	CListCtrl m_ctrlList02;
	CAMEditComboListCtrl m_ctrlList03;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;

	//

	long m_lIDProtocollo;

	int m_nColonnaTempo;
	int m_nColonnaSommaTempo;

};

#endif /* _PROTOCOLLIMODDLG_H_ */