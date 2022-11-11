#ifndef _STAMPAETICHETTEDLG_H_
	#define _STAMPAETICHETTEDLG_H_

#include "PazientiSet.h"

class CStampaEtichetteDlg : public CDialog
{
	DECLARE_DYNAMIC(CStampaEtichetteDlg)

public:

	CStampaEtichetteDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CStampaEtichetteDlg();

	enum { IDD = IDD_STAMPA_ETICHETTE_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnAdd3();
	afx_msg void OnBnClickedBtnAdd6();
	afx_msg void OnBnClickedBtnAdd9();
	afx_msg void OnBnClickedBtnRem3();
	afx_msg void OnBnClickedBtnRem6();
	afx_msg void OnBnClickedBtnRem9();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:

	BOOL StampaEtichette();

	CListCtrlLocalize m_ctrlListPazienti;
	CListCtrlLocalize m_ctrlListStampa3;
	CListCtrlLocalize m_ctrlListStampa6;
	CListCtrlLocalize m_ctrlListStampa9;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CPazientiSet m_setPazienti;
};

#endif /* _STAMPAETICHETTEDLG_H_ */