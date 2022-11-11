#include "stdafx.h"
#include "Endox.h"
#include "BaseForm.h"

#include "AlbumForm.h"
#include "DynCampoSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBaseForm::CBaseForm(CWnd* pParent, CEsamiView* pEsamiView, long lShowAlbum)
	: CEndoxResizableDlg(CBaseForm::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lShowAlbum = lShowAlbum;

	m_bLockResize = FALSE;

	m_bShowAlbumInverted = FALSE;
}

CBaseForm::~CBaseForm()
{
	POSITION pos = m_listControls.GetHeadPosition();
	while(pos != NULL)
	{
		CEndoxStatic* pStatic = m_listControls.GetAt(pos);

		if (pStatic != NULL)
		{
			RemoveAnchor(pStatic->m_hWnd);
			delete pStatic;
		}

		m_listControls.GetNext(pos);
	}

	m_listControls.RemoveAll();
}

BEGIN_MESSAGE_MAP(CBaseForm, CEndoxResizableDlg)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CBaseForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_FRAME, m_ctrlStaticFrame);
}

BOOL CBaseForm::CreateChildForm(CRect rectFrame, long lIDForm)
{
	BOOL result = CEndoxResizableDlg::Create(CBaseForm::IDD, m_pParentWnd);

	m_lIDForm = lIDForm;

	if (result != FALSE)
		SetWindowPos(NULL, rectFrame.left, rectFrame.top, rectFrame.Width(), rectFrame.Height(), SWP_NOZORDER | SWP_NOOWNERZORDER);

	return result;
}

BOOL CBaseForm::OnInitDialog() 
{
	BOOL bResult = CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_FRAME, CSize(0, 0), CSize(100, 100));

	return bResult;
}

void CBaseForm::OnCancel()
{
	// non chiamarla mai...
	// CEndoxResizableDlg::OnCancel();
}

void CBaseForm::OnOK()
{
	// non chiamarla mai...
	// CEndoxResizableDlg::OnOK();
}

void CBaseForm::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (bShow == TRUE)
	{
		if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pFormImmagini != NULL))
		{
			switch(m_lShowAlbum)
			{
				case 1: // album classico fisso //
				{
					m_pEsamiView->m_pFormImmagini->ShowWindow(SW_SHOW);

					m_pEsamiView->m_ctrlBtnShow.ShowWindow(SW_HIDE);
					m_pEsamiView->m_ctrlBtnHide.ShowWindow(SW_HIDE);

					//

					if (m_pEsamiView->m_bVisualizzaTastoCaricaImmagini)
					{
						m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_SHOW);
						m_pEsamiView->m_ctrlBtnImmagini.SetWindowPos(&m_pEsamiView->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
					}
					else
					{
						m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_HIDE);
					}

					//

					break;
				}
				case 2: // album mobile default visibile //
				{
					if (!m_bShowAlbumInverted)
					{
						m_pEsamiView->m_pFormImmagini->ShowWindow(SW_SHOW);

						m_pEsamiView->m_ctrlBtnShow.ShowWindow(SW_HIDE);
						m_pEsamiView->m_ctrlBtnHide.ShowWindow(SW_SHOW);

						m_pEsamiView->m_ctrlBtnHide.SetWindowPos(&m_pEsamiView->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

						//

						if (m_pEsamiView->m_bVisualizzaTastoCaricaImmagini)
						{
							m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_SHOW);
							m_pEsamiView->m_ctrlBtnImmagini.SetWindowPos(&m_pEsamiView->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
						}
						else
						{
							m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_HIDE);
						}
					}
					else
					{
						m_pEsamiView->m_pFormImmagini->ShowWindow(SW_HIDE);

						m_pEsamiView->m_ctrlBtnShow.ShowWindow(SW_SHOW);
						m_pEsamiView->m_ctrlBtnHide.ShowWindow(SW_HIDE);

						m_pEsamiView->m_ctrlBtnShow.SetWindowPos(&m_pEsamiView->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

						//

						m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_HIDE);
					}
					break;
				}
				case 3: // album mobile default nascosto //
				{
					if (!m_bShowAlbumInverted)
					{
						m_pEsamiView->m_pFormImmagini->ShowWindow(SW_HIDE);

						m_pEsamiView->m_ctrlBtnShow.ShowWindow(SW_SHOW);
						m_pEsamiView->m_ctrlBtnHide.ShowWindow(SW_HIDE);

						m_pEsamiView->m_ctrlBtnShow.SetWindowPos(&m_pEsamiView->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

						//

						m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_HIDE);
					}
					else
					{
						m_pEsamiView->m_pFormImmagini->ShowWindow(SW_SHOW);

						m_pEsamiView->m_ctrlBtnShow.ShowWindow(SW_HIDE);
						m_pEsamiView->m_ctrlBtnHide.ShowWindow(SW_SHOW);

						m_pEsamiView->m_ctrlBtnHide.SetWindowPos(&m_pEsamiView->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

						//

						if (m_pEsamiView->m_bVisualizzaTastoCaricaImmagini)
						{
							m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_SHOW);
							m_pEsamiView->m_ctrlBtnImmagini.SetWindowPos(&m_pEsamiView->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
						}
						else
						{
							m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_HIDE);
						}
					}
					break;
				}
				default: // no album//
				{
					m_pEsamiView->m_pFormImmagini->ShowWindow(SW_HIDE);

					m_pEsamiView->m_ctrlBtnShow.ShowWindow(SW_HIDE);
					m_pEsamiView->m_ctrlBtnHide.ShowWindow(SW_HIDE);

					//

					m_pEsamiView->m_ctrlBtnImmagini.ShowWindow(SW_HIDE);

					//

					break;
				}
			}
		}
	}
	else
	{
		m_pEsamiView->m_pFormImmagini->ShowWindow(SW_HIDE);
	}
}

void CBaseForm::OnSize(UINT nType, int cx, int cy) 
{
	if (!m_bLockResize)
		CEndoxResizableDlg::OnSize(nType, cx, cy);
}

void CBaseForm::InvertShowAlbumState()
{
	m_bShowAlbumInverted = !m_bShowAlbumInverted;
}

BOOL CBaseForm::GetInvertedState()
{
	return m_bShowAlbumInverted;
}

long CBaseForm::GetShowAlbum()
{
	return m_lShowAlbum;
}

void CBaseForm::LoadControls()
{
	if (theApp.m_bCentraleStampa)
	{
		CEndoxStatic *pEndoxStatic = new CEndoxStatic(this, m_pEsamiView);
		if (pEndoxStatic != NULL)
		{
			CRect rectForm;
			GetWindowRect(rectForm);
			rectForm.DeflateRect(DEF_BOR_X, DEF_BOR_Y);

			CRect rectTemp;
			rectTemp.top = 0;
			rectTemp.left = 0;
			rectTemp.bottom = rectForm.Height();
			rectTemp.right = rectForm.Width();
			rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

			if (pEndoxStatic->Create(rectTemp, this, SUB_CENTRALEDISTAMPA, 0, FALSE, 0))
			{
				pEndoxStatic->SetFont(&theApp.m_fontNormal);
				AddAnchor(pEndoxStatic->m_hWnd, CSize(0, 0), CSize(100, 100));

				m_listControls.AddTail(pEndoxStatic);
			}
		}
	}
	else
	{
		CRect rectForm;
		GetWindowRect(rectForm);
		rectForm.DeflateRect(DEF_BOR_X, DEF_BOR_Y);

		CString sFilter;
		sFilter.Format("IDForm=%li", m_lIDForm);

		CDynCampoSet setDynCampo;
		setDynCampo.SetOpenFilter(sFilter);
		setDynCampo.SetSortRecord("TabOrder");
		if (setDynCampo.OpenRecordset("CBaseForm::OnInitDialog"))
		{
			while (!setDynCampo.IsEOF())
			{
				CEndoxStatic *pEndoxStatic = new CEndoxStatic(this, m_pEsamiView);
				if (pEndoxStatic != NULL)
				{
					long DEF_X;
					if (m_lShowAlbum == 1) // album classico fisso //
						DEF_X = DEF_X1;
					else
						DEF_X = DEF_X2;

					// calcolo se il controllo, anche solo in parte, va a collocarsi nella zona dell'album //
					BOOL bOnAlbumZone = (setDynCampo.m_lX + setDynCampo.m_lL > DEF_X1);

					//
					switch (setDynCampo.m_lContenuto)
					{
						case SUB_OSSERVAZIONI:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_OSSERVAZIONI, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case EDT_DIAGNOSTICHE:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_DIAGNOSTICHE, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case EDT_TERAPEUTICHE:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_TERAPEUTICHE, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case SUB_DIAGNOSI:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_DIAGNOSI, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case SUB_CODIFICADIAGNOSIESAME:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_CODIFICADIAGNOSIESAME, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case SUB_CODIFICADIAGNOSIESAME5RIGHE:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_CODIFICADIAGNOSIESAME5RIGHE, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case EDT_MST_COMPLICANZE1:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_COMPLICANZE1, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case EDT_MST_COMPLICANZE2:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_COMPLICANZE2, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						case EDT_MST_COMPLICANZE3:
						{
							CRect rectButton;
							rectButton.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectButton.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectButton.bottom = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectButton.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectButton.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							CEndoxStatic *pEndoxButton = new CEndoxStatic(this, m_pEsamiView);
							if (pEndoxButton != NULL)
							{
								if (pEndoxButton->Create(rectButton, this, BTN_COMPLICANZE3, -1, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
								{
									pEndoxButton->SetFont(&theApp.m_fontNormal);
									AddAnchor(pEndoxButton->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y));

									m_listControls.AddTail(pEndoxButton);
								}
							}

							CRect rectTemp;
							rectTemp.top = (setDynCampo.m_lY + 1) * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);
							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * (setDynCampo.m_lY + 1) / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
						default:
						{
							CRect rectTemp;
							rectTemp.top = setDynCampo.m_lY * rectForm.Height() / DEF_Y;
							rectTemp.left = setDynCampo.m_lX * rectForm.Width() / DEF_X;
							rectTemp.bottom = (setDynCampo.m_lY + setDynCampo.m_lA) * rectForm.Height() / DEF_Y;
							rectTemp.right = (setDynCampo.m_lX + setDynCampo.m_lL) * rectForm.Width() / DEF_X;
							rectTemp.OffsetRect(DEF_BOR_X, DEF_BOR_Y);

							if (pEndoxStatic->Create(rectTemp, this, setDynCampo.m_lContenuto, setDynCampo.m_lColore, bOnAlbumZone, setDynCampo.m_lIDFaseBlocco))
							{
								pEndoxStatic->SetFont(&theApp.m_fontNormal);
								AddAnchor(pEndoxStatic->m_hWnd, CSize(100 * setDynCampo.m_lX / DEF_X, 100 * setDynCampo.m_lY / DEF_Y), CSize(100 * (setDynCampo.m_lX + setDynCampo.m_lL) / DEF_X, 100 * (setDynCampo.m_lY + setDynCampo.m_lA) / DEF_Y));

								m_listControls.AddTail(pEndoxStatic);
							}

							break;
						}
					}

					if ((pEndoxStatic != NULL) && bOnAlbumZone && (m_lShowAlbum == 2)) // album mobile default visibile //
						pEndoxStatic->ShowWindow(SW_HIDE);
				}

				setDynCampo.MoveNext();
			}

			setDynCampo.CloseRecordset("CBaseForm::OnInitDialog");
		}

		if (m_lShowAlbum == 2) // album mobile default visibile //
		{
			// ridimensiono il form portandolo alla dimensione di m_ctrlSubFormEsame //
			CRect rectTemp;
			m_pEsamiView->m_ctrlSubFormEsame.GetWindowRect(rectTemp);
			m_bLockResize = TRUE;
			SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);
			m_pParentFrame = &m_pEsamiView->m_ctrlSubFormEsame;
			m_bLockResize = FALSE;
		}
	}
}
