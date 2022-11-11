#pragma once

class CEndoGridCLItems : public CList<CXTPPropertyGridItem*>
{
public:
	CEndoGridCLItems()
	{
	}

	void Truncate()
	{
		CList<CXTPPropertyGridItem*>::RemoveAll();
	}

	void RemoveAll()
	{
		for (POSITION pos = GetHeadPosition(); pos;)
			GetNext(pos)->Remove();
		Truncate();
	}
};