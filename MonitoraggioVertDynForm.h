#ifndef _MONITORAGGIOVERTDYNFORM_H_
	#define _MONITORAGGIOVERTDYNFORM_H_

#include "DLL_Imaging\h\AMListCtrl.h"

#include "ExtInfermiere.h"
#include "InfermieriCombo.h"
#include "MonitoraggioBaseDynForm.h"
#include "MonitoraggioListCtrl.h"

class CMonitoraggioVertDynForm : public CMonitoraggioBaseDynForm
{

public:

	CMonitoraggioVertDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CMonitoraggioVertDynForm();

	enum { IDD = IDD_SUBFORM_MONITORAGGIO_VERT };

	void AggiungiRiga();
	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	int GetListItemCount();
	CString GetListItemText(int nItem, int nSubItem);
	CString GetFarmaciList(int nMonitoraggio);
	CString GetTotaleFarmaciList();

	long GetListNumCol();
	long GetListNumRig();
	void Reload();

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();
	virtual void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnDel();
	// afx_msg void OnBnClickedBtnRef();
	// afx_msg void OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);

	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	LRESULT OnMonitoraggioListEv(WPARAM wParam, LPARAM lParam);
	LRESULT OnMonitoraggio_VitalSign_ListEv(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	int RicercaFarmaco(int lID);
	void RiempiLista();
	void RiempiListaVitalSign();	

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CMonitoraggioListCtrl m_ctrlList;
	CAMEditComboListCtrl m_ctrlListVitalSign;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CInfermieriCombo m_ctrlInfermiere;
	CExtInfermiere m_ctrlInfermiereTxt;
	CButtonLocalize m_ctrlBtnAdd;
	CButtonLocalize m_ctrlBtnEdit;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnClose;
	// CButtonLocalize m_ctrlBtnRef;

	CStringIDList m_listaFarmaci;
	CStringIDList m_listaDosaggi;
	CList<int> m_idMonitoraggioList;
	CList<int> m_idMisurazioniVitalSignHeaderList;

public:
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnCopia();
};

#endif /* _MONITORAGGIOVERTDYNFORM_H_ */