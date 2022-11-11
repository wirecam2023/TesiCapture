#include "stdafx.h"
#include "Endox.h"
#include <iostream>
using namespace std;
#include "afxdb.h"
#include "odbcinst.h"


class NeoConnection
{
	public:
		 NeoConnection();
		 CString ConnectionString;
		 
		 void ConnectionDatabase();
		 void Select(CString query,CRecordset& rs);
	private:

};



