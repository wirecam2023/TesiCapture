#ifndef _PROCEDUREICD9DLG_H_
	#define _PROCEDUREICD9DLG_H_

#include "ProcedureICD9Set.h"

#define CORE_VISUA 0
#define CORE_NUOVO 1
#define CORE_MODIF 2

class CProcedureICD9Dlg : public CDialog
{
	DECLARE_DYNAMIC(CProcedureICD9Dlg)

public:

	CProcedureICD9Dlg(CWnd* pParent);
	virtual ~CProcedureICD9Dlg();

	enum { IDD = IDD_PROCEDUREICD9 };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnDlt();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnPri();
	afx_msg void OnBnClickedBtnSav();
	afx_msg void OnBnClickedBtnUnd();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnSelchangeList00();
	DECLARE_MESSAGE_MAP()

private:
	void CambiaModalita(int iNuovaModalita);
	void SvuotaDialog();
	void VisualizzaDati();

	CListBox m_ctrlList00;
	CProcedureICD9Set m_setProcedureICD9;

	int m_iModalita;

	CStaticLocalize m_ctrlFrame00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;

	CButtonLocalize m_ctrlButtonOK; 
	CButtonLocalize m_ctrlButtonSav;
	CButtonLocalize m_ctrlButtonUnd;
	CButtonLocalize m_ctrlButtonPri;
	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDlt;

};

#endif /* _PROCEDUREICD9DLG_H_ */