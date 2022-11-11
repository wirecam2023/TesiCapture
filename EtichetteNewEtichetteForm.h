#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewEtichetteForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewEtichetteForm(CWnd* pParent, int iIndex);
	~CEtichetteNewEtichetteForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_ETICHETTE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CString m_sTesto[NUM_LABEL_TESTO_PAGE];		

	int m_iIndex;
};

