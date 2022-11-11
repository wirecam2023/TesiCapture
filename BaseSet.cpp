#include "stdafx.h"
#include "Endox.h"
#include "BaseSet.h"

#include "LogFileWriter.h"
#include "MmSystem.h"
#include "RecordAddSP.h"
#include "ShowDbQueriesDlg.h"

#ifdef _DEBUG
	// #define _DEBUG_DB // Commentare questa riga per velocizzare il debug --> nella finestra di output non vengono più fatti i TRACE delle varie attività in corso sul DB //
	// #define _MAX_DB_TIME_ 500
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBaseSet, CAMBaseSet)

CBaseSet::CBaseSet(long *pIdentityField, const CString &strIdentityField)
	: CAMBaseSet(&theApp.m_dbEndox)
{
	m_pCopySet = NULL;
	m_pIdentityField = pIdentityField;
	m_sIdentityField = strIdentityField;
}

CBaseSet::~CBaseSet()
{
	if (m_pCopySet != NULL)
	{
		delete m_pCopySet;
		m_pCopySet = NULL;
	}
}

// chiude il recordset arrangiandosi a gestire le eccezioni ed i messaggi all'utente //
BOOL CBaseSet::CloseRecordset(const CString &sCommento, BOOL bDebugDB)
{
	#ifdef _DEBUG_DB
		if (bDebugDB)
		{
			TRACE0("-> -------------------------------------------------- ->\n");
			TRACE1("   CloseRecordset(%s)\n", sCommento);
			TRACE1("   SQL:        %s\n", GetDefaultSQL());
			TRACE1("   BASEFILTER: %s\n", m_strBaseFilter);
			TRACE1("   OPENFILTER: %s\n", m_strOpenFilter);
			TRACE1("   SORTRECORD: %s\n", m_strSort);
			TRACE0("<- -------------------------------------------------- <-\n");
		}
	#endif /* _DEBUG_DB */

	try
	{
		if (m_pDatabase)
			CAMBaseSet::Close();

		return TRUE;
	}
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("CloseRecordset (%s)\n%d: %s\n\nSQL: %s\n\nBaseFilter: %s\nOpenFilter: %s\nSortRecord: %s", sCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);
 		e->Delete();
	}

	return FALSE;
}

// apre il recordset arrangiandosi a gestire le eccezioni ed i messaggi all'utente //
BOOL CBaseSet::OpenRecordset(const CString &sCommento, BOOL bDebugDB, BOOL bForceDynaset)
{
	BOOL bReturn = FALSE;

	#ifdef _DEBUG_DB
		if (bDebugDB)
		{
			TRACE0("-> -------------------------------------------------- ->\n");

			TRACE1("   OpenRecordset(%s)\n", sCommento);
			TRACE1("   SQL:        %s\n", GetDefaultSQL());
			TRACE1("   BASEFILTER: %s\n", m_strBaseFilter);
			TRACE1("   OPENFILTER: %s\n", m_strOpenFilter);
			TRACE1("   SORTRECORD: %s\n", m_strSort);
		}
		DWORD timeDurata = timeGetTime();
	#endif // _DEBUG_DB //

	#ifdef _LOG_DB
		if (bDebugDB)
		{
			CString strLogLine;

			strLogLine.Format("-> -------------------------------------------------- ->");
			CLogFileWriter::Get()->WriteLogLine(strLogLine);

			strLogLine.Format("   OpenRecordset(%s)", sCommento);
			CLogFileWriter::Get()->WriteLogLine(strLogLine);
			strLogLine.Format("   SQL:        %s", GetDefaultSQL());
			CLogFileWriter::Get()->WriteLogLine(strLogLine);
			strLogLine.Format("   BASEFILTER: %s", m_strBaseFilter);
			CLogFileWriter::Get()->WriteLogLine(strLogLine);
			strLogLine.Format("   OPENFILTER: %s", m_strOpenFilter);
			CLogFileWriter::Get()->WriteLogLine(strLogLine);
			strLogLine.Format("   SORTRECORD: %s", m_strSort);
			CLogFileWriter::Get()->WriteLogLine(strLogLine);

		}
		DWORD timeDurata2 = timeGetTime();
	#endif // _LOG_DB //

	try
	{
		if (CAMBaseSet::IsOpen())
			CAMBaseSet::Close();

		// verifico se è stato impostato un ordinamento e nel caso imposto l'ordinamento sulla chiave primaria che velocizza varie operazioni e male non fa //
		if (m_strSort.Trim().IsEmpty() && m_sIdentityField.CompareNoCase("VIEW") != 0)
			SetSortRecord(m_sIdentityField); 

		int nOpenType = CRecordset::dynaset;
		int nOptions = CRecordset::skipDeletedRecords;
		if ((m_sIdentityField.CompareNoCase("VIEW") == 0 || m_sIdentityField.IsEmpty()) && (!bForceDynaset))
		{
			nOpenType = CRecordset::snapshot;
			nOptions |= CRecordset::readOnly;
		}

		DWORD timeOpen = timeGetTime();
		CAMBaseSet::Open(nOpenType, NULL, nOptions);

		if (theApp.m_bSaveCompleteLog)
			CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, m_strSQL, sCommento);

		if (theApp.m_pShowDbQueriesWnd != NULL)
			theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, m_strSQL, sCommento);

		bReturn = TRUE;
    }
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("OpenRecordset (%s)\n%d: %s\n\nSQL\n%s\n\nBASEFILTER\n%s\n\nOPENFILTER\n%s\n\nSORTRECORD\n%s\n", sCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);
 		e->Delete();
	}

	#ifdef _DEBUG_DB
		if (bDebugDB)
		{
			timeDurata = timeGetTime() - timeDurata;

			if (timeDurata > _MAX_DB_TIME_)
				TRACE1("   TEMPO ESEC: %li msec. !!!!!!!!!!!!!!!!!!!!\n", (long)timeDurata);
			else
				TRACE1("   TEMPO ESEC: %li msec.\n", (long)timeDurata);

			TRACE0("<- -------------------------------------------------- <-\n");
		}
	#endif // _DEBUG_DB //

	#ifdef _LOG_DB
		if (bDebugDB)
		{
			timeDurata2 = timeGetTime() - timeDurata2;

			CString strLogLine;
			if (timeDurata2 > _MAX_DB_TIME_)
				strLogLine.Format("   TEMPO ESEC: %li msec. !!!!!!!!!!!!!!!!!!!!", (long)timeDurata2);
			else
				strLogLine.Format("   TEMPO ESEC: %li msec.", (long)timeDurata2);
			CLogFileWriter::Get()->WriteLogLine(strLogLine);
			strLogLine.Format("<- -------------------------------------------------- <-");
			CLogFileWriter::Get()->WriteLogLine(strLogLine);
			CLogFileWriter::Get()->WriteLogLine("");
		}
	#endif // _LOG_DB //

	return bReturn;
}

// chiude e riapre il recordset arrangiandosi a gestire le eccezioni ed i messaggi all'utente //
BOOL CBaseSet::RecordsetReOpen(BOOL &bError, const CString &strFilter, const CString &strSort, const CString &sCommento)
{
	BOOL bReturn = FALSE;
	bError = FALSE;

	#ifdef _DEBUG_DB
		TRACE0("-> -------------------------------------------------- ->\n");
		TRACE1("   RecordsetReOpen(%s)\n", sCommento);
		TRACE1("   SQL:        %s\n", GetDefaultSQL());
		TRACE1("   BASEFILTER: %s\n", m_strBaseFilter);
		TRACE1("   OPENFILTER: %s\n", m_strOpenFilter);
		TRACE1("   SORTRECORD: %s\n", m_strSort);

		DWORD timeDurata = timeGetTime();
	#endif // _DEBUG_DB //

	#ifdef _LOG_DB
		CString strLogLine;

		strLogLine.Format("-> -------------------------------------------------- ->");
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   RecordsetReOpen(%s)", sCommento);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   SQL:        %s", GetDefaultSQL());
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   BASEFILTER: %s", m_strBaseFilter);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   OPENFILTER: %s", m_strOpenFilter);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   SORTRECORD: %s", m_strSort);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);

		DWORD timeDurata2 = timeGetTime();
	#endif // _LOG_DB //

	try
	{
		if (CAMBaseSet::IsOpen())
			CAMBaseSet::Close();

		SetOpenFilter(strFilter);

		if (!strSort.IsEmpty())
			SetSortRecord(strSort);

		DWORD timeOpen = timeGetTime();
		CAMBaseSet::Open();

		if (theApp.m_bSaveCompleteLog)
			CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, m_strSQL, sCommento);

		if (theApp.m_pShowDbQueriesWnd != NULL)
			theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, m_strSQL, sCommento);
	
		if (!CAMBaseSet::IsBOF() && !CAMBaseSet::IsEOF())
			bReturn = TRUE;
	}
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("RecordsetReOpen (%s)\n%d: %s\n\nSQL\n%s\n\nBASEFILTER\n%s\n\nOPENFILTER\n%s\n\nSORTRECORD\n%s\n", sCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);

 		e->Delete();

		bError = TRUE;
	}

	#ifdef _DEBUG_DB
		timeDurata = timeGetTime() - timeDurata;

		if (timeDurata > _MAX_DB_TIME_)
			TRACE1("   TEMPO ESEC: %li msec. !!!!!!!!!!!!!!!!!!!!\n", (long)timeDurata);
		else
			TRACE1("   TEMPO ESEC: %li msec.\n", (long)timeDurata);

		TRACE0("<- -------------------------------------------------- <-\n");
	#endif /* _DEBUG_DB */

	#ifdef _LOG_DB
		timeDurata2 = timeGetTime() - timeDurata2;

		if (timeDurata2 > _MAX_DB_TIME_)
			strLogLine.Format("   TEMPO ESEC: %li msec. !!!!!!!!!!!!!!!!!!!!", (long)timeDurata2);
		else
			strLogLine.Format("   TEMPO ESEC: %li msec.", (long)timeDurata2);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("<- -------------------------------------------------- <-");
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		CLogFileWriter::Get()->WriteLogLine("");
	#endif // _LOG_DB //

	return bReturn;
}

// aggiorna i dati del record corrente //
BOOL CBaseSet::RefreshRecordset()
{
	if (CAMBaseSet::IsBOF() || CAMBaseSet::IsEOF())
	{
		CAMBaseSet::SetFieldNull(NULL, TRUE);  // set all fields to NULL
	}
	else
	{
		if (!CAMBaseSet::IsBOF())
		{
			MovePrev();
			MoveNext();
		}
		else
		{
			MoveNext();
			MovePrev();
		}
	}

	return TRUE;
}

// aggiorna i dati del record corrente //
BOOL CBaseSet::RequeryRecordset()
{
	return CAMBaseSet::Requery();
}

// aggiunge un nuovo record //
BOOL CBaseSet::AddNewRecordset(const CString &sCommento)
{
	try
	{
		CAMBaseSet::AddNew();
		
		m_lLastAdd = 0;

		return TRUE;
	}
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("AddNewRecordset (%s)\n%d: %s\n\nSQL: %s\n\nBaseFilter: %s\nOpenFilter: %s\nSortRecord: %s", sCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);
 		e->Delete();
	}

	try
	{
		CAMBaseSet::CancelUpdate();
	}
	catch(CDBException* e)
	{
 		e->Delete();
	}

	return FALSE;
}

// elimina il record corrente //
/*
BOOL CBaseSet::DeleteRecordset(const CString &sCommento)
{
	return UpdateDel(sCommento);
}*/

// attiva la modifica sul record corrente //
BOOL CBaseSet::EditRecordset(const CString &sCommento)
{
	try
	{
		// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
		if (CAMBaseSet::IsOpen())
		{
			CAMBaseSet::Refresh();
			CAMBaseSet::Edit();
		}

		// ora mi salvo in memoria una copia del recordset che riutilizzo durante il salvataggio per capire le modifiche apportate //
		if (m_pCopySet != NULL)
		{
			delete m_pCopySet;
			m_pCopySet = NULL;
		}
		if (m_pCopySet == NULL)
		{
			m_pCopySet = CreateNew();
			if (m_pCopySet != NULL)
				m_pCopySet->CopyFields(this, TRUE);
		}

		return TRUE;
	}
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("EditRecordset (%s)\n%d: %s\n\nSQL: %s\n\nBaseFilter: %s\nOpenFilter: %s\nSortRecord: %s", sCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);
		e->Delete();
	}

	try
	{
		CAMBaseSet::CancelUpdate();
	}
	catch(CDBException* e)
	{
 		e->Delete();
	}

	return FALSE;
}

// annulla le modifiche al record corrente //
BOOL CBaseSet::NoEditRecordset(const CString &sCommento)
{
	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	if (!IsOpen())
	{
		return FALSE;
	}

	try
	{
		CAMBaseSet::CancelUpdate();

		return TRUE;
	}
	catch(CDBException* e)
	{
 		e->Delete();
	}

	return FALSE;
}

// salva le modifiche al record corrente //
BOOL CBaseSet::UpdateRecordset(const CString &sCommento)
{
	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	if (!IsOpen())
	{
		return FALSE;
	}

	BOOL bReturn = FALSE;

	DWORD timeDurata = 0;//timeGetTime();

	#ifdef _DEBUG_DB
		TRACE0("-> -------------------------------------------------- ->\n");
		TRACE1("   UpdateRecordset(%s)\n", sCommento);
		TRACE1("   SQL:        %s\n", GetDefaultSQL());
		TRACE1("   BASEFILTER: %s\n", m_strBaseFilter);
		TRACE1("   OPENFILTER: %s\n", m_strOpenFilter);
		TRACE1("   SORTRECORD: %s\n", m_strSort);

		//DWORD timeDurata = timeGetTime();
	#endif // _DEBUG_DB //

	#ifdef _LOG_DB
		CString strLogLine;

		strLogLine.Format("-> -------------------------------------------------- ->");
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   UpdateRecordset(%s)", sCommento);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   SQL:        %s", GetDefaultSQL());
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   BASEFILTER: %s", m_strBaseFilter);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   OPENFILTER: %s", m_strOpenFilter);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("   SORTRECORD: %s", m_strSort);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);

		DWORD timeDurata2 = timeGetTime();
	#endif // _LOG_DB //

	switch(m_nEditMode)
	{
		case edit:
		{
			bReturn = UpdateEdt(sCommento);
			break;
		}
		case addnew:
		{
			bReturn = UpdateAdd(sCommento);
			break;
		}
	}

	#ifdef _DEBUG_DB
		if (timeGetTime() - timeDurata > _MAX_DB_TIME_)
			TRACE1("   TEMPO ESEC: %li msec. !!!!!!!!!!!!!!!!!!!!\n", (long)timeGetTime() - timeDurata);
		else
			TRACE1("   TEMPO ESEC: %li msec.\n", (long)timeGetTime() - timeDurata);

		TRACE0("<- -------------------------------------------------- <-\n");
	#endif /* _DEBUG_DB */

	#ifdef _LOG_DB
		timeDurata2 = timeGetTime() - timeDurata2;

		if (timeDurata2 > _MAX_DB_TIME_)
			strLogLine.Format("   TEMPO ESEC: %li msec. !!!!!!!!!!!!!!!!!!!!", (long)timeDurata2);
		else
			strLogLine.Format("   TEMPO ESEC: %li msec.", (long)timeDurata2);
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		strLogLine.Format("<- -------------------------------------------------- <-");
		CLogFileWriter::Get()->WriteLogLine(strLogLine);
		CLogFileWriter::Get()->WriteLogLine("");
	#endif // _LOG_DB //

		if (theApp.m_bSaveCompleteLog)
			CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeDurata, "UpdateRecordset " + m_strSQL, sCommento);

		if (theApp.m_pShowDbQueriesWnd != NULL)
			theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeDurata, "UpdateRecordset " + m_strSQL, sCommento);

	return bReturn;
}

long CBaseSet::GetIdentityLong()
{
	return *m_pIdentityField;
}

CString CBaseSet::GetIdentityString()
{
	return m_sIdentityField;
}

long CBaseSet::GetLastAdd()
{
	return m_lLastAdd;
}

BOOL CBaseSet::UpdateAdd(const CString &sCommento)
{
	CBaseSet *pCopySet = NULL;

	try
	{
		if (m_pIdentityField != NULL)
		{
			if (m_sIdentityField.CompareNoCase("IDESAME") == 0)
			{
				// In questo caso segno l'aggiunta nel LOG ma senza eseguire la procedura automatica sp_RecordAdd //

				int nEditMode = m_nEditMode;
				long lIDEsame = (*m_pIdentityField);

				DWORD timeOpen = timeGetTime();
				CAMBaseSet::Update();

				if (theApp.m_bSaveCompleteLog)
					CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, "INSERT INTO " + GetDefaultSQL(), sCommento);

				if (theApp.m_pShowDbQueriesWnd != NULL)
					theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, "INSERT INTO " + GetDefaultSQL(), sCommento);

				// Sandro 14/12/2011 //
				if (nEditMode == addnew)
				{
					// mi posiziono sopra al record appena aggiunto //
					CString strFilter;
					strFilter.Format("IDESAME=%li", lIDEsame);
					SetOpenFilter(strFilter);
					RequeryRecordset();
				}

				CWriteLogLineSet sp(GetTableName(), m_sIdentityField, lIDEsame, sCommento);
				sp.Execute();

				(*m_pIdentityField) = lIDEsame;

				pCopySet = CreateNew();
				SaveLog(pCopySet, this, sCommento);
				delete pCopySet;

				return TRUE;
			}
			else
			{
				// copio il recordset //
				pCopySet = CreateNew();
				pCopySet->CopyFields(this, FALSE);

				// annullo lo stato di modifica //
				NoEditRecordset(sCommento);

				// inserisco il record tramite la stored procedure //
				CRecordAddSP mySP;
				long lResult = mySP.Execute(GetDefaultSQL(), m_sIdentityField);

				if (lResult > 0) // è andato tutto bene //
				{
					CWriteLogLineSet sp(GetTableName(), m_sIdentityField, lResult, sCommento);
					sp.Execute();

					CString strQuery;
					CRecordset setCount(&theApp.m_dbEndox);
					CDBVariant dbVariant;

					// resetto ordinamento e filtri salvandomi i valori precedenti //
					CString strBaseFilter = CAMBaseSet::SetBaseFilter("");
					CString strSortRecord = CAMBaseSet::SetSortRecord(m_sIdentityField);

					CString strEditFilter;
					strEditFilter.Format("%s = %li", m_sIdentityField, lResult);
					CString strOpenFilter = CAMBaseSet::SetOpenFilter(strEditFilter);

					// chiudo e riapro il recordset (sempre in dynaset perchè lo snapshot in SQL Server è readonly) //
					CloseRecordset(sCommento, FALSE);

					UINT nOpenTypeTemp = m_nOpenType;
					m_nOpenType = CRecordset::dynaset;
					OpenRecordset(sCommento, FALSE);
					m_nOpenType = nOpenTypeTemp;

					// verifico di essere sopra al record corretto //
					VERIFY(lResult == *m_pIdentityField);

					// rimetto il recordset in modifica e ci ricopio sopra i dati salvati precedentemente //
					EditRecordset(sCommento);

					#ifdef _DEBUG_DB
						DWORD timeDurata = timeGetTime();
					#endif // _DEBUG_DB //

					#ifdef _LOG_DB
						DWORD timeDurata2 = timeGetTime();
					#endif // _LOG_DB //

					SaveLog(this, pCopySet, sCommento);

					#ifdef _DEBUG_DB
						timeDurata = timeGetTime() - timeDurata;

						if (timeDurata > _MAX_DB_TIME_)
							TRACE1("   SaveLog TE: %li msec. !!!!!!!!!!!!!!!!!!!!\n", (long)timeDurata);
						else
							TRACE1("   SaveLog TE: %li msec.\n", (long)timeDurata);
					#endif /* _DEBUG_DB */

					#ifdef _LOG_DB
						timeDurata2 = timeGetTime() - timeDurata2;

						CString strLogLine;
						if (timeDurata2 > _MAX_DB_TIME_)
							strLogLine.Format("   SaveLog TE: %li msec. !!!!!!!!!!!!!!!!!!!!", (long)timeDurata2);
						else
							strLogLine.Format("   SaveLog TE: %li msec.", (long)timeDurata2);

						CLogFileWriter::Get()->WriteLogLine(strLogLine);
					#endif /* _LOG_DB */

					// continuo con le altre operazioni //
					CopyFields(pCopySet, FALSE);
					delete pCopySet;
					pCopySet = NULL;

					// salvo il tutto //
					DWORD timeOpen = timeGetTime();
					CAMBaseSet::Update();

					if (theApp.m_bSaveCompleteLog)
						CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, "INSERT INTO " + GetDefaultSQL(), sCommento);

					if (theApp.m_pShowDbQueriesWnd != NULL)
						theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, "INSERT INTO " + GetDefaultSQL(), sCommento);

					// ripristino filtri ed ordinamento // 
					SetBaseFilter(strBaseFilter);
					SetOpenFilter(strOpenFilter);
					SetSortRecord(strSortRecord);

					// chiudo e riapro il recordset //
					CloseRecordset(sCommento, FALSE);
					OpenRecordset(sCommento, FALSE);

					if (!IsEOF() && !IsBOF())
					{
						// mi riposiziono sul record giusto //
						if (m_strSort.CompareNoCase(m_sIdentityField) == 0) // ordinati "bene" //
						{
							// costruisco la query che mi permette di posizionarmi sul nuovo record inserito dalla SP //
							strQuery.Format("SELECT COUNT(%s) AS CONTEGGIO FROM %s WHERE %s<=%li", m_sIdentityField, GetTableName(), m_sIdentityField, lResult);

							// aggiungo al filtro originale anche l'eventuale "BaseFilter" //
							m_strBaseFilter.Trim();
							if (!m_strBaseFilter.IsEmpty())
								strQuery += " AND (" + m_strBaseFilter + ")";

							// aggiungo al filtro originale anche l'eventuale "OpenFilter" //
							m_strOpenFilter.Trim();
							if (!m_strOpenFilter.IsEmpty())
								strQuery += " AND (" + m_strOpenFilter + ")";

							// apro recordset temporaneo per contare le righe //
							setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);

							// prendo il numero di righe che mi serve per il posizionamento //
							setCount.GetFieldValue("CONTEGGIO", dbVariant, SQL_C_SLONG);

							// ORA mi posiziono sul record appena inserito //
							SetAbsolutePosition(dbVariant.m_lVal);
							setCount.Close();

							// verifico di averlo trovato //
							if (*m_pIdentityField != lResult)
							{
								MoveLast();

								// a dire il vero l'inserimento dovrebbe essere OK ma in realtà non riesco a ritrovare il record... //
								// return FALSE; // Sandro 11/02/2010: se è già impostato un filtro non è detto che il record si trovi tra i risultati quindi non mi risulta //
							}
						}
						else // ordinati "MALE" //
						{
							UINT nFields = m_nFields;

							// imposto modalità fast search //
							m_nFields = 1;

							// vado avanti finche non trovo il mio record //
							while((!IsEOF()) && (*m_pIdentityField != lResult))
								MoveNext();

							// rimetto in modalità slow search :-D //
							m_nFields = nFields; 

							// verifico di averlo trovato //
							if (*m_pIdentityField != lResult)
							{
								MoveLast();

								// a dire il vero l'inserimento dovrebbe essere OK ma in realtà non riesco a ritrovare il record... //
								// return FALSE; // Sandro 11/02/2010: se è già impostato un filtro non è detto che il record si trovi tra i risultati quindi non mi risulta //
							}
						}
					}

					m_lLastAdd = lResult;
				}
				else // lResult <= 0 //
				{
					delete pCopySet;
					pCopySet = NULL;
					m_lLastAdd = 0;
					return FALSE;
				}
			}
		}
		else // m_pIdentityField == NULL //
		{
			ASSERT(m_sIdentityField.CompareNoCase("VIEW") != 0); // controllo che non sia una vista!!! //
			ASSERT(!m_sIdentityField.Trim().IsEmpty()); // controllo che il campo identità non sia vuoto //

			DWORD timeOpen = timeGetTime();
			CAMBaseSet::Update();

			if (theApp.m_bSaveCompleteLog)
				CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, "INSERT INTO " + GetDefaultSQL(), sCommento);

			if (theApp.m_pShowDbQueriesWnd != NULL)
				theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, "INSERT INTO " + GetDefaultSQL(), sCommento);
		}

		return TRUE;
	}
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("UpdateRecordset (%s)\n%d: %s\n\nSQL: %s\n\nBaseFilter: %s\nOpenFilter: %s\nSortRecord: %s", sCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);
 		e->Delete();

		if (pCopySet != NULL)
			delete pCopySet;
	}

	try
	{
		CAMBaseSet::CancelUpdate();
	}
	catch(CDBException* e)
	{
 		e->Delete();
	}

	return FALSE;
}

BOOL CBaseSet::UpdateEdt(const CString &sCommento)
{
	try
	{
		if (m_pIdentityField != NULL)
		{
			// segno il record come modificato tramite la stored procedure //
			//DavideCRecordEdtSP mySP;
			//Davidelong lResult = mySP.Execute(GetDefaultSQL(), m_sIdentityField, (*m_pIdentityField));

			//Davideif(lResult > 0) // è andato tutto bene //
			{
				// salvo nel log le modifiche apportate al record //
				SaveLog(m_pCopySet, this, sCommento);

				// cancello la copia del recordset //
				if (m_pCopySet != NULL)
				{
					delete m_pCopySet;
					m_pCopySet = NULL;
				}

				// salvo tutto //
				DWORD timeOpen = timeGetTime();
				if (!CAMBaseSet::Update())
					m_nEditMode = 0;

				if (theApp.m_bSaveCompleteLog)
					CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, "UPDATE " + GetDefaultSQL(), sCommento);

				if (theApp.m_pShowDbQueriesWnd != NULL)
					theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, "UPDATE " + GetDefaultSQL(), sCommento);

				return TRUE;
			}
			//Davideelse
			//Davide{
			//Davide	// annullo lo stato di modifica //
			//Davide	NoEditRecordset(sCommento);
			//Davide	return FALSE;
			//Davide}
		}
		else
		{
			ASSERT(m_sIdentityField.CompareNoCase("VIEW") != 0); // controllo che non sia una vista!!! //
			ASSERT(!m_sIdentityField.Trim().IsEmpty()); // controllo che il campo identità non sia vuoto //

			// salvo normalmente come da tradizione //
			DWORD timeOpen = timeGetTime();
 			CAMBaseSet::Update();

			if (theApp.m_bSaveCompleteLog)
				CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, "UPDATE " + GetDefaultSQL(), sCommento);

			if (theApp.m_pShowDbQueriesWnd != NULL)
				theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, "UPDATE " + GetDefaultSQL(), sCommento);

			return TRUE;
		}
	}
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("UpdateRecordset (%s)\n%d: %s\n\nSQL: %s\n\nBaseFilter: %s\nOpenFilter: %s\nSortRecord: %s", sCommento, e->m_nRetCode, e->m_strError, GetDefaultSQL(), m_strBaseFilter, m_strOpenFilter, m_strSort);
		theApp.AfxMessageBoxEndo(strError);
 		e->Delete();
	}

	try
  	{
		CAMBaseSet::CancelUpdate();
	}
	catch(CDBException* e)
	{
 		e->Delete();
	}

	return FALSE;
}

BOOL CBaseSet::IsFieldNull(void* pv)
{ 
	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture)
	// try to avoid unhandled exceptions
	if (pv == NULL || pv == nullptr)
	{
		return CAMBaseSet::IsFieldNull(pv);
	}

	BOOL bReturn = TRUE;

	int iFieldNum = GetBoundFieldIndex(pv);
	if (iFieldNum < 1)
	{
		CString strError;
		strError.Format("IsFieldNull()\n\nSQL: %s", GetDefaultSQL());
		theApp.AfxMessageBoxEndo(strError);

		return bReturn;
	}

	try
  	{
		bReturn = CAMBaseSet::IsFieldNull(pv);
	}
	catch(CDBException* e)
	{
		CString strError;
		strError.Format("IsFieldNull(%d)\n%d: %s\n\nSQL: %s", iFieldNum, e->m_nRetCode, e->m_strError, GetDefaultSQL());
		theApp.AfxMessageBoxEndo(strError);
 		e->Delete();
	}
	catch(CMemoryException* e)
	{
		TCHAR szError[255];
		e->GetErrorMessage(szError, 255);
 		e->Delete();

		CString strError;
		strError.Format("IsFieldNull(%d)\n%d: %s\n\nSQL: %s", iFieldNum, szError, GetDefaultSQL());
		theApp.AfxMessageBoxEndo(strError);
	}
	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture)
	// add an exception handler with message
	catch (CException* e )
	{
		TCHAR szError[255];
		e->GetErrorMessage(szError, 255);
		e->Delete();

		CString strError;
		strError.Format("IsFieldNull(%d)\n%d: %s\n\nSQL: %s", iFieldNum, szError, GetDefaultSQL());
		theApp.AfxMessageBoxEndo(strError);
	}

	return bReturn;
}

//Gabriel - TCP
BOOL CBaseSet::CheckColumnExists(LPCTSTR szTable, LPCTSTR szColumnName)
{
	tagDsnConnection tagTemp1;
	Amdbx_GetConnectionParam(&tagTemp1, theApp.m_sFileConfig);
	_strupr_s(tagTemp1.strParam1);
	_strupr_s(tagTemp1.strUser);

	BOOL bOracle = CString(tagTemp1.strParam1).Find("ORACLE") >= 0;
	BOOL bReturn = FALSE;

	SQLHANDLE handle;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_pDatabase->m_hdbc, &handle) == SQL_SUCCESS)
	{
		SQLRETURN rc = SQLColumns(handle,
			NULL,
			0,
			bOracle ? (SQLCHAR*)tagTemp1.strUser : NULL,
			bOracle ? SQL_NTS : 0,
			(SQLCHAR*)szTable,
			SQL_NTS,
			NULL,
			0);

		if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO)
		{
			SQLCHAR szColumnName2[255];
			SQLINTEGER cbName;

			SQLBindCol(handle, 4, SQL_C_CHAR, szColumnName2, 255, &cbName);

			while (SQLFetch(handle) != SQL_NO_DATA_FOUND)
			{
				_strupr_s((LPSTR)szColumnName2, 255);

				if (CString(szColumnName2).CompareNoCase(CString(szColumnName)) == 0)
					bReturn = TRUE;
			}
		}
	}

	if (handle != NULL)
		SQLFreeHandle(SQL_HANDLE_STMT, handle);

	return bReturn;
}