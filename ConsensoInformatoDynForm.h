#ifndef _CONSENSOINFORMATODYNFORM_H_
	#define _CONSENSOINFORMATODYNFORM_H_

#include "EndoxDynForm.h"
#include "ExtEdit.h"
#include "MyRadio.h"

class CConsensoInformatoDynForm : public CEndoxDynForm
{

public:

	CConsensoInformatoDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CConsensoInformatoDynForm();

	enum { IDD = IDD_SUBFORM_CONSENSO };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:

	afx_msg void OnClickedBtnAcquisisci();
	afx_msg void OnClickedBtnStampa();
	afx_msg void OnClickedBtnStampaBat();
	afx_msg void OnClickedRadio();

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

	WPARAM m_wReadOnly;

	CStaticLocalize m_ctrlStaticConsenso, m_ctrlStatic1, m_ctrlStatic2, m_ctrlStaticNote;

	CMyRadio m_ctrlRadio1;
	CMyRadio m_ctrlRadio2;

	CExtEdit m_ctrlMotivo;
	CButtonLocalize m_ctrlButtonAcquisisci;
	CButtonLocalize m_ctrlButtonStampa;
	CButtonLocalize m_ctrlButtonStampaBat;
public:
	afx_msg void OnPaint();
};

#endif /* _CONSENSOINFORMATODYNFORM_H_ */