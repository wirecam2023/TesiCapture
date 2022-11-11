#ifndef _CODICICLASSIFICAZIONEDIAGNOSTICADYNFORM_H_
	#define _CODICICLASSIFICAZIONEDIAGNOSTICADYNFORM_H_

#include "EndoxDynForm.h"

class CCodiciClassificazioneDiagnosticaDynForm : public CEndoxDynForm
{

public:

	CCodiciClassificazioneDiagnosticaDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CCodiciClassificazioneDiagnosticaDynForm();

	enum { IDD = IDD_SUBFORM_CODICICLASSIFICAZIONEDIAGNOSTICA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	void SetText(CString value);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormFocusLost(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	//

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;

	CButtonLocalize m_ctrlRadio1;
	CButtonLocalize m_ctrlRadio2;

	CListCtrl m_ctrlList;

	CStaticLocalize m_ctrlStaticTitle;

	//

	BOOL m_bReadOnly;
	int m_iRadioSearch;

};

#endif /* _CODICICLASSIFICAZIONEDIAGNOSTICADYNFORM_H_ */