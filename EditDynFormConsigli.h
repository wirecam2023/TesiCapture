#ifndef _EDITDYNFORMCONSIGLI_H_
	#define _EDITDYNFORMCONSIGLI_H_

#include "EndoxDynForm.h"
#include "FrasiNewEdit.h"

class CEditDynFormConsigli : public CEndoxDynForm
{

public:

	CEditDynFormConsigli(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEditDynFormConsigli();

	enum { IDD = IDD_SUBFORM_EDITCONSIGLI };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnStampa();

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	long m_lContenuto;

	static CFrasiNewEdit m_ctrlAnatomiaPatologicaSugger1;
	static CFrasiNewEdit m_ctrlAnatomiaPatologicaSugger2;

	CButtonLocalize m_ctrlButtonStampa;

};

#endif /* _EDITDYNFORMCONSIGLI_H_ */