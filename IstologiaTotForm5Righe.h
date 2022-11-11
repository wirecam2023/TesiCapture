#ifndef _ISTOLOGIATOTFORM5RIGHE_H_
	#define _ISTOLOGIATOTFORM5RIGHE_H_

#include "OrganoDiagnosiEdit.h"
#include "SubForm.h"

class CIstologiaTotForm5Righe : public CSubForm
{

public:

	CIstologiaTotForm5Righe(CWnd* pParent, CEsamiView* pEsamiView);
	~CIstologiaTotForm5Righe();

	enum { IDD = IDD_SUBFORM_ISTOLOGIA_COMPLETA_5RIGHE };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	CString GetField(int nSubItem);
	void StampaTutteLeRighe(); // Sandro 19/09/2013 // RAS 20130099 //

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

	afx_msg void OnBnClickedGruppi();
	afx_msg void OnBnClickedStampaTutte();
	afx_msg void OnBnClickedStampa1();
	afx_msg void OnBnClickedStampa2();
	afx_msg void OnBnClickedStampa3();
	afx_msg void OnBnClickedStampa4();
	afx_msg void OnBnClickedStampa5();

private:

	COrganoDiagnosiEdit m_ctrlOrgano[5];
	COrganoDiagnosiEdit m_ctrlSede[5];
	COrganoDiagnosiEdit m_ctrlDiagnosi[5];
	CComboBox m_ctrlTipo[5];
	CStaticLocalize m_ctrlStatic[8];
	CButtonLocalize m_ctrlStampa[5];
	CButtonLocalize m_ctrlBtnGruppi;
	CButtonLocalize m_ctrlButtonStampaTutte;

	int m_rigaSelezionata;
	BOOL m_bStampaTutte;

	STRUCT_ISTOLOGIA m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();
	static void StampaRiga(CEsamiView* pEsamiView);

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsLineDirty(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	afx_msg void OnChangeOrgano1();
	afx_msg void OnChangeOrgano2();
	afx_msg void OnChangeOrgano3();
	afx_msg void OnChangeOrgano4();
	afx_msg void OnChangeOrgano5();
	afx_msg void OnChangeSede1();
	afx_msg void OnChangeSede2();
	afx_msg void OnChangeSede3();
	afx_msg void OnChangeSede4();
	afx_msg void OnChangeSede5();
	afx_msg void OnChangeTipo1();
	afx_msg void OnChangeTipo2();
	afx_msg void OnChangeTipo3();
	afx_msg void OnChangeTipo4();
	afx_msg void OnChangeTipo5();
	afx_msg void OnChangeProvette1();
	afx_msg void OnChangeProvette2();
	afx_msg void OnChangeProvette3();
	afx_msg void OnChangeProvette4();
	afx_msg void OnChangeProvette5();
	afx_msg void OnChangeDiagnosi1();
	afx_msg void OnChangeDiagnosi2();
	afx_msg void OnChangeDiagnosi3();
	afx_msg void OnChangeDiagnosi4();
	afx_msg void OnChangeDiagnosi5();

};

#endif /* _ISTOLOGIATOTFORM5RIGHE_H_ */