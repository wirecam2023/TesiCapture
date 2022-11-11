#include "stdafx.h"
#include "Endox.h"
#include ".\MenuDlg.h"

#include "BaseSet.h"
#include "DisplayHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMenuDlg::CMenuDlg(CWnd* pParent, long lComboDefine, CBaseSet* pSet, CString* pStrParent, long* pNumParent, CString* pStrRicerca, CString* pStrRicercaOutput, BOOL bMoreFields, BOOL bSameMultipleSelect, BOOL bOrderByString, CString strInit, int nProgramMode, CRect rect)
	: CDialog(CMenuDlg::IDD, pParent)
{
	if (nProgramMode & FILTER_RECORD_ESAMI)
		m_bModalitaRicerca = TRUE;
	else
		m_bModalitaRicerca = FALSE;

	m_bMoreFields = bMoreFields;
	m_bMoreFieldsOld = FALSE;
	m_bOrderByString = bOrderByString;
	m_bOrPressed = FALSE;
	m_bSameMultipleSelect = bSameMultipleSelect;

	m_nItemCount = 0;
	m_nItemPressed = 0;

	m_lComboDefine = lComboDefine;
	m_lContatore = 0;

	m_rect = rect;

	m_strRicerca = strInit;

	//

	m_pSet = pSet;

	m_pNumOutput = pNumParent;

	m_pStrOutput = pStrParent;
	m_pStrQuery = pStrRicerca;
	m_pStrQueryOut = pStrRicercaOutput;

}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RICERCA, m_ctrlRicerca);
	DDX_Control(pDX, IDC_LISTA, m_ctrLista);

	DDX_Control(pDX, IDC_RESET, m_ctrlButtonReset);
	DDX_Control(pDX, IDC_CLOSE, m_ctrlButtonClose);

	DDX_Text(pDX, IDC_RICERCA, m_strRicerca);
}

BEGIN_MESSAGE_MAP(CMenuDlg, CDialog)

	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_RESET, OnReset)

	ON_BN_CLICKED(IDC_AND, OnBtnAnd)
	ON_BN_CLICKED(IDC_OR, OnBtnOr)

	ON_EN_CHANGE(IDC_RICERCA, OnChangeRicerca)

	ON_LBN_DBLCLK(IDC_LISTA, OnSelectWithMouse)
	ON_LBN_SELCHANGE(IDC_LISTA, OnLbnSelchangeLista)

	ON_WM_SHOWWINDOW()

END_MESSAGE_MAP()

BOOL CMenuDlg::SelectLista()
{
	int		nPos	= m_ctrLista.GetCurSel();
	BOOL	bResult = (nPos != LB_ERR);

	if (m_strRicerca.IsEmpty() && !m_bMoreFields)
		bResult = TRUE;
	
	if (bResult)
	{
		CString strSelect = "";
		long	nSelect   = 0;

		if (nPos != LB_ERR)
		{
			m_ctrLista.GetText(nPos, strSelect);
			nSelect = (long)m_ctrLista.GetItemData(nPos);
		}

		//Selezione multipla
		if (m_pStrOutput)
		{
			BOOL bModify = FALSE;
			
			if (m_bMoreFields)
			{
				if (m_pStrOutput->IsEmpty())
				{
					*m_pStrOutput = strSelect;
					bModify = TRUE;
				
					m_nItemPressed = 1;
					
					if (m_nItemCount > 1)
					{
						GetDlgItem(IDC_AND)->EnableWindow(TRUE);
						GetDlgItem(IDC_OR)->EnableWindow(TRUE);
					}
				}
				else
				{
					//Se non è già stato premuto l'elemento
					CString strOutputUpper(*m_pStrOutput), strSelectUpper(strSelect);
					strOutputUpper.MakeUpper();
					strSelectUpper.MakeUpper();
					if ((m_bSameMultipleSelect) || (strOutputUpper.Find(strSelectUpper) < 0)) // Sandro 20/04/2009 per Bolzano //
					{
						if (!m_bOrPressed)
						{	
							if (m_bModalitaRicerca)
							{
								if (m_bMoreFieldsOld)
								{
									if (m_strRicerca.Find("OR ") != -1)
										*m_pStrOutput = "(" + *m_pStrOutput + ")";

									*m_pStrOutput += " AND " + strSelect;
								}
								else
								{
									*m_pStrOutput += " OR " + strSelect;
								}
							}
							else
							{
								*m_pStrOutput += theApp.m_sTestiConcatenatiSeparatore + strSelect;
							}
						}
						else
						{
							*m_pStrOutput += " " + strSelect;
						}

						bModify = TRUE;
						m_nItemPressed++;

						if (m_nItemPressed < m_nItemCount)
						{
							GetDlgItem(IDC_AND)->EnableWindow(TRUE);
							GetDlgItem(IDC_OR)->EnableWindow(TRUE);
						}
					}
				}
			}
			else
			{
				m_nItemPressed = 1;
				*m_pStrOutput = strSelect;
				bModify = TRUE;
			}

			if (bModify)
			{
				m_bOrPressed = FALSE;
				m_strRicerca = *m_pStrOutput;
				
				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrOutput, FALSE);
			}

			m_lContatore = nSelect;
		}
		
		//Selezione singola
		if (m_pNumOutput)
		{
			CString strTmp;
			//solo se sono in ricerca
			if (m_bModalitaRicerca)
			{
				if (m_bOrPressed)
				{
					if (m_strRicerca.Find(strSelect) < 0)
					{
						m_strRicerca += " " + strSelect;
					
						strTmp.Format("%s %i", *m_pStrQuery, nSelect);
						*m_pStrQuery = strTmp;
						
						m_nItemPressed++;

						if (m_nItemPressed < m_nItemCount)
						{
							GetDlgItem(IDC_AND)->EnableWindow(TRUE);
							GetDlgItem(IDC_OR)->EnableWindow(TRUE);
						}

						m_bOrPressed = FALSE;
					}
				}
				else
				{
					//Ricomincio
					m_strRicerca = strSelect;
					
					strTmp.Format("%i", nSelect);
					*m_pStrQuery = strTmp;

					m_nItemPressed = 1;

					if (m_nItemCount > 1)
					{
						GetDlgItem(IDC_AND)->EnableWindow(TRUE);
						GetDlgItem(IDC_OR)->EnableWindow(TRUE);
					}
				}
			}
			else
			{
				m_strRicerca = strSelect;
			}
			
			(*m_pNumOutput) = nSelect;

			m_lContatore = nSelect;
	
			if (m_pSet->IsOpen())
				m_pSet->SetFieldNull(m_pNumOutput, FALSE);
		
		}
	
	}

	return bResult;
}

BOOL CMenuDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	m_lContatore = 0;

	GetDlgItem(IDC_RESET)->EnableWindow(TRUE);
	
	m_ctrlRicerca.SetParam(this, &m_ctrLista);
	
	if (m_lComboDefine >= 0)
	{
		BOOL bOrderByString = (m_pStrOutput != NULL) && m_bOrderByString;

		m_ctrLista.SetParam(this);

		if (m_ctrLista.SetParamSet(m_lComboDefine, bOrderByString))
			OnChangeRicerca();
	}
	else
	{
		// STRUMENTI //

		BOOL bOrderByString = (m_pStrOutput != NULL) && m_bOrderByString;

		m_ctrLista.SetParam(this);

		if (m_ctrLista.SetParamSet(-1 /* STRUMENTI */, bOrderByString))
			OnChangeRicerca();
	}

	if (m_strRicerca.IsEmpty())
	{
		GetDlgItem(IDC_AND)->EnableWindow(FALSE);
		GetDlgItem(IDC_OR)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_AND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OR)->ShowWindow(SW_HIDE);
	
	if (m_bModalitaRicerca)
	{
		m_bMoreFieldsOld = m_bMoreFields;
		m_bMoreFields = TRUE;

		GetDlgItem(IDC_OR)->ShowWindow(SW_SHOW);
		
		// Davide: forse è giusto
		if (m_pStrOutput && m_bMoreFieldsOld)
			GetDlgItem(IDC_AND)->ShowWindow(SW_SHOW);
	}
	
	m_nItemCount = m_ctrLista.GetCount();

	CRect rectWnd;
	GetWindowRect(&rectWnd);

	SetWindowPos(NULL, min(m_rect.left, theApp.m_rectDesk.right - rectWnd.Width()), min(m_rect.bottom, theApp.m_rectDesk.bottom - rectWnd.Height()), 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	theApp.LocalizeDialog(this, CMenuDlg::IDD, "MenuDlg");
	return TRUE;
}

void CMenuDlg::OnSelectWithMouse()
{
	UpdateData(TRUE);
	
	if (SelectLista())
	{
		if (m_bMoreFields)
		{
			UpdateData(FALSE);
		}
		else
		{
			CDialog::OnOK();
		}
	}
}

void CMenuDlg::OnOK()
{
	UpdateData(TRUE);
	
	if (SelectLista())
	{
		//esco subito in qualsiasi caso....
		CDialog::OnOK();
	}
}

void CMenuDlg::OnClose()
{
	if (m_bOrPressed && m_pStrOutput)
	{
		//Se è stato premuto OR senza aggiungere una condizione lo cancello
		*m_pStrOutput = m_pStrOutput->Left(m_pStrOutput->GetLength() - 3);
		m_pStrOutput->TrimRight();

		if (m_pStrOutput->Right(1) == ")")
			*m_pStrOutput = m_pStrOutput->Mid(1, m_pStrOutput->GetLength() - 2);
	}

	if (m_pStrQueryOut)
		*m_pStrQueryOut = m_strRicerca;

	m_bMoreFields = m_bMoreFieldsOld;

	CDialog::OnOK();
}

void CMenuDlg::OnReset()
{
	GetDlgItem(IDC_RICERCA)->SetWindowText("");
	
	//12/04/2002 Per pararmi il culo
	if (m_pStrOutput != NULL)
		*m_pStrOutput = "";

	if (m_pNumOutput != NULL)
		*m_pNumOutput = -1;
	
	UpdateData(TRUE);
}

void CMenuDlg::OnBtnAnd()
{
	BOOL bAddParentesi = FALSE;

	UpdateData(TRUE);

	if (m_strRicerca.Find("OR ") != -1)
		bAddParentesi = TRUE;

	if (bAddParentesi)
		m_strRicerca = "(" + m_strRicerca + ")";
	
	m_strRicerca += " AND";
	
	if (m_pStrOutput)
	{
		if (bAddParentesi)
			*m_pStrOutput = "(" + *m_pStrOutput + ")";
		
		*m_pStrOutput += " AND";
	}
	else
	{
		if (bAddParentesi)
			*m_pStrQuery = "(" + *m_pStrQuery + ")";
		
		*m_pStrQuery += " AND";
	}

	UpdateData(FALSE);

	GetDlgItem(IDC_AND)->EnableWindow(FALSE);
	GetDlgItem(IDC_OR)->EnableWindow(FALSE);

	m_bOrPressed = TRUE;
}

void CMenuDlg::OnBtnOr()
{
	BOOL bAddParentesi = FALSE;

	UpdateData(TRUE);

	if (m_strRicerca.Find("AND ") != -1)
		bAddParentesi = TRUE;

	if (bAddParentesi)
		m_strRicerca = "(" + m_strRicerca + ")";
	
	m_strRicerca += " OR";
	
	if (m_pStrOutput)
	{
		if (bAddParentesi)
			*m_pStrOutput = "(" + *m_pStrOutput + ")";
		
		*m_pStrOutput += " OR";
	}
	else
	{
		if (bAddParentesi)
			*m_pStrQuery = "(" + *m_pStrQuery + ")";
		
		*m_pStrQuery += " OR";
	}

	UpdateData(FALSE);

	GetDlgItem(IDC_AND)->EnableWindow(FALSE);
	GetDlgItem(IDC_OR)->EnableWindow(FALSE);

	m_bOrPressed = TRUE;
}

void CMenuDlg::OnChangeRicerca()
{
	int nNewPos = -1; 

	UpdateData(TRUE);
	
	if (m_pStrOutput)
	{
		nNewPos = m_ctrLista.FindString(-1, m_strRicerca);
	}
	else
	{
		//significa che dovrei scrivere l'ordinale giusto....
		if (m_pNumOutput)
		{
			CString strNumber;
			long	nNumber;

			nNumber = atoi(m_strRicerca);

			strNumber.Format("%li", nNumber);

			//se non scrivo un numero, mi comporto come per le stringhe...
			if (strNumber != m_strRicerca)
			{
				nNewPos = m_ctrLista.FindString(-1, m_strRicerca);
			}
			else
			{
				int nCount = m_ctrLista.GetCount();
				
				for(int i=0; i<nCount; i++)
				{
					if (nNumber == (long)m_ctrLista.GetItemData(i))
					{
						nNewPos = i;
						break;
					}
				}
			}
		}
	}

	m_ctrLista.SetCurSel(nNewPos);
		
	UpdateData(FALSE);
}

void CMenuDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		int nStart, nEnd;
		m_ctrlRicerca.GetSel(nStart, nEnd);
		m_ctrlRicerca.SetSel(nEnd+1, nEnd+1);
	}
}

void CMenuDlg::OnLbnSelchangeLista()
{
	//Selezione singola
	if (m_pNumOutput)
		OnClose();
}
