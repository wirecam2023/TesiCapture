#ifndef _DIAGNOSIICD9FORM_H_
	#define _DIAGNOSIICD9FORM_H_

#include "DiagnosiICD9Combo.h"
#include "SubForm.h"

class CDiagnosiICD9Form : public CSubForm
{

public:

	CDiagnosiICD9Form(CWnd* pParent, CEsamiView* pEsamiView);
	~CDiagnosiICD9Form();

	enum { IDD = IDD_SUBFORM_DIAGNOSIICD9 };

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

	CDiagnosiICD9Combo m_ctrlDiagnosi[3];
	CStaticLocalize m_ctrlStatic;

	STRUCT_DIAGNOSIICD9 m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	virtual BOOL IsLineDirty(int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);

	void SaveForm(BOOL bPaziente, long* pParamOfFilter, CBaseSet* pSet, long* pCounterSet, long* pParamSet);

	afx_msg void OnChangeDiagnosi1();
	afx_msg void OnChangeDiagnosi2();
	afx_msg void OnChangeDiagnosi3();
	afx_msg void OnBnClickedBtnGruppi();
	afx_msg void OnBnClickedBtnReset();

	CButtonLocalize m_ctrlButtonGruppi;
	CButtonLocalize m_ctrlButtonReset;

	int m_nSearchMode;
};

#endif /* _DIAGNOSIICD9FORM_H_ */