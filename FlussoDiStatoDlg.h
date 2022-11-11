//Gabriel BUG 6225 - Lista DO
#pragma once

#ifndef _FLUSSODISTATODLG_H_
#define _FLUSSODISTATODLG_H_

#include "EndoxResizableDlg.h"
#include "ListSortableCtrl.h"

class CFlussoDiStatoDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CFlussoDiStatoDlg)

public:

	CFlussoDiStatoDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CFlussoDiStatoDlg();

	enum { IDD = IDD_FLUSSODISTATO };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:
	void RiempiLista();
	void RiempiComboMedico();
	void RefreshCount(); //Gabriel BUG 6225 - Lista DO FIX

	CString GetDataOraFrom();
	CString GetDataOraTo();

	CEsamiView* m_pEsamiView;

	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2, m_ctrlStatic3, m_ctrlStatic4, m_ctrlStatic5; //Gabriel BUG 6225 - Lista DO FIX
	CButtonLocalize m_ctrlButtonChiudi;
	CButtonLocalize m_ctrlButtonMedico;
	CListSortableCtrl m_ctrlList;

	CComboBox m_ctrlComboMedico;
	CDateTimeCtrl m_ctrlDateFrom, m_ctrlTimeFrom;
	CDateTimeCtrl m_ctrlDateTo, m_ctrlTimeTo;

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedMedico();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult); //Gabriel BUG 6225 - Lista DO FIX
};

#endif /* _FLUSSODISTATODLG_H_ */