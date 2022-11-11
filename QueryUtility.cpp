#include "stdafx.h"
#include "Endox.h"
#include "QueryUtility.h"

#include "ComboBoxSet.h"
#include "CustomDate.h"

#include "ExportCSV.h"
#include "ExportFileDlg.h"
#include "ExportExcel.h"
#include "ExportHtml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CQueryUtility::CQueryUtility(void)
{
}

void CQueryUtility::GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idDateA)
{
	CString strTemp;
	
	CString strDa, strA;
	pParentWnd->GetDlgItemText(idDateDa, strDa);
	pParentWnd->GetDlgItemText(idDateA, strA);

	CCustomDate dataDa(strDa), dataA(strA);

	if (dataDa.GetDate() > 0)
	{
		CCustomDate dataTemp(dataDa.GetYear(), dataDa.GetMonth(), dataDa.GetDay(), 0, 0, 0);
		strTemp.Format("%s >= %li", strField, dataTemp.GetDate());
	}
	else
		strTemp.Empty();

	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}

	if (dataA.GetDate() > 0)
	{
		CCustomDate dataTemp(dataA.GetYear(), dataA.GetMonth(), dataA.GetDay(), 0, 23, 59);
		strTemp.Format("%s <= %li", strField, dataTemp.GetDate());
	}
	else
		strTemp.Empty();

	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

void CQueryUtility::GetCustomDateFilter(long* pData1, long* pData2, CWnd* pParentWnd, UINT idDateDa, UINT idDateA)
{
	CString strDa, strA;
	pParentWnd->GetDlgItemText(idDateDa, strDa);
	pParentWnd->GetDlgItemText(idDateA, strA);

	CCustomDate dataDa(strDa), dataA(strA);

	if (dataDa.GetDate() > 0)
	{
		CCustomDate dataTemp(dataDa.GetYear(), dataDa.GetMonth(), dataDa.GetDay(), 0, 0, 0);
		*pData1 = dataTemp.GetDate();
	}

	if (dataA.GetDate() > 0)
	{
		CCustomDate dataTemp(dataA.GetYear(), dataA.GetMonth(), dataA.GetDay(), 0, 23, 59);
		*pData2 = dataTemp.GetDate();
	}
}

void CQueryUtility::GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA)
{
	CString strTemp;
	
	CString strDateDa, strDateA, strTimeDa, strTimeA;
	pParentWnd->GetDlgItemText(idDateDa, strDateDa);
	pParentWnd->GetDlgItemText(idTimeDa, strTimeDa);
	pParentWnd->GetDlgItemText(idDateA, strDateA);
	pParentWnd->GetDlgItemText(idTimeA, strTimeA);

	CCustomDate dataDa(strDateDa), dataA(strDateA);

	if (dataDa.GetDate() > 0)
	{
		long lHour = 0, lMinute = 0;
		if (!GetTimeFromString(strTimeDa, &lHour, &lMinute))
		{
			lHour = 0;
			lMinute = 0;
		}

		CCustomDate dataTemp(dataDa.GetYear(), dataDa.GetMonth(), dataDa.GetDay(), 0, lHour, lMinute);
		strTemp.Format("%s >= %li", strField, dataTemp.GetDate());
	}
	else
		strTemp.Empty();

	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}

	if (dataA.GetDate() > 0)
	{
		long lHour = 0, lMinute = 0;
		if (!GetTimeFromString(strTimeA, &lHour, &lMinute))
		{
			lHour = 23;
			lMinute = 59;
		}

		CCustomDate dataTemp(dataA.GetYear(), dataA.GetMonth(), dataA.GetDay(), 0, lHour, lMinute);
		strTemp.Format("%s <= %li", strField, dataTemp.GetDate());
	}
	else
		strTemp.Empty();

	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

void CQueryUtility::GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idDateA)
{
	CString strTemp;
	
	CString strDa, strA;
	pParentWnd->GetDlgItemText(idDateDa, strDa);
	pParentWnd->GetDlgItemText(idDateA, strA);

	int iYearDa  = atoi(strDa.Mid(6, 4));
	int iMonthDa = atoi(strDa.Mid(3, 2));
	int iDayDa   = atoi(strDa.Mid(0, 2));
	int iYearA   = atoi(strA.Mid(6, 4));
	int iMonthA  = atoi(strA.Mid(3, 2));
	int iDayA    = atoi(strA.Mid(0, 2));

	if (iYearDa > 0 || iMonthDa > 0 || iDayDa > 0)
	{
		COleDateTime dataDa(iYearDa, iMonthDa, iDayDa, 0, 0, 0);

		if (dataDa.GetStatus() == COleDateTime::valid)
		{
			strTemp.Format("%s >= '%04d%02d%02d000000'", 
						strField, 
						dataDa.GetYear(),
						dataDa.GetMonth(),
						dataDa.GetDay());
		}
		else
			strTemp.Empty();

		if (!strTemp.IsEmpty())
		{
			if (!pFilter->IsEmpty())
				(*pFilter) += " AND " + strTemp;
			else
				(*pFilter) = strTemp;
		}
	}

	if (iYearA > 0 && iMonthA > 0 && iDayA > 0)
	{
		COleDateTime dataA(iYearA, iMonthA, iDayA, 0, 0, 0);

		if (dataA.GetStatus() == COleDateTime::valid)
		{
			strTemp.Format("%s <= '%04d%02d%02d235959'", 
						strField, 
						dataA.GetYear(),
						dataA.GetMonth(),
						dataA.GetDay());
		}
		else
			strTemp.Empty();

		if (!strTemp.IsEmpty())
		{
			if (!pFilter->IsEmpty())
				(*pFilter) += " AND " + strTemp;
			else
				(*pFilter) = strTemp;
		}
	}
}

void CQueryUtility::GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA)
{
	CString strTemp;
	
	CString strDateDa;
	CString strDateA;
	pParentWnd->GetDlgItemText(idDateDa, strDateDa);
	pParentWnd->GetDlgItemText(idDateA, strDateA);

	CString strTimeDa;
	CString strTimeA;
	pParentWnd->GetDlgItemText(idTimeDa, strTimeDa);
	pParentWnd->GetDlgItemText(idTimeA, strTimeA);

	int iYearDa  = atoi(strDateDa.Mid(6, 4));
	int iMonthDa = atoi(strDateDa.Mid(3, 2));
	int iDayDa   = atoi(strDateDa.Mid(0, 2));
	int iHourDa	 = atoi(strTimeDa.Mid(0, 2));
	int iMinDa	 = atoi(strTimeDa.Mid(3, 2));
	int iSecDa	 = atoi(strTimeDa.Mid(6, 2));

	int iYearA   = atoi(strDateA.Mid(6, 4));
	int iMonthA  = atoi(strDateA.Mid(3, 2));
	int iDayA    = atoi(strDateA.Mid(0, 2));
	int iHourA	 = atoi(strTimeA.Mid(0, 2));
	int iMinA	 = atoi(strTimeA.Mid(3, 2));
	int iSecA	 = atoi(strTimeA.Mid(6, 2));

	if ((iYearDa > 0) && (iMonthDa > 0) && (iDayDa > 0))
	{
		COleDateTime dataDa(iYearDa, iMonthDa, iDayDa, iHourDa, iMinDa, iSecDa);

		if (dataDa.GetStatus() == COleDateTime::valid)
		{
			strTemp.Format("%s >= '%04d%02d%02d%02d%02d%02d'", 
						strField, 
						dataDa.GetYear(),
						dataDa.GetMonth(),
						dataDa.GetDay(),
						dataDa.GetHour(),
						dataDa.GetMinute(),
						dataDa.GetSecond());
		}
		else
		{
			strTemp.Empty();
		}

		if (!strTemp.IsEmpty())
		{
			if (!pFilter->IsEmpty())
				(*pFilter) += " AND " + strTemp;
			else
				(*pFilter) = strTemp;
		}
	}

	if ((iYearA > 0) && (iMonthA > 0) && (iDayA > 0))
	{
		COleDateTime dataA(iYearA, iMonthA, iDayA, iHourA, iMinA, 0);

		if (dataA.GetStatus() == COleDateTime::valid)
		{
			strTemp.Format("%s <= '%04d%02d%02d%02d%02d%02d'", 
						strField, 
						dataA.GetYear(),
						dataA.GetMonth(),
						dataA.GetDay(),
						dataA.GetHour(),
						dataA.GetMinute(),
						dataA.GetSecond());
		}
		else
		{
			strTemp.Empty();
		}

		if (!strTemp.IsEmpty())
		{
			if (!pFilter->IsEmpty())
				(*pFilter) += " AND " + strTemp;
			else
				(*pFilter) = strTemp;
		}
	}
}

void CQueryUtility::GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA)
{
	COleDateTime dateNow = COleDateTime::GetCurrentTime();
	CString strTemp;

	switch(pDataPeriodCombo->GetCurSel())
	{
		case 1: // giorno corrente //
		{
			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		case 2: // giorno precedente //
		{
			dateNow -= COleDateTimeSpan(1, 0, 0, 0);

			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		case 3: // settimana corrente (da lunedì a domenica) //
		{
			int iWeekDay = dateNow.GetDayOfWeek() - 2; // -1 Domenica , 0 Lunedì , 1 Martedì , ... , 5 Sabato
			if (iWeekDay == -1)
				iWeekDay = 6; // 0 Lunedì , 1 Martedì , ... , 5 Sabato, 6 Domenica

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			CCustomDate date1(dateDa.GetYear(), dateDa.GetMonth(), dateDa.GetDay(), 0,  0,  0);
			CCustomDate date2(dateA.GetYear(),  dateA.GetMonth(),  dateA.GetDay(),  0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		case 4: // settimana precedente (da lunedì a domenica) //
		{
			dateNow -= COleDateTimeSpan(7, 0, 0, 0);

			int iWeekDay = dateNow.GetDayOfWeek() - 2; // -1 Domenica , 0 Lunedì , 1 Martedì , ... , 5 Sabato
			if (iWeekDay == -1)
				iWeekDay = 6; // 0 Lunedì , 1 Martedì , ... , 5 Sabato, 6 Domenica

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			CCustomDate date1(dateDa.GetYear(), dateDa.GetMonth(), dateDa.GetDay(), 0,  0,  0);
			CCustomDate date2(dateA.GetYear(),  dateA.GetMonth(),  dateA.GetDay(),  0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		case 5: // mese corrente //
		{
			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(),  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), 31, 0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		case 6: // mese precedente //
		{
			if (dateNow.GetMonth() == 1)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 1, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(),  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), 31, 0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		case 7: // trimestre corrente //
		{
			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate date1(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 3, 31, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}

				case 4:
				case 5:
				case 6:
				{
					CCustomDate date1(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 6, 30, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}

				case 7:
				case 8:
				case 9:
				{
					CCustomDate date1(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 9, 30, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}

				case 10:
				case 11:
				case 12:
				{
					CCustomDate date1(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}
			}
			break;
		}
		case 8: // trimestre precedente //
		{
			if (dateNow.GetMonth() < 4)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 3, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate date1(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 3, 31, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}

				case 4:
				case 5:
				case 6:
				{
					CCustomDate date1(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 6, 30, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}

				case 7:
				case 8:
				case 9:
				{
					CCustomDate date1(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 9, 30, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}

				case 10:
				case 11:
				case 12:
				{
					CCustomDate date1(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);
					strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
					break;
				}
			}
			break;
		}
		case 9: // anno corrente //
		{
			CCustomDate date1(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		case 10: // anno precedente //
		{
			dateNow.SetDateTime(dateNow.GetYear() - 1, dateNow.GetMonth(), 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			CCustomDate date1(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);

			strTemp.Format("(%s>=%li AND %s<=%li)", strField, date1.GetDate(), strField, date2.GetDate());
			break;
		}
		default: // intervallo date //
		{
			GetCustomDateFilter(&strTemp, strField, pParentWnd, idDateDa, idDateA);
			break;
		}
	}

	strTemp.Trim();
	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

void CQueryUtility::GetCustomDateFilter(long* pData1, long* pData2, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA)
{
	*pData1 = 0;
	*pData2 = 0;

	COleDateTime dateNow = COleDateTime::GetCurrentTime();

	switch(pDataPeriodCombo->GetCurSel())
	{
		case 1: // giorno corrente //
		{
			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		case 2: // giorno precedente //
		{
			dateNow -= COleDateTimeSpan(1, 0, 0, 0);

			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		case 3: // settimana corrente (da lunedì a domenica) //
		{
			int iWeekDay = dateNow.GetDayOfWeek() - 1; // 0 Lunedì - 6 Domenica
			if (iWeekDay == 0)
				iWeekDay = 6;

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			CCustomDate date1(dateDa.GetYear(), dateDa.GetMonth(), dateDa.GetDay(), 0,  0,  0);
			CCustomDate date2(dateA.GetYear(),  dateA.GetMonth(),  dateA.GetDay(),  0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		case 4: // settimana precedente (da lunedì a domenica) //
		{
			dateNow -= COleDateTimeSpan(7, 0, 0, 0);

			int iWeekDay = dateNow.GetDayOfWeek() - 1; // 0 Lunedì - 6 Domenica
			if (iWeekDay == 0)
				iWeekDay = 6;

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			CCustomDate date1(dateDa.GetYear(), dateDa.GetMonth(), dateDa.GetDay(), 0,  0,  0);
			CCustomDate date2(dateA.GetYear(),  dateA.GetMonth(),  dateA.GetDay(),  0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		case 5: // mese corrente //
		{
			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(),  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), 31, 0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		case 6: // mese precedente //
		{
			if (dateNow.GetMonth() == 1)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 1, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			CCustomDate date1(dateNow.GetYear(), dateNow.GetMonth(),  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), dateNow.GetMonth(), 31, 0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		case 7: // trimestre corrente //
		{
			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate date1(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 3, 31, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
				case 4:
				case 5:
				case 6:
				{
					CCustomDate date1(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 6, 30, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
				case 7:
				case 8:
				case 9:
				{
					CCustomDate date1(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 9, 30, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
				case 10:
				case 11:
				case 12:
				{
					CCustomDate date1(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
			}
			break;
		}
		case 8: // trimestre precedente //
		{
			if (dateNow.GetMonth() < 4)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 3, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate date1(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 3, 31, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
				case 4:
				case 5:
				case 6:
				{
					CCustomDate date1(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 6, 30, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
				case 7:
				case 8:
				case 9:
				{
					CCustomDate date1(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 9, 30, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
				case 10:
				case 11:
				case 12:
				{
					CCustomDate date1(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);
					*pData1 = date1.GetDate();
					*pData2 = date2.GetDate();
					break;
				}
			}
			break;
		}
		case 9: // anno corrente //
		{
			CCustomDate date1(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		case 10: // anno precedente //
		{
			dateNow.SetDateTime(dateNow.GetYear() - 1, dateNow.GetMonth(), 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			CCustomDate date1(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate date2(dateNow.GetYear(), 12, 31, 0, 23, 59);

			*pData1 = date1.GetDate();
			*pData2 = date2.GetDate();
			break;
		}
		default: // intervallo date //
		{
			GetCustomDateFilter(pData1, pData2, pParentWnd, idDateDa, idDateA);
			break;
		}
	}
}

void CQueryUtility::GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA)
{
	if (pDataPeriodCombo->GetCurSel() != 0)
		GetCustomDateFilter(pFilter, strField, pParentWnd, pDataPeriodCombo, idDateDa, idDateA);
	else
		GetCustomDateFilter(pFilter, strField, pParentWnd, idDateDa, idTimeDa, idDateA, idTimeA);
}

void CQueryUtility::GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA)
{
	COleDateTime dateNow = COleDateTime::GetCurrentTime();
	CString strTemp;

	switch(pDataPeriodCombo->GetCurSel())
	{
		case 1: // giorno corrente //
		{
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay(),
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay());
			break;
		}
		case 2: // giorno precedente //
		{
			dateNow -= COleDateTimeSpan(1, 0, 0, 0);
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay(),
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay());
			break;
		}
		case 3: // settimana corrente (da lunedì a domenica) //
		{
			int iWeekDay = dateNow.GetDayOfWeek() - 1; // 0 Lunedì - 6 Domenica
			if (iWeekDay == 0)
				iWeekDay = 6;

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateDa.GetYear(), 
							dateDa.GetMonth(),
							dateDa.GetDay(),
							strField, 
							dateA.GetYear(), 
							dateA.GetMonth(),
							dateA.GetDay());
			break;
		}
		case 4: // settimana precedente (da lunedì a domenica) //
		{
			dateNow -= COleDateTimeSpan(7, 0, 0, 0);

			int iWeekDay = dateNow.GetDayOfWeek() - 1; // 0 Lunedì - 6 Domenica
			if (iWeekDay == 0)
				iWeekDay = 6;

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateDa.GetYear(), 
							dateDa.GetMonth(),
							dateDa.GetDay(),
							strField, 
							dateA.GetYear(), 
							dateA.GetMonth(),
							dateA.GetDay());
			break;
		}
		case 5: // mese corrente //
		{
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							1,
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							31);
			break;
		}
		case 6: // mese precedente //
		{
			if (dateNow.GetMonth() == 1)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 1, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							1,
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							31);
			break;
		}
		case 7: // trimestre corrente //
		{
			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									1,
									1,
									strField, 
									dateNow.GetYear(), 
									3,
									31);
					break;
				}
				case 4:
				case 5:
				case 6:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									6,
									1,
									strField, 
									dateNow.GetYear(), 
									6,
									30);
					break;
				}
				case 7:
				case 8:
				case 9:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									7,
									1,
									strField, 
									dateNow.GetYear(), 
									9,
									30);
					break;
				}
				case 10:
				case 11:
				case 12:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									10,
									1,
									strField, 
									dateNow.GetYear(), 
									12,
									31);
					break;
				}
			}
			break;
		}
		case 8: // trimestre precedente //
		{
			if (dateNow.GetMonth() < 4)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 3, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									1,
									1,
									strField, 
									dateNow.GetYear(), 
									3,
									31);
					break;
				}
				case 4:
				case 5:
				case 6:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									6,
									1,
									strField, 
									dateNow.GetYear(), 
									6,
									30);
					break;
				}
				case 7:
				case 8:
				case 9:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									7,
									1,
									strField, 
									dateNow.GetYear(), 
									9,
									30);
					break;
				}
				case 10:
				case 11:
				case 12:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									10,
									1,
									strField, 
									dateNow.GetYear(), 
									12,
									31);
					break;
				}
			}
			break;
		}
		case 9: // anno corrente //
		{
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							1,
							1,
							strField, 
							dateNow.GetYear(), 
							12,
							31);
			break;
		}
		case 10: // anno precedente //
		{
			dateNow.SetDateTime(dateNow.GetYear() - 1, dateNow.GetMonth(), 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							1,
							1,
							strField, 
							dateNow.GetYear(), 
							12,
							31);
			break;
		}
		default: // intervallo date //
		{
			GetNormalDateFilter(&strTemp, strField, pParentWnd, idDateDa, idDateA);
			break;
		}
	}

	strTemp.Trim();
	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

void CQueryUtility::GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA)
{
	COleDateTime dateNow = COleDateTime::GetCurrentTime();
	CString strTemp;

	switch(pDataPeriodCombo->GetCurSel())
	{
		case 1: // giorno corrente //
		{
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay(),
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay());
			break;
		}
		case 2: // giorno precedente //
		{
			dateNow -= COleDateTimeSpan(1, 0, 0, 0);
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay(),
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							dateNow.GetDay());
			break;
		}
		case 3: // settimana corrente (da lunedì a domenica) //
		{
			int iWeekDay = dateNow.GetDayOfWeek() - 1; // 0 Lunedì - 6 Domenica
			if (iWeekDay == 0)
				iWeekDay = 6;

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateDa.GetYear(), 
							dateDa.GetMonth(),
							dateDa.GetDay(),
							strField, 
							dateA.GetYear(), 
							dateA.GetMonth(),
							dateA.GetDay());
			break;
		}
		case 4: // settimana precedente (da lunedì a domenica) //
		{
			dateNow -= COleDateTimeSpan(7, 0, 0, 0);

			int iWeekDay = dateNow.GetDayOfWeek() - 1; // 0 Lunedì - 6 Domenica
			if (iWeekDay == 0)
				iWeekDay = 6;

			COleDateTime dateDa = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateA  = dateDa  + COleDateTimeSpan(6);

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateDa.GetYear(), 
							dateDa.GetMonth(),
							dateDa.GetDay(),
							strField, 
							dateA.GetYear(), 
							dateA.GetMonth(),
							dateA.GetDay());
			break;
		}
		case 5: // mese corrente //
		{
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							1,
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							31);
			break;
		}
		case 6: // mese precedente //
		{
			if (dateNow.GetMonth() == 1)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 1, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							1,
							strField, 
							dateNow.GetYear(), 
							dateNow.GetMonth(),
							31);
			break;
		}
		case 7: // trimestre corrente //
		{
			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									1,
									1,
									strField, 
									dateNow.GetYear(), 
									3,
									31);
					break;
				}
				case 4:
				case 5:
				case 6:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									6,
									1,
									strField, 
									dateNow.GetYear(), 
									6,
									30);
					break;
				}
				case 7:
				case 8:
				case 9:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									7,
									1,
									strField, 
									dateNow.GetYear(), 
									9,
									30);
					break;
				}
				case 10:
				case 11:
				case 12:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									10,
									1,
									strField, 
									dateNow.GetYear(), 
									12,
									31);
					break;
				}
			}
			break;
		}
		case 8: // trimestre precedente //
		{
			if (dateNow.GetMonth() < 4)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 3, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									1,
									1,
									strField, 
									dateNow.GetYear(), 
									3,
									31);
					break;
				}
				case 4:
				case 5:
				case 6:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									6,
									1,
									strField, 
									dateNow.GetYear(), 
									6,
									30);
					break;
				}
				case 7:
				case 8:
				case 9:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									7,
									1,
									strField, 
									dateNow.GetYear(), 
									9,
									30);
					break;
				}
				case 10:
				case 11:
				case 12:
				{
					strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
									strField, 
									dateNow.GetYear(), 
									10,
									1,
									strField, 
									dateNow.GetYear(), 
									12,
									31);
					break;
				}
			}
			break;
		}
		case 9: // anno corrente //
		{
			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							1,
							1,
							strField, 
							dateNow.GetYear(), 
							12,
							31);
			break;
		}
		case 10: // anno precedente //
		{
			dateNow.SetDateTime(dateNow.GetYear() - 1, dateNow.GetMonth(), 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			strTemp.Format("(%s >= '%04d%02d%02d000000' AND %s <= '%04d%02d%02d235959')", 
				            strField, 
							dateNow.GetYear(), 
							1,
							1,
							strField, 
							dateNow.GetYear(), 
							12,
							31);
			break;
		}
		default: // intervallo date //
		{
			GetNormalDateFilter(&strTemp, strField, pParentWnd, idDateDa, idTimeDa, idDateA, idTimeA);
			break;
		}
	}

	strTemp.Trim();
	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

void CQueryUtility::GetComboFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl)
{
	CComboBox* pCombo = (CComboBox*)pParentWnd->GetDlgItem(idControl);
	
	CString strTemp;
	pParentWnd->GetDlgItemText(idControl, strTemp);

	if (!strTemp.IsEmpty())
	{
		strTemp.Format("%s = %li", strField, (long)pCombo->GetItemData(pCombo->GetCurSel()));
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

void CQueryUtility::GetListboxFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl, BOOL bExclude)
{
	CListBox* pList = (CListBox*)pParentWnd->GetDlgItem(idControl);

	CString strFilter, strTmp;
	for (int i = 0; i < pList->GetCount(); i++)
	{
		if (!strFilter.IsEmpty())
			strFilter += bExclude ? " AND " : " OR ";

		strTmp.Format("%s %s %li",
			strField,
			bExclude ? "<>" : "=",
			pList->GetItemData(i));
		strFilter += strTmp;
	}

	if (!strFilter.IsEmpty())
	{
		strFilter = "(" + strFilter + ")";
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strFilter;
		else
			(*pFilter) = strFilter;
	}
}

void CQueryUtility::GetListboxFilterText(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl, BOOL bExclude)
{
	CListBox* pList = (CListBox*)pParentWnd->GetDlgItem(idControl);

	CString strFilter, strTmp;
	for (int i = 0; i < pList->GetCount(); i++)
	{
		if (!strFilter.IsEmpty())
			strFilter += bExclude ? " AND " : " OR ";

		//

		CString sTempX;
		pList->GetText(i, sTempX);

		int iTempX = sTempX.Find(" - ");
		if (iTempX > 0)
			sTempX = sTempX.Right(sTempX.GetLength() - (iTempX + 3));

		sTempX.Replace("'", "''");

		//

		strTmp.Format("%s %s '%s'",
			strField,
			bExclude ? "<>" : "=",
			sTempX);
		strFilter += strTmp;
	}

	if (!strFilter.IsEmpty())
	{
		strFilter = "(" + strFilter + ")";
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strFilter;
		else
			(*pFilter) = strFilter;
	}
}

void CQueryUtility::GetEditFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl)
{
	CString strEdit, strTemp;
	pParentWnd->GetDlgItemText(idControl, strEdit);

	if (!strEdit.IsEmpty())
	{
		strTemp.Format("%s LIKE '%s%s%s'", strField, "%", strEdit, "%");
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

void CQueryUtility::GetEditFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT id1, UINT id2)
{
	CString strTemp;
	
	CString strDa, strA;
	pParentWnd->GetDlgItemText(id1, strDa);
	pParentWnd->GetDlgItemText(id2, strA);

	strDa.Replace("'", "''");
	strA.Replace("'", "''");

	strDa.Trim();
	strA.Trim();

	strTemp.Empty();
	if (!strDa.IsEmpty())
		strTemp.Format("%s>='%s'", strField, strDa);

	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}

	strTemp.Empty();
	if (!strA.IsEmpty())
		strTemp.Format("%s<='%s'", strField, strA);

	if (!strTemp.IsEmpty())
	{
		if (!pFilter->IsEmpty())
			(*pFilter) += " AND " + strTemp;
		else
			(*pFilter) = strTemp;
	}
}

CString CQueryUtility::GetDateString(CRecordset* pSet, long* pDate)
{
	CString str;
	if (!pSet->IsFieldNull(pDate) && (*pDate) > 0)
		str = CCustomDate(*pDate).GetDate("%d/%m/%Y");
	return str;
}

CString CQueryUtility::GetDateHourString(CRecordset* pSet, long* pDate)
{
	CString str;
	if (!pSet->IsFieldNull(pDate) && (*pDate) > 0)
		str = CCustomDate(*pDate).GetDate("%d/%m/%Y %H:%M");
	return str;
}

BOOL CQueryUtility::IsValidRecordsetDate(CRecordset* pSet, long* pDate)
{
	if (!pSet || !pDate)
		return FALSE;
	
	if (pSet->IsFieldNull(pDate))
		return FALSE;

	if (*pDate <= 0)
		return FALSE;

	CCustomDate date(*pDate);
	return date.IsValidDate(date.GetYear(), date.GetMonth(), date.GetDay()) && 
		   date.IsValidTime(date.GetHour(), date.GetMinute());
}

void CQueryUtility::InitComboDataPeriod(CComboBox* pCombo)
{
	pCombo->ResetContent();
	pCombo->InsertString(0, theApp.GetMessageString(IDS_DATA_PERIOD_00)); // INTERVALLO DATE //
	pCombo->InsertString(1, theApp.GetMessageString(IDS_DATA_PERIOD_01)); // giorno corrente //
	pCombo->InsertString(2, theApp.GetMessageString(IDS_DATA_PERIOD_02)); // giorno precedente //
	pCombo->InsertString(3, theApp.GetMessageString(IDS_DATA_PERIOD_03)); // settimana corrente //
	pCombo->InsertString(4, theApp.GetMessageString(IDS_DATA_PERIOD_04)); // settimana precedente //
	pCombo->InsertString(5, theApp.GetMessageString(IDS_DATA_PERIOD_05)); // mese corrente //
	pCombo->InsertString(6, theApp.GetMessageString(IDS_DATA_PERIOD_06)); // mese precedente //
	pCombo->InsertString(7, theApp.GetMessageString(IDS_DATA_PERIOD_07)); // trimestre corrente //
	pCombo->InsertString(8, theApp.GetMessageString(IDS_DATA_PERIOD_08)); // trimestre precedente //
	pCombo->InsertString(9, theApp.GetMessageString(IDS_DATA_PERIOD_09)); // anno corrente //
	pCombo->InsertString(10, theApp.GetMessageString(IDS_DATA_PERIOD_10)); // anno precedente //
	pCombo->SetCurSel(1); //Julio 06/03/2018
}

void CQueryUtility::ComboDataPeriodUpdated(CComboBox* pCombo, CWnd* pParentWnd, UINT idDateIniz, UINT idDateFine)
{
	pParentWnd->GetDlgItem(idDateIniz)->EnableWindow(pCombo->GetCurSel() == 0);
	pParentWnd->GetDlgItem(idDateFine)->EnableWindow(pCombo->GetCurSel() == 0);

	CString strDataIniz;
	CString strDataFine;
	COleDateTime dateNow = COleDateTime::GetCurrentTime();

	switch(pCombo->GetCurSel())
	{
		case 1: // giorno corrente //
		{
			strDataIniz.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		case 2: // giorno precedente //
		{
			dateNow -= COleDateTimeSpan(1, 0, 0, 0);

			strDataIniz.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		case 3: // settimana corrente (da lunedì a domenica) //
		{
			int iWeekDay = dateNow.GetDayOfWeek() - 2; // -1 Domenica , 0 Lunedì , 1 Martedì , ... , 5 Sabato
			if (iWeekDay == -1)
				iWeekDay = 6; // 0 Lunedì , 1 Martedì , ... , 5 Sabato, 6 Domenica

			COleDateTime dateIniz = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateFine = dateIniz + COleDateTimeSpan(6);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		case 4: // settimana precedente (da lunedì a domenica) //
		{
			dateNow -= COleDateTimeSpan(7, 0, 0, 0);

			int iWeekDay = dateNow.GetDayOfWeek() - 2; // -1 Domenica , 0 Lunedì , 1 Martedì , ... , 5 Sabato
			if (iWeekDay == -1)
				iWeekDay = 6; // 0 Lunedì , 1 Martedì , ... , 5 Sabato, 6 Domenica

			COleDateTime dateIniz = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateFine = dateIniz + COleDateTimeSpan(6);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		case 5: // mese corrente //
		{
			int nMonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			CCustomDate dateIniz(dateNow.GetYear(), dateNow.GetMonth(),  1,  0,  0,  0);
			CCustomDate dateFine(dateNow.GetYear(), dateNow.GetMonth(), nMonthDays[dateNow.GetMonth() - 1],  0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		case 6: // mese precedente //
		{
			if (dateNow.GetMonth() == 1)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 1, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			int nMonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			CCustomDate dateIniz(dateNow.GetYear(), dateNow.GetMonth(),  1,  0,  0,  0);
			CCustomDate dateFine(dateNow.GetYear(), dateNow.GetMonth(), nMonthDays[dateNow.GetMonth() - 1],  0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		case 7: // trimestre corrente //
		{
			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 3, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
				case 4:
				case 5:
				case 6:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 6, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
				case 7:
				case 8:
				case 9:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 9, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
				case 10:
				case 11:
				case 12:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
			}
			break;
		}
		case 8: // trimestre precedente //
		{
			if (dateNow.GetMonth() < 4)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 3, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 3, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
				case 4:
				case 5:
				case 6:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 6, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
				case 7:
				case 8:
				case 9:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 9, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
				case 10:
				case 11:
				case 12:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

					break;
				}
			}
			break;
		}
		case 9: // anno corrente //
		{
			CCustomDate dateIniz(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		case 10: // anno precedente //
		{
			dateNow.SetDateTime(dateNow.GetYear() - 1, dateNow.GetMonth(), 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			CCustomDate dateIniz(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateIniz)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateFine)->SetWindowText(strDataFine);

			break;
		}
		default: // intervallo date //
		{
			break;
		}
	}
}

void CQueryUtility::ComboDataPeriodUpdated(CComboBox* pCombo, CWnd* pParentWnd, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA)
{
	pParentWnd->GetDlgItem(idDateDa)->EnableWindow(pCombo->GetCurSel() == 0);
	pParentWnd->GetDlgItem(idTimeDa)->EnableWindow(pCombo->GetCurSel() == 0);

	pParentWnd->GetDlgItem(idDateA)->EnableWindow(pCombo->GetCurSel() == 0);
	pParentWnd->GetDlgItem(idTimeA)->EnableWindow(pCombo->GetCurSel() == 0);

	CString strDataIniz;
	CString strDataFine;
	COleDateTime dateNow = COleDateTime::GetCurrentTime();

	switch(pCombo->GetCurSel())
	{
		case 1: // giorno corrente //
		{
			strDataIniz.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		case 2: // giorno precedente //
		{
			dateNow -= COleDateTimeSpan(1, 0, 0, 0);

			strDataIniz.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateNow.GetDay(), dateNow.GetMonth(), dateNow.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		case 3: // settimana corrente (da lunedì a domenica) //
		{
			int iWeekDay = dateNow.GetDayOfWeek() - 2; // -1 Domenica , 0 Lunedì , 1 Martedì , ... , 5 Sabato
			if (iWeekDay == -1)
				iWeekDay = 6; // 0 Lunedì , 1 Martedì , ... , 5 Sabato, 6 Domenica

			COleDateTime dateIniz = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateFine = dateIniz + COleDateTimeSpan(6);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		case 4: // settimana precedente (da lunedì a domenica) //
		{
			dateNow -= COleDateTimeSpan(7, 0, 0, 0);

			int iWeekDay = dateNow.GetDayOfWeek() - 2; // -1 Domenica , 0 Lunedì , 1 Martedì , ... , 5 Sabato
			if (iWeekDay == -1)
				iWeekDay = 6; // 0 Lunedì , 1 Martedì , ... , 5 Sabato, 6 Domenica

			COleDateTime dateIniz = dateNow - COleDateTimeSpan(iWeekDay);
			COleDateTime dateFine = dateIniz + COleDateTimeSpan(6);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		case 5: // mese corrente //
		{
			int nMonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			CCustomDate dateIniz(dateNow.GetYear(), dateNow.GetMonth(),  1,  0,  0,  0);
			CCustomDate dateFine(dateNow.GetYear(), dateNow.GetMonth(), nMonthDays[dateNow.GetMonth() - 1],  0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		case 6: // mese precedente //
		{
			if (dateNow.GetMonth() == 1)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 1, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			int nMonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			CCustomDate dateIniz(dateNow.GetYear(), dateNow.GetMonth(),  1,  0,  0,  0);
			CCustomDate dateFine(dateNow.GetYear(), dateNow.GetMonth(), nMonthDays[dateNow.GetMonth() - 1],  0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		case 7: // trimestre corrente //
		{
			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 3, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
				case 4:
				case 5:
				case 6:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 6, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
				case 7:
				case 8:
				case 9:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 9, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
				case 10:
				case 11:
				case 12:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
			}
			break;
		}
		case 8: // trimestre precedente //
		{
			if (dateNow.GetMonth() < 4)
				dateNow.SetDateTime(dateNow.GetYear() - 1, 12, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
			else
				dateNow.SetDateTime(dateNow.GetYear(), dateNow.GetMonth() - 3, 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			switch(dateNow.GetMonth())
			{
				case 1:
				case 2:
				case 3:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 1,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 3, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
				case 4:
				case 5:
				case 6:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 4,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 6, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
				case 7:
				case 8:
				case 9:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 7,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 9, 30, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
				case 10:
				case 11:
				case 12:
				{
					CCustomDate dateIniz(dateNow.GetYear(), 10,  1, 0, 0, 0);
					CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

					strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
					strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

					pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
					pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

					pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
					pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

					break;
				}
			}
			break;
		}
		case 9: // anno corrente //
		{
			CCustomDate dateIniz(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		case 10: // anno precedente //
		{
			dateNow.SetDateTime(dateNow.GetYear() - 1, dateNow.GetMonth(), 28, dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());

			CCustomDate dateIniz(dateNow.GetYear(),  1,  1, 0, 0, 0);
			CCustomDate dateFine(dateNow.GetYear(), 12, 31, 0, 23, 59);

			strDataIniz.Format("%02d/%02d/%04d", dateIniz.GetDay(), dateIniz.GetMonth(), dateIniz.GetYear());
			strDataFine.Format("%02d/%02d/%04d", dateFine.GetDay(), dateFine.GetMonth(), dateFine.GetYear());

			pParentWnd->GetDlgItem(idDateDa)->SetWindowText(strDataIniz);
			pParentWnd->GetDlgItem(idDateA)->SetWindowText(strDataFine);

			pParentWnd->GetDlgItem(idTimeDa)->SetWindowText("00:00:00");
			pParentWnd->GetDlgItem(idTimeA)->SetWindowText("23:59:59");

			break;
		}
		default: // intervallo date //
		{
			break;
		}
	}
}

void CQueryUtility::GetDateDescription(CString* pDescription, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA)
{
	pDescription->Empty();

	CString str;
	if (pDataPeriodCombo->GetCurSel() == 0)
	{
		CString strDa, strA;
		pParentWnd->GetDlgItemText(idDateDa, strDa);
		pParentWnd->GetDlgItemText(idDateA, strA);

		CCustomDate dataDa(strDa), dataA(strA);
		if (dataDa.GetDate() > 0 && dataA.GetDate() > 0)
			pDescription->Format("da %s a %s", strDa, strA);
	}
	else if (pDataPeriodCombo->GetCurSel() > 0)
		pDataPeriodCombo->GetLBText(pDataPeriodCombo->GetCurSel(), *pDescription);
}

BOOL CQueryUtility::GetTimeFromString(CString str, long* pHour, long* pMinute)
{
	BOOL bReturn = FALSE;
	*pHour = -1;
	*pMinute = -1;

	if (str.GetAt(0) >= '0' && str.GetAt(0) <= '2' &&
		str.GetAt(1) >= '0' && str.GetAt(1) <= '9' &&
		str.GetAt(3) >= '0' && str.GetAt(3) <= '5' &&
		str.GetAt(4) >= '0' && str.GetAt(4) <= '9')
	{
		*pHour = atol(str.Left(2));
		*pMinute = atol(str.Right(2));
		if ((*pHour < 0 && *pHour > 23) || (*pMinute < 0 && *pMinute > 59))
		{
			*pHour = -1;
			*pMinute = -1;
		}
		else
			bReturn = TRUE;
	}

	return bReturn;
}

void CQueryUtility::ExportListCtrl(CListCtrl* pListCtrl, CString strTitle)
{
	CString strFilter, strFileExport;
	CExportFileDlg dlg;
	CExportExcel excel;
	CExportHtml  html;
	CExportCSV   csv;
	int nModalita;
	BOOL bContinue = FALSE;

	HDITEM hdItem;
	char lpBuffer[256];
	hdItem.mask = HDI_TEXT;
	hdItem.pszText = lpBuffer;
	hdItem.cchTextMax = 256;

	if (dlg.DoModal() == IDOK)
	{
		nModalita = dlg.m_nTipoExport;
	
		switch(nModalita)
		{
			case 0:
			{
				strFilter = "File Microsoft Excel (*.xls)|*.xls|Tutti i file|*.*|";
				break;
			}
			case 1:
			{
				strFilter = "File HTML (*.htm)|*.htm|Tutti i file|*.*|";
				break;
			}
			case 2:
			{
				strFilter = "File CSV (*.csv)|*.csv|Tutti i file|*.*|";
				break;
			}
		}

		CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, NULL, 0, FALSE);
		if (FileDlg.DoModal() == IDOK)
		{
			strFileExport = FileDlg.GetPathName();

			switch(nModalita)
			{
				case 0:
				{
					if (strFileExport.Right(4) != ".xls")
						strFileExport += ".xls";
					break;
				}
				case 1:
				{
					if (strFileExport.Right(4) != ".htm")
						strFileExport += ".htm";
					break;
				}
				case 2:
				{
					if (strFileExport.Right(4) != ".csv")
						strFileExport += ".csv";
					break;
				}
			}

			switch(nModalita)
			{
				case 0:
				{
					bContinue = excel.CreateFile(strFileExport);
					break;
				}
				case 1:
				{
					bContinue = html.CreateFile(strFileExport, "Nomenclatore " + theApp.m_sNomeProgramma, pListCtrl->GetHeaderCtrl()->GetItemCount());
					break;
				}
				case 2:
				{
					bContinue = csv.CreateFile(strFileExport);
					break;
				}
			}
			
			if (!bContinue)
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NOMENCLATORE_ERR_FILE) + strFileExport);
		}	
		else
		{
			bContinue = FALSE;
		}
	}

	CString strToWrite;
	CellFont nCellFont;
	int nMaxLength[10];
	ZeroMemory(nMaxLength, 10 * sizeof(int));

	if (bContinue)
	{
		// Sandro Gallina - 31/05/2004 --> //
		switch(nModalita)
		{
			case 0:
			{
				excel.WriteValue(strTitle, 0, 0, xlsFont1, xlsGeneralAlign, xlsNormal);
				break;
			}
			case 1:
			{
				html.WriteTitle(strTitle);
				break;
			}
		}
		// <-- Sandro Gallina - 31/05/2004 //

		for(int i = 0; i <= pListCtrl->GetItemCount(); i++)
		{
			for(int j = 0; j < pListCtrl->GetHeaderCtrl()->GetItemCount(); j++)
			{
				if (i == 0)
				{
					//Scrivo intestazioni
					pListCtrl->GetHeaderCtrl()->GetItem(j, &hdItem);
					strToWrite = hdItem.pszText;
					nCellFont = xlsFont0;
				}
				else
				{
					strToWrite = pListCtrl->GetItemText(i - 1, j);
					nCellFont = xlsFont1;
				}
				
				if (nMaxLength[j] < strToWrite.GetLength())
					nMaxLength[j] = strToWrite.GetLength();
				
				switch(nModalita)
				{
					case 0:
					{
						excel.WriteValue(strToWrite, i + 2, j, nCellFont, xlsGeneralAlign, xlsNormal);
						break;
					}
					case 1:
					{
						html.WriteValue(strToWrite);
						//Per evitare errore di visualizzazione..
						if (j < pListCtrl->GetHeaderCtrl()->GetItemCount() - 1)
							html.WriteNewColumn();
						break;
					}
					case 2:
					{
						csv.WriteValue(strToWrite);
						csv.WriteNewColumn();
						break;
					}
				}
			}

			switch(nModalita)
			{
				case 1:
				{
					html.WriteNewRow();
					break;
				}
				case 2:
				{
					csv.WriteNewRow();
					break;
				}
			}
		}
				
		if (nModalita == 0)
			for(int j = 0; j < pListCtrl->GetHeaderCtrl()->GetItemCount(); j++)
				excel.SetColumnWidth(j, j, (short)(nMaxLength[j] * 1));
				
		switch(nModalita)
		{
			case 0:
			{
				excel.SetFont("Tahoma", 10, xlsBold);
				excel.SetFont("Tahoma", 10, xlsNoFormat);
				excel.CloseFile();
				break;
			}
			case 1:
			{
				html.CloseFile();
				break;
			}
			case 2:
			{
				csv.CloseFile(strTitle);
				break;
			}
		}
	}
}