#include "stdafx.h"
#include "Endox.h"
#include "MediciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMediciSet, CBaseSet)

CMediciSet::CMediciSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	if (theApp.m_bUsaIDSegu)
		m_nFields = 27; //Julio Login SEGU
	else
		m_nFields = 26; //Julio Login SEGU
}

void CMediciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore",	m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice",			m_sCodice,			 50);
		
		//Julio Login SEGU
		if (theApp.m_bUsaIDSegu)
			RFX_Text(pFX, "Codice3L3N",	m_sCodice3L3N,		 50); 

		RFX_Text(pFX, "Titolo",			m_sTitolo,			 50);
		RFX_Text(pFX, "Cognome",		m_sCognome,			 50);
		RFX_Text(pFX, "Nome",			m_sNome,			 50);
		RFX_Text(pFX, "CodiceFiscale",	m_sCodiceFiscale,	 16);
		RFX_Text(pFX, "Via",			m_sVia,				 50);
		RFX_Text(pFX, "Citta",			m_sCitta,			 50);
		RFX_Text(pFX, "CAP",			m_sCAP,				  5);
		RFX_Text(pFX, "Provincia",		m_sProvincia,		  5);
		RFX_Text(pFX, "Telefono",		m_sTelefono,		 50);
		RFX_Text(pFX, "Firma0",			m_sFirma0,			255);
		RFX_Text(pFX, "Firma1",			m_sFirma1,			255);
		RFX_Text(pFX, "Firma2",			m_sFirma2,			255);
		RFX_Text(pFX, "Firma3",			m_sFirma3,			255);
		RFX_Text(pFX, "Firma4",			m_sFirma4,			255);
		RFX_Text(pFX, "Firma5",			m_sFirma5,			255);
		RFX_Text(pFX, "Firma6",			m_sFirma6,			255);
		RFX_Text(pFX, "Firma7",			m_sFirma7,			255);
		RFX_Text(pFX, "Firma8",			m_sFirma8,			255);
		RFX_Text(pFX, "Firma9",			m_sFirma9,			255);
		RFX_Text(pFX, "ImmagineFirma",	m_sImmagineFirma,	_FIRMA_BMP_MAX_LENGTH);
		RFX_Long(pFX, "IDUtenteEndox",	m_lIDUserEndox);
		RFX_Bool(pFX, "Libero", m_bLibero);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato",		m_bEliminato);
	}
}

CString CMediciSet::GetDefaultSQL()
{
	return "EMEDICI";
}

void CMediciSet::SetEmpty()
{
	m_lContatore = 0;
	m_sCodice = "";
	m_sCodice3L3N = "";//Julio Login SEGU
	m_sCognome = "";
	m_sNome = "";
	m_sTitolo = "";
	m_sVia = "";
	m_sCitta = "";
	m_sCAP = "";
	m_sProvincia = "";
	m_sTelefono = "";
	m_sCodiceFiscale = "";
	m_sFirma0 = "";
	m_sFirma1 = "";
	m_sFirma2 = "";
	m_sFirma3 = "";
	m_sFirma4 = "";
	m_sFirma5 = "";
	m_sFirma6 = "";
	m_sFirma7 = "";
	m_sFirma8 = "";
	m_sFirma9 = "";
	m_sImmagineFirma = "";
	m_lIDUserEndox = 0;
	m_bLibero = FALSE;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

// passo il contatore e mi ritorna il dato del relativo record //
CString CMediciSet::GetCodiceFiscaleFromContatore(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMediciSet::GetCodiceFiscaleFromContatore"))
	{
		if (!IsEOF())
		{
			strReturn = m_sCodiceFiscale;
			strReturn.Trim();
		}

		CloseRecordset("CMediciSet::GetCodiceFiscaleFromContatore");
	}

	return strReturn;
}

// passo il contatore e mi ritorna il dato del relativo record //
CString CMediciSet::GetCognomeNomeFromContatore(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMediciSet::GetCognomeNomeFromContatore"))
	{
		if (!IsEOF())
		{
			strReturn = m_sCognome + " " + m_sNome;
			strReturn.Trim();
		}

		CloseRecordset("CMediciSet::GetCognomeNomeFromContatore");
	}

	return strReturn;
}

// passo il contatore e mi ritorna il dato del relativo record //
CString CMediciSet::GetFieldFirmaFromContatore(long lContatore, long lRigaFirma)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMediciSet::GetFieldFirmaFromContatore"))
	{
		if (!IsEOF())
		{
			switch(lRigaFirma)
			{
				case 0:
				{
					strReturn = m_sFirma0;
					break;
				}
				case 1:
				{
					strReturn = m_sFirma1;
					break;
				}
				case 2:
				{
					strReturn = m_sFirma2;
					break;
				}
				case 3:
				{
					strReturn = m_sFirma3;
					break;
				}
				case 4:
				{
					strReturn = m_sFirma4;
					break;
				}
				case 5:
				{
					strReturn = m_sFirma5;
					break;
				}
				case 6:
				{
					strReturn = m_sFirma6;
					break;
				}
				case 7:
				{
					strReturn = m_sFirma7;
					break;
				}
				case 8:
				{
					strReturn = m_sFirma8;
					break;
				}
				case 9:
				{
					strReturn = m_sFirma9;
					break;
				}
			}
		}

		CloseRecordset("CMediciSet::GetFieldFirmaFromContatore");
	}

	return strReturn;
}

// passo il contatore e mi ritorna il dato del relativo record //
CString CMediciSet::GetFieldTextFromContatore(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMediciSet::GetFieldTextFromContatore"))
	{
		if (!IsEOF())
		{
			strReturn = m_sTitolo + " " + m_sNome + " " + m_sCognome;
			strReturn.Trim();
		}

		CloseRecordset("CMediciSet::GetFieldTextFromContatore");
	}

	return strReturn;
}

// passo il contatore e mi ritorna il dato del relativo record //
BOOL CMediciSet::IsLiberoFromContatore(long lContatore)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMediciSet::GetFieldTextFromContatore"))
	{
		if (!IsEOF())
			bReturn = m_bLibero;

		CloseRecordset("CMediciSet::GetFieldTextFromContatore");
	}

	return bReturn;
}

BOOL CMediciSet::IsImmagineFirmaEmpty(long lContatore)
{
	BOOL bReturn = TRUE;

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMediciSet::IsImmagineFirmaEmpty"))
	{
		if (!IsEOF())
			bReturn = m_sImmagineFirma.IsEmpty();

		CloseRecordset("CMediciSet::IsImmagineFirmaEmpty");
	}

	return bReturn;
}

// passo l'ID utente e mi torna il dato del relativo record //
CString CMediciSet::GetCodiceFiscaleFromUserID(long lUserID)
{
	CString sReturn = "";

	if (lUserID > 0)
	{
		CString sFilter;
		sFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::GetCodiceFiscaleFromUserID"))
		{
			if (!IsEOF())
				sReturn = m_sCodiceFiscale;

			CloseRecordset("CMediciSet::GetCodiceFiscaleFromUserID");
		}
	}

	return sReturn;
}

// passo l'ID utente e mi torna il dato del relativo record //
CString CMediciSet::GetCodiceFromUserID(long lUserID)
{
	CString sReturn = "";

	if (lUserID > 0)
	{
		CString sFilter;
		sFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::GetCodiceFromUserID"))
		{
			if (!IsEOF())
				sReturn = m_sCodice;

			CloseRecordset("CMediciSet::GetCodiceFromUserID");
		}
	}

	return sReturn;
}
CString CMediciSet::GetCodice3L3NFromUserID(long lUserID) //Julio Login SEGU
{
	CString sReturn = "";

	if (lUserID > 0)
	{
		CString sFilter;
		sFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::GetCodiceFromUserID"))
		{
			if (!IsEOF())
				sReturn = m_sCodice3L3N;

			CloseRecordset("CMediciSet::GetCodiceFromUserID");
		}
	}

	return sReturn;
}

// passo l'ID utente e mi torna il dato del relativo record //
CString CMediciSet::GetCognomeNomeFromUserID(long lUserID)
{
	CString strReturn = "";

	if (lUserID > 0)
	{
		CString strFilter;
		strFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CMediciSet::GetCognomeNomeFromUserID"))
		{
			if (!IsEOF())
			{
				strReturn = m_sCognome + " " + m_sNome;
				strReturn.Trim();
			}

			CloseRecordset("CMediciSet::GetCognomeNomeFromUserID");
		}
	}

	return strReturn;
}

// passo l'ID utente e mi torna il dato del relativo record //
long CMediciSet::GetContatoreFromUserID(long lUserID)
{
	long lReturn = 0;

	if (lUserID > 0)
	{
		CString sFilter;
		sFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::GetContatoreFromUserID"))
		{
			if (!IsEOF())
				lReturn = m_lContatore;

			CloseRecordset("CMediciSet::GetContatoreFromUserID");
		}
	}

	return lReturn;
}

long CMediciSet::GetContatoreFromCodice(CString codice)
{
	long lReturn = 0;

	if (codice != "")
	{
		CString sFilter;
		sFilter.Format("codice='%s'", codice);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::GetContatoreFromCodice"))
		{
			if (!IsEOF())
				lReturn = m_lContatore;

			CloseRecordset("CMediciSet::GetContatoreFromCodice");
		}
	}

	return lReturn;
}

// passo l'ID utente e mi torna il dato del relativo record //
CString CMediciSet::GetFieldFirmaFromUserID(long lUserID, long lRigaFirma)
{
	CString strReturn = "";

	if (lUserID > 0)
	{
		CString sFilter;
		sFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::GetFieldFirmaFromUserID"))
		{
			if (!IsEOF())
			{
				switch (lRigaFirma)
				{
					case 0:
					{
						strReturn = m_sFirma0;
						break;
					}
					case 1:
					{
						strReturn = m_sFirma1;
						break;
					}
					case 2:
					{
						strReturn = m_sFirma2;
						break;
					}
					case 3:
					{
						strReturn = m_sFirma3;
						break;
					}
					case 4:
					{
						strReturn = m_sFirma4;
						break;
					}
					case 5:
					{
						strReturn = m_sFirma5;
						break;
					}
					case 6:
					{
						strReturn = m_sFirma6;
						break;
					}
					case 7:
					{
						strReturn = m_sFirma7;
						break;
					}
					case 8:
					{
						strReturn = m_sFirma8;
						break;
					}
					case 9:
					{
						strReturn = m_sFirma9;
						break;
					}
					default:
					{
						ASSERT(FALSE);
						break;
					}
				}
			}

			CloseRecordset("CMediciSet::GetFieldFirmaFromUserID");
		}
	}

	return strReturn;
}

// passo l'ID utente e mi torna il dato del relativo record //
void CMediciSet::GetUserDataFromUserID(long lUserID, CString* pStrMedicoCognome, CString* pStrMedicoNome, CString* pStrMedicoCodFisc)
{
	pStrMedicoCognome->Empty();
	pStrMedicoNome->Empty();
	pStrMedicoCodFisc->Empty();

	if (lUserID > 0)
	{
		CString sFilter;
		sFilter.Format("IDUtenteEndox=%li", lUserID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::GetUserDataFromUserID"))
		{
			if (!IsEOF())
			{
				*pStrMedicoCognome = m_sCognome;
				*pStrMedicoNome = m_sNome;
				*pStrMedicoCodFisc = m_sCodiceFiscale;
			}

			CloseRecordset("CMediciSet::GetUserDataFromUserID");
		}
	}
}

BOOL CMediciSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", lID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::SetCodice"))
		{
			if (!IsEOF())
			{
				if (EditRecordset("CMediciSet::SetCodice"))
				{
					m_sCodice = sCodice;

					bReturn = UpdateRecordset("CMediciSet::SetCodice");
				}
			}

			CloseRecordset("CMediciSet::SetCodice");
		}
	}

	return bReturn;
}

BOOL CMediciSet::SetImmagineFirma(long lID, CString sImmagineFirma)
{
	BOOL bReturn = FALSE;

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", lID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::SetImmagineFirma"))
		{
			if (!IsEOF())
			{
				if (EditRecordset("CMediciSet::SetImmagineFirma"))
				{
					m_sImmagineFirma = sImmagineFirma;

					bReturn = UpdateRecordset("CMediciSet::SetImmagineFirma");
				}
			}

			CloseRecordset("CMediciSet::SetImmagineFirma");
		}
	}

	return bReturn;
}
//Julio Login SEGU
BOOL CMediciSet::UpdateInformation(long lID, CString sNome, CString sCodiceFiscale, CString sFirma, CString sCodice3L3N, CString sCodiceSEGU)
{
	BOOL bReturn = FALSE;

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", lID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::UpdateInformation"))
		{
			if (!IsEOF())
			{
				if (EditRecordset("CMediciSet::UpdateInformation"))
				{
					m_sNome = sNome;					
					m_sCodiceFiscale = sCodiceFiscale;
					m_sFirma0 = sFirma;
					m_sCodice3L3N = sCodice3L3N;
					m_sCodice = sCodiceSEGU;

					bReturn = UpdateRecordset("CMediciSet::UpdateInformation");
				}
			}

			CloseRecordset("CMediciSet::UpdateInformation");
		}
	}

	return bReturn;
}

long CMediciSet::FleuryTrans(CString sCognome, CString sNome)
{
	long lReturn = 0;

	sCognome.Trim();
	sCognome.Replace("'", "''");

	sNome.Trim();
	sNome.Replace("'", "''");

	if ((!sCognome.IsEmpty()) && (!sNome.IsEmpty()))
	{
		CString sFilter;
		sFilter.Format("COGNOME = '%s' AND NOME = '%s'", sCognome, sNome);
		SetOpenFilter(sFilter);
		if (OpenRecordset("CMediciSet::FleuryTrans"))
		{
			if (IsEOF())
			{
				if (AddNewRecordset("CMediciSet::FleuryTrans"))
				{
					m_sCognome = sCognome;
					m_sNome = sNome;

					if (UpdateRecordset("CMediciSet::FleuryTrans"))
						lReturn = GetLastAdd();
				}
			}
			else
			{
				lReturn = m_lContatore;
			}

			CloseRecordset("CMediciSet::FleuryTrans");
		}
	}

	return lReturn;
}

//
CBaseSet* CMediciSet::CreateNew()
{
	return (CBaseSet*)new CMediciSet;
}

void CMediciSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMediciSet* pSet = (CMediciSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	//Julio Login SEGU
	if (theApp.m_bUsaIDSegu)
	{
		if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice3L3N) || bCopyAll)
			m_sCodice3L3N = pSet->m_sCodice3L3N;
	}
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCognome) || bCopyAll)
		m_sCognome = pSet->m_sCognome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pSet->m_sTitolo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sVia) || bCopyAll)
		m_sVia = pSet->m_sVia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCitta) || bCopyAll)
		m_sCitta = pSet->m_sCitta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCAP) || bCopyAll)
		m_sCAP = pSet->m_sCAP;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sProvincia) || bCopyAll)
		m_sProvincia = pSet->m_sProvincia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTelefono) || bCopyAll)
		m_sTelefono = pSet->m_sTelefono;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceFiscale) || bCopyAll)
		m_sCodiceFiscale = pSet->m_sCodiceFiscale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma0) || bCopyAll)
		m_sFirma0 = pSet->m_sFirma0;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma1) || bCopyAll)
		m_sFirma1 = pSet->m_sFirma1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma2) || bCopyAll)
		m_sFirma2 = pSet->m_sFirma2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma3) || bCopyAll)
		m_sFirma3 = pSet->m_sFirma3;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma4) || bCopyAll)
		m_sFirma4 = pSet->m_sFirma4;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma5) || bCopyAll)
		m_sFirma5 = pSet->m_sFirma5;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma6) || bCopyAll)
		m_sFirma6 = pSet->m_sFirma6;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma7) || bCopyAll)
		m_sFirma7 = pSet->m_sFirma7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma8) || bCopyAll)
		m_sFirma8 = pSet->m_sFirma8;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFirma9) || bCopyAll)
		m_sFirma9 = pSet->m_sFirma9;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sImmagineFirma) || bCopyAll)
		m_sImmagineFirma = pSet->m_sImmagineFirma;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUserEndox) || bCopyAll)
		m_lIDUserEndox = pSet->m_lIDUserEndox;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bLibero) || bCopyAll)
		m_bLibero = pSet->m_bLibero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMediciSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMediciSet* pOV = (CMediciSet*)pOldValues;
	CMediciSet* pNV = (CMediciSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Codice3L3N", pOV, &pOV->m_sCodice3L3N, pNV, &pNV->m_sCodice3L3N);//Julio Login SEGU	
	sp.Execute("Cognome", pOV, &pOV->m_sCognome, pNV, &pNV->m_sCognome);
	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("Via", pOV, &pOV->m_sVia, pNV, &pNV->m_sVia);
	sp.Execute("Citta", pOV, &pOV->m_sCitta, pNV, &pNV->m_sCitta);
	sp.Execute("CAP", pOV, &pOV->m_sCAP, pNV, &pNV->m_sCAP);
	sp.Execute("Provincia", pOV, &pOV->m_sProvincia, pNV, &pNV->m_sProvincia);
	sp.Execute("Telefono", pOV, &pOV->m_sTelefono, pNV, &pNV->m_sTelefono);
	sp.Execute("CodiceFiscale", pOV, &pOV->m_sCodiceFiscale, pNV, &pNV->m_sCodiceFiscale);
	sp.Execute("Firma0", pOV, &pOV->m_sFirma0, pNV, &pNV->m_sFirma0);
	sp.Execute("Firma1", pOV, &pOV->m_sFirma1, pNV, &pNV->m_sFirma1);
	sp.Execute("Firma2", pOV, &pOV->m_sFirma2, pNV, &pNV->m_sFirma2);
	sp.Execute("Firma3", pOV, &pOV->m_sFirma3, pNV, &pNV->m_sFirma3);
	sp.Execute("Firma4", pOV, &pOV->m_sFirma4, pNV, &pNV->m_sFirma4);
	sp.Execute("Firma5", pOV, &pOV->m_sFirma5, pNV, &pNV->m_sFirma5);
	sp.Execute("Firma6", pOV, &pOV->m_sFirma6, pNV, &pNV->m_sFirma6);
	sp.Execute("Firma7", pOV, &pOV->m_sFirma7, pNV, &pNV->m_sFirma7);
	sp.Execute("Firma8", pOV, &pOV->m_sFirma8, pNV, &pNV->m_sFirma8);
	sp.Execute("Firma9", pOV, &pOV->m_sFirma9, pNV, &pNV->m_sFirma9);
	sp.Execute("ImmagineFirma", pOV, &pOV->m_sImmagineFirma, pNV, &pNV->m_sImmagineFirma);
	sp.Execute("IDUtenteEndox", pOV, &pOV->m_lIDUserEndox, pNV, &pNV->m_lIDUserEndox);
	sp.Execute("Libero", pOV, &pOV->m_bLibero, pNV, &pNV->m_bLibero);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMediciSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMediciSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMediciSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMediciSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CMediciSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

//Gabriel BUG 6225 - Lista DO
CString CMediciSet::GetNomeCognomeFromContatore(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("CONTATORE = %li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMediciSet::GetNomeCognomeFromContatore"))
	{
		if (!IsEOF())
		{
			return m_sNome + " " + m_sCognome;
		}

		CloseRecordset("CMediciSet::GetNomeCognomeFromContatore");
	}

	return "";
}