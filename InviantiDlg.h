#ifndef _INVIANTIDLG_H_
	#define _INVIANTIDLG_H_

#include "ExtListBox.h"

class CEsamiView;

class CInviantiDlg : public CDialog
{

public:

	CInviantiDlg(CEsamiView* pEsamiView, BOOL bInterni, BOOL bMenu);
	virtual ~CInviantiDlg();

	enum { IDD = IDD_INVIANTI };

	long m_lCode;

	CString m_strRicerca;
	CString m_strRicercaView;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBtnOr();
	afx_msg void OnDelete();
	afx_msg void OnLbnDblclkLista();
	afx_msg void OnModify();
	afx_msg void OnNew();
	afx_msg void OnRefresh();
	afx_msg void OnSelchangeLista();
	afx_msg void OnUpdate();

private: 

	void RiempiListaMedici();
	void RiempiListaCentriDiCosto();

	//

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonMod;
	CButtonLocalize m_ctrlButtonCanc;
	CButtonLocalize m_ctrlButtonUpd;
	CButtonLocalize m_ctrlButtonRefresh;
	CButtonLocalize m_ctrlButtonOK;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;

	BOOL m_bInterni;
	BOOL m_bMenu;
	CComboBox m_ctrlCentriDiCosto;

	CString m_strDescr;
	CString m_strFax;
	CString m_strPhone;
	CString m_strCodiceIntegrazione;

	CExtListBox m_ctrlLista;

	CEsamiView* m_pEsamiView;

	int m_lSavedPosition;
	BOOL m_bAddNew;
	BOOL m_bModify;

	BOOL m_bRicercaAttivata;
	BOOL m_bOrPressed;

	int m_nItemCount;
	int m_nItemPressed;

};

#endif /* _INVIANTIDLG_H_ */