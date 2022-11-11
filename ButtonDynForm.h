#ifndef _BUTTONDYNFORM_H_
	#define _BUTTONDYNFORM_H_

#include "EndoxDynForm.h"
#include "ExtDateEdit.h"
#include "MediciCombo.h"

class CButtonDynForm : public CEndoxDynForm
{

public:

	CButtonDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CButtonDynForm();

	enum { IDD = IDD_SUBFORM_BUTTON };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnClickButton();

	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	CStaticLocalize m_ctrlStatic;
	CStaticLocalize m_ctrlStaticSearch1;
	CStaticLocalize m_ctrlStaticSearch2;
	CMediciCombo m_ctrlComboUtenteSearch;	
	CExtDateEdit m_ctrlDataOraSearch;

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	void SetButtonText();		

	long m_lContenuto;

	static CButton m_ctrlButtonOsservazioni;
	static CButton m_ctrlButtonDiagnostiche;
	static CButton m_ctrlButtonTerapeutiche;
	static CButton m_ctrlButtonDiagnosi;
	static CButton m_ctrlButtonCodificaDiagnosiEsame;
	static CButton m_ctrlButtonConvalida;
	static CButton m_ctrlButtonChiusuraEsame;
	static CButton m_ctrlButtonComplicanze1;
	static CButton m_ctrlButtonComplicanze2;
	static CButton m_ctrlButtonComplicanze3;
	static CButton m_ctrlButtonVideocapsula;
	static CButton m_ctrlButtonStampa[NUM_LABEL_TASTO_STAMPA];
	static CButton m_ctrlButtonBrowser[NUM_LABEL_TASTO_BROWSER];
	static CButton m_ctrlButtonEseguibile[NUM_LABEL_TASTO_EXEC];
	static CButton m_ctrlButtonChiusuraFase[NUM_LABEL_TASTO_CHIUSURAFASE];
	static CButton m_ctrlButtonCentraleRefertazione;
	static CButton m_ctrlButtonCarestream;
	static CButton m_ctrlButtonInviaAltraUnita; //Gabriel - TCP

	BOOL DoCentraleRefertazione(); // Marvel Carvalho - BUG 4621 Pop up central de laudos
	BOOL InviaAltraUnita(); //Gabriel - TCP

public:
	afx_msg void OnCbnSelchangeComboUser();
};

#endif /* _BUTTONDYNFORM_H_ */