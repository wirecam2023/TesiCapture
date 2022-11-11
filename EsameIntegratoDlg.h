#ifndef _ESAMEINTEGRATODLG_H_
	#define _ESAMEINTEGRATODLG_H_

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

class CEsameIntegratoDlg : public CDialog
{

	DECLARE_DYNAMIC(CEsameIntegratoDlg)

public:

	CEsameIntegratoDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CEsameIntegratoDlg();

	enum { IDD = IDD_ESAMEINTEGRATO };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();

	//

	CAMEditComboListCtrl m_ctrlList;

	//

	CEsamiView* m_pEsamiView;

};

#endif