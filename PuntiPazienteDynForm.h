#ifndef _PUNTIPAZIENTEDYNFORM_H_
	#define _PUNTIPAZIENTEDYNFORM_H_

#include "EndoxDynForm.h"

class CPuntiPazienteDynForm : public CEndoxDynForm
{

public:

	CPuntiPazienteDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CPuntiPazienteDynForm();

	enum { IDD = IDD_SUBFORM_PUNTIPAZIENTE };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	BOOL CampoObbligatorioValido();
	long GetContenuto();
	void RiempiLista();

	CListCtrl m_ctrlList;
	CStaticLocalize m_ctrlStaticTitle;
	CStaticLocalize m_ctrlStatic00;
	CComboBox m_ctrlCombo;

};

#endif /* _PUNTIPAZIENTEDYNFORM_H_ */