#ifndef _EDITDYNFORMCODICEDESCRIZIONE_H_
	#define _EDITDYNFORMCODICEDESCRIZIONE_H_

#include "EndoxDynForm.h"
#include "MyEdit.h"

class CEsamiView;

class CEditDynFormCodiceDescrizione : public CEndoxDynForm
{

public:

	CEditDynFormCodiceDescrizione(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEditDynFormCodiceDescrizione();

	enum { IDD = IDD_SUBFORM_EDITCODICEDESCRIZIONE };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

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

	LRESULT OnCheckValue(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	afx_msg void OnBnSetfocusButton1();
	afx_msg void OnBnSetfocusButton2();

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();

private:

	struct tagITEM
	{
		tagITEM()
		{
			ZeroMemory(this, sizeof(tagITEM));
		}

		long lID;
		TCHAR szCode[1024];
		TCHAR szDescription[1024];
		BOOL bUserSpecific;
		BOOL bLibero;
	};

	BOOL CampoObbligatorioValido();
	long GetContenuto();

	void OnOK1(long lSel);
	void OnOK2(long lSel);

	//

	CMyEdit m_ctrlEdit1;
	CMyEdit m_ctrlEdit2;
	CButton m_ctrlButton1;
	CButton m_ctrlButton2;

	//

	long m_lContenuto;

	BOOL m_bResetting1;
	BOOL m_bResetting2;
	BOOL m_bLibero;
	BOOL m_bOK;

	long m_lID;

};

#endif /* _EDITDYNFORMCODICEDESCRIZIONE_H_ */