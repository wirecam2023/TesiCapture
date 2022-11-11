#ifndef _MIELOGRAMMADYNFORM_H_
	#define _MIELOGRAMMADYNFORM_H_

#include "EndoxDynForm.h"
#include "FormulaOne.h"

class CMielogrammaDynForm : public CEndoxDynForm
{

public:

	CMielogrammaDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CMielogrammaDynForm();

	enum { IDD = IDD_SUBFORM_MIELOGRAMMA };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

	CString GetTableCellNumberPercent(long lRow, long lCol);
	CString GetTableCellText(long lRow, long lCol);

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
	// LRESULT OnResizeForm(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

	void InitSpreadsheet();
	void OnSpreadsheetEndEditCell(BSTR* EditString, short* Cancel);
	void OnSpreadsheetKeyDown(short* KeyCode, short Shift);
	void ResizeSpreadsheet();

	LRESULT UpdateContagem(WPARAM wParam, LPARAM lParam);

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	//

	CFormulaOne m_ctrlSpreadsheet;

};

#endif /* _MIELOGRAMMADYNFORM_H_ */