#pragma once

#include "DLL_Imaging\h\AmListCtrl.h"

class CEtichetteCondConfigDlg : public CDialog
{

public:
	enum conditionalType {
		combo = 0,
		text,
		numeric
	};

	DECLARE_DYNAMIC(CEtichetteCondConfigDlg)

public:
	CEtichetteCondConfigDlg(CWnd* pParent, long idCondizionato, long idRelazionato, conditionalType tipoCondizionato);
	~CEtichetteCondConfigDlg();

	enum { IDD = IDD_ETICHETTE_COND_CONFIG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	//virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

private:
	CAMEditComboListCtrl m_ctrlList;

	CButtonLocalize m_ctrlBtnAggiungi;
	CButtonLocalize m_ctrlBtnRimuovi;
	CButtonLocalize m_ctrlBtnOK;
	CButtonLocalize m_ctrlBtnCancel;

	long m_lIdCondizionato;
	int m_iIndexRelazionato;
	int m_iIndexCondizionato;
	long m_lIdRelazionato;
	conditionalType m_tipoCondizionato;
	CString m_sDescrizioneCondizionato;
	CString m_sDescrizioneRelazionato;

	CStringIDList m_strIdList;
	CStringIDList m_strIdListCondizionato;

public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDel();
};


