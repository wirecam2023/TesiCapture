#ifndef _NOMENCALTORERISDLG_H_
	#define _NOMENCALTORERISDLG_H_

#include "NomenclatoreListCtrl.h"

class CNomenclatoreRisDlg : public CDialog
{

public:

	CNomenclatoreRisDlg(CWnd* pParentWnd, CEsamiView* pEsamiView);

	enum { IDD = IDD_NOMENCLATORE_RIS };

	CNomenclatoreListCtrl m_ctrlListResult;

	CBitmapButton m_BtnStampa;
	CBitmapButton m_BtnExport;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnExport();
	afx_msg void OnLvnEndScrollListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStampa();

	CButtonLocalize m_ctrlButtonOK;

	CString m_sFiltroData;
	CString m_sDataIniz;
	CString m_sDataFine;
	CString m_sSedeEsame;
	long m_lMedico;
	int m_nProvenienza;

private:

	CEsamiView* m_pEsamiView;

};

#endif /* _NOMENCALTORERISDLG_H_ */