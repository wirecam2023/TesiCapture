#include "stdafx.h"
#include "Endox.h"
#include "EditBmp.h"

#include "Bmp.h"
#include "EditCommentoImmagineDlg.h"
#include "EditStringDlg.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEditBmp::CEditBmp()
{
	m_pParentBmp = NULL;
}

CEditBmp::~CEditBmp()
{
}

BEGIN_MESSAGE_MAP(CEditBmp, CEdit)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CEditBmp::AssignBmp(CBmp* pBmp) 
{
	m_pParentBmp = pBmp;
}

void CEditBmp::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((m_pParentBmp != NULL) && (m_pParentBmp->m_pDib != NULL))
	{
		GetWindowText(m_pParentBmp->m_strComment);

		// Sandro 28/10/2015 // 
		if (theApp.m_bAlbumImmaginiUsaListaCommenti)
		{
			CRect rectEdit;
			GetWindowRect(rectEdit);

			CRect rectBmp;
			m_pParentBmp->GetWindowRect(rectBmp);

			CRect rectPos;
			rectPos.left = rectEdit.left;
			rectPos.top = rectBmp.top;
			rectPos.right = rectEdit.right;
			rectPos.bottom = rectEdit.bottom;

			CEditCommentoImmagineDlg dlg(this, IDS_MODIFY_COMMENT, m_pParentBmp->m_strComment, m_pParentBmp->m_pEsamiView->m_pEsamiSet->m_lIDEsame, rectPos);
			if (dlg.DoModal() == IDOK)
			{
				if ((m_pParentBmp->m_pEsamiView != NULL) && (m_pParentBmp->m_pEsamiView->m_pImgManager != NULL))
				{
					if (m_pParentBmp->m_pEsamiView->m_pImgManager->UpdateImgDescription(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, m_pParentBmp->m_lID, dlg.GetValue()) == TRUE)
					{
						m_pParentBmp->m_strComment = dlg.GetValue();
						SetWindowText(m_pParentBmp->m_strComment);

						m_pParentBmp->m_pParentAlbum->SendMessage(MSG_AFTER_CHANGECOMMENT, (WPARAM)m_pParentBmp->m_lID, (LPARAM)&m_pParentBmp->m_strComment);
					}
				}
			}
		}
		else
		{
			CEditStringDlg dlg(this, IDS_MODIFY_COMMENT, m_pParentBmp->m_strComment);
			if (dlg.DoModal() == IDOK)
			{
				if ((m_pParentBmp->m_pEsamiView != NULL) && (m_pParentBmp->m_pEsamiView->m_pImgManager != NULL))
				{
					if (m_pParentBmp->m_pEsamiView->m_pImgManager->UpdateImgDescription(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, m_pParentBmp->m_lID, dlg.GetValue()) == TRUE)
					{
						m_pParentBmp->m_strComment = dlg.GetValue();
						SetWindowText(m_pParentBmp->m_strComment);

						m_pParentBmp->m_pParentAlbum->SendMessage(MSG_AFTER_CHANGECOMMENT, (WPARAM)m_pParentBmp->m_lID, (LPARAM)&m_pParentBmp->m_strComment);
					}
				}
			}
		}
	}
}

void CEditBmp::Refresh()
{
	if (m_pParentBmp != NULL)
		SetWindowText(m_pParentBmp->m_strComment);
}