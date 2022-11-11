#ifndef _VOLUMEDYNFORM_H_
	#define _VOLUMEDYNFORM_H_

#include "EndoxDynForm.h"

class CEsamiView;

class CVolumeDynForm : public CEndoxDynForm
{

public:

	CVolumeDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CVolumeDynForm();

	enum { IDD = IDD_SUBFORM_VOLUME };

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

	afx_msg void OnEnChangeMisuraABC();

	DECLARE_MESSAGE_MAP()

private:

	void UpdateVolume(float fMisuraA, float fMisuraB, float fMisuraC);

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CEdit m_ctrlEditMisuraA;
	CEdit m_ctrlEditMisuraB;
	CEdit m_ctrlEditMisuraC;
	CEdit m_ctrlEditVolume;

	CStaticLocalize m_ctrlStaticMisuraA;
	CStaticLocalize m_ctrlStaticMisuraB;
	CStaticLocalize m_ctrlStaticMisuraC;
	CStaticLocalize m_ctrlStaticVolume;

	float m_fMisuraA1;
	float m_fMisuraA2;
	float m_fMisuraB1;
	float m_fMisuraB2;
	float m_fMisuraC1;
	float m_fMisuraC2;
	float m_fVolume1;
	float m_fVolume2;

	BOOL m_bAutoUpdate;
};

#endif /* _VOLUMEDYNFORM_H_ */