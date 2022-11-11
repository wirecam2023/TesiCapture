#pragma once


// CEditMeasurementDlg dialog

class CEditMeasurementDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditMeasurementDlg)

public:
	CEditMeasurementDlg(CWnd* pParent, long lID, BOOL bAddNew = FALSE);   // standard constructor
	virtual ~CEditMeasurementDlg();

// Dialog Data
	enum { IDD = IDD_EDITMEASUREMENT_DLG };

	long m_lID;
	CString m_sAlias;
	CString m_sNumeric;
	CString m_sCode;
	CComboBox m_ctrlComboNomeParametro;

	BOOL m_bAddNew;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnInitDialog();
	
	void RiempiCombo();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditValue();
	afx_msg void OnCbnSelchangeComboNomeparametro();
};
