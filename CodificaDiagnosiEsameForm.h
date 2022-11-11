#ifndef _CODIFICADIAGNOSIESAMEFORM_H_
	#define _CODIFICADIAGNOSIESAMEFORM_H_

#include "OrganoEdit.h"
#include "SubForm.h"

class CCodificaDiagnosiEsameForm : public CSubForm
{

public:

	CCodificaDiagnosiEsameForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CCodificaDiagnosiEsameForm();

	enum { IDD = IDD_SUBFORM_CODIFICADIAGNOSIESAME };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);
	static BOOL CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CCodificaDiagnosiEsameForm** pForm);

	BOOL UpdateNewDataLine(CCodificaDiagnosiEsameSet* pNewSet);
	STRUCT_CODIFICADIAGNOSIESAME m_ctrLine[MAX_OBJ_X_FORM];

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

	COrganoEdit m_ctrlOrgano[2];
	COrganoEdit m_ctrlSede[2];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsLineDirty(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	afx_msg void OnChangeOrgano1();
	afx_msg void OnChangeOrgano2();
	afx_msg void OnChangeSede1();
	afx_msg void OnChangeSede2();
	afx_msg void OnChangeCodificaDiagnosiEsame1();
	afx_msg void OnChangeCodificaDiagnosiEsame2();

	static int m_nSearchMode;

};

#endif /* _CODIFICADIAGNOSIESAMEFORM_H_ */