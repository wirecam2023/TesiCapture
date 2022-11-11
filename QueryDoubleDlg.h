#ifndef _QUERYDOUBLEDLG_H_
	#define _QUERYDOUBLEDLG_H_

#include "MonitoraggioListCtrl.h"

#define OP_ANNULLA			-1000 // non fa niente //
#define OP_INSERISCINUOVO	-1001 // paziente da inserire sia in anagrafica di Endox che in quella centralizzata //
#define OP_SOLOENDOX		-1002 // va al paziente esistente di endox //
#define OP_SOLOCENTRALE		-1003 // importa il paziente dall'anagrafica centralizzata //
#define OP_MERGE			-1004 // va al paziente esistente di Endox ma aggiorna i dati con quelli dell'anagrafica centralizzata //

struct PazienteCentrale
{
	CString sAssiden;
	CString sCognome;
	CString sNome;
	CString sDataNascita;
	CString sCittaNascita;
	CString sIstatNascita;
	CString sIndirizzo;
	CString sCitta;
	CString sIstat;
	CString sCap;
	CString sTelefono1;
	CString sTelefono2;
	CString sCellulare1;
	CString sCellulare2;
	CString sEmail;
	CString sCodFiscale;
	CString sSesso;
	CString sCittadinanza;
	CString sCodiceSanitario;
	CString sAsl;
};

class CQueryDoubleDlg : public CResizableDialog
{
	DECLARE_DYNAMIC(CQueryDoubleDlg)

public:

	CQueryDoubleDlg(CWnd* pParent, CString sCognome, CString sNome, CString sDataNascita, CString sSesso, CString sCodiceFiscale);
	virtual ~CQueryDoubleDlg();

	enum { IDD = IDD_QUERY_DOUBLE };

	long m_lOperationToDo;
	long m_lContatoreEndox;
	long m_lEsameSelezionato;
	PazienteCentrale m_pazienteCentraleSelezionato;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel() { }
	virtual BOOL OnInitDialog();
	virtual void OnOK() { }

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void InserisciPazienteNuovo();
	int RiempiLista1();
	int RiempiLista2();
	void RiempiLista1Dettaglio(long contatorePaziente);
	void RiempiLista2Dettaglio(long indice);

	CButtonLocalize m_ctrlSave;
	CButtonLocalize m_ctrlUndo;

	CMonitoraggioListCtrl m_ctrlList1;
	CMonitoraggioListCtrl m_ctrlListDett1;
	CListCtrlLocalize m_ctrlList2;
	CListCtrlLocalize m_ctrlListDett2;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

	CString m_sCognome;
	CString m_sNome;
	CString m_sDataNascita;
	CString m_sSesso;
	CString m_sCodiceFiscale;

	CList<PazienteCentrale> m_pazientiCentrale;

public:
	afx_msg void OnBnClickedBtnNuovo();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListDett1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListDett1(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif /* _QUERYDOUBLEDLG_H_ */