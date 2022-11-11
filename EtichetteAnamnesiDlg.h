#ifndef _LABELANAMNESIDLG_H_
	#define _LABELANAMNESIDLG_H_

class CEtichetteAnamnesiDlg : public CDialog
{

public:

	CEtichetteAnamnesiDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_ETICHETTE_ANAMNESI };

	CString m_sAnamText[NUM_FIELD_ANAM];
	BOOL m_bAnamVisi[NUM_FIELD_ANAM];
	BOOL m_bAnamAuto[NUM_FIELD_ANAM];

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CStaticLocalize m_ctrlStatic15;
	CStaticLocalize m_ctrlStatic16;
	CStaticLocalize m_ctrlStatic17;
	CStaticLocalize m_ctrlStatic18;
	CStaticLocalize m_ctrlStatic19;
	CStaticLocalize m_ctrlStatic20;
	CStaticLocalize m_ctrlStatic21;
	CStaticLocalize m_ctrlStatic22;
	CStaticLocalize m_ctrlStatic23;
	CStaticLocalize m_ctrlStatic24;
	CStaticLocalize m_ctrlStatic25;

	CStaticLocalize m_ctrlStatic30;
	CStaticLocalize m_ctrlStatic31;
	CStaticLocalize m_ctrlStatic32;
	CStaticLocalize m_ctrlStatic33;
	CStaticLocalize m_ctrlStatic34;
	CStaticLocalize m_ctrlStatic35;
	CStaticLocalize m_ctrlStatic36;
	CStaticLocalize m_ctrlStatic37;
	CStaticLocalize m_ctrlStatic38;
	CStaticLocalize m_ctrlStatic39;
	CStaticLocalize m_ctrlStatic40;

	DECLARE_MESSAGE_MAP()
};

#endif /* _LABELANAMNESIDLG_H_ */