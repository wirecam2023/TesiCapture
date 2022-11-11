#ifndef _INVIANTEDYNFORM_H_
	#define _INVIANTEDYNFORM_H_

#include "EndoxDynForm.h"
#include "ProvenienzeCombo.h"
#include "ExtProvenienza.h"

class CInvianteDynForm : public CEndoxDynForm
{

public:

	CInvianteDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CInvianteDynForm();

	enum { IDD = IDD_SUBFORM_INVIANTE };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);
	BOOL HasValue();

protected:

	afx_msg void OnChangeProvenienza();

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

	afx_msg void OnEnSetfocusEditProvenienza();
	afx_msg void OnCbnSetfocusComboProvenienza();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CProvenienzeCombo m_ctrlComboProvenienza;
	CExtProvenienza m_ctrlEditProvenienza;

public:
	afx_msg void OnCbnSelchangeComboProvenienza();
	afx_msg void OnEnChangeEditProvenienza();
};

#endif /* _INVIANTEDYNFORM_H_ */