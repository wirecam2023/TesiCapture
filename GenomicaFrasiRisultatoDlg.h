#pragma once


// CGenomicaFrasiRisultatoDlg dialog

class CGenomicaFrasiRisultatoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaFrasiRisultatoDlg)

public:
	CGenomicaFrasiRisultatoDlg(CWnd* pParent);
	virtual ~CGenomicaFrasiRisultatoDlg();

// Dialog Data
	enum { IDD = IDD_GENOMICA_FRASIRISULTATO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();	
	afx_msg void OnCbnSelchange(); //Julio BUG 3791 - Melhoria frases resultado laudo genomica

	DECLARE_MESSAGE_MAP()

private:
	void CaricaDati();
	void RiempiCombos();

	void EditDialog(BOOL bEdit);

	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;	
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;
	CStaticLocalize m_ctrlStatic9;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStatic12; //Julio BUG 3791 - Melhoria frases resultado laudo genomica

	CComboBox m_ctrlComboTipoVariante; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	CComboBox m_ctrlComboPatogenicita; //Julio BUG 3791 - Melhoria frases resultado laudo genomica

	long m_lIDTipoVarianteSelected; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	long m_lIDPatogenicita; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
};

