#ifndef _RAODLG_H_
	#define _RAODLG_H_

#include "ExtListBox.h"

class CEsamiView;
class CComboRAOSet;

class CRAODlg : public CDialog
{

public:

	CRAODlg(CWnd* pParentWnd);
	virtual ~CRAODlg();

	enum { IDD = IDD_RAO };

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

	void RiempiListaRAO();

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonOK;

	CEdit			m_ctrlEditDescrizione;
	CEdit			m_ctrlEditCodiceIntegrazione;

	CExtListBox		m_ctrlLista;

	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2;

	BOOL m_bAddNew;
	BOOL m_bModify;

};

#endif /* _RAODLG_H_ */