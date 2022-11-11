#pragma once

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

class CIntegrazioniConfigurazioneModDlg;

class CIntegrazioniRobotConfigForm : public CResizableDialog
{

public:
	enum { IDD = IDD_INTEGRAZIONI_ROBOT };
	CIntegrazioniRobotConfigForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* configDlg);
	~CIntegrazioniRobotConfigForm();

	void Save();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnNuovoDispositivo();
	afx_msg void OnEliminaDispositivo();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CIntegrazioniConfigurazioneModDlg* m_pConfigDlg;

	void Load();
	
	CStaticLocalize m_ctrlStatic1;
	CAMEditComboListCtrl m_ctrlListLista;
	CButtonLocalize m_ctrlBtnAdd, m_ctrlBtnDel;

	CList<long> m_listDeletedItem;


public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonNuovo();
	afx_msg void OnBnClickedButtonCanc();

};
