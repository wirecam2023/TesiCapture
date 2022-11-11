#ifndef _QUERYFORMLISTDLG_H_
	#define _QUERYFORMLISTDLG_H_

#include "EndoxResizableDlg.h"

class CQueryFormListDlg : public CEndoxResizableDlg
{

	DECLARE_DYNAMIC(CQueryFormListDlg)

public:

	struct tagITEM
	{
		tagITEM()
		{
			ZeroMemory(this, sizeof(tagITEM));
		}

		long lContatore;
		char szCodice[1024];
		char szDescrizione[1024];
		BOOL bLibero;
	};

	CQueryFormListDlg(CWnd* pParent, CPoint ptLocation, CList<tagITEM>* pListItems, long lSelectedID, BOOL bCanImportAll);
	virtual ~CQueryFormListDlg();

	enum { IDD = IDD_QUERY_FORM_LIST_DLG };

	tagITEM GetItemSelected();
	void GetItemsSelected(CList<tagITEM>* pList);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	void FillList();
	void ResizeColumns();

	//

	CListCtrlLocalize m_ctrlList;

	CList<tagITEM> m_listItems;

	tagITEM m_ItemSelected;
	CList<tagITEM> m_listSelected;

	//

	CPoint m_ptLocation;
	long m_lSelectedID;
	BOOL m_bCanImportAll;

};

#endif /*_QUERYFORMLISTDLG_H_ */