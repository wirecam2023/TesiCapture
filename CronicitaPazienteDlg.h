#ifndef _CRONICITAPAZIENTEDLG_H_
	#define _CRONICITAPAZIENTEDLG_H_

#include "PazienteCronicoDxListCtrl.h"
#include "PazienteCronicoSnListCtrl.h"

enum FieldType
{
	FT_BOH,
	FT_NUMERICO,
	FT_TESTOLIBERO,
	FT_LISTAVELOCE,
	FT_CUSTOM_DATAORA,
	FT_CUSTOM_SOLODATA,
	FT_CUSTOM_SOLOORA,
	FT_SCORE,
	FT_FARMACO
};

enum FarmacoSomministrazione
{
	FARMACO_NIENTE,
	FARMACO_INIZIO,
	FARMACO_CONTINUA,
	FARMACO_FINE
};

typedef struct Colonna
{
	long lIDEsame;
	BOOL bRecordSenzaAccesso;
} STRUCT_COLONNA;

typedef struct Riga
{  
	char szTitoloRiga[1024];
	long lIDCampo;
	FieldType lTipoCampo;
	void* pCampo;
	long lFaseFarmaco;
} STRUCT_RIGA;

class CCronicitaPazienteDlg : public CResizableDialog
{

	DECLARE_DYNAMIC(CCronicitaPazienteDlg)

public:

	CCronicitaPazienteDlg(CWnd* pParent, CEsamiView* pEsamiView, CPazientiSet* pPazientiSet);
	virtual ~CCronicitaPazienteDlg();

	enum { IDD = IDD_CRONICITA_PAZIENTE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnChiudi();
	afx_msg void OnBnClickedBtnNewRecord();
	afx_msg void OnNMClickListSn(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListDx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:

	void FillDatiCampoLibero(long lIDCampo, STRUCT_RIGA* pRiga);
	void FillDatiCampoScore(long lIDCampo, STRUCT_RIGA* pRiga);
	void FillDatiCampoFarmaco(long lIDCampo, STRUCT_RIGA* pRiga);
	void RiempiLista();

	//

	CEsamiView* m_pEsamiView;

	CEsamiSet m_setEsami;
	CPazientiSet* m_pPazientiSet;

	long m_lNumeroColonne;
	STRUCT_COLONNA* m_pColonne;

	long m_lNumeroRighe;
	STRUCT_RIGA* m_pRighe;

	//

	CBrush m_brushSfondoEdit;

	CButtonLocalize m_ctrlBtnNewRecord;
	CButtonLocalize m_ctrlBtnChiudi;

	CEdit m_ctrlEdit01;

	CImageList m_ctrlImageList;

	CPazienteCronicoSnListCtrl m_ctrlListSn;
	CPazienteCronicoDxListCtrl m_ctrlListDx;

	CStatic m_ctrlStatic01;
	CStatic m_ctrlStatic02;
	CStatic m_ctrlStatic03;

};

#endif /* _CRONICITAPAZIENTEDLG_H_ */