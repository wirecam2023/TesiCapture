#ifndef _INTERVALLODATEDLG_H_
	#define _INTERVALLODATEDLG_H_

#include "MaskEdit.h"
#include "QueryUtility.h"

class CIntervalloDateDlg : public CDialog, public CQueryUtility
{

public:

	CIntervalloDateDlg(CWnd* pParent);

	enum { IDD = IDD_INTERVALLODATE };

	CString GetFilter();
	CString GetDataOraIniz();
	CString GetDataOraFine();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnCbnSelchangeComboData();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;
	CComboBox		m_ctrlComboData;
	CMaskEdit		m_ctrlDataFine;
	CMaskEdit		m_ctrlDataIniz;
	CMaskEdit		m_ctrlOraFine;
	CMaskEdit		m_ctrlOraIniz;
	CStaticLocalize m_ctrlStatic00; 
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;

private:

	CString m_strFilter;
	CString m_strDataOraIniz;
	CString m_strDataOraFine;

};

#endif /* _INTERVALLODATEDLG_H_ */