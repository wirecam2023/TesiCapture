#pragma once

#include "WSpellCtrl.h"

class CSpellCheckerDlg : protected CDialog
{
	DECLARE_DYNAMIC(CSpellCheckerDlg)

public:

	CSpellCheckerDlg();
	~CSpellCheckerDlg();

	BOOL Create(CWnd* pParentWnd);
	BOOL Destroy();

	void SetTextControl(CWnd* pTextControl);

	// si usa per fare il check mentre si scrive //
	void Check(); 
	// si usa per far apparire lista suggerimenti //
	void Menu(CPoint point); 

	// si usa prima del salvataggio per togliere sottolineature errori //
	void DeleteUnderline(); 
	// si usa dopo caricamento per ricontrollare tutto //
	void Recheck(); 

	//
	void ImportWordsFromExcel(CString strFile);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()

	afx_msg void OnDoubledWordWspell();

	enum { IDD = IDD_SPELLCHECKER };

private:

	CWnd* m_pTextControl;
	CWspellctrl m_ctrl;

	BOOL m_bAlreadyCreated;

};
