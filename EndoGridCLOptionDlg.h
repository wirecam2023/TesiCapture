#pragma once

#include "EndoGridCLParameterSet.h"
#include "EndoGridMaskEdit.h"

class CEndoGridCLOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(CEndoGridCLOptionDlg)

public:
	CEndoGridCLOptionDlg(CEndoGridCLParameterSet* pUserField, CWnd* pParentWnd = NULL);   // standard constructor
	virtual ~CEndoGridCLOptionDlg();

	// Dialog Data
	enum { IDD = IDD_GRIDCL_FIELD_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRadio();
	afx_msg void OnButtonCombo();
	afx_msg void OnButtonComboMulti();
	afx_msg void OnButtonComboFixed();
	afx_msg void OnButtonAllarm();
	afx_msg void OnOK();
	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic1,
		m_ctrlStatic2,
		m_ctrlStatic3,
		m_ctrlStatic4;
	CButtonLocalize m_ctrlButton1,
		m_ctrlButton2,
		m_ctrlButton3,
		m_ctrlButton4,
		m_ctrlButton5,
		m_ctrlButton6,
		m_ctrlButton7,
		//m_ctrlButton8,
		m_ctrlButton9,
		m_ctrlButton10,
		m_ctrlButton11,
		//m_ctrlButton12,
		m_ctrlButton13,
		//m_ctrlButton14,
		m_ctrlButton15,
		//m_ctrlButton16,
		//m_ctrlButton17,
		m_ctrlButton18,
		m_ctrlButton19,
		m_ctrlButton20,
		m_ctrlButton21;

	CEndoGridInplaceMaskEdit m_ctrlDate;

	CEndoGridCLParameterSet* m_pUserField;

	float m_fDefaultReal;
	BOOL  m_bDefaultBool;
	BOOL m_bDefaultCheck;
	long  m_lDefaultInt;
	CString m_strDefaultCombo;
	CString m_strDefaultComboMulti;
	CString m_strDefaultDate;
	CString m_strDefaultString;
	CString m_strDefaultNotes;
	CString m_strDefaultComboFixed;
	CString m_strDefaultDateFree;

	BOOL m_bCheckDayList, m_bCheckDayListOriginal;

private:
	void UpdateDefaultFields();
};