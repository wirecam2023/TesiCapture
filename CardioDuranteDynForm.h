#ifndef _CARDIODURANTEDYNFORM_H_
	#define _CARDIODURANTEDYNFORM_H_

#include "DLL_Imaging\h\AMListCtrl.h"

#include "Common.h"
#include "EndoxDynForm.h"
#include "CardioDopoDynForm.h"

class CEsamiView;

class CCardioDuranteDynForm : public CEndoxDynForm
{

public:

	CCardioDuranteDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CCardioDuranteDynForm();

	enum { IDD = IDD_SUBFORM_CARDIO_DURANTE };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	short GetColNumber();
	short GetRowNumber();
	CString GetTableCellText(short shCol, short shRow);
	CString GetTitle();
	CString GetNomeProtocollo();

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

	LRESULT OnListSubitemChanged(WPARAM wParam, LPARAM lParam);

private:

	BOOL CampoObbligatorioValido();
	long GetContenuto();

	void ListControlRiempi();
	void ListControlCaricaDatiEsame();
	void ListControlCaricaDefault();
	void RiempiCombo();

	void CalcolaTempi();

	//

	CAMEditComboListCtrl m_ctrlList;
	
	CButtonLocalize m_ctrlBtnAdd;
	CButtonLocalize m_ctrlBtnDel;

	CComboBox m_ctrlCombo;

	CStaticLocalize m_ctrlStaticTitle;
	CStaticLocalize m_ctrlStatic00;

	//

	BOOL m_bReadOnly;

	long m_lIDProtocollo;
	CString m_sNomeProtocollo;

	long m_lNumColonne;
	STRUCT_COLONNE* m_pArrayStructColonne;

	int m_nColonnaTempo;
	int m_nColonnaSommaTempo;
	int m_nColonnaMETS;
	int m_nColonnaTempoOriginale;

	//

	CCardioDopoDynForm* m_ctrlCardioDopoForm;

};

#endif /* _CARDIODURANTEDYNFORM_H_ */