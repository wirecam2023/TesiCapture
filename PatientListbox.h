#ifndef _PATIENTLISTBOX_H_
	#define _PATIENTLISTBOX_H_

typedef struct _LISTBOX_COLOR_
{
	TCHAR strText[MAX_PATH]; // text content, default value is ""
	COLORREF fgColor; // foreground color, default color is black
	COLORREF bgColor; // background color, default color is white
	DWORD iValue;

	_LISTBOX_COLOR_() // constructor
	{
		ZeroMemory(strText, sizeof(TCHAR) * MAX_PATH);
		fgColor = RGB_BLACK;
		bgColor = RGB_WHITE;
		iValue = 0;
	}

} LISTBOX_COLOR, *PLISTBOX_COLOR;

class CPatientListBox : public CListBox
{
	DECLARE_DYNAMIC(CPatientListBox)

public:

	CPatientListBox();
	virtual ~CPatientListBox();	

	int AddString(LPCTSTR lpszItem);
	int AddString(LPCTSTR lpszItem, COLORREF fgColor, COLORREF bgColor);
	int DeleteString(UINT nIndex);
	int InsertString(int nIndex, LPCTSTR lpszItem);
	int InsertString(int nIndex, LPCTSTR lpszItem, COLORREF fgColor, COLORREF bgColor);

	int SetItemData(int index, DWORD value);
	DWORD GetItemData(int index);
	void GetText(int index, CString &value);

protected:	

	DECLARE_MESSAGE_MAP()		

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	afx_msg void OnDestroy();

};

#endif /* _PATIENTLISTBOX_H_ */