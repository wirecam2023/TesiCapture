#pragma once

class CEndoGridMonthCalDlg : public CDialog
{
public:
	CEndoGridMonthCalDlg(CString strValue, CRect rect, CString strFormat);

	enum { IDD = IDD_MONTH_CAL };

	CString m_strDate;

protected:
	void OnSelect(NMHDR*, LRESULT*);
	BOOL OnInitDialog();
	void OnDestroy();
	void OnOK();
	DECLARE_MESSAGE_MAP()

	CXTMonthCalCtrl* m_pMonthCtrl;
	CString m_strValue, m_strFormat;
	CRect m_rectItem;
};
