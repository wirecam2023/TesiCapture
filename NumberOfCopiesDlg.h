#ifndef _NUMBEROFCOPIESDLG_H_
	#define _NUMBEROFCOPIESDLG_H_

class CNumberOfCopiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CNumberOfCopiesDlg)

public:

	CNumberOfCopiesDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CNumberOfCopiesDlg();

	enum { IDD = IDD_NUMBEROFCOPIES };

	int m_iCopies;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CStaticLocalize m_ctrlStaticLabel;
	CEdit m_ctrlEditCopies;
};

#endif /* _NUMBEROFCOPIESDLG_H_ */