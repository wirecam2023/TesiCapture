#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewChecklistForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewChecklistForm(CWnd* pParent);
	~CEtichetteNewChecklistForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_CHECKLIST };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio();

	DECLARE_MESSAGE_MAP()

private:
	CString m_sTesto[NUM_LABEL_TESTO_PAGE];
	BOOL m_bCopia[NUM_LABEL_TESTO_PAGE];
	BOOL m_bAlarmCL[NUM_LABEL_TESTO_PAGE];
	CString m_sParoleChiaveCL[NUM_LABEL_TESTO_PAGE];

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;	

public:
	afx_msg void OnBnClickedAlarm();
};

