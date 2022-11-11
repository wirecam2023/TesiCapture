#ifndef _CRONICITAPAZIENTERECORDDLG_H_
	#define _CRONICITAPAZIENTERECORDDLG_H_

#include "DLL_Imaging\h\AMListCtrl.h"

#include "CronicitaPazienteDlg.h"

class CCronicitaPazienteRecordDlg : public CDialog
{

	DECLARE_DYNAMIC(CCronicitaPazienteRecordDlg)

public:

	CCronicitaPazienteRecordDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDMalattiaCronica, long lIDEsame);
	virtual ~CCronicitaPazienteRecordDlg();

	enum { IDD = IDD_CRONICITA_PAZIENTE_RECORD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnAnnulla();
	afx_msg void OnBnClickedBtnConferma();

private:

	void FillDatiCampoLibero(long lIDCampo, STRUCT_RIGA* pRiga);
	void FillDatiCampoScore(long lIDCampo, STRUCT_RIGA* pRiga);
	void FillDatiCampoFarmaco(long lIDCampo, STRUCT_RIGA* pRiga);
	void RiempiRecordset();

	//

	CEsamiView* m_pEsamiView;

	CEsamiSet m_setEsami;

	long m_lIDMalattiaCronica;
	long m_lIDEsame;

	long m_lNumeroRighe;
	STRUCT_RIGA* m_pRighe;

	//

	CAMEditComboListCtrl m_ctrlList;

	CButtonLocalize m_ctrlBtnAnnulla;
	CButtonLocalize m_ctrlBtnConferma;

};

#endif /* _CRONICITAPAZIENTERECORDDLG_H_ */