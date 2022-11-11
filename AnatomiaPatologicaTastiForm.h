#ifndef _ANATOMIAPATOLOGICATASTIFORM_H_
	#define _ANATOMIAPATOLOGICATASTIFORM_H_

#include "SubForm.h"
#include "afxcmn.h"
#include "afxwin.h"

class CAnatomiaPatologicaTastiForm : public CEndoxDynForm
{

public:

	CAnatomiaPatologicaTastiForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CAnatomiaPatologicaTastiForm();

	enum { IDD = IDD_SUBFORM_ANATOMIAPATOLOGICA_TASTI };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	BOOL InviaRichiestaProc();

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnAnnulla();
	afx_msg void OnBnClickedBtnInvia();
	afx_msg void OnBnClickedBtnStampa();
	afx_msg void OnBnClickedCheckVerificato();
	afx_msg void OnCbnSelchangeComboSpedireRitirare();

	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);

	void InviaRichiesta();
	void AnnullaRichiesta();
	void PSMGo();

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	BOOL m_bReadOnly;
	// long m_lStato; // Sandro 01/02/2013 - RAS 20130022 //

	CButtonLocalize m_ctrlButtonAnnulla;
	CButtonLocalize m_ctrlButtonInvia;
	CButtonLocalize m_ctrlButtonStampa;
	CButtonLocalize m_ctrlCheckVerificato;

	CComboBox m_ctrlComboMedico;
	CComboBox m_ctrlComboSpedireRitirare;

	CEdit m_ctrlEditIndirizzo;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;

	CStatic m_ctrlStatic5;
	CStatic m_ctrlStaticStato;

	CString m_sDataVerifica;
	CString m_sDataSpedRit;

};

#endif /* _ANATOMIAPATOLOGICATASTIFORM_H_ */