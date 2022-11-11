#ifndef _ANTICOAGULANTIDYNFORM_H_
	#define _ANTICOAGULANTIDYNFORM_H_

#include "EndoxDynForm.h"
#include "MyRadio.h"

class CAnticoagulantiDynForm : public CEndoxDynForm
{

public:

	CAnticoagulantiDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CAnticoagulantiDynForm();

	enum { IDD = IDD_SUBFORM_ANTICOAGULANTI };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	afx_msg void OnClickedRadio1();
	afx_msg void OnClickedRadio2();

	afx_msg void OnStnClickedStatic1();
	afx_msg void OnStnClickedStatic2();

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

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	BOOL m_bReadOnly;

	CEdit m_ctrlDescrizione;

	CMyRadio m_ctrlRadio1;
	CMyRadio m_ctrlRadio2;

	CStaticLocalize m_ctrlStaticAnticoagulanti;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;

};

#endif /* _ANTICOAGULANTIDYNFORM_H_ */