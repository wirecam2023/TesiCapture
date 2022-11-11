#ifndef _ANATOMIAPATOLOGICASEARCHDLG_H_
	#define _ANATOMIAPATOLOGICASEARCHDLG_H_

#include "afxwin.h"

// #include "afxwin.h"
// #include "AnatomiaPatologicaSet.h"

class CAnatomiaPatologicaSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CAnatomiaPatologicaSearchDlg)

public:

	CAnatomiaPatologicaSearchDlg(CWnd* pParent, CListCtrl* pListCtrl);
	virtual ~CAnatomiaPatologicaSearchDlg();

	enum { IDD = IDD_ANATOMIAPATOLOGICA_SEARCH_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCbnSelchangeComboCodice();
	afx_msg void OnCbnSelchangeComboDescrizione();
	afx_msg void OnDestroy();

private:

	void ResetContentCodice();
	void ResetContentDescrizione();

	void RiempiComboCodice();
	void RiempiComboDescrizione();

	CListCtrl* m_pListCtrl;

	CComboBox m_ctrlComboCodice;
	CComboBox m_ctrlComboDescrizione;

};

#endif /* _ANATOMIAPATOLOGICASEARCHDLG_H_ */