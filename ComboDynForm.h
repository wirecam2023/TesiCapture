#ifndef _COMBODYNFORM1_H_
	#define _COMBODYNFORM1_H_

#include "ComboAltreAnomalieSet.h"
#include "ComboCauseNonCompletamentoSet.h"
#include "ComboConclusioniColonSet.h"
#include "ComboConclusioniScreeningSet.h"
#include "ComboComplicanzeSet.h"
#include "ComboComplicanzeSet.h"
#include "ComboDiagnosiFinaleSet.h"
#include "ComboPuliziaSet.h"
#include "ComboTolleranzaSet.h"
#include "ComboTransCombo.h"
#include "EndoxDynForm.h"
#include "ExtComboTrans.h"
#include "ExtInfermiere.h"
#include "ExtInviante.h"
#include "ExtMedico.h"
#include "ExtTipoEsame.h"
#include "InfermieriCombo.h"
#include "InviantiCombo.h"
#include "MediciCombo.h"
#include "TipoEsameCombo.h"

class CComboDynForm1 : public CEndoxDynForm
{

public:

	CComboDynForm1(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CComboDynForm1();

	enum { IDD = IDD_SUBFORM_COMBO };  

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

protected:

	afx_msg void OnCbnSetfocusCombo();

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

	long m_lContenuto;

	static CTipoEsameCombo m_ctrlTipoEsame;
	static CExtTipoEsame m_ctrlTipoEsameTxt;
	static CMediciCombo m_ctrlMedico;
	static CExtMedico m_ctrlMedicoTxt;
	static CMediciCombo m_ctrlAssistente;
	static CExtMedico m_ctrlAssistenteTxt;
	static CInfermieriCombo m_ctrlInfermiere1;
	static CExtInfermiere m_ctrlInfermiere1Txt;
	static CInfermieriCombo m_ctrlInfermiere2;
	static CExtInfermiere m_ctrlInfermiere2Txt;
	static CInviantiCombo m_ctrlInviante;
	static CExtInviante m_ctrlInvianteTxt;
	static CComboTransCombo m_ctrlComplicanzeImmediate;
	static CExtComboTrans	m_ctrlComplicanzeImmediateTxt;
	static CComboTransCombo m_ctrlComplicanzeTardive;
	static CExtComboTrans	m_ctrlComplicanzeTardiveTxt;
	static CComboTransCombo m_ctrlPulizia;
	static CExtComboTrans m_ctrlPuliziaTxt;
	static CComboTransCombo m_ctrlCauseNonCompletamento;
	static CExtComboTrans m_ctrlCauseNonCompletamentoTxt;
	static CComboTransCombo m_ctrlTolleranza;
	static CExtComboTrans m_ctrlTolleranzaTxt;
	static CComboTransCombo m_ctrlConclusioniScreening;
	static CExtComboTrans m_ctrlConclusioniScreeningTxt;
	static CComboTransCombo m_ctrlConclusioniColon;
	static CExtComboTrans m_ctrlConclusioniColonTxt;
	static CComboTransCombo m_ctrlDiagnosiFinale;
	static CExtComboTrans m_ctrlDiagnosiFinaleTxt;
	static CComboTransCombo m_ctrlAltreAnomalie;
	static CExtComboTrans m_ctrlAltreAnomalieTxt;
	static CComboBox m_ctrlEsameUrgente;

	CComboAltreAnomalieSet m_setComboAltreAnomalie;
	CComboCauseNonCompletamentoSet m_setComboCauseNonCompletamento;
	CComboConclusioniColonSet m_setComboConclusioniColon;
	CComboConclusioniScreeningSet m_setComboConclusioniScreening;
	CComboComplicanzeSet m_setComboComplicanzeImmediate;
	CComboComplicanzeSet m_setComboComplicanzeTardive;
	CComboDiagnosiFinaleSet m_setComboDiagnosiFinale;
	CComboPuliziaSet m_setComboPulizia;
	CComboTolleranzaSet m_setComboTolleranza;

};

#endif /* _COMBODYNFORM1_H_ */