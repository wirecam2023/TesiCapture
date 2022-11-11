// ComboBoxExt.cpp : header file
// Marvel BUG 4094 - Combo Checklists filtradas deve ser vazio por default
//

#if !defined(AFX_COMBOBOXEXT)
#define AFX_COMBOBOXEXT

#include <afxtempl.h>

class CComboBoxExt : public CComboBox
{
// Construction
public:
	CComboBoxExt();
// Attributes
// Operations

// Implementation
public:
	virtual ~CComboBoxExt();

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint(); // Marvel BUG 4094 - Combo Checklists filtradas deve ser vazio por default
};

#endif // !defined(AFX_COMBOBOXEXT)
