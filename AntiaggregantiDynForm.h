#ifndef _ANTIAGGREGANTIDYNFORM_H_
	#define _ANTIAGGREGANTIDYNFORM_H_

#include "EndoxDynForm.h"
#include "MyRadio.h"

class CAntiaggregantiDynForm : public CEndoxDynForm
{

public:

	CAntiaggregantiDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CAntiaggregantiDynForm();

	enum { IDD = IDD_SUBFORM_ANTIAGGREGANTI };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	afx_msg void OnClickedRadio1();
	afx_msg void OnClickedRadio2();
	afx_msg void OnClickedRadio3();

	afx_msg void OnStnClickedStatic1();
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnStnClickedStatic4();

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
	CMyRadio m_ctrlRadio3;

	CStaticLocalize m_ctrlStaticAntiaggreganti;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;

};

#endif /* _ANTIAGGREGANTIDYNFORM_H_ */