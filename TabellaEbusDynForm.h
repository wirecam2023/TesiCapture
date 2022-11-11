#ifndef _TABELLAEBUSFORM_H_
	#define _TABELLAEBUSFORM_H_

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

#include "EbusSet.h"
#include "EndoxDynForm.h"

class CTabellaEbusDynForm : public CEndoxDynForm
{

public:

	CTabellaEbusDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CTabellaEbusDynForm();

	enum { IDD = IDD_SUBFORM_TABELLAEBUS };

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

	void AssociaRecordset();
	void RiempiLista();

	//

	CEbusSet m_setEBUS;

	CString* m_pRecordFields[8][11];

	//

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	BOOL m_bReadOnly;

	CStaticLocalize m_ctrlStaticTitolo;
	CAMEditComboListCtrl m_ctrlList;

};

#endif /* _TABELLAEBUSFORM_H_ */