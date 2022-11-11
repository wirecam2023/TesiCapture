#ifndef _QUERYDLG_H_
	#define _QUERYDLG_H_

// #include "DLL_Imaging/h/amremote.h" 

#include "EsamiSet.h"
#include "PatientListbox.h"
#include "PazientiSet.h"

class CCaricaReport;
class CExportCSV;
class CExportExcel;
class CExportHtml;
class CElemReportSet;
class CJoinEsamiSet;

enum
{
	SOLO_ESAMI_ONLYPATIENTS = -3,
	PAZIENTI_ESAMI_ONLYPATIENTS,
	SOLO_ESAMI,
	PAZIENTI_ESAMI,
	SOLO_PAZIENTI
};

struct itemlistapazienti
{
	long lID;
	CString sCognome;
	CString sNome;
	long lDataNascita;
};

class CQueryDlg : public CResizableDialog
{

public:

	CQueryDlg(CEsamiView* pEsamiView, BOOL bVerifyDuplicated, CString strTitle, BOOL bModale = FALSE, BOOL bSoloRicerca = FALSE, BOOL bMostraTastoUnificazione = TRUE);
	virtual ~CQueryDlg();

	enum { IDD = IDD_QUERY };

	void CreateModelessDialog(CWnd* pParent);
	void SelectListRow(long lRowNum);

	CDWordArray m_ArrayCode;
	BOOL m_bAddNew;
	BOOL m_bCercaPaziente;
	long m_lCurrentPri;
	long m_lCurrentSec;
	long m_lRelazione;
	long m_lTotale;
	CString m_strPazFilter;
	CString m_strEsameFrom;
	CString m_strEsameWhere;

	CEsamiSet* m_pEsamiSet;
	CJoinEsamiSet* m_pJoinEsamiSet;
	CPazientiSet* m_pPazientiSet;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnShowQueryWnd(WPARAM, LPARAM);
	afx_msg void OnAlbum();
	afx_msg void OnDestroy();
	afx_msg void OnExport();
	afx_msg void OnLvnItemChangedListEsami(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNew();
	afx_msg void OnNext();
	afx_msg void OnNMDblClkListEsami(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPrev();
	afx_msg void OnSelChangeLista();
	afx_msg void OnStampa();
	afx_msg void OnReport();
	afx_msg void OnBnClickedBtnUnificazioneanagrafiche();

private:

	void EsportaRigaRisultato(int i, short nRiga, int nModalita, CExportExcel* excel, CExportHtml* html, CExportCSV* csv, CCaricaReport* Report);
	void FiltraEsami();
	void FiltraPazienti();
	void FiltraSubEsami();
	void MostraDatiEsame(CString* pStrEdit);
	void MostraDatiPaziente(CString* pStrEdit);
	void MostraEsameSelezionato();
	CString ReturnField(CString strTipo, CString strEtichetta, CPazientiSet* pPazientiSet);
	CString ReturnLabel(CString strEtichetta);
	void RiempiListaEsami();
	void RiempiListaQuery();
	void RiempiListeDati();

	BOOL SelectOnlyPatient(CCaricaReport* Report);

	BOOL IsAfter(itemlistapazienti* pItemToInsert, itemlistapazienti* pItemOnList);
	BOOL IsBefore(itemlistapazienti* pItemToInsert, itemlistapazienti* pItemOnList);

	BOOL m_bVerifyDuplicated;
	int m_nCurExam;
	int m_nTotExam;
	CString m_StrAssociato;
	CString m_StrPrincipale;
	CString m_strTitolo;

	CEsamiSet m_EsamiSet;
	CElemReportSet* m_pReportElemSet;
	CEsamiView* m_pEsamiView;

	BOOL m_bModale;
	BOOL m_bSoloRicerca;

	CString m_strTitle;

	BOOL m_bMostraTastoUnificazione;

	//

	CPatientListBox m_ctrlLista;
	CBitmapButtonEx m_PrevButton;
	CBitmapButtonEx m_NextButton;
	CBitmapButtonEx m_btnExport;
	CBitmapButtonEx m_AlbumButton;
	CBitmapButtonEx m_PrintButton;
	CBitmapButtonEx m_ReportButton;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStaticStorico;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonNew;

	CEdit m_ctrlPrincipale;

	CListCtrlLocalize m_ctrlListEsami;
	CListBox m_ctrlListaStorico;

	CButtonLocalize m_ctrlBtnUnificazioneAnagrafiche;

public:
	afx_msg void OnLbnDblclkListStorico();
};

#endif /*_QUERYDLG_H_ */