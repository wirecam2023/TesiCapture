#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewTastiStampaForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewTastiStampaForm(CWnd* pParent);
	~CEtichetteNewTastiStampaForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_TASTISTAMPA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio();

	DECLARE_MESSAGE_MAP()

private:
	CString m_sTesto[NUM_LABEL_TESTO_PAGE];
	CString m_sTastoStampaFile[NUM_LABEL_TESTO_PAGE];
	BOOL m_bTastoStampaCheck[NUM_LABEL_TESTO_PAGE];

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;

};

