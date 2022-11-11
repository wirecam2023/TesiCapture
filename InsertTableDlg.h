#ifndef _INSERTTABLEDLG_H_
	#define _INSERTTABLEDLG_H_

#include "resource.h"

class CInsertTableDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertTableDlg)

public:

	CInsertTableDlg(CWnd* pParent);
	virtual ~CInsertTableDlg();

	enum { IDD = IDD_INSERT_TABLE };

	short GetRows();
	short GetCols();
	short GetBordi();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDeltaposSpinBordi(NMHDR *pNMHDR, LRESULT *pResult);

private:

	short m_shRows;
	short m_shCols;
	short m_shBordi;

	//

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CSpinButtonCtrl m_ctrlSpinRows;
	CSpinButtonCtrl m_ctrlSpinCols;
	CSpinButtonCtrl m_ctrlSpinBordi;

	CStaticLocalize m_ctrlStaticRows;
	CStaticLocalize m_ctrlStaticCols;
	CStaticLocalize m_ctrlStaticBordi;

};

#endif /* _INSERTTABLEDLG_H_ */