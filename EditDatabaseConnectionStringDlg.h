#ifndef _EDITDATABASECONNECTIONSTRINGDLG_H_
	#define _EDITDATABASECONNECTIONSTRINGDLG_H_

class CEditDatabaseConnectionStringDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditDatabaseConnectionStringDlg)

public:

	CEditDatabaseConnectionStringDlg(CWnd* pParent, BOOL bIsOracle, long lID);
	~CEditDatabaseConnectionStringDlg();

	enum { IDD = IDD_EDITDATABASECONNECTIONSTRING };

	// da usare SOLO DOPO aver chiamato il dialogo per l'inserimento di una NUOVA stringa di connessione //
	long GetLastAdd();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnTest();

	afx_msg void OnEnChangeEditDescrizione();
	afx_msg void OnEnChangeEdit01();
	afx_msg void OnEnChangeEdit02();
	afx_msg void OnEnChangeEdit03();
	afx_msg void OnEnChangeEdit04();

private:

	void AggiornaTastoOK();

	//

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlBtnTest;

	CEdit m_ctrlEditDescrizione;
	CEdit m_ctrlEdit00DBEngine;
	CEdit m_ctrlEdit01Driver;
	CEdit m_ctrlEdit02ServerDBQ;
	CEdit m_ctrlEdit03Username;
	CEdit m_ctrlEdit04Password;
	
	CStaticLocalize m_ctrlStaticDescrizione;
	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;

	//

	BOOL m_bIsOracle;
	long m_lID;

};

#endif /* _EDITDATABASECONNECTIONSTRINGDLG_H_ */