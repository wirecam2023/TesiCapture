#ifndef _FARMACIPAZIENTICRONICIFORM_H_
	#define _FARMACIPAZIENTICRONICIFORM_H_

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

#include "EndoxDynForm.h"

class CFarmaciPazientiCroniciDynForm : public CEndoxDynForm
{

public:

	CFarmaciPazientiCroniciDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CFarmaciPazientiCroniciDynForm();

	enum { IDD = IDD_SUBFORM_FARMACIPAZIENTICRONICI };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();
	void OnSize(UINT nType, int cx, int cy);

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormClone(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	BOOL m_bReadOnly;
	CStringIDList m_slTerapia;

	CStaticLocalize m_ctrlStaticTitolo;
	CAMEditComboListCtrl m_ctrlListFarmaci;

};

#endif /* _FARMACIPAZIENTICRONICIFORM_H_ */