#ifndef _ORGANOSEDEDYNFORM_H_
	#define _ORGANOSEDEDYNFORM_H_

#include "EndoxDynForm.h"

#include "OrganoEdit.h"

class COrganoSedeDynForm : public CEndoxDynForm
{

public:

	COrganoSedeDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~COrganoSedeDynForm();

	enum { IDD = IDD_SUBFORM_ORGANOSEDE };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

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
	LRESULT OnMessageEditUpdated(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	void SetEditText(CString strEdit);

	COrganoEdit m_ctrlEditOrganoSede;

	long m_lContenuto;

};

#endif /* _ORGANOSEDEDYNFORM_H_ */