#ifndef _ALBUMESAMEEXPORTCDDLG_H_
	#define _ALBUMESAMEEXPORTCDDLG_H_

#include "ExportProgressDiscDlg.h"

class CAlbumEsameExportCdDlg : public CExportProgressDiscDlg
{

public:

	CAlbumEsameExportCdDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp, int iDiscType);
	~CAlbumEsameExportCdDlg();

	virtual BOOL ExportImmagini();
};

#endif /* _ALBUMESAMEEXPORTCDDLG_H_ */