#ifndef _ABITUDINIDYNFORM_H_
	#define _ABITUDINIDYNFORM_H_

#include "EndoxDynForm.h"
#include "ExtEdit.h"
#include "ExtFarmaci.h"

class CAbitudiniDynForm : public CEndoxDynForm
{

public:

	CAbitudiniDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CAbitudiniDynForm();

	enum { IDD = IDD_SUBFORM_ABITUDINI };

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

	afx_msg void OnEnChangePeso();
	afx_msg void OnEnChangeAltezza();

	DECLARE_MESSAGE_MAP()

private:

	void UpdateBMI(float fPeso, float fAltezza);

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CExtEdit m_ctrlTesto[9];
	//CFarmaciExtEdit m_ctrlFarmaci;
	CExtEdit m_ctrlFarmaci;
	CStaticLocalize m_ctrlStatic;
	CEdit m_ctrlEditPeso;
	CEdit m_ctrlEditAltezza;

	float m_fPeso1;
	float m_fPeso2;
	float m_fAltezza1;
	float m_fAltezza2;
	float m_fBMI1;
	float m_fBMI2;

	BOOL m_bAutoUpdate;

};

#endif /* _ABITUDINIDYNFORM_H_ */