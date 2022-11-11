#ifndef _ESAMIPREGRESSIFORM_H_
	#define _ESAMIPREGRESSIFORM_H_

#include "ExtEdit.h"
#include "MaskEdit.h"
#include "SubForm.h"

class CEsamiPregressiForm : public CSubForm
{

public:

	CEsamiPregressiForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CEsamiPregressiForm();

	enum { IDD = IDD_SUBFORM_ESAMIPREGRESSI };

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

	CExtEdit m_ctrlEsamiPregressi[3];
	CMaskEdit m_ctrlData[3];
	CStaticLocalize m_ctrlStatic[3];

	STRUCT_ESAMIPREGRESSI m_ctrLine[MAX_OBJ_X_FORM];

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	virtual void ModificaForm();

	virtual long GetCounterSetOfLine(int nCounter);
	virtual BOOL IsLineDirty(int nCounter);
	virtual BOOL IsValidSet (int nCounter);
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty);
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet);

	afx_msg void OnChangeEsamePregresso1();
	afx_msg void OnChangeEsamePregresso2();
	afx_msg void OnChangeEsamePregresso3();
	afx_msg void OnChangeData1();
	afx_msg void OnChangeData2();
	afx_msg void OnChangeData3();
	afx_msg void OnChangeEsito1();
	afx_msg void OnChangeEsito2();
	afx_msg void OnChangeEsito3();

};

#endif /* _ESAMIPREGRESSIFORM_H_ */