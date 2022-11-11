#ifndef _MONITORAGGIOORIZDYNFORM_H_
	#define _MONITORAGGIOORIZDYNFORM_H_

#include "ExtInfermiere.h"
#include "InfermieriCombo.h"
#include "MonitoraggioBaseDynForm.h"

#include "DLL_Imaging\h\AMListCtrl.h"

class CMonitoraggioOrizDynForm : public CMonitoraggioBaseDynForm
{

public:

	CMonitoraggioOrizDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CMonitoraggioOrizDynForm();

	enum { IDD = IDD_SUBFORM_MONITORAGGIO_ORIZ };

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

	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);
	// afx_msg void OnBnClickedBtnRef();

	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);
	LRESULT OnMonitoraggioListEv(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CAMEditComboListCtrl m_ctrlList;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CInfermieriCombo m_ctrlInfermiere;
	CExtInfermiere m_ctrlInfermiereTxt;
	CButtonLocalize m_ctrlBtnAdd;
	CButtonLocalize m_ctrlBtnEdit;
	CButtonLocalize m_ctrlBtnDel;
	// CButtonLocalize m_ctrlBtnRef;

public:
	afx_msg void OnBnClickedBtnRefresh();
};

#endif /* _MONITORAGGIOORIZDYNFORM_H_ */