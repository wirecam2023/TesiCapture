#ifndef _FRASIRTFDLG_H_
	#define _FRASIRTFDLG_H_

#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "EditDynFormToolbar.h"
#include "Common.h"

class CFrasiRtfDlg : public CDialog
{
	DECLARE_DYNAMIC(CFrasiRtfDlg)

public:

	CFrasiRtfDlg(CWnd* pParent);
	~CFrasiRtfDlg();

	enum { IDD = IDD_FRASI_RTF };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnChiudi();

	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();

	afx_msg void OnEnChangeEditRtfCodiceFrase();

	afx_msg void OnLvnItemchangedListFrasiRtf(NMHDR *pNMHDR, LRESULT *pResult);

private:

	CButtonLocalize m_ctrlBtnChiudi;
	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnUndo;

	CEdit m_ctrlEditCodice;
	CEdit m_ctrlEditRtfCodice;
	CEdit m_ctrlEditRtfFrase;

	CEditDynFormToolbar m_ctrlToolbar;

	CListCtrl m_ctrlListFrasiRTF;

	CStaticLocalize m_ctrlStaticCodice;

	//

	CTXButtonBar23Ex m_ctrlButtonBar;
	CTXTextControl23Ex m_ctrlTextControl;

	void SetEditState(BOOL bEditable);
	void cleanEditToStart();											// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	void updateEditableFields(CString p_sCodice, CString p_sTestoRTF);	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	BOOL m_bProcessOnEnChange;											// Marvel Carvalho - Bug 3457 (FIX) TEXTER

public:
	afx_msg void OnEnSetfocusEditRtfCodice();	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	afx_msg void OnEnSetfocusEditRtfFrase();	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
};

#endif /* _FRASIRTFDLG_H_ */