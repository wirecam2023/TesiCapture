#pragma once

#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "EditDynFormToolbar.h"

class CGenomicaTipiRefertoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaTipiRefertoDlg)

public:
	CGenomicaTipiRefertoDlg(CWnd* pParent);
	virtual ~CGenomicaTipiRefertoDlg();

	enum { IDD = IDD_GENOMICA_TIPIREFERTO };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeFamiglia(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();

	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();
	afx_msg void OnBnClickedBtnRtfFont();//Julio - BUG 4392 Edicao de texto

	DECLARE_MESSAGE_MAP()
private:

	void RiempiLista();
	void CaricaDati();
	void EditDialog(BOOL bEdit);	
	void UnselectAll();
	void SaveRtfsToMemory();
	void ResetMemoryRtfs();
	void SetupCtrlFamiglia();


	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;

	CListCtrl m_ctrlList;
	CTabCtrl m_ctrlFamiglia;
	long m_lFamiglia;

	CStaticLocalize m_ctrlStatic1;	

	CTXButtonBar23Ex m_ctrlButtonBar;
	CEditDynFormToolbar m_ctrlToolbar;
	CTXTextControl23Ex m_ctrlTextControl;

	CTXButtonBar23Ex m_ctrlButtonBarTab;
	CEditDynFormToolbar m_ctrlToolbarTab;
	CTXTextControl23Ex m_ctrlTextControlTab;

	long m_lIDSelected;
	CString m_sTestoRtf1;
	CString m_sTestoRtf2;
	CString m_sTestoRtf3;
	CString m_sTestoRtf4;
	CString m_sTestoRtf5;
	CString m_sTestoRtf6;
	CString m_sTestoRtf7;
	CString m_sTestoRtf8;
	CString m_sTestoRtf9;
	CString m_sTestoRtf10;

	CString m_sFontNameRtf1;
	int m_nFontSizeRtf1;

	CString m_sFontNameRtf2;
	int m_nFontSizeRtf2;

	CString m_sFontNameRtf3;
	int m_nFontSizeRtf3;

	CString m_sFontNameRtf4;
	int m_nFontSizeRtf4;

	CString m_sFontNameRtf5;
	int m_nFontSizeRtf5;

	CString m_sFontNameRtf6;
	int m_nFontSizeRtf6;

	CString m_sFontNameRtf7;
	int m_nFontSizeRtf7;

	CString m_sFontNameRtf8;
	int m_nFontSizeRtf8;

	CString m_sFontNameRtf9;
	int m_nFontSizeRtf9;

	CString m_sFontNameRtf10;
	int m_nFontSizeRtf10;
};