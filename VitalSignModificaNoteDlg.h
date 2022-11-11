#pragma once

#include "EndoxResizableDlg.h"

class CVitalSignModificaNoteDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CVitalSignModificaNoteDlg)

public:

	CVitalSignModificaNoteDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, long lIDHeaderMisurazioni);
	virtual ~CVitalSignModificaNoteDlg();

	enum { IDD = IDD_VS_MODIFICANOTE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnCancel;

	CEdit m_ctrlEdtNote;

	long m_lIDHeaderMisurazioni;
	CEsamiView* m_pEsamiView;

	//

};
