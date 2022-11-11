#ifndef _REFERTOFORM_H_
	#define _REFERTOFORM_H_

#include "EndoxDynForm.h"
#include "TXTextControl23.h"

class CRefertoForm : public CEndoxDynForm
{

public:

	CRefertoForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CRefertoForm();

	enum { IDD = IDD_SUBFORM_REFERTO };

	CTXTextControl23Ex m_ctrlTextControl;

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lIDFaseBlocco);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedBtnReferto();
	afx_msg void OnBnClickedBtnRefertoGenomica();//Julio Genomica

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonReferto;
	CButtonLocalize m_ctrlButtonRefertoGenomica;//Julio Genomica
	CStaticLocalize m_ctrlStaticUser;

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	//

	CString m_sTempDataOra;
	long m_lTempRedattore;
	BOOL m_bTempScaduto;
	long m_lTempStato;

	virtual afx_msg LRESULT OnFormReadOnly(WPARAM wParam = 0 /* passare TRUE o FALSE */, LPARAM lParam = 0);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

};

#endif /* _REFERTOFORM_H_ */