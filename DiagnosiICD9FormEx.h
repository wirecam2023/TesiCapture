#ifndef _DIAGNOSIICD9FORMEX_H_
	#define _DIAGNOSIICD9FORMEX_H_

#include "SubForm.h"
#include "MaskEdit.h"
#include "ExtDiagnosiICD9Edit.h"

class CDiagnosiICD9FormEx : public CSubForm
{

public:

	CDiagnosiICD9FormEx(CWnd* pParent, CEsamiView* pEsamiView);
	~CDiagnosiICD9FormEx();

	enum { IDD = IDD_SUBFORM_DIAGNOSIICD9EX};

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

	CExtDiagnosiICD9Edit m_ctrlDiagnosi[3];
	CStatic m_ctrlStatic;

	STRUCT_DIAGNOSIICD9 m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsLineDirty(int nCounter);
	virtual BOOL IsValidSet(int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	afx_msg void OnChangeDiagnosi1();
	afx_msg void OnChangeDiagnosi2();
	afx_msg void OnChangeDiagnosi3();

};

#endif /* _DIAGNOSIICD9FORMEX_H_ */