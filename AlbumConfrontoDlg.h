#ifndef _ALBUMCONFRONTODLG_H_
	#define _ALBUMCONFRONTODLG_H_

#include "EndoxResizableDlg.h"

class CEsamiSet;

class CAlbumConfrontoDlg : public CEndoxResizableDlg
{

public:

	CAlbumConfrontoDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CAlbumConfrontoDlg();

	enum { IDD = IDD_ALBUM_CONFRONTO };

	CBitmapButtonEx	m_BtnImmFirst[2];
	CBitmapButtonEx	m_BtnImmPrev[2];
	CBitmapButtonEx	m_BtnImmNext[2];
	CBitmapButtonEx	m_BtnImmLast[2];

	CBitmapButtonEx	m_BtnChangeView;
	CBitmapButtonEx	m_BtnPrintImages;
	
	CFileBmp*		m_pFileBmp[2][SEI_IMMAGINI];

	CEsamiView*		m_pEsamiView;
	CEsamiSet		m_setEsami[2];

	int				m_nDiapoPage[2];
	int				m_nMaxDiapo[2];

	int				m_nEsamePage[2];
	int				m_nMaxEsami[2];

	int				m_nDiapoPerEsame;

	void	ResetVetDiapo(BOOL bReposition, int nEsame);
	int		FillDiapoIndex(int nEsame);
	void	MoveImage(int nEsame);
	void	EsamiMove(int nEsame);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnImmFirst1();
	afx_msg void OnImmFirst2();
	afx_msg void OnImmLast1();
	afx_msg void OnImmLast2();
	afx_msg void OnImmNext1();
	afx_msg void OnImmNext2();
	afx_msg void OnImmPrev1();
	afx_msg void OnImmPrev2();
	afx_msg void OnChangeView();
	afx_msg void OnPrintImages();

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();

	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic08;

	CButtonLocalize m_ctrlButtonOK;

private:

	void CaricaPunti(int nEsame);
	CList <tagPunti> listPunti[2];

	CImgListOrgani m_ImgListOrgani[2];
	CComboBox m_ctrlCombo[2];
};

#endif /* _ALBUMCONFRONTODLG_H_ */