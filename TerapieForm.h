#ifndef _TERAPIEFORM_H_
	#define _TERAPIEFORM_H_

#include "SubForm.h"
#include "ExtFarmaci.h"
#include "ExtEdit.h"

class CTerapieForm : public CSubForm
{

public:

	CTerapieForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CTerapieForm();

	enum { IDD = IDD_SUBFORM_TERAPIE };

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

	CExtEdit m_ctrlTerapiaCombo[3];
	CFarmaciExtEdit m_ctrlTerapiaPront[3];
	CExtEdit m_ctrlDurata[3];
	CExtEdit m_ctrlDose[3];
	CStaticLocalize m_ctrlStatic[3];

	STRUCT_TERAPIA m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsLineDirty(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);
							
	afx_msg void OnChangeTerapia1();
	afx_msg void OnChangeTerapia2();
	afx_msg void OnChangeTerapia3();
	afx_msg void OnChangeDurata1();
	afx_msg void OnChangeDurata2();
	afx_msg void OnChangeDurata3();
	afx_msg void OnChangeDose1();
	afx_msg void OnChangeDose2();
	afx_msg void OnChangeDose3();

};

#endif /* _TERAPIEFORM_H_ */