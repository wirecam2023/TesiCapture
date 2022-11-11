#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "CampiObbligatoriInsModDlg.h"
#include "CampiObbligatoriProvenienzaSet.h"
#include "Common.h"
#include "EsamiView.h"
#include "FasiEsameSet.h"
#include "TipoEsameSet.h"
#include "CampiObbligatoriSet.h"
#include "FieldDlg.h"
#include "ProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCampiObbligatoriInsModDlg, CDialog)

CCampiObbligatoriInsModDlg::CCampiObbligatoriInsModDlg(CWnd* pParent, CEsamiView* pEsamiView, long lID)
: CDialog(CCampiObbligatoriInsModDlg::IDD, pParent), m_ctrlListProvenienze(TRUE,TRUE, FALSE)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lID = lID;
}

CCampiObbligatoriInsModDlg::~CCampiObbligatoriInsModDlg()
{
}

BEGIN_MESSAGE_MAP(CCampiObbligatoriInsModDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_CMB_FASE, &CCampiObbligatoriInsModDlg::OnCbnSelchangeCmbFase)
	ON_CBN_SELCHANGE(IDC_CMB_FASE2, &CCampiObbligatoriInsModDlg::OnCbnSelchangeCmbFase2)
END_MESSAGE_MAP()

void CCampiObbligatoriInsModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_CMB_TIPOESAME, m_ctrlComboTipoEsame);
	DDX_Control(pDX, IDC_LIST_PROVENIENZE, m_ctrlListProvenienze);
	DDX_Control(pDX, IDC_CMB_FASE, m_ctrlComboFase);
	DDX_Control(pDX, IDC_CMB_FASE2, m_ctrlComboFase2);
	DDX_Control(pDX, IDC_CMB_CAMPO, m_ctrlComboCampo);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
}

BOOL CCampiObbligatoriInsModDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	int nIndex;

	nIndex = m_ctrlComboTipoEsame.AddString(theApp.GetMessageString(IDS_INVIANTE_TUTTI));
	m_ctrlComboTipoEsame.SetItemData(nIndex, (DWORD)-1);
	CTipoEsameSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CCampiObbligatoriInsModDlg::OnInitDialog") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			nIndex = m_ctrlComboTipoEsame.AddString(setTemp.m_sDescrizione);
			m_ctrlComboTipoEsame.SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}
		setTemp.CloseRecordset("CCampiObbligatoriInsModDlg::OnInitDialog");
	}

	/*nIndex = m_ctrlComboProvenienza.AddString(theApp.GetMessageString(IDS_INVIANTE_TUTTI));
	m_ctrlComboProvenienza.SetItemData(nIndex, (DWORD)-1);
	nIndex = m_ctrlComboProvenienza.AddString(theApp.GetMessageString(IDS_INVIANTE_INTERNO));
	m_ctrlComboProvenienza.SetItemData(nIndex, (DWORD)0);
	nIndex = m_ctrlComboProvenienza.AddString(theApp.GetMessageString(IDS_INVIANTE_ESTERNO));
	m_ctrlComboProvenienza.SetItemData(nIndex, (DWORD)1);*/

	//Nuova gestione provenienze
	//RIMA 15158
	m_ctrlListProvenienze.InsertColumn(0, "");
	m_ctrlListProvenienze.InsertColumn(1, theApp.GetMessageString(IDS_DESCRIZIONE));

	m_ctrlListProvenienze.DeleteAllItems();
	m_ctrlListProvenienze.SetSubItemCheck(-1, 0);

	CProvenienzaSet provenienzaSet;
	if (provenienzaSet.OpenRecordset("CCampiObbligatoriInsModDlg::OnInitDialog"))
	{
		while (!provenienzaSet.IsEOF())
		{
			int index = m_ctrlListProvenienze.InsertItem(m_ctrlListProvenienze.GetItemCount(), "");			
			m_ctrlListProvenienze.SetItemData(index, provenienzaSet.m_lId);

			CCampiObbligatoriProvenienzaSet obbligatoriProvenienzaSet;
			CString filter;
			filter.Format("IDCAMPOOBBLIGATORIO=%li AND IDPROVENIENZA=%li", m_lID, provenienzaSet.m_lId);
			obbligatoriProvenienzaSet.SetOpenFilter(filter);

			if (obbligatoriProvenienzaSet.OpenRecordset("CCampiObbligatoriInsModDlg::OnInitDialog"))
			{
				if (!obbligatoriProvenienzaSet.IsEOF())
					m_ctrlListProvenienze.SetSubItemData(index, 0, 1);
				else
					m_ctrlListProvenienze.SetSubItemData(index, 0, 0);

				obbligatoriProvenienzaSet.CloseRecordset("CCampiObbligatoriInsModDlg::OnInitDialog");
			}
			m_ctrlListProvenienze.SetItem(index, 1, LVFIF_TEXT, provenienzaSet.m_sDescrizione, 0, 0, 0, 0);

			provenienzaSet.MoveNext();
		}

		provenienzaSet.CloseRecordset("CCampiObbligatoriInsModDlg::OnInitDialog");
	}

	

	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_ctrlListProvenienze.GetDlgItem(0);
	for (int h = 0; h<pHeader->GetItemCount(); h++)
		m_ctrlListProvenienze.SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

	//

	nIndex = m_ctrlComboFase.AddString("");
	m_ctrlComboFase.SetItemData(nIndex, (DWORD)-1);
	nIndex = m_ctrlComboFase.AddString(theApp.GetMessageString(IDS_CO_CHIUSURA_STAMPA));
	m_ctrlComboFase.SetItemData(nIndex, (DWORD)0);
	nIndex = m_ctrlComboFase.AddString(theApp.GetMessageString(IDS_CO_CONVALIDA));
	m_ctrlComboFase.SetItemData(nIndex, (DWORD)1);

	//Nuove fasi
	CFasiEsameSet fasiEsameSet;
	if (fasiEsameSet.OpenRecordset("CCampiObbligatoriInsModDlg::OnInitDialog"))
	{
		while (!fasiEsameSet.IsEOF())
		{
			nIndex = m_ctrlComboFase2.AddString(fasiEsameSet.m_sDescrizione);
			m_ctrlComboFase2.SetItemData(nIndex, fasiEsameSet.m_lID);			

			fasiEsameSet.MoveNext();
		}

		fasiEsameSet.CloseRecordset("CCampiObbligatoriInsModDlg::OnInitDialog");
	}

	//

	switch(theApp.m_nApplication)
	{
		case PRG_IMAGENT:
		{
			// Sandro 29/05/2013 // 

			//Simone
			//	Secondo me non ha più senso che i campi obbligatori siano quelli che si possono mettere nel report, soprattutto dopo l'introduzione delle fasi.
			//		Adesso tutti i campi dell'interfaccia possono essere resi obbligatori

			/*CString sTestoFisso = theApp.GetMessageString(IDS_TESTOFISSO);
			long lLenTestoFisso = sTestoFisso.GetLength();

			//

			for(int i = 0; i < endox_report_field_num_total; i++)
			{
				if ((CFieldDlg::m_strFieldEndox[i].lID > 0) && (CFieldDlg::m_strFieldEndox[i].bImageNT) && (!CFieldDlg::m_strFieldEndox[i].sCombo.Trim().IsEmpty()))
				{
					// Sandro 29/05/2013 // 

					CString sToAdd = CFieldDlg::m_strFieldEndox[i].sCombo;
					if (sToAdd.GetLength() > lLenTestoFisso)
					{
						if (sToAdd.Right(lLenTestoFisso).CompareNoCase(sTestoFisso) == 0)
						{
							sToAdd = sToAdd.Left(sToAdd.GetLength() - lLenTestoFisso);
							sToAdd.Trim();
						}
					}

					//

					nIndex = m_ctrlComboCampo.AddString(sToAdd);
					m_ctrlComboCampo.SetItemData(nIndex, (DWORD)CFieldDlg::m_strFieldEndox[i].lID);
				}
			}
			break;*/

			CString sTestoFisso = theApp.GetMessageString(IDS_TESTOFISSO);
			long lLenTestoFisso = sTestoFisso.GetLength();

			for (int i = 0; i < form_list_total; i++)
			{
				if ((g_FormCaract[i].lID > 0) && (g_FormCaract[i].bImageNT) && (!g_FormCaract[i].sDescrizione.Trim().IsEmpty()))
				{
					// Sandro 29/05/2013 // 

					CString sToAdd = g_FormCaract[i].sDescrizione;
					if (sToAdd.GetLength() > lLenTestoFisso)
					{
						if (sToAdd.Right(lLenTestoFisso).CompareNoCase(sTestoFisso) == 0)
						{
							sToAdd = sToAdd.Left(sToAdd.GetLength() - lLenTestoFisso);
							sToAdd.Trim();
						}
					}

					//

					nIndex = m_ctrlComboCampo.AddString(sToAdd);
					m_ctrlComboCampo.SetItemData(nIndex, (DWORD)g_FormCaract[i].lID);
				}
			}

			break;
		}
		default:
		{
			//Simone
			//	Secondo me non ha più senso che i campi obbligatori siano quelli che si possono mettere nel report, soprattutto dopo l'introduzione delle fasi.
			//		Adesso tutti i campi dell'interfaccia possono essere resi obbligatori

			/*CString sTestoFisso = theApp.GetMessageString(IDS_TESTOFISSO);
			long lLenTestoFisso = sTestoFisso.GetLength();

			for(int i = 0; i < endox_report_field_num_total; i++)
			{
				if ((CFieldDlg::m_strFieldEndox[i].lID > 0) && (CFieldDlg::m_strFieldEndox[i].bEndox) && (!CFieldDlg::m_strFieldEndox[i].sCombo.Trim().IsEmpty()))
				{
					// Sandro 29/05/2013 // 

					CString sToAdd = CFieldDlg::m_strFieldEndox[i].sCombo;
					if (sToAdd.GetLength() > lLenTestoFisso)
					{
						if (sToAdd.Right(lLenTestoFisso).CompareNoCase(sTestoFisso) == 0)
						{
							sToAdd = sToAdd.Left(sToAdd.GetLength() - lLenTestoFisso);
							sToAdd.Trim();
						}
					}

					//

					nIndex = m_ctrlComboCampo.AddString(sToAdd);
					m_ctrlComboCampo.SetItemData(nIndex, (DWORD)CFieldDlg::m_strFieldEndox[i].lID);
				}
			}*/

			CString sTestoFisso = theApp.GetMessageString(IDS_TESTOFISSO);
			long lLenTestoFisso = sTestoFisso.GetLength();

			for (int i = 0; i < form_list_total; i++)
			{
				if ((g_FormCaract[i].lID > 0) && (g_FormCaract[i].bEndox) && (!g_FormCaract[i].sDescrizione.Trim().IsEmpty()))
				{
					// Sandro 29/05/2013 // 

					CString sToAdd = g_FormCaract[i].sDescrizione;
					if (sToAdd.GetLength() > lLenTestoFisso)
					{
						if (sToAdd.Right(lLenTestoFisso).CompareNoCase(sTestoFisso) == 0)
						{
							sToAdd = sToAdd.Left(sToAdd.GetLength() - lLenTestoFisso);
							sToAdd.Trim();
						}
					}

					//

					nIndex = m_ctrlComboCampo.AddString(sToAdd);
					m_ctrlComboCampo.SetItemData(nIndex, (DWORD)g_FormCaract[i].lID);
				}
			}

			break;
		}
	}

	m_ctrlComboTipoEsame.SetCurSel(0);
	//m_ctrlComboProvenienza.SetCurSel(0);
	m_ctrlComboFase.SetCurSel(0);
	if (m_lID > 0) // sto modificando uno preesistente //
	{
		CCampiObbligatoriSet setLoad;

		CString strTemp;
		strTemp.Format("ID=%li", m_lID);

		setLoad.SetOpenFilter(strTemp);
		if (setLoad.OpenRecordset("CCampiObbligatoriInsModDlg::OnInitDialog"))
		{
			if (!setLoad.IsEOF())
			{
				int nTemp;

				if (setLoad.m_lIDTipoEsame > 0)
				{
					CTipoEsameSet setTipoEsame;
					nTemp = m_ctrlComboTipoEsame.FindStringExact(-1, setTipoEsame.GetDescrizione(setLoad.m_lIDTipoEsame));
					if (nTemp >=0)
						m_ctrlComboTipoEsame.SetCurSel(nTemp);
				}

				//m_ctrlComboProvenienza.SetCurSel(setLoad.m_li + 1);


				for (int i = 0; i < m_ctrlComboFase2.GetCount(); i++)
				{
					if (m_ctrlComboFase2.GetItemData(i) == setLoad.m_lIDFaseNew)
					{
						m_ctrlComboFase2.SetCurSel(i);
						break;
					}
				}

				for(int i = 0; i < m_ctrlComboCampo.GetCount(); i++)
				{
					if ((long)m_ctrlComboCampo.GetItemData(i) == setLoad.m_lCampo)
					{
						m_ctrlComboCampo.SetCurSel(i);
						break;
					}
				}
			}

			setLoad.CloseRecordset("CCampiObbligatoriInsModDlg::OnInitDialog");
		}
	}

	if (theApp.m_nApplication == PRG_IMAGENT)
	{
		m_ctrlStatic01.ShowWindow(SW_HIDE);
		m_ctrlStatic02.ShowWindow(SW_HIDE);
		m_ctrlStatic04.ShowWindow(SW_HIDE);
		m_ctrlComboTipoEsame.ShowWindow(SW_HIDE);
		m_ctrlListProvenienze.ShowWindow(SW_HIDE);
		m_ctrlComboFase.ShowWindow(SW_HIDE);
	}

	theApp.LocalizeDialog(this, CCampiObbligatoriInsModDlg::IDD, "CampiObbligatoriInsModDlg");
	return bReturn;
}

void CCampiObbligatoriInsModDlg::OnOK()
{
	if (m_ctrlComboCampo.GetCurSel() < 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REQUESTEDFIELD_NOTSELECTED));
		return;
	}

	CCampiObbligatoriSet setSave;
	if (m_lID > 0) // sto modificando uno preesistente //
	{
		CString strTemp;
		strTemp.Format("ID=%li", m_lID);
		setSave.SetOpenFilter(strTemp);
		if (setSave.OpenRecordset("CCampiObbligatoriInsModDlg::OnOK", TRUE))
		{
			if (!setSave.IsEOF())
			{
				if (setSave.EditRecordset("CCampiObbligatoriInsModDlg::OnOK"))
				{
					setSave.m_lIDTipoEsame = (long)m_ctrlComboTipoEsame.GetItemData(m_ctrlComboTipoEsame.GetCurSel());		
					if ((long)m_ctrlComboFase.GetItemData(m_ctrlComboFase.GetCurSel()) > 0)
					{
						setSave.m_lIDFaseNew = -1;
					}
					else
					{
						setSave.m_lIDFaseNew = (long)m_ctrlComboFase2.GetItemData(m_ctrlComboFase2.GetCurSel());
					}
					setSave.m_lCampo = (long)m_ctrlComboCampo.GetItemData(m_ctrlComboCampo.GetCurSel());

					if (setSave.UpdateRecordset("CCampiObbligatoriInsModDlg::OnOK"))
					{
						//Nella modifica devo aggiungere quelli attivati e non già presenti, e rimuovere quelli disattivati se presenti
						for (int i = 0; i < m_ctrlListProvenienze.GetItemCount(); i++)
						{
							int active = m_ctrlListProvenienze.GetSubItemData(i, 0);
							int idProvenienza = m_ctrlListProvenienze.GetItemData(i);

							if (active)
							{								
								CCampiObbligatoriProvenienzaSet set;
								CString filter;
								filter.Format("IDCAMPOOBBLIGATORIO=%li AND IDPROVENIENZA=%li", m_lID, idProvenienza);
								set.SetOpenFilter(filter);

								if (set.OpenRecordset("CCampiObbligatoriInsModDlg::OnOK"))
								{
									if (set.IsEOF())									
									{
										if (set.AddNewRecordset("CCampiObbligatoriInsModDlg::OnOK"))
										{
											set.m_lIdCampiObbligatori = setSave.m_lID;
											set.m_lIdProvenienza = idProvenienza;

											set.UpdateRecordset("CCampiObbligatoriInsModDlg::OnOK");
										}
									}

									set.CloseRecordset("CCampiObbligatoriInsModDlg::OnOK");
								}
							}
							else
							{
								CCampiObbligatoriProvenienzaSet set;
								CString filter;
								filter.Format("IDCAMPOOBBLIGATORIO=%li AND IDPROVENIENZA=%li", m_lID, idProvenienza);
								set.SetOpenFilter(filter);

								if (set.OpenRecordset("CCampiObbligatoriInsModDlg::OnOK"))
								{
									if (!set.IsEOF())
									{
										set.DeleteRecordset("CCampiObbligatoriInsModDlg::OnOK");										
									}

									set.CloseRecordset("CCampiObbligatoriInsModDlg::OnOK");
								}
							}
						}
					}					
				}
			}

			setSave.CloseRecordset("CCampiObbligatoriInsModDlg::OnOK");
		}
	}
	else // sto inserendo uno nuovo //
	{
		if (setSave.OpenRecordset("CCampiObbligatoriInsModDlg::OnOK", TRUE))
		{
			if (setSave.AddNewRecordset("CCampiObbligatoriInsModDlg::OnOK"))
			{
				setSave.m_lIDTipoEsame = (long)m_ctrlComboTipoEsame.GetItemData(m_ctrlComboTipoEsame.GetCurSel());
				if ((long)m_ctrlComboFase.GetItemData(m_ctrlComboFase.GetCurSel()) > 0)
				{
					setSave.m_lIDFaseNew = -1;
				}
				else
				{
					setSave.m_lIDFaseNew = (long)m_ctrlComboFase2.GetItemData(m_ctrlComboFase2.GetCurSel());
				}
				setSave.m_lCampo = (long)m_ctrlComboCampo.GetItemData(m_ctrlComboCampo.GetCurSel());

				if (setSave.UpdateRecordset("CCampiObbligatoriInsModDlg::OnOK"))
				{
					//Nell'inserimento di un nuovo campo obbligatorio, posso andare tranquillo in inserimento nella tabella CAMPIOBBLIGATORIPROVENIENZA
					for (int i = 0; i < m_ctrlListProvenienze.GetItemCount(); i++)
					{
						int active = m_ctrlListProvenienze.GetSubItemData(i, 0);

						if (active)
						{
							int idProvenienza = m_ctrlListProvenienze.GetItemData(i);

							CCampiObbligatoriProvenienzaSet set;
							if (set.OpenRecordset("CCampiObbligatoriInsModDlg::OnOK"))
							{
								if (set.AddNewRecordset("CCampiObbligatoriInsModDlg::OnOK"))
								{
									set.m_lIdCampiObbligatori = setSave.GetLastAdd();
									set.m_lIdProvenienza = idProvenienza;

									set.UpdateRecordset("CCampiObbligatoriInsModDlg::OnOK");
								}

								set.CloseRecordset("CCampiObbligatoriInsModDlg::OnOK");
							}
						}
					}
				}
			}

			setSave.CloseRecordset("CCampiObbligatoriInsModDlg::OnOK");
		}
	}

	CDialog::OnOK();
}

void CCampiObbligatoriInsModDlg::OnCbnSelchangeCmbFase()
{
	if (m_ctrlComboFase.GetItemData(m_ctrlComboFase.GetCurSel()) >= 0)
	{
		m_ctrlComboFase2.SetCurSel(-1);
	}		
}


void CCampiObbligatoriInsModDlg::OnCbnSelchangeCmbFase2()
{
	if (m_ctrlComboFase2.GetItemData(m_ctrlComboFase.GetCurSel()) >= 0)
	{
		m_ctrlComboFase.SetCurSel(-1);
	}
}
