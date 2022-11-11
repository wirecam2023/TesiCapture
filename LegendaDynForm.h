#ifndef _LEGENDADYNFORM_H_
	#define _LEGENDADYNFORM_H_

#include "EndoxDynForm.h"

class CLegendaDynForm : public CEndoxDynForm
{

public:

	CLegendaDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CLegendaDynForm();

	enum { IDD = IDD_SUBFORM_LEGENDA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	long m_lContenuto;
};

#endif /* _LEGENDADYNFORM_H_ */