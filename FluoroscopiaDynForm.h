#ifndef _FLUOROSCOPIADYNFORM_H_
	#define _FLUOROSCOPIADYNFORM_H_

#include "EndoxDynForm.h"
#include "FreeExtEdit.h"
#include "ExtFarmaci.h"

class CFluoroscopiaDynForm : public CEndoxDynForm
{

public:

	CFluoroscopiaDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CFluoroscopiaDynForm();

	enum { IDD = IDD_SUBFORM_FLUOROSCOPIA };

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
	LRESULT OnEditFocusLost(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CFreeExtEdit m_ctrlTesto[3];
	//CFarmaciExtEdit m_ctrlFarmaci;
	//CExtEdit m_ctrlFarmaci;
	CStaticLocalize m_ctrlFluo, m_ctrlMin, m_ctrlSec, m_ctrlDose;

	long m_lMinuti1;
	long m_lMinuti2;
	long m_lSecondi1;
	long m_lSecondi2;
	float m_fDose1;
	float m_fDose2;
};

#endif /* _FLUOROSCOPIADYNFORM_H_ */