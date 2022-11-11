#ifndef _NOMENCLATORELISTAPRESTAZREPARTODLG_H_
	#define _NOMENCLATORELISTAPRESTAZREPARTODLG_H_

#include "NomenclatoreRisDlg.h"

class CNomenclatoreListaPrestazRepartoDlg : public CNomenclatoreRisDlg  
{

public:

	CNomenclatoreListaPrestazRepartoDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CString &sFiltroData, CString &sDataIniz, CString &sDataFine, CString &sSedeEsame, long lMedico, int nProvenienza);

protected:

	afx_msg BOOL OnInitDialog();

private:

	BOOL RiempiLista();
};

#endif /* _NOMENCLATORELISTAPRESTAZREPARTODLG_H_ */