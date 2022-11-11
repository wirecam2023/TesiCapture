#ifndef _STRUMENTIDLG_H_
	#define _STRUMENTIDLG_H_

class CStrumentiDlg : public CDialog
{

public:

	CStrumentiDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CStrumentiDlg(void);
	
	enum { IDD = IDD_STRUMENTI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnElimina();
	afx_msg void OnModifica();
	afx_msg void OnNuovo();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonModify;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonCancel;

private:

	void RiempiLista();

	CListBox m_ctrlListStrumenti;
	CEsamiView* m_pEsamiView;
};

#endif /* _STRUMENTIDLG_H_ */