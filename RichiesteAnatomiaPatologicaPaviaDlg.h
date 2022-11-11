#ifndef _RICHIESTEANATOMIAPATOLOGICAPAVIADLG_H_
	#define _RICHIESTEANATOMIAPATOLOGICAPAVIADLG_H_

#include "EndoxResizableDlg.h"
#include "MaskEdit.h"
#include "QueryUtility.h"

class CRichiesteAnatomiaPatologicaPaviaDlg : public CEndoxResizableDlg , public CQueryUtility
{
	DECLARE_DYNAMIC(CRichiesteAnatomiaPatologicaPaviaDlg)

public:

	CRichiesteAnatomiaPatologicaPaviaDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CRichiesteAnatomiaPatologicaPaviaDlg();

	enum { IDD = IDD_RICHIESTEANATOMIAPATOLOGICA_PAVIA };

	void CreateModelessDialog(CWnd* pParent);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnBnClickedBtnAggiorna();
	afx_msg void OnCbnSelchangeComboMedico();
	afx_msg void OnCbnSelchangeComboData();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnShowSospesiIstologiciWnd(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();

	CListCtrlLocalize m_ctrlList;

	CComboBox m_ctrlComboMedico;
	CComboBox m_ctrlComboData;

	CMaskEdit m_ctrlDataFine;
	CMaskEdit m_ctrlDataIniz;

	CEsamiView* m_pEsamiView;

	BOOL m_bInitializing;

};

#endif /* _RICHIESTEANATOMIAPATOLOGICAPAVIADLG_H_ */