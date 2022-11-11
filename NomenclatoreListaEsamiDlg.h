#ifndef _NOMENCALTORELISTAESAMIDLG_H_
	#define _NOMENCALTORELISTAESAMIDLG_H_

#include "NomenclatoreRisDlg.h"

class CNomenclatoreListaEsamiDlg : public CNomenclatoreRisDlg  
{

public:

	CNomenclatoreListaEsamiDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CString &sFiltroData, CString &sDataIniz, CString &sDataFine, CString &sSedeEsame, long lMedico, int nProvenienza);

protected:

	afx_msg BOOL OnInitDialog();

private:

	UINT RiempiLista();
};

#endif /* _NOMENCALTORELISTAPRESTDLG_H_ */