#ifndef _REGIONEFORM5RIGHE_H_
	#define _REGIONEFORM5RIGHE_H_

#include "RegioneCombo.h"
#include "SubForm.h"

class CRegioneForm5Righe : public CSubForm
{

public:

	CRegioneForm5Righe(CWnd* pParent, CEsamiView* pEsamiView);
	~CRegioneForm5Righe();

	enum { IDD = IDD_SUBFORM_REGIONE_5RIGHE };

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

	CRegioneCombo m_ctrlRegione[5];
	CStaticLocalize m_ctrlStatic;

	STRUCT_REGIONE m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	virtual BOOL IsLineDirty(int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);

	void SaveForm(BOOL bPaziente, long* pParamOfFilter, CBaseSet* pSet, long* pCounterSet, long* pParamSet);

	afx_msg void OnChangeRegione1();
	afx_msg void OnChangeRegione2();
	afx_msg void OnChangeRegione3();
	afx_msg void OnChangeRegione4();
	afx_msg void OnChangeRegione5();
	afx_msg void OnChangeQta1();
	afx_msg void OnChangeQta2();
	afx_msg void OnChangeQta3();
	afx_msg void OnChangeQta4();
	afx_msg void OnChangeQta5();
	afx_msg void OnBnClickedBtnGruppi();
	afx_msg void OnBnClickedBtnReset();

	CButtonLocalize m_ctrlButtonGruppi;
	CButtonLocalize m_ctrlButtonReset;

	int m_nSearchMode;
};

#endif /* _REGIONEFORM5RIGHE_H_ */