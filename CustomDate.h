#ifndef _CUSTOMDATE_H_
	#define _CUSTOMDATE_H_

// Mappatura dei bit per il campo m_lDate della classe CCustomDate
// x1111111 1xxxxxxx xxxxxxxx xxxxxxxx = 0..255 anni da sommare a 1900
// xxxxxxxx x1111xxx xxxxxxxx xxxxxxxx = 1..12 mesi
// xxxxxxxx xxxxx111 11xxxxxx xxxxxxxx = 1..31 giorni
// xxxxxxxx xxxxxxxx xx111xxx xxxxxxxx = 1..7 giorno della settimana
// xxxxxxxx xxxxxxxx xxxxx111 11xxxxxx = 0..23 ore
// xxxxxxxx xxxxxxxx xxxxxxxx xx111111 = 0..59 minuti

class CCustomDate : public CObject
{             

public:

	CCustomDate(BOOL initDate = FALSE, BOOL initTime = FALSE);
	CCustomDate(long lDate);
	CCustomDate(int nYear, int nMonth, int nDay, int nWeekday, int nHour, int nMinute);
	CCustomDate(const CCustomDate& dateSrc);
	CCustomDate(LPCSTR strDateSrc);
	
	static int  j_cumday[13];
	static int  v_monlen[13];

	static int	m_nLimitYearPrev;

	long FindCurrentTime(BOOL bSetup = FALSE, BOOL bTimeAlso = FALSE);	
												// ritorna la data corrente altrimenti 0
												// se il parametro è TRUE la data corrente
												// diverrà la data della classe CCustomData

	long 	GetDate() const;					// ritorna la data in formato compresso altrimenti 0
	CString GetDate(CString strFormat) const;	// ritorna la data in formato stringa altrimenti NULL
	CString GetDateForEdit(int nModalita) const;
	CString GetDateForPrint(int nModalita) const;
	int 	GetYear() const;					// anno della data corrente altrimenti 0
	int 	GetMonth() const;       			// mese dell'anno (1 = Jan) altrimenti 0
	int 	GetDay() const;         			// 1.. giorno del mese altrimenti 0
	int 	GetCurrentCentury() const;			// Restituisce il secolo di default in formato xx

	long 	GetTime() const;					// ritorna l'ora in formato compresso altrimenti 0
	int 	GetHour() const;         			// Ore
	int 	GetMinute() const;         			// Minuti
    
		// ritorna una distanza temporale in settimane + giorni con la seguente
		// mappatura dei bit:	11111111 11111xxx = settimane, 
		//						xxxxxxxx xxxxx111 = giorni
		// NB	questo metodo richiede un delta massimo di 8191 settimane e 7 giorni
		//		ritorna 0 in caso di overflow o Delta = 0
		//
		// Se Base = 0 allora il metodo considera la data interna della classe
		
	int		GetElapsedWeek(CCustomDate& Base, CCustomDate& Delta);
	int		GetElapsedWeek(long Base, long Delta);
	int		GetElapsedWeek(CCustomDate& Base, int Delta);
	int		GetElapsedWeek(int Delta, CCustomDate& Base);
	int		GetElapsedWeek(long Base, int Delta);
	int		GetElapsedWeek(int Delta, long Base);

		// dato un numero di giorni ritorna le settimane + giorni con la seguente
		// mappatura dei bit:	11111111 11111xxx = settimane, 
		//						xxxxxxxx xxxxx111 = giorni
		// NB	questo metodo richiede un delta massimo di 8191 settimane e 7 giorni
	int		GetWeeksAndDays(int nManyDays);

		// dato un numero settimane e di giorni ritorna le settimane + giorni compressi
	int		GetWeeksAndDays(int Weeks, int Days);

		// distanza in giorni
		// NB questo metodo richiede un delta massimo di 64K giorni
	int		GetElapsedDay(CCustomDate& Base, CCustomDate& Delta);

	// Questi metodi ritornano la data in formato "long" precedente altrimenti 0

	long    SetDateTime(CString sDateTime);		// Sandro 30/03/2016 // imposta data e ora in formato stringa (19781022 oppure 197810221234) //

	long 	SetDate(long lNewDate);				// imposta la data in formato compresso
	long 	SetDate(LPCSTR strNewData);			// imposta la data in formato stringa (22/10/1978)
	long 	SetYear(int nNewYear);				// nuovo anno dal 1900 al 2155 sottratto di 1900
	long 	SetMonth(int nNewMonth);			// mese dell'anno (1 = Gennaio)
	long 	SetDay(int nNewDay);				// giorno del mese 1..[31][30][29][28]

	long 	SetTime(LPCSTR strNewTime);			// imposta l'ora in formato stringa (12:34)
	long 	SetHour(int nNewHour);		// 1..23
	long 	SetMinute(int nNewMinute);	// 0..59
	
	// Imposta il secolo di default in formato xx altrimenti 0 = 19° secolo
	int 	SetCurrentCentury(int nNewCentury = 0);

	// time math
	const CCustomDate& operator=(const CCustomDate& timeSrc);

	CCustomDate  operator+(int days);           // ritorna una data
	CCustomDate  operator-(int days);			// ritorna una data
	long 		 operator-(CCustomDate& days);	// ritorna un numero di giorni
	CCustomDate& operator+=(int days);			// ritorna una data
	CCustomDate& operator-=(int days);			// ritorna una data
	
	long		ConvertDateInLong(int year, int month, int day);
	long		JulianDate(int yr, int mon, int day);
	BOOL		IconDate(const char * date,int *yr, int *mon, int *day);
	long 		DaysFrom(int year, int month, int day, int numdays);
	int 		DayOfWeek(int year,	int month,	int day);
	BOOL		IsValidDate(int yr, int mon, int day);

	BOOL		IconTime(const char * time,int *hour, int *min);
	BOOL		IsValidTime(int hour, int min);

	// serialization
#ifdef _DEBUG
	friend CDumpContext& AFXAPI operator<<(CDumpContext& dc, CCustomDate date);
#endif
	friend CArchive& AFXAPI operator<<(CArchive& ar, CCustomDate date);
	friend CArchive& AFXAPI operator>>(CArchive& ar, CCustomDate& rDate);

private:

	long	m_lDate;
	int		m_nCurrentCentury;
};

#endif /* _CUSTOMDATE_H_ */