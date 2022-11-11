#ifndef _INVIANTEDYNFORM2_H_
	#define _INVIANTEDYNFORM2_H_

#include "EndoxDynForm.h"

#include "InviantiCombo.h"
#include "ExtInviante.h"
#include "ExtMedicoCuranteInviante.h"

class CInvianteDynForm2 : public CEndoxDynForm
{

public:

	CInvianteDynForm2(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CInvianteDynForm2();

	enum { IDD = IDD_SUBFORM_INVIANTE2 };

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

	afx_msg void OnEnSetfocusEditReparto();
	afx_msg void OnCbnSetfocusComboReparto();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CInviantiCombo m_ctrlComboReparto;
	CExtInviante m_ctrlEditReparto;
	CExtMedicoCuranteInviante m_ctrlEditMedicoCurante;
};

#endif /* _INVIANTEDYNFORM2_H_ */