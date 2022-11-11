#ifndef _WAITDVDDLG_H_
	#define _WAITDVDDLG_H_

class CWaitDVDDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitDVDDlg)

public:

	CWaitDVDDlg(CString strExamLabel, CString strDiskLabel, CWnd* pParent = NULL);
	virtual ~CWaitDVDDlg();

	enum { IDD = IDD_WAIT_DVD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnEject();
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CString m_strLabelExam, m_strLabelDisk;

	CStaticLocalize m_ctrlStaticErr,
		            m_ctrlStaticLabel1,
					m_ctrlStaticLabel2;
	CButtonLocalize m_ctrlButtonEject,
		            m_ctrlButtonOK,
					m_ctrlButtonCancel;
};

#endif /* _WAITDVDDLG_H_ */