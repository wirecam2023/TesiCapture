#include "stdafx.h"
#include "Endox.h"
#include "EndoxTabCtrl.h"

#include "EndoxDynForm.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoxTabCtrl, CTabCtrl)

CEndoxTabCtrl::CEndoxTabCtrl()
{
	m_pEsamiView = NULL;

	m_iSelected = -1;
}

CEndoxTabCtrl::~CEndoxTabCtrl()
{
	POSITION pos = m_listForms.GetHeadPosition();
	while(pos != NULL)
	{
		CBaseForm* pForm = m_listForms.GetAt(pos);
		if (pForm != NULL)
		{
			pForm->DestroyWindow();	

			delete pForm;
		}

		m_listForms.GetNext(pos);
	}

	m_listForms.RemoveAll();
}

BEGIN_MESSAGE_MAP(CEndoxTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelChange)

	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CEndoxTabCtrl::DeleteAllItems()
{
	POSITION pos = m_listForms.GetHeadPosition();
	while(pos != NULL)
	{
		CBaseForm* pForm = m_listForms.GetAt(pos);
		if (pForm != NULL)
		{
			pForm->DestroyWindow();	

			delete pForm;
			pForm = NULL;
		}

		m_listForms.GetNext(pos);
	}

	for(int i = 0; i < form_list_total; i++)
	{
		if (m_pEsamiView->m_pDynForm[i] != NULL)
		{
			delete m_pEsamiView->m_pDynForm[i];
			m_pEsamiView->m_pDynForm[i] = NULL;
		}
	}

	m_listForms.RemoveAll();
	return CTabCtrl::DeleteAllItems();
}

LONG CEndoxTabCtrl::InsertItem(LPCTSTR lpszNome, long lIDForm, long lShowAlbum)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(m_pEsamiView != NULL);

	TCITEM item;
	item.mask = TCIF_PARAM | TCIF_TEXT;
	item.lParam = (LPARAM)lIDForm;
	item.pszText = (LPTSTR)lpszNome;

	CBaseForm* formTemp;
	formTemp = new CBaseForm(this, m_pEsamiView, lShowAlbum);
	if (formTemp != NULL)
	{
		CRect rectTemp;

		switch(lShowAlbum)
		{
			case 1: // album classico fisso //
			{
				formTemp->m_pParentFrame = &m_pEsamiView->m_ctrlSubFormEsame;
				m_pEsamiView->m_ctrlSubFormEsame.GetWindowRect(rectTemp);
				break;
			}
			case 2: // album mobile default visibile //
			case 3: // album mobile default nascosto //
			default: // no album //
			{
				formTemp->m_pParentFrame = &m_pEsamiView->m_ctrlSubForm3;
				m_pEsamiView->m_ctrlSubForm3.GetWindowRect(rectTemp);
				break;
			}
		}

		m_pEsamiView->m_ctrlGruppoEsame.ScreenToClient(&rectTemp);

		formTemp->CreateChildForm(rectTemp, lIDForm);
		formTemp->LoadControls();

		m_listForms.AddTail(formTemp);
	}

	return CTabCtrl::InsertItem(GetItemCount(), &item);
}

void CEndoxTabCtrl::MostraSubform()
{
	POSITION pos;
	
	// nascondo il subform vecchio //
	pos = m_listForms.FindIndex(m_iSelected);
	if (pos != NULL)
		m_listForms.GetAt(pos)->ShowWindow(SW_HIDE);

	// mostro il subform nuovo //
	m_iSelected = GetCurSel();
	pos = m_listForms.FindIndex(m_iSelected);
	if (pos != NULL)
		m_listForms.GetAt(pos)->ShowWindow(SW_SHOW);
}

void CEndoxTabCtrl::OnSelChange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	MostraSubform();

	/* Sandro 11/07/2013 // ridisegno tabctrl con problemi da VS2012 //
	
	// Sandro 05/03/2013 // con Visual Studio 2012 non aggiorna più la parte alta dei CTabCtrl //

	CRect rectTemp;
	GetClientRect(rectTemp);
	rectTemp.bottom = 23;

	CBrush brushNull;
	brushNull.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	GetDC()->FillRect(rectTemp, &brushNull);
	brushNull.DeleteObject();

	// aggiungo per un attimo una linguetta finta e la cancello subito perchè così mi ridisegna il controllo correttamente //
	CTabCtrl::DeleteItem(CTabCtrl::InsertItem(GetItemCount(), ""));

	*/
}

void CEndoxTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	// TRACE("--> CEndoxTabCtrl::OnSize --> INIZIO\n");

	CTabCtrl::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	HRGN hReg = ::CreateRectRgn(0, 0, rect.Width(), rect.Height());

	SetWindowRgn(hReg, TRUE);

	int i = 1;

	POSITION pos = m_listForms.GetHeadPosition();
	while(pos != NULL)
	{
		CBaseForm* pBaseForm = m_listForms.GetAt(pos);

		if (pBaseForm != NULL)
		{
			switch(pBaseForm->GetShowAlbum())
			{
				case 2: // album mobile default visibile //
				{
					if (!pBaseForm->GetInvertedState())
					{
						CRect rectTemp;

						// ridimensiono il form portandolo alla dimensione di m_ctrlSubForm3 senza bloccare il resize //
						m_pEsamiView->m_ctrlSubForm3.GetWindowRect(rectTemp);
						pBaseForm->SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);
						pBaseForm->m_pParentFrame = &m_pEsamiView->m_ctrlSubForm3;

						//
						pBaseForm->SendMessage(EPM_RESIZE_FORM);

						// ridimensiono il form portandolo alla dimensione di m_ctrlSubFormEsame bloccando il resize //
						m_pEsamiView->m_ctrlSubFormEsame.GetWindowRect(rectTemp);
						pBaseForm->m_bLockResize = TRUE;
						pBaseForm->SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);
						pBaseForm->m_pParentFrame = &m_pEsamiView->m_ctrlSubFormEsame;
						pBaseForm->m_bLockResize = FALSE;
					}
					else
					{
						pBaseForm->SendMessage(EPM_RESIZE_FORM);
					}

					// TRACE1("    --> BaseForm%d default visibile\n", i);
					break;
				}
				case 3: // album mobile default nascosto //
				{
					if (pBaseForm->GetInvertedState())
					{
						CRect rectTemp;

						// ridimensiono il form portandolo alla dimensione di m_ctrlSubForm3 senza bloccare il resize //
						m_pEsamiView->m_ctrlSubForm3.GetWindowRect(rectTemp);
						pBaseForm->SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);
						pBaseForm->m_pParentFrame = &m_pEsamiView->m_ctrlSubForm3;

						//
						pBaseForm->SendMessage(EPM_RESIZE_FORM);

						// ridimensiono il form portandolo alla dimensione di m_ctrlSubFormEsame bloccando il resize //
						m_pEsamiView->m_ctrlSubFormEsame.GetWindowRect(rectTemp);
						pBaseForm->m_bLockResize = TRUE;
						pBaseForm->SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);
						pBaseForm->m_pParentFrame = &m_pEsamiView->m_ctrlSubFormEsame;
						pBaseForm->m_bLockResize = FALSE;
					}
					else
					{
						pBaseForm->SendMessage(EPM_RESIZE_FORM);
					}

					// TRACE1("    --> BaseForm%d default nascosto\n", i);
					break;
				}
				default:
				{
					pBaseForm->SendMessage(EPM_RESIZE_FORM);

					// TRACE1("    --> BaseForm%d altro tipo\n", i);
					break;
				}
			}
		}
		else
		{
			// TRACE1("    --> BaseForm%d NULL\n", i);
		}

		i++;
		m_listForms.GetNext(pos);
	}
}

CBaseForm* CEndoxTabCtrl::GetSelectedBaseForm()
{
	CBaseForm* pReturn = NULL;

	if (m_iSelected >= 0)
	{
		POSITION pos = m_listForms.FindIndex(m_iSelected);
		if (pos != NULL)
			pReturn = m_listForms.GetAt(pos);
	}

	return pReturn;
}
