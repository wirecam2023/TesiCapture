#ifndef _ISTOLOGIATOTFORM_H_
	#define _ISTOLOGIATOTFORM_H_

#include "OrganoEdit.h"
#include "SubForm.h"

class CIstologiaTotForm : public CSubForm
{

public:

	CIstologiaTotForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CIstologiaTotForm();

	enum { IDD = IDD_SUBFORM_ISTOLOGIA_COMPLETA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

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

private:

	COrganoEdit m_ctrlOrgano[3];
	COrganoEdit m_ctrlSede[3];
	CComboBox m_ctrlTipo[3];
	CEdit m_ctrlDiagnosi[3];
	CStaticLocalize m_ctrlStatic[6];
	CButtonLocalize m_ctrlStampa[3];
	CButtonLocalize m_ctrlButtonStampaTutte;

	int m_rigaSelezionata;

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
	afx_msg void OnChangeSede1();
	afx_msg void OnChangeSede2();
	afx_msg void OnChangeSede3();
	afx_msg void OnChangeTipo1();
	afx_msg void OnChangeTipo2();
	afx_msg void OnChangeTipo3();
	afx_msg void OnChangeProvette1();
	afx_msg void OnChangeProvette2();
	afx_msg void OnChangeProvette3();
	afx_msg void OnChangeDiagnosi1();
	afx_msg void OnChangeDiagnosi2();
	afx_msg void OnChangeDiagnosi3();

	afx_msg void OnBnClickedStampaTutte();
	afx_msg void OnBnClickedStampa1();
	afx_msg void OnBnClickedStampa2();
	afx_msg void OnBnClickedStampa3();

public:

	CString GetField(int nSubItem);
};

#endif /* _ISTOLOGIATOTFORM_H_ */