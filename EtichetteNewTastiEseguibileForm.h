#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewTastiEseguibileForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewTastiEseguibileForm(CWnd* pParent);
	~CEtichetteNewTastiEseguibileForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_TASTIESEGUIBILE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CString m_sTesto[NUM_LABEL_TESTO_PAGE];
	CString m_sTastoEseguibileFile[NUM_LABEL_TESTO_PAGE];

	CStaticLocalize m_ctrlStatic00;

};


