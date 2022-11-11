#ifndef _CAMPIOBBLIGATORIINSMODDLG_H_
	#define _CAMPIOBBLIGATORIINSMODDLG_H_

#include "afxwin.h"

#include "..\DLL_Imaging\h\AMEditComboListCtrl.h"

class CCampiObbligatoriInsModDlg : public CDialog
{
	DECLARE_DYNAMIC(CCampiObbligatoriInsModDlg)

public:

	CCampiObbligatoriInsModDlg(CWnd* pParent, CEsamiView* pEsamiView, long lID);
	virtual ~CCampiObbligatoriInsModDlg();

	enum { IDD = IDD_CAMPI_OBBLIGATORI_INSMOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CEsamiView* m_pEsamiView;
	long m_lID;

	//

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CComboBox m_ctrlComboTipoEsame;
	CAMEditComboListCtrl m_ctrlListProvenienze;
	CComboBox m_ctrlComboFase;
	CComboBox m_ctrlComboFase2;
	CComboBox m_ctrlComboCampo;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;

public:
	afx_msg void OnCbnSelchangeCmbFase();
	afx_msg void OnCbnSelchangeCmbFase2();
};

#endif /* _CAMPIOBBLIGATORIINSMODDLG_H_ */