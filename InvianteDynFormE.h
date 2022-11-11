#ifndef _INVIANTEDYNFORM_E_H_
	#define _INVIANTEDYNFORM_E_H_

#include "EndoxDynForm.h"

#include "ExtMedicoCuranteInviante.h"

class CInvianteDynFormE : public CEndoxDynForm
{

public:

	CInvianteDynFormE(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CInvianteDynFormE();

	enum { IDD = IDD_SUBFORM_INVIANTE_E };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

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

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CExtMedicoCuranteInviante m_ctrlEditMedicoCurante;

};

#endif /* _INVIANTEDYNFORM_E_H_ */