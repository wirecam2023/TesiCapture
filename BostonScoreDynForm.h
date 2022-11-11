#ifndef _BOSTONSCOREDYNFORM_H_
	#define _BOSTONSCOREDYNFORM_H_

#include "EndoxDynForm.h"

class CEsamiView;

class CBostonScoreDynForm : public CEndoxDynForm
{

public:

	CBostonScoreDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CBostonScoreDynForm();

	enum { IDD = IDD_SUBFORM_BOSTONSCORE };  

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

	afx_msg void OnCbnSelchangeComboDx();
	afx_msg void OnCbnSelchangeComboMid();
	afx_msg void OnCbnSelchangeComboSx();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	void AggiornaScore();

	//

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CComboBox m_ctrlComboDx;
	CComboBox m_ctrlComboMid;
	CComboBox m_ctrlComboSx;
	CStatic m_ctrlStaticTotale;
	CStatic m_ctrlStaticFrase;

};

#endif /* _BOSTONSCOREDYNFORM_H_ */