#ifndef _ACCESSORIFORM5RIGHE_H_
	#define _ACCESSORIFORM5RIGHE_H_

#include "AccessoriCombo.h"
#include "SubForm.h"

class CAccessoriForm5Righe : public CSubForm
{

public:

	CAccessoriForm5Righe(CWnd* pParent, CEsamiView* pEsamiView);
	~CAccessoriForm5Righe();

	enum { IDD = IDD_SUBFORM_ACCESSORI_5RIGHE };

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

	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedRadioAnd();
	afx_msg void OnBnClickedRadioOr();
	afx_msg void OnChangeAccessorio1();
	afx_msg void OnChangeAccessorio2();
	afx_msg void OnChangeAccessorio3();
	afx_msg void OnChangeAccessorio4();
	afx_msg void OnChangeAccessorio5();
	afx_msg void OnChangeQta1();
	afx_msg void OnChangeQta2();
	afx_msg void OnChangeQta3();
	afx_msg void OnChangeQta4();
	afx_msg void OnChangeQta5();

private:

	CAccessoriCombo m_ctrlAccessori[5];
	CStaticLocalize m_ctrlStatic;

	STRUCT_ACCESSORI m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	virtual BOOL IsLineDirty(int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);

	CButton m_ctrlButtonGruppi;
	CButton m_ctrlButtonReset;

	int m_nSearchMode;

};

#endif /* _ACCESSORIFORM5RIGHE_H_ */