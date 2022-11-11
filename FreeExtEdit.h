#ifndef _FREEEXTEDIT_H_
	#define _FREEEXTEDIT_H_

#include "ExtEdit.h"

class CFreeExtEdit : public CExtEdit
{
	DECLARE_DYNCREATE (CFreeExtEdit)

public:

	CFreeExtEdit();
	virtual ~CFreeExtEdit();

protected:

	afx_msg void OnKillFocus(CWnd* pNewWnd);

	DECLARE_MESSAGE_MAP()

};

#endif /* _FREEEXTEDIT_H_ */