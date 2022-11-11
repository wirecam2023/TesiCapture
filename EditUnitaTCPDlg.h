#pragma once
#ifndef _EDITUNITATCPDLG_H_
#define _EDITUNITATCPDLG_H_

class CEditUnitaTCPDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditUnitaTCPDlg)

public:

	CEditUnitaTCPDlg(CWnd* pParent, BOOL bIsOracle, long lID);
	~CEditUnitaTCPDlg();

	enum { IDD = IDD_EDITUNITATCP };

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

	afx_msg void OnEnChangeEditDescrizione();
	afx_msg void OnEnChangeEdit00();
	afx_msg void OnEnChangeEdit01();

private:

	void AggiornaTastoOK();

	//

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;

	CEdit m_ctrlEditDescrizione;
	CEdit m_ctrlEdit00Unita;
	CEdit m_ctrlEdit01Endpoint;

	CStaticLocalize m_ctrlStaticDescrizione;
	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;

	//

	BOOL m_bIsOracle;
	long m_lID;

};

#endif /* _EDITUNITATCPDLG_H_ */