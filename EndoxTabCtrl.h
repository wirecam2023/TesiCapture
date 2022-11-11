#ifndef _ENDOXTABCTRL_H_
	#define _ENDOXTABCTRL_H_

#include "BaseForm.h"

class CEndoxTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CEndoxTabCtrl)

public:

	CEndoxTabCtrl();
	virtual ~CEndoxTabCtrl();

	BOOL DeleteAllItems();
	CBaseForm* GetSelectedBaseForm();
	LONG InsertItem(LPCTSTR lpszNome, long lIDForm, long lShowAlbum);
	void MostraSubform();

	CEsamiView* m_pEsamiView;

protected:

	afx_msg void OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:

	CList <CBaseForm*> m_listForms;
	int m_iSelected;

	// li metto privati apposta perchè voglio essere sicuro che non vengano utilizzati in quanto non ridefiniti --> //
    BOOL DeleteItem(int nItem);
	LONG InsertItem(int nItem, TCITEM* pTabCtrlItem);
	LONG InsertItem(int nItem, LPCTSTR lpszItem);
	LONG InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	LONG InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, int nImage, LPARAM lParam);
	LONG InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, int nImage, LPARAM lParam, DWORD dwState, DWORD dwStateMask);
	// <-- li metto privati apposta perchè voglio essere sicuro che non vengano utilizzati in quanto non ridefiniti //
};

#endif /* _ENDOXTABCTRL_H_ */