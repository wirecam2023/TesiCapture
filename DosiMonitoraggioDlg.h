#ifndef _DOSIMONITORAGGIODLG_H_
	#define _DOSIMONITORAGGIODLG_H_

#include "ExtListBox.h"

class CEsamiView;

class CDosiMonitoraggioDlg : public CDialog
{

public:

	CDosiMonitoraggioDlg(CEsamiView* pEsamiView, BOOL bMenu);
	virtual ~CDosiMonitoraggioDlg();

	enum { IDD = IDD_DOSI_MONITORAGGIO};

	long		m_lID;
	CString		m_strDescrizione;

	CExtListBox		m_ctrlLista;

	CEsamiView*		m_pEsamiView; 

	int				m_lSavedPosition;
	BOOL			m_bAddNew;
	BOOL			m_bModify;

	int             m_nItemPressed;
	int             m_nItemCount;

	void RiempiLista();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDelete();
	afx_msg void OnModify();
	afx_msg void OnNew();
	afx_msg void OnRefresh();
	afx_msg void OnUpdate();
	afx_msg void OnLbnDblclkLista();
	afx_msg void OnSelchangeLista();
	DECLARE_MESSAGE_MAP()

private:

	BOOL m_bMenu;

	CStaticLocalize m_ctrlStatic1;
	CButtonLocalize m_ctrlButtonNew,
					m_ctrlButtonMod,
					m_ctrlButtonDel,
					m_ctrlButtonUpd,
					m_ctrlButtonRefresh,
					m_ctrlButtonOK;
};

#endif /* _RAODLG_H_ */