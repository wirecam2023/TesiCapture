#ifndef _GRUPPIPROCEDUREICD9MODDLG_H_
	#define _GRUPPIPROCEDUREICD9MODDLG_H_
#include "afxwin.h"

#include "MyListBox.h"

class m_pEsamiView;

class CGruppiProcedureICD9ModDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiProcedureICD9ModDlg)

public:

	CGruppiProcedureICD9ModDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CGruppiProcedureICD9ModDlg();

	enum { IDD = IDD_GRUPPIPROCEDUREICD9_MOD_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedEdt();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedUndo();
	afx_msg void OnLbnSelchangeListaGruppi();

	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;

private:

	void RiempiListaGruppi();
	void RiempiListaProcedure();
	void SalvaProcedureICD9(long lContatoreEsame);
	void SelezionaProcedureICD9(long lContatoreEsame);

	CEsamiView* m_pEsamiView;

	CMyListBox m_ctrlListaGruppi;
	CMyListBox m_ctrlListaProcedure;

	CString m_sDescrizione;
	BOOL m_bAddNew;
	BOOL m_bModify;

};

#endif /* _GRUPPIPROCEDUREICD9MODDLG_H_ */