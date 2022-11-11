#ifndef _CARDIOPRIMADYNFORM_H_
	#define _CARDIOPRIMADYNFORM_H_

#include "DLL_Imaging\h\AMListCtrl.h"

#include "Common.h"
#include "EndoxDynForm.h"

class CEsamiView;

class CCardioPrimaDynForm : public CEndoxDynForm
{

public:

	CCardioPrimaDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CCardioPrimaDynForm();

	enum { IDD = IDD_SUBFORM_CARDIO_PRIMA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	short GetColNumber();
	short GetRowNumber();
	CString GetMassimaBpm();
	CString GetMassimaTitle();
	CString GetSubmassimaBpm();
	CString GetSubmassimaTitle();
	CString GetTableCellText(short shCol, short shRow);
	CString GetTitle();

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

private:

	BOOL CampoObbligatorioValido();
	long GetContenuto();

	void ListControlPrepara();
	void ListControlCaricaDatiEsame();
	void ListControlCaricaDefault();
	void ListControlDeleteAll();

	//

	CAMEditComboListCtrl m_ctrlList;

	CEdit m_ctrlEditMassima;
	CEdit m_ctrlEditSubmassima;

	CStaticLocalize m_ctrlStaticTitle;
	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;

	//

	long m_lIDProtocollo;

	long m_lNumColonne;
	STRUCT_COLONNE* m_pArrayStructColonne;

};

#endif /* _CARDIOPRIMADYNFORM_H_ */