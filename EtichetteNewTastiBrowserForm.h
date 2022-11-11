#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewTastiBrowserForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewTastiBrowserForm(CWnd* pParent);
	~CEtichetteNewTastiBrowserForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_TASTIBROWSER };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CString m_sTesto[NUM_LABEL_TESTO_PAGE];
	CString m_sTastoBrowserIndirizzo[NUM_LABEL_TESTO_PAGE];

	CStaticLocalize m_ctrlStatic00;

};


