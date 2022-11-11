#ifndef _PRESSIONEDYNFORM_H_
	#define _PRESSIONEDYNFORM_H_

#include "EndoxDynForm.h"

class CPressioneDynForm : public CEndoxDynForm
{

public:

	CPressioneDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CPressioneDynForm();

	enum { IDD = IDD_SUBFORM_PRESSIONE };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnEnKillfocusEditPress1();
	afx_msg void OnEnKillfocusEditPress2();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

};

#endif /* _PRESSIONEDYNFORM_H_ */