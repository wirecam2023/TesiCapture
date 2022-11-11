#include "stdafx.h"
#include "Endox.h"
#include "WriteLogLineSet.h"

#include "DLL_Imaging\h\AmLogin.h"

#include "LogFileWriter.h"
#include "MmSystem.h"
#include "WriteLogLineSPSet.h"
#include "Common.h"

/*
#ifdef _DEBUG
#define _DEBUG_DB // Commentare questa riga per velocizzare il debug --> nella finestra di output non vengono più fatti i TRACE delle varie attività in corso sul DB //
#endif
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWriteLogLineSet, CAMBaseSet)

CWriteLogLineSet::CWriteLogLineSet(LPCTSTR szTabella, LPCTSTR szNomeChiave, const long lValoreChiave, const CString &sCommento)
: CAMBaseSet(&theApp.m_dbEndox)
{
	m_sSavedTabella = szTabella;
	m_sSavedNomeChiave = szNomeChiave;
	m_lSavedValoreChiave = lValoreChiave;
	m_sSavedCommento = sCommento;

	m_lID = 0;
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_sData = "";
	m_sImpianto = "";
	m_sUtente = "";
	m_sStazione = "";
	m_sTabella = "";
	m_lOperazione = 0;
	m_sNomeChiave = "";
	m_lValoreChiave = 0;
	m_sCampo = "";
	m_sValoreOld = "";
	m_sValoreNew = "";
	m_sCommento = "";

	m_nFields = 15;
}

CWriteLogLineSet::~CWriteLogLineSet()
{
	if (IsOpen())
		Close();
}

void CWriteLogLineSet::DoFieldExchange(CFieldExchange* pFX)
{
	CAMBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "DataOra", m_sData, 14);
	RFX_Text(pFX, "Impianto", m_sImpianto, 50);
	RFX_Text(pFX, "Utente", m_sUtente, 50);
	RFX_Text(pFX, "Stazione", m_sStazione, 50);
	RFX_Text(pFX, "Tabella", m_sTabella, 50);
	RFX_Long(pFX, "Operazione", m_lOperazione);
	RFX_Text(pFX, "NomeChiave", m_sNomeChiave, 50);
	RFX_Long(pFX, "ValoreChiave", m_lValoreChiave);
	RFX_Text(pFX, "Campo", m_sCampo, 50);
	RFX_Text(pFX, "ValoreOld", m_sValoreOld, _TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, "ValoreNew", m_sValoreNew, _TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, "Commento", m_sCommento, 255);
}

CString CWriteLogLineSet::GetDefaultSQL()
{
	return "tb_LogCompleto";
}

void CWriteLogLineSet::Execute(const CString &sCampo, CRecordset* pSetOld, double* pValoreOld, CRecordset* pSetNew, double* pValoreNew)
{
	CString sValoreOld = "";
	try
	{
		if (!pSetOld->IsOpen() || !pSetOld->IsFieldNull(pValoreOld))
			sValoreOld.Format("%.3lf", *pValoreOld);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreOld.Format("%.3lf", *pValoreOld);
	}

	CString sValoreNew = "";
	try
	{
		if (!pSetNew->IsOpen() || !pSetNew->IsFieldNull(pValoreNew))
			sValoreNew.Format("%.3lf", *pValoreNew);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreNew.Format("%.3lf", *pValoreNew);
	}

	if (sValoreOld.Compare(sValoreNew) != 0)
		Execute(op_edit, sCampo, sValoreOld, sValoreNew);
}

void CWriteLogLineSet::Execute(const CString &sCampo, CRecordset* pSetOld, float* pValoreOld, CRecordset* pSetNew, float* pValoreNew)
{
	CString sValoreOld = "";
	try
	{
		if (!pSetOld->IsOpen() || !pSetOld->IsFieldNull(pValoreOld))
			sValoreOld.Format("%.3f", *pValoreOld);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreOld.Format("%.3f", *pValoreOld);
	}

	CString sValoreNew = "";
	try
	{
		if (!pSetNew->IsOpen() || !pSetNew->IsFieldNull(pValoreNew))
			sValoreNew.Format("%.3f", *pValoreNew);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreNew.Format("%.3f", *pValoreNew);
	}

	if (sValoreOld.Compare(sValoreNew) != 0)
		Execute(op_edit, sCampo, sValoreOld, sValoreNew);
}

void CWriteLogLineSet::Execute(const CString &sCampo, CRecordset* pSetOld, int* pValoreOld, CRecordset* pSetNew, int* pValoreNew)
{
	CString sValoreOld = "";
	try
	{
		if (!pSetOld->IsOpen() || !pSetOld->IsFieldNull(pValoreOld))
			sValoreOld.Format("%d", *pValoreOld);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreOld.Format("%d", *pValoreOld);
	}

	CString sValoreNew = "";
	try
	{
		if (!pSetNew->IsOpen() || !pSetNew->IsFieldNull(pValoreNew))
			sValoreNew.Format("%d", *pValoreNew);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreNew.Format("%d", *pValoreNew);
	}

	if (sValoreOld.Compare(sValoreNew) != 0)
		Execute(op_edit, sCampo, sValoreOld, sValoreNew);
}

void CWriteLogLineSet::Execute(const CString &sCampo, CRecordset* pSetOld, long* pValoreOld, CRecordset* pSetNew, long* pValoreNew)
{
	CString sValoreOld = "";
	try
	{
		if (!pSetOld->IsOpen() || !pSetOld->IsFieldNull(pValoreOld))
			sValoreOld.Format("%li", *pValoreOld);
	}
	catch(CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreOld.Format("%li", *pValoreOld);
	}

	CString sValoreNew = "";
	try
	{
		if (!pSetNew->IsOpen() || !pSetNew->IsFieldNull(pValoreNew))
			sValoreNew.Format("%li", *pValoreNew);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();

		sValoreNew.Format("%li", *pValoreNew);
	}

	//Davide 20170717 - tentativo velocizzazione worklist
	if (sValoreOld == "1246576928")
		sValoreOld = "";
	//

	if (sValoreOld.Compare(sValoreNew) != 0)
		Execute(op_edit, sCampo, sValoreOld, sValoreNew);
}

void CWriteLogLineSet::Execute(const CString &sCampo, CRecordset* pSetOld, CString* pValoreOld, CRecordset* pSetNew, CString* pValoreNew)
{
	if (pValoreOld->Compare(*pValoreNew) != 0)
		Execute(op_edit, sCampo, *pValoreOld, *pValoreNew);
}

void CWriteLogLineSet::Execute()
{
	Execute(op_addnew, "", "", "");
}

void CWriteLogLineSet::Execute(const long lOperazione, const CString &sCampo, const CString &sValoreOld, const CString &sValoreNew)
{
	if ((sValoreOld.GetLength() < 4000) && (sValoreNew.GetLength() < 4000))
	{
		//#ifdef _DEBUG_DB
		DWORD timeDurata = timeGetTime();
		//#endif // _DEBUG_DB //

		long lIDPaziente = 0;
		if (theApp.m_pSetPazienti != NULL)
		{
			if (theApp.m_pSetPazienti->IsOpen())
			{
				if (!theApp.m_pSetPazienti->IsEOF() && !theApp.m_pSetPazienti->IsFieldNull(&theApp.m_pSetPazienti->m_lContatore))
				{
					lIDPaziente = theApp.m_pSetPazienti->m_lContatore;
				}
			}
		}

		long lIDEsame = 0;
		if (theApp.m_pSetEsami != NULL)
		{
			if (theApp.m_pSetEsami->IsOpen())
			{
				if (!theApp.m_pSetEsami->IsEOF() && !theApp.m_pSetEsami->IsFieldNull(&theApp.m_pSetEsami->m_lContatore))
				{
					lIDEsame = theApp.m_pSetEsami->m_lContatore;
				}
			}
		}

		CWriteLogLineSPSet().Exec(lIDPaziente,
			lIDEsame,
			(theApp.m_bImpersonated) ? theApp.m_sUtenteLoggato + " IMPERSONATED AS " + theApp.m_sImpersonatedUsername : theApp.m_sUtenteLoggato,
			theApp.m_sNomeComputer.Left(50),
			theApp.m_sNomeImpianto.Left(50),
			m_sSavedTabella,
			lOperazione,
			m_sSavedNomeChiave.Left(50),
			m_lSavedValoreChiave,
			sCampo,
			sValoreOld,
			sValoreNew,
			m_sSavedCommento);

		//#ifdef _DEBUG_DB
		timeDurata = timeGetTime() - timeDurata;
		XWriteLogTime("CWriteLogLineSet::Execute SP " + m_sSavedTabella + " " + sCampo + " OLD: \"" + sValoreOld + "\" NEW: \"" + sValoreNew + "\"", timeDurata, 0);
		/*
		if (timeDurata > _MAX_DB_TIME_)
		{
		TRACE("CWriteLogLineSet::Execute SP %s %s %li msec. !!!!!!!!!!!!!!!!!!!!\n", m_sSavedTabella, sCampo, (long)timeDurata);
		}
		else
		{
		TRACE("CWriteLogLineSet::Execute SP %s %s %li msec.\n", m_sSavedTabella, sCampo, (long)timeDurata);
		}
		*/
		//#endif /* _DEBUG_DB */
	}
	else
	{
		try
		{
			//#ifdef _DEBUG_DB
			DWORD timeDurata = timeGetTime();
			//#endif // _DEBUG_DB //

			//#ifdef _LOG_DB
			//	DWORD timeDurata2 = timeGetTime();
			//#endif // _LOG_DB //

			SetOpenFilter("ID=0");

			//Davide 20170717 - tentativo velocizzazione worklist
			//Open();

			if (!IsOpen())
			{
				SetOpenFilter("ID=0");
				Open();

				m_strDataSaved = theApp.GetServerDate();
			}
			//

			AddNew();

			m_lIDPaziente = 0;
			if (theApp.m_pSetPazienti != NULL)
			{
				if (!theApp.m_pSetPazienti->IsEOF() && !theApp.m_pSetPazienti->IsFieldNull(&theApp.m_pSetPazienti->m_lContatore))
				{
					m_lIDPaziente = theApp.m_pSetPazienti->m_lContatore;
				}
			}

			m_lIDEsame = 0;
			if (theApp.m_pSetEsami != NULL)
			{
				if (!theApp.m_pSetEsami->IsEOF() && !theApp.m_pSetEsami->IsFieldNull(&theApp.m_pSetEsami->m_lContatore))
				{
					m_lIDEsame = theApp.m_pSetEsami->m_lContatore;
				}
			}

			m_lOperazione = lOperazione;
			m_sCampo = sCampo.Left(50);
			m_sValoreOld = sValoreOld.Left(_TEXT_CONTROL_FIELD_LIMIT);
			m_sValoreNew = sValoreNew.Left(_TEXT_CONTROL_FIELD_LIMIT);

			m_sUtente = theApp.m_sUtenteLoggato.Left(50);

			//Davide 20170717 - tentativo velocizzazione worklist
			/*
			CRecordset set(&theApp.m_dbEndox);
			set.Open(CRecordset::snapshot, "SELECT DATA FROM AM_GETSERVERDATE", CRecordset::readOnly);
			if (!set.IsEOF())
			{
			set.GetFieldValue((short)0, m_sData);
			}
			set.Close();*/

			m_sStazione = theApp.m_sNomeComputer.Left(50);
			m_sImpianto = theApp.m_sNomeImpianto.Left(50);
			m_sData = m_strDataSaved;
			m_sTabella = m_sSavedTabella;
			m_sNomeChiave = m_sSavedNomeChiave.Left(50);
			m_lValoreChiave = m_lSavedValoreChiave;
			m_sCommento = m_sSavedCommento;

			Update();

			/*
			#ifdef _DEBUG_DB
			timeDurata = timeGetTime() - timeDurata;

			if (timeDurata > _MAX_DB_TIME_)
			{
				TRACE1("   Execute TE: %li msec. !!!!!!!!!!!!!!!!!!!!\n", (long)timeDurata);
			}
			else
			{
				TRACE1("   Execute TE: %li msec.\n", (long)timeDurata);
			}
			#endif /* _DEBUG_DB * /

			#ifdef _LOG_DB
			timeDurata2 = timeGetTime() - timeDurata2;

			CString strLogLine;
			if (timeDurata2 > _MAX_DB_TIME_)
			{
				strLogLine.Format("   Execute TE: %li msec. !!!!!!!!!!!!!!!!!!!!", (long)timeDurata2);
			}
			else
			{
				strLogLine.Format("   Execute TE: %li msec.", (long)timeDurata2);
			}
			CLogFileWriter::Get()->WriteLogLine(strLogLine);
			#endif /* _LOG_DB * /
			*/
			timeDurata = timeGetTime() - timeDurata;
			XWriteLogTime("CWriteLogLineSet::Execute noSP " + m_sSavedTabella + " " + sCampo + " OLD: \"" + m_sValoreOld + "\" NEW: \"" + m_sValoreNew + "\"", timeDurata, 0);
		}
		catch (CDBException* pEx)
		{
			pEx->ReportError();
			pEx->Delete();
		}
		catch (CMemoryException* pEx)
		{
			pEx->ReportError();
			pEx->Delete();
		}

		//Davide 20170717 - tentativo velocizzazione worklist if (IsOpen())
		//Davide 20170717 - tentativo velocizzazione worklist	Close();
	}
}