#ifndef _MEDICISET_H_
	#define _MEDICISET_H_

#include "BaseSet.h"

#define _FIRMA_BMP_MAX_LENGTH 2*1024*1024

class CMediciSet : public CBaseSet
{

	DECLARE_DYNAMIC(CMediciSet)

public:

	CMediciSet();

	long m_lContatore;
	CString m_sCodice;
	CString m_sCodice3L3N; //Julio Login SEGU
	CString	m_sTitolo;
	CString	m_sCognome;
	CString	m_sNome;
	CString m_sCodiceFiscale;
	CString	m_sVia;
	CString	m_sCitta;
	CString	m_sCAP;
	CString	m_sProvincia;
	CString	m_sTelefono;
	CString m_sFirma0;
	CString m_sFirma1;
	CString m_sFirma2;
	CString m_sFirma3;
	CString m_sFirma4;
	CString m_sFirma5;
	CString m_sFirma6;
	CString m_sFirma7;
	CString m_sFirma8;
	CString m_sFirma9;
	CString m_sImmagineFirma;
	long m_lIDUserEndox;
	BOOL m_bLibero;
	long m_lUO;
	BOOL m_bEliminato;

	// passo il contatore e mi ritorna il dato del relativo record //
	CString GetCodiceFiscaleFromContatore(long lContatore);
	CString GetCognomeNomeFromContatore(long lContatore);
	CString GetFieldFirmaFromContatore(long lContatore, long lRigaFirma);
	CString GetFieldTextFromContatore(long lContatore);
	BOOL IsLiberoFromContatore(long lContatore);
	BOOL IsImmagineFirmaEmpty(long lContatore);

	// Set
	BOOL SetCodice(long lID, CString sCodice);
	CString GetCodice3L3NFromUserID(long lUserID); //Julio Login SEGU
	BOOL SetImmagineFirma(long lID, CString sImmagineFirma);
	BOOL UpdateInformation(long lID, CString sNome, CString sCodiceFiscale, CString sFirma, CString sCodice3L3N, CString sCodiceSEGU); //Julio Login SEGU

	// passo l'ID utente e mi torna il dato del relativo record //
	CString GetCodiceFiscaleFromUserID(long lUserID);
	CString GetCodiceFromUserID(long lUserID);
	CString GetCognomeNomeFromUserID(long lUserID);
	long GetContatoreFromUserID(long lUserID);
	CString GetFieldFirmaFromUserID(long lUserID, long lRigaFirma);
	void GetUserDataFromUserID(long lUserID, CString* pStrMedicoCognome, CString* pStrMedicoNome, CString* pStrMedicoCodFisc);
	long GetContatoreFromCodice(CString codice);

	long FleuryTrans(CString sCognome, CString sNome);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	virtual CString GetDefaultSQL();

	//Gabriel BUG 6225 - Lista DO
	CString GetNomeCognomeFromContatore(long lContatore);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _MEDICISET_H_ */