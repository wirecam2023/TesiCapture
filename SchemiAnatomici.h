// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
#ifndef _SchemiAnatomici_H_
#define _SchemiAnatomici_H_

#include <io.h>
#include <math.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "Bmp.h"
#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "PuntiSet.h"

#include "SchemiAnatomiciEtichette.h"

class CSchemiAnatomici
{
public:
	CSchemiAnatomici();
	~CSchemiAnatomici();

	//void SetUIProperties(CEsamiView* p_pEsamiView, CWnd* p_Frame, CRect p_Rect);
	//BOOL ImportImageFromDisk(CString p_sFullPathImg, CRect* p_Rect, CDib* p_Dib);

protected:
	/*
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT uFlags, CPoint ptMouse);
	afx_msg void OnDraw(CDC* pDC);
	*/

private:
	long    m_lID; // do esquema anatomico - PK da tabela Schemi_Anatomici
	CString m_sDescrizione; // do esquema anatomico
	long    m_lUO; // FK: ID em UO
	CString m_sCodicePrestazionePrevista; // FK: CODICEPRESTAZIONEPREVISTA na tabela VISTA_EXT_PRESTAZIONI
	CString m_sImmagine_FullPath; // pasta e nome do arquivo da imagem
	long    m_lImmagine_Larghezza; // in pixels
	long    m_lImmagine_Altezza; // in pixels
	double	m_dZoom_Factor;
	BOOL    m_bEliminato; // bool deleted or not in table Schemi_Anatomici

	CList<CSchemiAnatomiciEtichette> m_lstEtichette;
	CSchemiAnatomiciEtichette        m_lstEtichette_[1];    // usado apenas para ligação no diagrama de classes

	friend class CSchemiAnatomiciSet;
	friend class CSchemiAnatomiciRecordDlg;
	friend class CSchemiAnatomiciEditDlg;

	//CEsamiView* m_pEsamiView;

	//CWnd* m_pFrame;
	//CRect m_Rect;
	//CDib m_Dib;
};

// -------------------------------------------------------------------------------------

class CSchemiAnatomiciAggiunto : public CSchemiAnatomici
{
public:
	CSchemiAnatomiciAggiunto();
	~CSchemiAnatomiciAggiunto();

private:
	long    m_lContatore; // CONTATORE da inclusao - PK: na tabela Schemi_Anatomici_Aggiunto
	long    m_lContatore_Eesami; // FK: CONTATORE na tabela EXT_EESAME
	CString m_sDescrizione; // descricao da inclusao do esquema no exame
	CString m_sData_Ora; // data e hora da inclusao
	int     m_Stato; // 0=criado; 1=definido; 2=exportado
	BOOL    m_bEliminato; // bool deleted or not na tabela Schemi_Anatomici_Aggiunto

	CList<CSchemiAnatomiciEtichetteAggiunto> m_lstEtichetteAggiunto;
	CSchemiAnatomiciEtichetteAggiunto        m_lstEtichetteAggiunto_[1];    // usado apenas para ligação no diagrama de classes
};

#endif