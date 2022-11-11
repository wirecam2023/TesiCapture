#ifndef _ANATOMIAPATOLOGICAPRESTFORM_H_
	#define _ANATOMIAPATOLOGICAPRESTFORM_H_

#include "SubForm.h"
#include "afxcmn.h"
#include "afxwin.h"

class CAnatomiaPatologicaPrestForm : public CEndoxDynForm
{

public:

	CAnatomiaPatologicaPrestForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CAnatomiaPatologicaPrestForm();

	// enum { IDD = IDD_SUBFORM_ANATOMIAPATOLOGICA_PREST };

	static void CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);
	static BOOL CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CAnatomiaPatologicaPrestForm** pForm);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);

	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	WPARAM m_wpReadOnly;
	BOOL m_bEsameOK;

	CListCtrlLocalize m_ctrlList;
	CButton m_ctrlButtonNew;
	CButton m_ctrlButtonEdt;
	CButton m_ctrlButtonDel;
};

#endif /* _ANATOMIAPATOLOGICAPRESTFORM_H_ */