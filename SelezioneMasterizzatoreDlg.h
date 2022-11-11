#ifndef _SELEZIONEMASTERIZZATORE_H_
	#define _SELEZIONEMASTERIZZATORE_H_

class CSelezioneMasterizzatoreDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelezioneMasterizzatoreDlg)

public:

	CSelezioneMasterizzatoreDlg(CWnd* pParent, int iTipoMasterizzatore);
	virtual ~CSelezioneMasterizzatoreDlg();

	enum { IDD = IDD_SELEZIONE_MASTERIZZATORE };

	long GetDeviceID();

	virtual INT_PTR DoModal();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CComboBox m_ctrlComboMast;

	int m_iTipoMasterizzatore;
	long m_lDeviceID;
};

#endif /* _SELEZIONEMASTERIZZATORE_H_ */