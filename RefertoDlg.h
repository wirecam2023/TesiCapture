#ifndef _REFERTODLG_H_
#define _REFERTODLG_H_

#include "EndoxResizableDlg.h"
#include "FrasiTreeListBox.h"
#include "FrasiExSet.h"
#include "SpellCheckerDlg.h"
#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "VistaRefertiPazienteSet.h"
#include "EditDynFormToolbar.h"
#include "ChecklistForm.h"
#include "DLL_Imaging\h\AmDocManager.h"
#include "DocManager.h"
#include "Common.h"
#include "DLL_Imaging\h\AMEditComboListCtrl.h"

#define _RTFLINESEPARATOR _T("{\\rtf1 \\pard \\brdrb \\brdrs\\brdrw10\\brsp20 {\\fs4\\~}\\par \\pard }")

class CTabellaForm;
class CEditDynForm2;
class CEsamiSet;

class CRefertoExDlg : public CEndoxResizableDlg
{

public:

	CRefertoExDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CRefertoExDlg();

	enum { IDD = IDD_REFERTO };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

	afx_msg void OnBnClickedBtnInsertTable();
	afx_msg void OnBnClickedBtnMakeUpper();
	afx_msg void OnBnClickedBtnMakeNormal();
	afx_msg void OnBnClickedBtnMakeLower();
	afx_msg void OnBnClickedBtnRtfFont();//Julio - BUG 4392 Edicao de texto
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBtnCopyPrevRef();
	afx_msg void OnBtnSpeak();
	afx_msg void OnBtnSforzo();
	afx_msg void OnBtnPreview();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkListaFrasi();
	afx_msg void OnInsertFrasi();
	afx_msg void OnNMDblclkListFrasiRtf(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeFamiglia(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeListaFrasi();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeEditRtfCodiceFrase();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();

	LRESULT OnAddRtfTextToReport(WPARAM wParam, LPARAM lParam);
	LRESULT OnAddTxtTextToReport(WPARAM wParam, LPARAM lParam);

	void OnTextControlChange();
	void OnTextControlMouseDown(short Button, short Shift, long X, long Y);

	void RiempiListaPdf();
	void RiempiListaMeasurements();

	LRESULT OnKeyboardPress(WPARAM wParam, LPARAM lParam);	//Julio BUG 3457 - Texter
	void SearchAndReplaceTexterPhrase(CString sFrase);		// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	void ApplyTexterPhrase(long p_lIDFrase);				// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	void cleanEditToStart();

private:

	CTabCtrl m_ctrlFamiglia;
	CTXButtonBar23Ex m_ctrlButtonBar;
	CTXTextControl23Ex m_ctrlText;
	CFrasiTreeListBox m_ctrlTreeListFrasi;
	CString m_strFrase;

	//

	CButtonLocalize m_ctrlButtonCopyReport;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonFrasi;
	CButtonLocalize m_ctrlButtonSpeak;
	CButtonLocalize m_ctrlButtonSforzo;
	CButtonLocalize m_ctrlButtonPreview;

	CEdit m_ctrlEditRtfCodice;
	CEdit m_ctrlEditRtfFrase;

	CEditDynFormToolbar m_ctrlToolbar;

	CListCtrl m_ctrlListFrasiRTF;

	//

	CSpellCheckerDlg* GetWSpell(); // Sandro 07/05/2012 //
	void DestroyWSpell(); // Sandro 07/05/2012 //

	void  DistruggiListaFrasi();
	void  PreparaListaFrasi();
	short RicercaFigli(long lCodice);
	void  RiempiListaImmagini();
	void  SetReferto(CString strRTF);

	long			m_lFamiglia;
	long			m_nSelLength;
	long			m_nSelStart;
	long			m_nScrollx;
	long			m_nScrolly;

	CEsamiView*		m_pEsamiView;
	CEsamiSet*		m_pEsamiSet;
	CMyDocManager*  m_pDocManager; //Julio 14/08/2018

	CString			m_sTipoEsame;

	CFrasiExSet		m_FrasiSet;

	CListCtrl m_ctrlListImage;
	CListCtrl m_ctrlListPdf; //Julio 13/08/2018
	BOOL m_bHasPdfs; //Julio 01/02/2019	

	CAMEditComboListCtrl m_ctrlListMeasurements; //Julio 01/02/2019		
	CButtonLocalize m_ctrlBtnSaveMeasurements;//Julio - correcao lista biometria

	BOOL m_bHasMeasurements; //Julio 01/02/2019
	CImageList m_listImage;
	CImgListOrgani m_ImgListOrgani;

	CStatic m_ctrlStaticChecklistForm;
	CStatic m_ctrlStaticTabellaForm;

	CChecklistForm* m_pChecklistForm;
	CTabellaForm* m_pTabellaForm;

	static CSpellCheckerDlg m_WSpellChecker; // Sandro 07/05/2012 //

	CBrush m_brushSolidWhite;

	// 4 //

	void CaricaTestoAltroReferto();
	void CaricaTestoReferences(); // Julio 06/02/2019
	BOOL CaricaTestoAnamnesi(BOOL bLogSteps = FALSE);			// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
	void AddRTFAnamnese(CString sRTF);		// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
	void AddTXTAnamnese(CString sTXT);
	BOOL simpleCheckValidRTF(CString p_str);// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)

	CVistaRefertiPazienteSet m_setVistaRefertiPaziente;
	long m_lNumRefertiAct;
	long m_lNumRefertiTot;

	CTXTextControl23Ex m_ctrlTextAltriReferti;
	CTXTextControl23Ex m_ctrlTextReferences; //Julio 06/02/2018
	CTXTextControl23Ex m_ctrlTextTabAnamnesi;// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnesi)

	CButton m_ctrlBtnPrev;
	CButton m_ctrlBtnNext;
	CStaticLocalize m_ctrlStatic00;
	CStatic m_ctrlStatic01;
	CStatic m_ctrlStatic02;
	CButton m_ctrlBtnCopy;
	CButton m_ctrlBtnGetLaudoAnterior;
	CButton m_ctrlBtnConsultaResultado;
	CEdit m_ctrlEditInfoLaudoAnterior;

	CString m_sFichaLaudoAnterior;
	CString m_sItemLaudoAnterior;
	CString m_sDataLaudoAnterior;

	CButton m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade;
	BOOL m_bCheckBoxChecked;

	static UINT GetLaudoRtfAnterior(LPVOID pParam);
	//

	CButtonLocalize m_ctrlBtnPrevPdfPage;
	CButtonLocalize m_ctrlBtnNextPdfPage;
	CButtonLocalize m_ctrlBtnZoomIn;
	CButtonLocalize m_ctrlBtnZoomOut;

	// Sandro 13/04/2017 //

	static DWORD WINAPI ThreadPdfPageCount(LPVOID lpParam);

	LRESULT OnThreadPdfCountPagesUpdate(WPARAM wParam, LPARAM lParam);
	// LRESULT OnThreadPdfCountPagesEnd(WPARAM wParam, LPARAM lParam);

	CString m_sReportDefault;

	BOOL m_bIsTextChanged;
	CString m_sRTFSelText;

	HANDLE m_hPdfPageCountThread;
	HANDLE m_hEventExitPdfPageCountThread;

	UINT m_uiPreview;

	BYTE* m_pPdfBuffer;

	BOOL m_bImClosing;

	CString* m_sArrayPdf;

	BOOL m_bProcessOnEnChange;	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	BOOL m_bMeasurementUpdated;
	BOOL m_bSpermChartMeasurementUpdated; //Gabriel BUG 5533
	BOOL m_bSpermMeasurementVitalityAllowEdit; //Gabriel BUG 5533
	void CheckVitalityMeasurement(CString sNumericValue); //Gabriel BUG 5533
	BOOL CheckVitalityClosure(); //Gabriel BUG 5533
	CString m_sConcentracao; //Gabriel BUG 5533
	CString m_sMotilidadeProgressiva; //Gabriel BUG 5533
	CString m_sMorfologia; //Gabriel BUG 5533
	BOOL IsSpermExam(); //Gabriel BUG 5533

	CToolTipCtrl* m_ToolTipLaudoAnterior;

	//Gabriel - BUG 5533 V2
	struct tagFIELDRULE
	{
		long lID;
		long lIDCondition;
		long lMeasurementCondition;
		long lIDRule;
		long lMeasurementRule;
		TCHAR szValueCondition1[256];
		TCHAR szValueCondition2[256];
	};

	struct tagFIELDCALC
	{
		long lID;
		long lIDCalc;
		long lMeasurement1;
		long lMeasurement2;
		long lMeasurement3;
		long lMeasurement4;
		float fValue1;
	};

	CList<tagFIELDRULE> m_listRules;
	CList<tagFIELDCALC> m_listCalc;
	CList<long> m_listRulesId;
	CList<long> m_listCalcId;

	void CalculateMeasurements(long lItem, float fMeasurement2, float fMeasurement3, float fMeasurement4, float fValue1, long lIDCalc, long lMeasurement);
	void Recalculate();
	BOOL CanEdit(long lIDMeasurement);
	BOOL CanClose();
	CString FormatNumber(long lMeasurement, CString sValue, float fValue);

public:
	afx_msg void OnBnClickedBtnPrev2();
	afx_msg void OnBnClickedBtnNext2();
	afx_msg void OnBnClickedBtnZoomOut();
	afx_msg void OnBnClickedBtnZoomIn();
	afx_msg void OnBnClickedBtnGetLaudoAnterior();
	afx_msg void OnBnClickedBtnCopy();
	afx_msg void OnBnClickedBtnConsultaResultado();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnNMDblclkListPdf(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListMeasurements(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnMeasurentsRefresh();
	afx_msg void OnBnClickedBtnMeasurentsAdd();
	afx_msg void OnBnClickedBtnMeasurentsRemove();
	afx_msg void OnEnSetfocusEditRtfCodice();	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	afx_msg void OnEnSetfocusEditRtfFrase();	// Marvel Carvalho - Bug 3457 (FIX) TEXTER	
	afx_msg void SaveEditedMeasurement(); //Julio - correcao lista biometria
	afx_msg void OnItemChangedList(NMHDR* pNMHDR, LRESULT* pResult); //Gabriel - BUG 5533 V2
};

#endif /* _REFERTODLG_H_ */