#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewTastiChiusuraFaseForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewTastiChiusuraFaseForm(CWnd* pParent);
	~CEtichetteNewTastiChiusuraFaseForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_TASTICHIUSURAFASE };	

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:	

	CString m_sTesto[NUM_LABEL_TESTO_PAGE];
	long m_lSelectedIndex[NUM_LABEL_TESTO_PAGE];
	
	CStaticLocalize m_ctrlStatic01;

};

