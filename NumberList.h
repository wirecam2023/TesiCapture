#pragma once

class CNumberList : protected CList<long>
{
public:
	CNumberList();
	~CNumberList();

	void SetString(const CString strNumbers);
	CString GetString();

	BOOL IsPresent(long lNumber);

	long GetAt(int iIndex);
	INT_PTR GetCount();

	void Add(long lNum);
	void Remove(long lNum);

	void Reset();
};