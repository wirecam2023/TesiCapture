#ifndef _BASETREELISTBOX_H_
	#define _BASETREELISTBOX_H_

class CBaseTreeObject;

class CBaseTreeListBox : public CListBox
{         
   DECLARE_DYNAMIC (CBaseTreeListBox)

public:

	CBaseTreeListBox();
	virtual ~CBaseTreeListBox();

	CBitmap		bitmapArrayToShow;
	CString		m_strSeparatorDesc;
	CString		m_strSeparatorCode;
	int			m_nHScrollWidth;

	CString		GetSeparatorDesc()	{ return m_strSeparatorDesc; }
	CString		GetSeparatorCode()	{ return m_strSeparatorCode; }

	virtual BOOL		PrepareDataToShow(CBaseTreeObject* pData) = 0;
	virtual BOOL		IsValidLevel	 (CBaseTreeObject* pData) = 0;
	virtual CString		GetLevelStr		 (CBaseTreeObject* pData) = 0;
	virtual	CString		GetDescritionStr (CBaseTreeObject* pData) = 0;
	virtual CString		GetCurDataPathSel(BOOL bCumulate);
	virtual CString		GetCurDesPathSel (BOOL bCumulate);

	int					SetTreeItemDataPtr(int nIndex, CBaseTreeObject* pDataStruct);
	CBaseTreeObject*	GetTreeItemDataPtr(int nIndex);

	virtual int			AddTreeItem(CBaseTreeObject* pData);
	virtual int			InsTreeItem(int nIndex, CBaseTreeObject* pData);
	virtual int			DelTreeItem(int nIndex) = 0;
	void				AdjustHScrollBar();

protected:

	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

public:

	virtual	void	MeasureItem(LPMEASUREITEMSTRUCT lpMeasure);
	virtual	void	DrawItem(LPDRAWITEMSTRUCT lpDraw);
};

#endif /* _BASETREELISTBOX_H_ */