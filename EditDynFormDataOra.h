#ifndef _EDITDYNFORMDATAORA_H_
	#define _EDITDYNFORMDATAORA_H_

#include "EndoxDynForm.h"
#include "ExtDateEdit.h"

class CEditDynFormDataOra : public CEndoxDynForm
{

public:

	CEditDynFormDataOra(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEditDynFormDataOra();

	enum { IDD = IDD_SUBFORM_EDITDATAORA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButton();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	long m_lContenuto;

	CButton m_ctrlBtnButton;

	static CExtDateEdit m_ctrlDataOra000;
	static CExtDateEdit m_ctrlDataOra001;
	static CExtDateEdit m_ctrlDataOra002;
	static CExtDateEdit m_ctrlDataOra003;
	static CExtDateEdit m_ctrlDataOra004;
	static CExtDateEdit m_ctrlDataOra005;
	static CExtDateEdit m_ctrlDataOra006;
	static CExtDateEdit m_ctrlDataOra007;
	static CExtDateEdit m_ctrlDataOra008;
	static CExtDateEdit m_ctrlDataOra009;
	static CExtDateEdit m_ctrlDataOra010;
	static CExtDateEdit m_ctrlDataOra011;
	static CExtDateEdit m_ctrlDataOra012;
	static CExtDateEdit m_ctrlDataOra013;
	static CExtDateEdit m_ctrlDataOra014;
	static CExtDateEdit m_ctrlDataOra015;
	static CExtDateEdit m_ctrlDataOra016;
	static CExtDateEdit m_ctrlDataOra017;
	static CExtDateEdit m_ctrlDataOra018;
	static CExtDateEdit m_ctrlDataOra019;
	static CExtDateEdit m_ctrlDataRefertoIstologico;

};

#endif /* _EDITDYNFORMDATAORA_H_ */