#include "stdafx.h"
#include "NeoConnection.h"
#include "odbcinst.h"
#include <iostream>
#include "afxdb.h"
#include "afxwin.h"
#include <string.h>

using namespace std;


	CString ConnectString;
	CDatabase dbConn;

	NeoConnection::NeoConnection()
	{

	}

    void NeoConnection::ConnectionDatabase() 
	{
		try
		{
			CString str = theApp.m_dbEndox.GetDecryptedConnectionString();
			str = str.Right(str.GetLength() - str.Find(_T(';')));
			dbConn.OpenEx(str);
		}
		catch (CDBException* e)
		{
			AfxMessageBox(L"Database error: " + e->m_strError);
		}

	}

	void NeoConnection::Select(CString query, CRecordset& rs)
	{
		rs.m_pDatabase = &dbConn;

		rs.Open(CRecordset::forwardOnly, query);
		
	}

	


