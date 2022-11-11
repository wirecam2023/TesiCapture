#ifndef _PACEMAKERDYNFORM_H_
	#define _PACEMAKERDYNFORM_H_

#include "EndoxDynForm.h"
#include "MyRadio.h"

class CPacemakerDynForm : public CEndoxDynForm
{

public:

	CPacemakerDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CPacemakerDynForm();

	enum { IDD = IDD_SUBFORM_PACEMAKER };

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

	afx_msg void OnStnClickedStatic1();
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnStnClickedStatic4();
	afx_msg void OnStnClickedStatic5();
	afx_msg void OnStnClickedStatic6();
	afx_msg void OnStnClickedStatic7();

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	BOOL m_bReadOnly;

	CMyRadio m_ctrlRadio1;
	CMyRadio m_ctrlRadio2;
	CMyRadio m_ctrlRadio3;
	CMyRadio m_ctrlRadio4;
	CMyRadio m_ctrlRadio5;
	CMyRadio m_ctrlRadio6;
	CMyRadio m_ctrlRadio7;

	CStaticLocalize m_ctrlStaticPacemaker;
	CStaticLocalize m_ctrlTerapia;
	CStaticLocalize m_ctrlTerapia2;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;

};

#endif /* _PACEMAKERDYNFORM_H_ */