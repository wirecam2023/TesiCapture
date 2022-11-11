#ifndef _CHECKLISTELMODDLG_H_
	#define _CHECKLISTELMODDLG_H_

#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "EditDynFormToolbar.h"
#include "QueryForm.h"

class CCheckListElModDlg : public CDialog
{

	DECLARE_DYNAMIC(CCheckListElModDlg)

public:

	CCheckListElModDlg(CWnd* pParent, long lIDCheckList, long lIDPadre, const CTreeCtrl* pTreeCtrl);	// costruttore per l'inserimento di un nuovo elemento //
	CCheckListElModDlg(CWnd* pParent, long lIDEl, const CTreeCtrl* pTreeCtrl);							// costruttore per la modifica di un elemento esistente //
	virtual ~CCheckListElModDlg();

	enum { IDD = IDD_CHECKLISTEL_MOD_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();

private:

	void CaricaDati();
	BOOL SalvaDati();

	void FillTree(int iIndex, HTREEITEM hItemParentSource = NULL, HTREEITEM hItemParent = NULL);

	void SetCheckTreeItem(int iIndex, const CList<long>* pItemSelected, HTREEITEM hItemParent = NULL);
	void GetCheckTreeItem(int iIndex, CList<long>* pItemSelected, HTREEITEM hItemParent = NULL);

	// --- //

	long m_lIDCheckList;
	long m_lIDPadre;
	long m_lIDEl;

	// --- //

	CButton m_ctrlCheck1;
	CButton m_ctrlCheck2;

	CTXButtonBar23Ex m_ctrlButtonBar;
	CEditDynFormToolbar m_ctrlToolbar;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CEdit m_ctrlEditTitolo;

	CQueryForm m_wndCampoSingolo;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic17;
	CStaticLocalize m_ctrlStatic18;
	CStaticLocalize m_ctrlStatic19;
	CStaticLocalize m_ctrlStatic20;

	CTreeCtrl m_ctrlTree[4];

	CTXTextControl23Ex m_ctrlTextControl;

	const CTreeCtrl* m_pCheckListTreeCtrl;

};

#endif /* _CHECKLISTELMODDLG_H_ */