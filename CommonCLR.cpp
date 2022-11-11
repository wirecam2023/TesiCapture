#include "stdafx.h"
#include "Endox.h"
#include "CommonCLR.h"

#using "System.dll"

using namespace System;
using namespace System::IO;
using namespace System::Security::Cryptography;
using namespace System::Runtime::InteropServices;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOL CCommonCLR::SaveHexToFile(LPCTSTR szHexa, LPCTSTR szPath)
{
	try
	{				
		String^ sHEX = gcnew String(szHexa);
		String^ sPath = gcnew String(szPath);

		long lSize = (sHEX->Length / 2 - 1);
		array<byte> ^pByteArray = gcnew array<byte>(lSize);
		
		int iPos = 2;
		while (iPos < sHEX->Length)
		{
			pByteArray[iPos / 2 - 1] = System::Byte::Parse(sHEX->Substring(iPos, 2), System::Globalization::NumberStyles::HexNumber);
			iPos += 2;
		}
		
		System::IO::File::WriteAllBytes(sPath, pByteArray);

		return TRUE;
	}
	catch (Exception^ ex)
	{
		AfxMessageBox(CString(ex->Message));		
		return FALSE;
	}
}

CString CCommonCLR::GetHASHFromFile(LPCTSTR szPath)
{
	try
	{
		CString sReturn = "";

		String^ sPath = gcnew String(szPath);		
		array<byte>^ pByteArray = System::IO::File::ReadAllBytes(sPath);

		System::Security::Cryptography::SHA256Managed^ SHA = gcnew System::Security::Cryptography::SHA256Managed();		
		sReturn = Convert::ToBase64String(SHA->ComputeHash(pByteArray));
		
		delete SHA;
		delete pByteArray;

		return sReturn;
	}
	catch (Exception^ ex)
	{
		AfxMessageBox(CString(ex->Message));
		return "";
	}
}

CString CCommonCLR::ForceGC()
{
	CString sMessageBefore = "";
	sMessageBefore.Format("Memory before = %li", System::GC::GetTotalMemory(false));
	
	System::GC::Collect();

	CString sMessageAfter = "";
	sMessageAfter.Format("Memory after = %li", System::GC::GetTotalMemory(true));

	return sMessageBefore + "\n\n" + sMessageAfter;
}

BOOL CCommonCLR::MoveFileSafe(LPCTSTR szCurLocation, LPCTSTR szNewLocation)
{
	String^ sCurLocation = gcnew String(szCurLocation);
	String^ sNewLocation = gcnew String(szNewLocation);

	try
	{
		{
			FileStream^ streamCur = File::Open(sCurLocation, FileMode::Open, FileAccess::Write, FileShare::ReadWrite);
			FileStream^ streamNew = File::Open(sNewLocation, FileMode::Create, FileAccess::Write, FileShare::ReadWrite);

			streamCur->CopyTo(streamNew);
			streamCur->Close();
			streamNew->Close();
		}
	}
	catch (Exception^ ee)
	{
		CString sMessage = "MoveFileSafe went wrong while moving:\n" + CString(ee->ToString());
		AfxMessageBox(sMessage);
		return FALSE;
	}

	try
	{
		File::Delete(sCurLocation);
		
		delete sCurLocation;
		delete sNewLocation;

		return TRUE;
	}
	catch (Exception^ ee)
	{
		CString sMessage = "MoveFileSafe went wrong while removing:\n" + CString(ee->ToString());
		AfxMessageBox(sMessage);
		return FALSE;
	}
	
}

BOOL CCommonCLR::DeleteFileSafe(LPCTSTR szFile)
{
	try
	{
		String^ sFile = gcnew String(szFile);
		File::Delete(sFile);
		delete sFile;

		return TRUE;
	}
	catch (Exception^ ee)
	{
		CString sMessage = "DeleteFileSafe went wrong:\n" + CString(ee->ToString());
		AfxMessageBox(sMessage);
		return FALSE;
	}
}
