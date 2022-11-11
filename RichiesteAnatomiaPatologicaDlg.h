#ifndef _RICHIESTEANATOMIAPATOLOGICADLG_H_
	#define _RICHIESTEANATOMIAPATOLOGICADLG_H_

#include "AnatomiaPatologicaRichListCtrl.h"
#include "EndoxResizableDlg.h"
#include "afxwin.h"

class CRichiesteAnatomiaPatologicaDlg : public CEndoxResizableDlg 
{
	DECLARE_DYNAMIC(CRichiesteAnatomiaPatologicaDlg)

public:

	CRichiesteAnatomiaPatologicaDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CRichiesteAnatomiaPatologicaDlg();

	enum { IDD = IDD_RICHIESTEANATOMIAPATOLOGICA_DLG };

	void CreateModelessDialog(CWnd* pParent);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnBnClickedBtnStampa();
	afx_msg void OnBnClickedBtnAggiorna();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedCheckArchiviate();
	afx_msg void OnCbnSelchangeComboSede();
	afx_msg void OnCbnSelchangeComboMedico();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListNew(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnShowSospesiIstologiciWnd(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();
	static void StampaRiga(long lPaziente, long lEsame, CEsamiView* pEsamiView, BOOL bAltroIndirizzo);

	CAnatomiaPatologicaRichListCtrl m_ctrlList;
	CImageList m_ctrlImageList;

	CComboBox m_ctrlComboSede;
	CComboBox m_ctrlComboMedico;
	CButtonLocalize m_ctrlCheckArchiviate;

	CEsamiView* m_pEsamiView;

	BOOL m_bInitializing;

};

#endif /* _RICHIESTEANATOMIAPATOLOGICADLG_H_ */