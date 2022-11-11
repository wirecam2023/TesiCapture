#ifndef _MENUDLG_H_
	#define _MENUDLG_H_

#include "ListEdit.h"
#include "ExtListCombo.h"

class CMenuDlg : public CDialog
{

public:

	CMenuDlg(CWnd* pParent, long lComboDefine, CBaseSet* pSet, CString* pStrParent, long* pNumParent, CString* pStrRicerca, CString* pStrRicercaOutput, BOOL bMoreFields, BOOL bSameMultipleSelect, BOOL bOrderByString, CString strInit, int nProgramMode, CRect rect);
	virtual ~CMenuDlg();

	enum { IDD = IDD_MENU };

	long m_lContatore;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSelectWithMouse();
	afx_msg void OnClose();
	afx_msg void OnReset();
	afx_msg void OnBtnAnd();
	afx_msg void OnBtnOr();
	afx_msg void OnChangeRicerca();
	afx_msg void OnLbnSelchangeLista();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

private:

	BOOL SelectLista();

	//

	CButtonLocalize m_ctrlButtonReset;
	CButtonLocalize m_ctrlButtonClose;

	CExtListCombo m_ctrLista;

	CListEdit m_ctrlRicerca;

	//

	BOOL m_bModalitaRicerca;
	BOOL m_bMoreFields;
	BOOL m_bMoreFieldsOld;
	BOOL m_bOrderByString;
	BOOL m_bOrPressed;
	BOOL m_bSameMultipleSelect;

	int m_nItemCount;
	int m_nItemPressed;

	long m_lComboDefine;

	CRect m_rect;

	CString m_strRicerca;

	//

	CBaseSet* m_pSet;

	long* m_pNumOutput;

	CString* m_pStrOutput;
	CString* m_pStrQuery;
	CString* m_pStrQueryOut;

};

#endif /* _MENUDLG_H_ */