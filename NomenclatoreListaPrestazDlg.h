#ifndef _NOMENCALTORELISTAPRESTAZDLG_H_
	#define _NOMENCALTORELISTAPRESTAZDLG_H_

#include "NomenclatoreRisDlg.h"

class CNomenclatoreListaPrestazDlg : public CNomenclatoreRisDlg  
{

public:

	CNomenclatoreListaPrestazDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CString &sFiltroData, CString &sDataIniz, CString &sDataFine, CString &sSedeEsame, long lMedico, int nProvenienza);

protected:

	afx_msg BOOL OnInitDialog();

private:

	UINT RiempiLista();
};

#endif /* _NOMENCALTORELISTAPRESTAZDLG_H_ */