#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewDateForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewDateForm(CWnd* pParent);
	~CEtichetteNewDateForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_DATE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio();

	DECLARE_MESSAGE_MAP()

private:
	CString m_sTesto[NUM_LABEL_DATAORA];
	BOOL m_bCopiaDate[NUM_LABEL_DATAORA];
	int m_iRadioDate[NUM_LABEL_DATAORA];

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;

};

