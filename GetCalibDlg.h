#ifndef _GETCALIBDLG_H_
	#define _GETCALIBDLG_H_

class CGetCalibDlg : public CDialog
{

public:

	CGetCalibDlg(CWnd* pParent);

	enum { IDD = IDD_MISURA_RIF };

	float	m_userMis;
	float	m_scrMis;

protected:

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

private:

	CStaticLocalize m_ctrlStaticRealDistance;
	CStaticLocalize m_ctrlStaticMonitorDistance;
	CButtonLocalize m_ctrlOk;
	CButtonLocalize m_ctrlCancel; 

};

#endif /* _GETCALIBDLG_H_ */