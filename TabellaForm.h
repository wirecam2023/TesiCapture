#pragma once

#include "FormulaOne.h"
#include "SubForm.h"

class CEsamiView;
class CTXTextControl23Ex;

#define _SPREADSHEET_FORMULA_SEPARATOR "@"
#define _SPREADSHEET_HEIGHT_NAME "HEIGHT"
#define _SPREADSHEET_WEIGHT_NAME "WEIGHT"

#define WM_ADD_TXTTEXT_TO_REPORT WM_USER + 0x6991

class CTabellaForm : public CEndoxDynForm
{

public:

	CTabellaForm(CWnd* pParentWnd, CEsamiView* pEsamiView, CTXTextControl23Ex* pTxTextControl);
	~CTabellaForm();

	enum { IDD = IDD_SUBFORM_TABELLA };

	static BOOL CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CTXTextControl23Ex* pTxTextControl, CTabellaForm** pForm);

	long GetContenuto();

	BOOL CampoObbligatorioValido();

	void SaveData();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual LRESULT OnResizeForm(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnSpreadsheetEndEditCell(BSTR* EditString, short* Cancel);
	void OnSpreadsheetKeyDown(short* KeyCode, short Shift);
	afx_msg void OnButtonImport();
	afx_msg void OnEnChangeAltezza();
	afx_msg void OnEnChangePeso();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()

	void EnableSpreadSheet(BOOL enable);
	void ResizeSpreadsheet();
	void InitSpreadsheet();

	void LoadData();

	void UpdateBSA(float fPeso, float fAltezza);
	void UpdateRiferimenti(float fPeso);

	CEdit m_ctrlEditPeso, m_ctrlEditAltezza;
	CFormulaOne m_ctrlSpreadsheet;

	BOOL m_bAutoUpdate;

	struct tagFORMULA
	{
		long lRow;
		TCHAR szFormula[4001];
	};

	//

	afx_msg void OnCbnSelchangeCmbFrazioneEiezione();

private:

	void RecolorFormulaCells();

	//

	CComboBox m_ctrlCmbFrazioneEiezione;

	CTXTextControl23Ex* m_pTxTextControl;

	CStaticLocalize m_ctrlStaticAnam11;
	CStaticLocalize m_ctrlStaticAnam12;

	BOOL m_bDebugBSA;
	long m_lFrassaoRow;
	CString m_sFrassaoFormula;

};
