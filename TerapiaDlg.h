#ifndef _TERAPIADLG_H_
	#define _TERAPIADLG_H_

#include "ExtListcombo.h"

class CTerapiaDlg : public CDialog
{

public:

	CTerapiaDlg ( CWnd* pParent, CBaseSet* pSet, CString* pStrParent, CString strInit);
	virtual ~CTerapiaDlg(void);

	enum { IDD = IDD_TERAPIA };

	CExtListCombo	m_ctrLista[3];
	CBaseSet* 		m_pSet;
	CString*		m_pStrOutput;

	BOOL 	SelectLista();

protected:

	BOOL m_bRicercaAttivata;
	BOOL m_bOrPressed;
	
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnReset();
	afx_msg void OnBtnOr();
	afx_msg void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonReset, m_ctrlButtonAdd, m_ctrlButtonOK;
};

#endif /* _TERAPIADLG_H_ */