#ifndef _PAZIENTIDLG_H_
	#define _PAZIENTIDLG_H_

#include "ComuneEdit.h"
#include "ExtDateEdit.h"
#include "ExtEdit.h"
#include "ExtMedicoCuranteInviante.h"
#include "InviantiCombo.h"

#define PAZ_SHOW 0
#define PAZ_ADDN 1
#define PAZ_EDIT 2
#define PAZ_SRCH 3

class CPazientiDlg : public CDialog
{
	DECLARE_DYNAMIC(CPazientiDlg)

public:

	CPazientiDlg(CWnd* pParent, CEsamiView* pEsamiView, CPazientiSet* pPazientiSet, int iModalita);
	virtual ~CPazientiDlg();

	enum { IDD = IDD_PAZIENTE_DLG };

	BOOL m_bSearchNow;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSearch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnEnChangeEdit35();
	afx_msg void OnEnSetfocusEdit35();
	afx_msg void OnEnKillfocusEdit35();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton35();

private:

	BOOL CheckComuneDataNascita();

	void OnOkAddnEdit();
	BOOL OnOkAddnEditSG();

	void RiempiComboCronico();
	void RiempiComboDirettore();
	
	CEsamiView* m_pEsamiView;
	CPazientiSet* m_pPazientiSet;
	int m_iModalita;
	//int m_iSessoComboSelIndex;
	BOOL m_bSendEmail;
	BOOL m_bSendSms;
	BOOL m_bValidUser;
	BOOL m_bUserFocus;
	BOOL m_bPazienteDelDirettore;

	CStaticLocalize m_ctrlStaticFrame00;
	CStaticLocalize m_ctrlStaticFrame01;
	CStaticLocalize m_ctrlStaticFrame02;
	CStaticLocalize m_ctrlStaticFrame03;
	CStaticLocalize m_ctrlStaticFrame05;
	CStaticLocalize m_ctrlStaticFrame06;
	CStaticLocalize m_ctrlStaticFrame07;
	CStaticLocalize m_ctrlStaticFrame08; //Julio - BUG 3285 - Adequação de laudos
	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;
	CStaticLocalize m_ctrlStatic07;
	CStaticLocalize m_ctrlStatic08;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStatic12;
	CStaticLocalize m_ctrlStatic13;
	CStaticLocalize m_ctrlStatic14;
	CStaticLocalize m_ctrlStatic15;
	CStaticLocalize m_ctrlStatic16;
	CStaticLocalize m_ctrlStatic17;
	CStaticLocalize m_ctrlStatic18;
	CStaticLocalize m_ctrlStatic19;
	CStaticLocalize m_ctrlStatic20;
	CStaticLocalize m_ctrlStatic21;
	CStaticLocalize m_ctrlStatic22;
	CStaticLocalize m_ctrlStatic23;
	CStaticLocalize m_ctrlStatic25;
	CStaticLocalize m_ctrlStatic26;
	CStaticLocalize m_ctrlStatic27;
	CStaticLocalize m_ctrlStatic28;
	CStaticLocalize m_ctrlStatic29;
	CStaticLocalize m_ctrlStatic30;
	CStaticLocalize m_ctrlStatic35;
	CStaticLocalize m_ctrlStatic36;  // PASSAPORTE //Julio - BUG 3285 - Adequação de laudos
	CStaticLocalize m_ctrlStatic185; // RG         //Julio - BUG 3285 - Adequação de laudos
	CStaticLocalize m_ctrlStatic186; // CPF        //Julio - BUG 3285 - Adequação de laudos

	CStaticLocalize m_ctrlStaticNosologico;
	CStaticLocalize m_ctrlStaticBarcode;
	CStaticLocalize m_ctrlStaticDataRicovero;
	CStaticLocalize m_ctrlStaticRepartoDegenza;

	CStaticLocalize m_ctrlStaticSTP;
	CStaticLocalize m_ctrlStaticTEAM;

	CButtonLocalize m_ctrlButtonSex0;
	CButtonLocalize m_ctrlButtonSex1;
	CButtonLocalize m_ctrlButtonSex2;
	CButtonLocalize m_ctrlButtonSex3;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonSearch;

	CInviantiCombo m_ctrlComboReparto;
	long m_lProvenienza;

	// CMaskEdit m_ctrlData; // Sandro 25/03/2010 - RAS 20100046 //
	CExtDateEdit m_ctrlData;
	CExtEdit m_ctrlPaziente08; // Professione //
	CExtMedicoCuranteInviante m_ctrlPaziente11; // Medico curante //
	CComuneEdit m_ctrlComune;
	CComuneEdit m_ctrlComuneNascita;
	CExtEdit m_ctrlNazionalita;

	CExtDateEdit m_ctrlDataRicovero;

	// paziente cronico //
	CComboBox m_ctrlComboCronico;
	CEdit m_ctrlEditCronico;

	// paziente del direttore //
	CButton m_ctrlCheckDirettore;
	CComboBox m_ctrlComboDirettore;

	CStaticLocalize m_ctrlStaticDataDecesso;
	CButtonLocalize m_ctrlCheckDeceduto;
	CExtDateEdit m_ctrlDataDecesso;

	CComboBox m_ctrlComboSesso;
public:
	afx_msg void OnBnClickedCheckDeceduto();
};

#endif /* _PAZIENTIDLG_H_ */