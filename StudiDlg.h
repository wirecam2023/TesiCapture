#ifndef _STUDIDLG_H_
	#define _STUDIDLG_H_

#include "ExtListBox.h"

class CEsamiView;

class CStudiDlg : public CDialog
{

public:

	CStudiDlg(CWnd* pParentWnd);
	virtual ~CStudiDlg();

	enum { IDD = IDD_STUDI };

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
	afx_msg void OnSelchangeLista();

private:

	void RiempiListaStudi();

	//

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonOK;

	CEdit m_ctrlEditDescrizione;

	CExtListBox m_ctrlLista;

	CStaticLocalize m_ctrlStatic1;

	//

	BOOL m_bAddNew;
	BOOL m_bModify;

};

#endif /* _STUDIDLG_H_ */