#ifndef _MODCODICICLASSIFDIAGDLG_H_
	#define _MODCODICICLASSIFDIAGDLG_H_

class CModCodiciClassifDiagDlg : public CDialog
{
	DECLARE_DYNAMIC(CModCodiciClassifDiagDlg)

public:

	CModCodiciClassifDiagDlg(CWnd* pParent);
	virtual ~CModCodiciClassifDiagDlg();

	enum { IDD = IDD_MODCODICICLASSIFDIAG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();

	DECLARE_MESSAGE_MAP()

private:

	void CaricaDati();
	void EditDialog(BOOL bEdit);
	void RiempiCombos();
	void RiempiLista();
	void UnselectAll();

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonPositivita;

	CComboBox m_ctrlComboClassificazione;
	CComboBox m_ctrlComboTipoEsame;

	CListCtrl m_ctrlList;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;

	long m_lID;
	float m_fScore;

};

#endif /* _MODCODICICLASSIFDIAGDLG_H_ */