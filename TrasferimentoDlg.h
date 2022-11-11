#ifndef _TRASFERIMENTODLG_H_
	#define _TRASFERIMENTODLG_H_

class CTrasferimentoDlg : public CDialog
{

public:

	CTrasferimentoDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_TRASFERIMENTO };

	BOOL      m_bTrasferimentoParziale;
	long	  m_DataDa;
	long	  m_DataA;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2, m_ctrlStatic3;
	CButtonLocalize m_ctrlButton1, m_ctrlButtonOK, m_ctrlButtonCancel;
};

#endif /* _TRASFERIMENTODLG_H_ */