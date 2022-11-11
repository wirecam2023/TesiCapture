#ifndef _FARMACIGRUPPIRICBULKSET_H_
	#define _FARMACIGRUPPIRICBULKSET_H_

class CFarmaciGruppiRicBulkSet : public CRecordset
{
	DECLARE_DYNAMIC(CFarmaciGruppiRicBulkSet)

public:

	CFarmaciGruppiRicBulkSet();

	void CaricaInMemoria();

private:

	virtual void DoBulkFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	CString GetTextField(LPTSTR szField, long* pFieldSize, int iIndex);

	long* m_pID;
	LPTSTR m_pDescrizione;

	long* m_pIDLength;
	long* m_pDescrizioneLength;

};

#endif /* _FARMACIGRUPPIRICBULKSET_H_ */