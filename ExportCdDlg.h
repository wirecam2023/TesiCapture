#ifndef _EXPORTCDDLG_H_
	#define _EXPORTCDDLG_H_

#include "ExportProgressDiscDlg.h"

class CExportDlg;

class CExportCdDlg : public CExportProgressDiscDlg
{

public:

	CExportCdDlg(CWnd* pParent, CEsamiView* pEsamiView, CExportDlg* pExportDlg, int iNumExp, int iDiscType);
	~CExportCdDlg();

	virtual BOOL ExportImmagini();

private:

	CExportDlg* m_pExportDlg;

};

#endif /* _EXPORTCDDLG_H_ */