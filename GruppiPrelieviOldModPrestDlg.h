#ifndef _GRUPPIPRELIEVIOLDMODPRESTDLG_H_
	#define _GRUPPIPRELIEVIOLDMODPRESTDLG_H_

#include "GruppiPrelieviOldItemSet.h"
#include "MstOrganoSet.h"
#include "OrganoDiagnosiEdit.h"

class CGruppiPrelieviOldModPrestDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiPrelieviOldModPrestDlg)

public:

	CGruppiPrelieviOldModPrestDlg(CWnd* pParent, long lIDGruppoOld, long lRecord);
	virtual ~CGruppiPrelieviOldModPrestDlg();

	enum { IDD = IDD_GRUPPIPRELIEVIOLD_MOD_PREST };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CComboBox m_ctrlTipo;
	COrganoDiagnosiEdit m_ctrlOrgano;
	COrganoDiagnosiEdit m_ctrlSede;
	CEdit m_ctrlProvetta;
	CComboBox m_ctrlProcedura;
	COrganoDiagnosiEdit m_ctrlDiagnosi;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;

	//

	CGruppiPrelieviOldItemSet m_setItem;

	long m_lIDGruppoOld;
	long m_lRecord;

};

#endif /* _GRUPPIPRELIEVIOLDMODPRESTDLG_H_ */