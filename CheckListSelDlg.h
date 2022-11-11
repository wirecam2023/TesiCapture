#ifndef _CHECKLISTSELDLG_H_
	#define _CHECKLISTSELDLG_H_

#include "Common.h"

class CCheckListSelDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckListSelDlg)

public:

	CCheckListSelDlg(CWnd* pParent, CList<STRUCT_CHECKLIST>* pListChecklist);
	virtual ~CCheckListSelDlg();

	enum { IDD = IDD_CHECKLIST_SEL_DLG };

	long GetIDCheckList();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista();

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CListCtrlLocalize m_ctrlList;

	CList<STRUCT_CHECKLIST>* m_pListChecklist;
	long m_lIDCheckList;

};

#endif /* _CHECKLISTSELDLG_H_ */