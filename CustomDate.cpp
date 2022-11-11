#include "stdafx.h"
#include "Endox.h"
#include "CustomDate.h"

#include "common.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CCustomDate::m_nLimitYearPrev = 30;
int CCustomDate::j_cumday[13] = {0,   0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334};
int CCustomDate::v_monlen[13] = {0,  31,  28,  31,  30,  31,  30,  31,  31,  30,  31,  30,  31};

CCustomDate::CCustomDate(BOOL initDate, BOOL initTime)
{
	m_lDate = 0;
	SetCurrentCentury();

	if (initDate)
		FindCurrentTime(initDate, initTime);
}

CCustomDate::CCustomDate(long lDate)
{
	m_lDate = 0;
	SetCurrentCentury();

	m_lDate = lDate;
}

CCustomDate::CCustomDate(int nYear, int nMonth, int nDay, int nWeekDay, int nHour, int nMinute)
{
	m_lDate = 0;
	SetCurrentCentury();

	if (nYear >= 0)
	{
		if (nYear < 100)
		{
			if (nYear > m_nLimitYearPrev && GetCurrentCentury() > 19)
				nYear += (GetCurrentCentury()-1) * 100;
			else
				nYear += GetCurrentCentury() * 100;
		}

		nYear -= 1900;
	}

	if (nYear<0 || nYear>255) 
		nYear = 0;
	
	m_lDate = long(	(long(0L)       << 31) | 
					(long(nYear)    << 23) | 
			  		(long(nMonth)   << 19) | 
			  		(long(nDay)     << 14) | 
			  		(long(nWeekDay) << 11) | 
			  		(long(nHour)    << 6 ) | 
			  		(long(nMinute)       ));
}

CCustomDate::CCustomDate(const CCustomDate& dateSrc)
{
	m_lDate = 0;
	m_nCurrentCentury = dateSrc.GetCurrentCentury();

	m_lDate = dateSrc.GetDate();
}

CCustomDate::CCustomDate(LPCSTR strDateSrc)
{
	m_lDate = 0;
	SetCurrentCentury();

	if (!SetDate(strDateSrc))
		m_lDate	= 0;
}

const CCustomDate& CCustomDate::operator=(const CCustomDate& timeSrc)
{ 
	m_nCurrentCentury = timeSrc.m_nCurrentCentury;

	m_lDate = timeSrc.m_lDate;

	return *this; 
}

long CCustomDate::FindCurrentTime(BOOL bSetup, BOOL bTimeAlso)
{
	SYSTEMTIME	SystemTime;
	long 		lDate;

	GetLocalTime(&SystemTime);	

	lDate = ((long(SystemTime.wYear - 1900)	<< 23) |
			 (long(SystemTime.wMonth)		<< 19) |
			 (long(SystemTime.wDay)			<< 14));

	if (bTimeAlso)
	{
		lDate |= long ( (long(SystemTime.wHour)    << 6) |
				 		(long(SystemTime.wMinute)));
	}

	if (bSetup)
		m_lDate = lDate;

	return lDate;
}

long CCustomDate::GetDate() const
{
	return m_lDate;
}

CString CCustomDate::GetDate(CString strFormat) const // vedere help di "strftime" per lista dei formati utilizzabili //
{
	char    szBuffer[128];
	tm		ExtendedTime;
	CString sendOut = "";
	
    ExtendedTime.tm_sec   = 0;
    ExtendedTime.tm_min   = GetMinute();
    ExtendedTime.tm_hour  = GetHour(); 
    ExtendedTime.tm_wday  = 0;
    ExtendedTime.tm_yday  = 0;
	ExtendedTime.tm_isdst = -1;
    
    ExtendedTime.tm_mday = GetDay();
    ExtendedTime.tm_mon  = GetMonth() - 1;
	ExtendedTime.tm_year = GetYear() - 1900;

	// Sandro 30/02/2011 // cambio la condizione per il nuovo salvataggio della sola ora (senza data) //
	if ((m_lDate > 0) && (m_lDate < MAXUINT))
	{
		if (ExtendedTime.tm_mday < 1)
			ExtendedTime.tm_mday = 1;
		if (ExtendedTime.tm_mday > 31)
			ExtendedTime.tm_mday = 31;

		if (ExtendedTime.tm_mon < 0)
			ExtendedTime.tm_mon = 0;
		if (ExtendedTime.tm_mon > 11)
			ExtendedTime.tm_mon = 11;

		if (!strftime(szBuffer, sizeof(szBuffer), (LPCSTR)strFormat, &ExtendedTime))
			szBuffer[0] = '\0';

		sendOut = szBuffer;
	}

	return sendOut;
}

CString CCustomDate::GetDateForEdit(int nModalita) const
{
	CString sReturn = "";

	switch(nModalita)
	{
		case DATA_ORA:
		{
			sReturn = GetDate("%d/%m/%Y - %H:%M");
			break;
		}
		case SOLO_DATA:
		{
			sReturn = GetDate("%d/%m/%Y"); 
			break;
		}
		case SOLO_ORA:
		{
			sReturn = GetDate("%H:%M"); 
			break;
		}
	}

	return sReturn;
}

CString CCustomDate::GetDateForPrint(int nModalita) const
{
	CString sReturn = "";

	switch(nModalita)
	{
		case DATA_ORA:
		{
			sReturn = GetDate("%d/%m/%Y %H:%M");
			break;
		}
		case SOLO_DATA:
		{
			sReturn = GetDate("%d/%m/%Y"); 
			break;
		}
		case SOLO_ORA:
		{
			sReturn = GetDate("%H:%M"); 
			break;
		}
	}

	return sReturn;
}

int CCustomDate::GetYear() const
{
	// year mask : 01111111 10000000 00000000 00000000
	
	long sendOut = 0x7F800000;

    sendOut &= m_lDate;
    sendOut >>= 23;
    
	sendOut += 1900;

    return ((int) sendOut);
}

int CCustomDate::GetMonth() const
{
	// month mask : 00000000 01111000 00000000 00000000
	
	long sendOut = 0x00780000;

    sendOut &= m_lDate;
    sendOut >>= 19;
    
    return ((int)sendOut);
}

int CCustomDate::GetDay() const
{
	// month mask : 00000000 00000111 11000000 00000000
	
	long sendOut = 0x0007C000;

    sendOut &= m_lDate;
    sendOut >>= 14;        
    
    return ((int) sendOut);
}

int CCustomDate::GetCurrentCentury() const
{
	return m_nCurrentCentury;
}

int CCustomDate::GetHour() const
{
	// hour mask : 00000000 00000000 00000111 11000000
	
	long sendOut = 0x000007C0;

    sendOut &= m_lDate;
    sendOut >>= 6;        
    
    return ((int) sendOut);
}

long CCustomDate::GetTime() const
{
	long hour = GetHour();
	long min  = GetMinute();
	
	return (hour << 6) + min;
}

int CCustomDate::GetMinute() const
{
	// minute mask : 00000000 00000000 00000000 00111111
	
	long sendOut = 0x0000003F;

    sendOut &= m_lDate;
    
    return ((int) sendOut);
}

// Sandro 30/03/2016 // imposta data e ora in formato stringa (19781022 oppure 197810221234) //
long CCustomDate::SetDateTime(CString sDateTime)
{
	m_lDate = 0;

	if (sDateTime.GetLength() == 8) // solo data //
	{
		SetDate(sDateTime.Right(2) + "/" + sDateTime.Mid(4, 2) + "/" + sDateTime.Left(4));
	}
	else if (sDateTime.GetLength() == 12) 
	{
		if (SetDate(sDateTime.Mid(6, 2) + "/" + sDateTime.Mid(4, 2) + "/" + sDateTime.Left(4)) > 0)
		{
			SetTime(sDateTime.Mid(8, 2) + ":" + sDateTime.Mid(10, 2));
		}
	}
	else if (sDateTime.GetLength() == 14)
	{
		if (SetDate(sDateTime.Mid(6, 2) + "/" + sDateTime.Mid(4, 2) + "/" + sDateTime.Left(4)) > 0)
		{
			SetTime(sDateTime.Mid(8, 2) + ":" + sDateTime.Mid(10, 2) + ":" + sDateTime.Mid(12, 2));
		}
	}

	return m_lDate;
}

long CCustomDate::SetDate(long lNewDate)
{
	long savedDate = m_lDate;

	m_lDate = lNewDate;

	if (!IsValidDate(GetYear(), GetMonth(), GetDay()))
	{
		m_lDate = savedDate;
		return 0;
    }
	
	return m_lDate;
}

long CCustomDate::SetDate(LPCSTR newData)
{
	int nYear, nMonth, nDay;

	if (!IconDate(newData, &nYear, &nMonth, &nDay))
		return 0;
	
    if (!SetDay(nDay))
    	return 0;

	if (!SetMonth(nMonth))
    	return 0;
    
	if (!SetYear(nYear))
		return 0;

	return m_lDate;
}

long CCustomDate::SetTime(LPCSTR newTime)
{
	int nHour, nMinute;

	if (!IconTime(newTime, &nHour, &nMinute))
		return 0;
	
    if (!SetHour(nHour))
    	return 0;

	if (!SetMinute(nMinute))
    	return 0;
	
	return m_lDate;
}

long CCustomDate::SetYear(int nNewYear)
{
	// year mask : 01111111 10000000 00000000 00000000

	nNewYear -= 1900;

	long AdjustedYear = (long(nNewYear)) << 23;
	
	m_lDate &= 0x807FFFFF;
    m_lDate |= AdjustedYear;

   	return m_lDate;
}

long CCustomDate::SetMonth(int nNewMonth)
{
	// month mask : 00000000 01111000 00000000 00000000
	
	long AdjustedMonth = (long(nNewMonth)) << 19;
	
	m_lDate &= 0xFF87FFFF;
    m_lDate |= AdjustedMonth;
    
    return m_lDate;
}

long CCustomDate::SetDay(int nNewDay)
{
	// month mask : 00000000 00000111 11000000 00000000
	
	long AdjustedDay = (long(nNewDay)) << 14;
	
	m_lDate &= 0xFFF83FFF;
    m_lDate |= AdjustedDay;
    
    return m_lDate;
}

int CCustomDate::SetCurrentCentury(int nNewCentury)
{
	if (nNewCentury)
	{
		m_nCurrentCentury = nNewCentury;
	}
	else
	{
		SYSTEMTIME SystemTime;

		GetLocalTime(&SystemTime);	

		m_nCurrentCentury = (long) (SystemTime.wYear / 100);
	}

	return m_nCurrentCentury;
}

long CCustomDate::SetHour(int nNewHour)
{
	// hour mask : 00000000 00000000 00000111 11000000
	
	long AdjustedDay = (long(nNewHour)) << 6;
	
	m_lDate &= 0xFFFFF83F;
    m_lDate |= AdjustedDay;
    
    return m_lDate;
}

long CCustomDate::SetMinute(int nNewMinute)
{
	// minute mask : 00000000 00000000 00000000 00111111
	
	long AdjustedDay = long(nNewMinute);
	
	m_lDate &= 0xFFFFFFC0;
    m_lDate |= AdjustedDay;
    
    return m_lDate;
}

int	CCustomDate::GetWeeksAndDays(int nManyDays)
{
	int weeks;
	int days;

	if (!nManyDays)
		return 0;			// 0 giorni non sono un periodo
	else
	{
	    weeks = int(nManyDays / 7);
        
        if (weeks > MAX_WEEK)	// ci sono solo 13 bit per le settimane !
        	return 0;		// quindi questo è un caso di overflow
        
	    weeks <<= 3;
	    
        days = int(nManyDays % 7);
	}
        
	return (weeks | days);
}

int	CCustomDate::GetElapsedWeek(CCustomDate& Base, CCustomDate& Delta)
{   
	if (!&Delta)
		return 0;			//  il delta è 0 quindi non c'è periodo

	long a;

	if (!&Base)
		a = ConvertDateInLong(GetYear(), 
							  GetMonth(), 
							  GetDay());
	else
		a = Base.ConvertDateInLong(Base.GetYear(), 
								   Base.GetMonth(), 
								   Base.GetDay());

	long b = Delta.ConvertDateInLong(Delta.GetYear(), 
									 Delta.GetMonth(), 
									 Delta.GetDay());

	long diff = labs(a - b);
	
	if (diff > MAX_WEEK)
		return 0;	// si è superata la massima rappresentazione consentita in 2 byte
					// 13 bit per le settimane e 3 per i giorni
	
	return GetWeeksAndDays((int) diff);
}

int	CCustomDate::GetElapsedWeek(long Base, long Delta)
{
	long savedDate = GetDate();

	if (Base & 0x7FFFC000)	// per ora verifica solo i campi AA MM GG
		SetDate(Base);
		
	int BaseYear	= GetYear();
	int BaseMonth	= GetMonth();
	int BaseDay		= GetDay();

	if (Delta & 0x7FFFC000)	// per ora verifica solo i campi AA MM GG
		SetDate(Delta);
	else
		return 0;			//  il delta è 0 quindi non c'è periodo
	
	int	DeltaYear	= GetYear();
	int	DeltaMonth	= GetMonth();
	int	DeltaDay	= GetDay();
    
    SetDate(savedDate);		// ripristina la data iniziale della classe
    
	long a = ConvertDateInLong(BaseYear, BaseMonth, BaseDay);
	
	long b = ConvertDateInLong(DeltaYear, DeltaMonth, DeltaDay);

	long diff = labs(a - b);
	
	if (diff > MAX_WEEK)
		return 0;	// si è superata la massima rappresentazione consentita in 2 byte
					// 13 bit per le settimane e 3 per i giorni
	
	return GetWeeksAndDays((int) diff);
}

int	CCustomDate::GetElapsedWeek(CCustomDate& Base, int Delta)
{
	if (!Delta)
		return 0;			// il delta è 0 quindi non c'è periodo

	long a;

	if (&Base)
		a = Base.ConvertDateInLong(Base.GetYear(), Base.GetMonth(), Base.GetDay());
	else
		a = ConvertDateInLong(GetYear(), GetMonth(), GetDay());
	
	long diff = labs(a - Delta);
	
	if (diff > MAX_WEEK)
		return 0;	// si è superata la massima rappresentazione consentita in 2 byte
					// 13 bit per le settimane e 3 per i giorni
	
	return GetWeeksAndDays((int) diff);
}

int	CCustomDate::GetElapsedWeek(int Delta, CCustomDate& Base)
{
	return GetElapsedWeek(Base, Delta);
}

int	CCustomDate::GetElapsedWeek(long Base, int Delta)
{
	if (!Delta)
		return 0;				// il delta è 0 quindi non c'è periodo
	
	long savedDate = GetDate();

	if (Base & 0x7FFFC000)		// per ora verifica solo i campi AA MM GG
		SetDate(Base);
		
	int BaseYear	= GetYear();
	int BaseMonth	= GetMonth();
	int BaseDay		= GetDay();

	if (Base & 0x7FFFC000)		// per ora verifica solo i campi AA MM GG
	    SetDate(savedDate);		// ripristina la data iniziale della classe
    
	long a = ConvertDateInLong(BaseYear, BaseMonth, BaseDay);
	
	long diff = labs(a - Delta);
	
	if (diff > MAX_WEEK)
		return 0;	// si è superata la massima rappresentazione consentita in 2 byte
					// 13 bit per le settimane e 3 per i giorni
	
	return GetWeeksAndDays((int) diff);
}

int	CCustomDate::GetElapsedWeek(int Delta, long Base)
{
	return GetElapsedWeek(Base, Delta);
}

int	CCustomDate::GetWeeksAndDays(int Weeks, int Days)
{
    // ci sono 13 bit per le settimane e 3 per i giorni !
    // quindi questo è un caso di overflow

    if (Weeks > MAX_WEEK || Days > 7)
    	return 0;
    
	return (Weeks << 3 | Days);
}

int	CCustomDate::GetElapsedDay(CCustomDate& Base, CCustomDate& Delta)
{
	long a = Base.ConvertDateInLong(GetYear(), GetMonth(), GetDay());
	long b = Delta.ConvertDateInLong(GetYear(), GetMonth(), GetDay());

	return abs((int)(a - b));
}

BOOL CCustomDate::IconTime(const char * time,int *hour, int *min)
{
	char *sptr;	// pointer to date 
	int  j,slash;   // work variables 
	
	*hour = 0;
	*min  = 0;
	slash = 0;
	
	if ((time == NULL) || (strlen(time) < 1) || (strlen(time) > 5))
		return FALSE;
	
	for( sptr = (char *)time,j = 0; *sptr != '\0'  ; sptr++, j++)
	{
		if ( *sptr == ':' || *sptr == '.' || *sptr == ',' || *sptr == ' ')
		{  	
			if (slash == 0 )
			{
				slash = j;            // location of first slash 
			}
		}
		else
			if ( *sptr < '0' || *sptr > '9') return FALSE; // invalid characters 
	}
	/* verify valid positions for slashes */
	if (slash == 0) return FALSE;
	
	*hour = (int) ( time[0] - '0' );  // based on ASCII codes 
	if ( slash != 1 )
	{
		if ( slash != 2 ) return FALSE;   // not in 1 or 2 char position 
		*hour *= 10;
		*hour += (int) ( time[1] - '0' );
	}

	sptr = (char *)&time[slash+1];
	while(*sptr != '\0')
	{
		*min *= 10;
		*min += (int) (*sptr - '0' );
		sptr++;
	}

	return (IsValidTime(*hour,*min));
}


BOOL CCustomDate::IsValidTime(int hour, int min)
{
	if ( hour < 0 || hour > 23) return FALSE;
	if ( min  < 0 || min  > 59) return FALSE;
	
	return TRUE;
}

BOOL CCustomDate::IconDate(const char * date,int *yr, int *mon, int *day)
{
	char *sptr;
	int j;
	int slash1;
	int slash2;
	
	slash1 = 0;
	slash2 = 0;

	if ((date == NULL) || (strlen(date) < 1) || (strlen(date) > 10))
		return FALSE;

	for( sptr = (char *)date,j = 0; *sptr != '\0'  ; sptr++, j++)
	{
		if ( *sptr == '-' || *sptr == '/' || *sptr == '.' || *sptr == ' ')
		{  	
			if (slash1 == 0 )
			{
				slash1 = j;            // location of first slash 
			}
			else
			{
				if (slash2 != 0)       // do we have 2 '/' already 
					return FALSE;
				else
					slash2 = j;	// location of second slash 
			}
		}
		else
			if ( *sptr < '0' || *sptr > '9') return FALSE; // invalid characters 
	}
	
	if (slash1 == 0 && slash2 == 0)
	{
		//ho scritto solo l'anno
		*day = 1;
		*mon = 1;
	
		slash2 = -1;
	}
	else
	{
		if (slash1 != 0 && slash2 == 0)
		{
			//ho scritto solo mese ed anno
			*day = 1;
		
			slash2 = slash1;
			slash1 = -1;
		}
		else
		{
			if (slash1 == 0 || slash2 == 0 || slash1 == slash2 - 1) return FALSE;
			if (date[slash1] != date[slash2]) return FALSE; /* must use same delimiter */

			*day = (int) ( date[0] - '0' );  /* based on ASCII codes */
			if ( slash1 != 1 )
			{
				if ( slash1 != 2 ) return FALSE;   /* not in 1 or 2 char position */
				*day *= 10;
				*day += (int) ( date[1] - '0' );
			}
		}
	
		*mon = (int) ( date[slash1+1] - '0' );
		if ( slash2 != slash1 + 2)
		{
			if (slash2 != slash1 + 3) return FALSE;
			*mon *= 10;
			*mon += (int) ( date[slash1+2] - '0' );
		}
	}

	sptr = (char *)&date[slash2+1];
	*yr = (int) ( *sptr - '0' );
	sptr++;
	while(*sptr != '\0')
	{
		*yr *= 10;
		*yr += (int) ( *sptr - '0' );
		sptr++;
	}

	if (*yr < 0 || *yr > 2155) return FALSE;

	//se ho scritto solo l'anno e l'anno vale 0...
	if (slash2 == -1)
	{
		if (*yr == 0)
		{
			*day = 0;
			*mon = 0;
		
			return FALSE;
		}
	}

	if (*yr < 100)
	{
		if (*yr > m_nLimitYearPrev && GetCurrentCentury() > 19)
			*yr += (GetCurrentCentury()-1) * 100;
		else
			*yr += GetCurrentCentury() * 100;
	}

	return (IsValidDate(*yr,*mon,*day));
}

BOOL CCustomDate::IsValidDate(int yr, int mon, int day)
{
	int maxDayInMonth = 0;

	if (yr < 0)
		return FALSE;

	if (yr < 100)
	{
		if (yr > m_nLimitYearPrev && GetCurrentCentury() > 19)
			yr += (GetCurrentCentury()-1) * 100;
		else
			yr += GetCurrentCentury() * 100;
	}

	if (yr<1900 || yr>2155) 
		return FALSE;

	if (mon >= 1 && mon <= 12)
		maxDayInMonth = v_monlen[mon];

	if (mon == 2)
	{
		if ((((yr % 4) == 0)&&((yr % 100) != 0))||((yr % 400) == 0))
			maxDayInMonth = 29;
		else
			maxDayInMonth = 28;
	}

	if ( (mon < 1 || mon > 12) || (day < 1 || day > maxDayInMonth) )
		return FALSE;
	else
		return TRUE;
}

long CCustomDate::ConvertDateInLong(int year, int month, int day)
{
	//year deve essere un anno completo 1998, 2001 etc...
	//se è <=99 diventa 1978 o 2078 a seconda dell'anno corrente...
	
	int 	y1; /* century part of year */
	int 	y2; /* rest of year */
	int 	n=0; /* leap year factor */
	int 	leapflag=1;  /* check if leap or not */
	long 	c=0;
	long 	c1=0; /* temp variables */
	
	// Attenzione che dopo il 2000 se si specificano anni a 2 cifre verrà 
	// considerato come anno base il 1900. Vedi controllo seguente
	if (year > 100)
	{
		y1 = year / 100;
		y2 = year % 100;
	}
	else
	{
		if (year > m_nLimitYearPrev && GetCurrentCentury() > 19)
		{
			y1 = GetCurrentCentury()-1;
			y2 = year;
		}
		else
		{
			y1 = GetCurrentCentury();
			y2 = year;
		}
	}
	
	/* year range check */
	if ((y1 < 19) || (y1 > 99)) return(0);
	if ((y2 < 0)  || (y2 > 99)) return(0);
	
	/* month range check */
	if ((month < 1) || (month > 12)) return(0);
	/* check how many leap year between the given date and 1/1/1900 */
	n = y2/4;
	if ((y2%4)==0 && (n!=0))  --n;
	if ((y1==20) && (y2>0))  ++n;	/* because 1900 is not a leap, but 2000 is a leap */

	/* day range check */
	c1 = v_monlen[month];

	if (month == 2)
  	{
		if (leapflag == 1) 
			c1 = 29;
		else 
			c1 = 28;
	}
	if ((day < 1) || (day > c1)) return(0);

	/* get the days */
	c = (long)365*y2+n;
	if (y1==20)
		c += 36524;	/* 36524 is the total days in 20 century */
	c1 = JulianDate(year,month,day);
	c += c1;
	return(c);
}

/* return the day of the year (Julianized date) */
long CCustomDate::JulianDate(int yr, int mon, int day)
{
	int	maxDayInMonth = 0;
	int leap = 0;  /* set = 1 if leap year and mon > 2; otherwise 0 */

	if (yr < 0)
		return(-1);

	// Attenzione che dopo il 2000 se si specificano anni a 2 cifre verrà 
	// considerato come anno base il 1900. Vedi controllo seguente
	if (yr < 100) 
	{
		if (yr > m_nLimitYearPrev && GetCurrentCentury() > 19)
			yr += (GetCurrentCentury()-1) * 100;
		else
			yr += GetCurrentCentury() * 100;
	}

	if (yr<1900 || yr>2155) 
		return FALSE;

	if (mon >= 1 && mon <= 12)
		maxDayInMonth = v_monlen[mon];

	if (mon == 2)
	{
		if ((((yr % 4) == 0)&&((yr % 100) != 0))||((yr % 400) == 0))
			maxDayInMonth = 29;
		else
			maxDayInMonth = 28;
	}

	if ( (mon < 1 || mon > 12) || (day < 1 || day > maxDayInMonth) )
		return(-1);

	if ((((yr % 4) == 0)&&((yr % 100) != 0))||((yr % 400) == 0)) 
	{
		//v_monlen[2] = 29;
		
		if (mon > 2)
			leap = 1;
		//else
		//	leap = 0;	
	}
	else
	{
		//v_monlen[2] = 28;
		//leap = 0;
	}
	
	return(leap + j_cumday[mon] + day);
}

CCustomDate CCustomDate::operator+(int days)
{ 
	return DaysFrom(GetYear(), GetMonth(), GetDay(), days);
}

CCustomDate& CCustomDate::operator+=(int days)
{	
	int a = GetYear();
	int m = GetMonth();
	int g = GetDay();

	long res = DaysFrom(a, m, g, days);
	
	SetDate(res);
	return *this;
}

CCustomDate CCustomDate::operator-(int days)
{
	return DaysFrom(GetYear(), GetMonth(), GetDay(), -days);
}

long CCustomDate::operator-(CCustomDate& days)
{
	long a = ConvertDateInLong(GetYear(), GetMonth(), GetDay());
	long b = days.ConvertDateInLong(days.GetYear(), days.GetMonth(), days.GetDay());

	return labs(a - b);
}

CCustomDate& CCustomDate::operator-=(int days)
{
	SetDate(DaysFrom(GetYear(), GetMonth(), GetDay(), -days));
	return *this;
}


#ifdef _DEBUG
CDumpContext& AFXAPI operator<<(CDumpContext& dc, CCustomDate date)
{
	return dc << "CCustomDate(\"I'm sorry, this feature is not implemented\")";
}
#endif

CArchive& AFXAPI operator<<(CArchive& ar, CCustomDate date)
{
	return ar << (DWORD) date.m_lDate;
}
CArchive& AFXAPI operator>>(CArchive& ar, CCustomDate& rDate)
{
	return ar >> (DWORD&) rDate.m_lDate;
}

/* function to return a new date from a date & a # of days to be added */
long CCustomDate::DaysFrom(int year, int month, int day, int numdays)
{
	//year deve essere un anno completo 1998, 2001 etc...
	//se è <=99 diventa 1978 o 2078 a seconda dell'anno corrente...

	int y1; 		// century part of the year
	int y2; 		// remaining part of the year
	int m1; 		// month part to pass to strdate
	int d1; 		// day part to pass to strdate
	int n; 			// temp variable for leap year added day
	int j; 			// temp variable for processing # of days
	int y3; 		// year part to pass strdate
	int y;
	int k; 			// temp variable to be used for incrementing
	int l; 			// temp variable for limit on for-loop counter
	
	j = DayOfWeek(year, month, day);

	if (j == 0) 
		return 0L;

	// Attenzione che dopo il 2000 se si specificano anni a 2 cifre verrà 
	// considerato come anno base il 1900. Vedi controllo seguente

	/* determine # of days in the year */
	if (year > 100)
	{
		y1 = year / 100;
		y2 = year % 100;
	}
	else
	{
		if (year > m_nLimitYearPrev && GetCurrentCentury() > 19)
		{
			y1 = GetCurrentCentury()-1;
			y2 = year;
		}
		else
		{
			y1 = GetCurrentCentury();
			y2 = year;
		}
	}

	m1 = month;
	d1 = -1;
	j = numdays;

	if (numdays == 0) 
		return 0L;	
	
	if (numdays < 0) k = -1;
	  else k = 1;

	/* start leaping thru */
	for( ; ; )
	{
		if (m1 == 2)
		{
			y = (y1 * 100) + y2;

			if ((((y % 4) == 0)&&((y % 100) != 0))||((y % 400) == 0))
				n = 2;
			else
				n = 1;
		}
		else 
		{
			n = 1;
		}

		if (k == 1)
			l = v_monlen[m1] + n;
		else
			l = 0;
		
		/* set day variable */
		if (d1 == -1)
			d1 = day + k;
		else 
			if (k == 1) 
				d1 = 1;
		    else
		    	d1 = v_monlen[m1] + n - 1;
		
		for( ; d1 != l; d1 = d1 +k)
		{
			j = j - k;

			if (j == 0) 
				break;
		}

		if (j == 0) 
			break;

		/* reset month and year if necessary */
		m1 = m1 + k;
		if ((m1 == 13) || (m1 == 0))
		{
			m1 = m1 - (12 * k);
			y2 = y2 + k;

			if ((y2 == 100)||( y2 == -1))
			{
				y2 = y2 - (100 * k);
				y1 = y1 + k;
			}
		}

		continue;
	}

	/* call date routine to put date in correct format */

	y3 = (y1 * 100) + y2;
	
	long savedDate = GetDate();

	SetYear(y3);
	SetMonth(m1);
	SetDay(d1);

	long sendOut = GetDate();
	
	SetDate(savedDate);
	
	// Bisogna aggiornare anche il giorno e la settimana dell'anno
    
	//if (j < 0) 
	//	return 0;

	return sendOut;
}

/* function to determine day of the week for a date */
int CCustomDate::DayOfWeek(int year,	int month,	int day)
{
	//year deve essere un anno completo 1998, 2001 etc...

	int w; /* return value (day of the week ) */
	long int c; /* temp variable */
	long int condate(); /* convert to day code function */

	c = ConvertDateInLong(year, month, day);

	if (c == 0) 
		return 0 ;

	w = int(c % 7);			// occhio se funziona !!!!
	
	if (w==0)
		w=7;

	return w ;
}