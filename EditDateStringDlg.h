#ifndef _EDITDATESTRINGDLG_H_
	#define _EDITDATESTRINGDLG_H_

#include "MaskEdit.h"

class CEditDateStringDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditDateStringDlg)

public:

	CEditDateStringDlg(CWnd* pParent, const CString &strTitle, const CString &sData, const CString &sDescrizione);
	CEditDateStringDlg(CWnd* pParent, UINT idTitle, const CString &sData, const CString &sDescrizione);
	~CEditDateStringDlg();

	enum { IDD = IDD_EDITDATESTRING_DLG };

	CString GetData();
	CString GetDescrizione();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();

private:

	CString m_sWindowTitle;
	CString m_sData;
	CString m_sDescrizione;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CMaskEdit m_ctrlEditData;
	CEdit m_ctrlEditDescrizione;

	CStaticLocalize m_ctrlStaticData;
	CStaticLocalize m_ctrlStaticDescrizione;

};

#endif /* _EDITDATESTRINGDLG_H_ */