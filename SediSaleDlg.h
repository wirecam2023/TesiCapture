#ifndef _SEDISALEDLG_H_
	#define _SEDISALEDLG_H_

#include "ExtListBox.h"

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

class CSediSaleDlg : public CDialog
{

public:

	CSediSaleDlg(CWnd* pParent);
	virtual ~CSediSaleDlg();

	enum { IDD = IDD_SEDISALE };	

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
	
	LRESULT OnSediChanged(WPARAM wParam, LPARAM lParam);
	LRESULT OnSaleChanged(WPARAM wParam, LPARAM lParam);
	LRESULT OnAgendeChanged(WPARAM wParam, LPARAM lParam);

private:

	void RiempiListaSedi();
	void RiempiListaSale();
	void RiempiListaAgende();

	long m_lIdSedeSel;
	long m_lIdSalaSel;
	long m_lIdAgendaSel;

	//
	
	CButtonLocalize m_ctrlButtonEsci;

	CButtonLocalize m_ctrlBtnSedeNuovo, m_ctrlBtnSedeCanc;
	CButtonLocalize m_ctrlBtnSalaNuovo, m_ctrlBtnSalaCanc;
	CButtonLocalize m_ctrlBtnAgendaNuovo, m_ctrlBtnAgendaCanc;

	CAMEditComboListCtrl m_ctrlListaSedi;
	CAMEditComboListCtrl m_ctrlListaSale;
	CAMEditComboListCtrl m_ctrlListaAgende;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;			
	CStaticLocalize m_ctrlStatic3;

public:
	afx_msg void OnLvnItemchangedListaSedi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListaSale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListaAgende(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSedeNuovo();
	afx_msg void OnBnClickedSedeCanc();
	afx_msg void OnBnClickedSalaNuovo();
	afx_msg void OnBnClickedSalaCanc();
	afx_msg void OnBnClickedAgendaNuovo();
	afx_msg void OnBnClickedAgendaCanc();
};

#endif /* _SEDISALEDLG_H_ */