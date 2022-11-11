#ifndef _CHECKDYNFORM_H_
	#define _CHECKDYNFORM_H_

#include "EndoxDynForm.h"
#include "afxwin.h"
#include "MaskDateEdit.h"

class CCheckDynForm : public CEndoxDynForm
{

public:

	CCheckDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CCheckDynForm();

	enum { IDD = IDD_SUBFORM_CHECK };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

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

	CStaticLocalize m_ctrlStaticSearch1;
	CStaticLocalize m_ctrlStaticSearch2;
	CComboBox m_ctrlComboUtenteSearch;
	CMaskDateEdit m_ctrlDataOraSearch;

	BOOL CampoObbligatorioValido();
	long GetContenuto();

	BOOL m_bReadOnly;
	long m_lContenuto;
};

#endif /* _CHECKDYNFORM_H_ */