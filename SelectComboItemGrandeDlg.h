#pragma once
//Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres

class CSelectComboItemGrandeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectComboItemGrandeDlg)	

public:		
	CSelectComboItemGrandeDlg(CWnd* pParent, const CString &sTitle, CString *sArray, long lArraySize, long lRectSize);
	CSelectComboItemGrandeDlg();
	~CSelectComboItemGrandeDlg();
	

	CString m_sSelectedItem;
	

	long GetRectSize(CString sTesto);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();
	void OnOK();

	afx_msg void OnCbnSelchangeCombo1();

	DECLARE_MESSAGE_MAP()	

	static const UINT m_uiIDD[5];
private:
	
	long m_lArraySize;
	CString *m_sArray;
	CString m_sTitle;	

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOk;
	CComboBox m_ctrlCombo1;
};
