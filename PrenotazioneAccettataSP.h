#ifndef _PRENOTAZIONEACCETTATASP_H_
	#define _PRENOTAZIONEACCETTATASP_H_

#include "AfxDB.h"

class CPrenotazioneAccettataSP : protected CRecordset // solo le Stored Procedure possono essere derivate da CRecordset //
{

public:

	CPrenotazioneAccettataSP();
	DECLARE_DYNAMIC(CPrenotazioneAccettataSP)

	void Move(long nRows, WORD wFetchType) {};
	BOOL Execute(long lIDPrenotazione);

protected:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	// INPUT //
	long m_lIDPrenotazione;

};

#endif /* _PRENOTAZIONEACCETTATASP_H_ */