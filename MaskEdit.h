#ifndef _MASKEDIT_H_
	#define _MASKEDIT_H_

#include "XTMaskEditTEndox.h"

class CMaskEdit : public CXTMaskEditTEndox<CEdit>
{
	DECLARE_DYNAMIC(CMaskEdit);

public:

	CMaskEdit();

protected:

	DECLARE_MESSAGE_MAP()
};

#endif /* _MASKEDIT_H_ */