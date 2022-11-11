#ifndef _FRASITREELISTBOX_H_
	#define _FRASITREELISTBOX_H_

#include "BaseTreeListBox.h"

class CFrasiTreeObject;

class CFrasiTreeListBox : public CBaseTreeListBox
{         
	DECLARE_DYNCREATE(CFrasiTreeListBox)

public:

	CFrasiTreeListBox();
	~CFrasiTreeListBox();

	CBitmap		bitmapArrayToShow;
	long		m_lFamily;

	void	SetFamily(long lFamily) { m_lFamily = lFamily; }
	CString GetCurDataDescr();
	CString GetCurDataTitle();
	int		GetCurDataFlag();

	virtual BOOL		PrepareDataToShow(CBaseTreeObject* pData);
	virtual BOOL		IsValidLevel(CBaseTreeObject* pData);
	virtual CString		GetLevelStr(CBaseTreeObject* pData);
	virtual CString		GetDescritionStr(CBaseTreeObject* pData);
	virtual CString		GetCurDataPathSel();

	virtual int	AddTreeItem(CFrasiTreeObject* pData);
	virtual int	InsTreeItem(int nIndex, CFrasiTreeObject* pData);
	virtual int	DelTreeItem(int nIndex);

protected:

	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};

#endif /* _FRASITREELISTBOX_H_ */