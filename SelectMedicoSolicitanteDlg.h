//GABRIEL - P3 - BUG 3812
#pragma once

class CSelectMedicoSolicitanteDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectMedicoSolicitanteDlg)

public:
	CSelectMedicoSolicitanteDlg(CWnd* pParent, CString *sArray, long lArraySize);
	CSelectMedicoSolicitanteDlg(CWnd* pParent, const CString &sTitle, CString *sArray, long lArraySize);
	~CSelectMedicoSolicitanteDlg();

	enum { IDD = IDD_SELECT_MEDICOSOLICITANTE };

	CString m_sSelectedMedico;

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
