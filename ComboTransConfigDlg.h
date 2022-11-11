#ifndef _COMBOTRANSCONFIGDLG_H_
	#define _COMBOTRANSCONFIGDLG_H_

#include "ExtListBox.h"
#include "ComboTransSet.h"

class CComboTransConfigDlg : public CDialog
{

public:

	CComboTransConfigDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CComboTransSet *set, CString sTitolo);
	virtual ~CComboTransConfigDlg();

	CString m_strRicerca;
	CString m_strRicercaView;

	enum { IDD = IDD_COMBOTRANSDLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBtnNew();
	afx_msg void OnBtnEdt();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnUndo();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista();

	CEsamiView* m_pEsamiView; 

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonOK;

	CEdit			m_ctrlEditDescrizione;
	CEdit			m_ctrlEditExtCode;
	long			m_lIdCurSel;
	CString			m_sTitolo;

	CListCtrl		m_ctrlLista;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

	CComboTransSet* m_pComboTransSet;

	BOOL m_bAddNew;
	BOOL m_bModify;

};

#endif /* _COMBOTRANSCONFIGDLG_H_ */