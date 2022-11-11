#pragma once

struct tagOBBLIGATORYFIELD_ERROR
{
	long lFieldID;
	TCHAR szFieldName[255];
};

class CObbligatoryFieldErrorList : public CList<tagOBBLIGATORYFIELD_ERROR>
{
public:
	CObbligatoryFieldErrorList(void);
	~CObbligatoryFieldErrorList(void);

	CString GetDescription();

	void Add(long lFieldID, LPCTSTR szFieldName);
};
