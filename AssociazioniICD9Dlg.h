#ifndef _ASSOCIAZIONIICD9DLG_H_
	#define _ASSOCIAZIONIICD9DLG_H_

#include "MyListBox.h"

class CEsamiView;
class CTipoEsameSet;

class CAssociazioniICD9Dlg : public CDialog
{

public:

	CAssociazioniICD9Dlg(CEsamiView* pEsamiView);
	virtual ~CAssociazioniICD9Dlg();

	void RiempiListaTipoEsame();

	enum { IDD = IDD_ASSOCIAZIONI_ICD9 };

	BOOL m_bVisibile;

	CMyListBox m_ctrlLista;
	CMyListBox m_ctrlListGruppiProcedure;
	CMyListBox m_ctrlListProcedure;
	CMyListBox m_ctrlListGruppiDiagnosi;
	CMyListBox m_ctrlListDiagnosi;

	CEsamiView* m_pEsamiView; 

	int m_lSavedPosition;
	BOOL m_bAddNew;
	BOOL m_bModify;

	BOOL m_bRicercaAttivata;
	BOOL m_bOrPressed;
	CString m_strRicerca;
	CString m_strRicercaView;
	int m_nItemPressed; 
	int m_nItemCount;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeLista();
	afx_msg void OnTipoEsameDelete();
	afx_msg void OnTipoEsameModify();
	afx_msg void OnTipoEsameNew();
	afx_msg void OnTipoEsameRefresh();
	afx_msg void OnTipoEsameUpdate();
	afx_msg void OnBtnOr();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnSelchangeGruppiDiagnosi();
	afx_msg void OnLbnSelchangeGruppiProcedure();

private:

	BOOL CanBeInserted(long lContatore);
	void RiempiListaGruppiProcedure();
	void RiempiListaProcedure();
	void RiempiListaGruppiDiagnosi();
	void RiempiListaDiagnosi();
	void SalvaGruppiProcedure(long lContatoreEsame);
	void SalvaProcedure(long lContatoreEsame);
	void SalvaGruppiDiagnosi(long lContatoreEsame);
	void SalvaDiagnosi(long lContatoreEsame);
	void SelezionaGruppiProcedure(long lContatoreEsame);
	void SelezionaProcedure(long lContatoreEsame);
	void SelezionaGruppiDiagnosi(long lContatoreEsame);
	void SelezionaDiagnosi(long lContatoreEsame);
	void SelezionaDiagnosiDaGruppo(long lIdGruppo);
	void SelectDiagnosi(long lIdDiagnosi);
	void SelezionaProceduraDaGruppo(long lIdGruppo);
	void SelectProcedura(long lIdProcedura);

	//

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;
	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonModify;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonUpdate;
	CButtonLocalize m_ctrlButtonRefresh;
	CButtonLocalize m_ctrlButtonCancel;

	//

	CString m_sDescrizione;
	CString m_sSigla;

};

#endif /* _ASSOCIAZIONIICD9DLG_H_ */