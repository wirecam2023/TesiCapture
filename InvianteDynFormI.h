#ifndef _INVIANTEDYNFORM_I_H_
	#define _INVIANTEDYNFORM_I_H_

#include "EndoxDynForm.h"

#include "InviantiCombo.h"
#include "ExtInviante.h"

class CInvianteDynFormI : public CEndoxDynForm
{

public:

	CInvianteDynFormI(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CInvianteDynFormI();

	enum { IDD = IDD_SUBFORM_INVIANTE_I };

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
	
};

#endif /* _INVIANTEDYNFORM_I_H_ */