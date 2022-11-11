#ifndef _INVIANTEDYNFORM1_H_
	#define _INVIANTEDYNFORM1_H_

#include "EndoxDynForm.h"

#include "ExtEdit.h"
#include "InviantiCombo.h"
#include "ExtInviante.h"
#include "ExtOspedale.h"

class CInvianteDynForm1 : public CEndoxDynForm
{

public:

	CInvianteDynForm1(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CInvianteDynForm1();

	enum { IDD = IDD_SUBFORM_INVIANTE1 };

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

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CExtEdit m_ctrlEditOspedale;
	CInviantiCombo m_ctrlComboComune;
	CExtInviante m_ctrlEditComune;
	CInviantiCombo m_ctrlComboReparto;
	CExtInviante m_ctrlEditReparto;
	CExtOspedale m_ctrlEditOspedaleEx;
};

#endif /* _INVIANTEDYNFORM1_H_ */