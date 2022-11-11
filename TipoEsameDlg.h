#ifndef _TIPOESAMEDLG_H_
	#define _TIPOESAMEDLG_H_

#include "MyListBox.h"

class CEsamiView;

class CTipoEsameDlg : public CDialog
{

public:

	CTipoEsameDlg(CEsamiView* pEsamiView);
	virtual ~CTipoEsameDlg();

	enum { IDD = IDD_TIPOESAME };

	CString m_strRicerca;
	CString m_strRicercaView;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	afx_msg void OnSelchangeLista();
	afx_msg void OnTipoEsameDelete();
	afx_msg void OnTipoEsameModify();
	afx_msg void OnTipoEsameNew();
	afx_msg void OnTipoEsameRefresh();
	afx_msg void OnTipoEsameUpdate();
	afx_msg void OnBtnResetColor();
	afx_msg void OnBtnOr();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()

private:

	BOOL CanBeInserted(long lContatore);
	void RiempiListaOrgani();
	void RiempiListaGruppi();
	void RiempiListaPrestazioni();
	void RiempiListaTipoEsame();
	
	void SalvaOrgani(long lContatoreEsame);
	void SalvaGruppi(long lContatoreEsame);
	void SalvaPrestazioni(long lContatoreEsame);

	void SelezionaComboCronicita(long lIDCronicita);
	void SelezionaOrgani(long lContatoreEsame);
	void SelezionaGruppi(long lContatoreEsame);
	void SelezionaPrestazioni(long lContatoreEsame);

	void RiempiComboCronicita();

	//

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonModify;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonUpdate;
	CButtonLocalize m_ctrlButtonRefresh;
	CButtonLocalize m_ctrlButtonCancel;

	CComboBox m_ctrlComboCronicita;

	CMyListBox m_ctrlLista;
	CMyListBox m_ctrlListOrgani;
	CMyListBox m_ctrlListGruppi;
	CMyListBox m_ctrlListPrestazioni;

	CStaticLocalize m_ctrlStaticTipi;
	CStaticLocalize m_ctrlStaticOrgani;
	CStaticLocalize m_ctrlStaticGruppi;
	CStaticLocalize m_ctrlStaticPrestazioni;
	CStaticLocalize m_ctrlStaticEsame;
	CStaticLocalize m_ctrlStaticSigla;
	CStaticLocalize m_ctrlStaticPrivato;
	CStaticLocalize m_ctrlStaticScreening;
	CStaticLocalize m_ctrlStaticErogaSoloPP;
	CStaticLocalize m_ctrlStaticSfondo;
	CStaticLocalize m_ctrlStaticMonitor;
	CStaticLocalize m_ctrlStaticCronicita;

	//

	CString m_sDescrizione;
	CString m_sSigla;
	int m_iPrivato;
	int m_iEsameScreening;
	int m_iErogaSoloPP;

	int m_lSavedPosition;
	BOOL m_bAddNew;
	BOOL m_bModify;

	BOOL m_bRicercaAttivata;
	BOOL m_bOrPressed;
	int m_nItemPressed; 
	int m_nItemCount;

	CEsamiView* m_pEsamiView; 

	COLORREF m_clColor;
	COLORREF m_clColorM1;
	COLORREF m_clColorM2;

	CBrush m_brushSfondo;

};

#endif /* _TIPOESAMEDLG_H_ */