#ifndef _FAMILIARITAFORM_H_
	#define _FAMILIARITAFORM_H_

#include "ExtEdit.h"
#include "SubForm.h"

class CFamiliaritaForm : public CSubForm
{

public:

	CFamiliaritaForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CFamiliaritaForm();

	enum { IDD = IDD_SUBFORM_FAMILIARITA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormAnnullaPaziente(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	CExtEdit m_ctrlFamiliarita[3];
	CExtEdit m_ctrlParentela[3];
	CStaticLocalize m_ctrlStatic[2];

	STRUCT_FAMILIARITA m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsLineDirty(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	afx_msg void OnChangeFamiliarita1();
	afx_msg void OnChangeFamiliarita2();
	afx_msg void OnChangeFamiliarita3();
	afx_msg void OnChangeParentela1();
	afx_msg void OnChangeParentela2();
	afx_msg void OnChangeParentela3();

};

#endif /* _FAMILIARITAFORM_H_ */