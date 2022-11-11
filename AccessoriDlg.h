#ifndef _ACCESSORIDLG_H_
	#define _ACCESSORIDLG_H_

#include "ExtListBox.h"

class CEsamiView;

class CAccessoriDlg : public CDialog
{

public:

	CAccessoriDlg(CEsamiView* pEsamiView, BOOL bMenu);
	virtual ~CAccessoriDlg();

	enum { IDD = IDD_ACCESSORI };

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

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonMod;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonUpd;
	CButtonLocalize m_ctrlButtonRefresh;
	CButtonLocalize m_ctrlButtonOK;

	CStaticLocalize m_ctrlStatic1;

};

#endif /* _ACCESSORIDLG_H_ */