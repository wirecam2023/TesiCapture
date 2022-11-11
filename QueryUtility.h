#pragma once

class CQueryUtility
{

protected:

	CQueryUtility(void);

	void GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idDateA);
	void GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA);

	void GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA);
	void GetCustomDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA);

	void GetCustomDateFilter(long* pData1, long* pData2, CWnd* pParentWnd, UINT idDateDa, UINT idDateA);
	void GetCustomDateFilter(long* pData1, long* pData2, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA);

	void GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idDateA);
	void GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA);

	void GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA);
	void GetNormalDateFilter(CString* pFilter, CString strField, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA);

	void GetComboFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl);

	void GetEditFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl);
	void GetEditFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT id1, UINT id2);

	void GetListboxFilter(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl, BOOL bExclude = FALSE);
	void GetListboxFilterText(CString* pFilter, CString strField, CWnd* pParentWnd, UINT idControl, BOOL bExclude = FALSE);

	CString GetDateString(CRecordset* pSet, long* pDate);
	CString GetDateHourString(CRecordset* pSet, long* pDate);

	void InitComboDataPeriod(CComboBox* pCombo);
	void ComboDataPeriodUpdated(CComboBox* pCombo, CWnd* pParentWnd, UINT idDateDa, UINT idDateA);
	void ComboDataPeriodUpdated(CComboBox* pCombo, CWnd* pParentWnd, UINT idDateDa, UINT idTimeDa, UINT idDateA, UINT idTimeA);

	void GetDateDescription(CString* pDescription, CWnd* pParentWnd, CComboBox* pDataPeriodCombo, UINT idDateDa, UINT idDateA);

	BOOL IsValidRecordsetDate(CRecordset* pSet, long* pDate);

	BOOL GetTimeFromString(CString str, long* pHour, long* pMinute);

	void ExportListCtrl(CListCtrl* pListCtrl, CString strTitle);

};
