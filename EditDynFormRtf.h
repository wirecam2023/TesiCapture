#ifndef _EDITDYNFORMRTF_H_
	#define _EDITDYNFORMRTF_H_

#include "EndoxDynForm.h"
#include "TXTextControl23.h"

class CEditDynFormRtf : public CEndoxDynForm
{

public:

	CEditDynFormRtf(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEditDynFormRtf();

	enum { IDD = IDD_SUBFORM_EDITRTF };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:

	CTXTextControl23Ex m_ctrlTextControl;

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	long m_lContenuto;

};

#endif /* _EDITDYNFORMRTF_H_ */