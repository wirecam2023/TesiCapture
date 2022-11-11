#ifndef _MEASUREMENTSMAPPINGDLG_H_
	#define _MEASUREMENTSMAPPINGDLG_H_

#include "MyListBox.h"

class CEsamiView;

class CMeasurementsMappingDlg : public CDialog
{	
	DECLARE_DYNAMIC(CMeasurementsMappingDlg)
public:
	
	CMeasurementsMappingDlg(CWnd* pParent);
	virtual ~CMeasurementsMappingDlg();

	enum { IDD = IDD_MEASUREMENTS_MAPPING_DLG };	

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog();
		
	afx_msg void OnBnClickedEdt();	
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedUndo();
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedDel();
	afx_msg void OnLbnSelchangeListaMedidas();
	afx_msg void OnCbnSelchangeComboType();

	DECLARE_MESSAGE_MAP()	

private:
	void RiempiLista();	
	void AggiornaCombo();
	
	CString m_sVariableName;
	CString m_sNomeParametro;
	CString m_sAlias;
	BOOL m_bAddNew;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonDelete;
	CComboBox m_ctrlComboType; //Gabriel - BUG 5533 V2
	CStaticLocalize m_ctrlStatic4; //Gabriel - BUG 5533 V2
	CStaticLocalize m_ctrlStatic5; //Gabriel - BUG 5533 V2
	CString m_sDecimals; //Gabriel - BUG 5533 V2

	CMyListBox m_ctrlListaVar;
public:
	afx_msg void OnBnClickedCancel();
};

#endif /* _MEASUREMENTSMAPPINGDLG_H_ */
