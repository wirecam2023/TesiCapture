#ifndef _ALBUMESAMEDLG_H_
	#define _ALBUMESAMEDLG_H_

#include "EditBmp.h"
#include "EndoxResizableDlg.h"
#include ".\DLL_Imaging\h\AmImgBackup.h"

class CAlbumEsameDlg : public CEndoxResizableDlg
{

public:

	CAlbumEsameDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bAlbumPaziente = FALSE); 
	virtual ~CAlbumEsameDlg();

	enum { IDD = IDD_ALBUM_ESAME };

	CBitmapButtonEx	m_BtnImmPrev;
	CBitmapButtonEx	m_BtnImmNext;

	CBitmapButtonEx	m_BtnChangeView;
	CBitmapButtonEx m_BtnExportCD;
	CBitmapButtonEx m_BtnExportDVD;
	CBitmapButtonEx m_BtnExportPPT;
	CBitmapButtonEx m_BtnSendMail;

	// Luiz - 12/03/2019 - P3 - Inclusão de botões Seleção/Deseleção/Preview-Print
	CBitmapButtonEx m_BtnSelectAll;
	CBitmapButtonEx m_BtnDeselectAll;
	CBitmapButtonEx m_BtnImagePreview;
	CEsamiSet* m_pEsamiSet;

	CBitmapButtonEx m_btnExp;
	CBitmapButtonEx m_btnCanc;
	CBitmapButtonEx m_btnEsci;
	
	CFileBmp*		m_pFileBmp[SEDICI_IMMAGINI];
	CEditBmp		m_ctrlEditCommentoSmall[SEDICI_IMMAGINI];
	CEditBmp		m_ctrlEditCommentoLarge[QUATTRO_IMMAGINI];

	CEsamiView*		m_pEsamiView;

	int				m_nDiapoPage;
	int				m_nMaxDiapo;

	int				m_nDiapoPerEsame;

	void	ResetVetDiapo(BOOL bReposition);
	int		FillDiapoIndex();
	void	MoveImage();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnImmPrev();
	afx_msg void OnImmNext();

	// Luiz - 12/03/2019 - P3 - Inclusão de botões Seleção/Deseleção/Preview-Print
	/// <summary> 
	/// Evento collegato al tasto che seleziona tutte le immagini
	/// </summary> 
	afx_msg void OnImmSelectAll();

	/// <summary> 
	/// Evento collegato al tasto che deseleziona tutte le immagini
	/// </summary> 
	afx_msg void OnImmUnselectAll();

	/// <summary> 
	/// Evento collegato al tasto che fa l'anteprima delle immagini
	/// </summary> 
	afx_msg void OnImmPreview();

	afx_msg void OnChangeView();

	afx_msg void OnBnClickedCanc();
	afx_msg void OnBnClickedExp();
	afx_msg void OnBnClickedExpCD();
	afx_msg void OnBnClickedExpDVD();
	afx_msg void OnBnClickedExpPPT();
	afx_msg void OnBnClickedMail();

	afx_msg LRESULT AfterChangeComment(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT AfterElabImage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateSel(WPARAM wParam, LPARAM lParam);

	static void DeleteTempImages(CString folder);
	BOOL RimageBurning(discType iType, int iNumSel);

	DECLARE_MESSAGE_MAP()
	
	//CString m_ctrlStaticNum1 = TEXT("0");	// BUG 4197 - total imagens / qtd selecionadas / OK
	//CStaticLocalize m_ctrlStaticNum1;		// antes apresentava a palavra "Seleção"
	CStaticLocalize m_ctrlStaticNum1;
	CStaticLocalize m_ctrlStaticNum3;	

private:

	void CaricaPunti();
	CList <tagPunti> listPunti;

	CImgListOrgani m_ImgListOrgani;

	// attributo che identifica se devo mostrare l'album del paziente (Esame 90000000+idPaziente)
	BOOL m_bAlbumPaziente;

	static UINT RimageDirectoryBurningThread(LPVOID pParam);
};

#endif /* _ALBUMESAMEDLG_H_ */