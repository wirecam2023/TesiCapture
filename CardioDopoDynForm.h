#ifndef _CARDIODOPODYNFORM_H_
	#define _CARDIODOPODYNFORM_H_

#include "DLL_Imaging\h\AMListCtrl.h"

#include "Common.h"
#include "EndoxDynForm.h"

class CEsamiView;

class CCardioDopoDynForm : public CEndoxDynForm
{

public:

	CCardioDopoDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CCardioDopoDynForm();

	enum { IDD = IDD_SUBFORM_CARDIO_DOPO };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	short GetColNumber();
	short GetRowNumber();
	CString GetTableCellText(short shCol, short shRow);
	CString GetTitle();
	void SetTitle(CString sTitle);

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
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	BOOL CampoObbligatorioValido();
	long GetContenuto();

	void ListControlPrepara();
	void ListControlCaricaDatiEsame();
	void ListControlCaricaDefault();
	void ListControlDeleteAll();

	//

	CAMEditComboListCtrl m_ctrlList;

	CStaticLocalize m_ctrlStaticTitle;
	CButtonLocalize m_ctrlBtnDel;

	//
	BOOL m_bReadOnly;

	long m_lIDProtocollo;

	long m_lNumColonne;
	STRUCT_COLONNE* m_pArrayStructColonne;

};

#endif /* _CARDIODOPODYNFORM_H_ */