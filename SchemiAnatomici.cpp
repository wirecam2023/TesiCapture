// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
#include "stdafx.h"
#include "Endox.h"
#include "SchemiAnatomici.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSchemiAnatomici::CSchemiAnatomici()
{
	//m_pEsamiView = NULL;	// default not valid value
	//m_Rect = NULL;		// default not valid value
	m_sDescrizione = "";
	m_sCodicePrestazionePrevista = "";
	m_sImmagine_FullPath = "";
}

//CSchemiAnatomici::CSchemiAnatomici(CEsamiView* p_pEsamiView, CRect p_Rect)
//{
//	m_pEsamiView = p_pEsamiView;
//	m_Rect = p_Rect;
//}

//void CSchemiAnatomici::SetUIProperties(CEsamiView* p_pEsamiView, CWnd* p_Frame, CRect p_Rect)
//{
//	m_pEsamiView = p_pEsamiView;
//	m_pFrame = p_Frame;
//	m_Rect = p_Rect;
//}

CSchemiAnatomici::~CSchemiAnatomici()
{
}


/*
void CSchemiAnatomici::OnMouseMove(UINT uFlags, CPoint ptMouse)
{
	BOOL bLeftButtonDown = (uFlags & MK_LBUTTON);

	if (bLeftButtonDown)
	{
		CClientDC dc(this);
		//OnPrepareDC(&dc);

		dc.DPtoLP(&ptMouse);
		//m_pDrawDoc->MouseDrag(ptMouse);
	}
}


void CSchemiAnatomici::OnDraw(CDC* pDC)
{
	static BOOL bFirstShow = TRUE;

	if (bFirstShow)
	{
		if (::IsWindow(GetSafeHwnd()))
		{
			bFirstShow = FALSE;
		}
	}
}
*/

// -------------------------------------------------------------------------------------

CSchemiAnatomiciAggiunto::CSchemiAnatomiciAggiunto()
{
}


CSchemiAnatomiciAggiunto::~CSchemiAnatomiciAggiunto()
{
}
