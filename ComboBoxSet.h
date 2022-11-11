#ifndef _COMBOBOXSET_H_
	#define _COMBOBOXSET_H_

#include "BaseSet.h"

class CComboBoxSet : public CBaseSet
{

	DECLARE_DYNAMIC(CComboBoxSet)

public:

	CComboBoxSet(long lComboDefine);

	long m_lContatore;
	CString m_sNomeTabella;
	CString m_sTesto;
	long m_lUO;
	BOOL m_bEliminato;

	// passo il contatore e mi ritorna il testo del relativo record //
	CString GetFieldText(long lContatore);

	// aggiunge una riga e ritorna il relativo contatore //
	long AddRow(CString sTesto);

	// elimina una riga specifica //
	BOOL DelRow(long lContatore);

	// modifica una riga specifica //
	BOOL EdtRow(long lContatore, CString sTesto);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

	// Sandro 22/12/2015 //
	CString GetComboTabellaBaseFilter(BOOL bSoloNomeTabella);

	//
	long m_lComboDefine;

};

#endif /* _COMBOBOXSET_H_ */