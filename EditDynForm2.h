#ifndef _EDITDYNFORM2_H_
	#define _EDITDYNFORM2_H_

#include "EndoxDynForm.h"
#include "ExtDateEdit.h"
#include "ExtEdit.h"
#include "FreeExtEdit.h"
#include "ExtMedico.h"
#include "ExtStrumentiEdit.h"
#include "ExtTerapia.h"
#include "MstIndicazioniEdit.h"
#include "MyEdit.h"

class CEditDynForm2 : public CEndoxDynForm
{

public:

	CEditDynForm2(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto);
	~CEditDynForm2();

	enum { IDD = IDD_SUBFORM_EDIT2 };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco);

	void SetText(CString value);

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormFocusLost(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	long GetContenuto();
	BOOL CampoObbligatorioValido();
	BOOL ControlloNumerico();

	long m_lContenuto;

	BOOL m_bReadOnly;

	static CMstIndicazioniEdit m_ctrlIndicazioni;
	static CExtEdit m_ctrlComplicanze;
	static CExtEdit m_ctrlTerapia;
	static CExtEdit m_ctrlProvvedimenti;
	static CExtEdit m_ctrlEsito;
	static CEdit m_ctrlDifficolta;
	static CExtTerapia m_ctrlTerapiaConsigliata;
	static CExtStrumentiEdit m_ctrlStrumenti;
	static CExtEdit m_ctrlAccessori;
	static CEdit m_ctrlNote;
	static CEdit m_ctrlRiferimento;
	static CFreeExtEdit m_ctrlTesto000;
	static CFreeExtEdit m_ctrlTesto001;
	static CFreeExtEdit m_ctrlTesto002;
	static CFreeExtEdit m_ctrlTesto003;
	static CFreeExtEdit m_ctrlTesto004;
	static CFreeExtEdit m_ctrlTesto005;
	static CFreeExtEdit m_ctrlTesto006;
	static CFreeExtEdit m_ctrlTesto007;
	static CFreeExtEdit m_ctrlTesto008;
	static CFreeExtEdit m_ctrlTesto009;
	static CFreeExtEdit m_ctrlTesto010;
	static CFreeExtEdit m_ctrlTesto011;
	static CFreeExtEdit m_ctrlTesto012;
	static CFreeExtEdit m_ctrlTesto013;
	static CFreeExtEdit m_ctrlTesto014;
	static CFreeExtEdit m_ctrlTesto015;
	static CFreeExtEdit m_ctrlTesto016;
	static CFreeExtEdit m_ctrlTesto017;
	static CFreeExtEdit m_ctrlTesto018;
	static CFreeExtEdit m_ctrlTesto019;
	static CFreeExtEdit m_ctrlTesto020;
	static CFreeExtEdit m_ctrlTesto021;
	static CFreeExtEdit m_ctrlTesto022;
	static CFreeExtEdit m_ctrlTesto023;
	static CFreeExtEdit m_ctrlTesto024;
	static CFreeExtEdit m_ctrlTesto025;
	static CFreeExtEdit m_ctrlTesto026;
	static CFreeExtEdit m_ctrlTesto027;
	static CFreeExtEdit m_ctrlTesto028;
	static CFreeExtEdit m_ctrlTesto029;
	static CFreeExtEdit m_ctrlTesto030;
	static CFreeExtEdit m_ctrlTesto031;
	static CFreeExtEdit m_ctrlTesto032;
	static CFreeExtEdit m_ctrlTesto033;
	static CFreeExtEdit m_ctrlTesto034;
	static CFreeExtEdit m_ctrlTesto035;
	static CFreeExtEdit m_ctrlTesto036;
	static CFreeExtEdit m_ctrlTesto037;
	static CFreeExtEdit m_ctrlTesto038;
	static CFreeExtEdit m_ctrlTesto039;
	static CFreeExtEdit m_ctrlTesto040;
	static CFreeExtEdit m_ctrlTesto041;
	static CFreeExtEdit m_ctrlTesto042;
	static CFreeExtEdit m_ctrlTesto043;
	static CFreeExtEdit m_ctrlTesto044;
	static CFreeExtEdit m_ctrlTesto045;
	static CFreeExtEdit m_ctrlTesto046;
	static CFreeExtEdit m_ctrlTesto047;
	static CFreeExtEdit m_ctrlTesto048;
	static CFreeExtEdit m_ctrlTesto049;
	static CFreeExtEdit m_ctrlTesto050;
	static CFreeExtEdit m_ctrlTesto051;
	static CFreeExtEdit m_ctrlTesto052;
	static CFreeExtEdit m_ctrlTesto053;
	static CFreeExtEdit m_ctrlTesto054;
	static CFreeExtEdit m_ctrlTesto055;
	static CFreeExtEdit m_ctrlTesto056;
	static CFreeExtEdit m_ctrlTesto057;
	static CFreeExtEdit m_ctrlTesto058;
	static CFreeExtEdit m_ctrlTesto059;
	static CFreeExtEdit m_ctrlTesto060;
	static CFreeExtEdit m_ctrlTesto061;
	static CFreeExtEdit m_ctrlTesto062;
	static CFreeExtEdit m_ctrlTesto063;
	static CFreeExtEdit m_ctrlTesto064;
	static CFreeExtEdit m_ctrlTesto065;
	static CFreeExtEdit m_ctrlTesto066;
	static CFreeExtEdit m_ctrlTesto067;
	static CFreeExtEdit m_ctrlTesto068;
	static CFreeExtEdit m_ctrlTesto069;
	static CFreeExtEdit m_ctrlTesto070;
	static CFreeExtEdit m_ctrlTesto071;
	static CFreeExtEdit m_ctrlTesto072;
	static CFreeExtEdit m_ctrlTesto073;
	static CFreeExtEdit m_ctrlTesto074;
	static CFreeExtEdit m_ctrlTesto075;
	static CFreeExtEdit m_ctrlTesto076;
	static CFreeExtEdit m_ctrlTesto077;
	static CFreeExtEdit m_ctrlTesto078;
	static CFreeExtEdit m_ctrlTesto079;
	static CFreeExtEdit m_ctrlTesto080;
	static CFreeExtEdit m_ctrlTesto081;
	static CFreeExtEdit m_ctrlTesto082;
	static CFreeExtEdit m_ctrlTesto083;
	static CFreeExtEdit m_ctrlTesto084;
	static CFreeExtEdit m_ctrlTesto085;
	static CFreeExtEdit m_ctrlTesto086;
	static CFreeExtEdit m_ctrlTesto087;
	static CFreeExtEdit m_ctrlTesto088;
	static CFreeExtEdit m_ctrlTesto089;
	static CFreeExtEdit m_ctrlTesto090;
	static CFreeExtEdit m_ctrlTesto091;
	static CFreeExtEdit m_ctrlTesto092;
	static CFreeExtEdit m_ctrlTesto093;
	static CFreeExtEdit m_ctrlTesto094;
	static CFreeExtEdit m_ctrlTesto095;
	static CFreeExtEdit m_ctrlTesto096;
	static CFreeExtEdit m_ctrlTesto097;
	static CFreeExtEdit m_ctrlTesto098;
	static CFreeExtEdit m_ctrlTesto099;

	static CEdit m_ctrlIntegrazioni;

	LRESULT OnExtEditCmbChanged(WPARAM wParam, LPARAM lParam);
	void ManageEditCmbChanged(CString sTipoCampoCondizionato, long lIndexCampoCondizionato, long lIDRisultato, CString sRisultatoTxt);

};

#endif /* _EDITDYNFORM2_H_ */