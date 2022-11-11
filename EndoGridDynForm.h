#pragma once

#include "EndoxDynForm.h"

class CEndoGridChecklist;
class CEsamiView;

class CEndoGridDynForm : public CEndoxDynForm
{

public:
	CEndoGridDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEndoGridDynForm();

	enum { IDD = IDD_SUBFORM_ENDOGRID };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);
	void EvidenziaCampoObbligatorioEx(COLORREF crColor);

	int GetLines();
	CString GetItemText(int row, int col);
	double GetViewDivider();
	void ExpandAll();
	BOOL IsCategory(int index);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	virtual afx_msg LRESULT OnFormLoad(WPARAM wParam = 0, LPARAM lParam = 0);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);

	afx_msg virtual LRESULT OnGridNotify(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	long m_lContenuto;
	BOOL m_bUserCanUseCL;

	CEndoGridChecklist* m_pEndoGrid;
	CButtonLocalize m_ctrlBtnEdit;
	CButtonLocalize m_ctrlBtnEnd;

	CStatic m_ctrlStatic1;
	CStatic m_ctrlStatic2;
public:
	afx_msg void OnBnClickedBtnEdit1();
	afx_msg void OnBnClickedBtnEnd1();
};
