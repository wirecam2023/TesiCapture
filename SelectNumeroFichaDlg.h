#pragma once

class CSelectNumeroFichaDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectNumeroFichaDlg)

public:
	CSelectNumeroFichaDlg(CWnd* pParent, CString *sArray, long lArraySize);
	CSelectNumeroFichaDlg(CWnd* pParent, const CString &sTitle, CString *sArray, long lArraySize);
	~CSelectNumeroFichaDlg();

	enum { IDD = IDD_SELECT_ITEM_FICHA };

	CString m_sSelectedFicha;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	void OnOK();

	afx_msg void OnCbnSelchangeCombo1();

	DECLARE_MESSAGE_MAP()

private:
	long m_lArraySize;
	CString *m_sArray;
	CString m_sTitle;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOk;
	CComboBox m_ctrlCombo1;
};
