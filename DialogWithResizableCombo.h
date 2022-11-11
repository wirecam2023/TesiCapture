#pragma once

// Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
// Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres

#include "ImageSimple2Dlg.h" // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO

class CDialogWithResizableCombo : public CDialog
{
	DECLARE_DYNAMIC(CDialogWithResizableCombo)

public:		
	CDialogWithResizableCombo(CWnd* pParent, const CString &sTitle, CString *sArray, long lArraySize, long lRectSize, BOOL p_bAddImgButton=FALSE);
	CDialogWithResizableCombo();
	~CDialogWithResizableCombo();


	CString m_sSelectedItem;


	long GetRectSize(CString sTesto);
	BOOL SetEsamiView(CEsamiView* pEsamiView); // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO

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
	CString m_sValue; // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOk;
	CButtonLocalize m_ctrlButtonImm; // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO

	CComboBox m_ctrlCombo1;
	CEsamiView* m_pEsamiView; // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
	BOOL m_bShowImgButton = FALSE; // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
	long m_lRectSize;

public:
	afx_msg void OnBnClickedBtnImm();
};
