#ifndef _ANATOMIAPATOLOGICADLG_H_
	#define _ANATOMIAPATOLOGICADLG_H_

#include "afxcmn.h"
#include "AnatomiaPatologicaListCtrl.h"

class CAnatomiaPatologicaDlg : public CDialog
{
	DECLARE_DYNAMIC(CAnatomiaPatologicaDlg)

public:

	CAnatomiaPatologicaDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CAnatomiaPatologicaDlg();

	enum { IDD = IDD_ANATOMIAPATOLOGICA_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnClickedBtnDel();
	afx_msg void OnClickedBtnEdt();
	afx_msg void OnClickedBtnNew();
	afx_msg void OnClickedBtnStampaTutti();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();
	static void StampaRiga(long lRecord, CEsamiView* pEsamiView);

	CImageList m_ctrlImageList;

	CAnatomiaPatologicaListCtrl m_ctrlList;
	CEsamiView* m_pEsamiView;
};

#endif /* _ANATOMIAPATOLOGICADLG_H_ */