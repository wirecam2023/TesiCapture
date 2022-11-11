#ifndef _QUERYONLYPATIENSDLG_H_
	#define _QUERYONLYPATIENSDLG_H_

class CQueryOnlyPatiensDlg : public CDialog
{

	DECLARE_DYNAMIC(CQueryOnlyPatiensDlg)

public:

	CQueryOnlyPatiensDlg(CWnd* pParent);
	virtual ~CQueryOnlyPatiensDlg();

	enum { IDD = IDD_QUERY_ONLYPATIENS };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK() { }

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnClassic();
	afx_msg void OnBnClickedBtnOnlyPatiens();

};

#endif /* _QUERYONLYPATIENSDLG_H_ */