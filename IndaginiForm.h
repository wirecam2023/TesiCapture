#ifndef _INDAGINIFORM_H_
	#define _INDAGINIFORM_H_

#include "ExtEdit.h"
#include "SubForm.h"

class CIndaginiForm : public CSubForm
{

public:

	CIndaginiForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CIndaginiForm();

	enum { IDD = IDD_SUBFORM_INDAGINI };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormClone(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	CExtEdit m_ctrlIndagine[3];
	CStaticLocalize m_ctrlStatic[2];

	STRUCT_INDAGINI m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsLineDirty(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	afx_msg void OnChangeIndagine1();
	afx_msg void OnChangeIndagine2();
	afx_msg void OnChangeIndagine3();
	afx_msg void OnChangePatologico1();
	afx_msg void OnChangePatologico2();
	afx_msg void OnChangePatologico3();

};

#endif /* _INDAGINIFORM_H_ */