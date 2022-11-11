#ifndef _NUMEROCOPIESTAMPADLG_H_
	#define _NUMEROCOPIESTAMPADLG_H_

class CNumeroCopieStampaDlg : public CDialog
{
	DECLARE_DYNAMIC(CNumeroCopieStampaDlg)

public:

	CNumeroCopieStampaDlg(CWnd* pParent, CString sReportFile);
	virtual ~CNumeroCopieStampaDlg();

	enum { IDD = IDD_NUMERO_COPIE_STAMPA };

	long GetNumeroCopie();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CSpinButtonCtrl m_ctrlSpin;

	CStaticLocalize m_ctrlStaticLabel;

	//

	long m_lNumeroCopie;

	CString m_sReportFile;

};

#endif /* _NUMEROCOPIESTAMPADLG_H_ */