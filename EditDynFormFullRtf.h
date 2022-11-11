#ifndef _EDITDYNFORMFULLRTF_H_
	#define _EDITDYNFORMFULLRTF_H_

#include "EditDynFormToolbar.h"
#include "EndoxDynForm.h"
#include "SpellCheckerDlg.h"
#include "TXTextControl23.h"
#include "TXButtonBar23.h"

class CEditDynFormFullRtf : public CEndoxDynForm
{

public:

	CEditDynFormFullRtf(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEditDynFormFullRtf();

	enum { IDD = IDD_SUBFORM_EDITFULLRTF };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

	void SetText(CString value);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnSize(UINT nType, int cx, int cy);

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

	afx_msg void OnBnClickedBtnChecklist();
	afx_msg void OnBnClickedBtnData();
	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();

private:

	void OnChangeTextControlForWSpell();
	void OnMouseDownTextControl(short Button, short Shift, long X, long Y);

	CTXButtonBar23Ex m_ctrlButtonBar;
	CEditDynFormToolbar m_ctrlToolbar;
	CButtonLocalize m_ctrlBtnCheckList;
	CButtonLocalize m_ctrlBtnData1;
	CButtonLocalize m_ctrlBtnData2;
	CTXTextControl23Ex m_ctrlTextControl;

	CSpellCheckerDlg* GetWSpell(); // Sandro 07/05/2012 //
	void DestroyWSpell(); // Sandro 07/05/2012 //

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	long m_lContenuto;
	BOOL m_bReadOnly;

	CList<long> m_elementCLSearchList;

	static CSpellCheckerDlg m_WSpellChecker[40]; // Sandro 07/05/2012 //

};

#endif /* _EDITDYNFORMFULLRTF_H_ */