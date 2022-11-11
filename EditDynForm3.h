#ifndef _EDITDYNFORM3_H_
	#define _EDITDYNFORM3_H_

#include "EndoxDynForm.h"
#include "ExtDateEdit.h"
#include "ExtMedico.h"
#include "MstIndicazioniEdit.h"
#include "ExtEdit.h"
#include "ExtTerapia.h"
#include "MyEdit.h"

class CEditDynForm3 : public CEndoxDynForm
{

public:

	CEditDynForm3(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEditDynForm3();

	enum { IDD = IDD_SUBFORM_EDIT3 };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	long m_lContenuto;

	static CEdit m_ctrlDiagnostiche;
	static CEdit m_ctrlTerapeutiche;
	static CEdit m_ctrlMstComplicanze1;
	static CEdit m_ctrlMstComplicanze2;
	static CEdit m_ctrlMstComplicanze3;

};

#endif /* _EDITDYNFORM3_H_ */