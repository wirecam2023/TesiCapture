#ifndef _STUDIODYNFORM_H_
	#define _STUDIODYNFORM_H_

#include "EndoxDynForm.h"
#include "MaskEdit.h"

class CStudioDynForm : public CEndoxDynForm
{

public:

	CStudioDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CStudioDynForm();

	enum { IDD = IDD_SUBFORM_STUDIO };

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

	afx_msg void OnEnChangeEditData();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	void RiempiComboStudio();

	//

	CComboBox m_ctrlComboStudio;

	CEdit m_ctrlEditStudio;

	CMaskEdit m_ctrlEditData;
	CEdit m_ctrlEditDiff;

	CStaticLocalize m_ctrlStatic01;

	//

	BOOL m_bReadOnly;

};

#endif /* _STUDIODYNFORM_H_ */