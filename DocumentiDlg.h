#ifndef _DOCUMENTIDLG_H_
	#define _DOCUMENTIDLG_H_

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

class CDocumentiDlg : public CDialog
{
	DECLARE_DYNAMIC(CDocumentiDlg)

public:

	CDocumentiDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bAlbumPaziente, BOOL bInviareCarestream, BOOL bInviaCentraleRefertazione);
	virtual ~CDocumentiDlg();

	enum { IDD = IDD_DOCUMENTI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnDisco();
	afx_msg void OnBnClickedBtnScanner();
	afx_msg void OnBnClickedBtnTiffMP();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnIntegrazione();
	afx_msg void OnBnClickedBtnExpAll();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista();

	CButtonLocalize m_ctrlBtnDisco;
	CButtonLocalize m_ctrlBtnScanner;
	CButtonLocalize m_ctrlBtnTiffMP;
	CButtonLocalize m_ctrlBtnIntegrazione;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnExpAll;
	CButtonLocalize m_ctrlBtnOK;
	CButtonLocalize m_ctrlBtnArchivia;

	CAMEditComboListCtrl m_ctrlList;

	// --- //

	CEsamiView* m_pEsamiView;
	BOOL m_bAlbumPaziente;
	BOOL m_bInviareCarestream;
	BOOL m_bInviaCentraleRefertazione; //Gabriel - P3

	void OnBnClickedBtnScannerTwain();
	void OnBnClickedBtnScannerWM();

};

#endif /* _DOCUMENTIDLG_H_ */