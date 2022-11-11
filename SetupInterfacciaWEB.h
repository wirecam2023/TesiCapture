#ifndef _SETUPINTERFACCIAWEB_H_
	#define _SETUPINTERFACCIAWEB_H_
#include "afxwin.h"

class CSetupInterfacciaWEB : public CDialog
{
	DECLARE_DYNAMIC(CSetupInterfacciaWEB)

public:

	CSetupInterfacciaWEB(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CSetupInterfacciaWEB();

	enum { IDD = IDD_SETUP_INTERFACCIA_WEB };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	CComboBox m_ctrlComboModalita;

private:

	CEsamiView* m_pEsamiView;
public:
	afx_msg void OnBnClickedBtnPercorso();
};

#endif /* _SETUPINTERFACCIAWEB_H_ */