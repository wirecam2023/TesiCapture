#pragma once

#include "Common.h"
#include "msxml6.tlh"

class CEsamiView;

class CVitalSignManager
{
public:

	struct Measurament
	{
		long lId;
		TCHAR sId[MAX_PATH];
		TCHAR sNotes[4000];
	};
		
	CVitalSignManager(CEsamiView *pEsamiView);
	~CVitalSignManager();

	BOOL Go(CString sInput, CString* sOutput);

	BOOL StartSession(int idDispositivo, CString *pIdSessione, MonitoringPhase fase);
	BOOL StopSession(CString pIdSessione);
	BOOL ChangeNotes(CString idSessione, CString note, CList<Measurament>* measuraments);

	BOOL ChangeNotesAndWait(CString sIdSessione, long lIDHeader, long lOldIdPdf, CString sOldNotes, CList<Measurament>* oldChangedMeasuraments, CString sNote, CList<Measurament>* changedMeasuraments);

private:
	CEsamiView *m_pEsamiView;

	MSXML2::IXMLDOMDocument3Ptr m_pxmlDocument;
};

