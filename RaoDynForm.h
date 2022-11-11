#ifndef _RAODYNFORM_H_
	#define _RAODYNFORM_H_

#include "EndoxDynForm.h"
#include "afxwin.h"

class CRaoDynForm : public CEndoxDynForm
{

public:

	CRaoDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CRaoDynForm();

	enum { IDD = IDD_SUBFORM_RAO };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	afx_msg void OnCbnSelchangeComboRao();
	afx_msg void OnCbnSelchangeComboRaoSpec();
	afx_msg void OnChangeCheckConcordanza();
	afx_msg void OnChangeCheckRicerca();

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	CButton m_ctrlChkRicerca;
	CComboBox m_cmbRao;
	CComboBox m_cmbRaoSpec;

	BOOL CampoObbligatorioValido();
	long GetContenuto();

	BOOL m_bReadOnly;
};

#endif /* _RAODYNFORM_H_ */