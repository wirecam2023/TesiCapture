#ifndef _QUERYCOUNTDLG_H_
	#define _QUERYCOUNTDLG_H_

class CQueryCountDlg : public CDialog
{

	DECLARE_DYNAMIC(CQueryCountDlg)

public:

	CQueryCountDlg(CWnd* pParent);
	virtual ~CQueryCountDlg();

	enum { IDD = IDD_QUERY_COUNT };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK() { }

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnClassic();
	afx_msg void OnBnClickedBtnCount();

};

#endif /* _QUERYCOUNTDLG_H_ */