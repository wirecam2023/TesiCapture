#ifndef _NOMENCLATORELISTAESAMIREPARTODLG_H_
	#define _NOMENCLATORELISTAESAMIREPARTODLG_H_

#include "NomenclatoreRisDlg.h"

class CNomenclatoreListaEsamiRepartoDlg : public CNomenclatoreRisDlg  
{

public:

	CNomenclatoreListaEsamiRepartoDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CString &sFiltroData, CString &sDataIniz, CString &sDataFine, CString &sSedeEsame, long lMedico, int nProvenienza);

protected:

	afx_msg BOOL OnInitDialog();

private:

	BOOL RiempiLista();
};

#endif /* _NOMENCLATORELISTAESAMIREPARTODLG_H_ */