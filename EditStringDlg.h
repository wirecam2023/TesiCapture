#ifndef _EDITSTRINGDLG_H_
	#define _EDITSTRINGDLG_H_

#include "ImageSimple2Dlg.h"

class CEditStringDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditStringDlg)

public:

	CEditStringDlg(CWnd* pParent, const CString &strTitle, const CString &sValue);
	CEditStringDlg(CWnd* pParent, UINT idTitle, const CString &sValue);
	~CEditStringDlg();

	enum { IDD = IDD_EDITSTRING_DLG };

	CString GetValue();
	BOOL SetEsamiView(CEsamiView* pEsamiView); //Julio 15/08/2018 used for CImgSimpleDlg2

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditValue();

private:

	CString m_sTitle;
	CString m_sValue;

	int m_iTipoInput;

	BOOL m_bRangeMin;
	BOOL m_bRangeMax;

	long m_lRangeValMin;
	long m_lRangeValMax;

	double m_lfRangeValMin;
	double m_lfRangeValMax;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonImm;

	CEsamiView* m_pEsamiView; //Julio 15/08/2018 used for CImgSimpleDlg2

public:
	afx_msg void OnBnClickedBtnImm();
};

#endif /* _EDITSTRINGDLG_H_ */