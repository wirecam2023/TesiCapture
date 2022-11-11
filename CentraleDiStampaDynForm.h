#ifndef _CENTRALEDISTAMPADYNFORM_H_
	#define _CENTRALEDISTAMPADYNFORM_H_

#include "DLL_Imaging\h\AmRemoteStruct.h"

#include "EndoxDynForm.h"
#include "MyEdit.h"
#include "TXTextControl23.h"

class CCentraleDiStampaDynForm : public CEndoxDynForm
{

public:

	CCentraleDiStampaDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CCentraleDiStampaDynForm();

	enum { IDD = IDD_SUBFORM_CENTRALEDISTAMPA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();
	void OnOK();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnConferma();
	afx_msg LRESULT OnCheckValue(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPrintingThreadEnded(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:

	BOOL CampoObbligatorioValido();
	long GetContenuto();

	static UINT PrintingThread(LPVOID pParam);
	BOOL RecuperaDatiUnita(CString sUnita, long lIDHeader, long lIDFooter1, long lIDFooter2, CString &sIDMarca);
	obterLaudoResponse* RecuperaDatiReferti(CString sIDMarca, CString sFicha, CString sUtente);
	void VaiConLaStampa(CString sFileDaStampare);

	//

	CButtonLocalize m_ctrlBtnConferma;

	CMyEdit m_ctrlEditFicha;

	CListCtrl m_ctrlList1;
	CListCtrl m_ctrlList2;

	CStaticLocalize m_ctrlStaticFicha;
	CStaticLocalize m_ctrlStaticPrinting1;
	CStatic m_ctrlStaticPrinting2;
	CStaticLocalize m_ctrlStaticTitle1;
	CStaticLocalize m_ctrlStaticTitle2;

	//

	BOOL m_bThreadAlreadyGoing;
	BOOL m_bUtilizzaCartaIntestata;

	long m_lFontHeightNormal;
	long m_lFontHeightSmall;
	long m_lFontHeightSmallSmall;

	CString m_sFontName;
	CString m_sPrintingFicha;
	CString m_sError;

};

#endif /* _CENTRALEDISTAMPADYNFORM_H_ */