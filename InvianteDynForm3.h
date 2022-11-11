#ifndef _INVIANTEDYNFORM3_H_
	#define _INVIANTEDYNFORM3_H_

#include "EndoxDynForm.h"
#include "ExtEdit.h"

class CInvianteDynForm3 : public CEndoxDynForm
{

public:

	CInvianteDynForm3(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CInvianteDynForm3();

	enum { IDD = IDD_SUBFORM_INVIANTE3 };

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

	afx_msg void OnEnSetfocusEditInterni();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CStaticLocalize m_ctrlLabel;
	CExtEdit m_ctrlTipoDegenzaInterno;
	CExtEdit m_ctrlTipoDegenzaEsterno;

};

#endif /* _INVIANTEDYNFORM3_H_ */