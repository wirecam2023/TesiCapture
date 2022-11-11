#include "stdafx.h"
#include "Endox.h"
#include "StatisticheEsamiDlg.h"

#include "CustomDate.h"
#include "MediciSet.h"
#include "TipoEsameSet.h"
#include "VistaStatisticheEsamiSet.h"

#include "ExportWaitDlg.h"
#include "XmlUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CStatisticheEsamiDlg, CEndoxResizableDlg)

CStatisticheEsamiDlg::CStatisticheEsamiDlg(CWnd* pParent, long lAnno)
	: CEndoxResizableDlg(CStatisticheEsamiDlg::IDD, pParent),
	  m_ctrlList(TRUE, TRUE, FALSE)
{
	BeginWaitCursor();

	//

	m_lAnno = lAnno;

	m_bStatisticaEsamiChiusi = (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_bPersonalizzazioniBrasileSirio);

	m_lNumeroEsami = 0;
	m_pArrayEsami = NULL;

	m_lNumeroMedici = 0;
	m_pArrayMedici = NULL;

	m_pNumeriTridimensionale = NULL;

	//

	CTipoEsameSet setTemp1;
	setTemp1.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	setTemp1.SetSortRecord("Descrizione");
	if (setTemp1.OpenRecordset("CStatisticheEsamiDlg::CStatisticheEsamiDlg"))
	{
		while(!setTemp1.IsEOF())
		{
			m_lNumeroEsami++;
			setTemp1.MoveNext();
		}

		if (m_lNumeroEsami > 0)
		{
			setTemp1.MoveFirst();

			m_pArrayEsami = new long[m_lNumeroEsami];

			int iTemp = 0;
			while(!setTemp1.IsEOF())
			{
				m_pArrayEsami[iTemp] = setTemp1.m_lContatore;

				iTemp++;
				setTemp1.MoveNext();
			}
		}

		setTemp1.CloseRecordset("CStatisticheEsamiDlg::CStatisticheEsamiDlg");
	}

	//

	CMediciSet setTemp2;
	setTemp2.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		setTemp2.SetSortRecord("Nome, Cognome");
	else
		setTemp2.SetSortRecord("Cognome, Nome");
	if (setTemp2.OpenRecordset("CStatisticheEsamiDlg::CStatisticheEsamiDlg"))
	{
		while(!setTemp2.IsEOF())
		{
			m_lNumeroMedici++;
			setTemp2.MoveNext();
		}

		if (m_lNumeroMedici > 0)
		{
			setTemp2.MoveFirst();

			m_pArrayMedici = new long[m_lNumeroMedici];

			int iTemp = 0;
			while(!setTemp2.IsEOF())
			{
				m_pArrayMedici[iTemp] = setTemp2.m_lContatore;

				iTemp++;
				setTemp2.MoveNext();
			}
		}

		setTemp2.CloseRecordset("CStatisticheEsamiDlg::CStatisticheEsamiDlg");
	}

	//

	if ((m_lNumeroEsami > 0) && (m_lNumeroMedici > 0))
	{
		// inizializzo ed azzero la matrice tridimensionale che terrà il numero di esami eseguiti //

		m_pNumeriTridimensionale = new long[12 * m_lNumeroEsami * m_lNumeroMedici];

		for(int i = 0; i < 12 * m_lNumeroEsami * m_lNumeroMedici; i++)
			m_pNumeriTridimensionale[i] = 0;

		// prendo da DB tutti gli esami dell'anno e li "catalogo" //

		CCustomDate dateIniz(m_lAnno, 1, 1, 0, 0, 0);
		CCustomDate dateFine(m_lAnno + 1, 1, 1, 0, 0, 0);

		CString strFilter;
		strFilter.Format("Data>=%li AND Data<%li", dateIniz.GetDate(), dateFine.GetDate());

		CVistaStatisticheEsamiSet setTemp(m_bStatisticaEsamiChiusi);
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CStatisticheEsamiDlg::CStatisticheEsamiDlg"))
		{
			while(!setTemp.IsEOF())
			{
				AggiungiEsame(setTemp.m_lData, setTemp.m_lIDEsame, setTemp.m_lMedico);
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CStatisticheEsamiDlg::CStatisticheEsamiDlg");
		}
	}
	else
	{
		if (m_lNumeroEsami <= 0)
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NESSUN_TIPOESAME_PRESENTE));

		if (m_lNumeroMedici <= 0)
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NESSUN_MEDICO_PRESENTE));
	}

	//

	m_pxmlDocument = NULL;

	EndWaitCursor();
}

CStatisticheEsamiDlg::~CStatisticheEsamiDlg()
{
	if (m_pArrayEsami != NULL)
	{
		delete m_pArrayEsami;
		m_pArrayEsami = NULL;
	}

	if (m_pArrayMedici != NULL)
	{
		delete m_pArrayMedici;
		m_pArrayMedici = NULL;
	}

	if (m_pNumeriTridimensionale != NULL)
	{
		delete m_pNumeriTridimensionale;
		m_pNumeriTridimensionale = NULL;
	}
	
}

BEGIN_MESSAGE_MAP(CStatisticheEsamiDlg, CEndoxResizableDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CStatisticheEsamiDlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_EXPORT, &CStatisticheEsamiDlg::OnBnClickedExport)
END_MESSAGE_MAP()

void CStatisticheEsamiDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDC_TAB, m_ctrlTab);
	DDX_Control(pDX, IDC_EXPORT, m_ctrlBtnExport);
}

BOOL CStatisticheEsamiDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	if (m_pNumeriTridimensionale != NULL)
	{
		BeginWaitCursor();

		//

		AddAnchor(IDC_TAB, CSize(0, 0), CSize(100, 100));
		AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
		AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));
		AddAnchor(IDC_EXPORT, CSize(0, 100), CSize(0, 100));

		//

		//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
		SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //;

		// inserisco i vari tab (TOTALE + uno per mese) //

		m_ctrlTab.InsertItem(0, theApp.GetMessageString(IDS_TOTALE));
		m_ctrlTab.InsertItem(1, theApp.GetMessageString(IDS_JANUARY));
		m_ctrlTab.InsertItem(2, theApp.GetMessageString(IDS_FEBRUARY));
		m_ctrlTab.InsertItem(3, theApp.GetMessageString(IDS_MARCH));
		m_ctrlTab.InsertItem(4, theApp.GetMessageString(IDS_APRIL));
		m_ctrlTab.InsertItem(5, theApp.GetMessageString(IDS_MAY));
		m_ctrlTab.InsertItem(6, theApp.GetMessageString(IDS_JUNE));
		m_ctrlTab.InsertItem(7, theApp.GetMessageString(IDS_JULY));
		m_ctrlTab.InsertItem(8, theApp.GetMessageString(IDS_AUGUST));
		m_ctrlTab.InsertItem(9, theApp.GetMessageString(IDS_SEPTEMBER));
		m_ctrlTab.InsertItem(10, theApp.GetMessageString(IDS_OCTOBER));
		m_ctrlTab.InsertItem(11, theApp.GetMessageString(IDS_NOVEMBER));
		m_ctrlTab.InsertItem(12, theApp.GetMessageString(IDS_DECEMBER));

		// inserisco le varie colonne //

		m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

		if (m_bStatisticaEsamiChiusi)
		{
			m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);							// prima colonna per il medico //
			for (int i = 0; i < m_lNumeroEsami; i++)
				m_ctrlList.InsertColumn(i + 1, "", LVCFMT_RIGHT, 0);				// una colonna per ciascun tipo di esame //
			m_ctrlList.InsertColumn(m_lNumeroEsami, "", LVCFMT_RIGHT, 0);			// una colonna per il totale //
			m_ctrlList.InsertColumn(m_lNumeroEsami + 1, "", LVCFMT_RIGHT, 0);		// ultima colonna sempre vuota //
		}
		else
		{
			m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);							// prima colonna per il tipo di esame //
			for (int i = 0; i < m_lNumeroMedici; i++)
				m_ctrlList.InsertColumn(i + 1, "", LVCFMT_RIGHT, 0);				// una colonna per ciascun medico //
			m_ctrlList.InsertColumn(m_lNumeroMedici, "", LVCFMT_RIGHT, 0);			// una colonna per il totale //
			m_ctrlList.InsertColumn(m_lNumeroMedici + 1, "", LVCFMT_RIGHT, 0);		// ultima colonna sempre vuota //
		}

		// inserisco la prima riga (titoli della tabella) //

		if (m_bStatisticaEsamiChiusi)
		{
			m_ctrlList.InsertItem(0, "");
			m_ctrlList.SetSubItemBkColor(0, 0, theApp.m_colorSfondo[4]);										// prima cella in alto a sinistra //
			for (int i = 0; i < m_lNumeroEsami; i++)
			{
				m_ctrlList.SetItemText(0, i + 1, CTipoEsameSet().GetDescrizione(m_pArrayEsami[i]));
				m_ctrlList.SetSubItemBkColor(0, i + 1, theApp.m_colorSfondo[4]);								// prima riga (tipi di esame) //
			}
			m_ctrlList.SetItemText(0, m_lNumeroEsami + 1, theApp.GetMessageString(IDS_TOTALE));
			m_ctrlList.SetSubItemBkColor(0, m_lNumeroEsami + 1, theApp.m_colorSfondo[4]);						// prima riga (TOTALE) //
		}
		else
		{
			m_ctrlList.InsertItem(0, "");
			m_ctrlList.SetSubItemBkColor(0, 0, theApp.m_colorSfondo[4]);										// prima cella in alto a sinistra //
			for (int i = 0; i < m_lNumeroMedici; i++)
			{
				m_ctrlList.SetItemText(0, i + 1, CMediciSet().GetCognomeNomeFromContatore(m_pArrayMedici[i]));
				m_ctrlList.SetSubItemBkColor(0, i + 1, theApp.m_colorSfondo[4]);								// prima riga (nomi dei medici) //
			}
			m_ctrlList.SetItemText(0, m_lNumeroMedici + 1, theApp.GetMessageString(IDS_TOTALE));
			m_ctrlList.SetSubItemBkColor(0, m_lNumeroMedici + 1, theApp.m_colorSfondo[4]);						// prima riga (TOTALE) //
		}

		// inserisco le righe //

		if (m_bStatisticaEsamiChiusi)
		{
		}
		else
		{
			for (int i = 0; i < m_lNumeroEsami; i++)
			{
				m_ctrlList.InsertItem(i + 1, CTipoEsameSet().GetDescrizione(m_pArrayEsami[i]));

				m_ctrlList.SetSubItemBkColor(i + 1, 0, theApp.m_colorSfondo[4]);								// prima colonna (nomi degli esami) //

				for (int j = 1; j < m_lNumeroMedici + 1; j++)
					m_ctrlList.SetSubItemBkColor(i + 1, j, RGB_WHITE);											// tutte le colonne in mezzo // Sandro 17/07/2014 // altrimenti rimangono nere :-D //

				m_ctrlList.SetSubItemBkColor(i + 1, m_lNumeroMedici + 1, theApp.m_colorSfondo[0]);				// ultima colonna (cifre totale) //
			}
		}

		// inserisco la riga dei totali //

		if (m_bStatisticaEsamiChiusi)
		{
		}
		else
		{
			m_ctrlList.InsertItem(m_lNumeroEsami + 1, theApp.GetMessageString(IDS_TOTALE));
			m_ctrlList.SetSubItemBkColor(m_lNumeroEsami + 1, 0, theApp.m_colorSfondo[4]);						// ultima riga (TOTALE) //
			for (int i = 1; i < m_lNumeroMedici + 1; i++)
				m_ctrlList.SetSubItemBkColor(m_lNumeroEsami + 1, i, theApp.m_colorSfondo[0]);					// ultima riga (cifre totali) //
			m_ctrlList.SetSubItemBkColor(m_lNumeroEsami + 1, m_lNumeroMedici + 1, theApp.m_colorSfondo[0]);		// ultima riga ultima cella (totale dei totali) //
		}

		// aggiusto la larghezza delle colonne //

		/*if (m_bStatisticaEsamiChiusi)
		{
			for (int i = 0; i < m_lNumeroEsami + 2; i++)
				m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);
		}
		else
		{
			for (int i = 0; i < m_lNumeroMedici + 2; i++)
				m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);
		}*/

		//

		OnTcnSelchangeTab(NULL, NULL);

		for (int h = 0; h<m_ctrlList.GetHeaderCtrl()->GetItemCount(); h++)
			m_ctrlList.SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

		//
		
		theApp.LocalizeDialog(this, CStatisticheEsamiDlg::IDD, "StatisticheEsamiDlg");

		//

		EndWaitCursor();
	}
	else
	{
		EndDialog(IDCANCEL);
	}

	return TRUE;
}

void CStatisticheEsamiDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);

	int nMese = m_ctrlTab.GetCurSel() - 1;

	if (m_bStatisticaEsamiChiusi)
	{
	}
	else
	{
		long* pTotaleColonna = new long[m_lNumeroMedici + 1];
		for (int i = 0; i < m_lNumeroMedici + 1; i++)
			pTotaleColonna[i] = 0;

		for (int i = 0; i < m_lNumeroEsami; i++)
		{
			long lTotaleRiga = 0;
			for (int j = 0; j < m_lNumeroMedici; j++)
			{
				long lTemp = GetValoreCella(nMese, i, j);

				CString strTemp;
				strTemp.Format("%li", lTemp);
				m_ctrlList.SetItemText(i + 1, j + 1, strTemp);

				lTotaleRiga += lTemp;
				pTotaleColonna[j] += lTemp;
			}

			CString strTemp;
			strTemp.Format("%li", lTotaleRiga);
			m_ctrlList.SetItemText(i + 1, m_lNumeroMedici + 1, strTemp);

			pTotaleColonna[m_lNumeroMedici] += lTotaleRiga;
		}

		for (int i = 0; i < m_lNumeroMedici + 1; i++)
		{
			CString strTemp;
			strTemp.Format("%li", pTotaleColonna[i]);
			m_ctrlList.SetItemText(m_lNumeroEsami + 1, i + 1, strTemp);
		}

		delete pTotaleColonna;
	}

	for (int h = 0; h<m_ctrlList.GetHeaderCtrl()->GetItemCount(); h++)
		m_ctrlList.SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CStatisticheEsamiDlg::AggiungiEsame(long lData, long lIDEsame, long lIDMedico)
{
	long lMese = CCustomDate(lData).GetMonth() - 1;
	if ((lMese >= 0) && (lMese <= 11))
	{
		long lIndexEsame = -1;
		for(int i = 0; i < m_lNumeroEsami; i++)
		{
			if (m_pArrayEsami[i] == lIDEsame)
			{
				lIndexEsame = i;
				break;
			}
		}

		long lIndexMedico = -1;
		for(int i = 0; i < m_lNumeroMedici; i++)
		{
			if (m_pArrayMedici[i] == lIDMedico)
			{
				lIndexMedico = i;
				break;
			}
		}

		if ((lIndexEsame >= 0) && (lIndexMedico >= 0))
		{
			int nArrayPosition = (lMese * m_lNumeroEsami * m_lNumeroMedici) + (lIndexEsame * m_lNumeroMedici) + lIndexMedico;
			m_pNumeriTridimensionale[nArrayPosition]++;
		}
	}
}

long CStatisticheEsamiDlg::GetValoreCella(long lMese, long lEsame, long lMedico)
{
	long lReturn = 0;

	if (lMese < 0)
	{
		// statistica annuale quindi faccio la somma di tutti i mesi //

		for(int i = 0; i < 12; i++)
			lReturn += GetValoreCella(i, lEsame, lMedico);
	}
	else
	{
		int nArrayPosition = (lMese * m_lNumeroEsami * m_lNumeroMedici) + (lEsame * m_lNumeroMedici) + lMedico;
		lReturn = m_pNumeriTridimensionale[nArrayPosition];
	}

	return lReturn;
}

void CStatisticheEsamiDlg::OnBnClickedExport()
{
	CString temp;

	CString strFileExport;
	CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, "File Microsoft Excel (*.xlsx)|*.xlsx|Tutti i file|*.*|", this, 0, FALSE);
	if (FileDlg.DoModal() == IDOK)
	{
		BeginWaitCursor();

		CExportWaitDlg dlgWait(m_ctrlTab.GetItemCount(), this);
		dlgWait.Create(IDD_EXPORT_WAIT, this);
		dlgWait.ShowWindow(SW_SHOW);

		strFileExport = FileDlg.GetPathName();

		if (strFileExport.Right(5).CompareNoCase(".xlsx") != 0)
			strFileExport += ".xlsx";

		//		

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

		if (SUCCEEDED(m_pxmlDocument.CreateInstance(__uuidof(MSXML2::DOMDocument60))))
		{
			m_pxmlDocument->async = VARIANT_FALSE;
			m_pxmlDocument->preserveWhiteSpace = VARIANT_TRUE;
		}

		//

		CString rootTag = "<Excel></Excel>";
		BSTR bstr = rootTag.AllocSysString();
		if (m_pxmlDocument->loadXML(bstr) == VARIANT_FALSE)
		{
			theApp.AfxMessageBoxEndo("Error creating xml document");
			::SysFreeString(bstr);
			return;
		}
		::SysFreeString(bstr);

		//Get the root element just created    
		MSXML2::IXMLDOMElementPtr pXMLRootElem = m_pxmlDocument->GetdocumentElement();

		MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =
			m_pxmlDocument->createProcessingInstruction("xml", " version='1.0' encoding='UTF-8'");

		//Attacco l'elemento root
		_variant_t vtObject;
		vtObject.vt = VT_DISPATCH;
		vtObject.pdispVal = pXMLRootElem;
		vtObject.pdispVal->AddRef();
		m_pxmlDocument->insertBefore(pXMLProcessingNode, vtObject);


		//tag Path
		MSXML2::IXMLDOMElementPtr pXMLChildPath;
		CXmlUtils::AddNode(pXMLChildPath, m_pxmlDocument, pXMLRootElem, "Path", strFileExport);

		//tag SheetList
		MSXML2::IXMLDOMElementPtr pXMLChildSheetList;
		CXmlUtils::AddNode(pXMLChildSheetList, m_pxmlDocument, pXMLRootElem, "SheetList");

		for (int mese = 0; mese < m_ctrlTab.GetItemCount(); mese++)
		{

			//tag SheetList->Sheet
			MSXML2::IXMLDOMElementPtr pXMLChildSheet;
			CXmlUtils::AddNode(pXMLChildSheet, m_pxmlDocument, pXMLChildSheetList, "Sheet");

			CString name = "";
			switch (mese)
			{
				case 0:
					name = theApp.GetMessageString(IDS_TOTALE);
					break;
				case 1:
					name = theApp.GetMessageString(IDS_JANUARY);
					break;
				case 2:
					name = theApp.GetMessageString(IDS_FEBRUARY);
					break;
				case 3:
					name = theApp.GetMessageString(IDS_MARCH);
					break;
				case 4:
					name = theApp.GetMessageString(IDS_APRIL);
					break;
				case 5:
					name = theApp.GetMessageString(IDS_MAY);
					break;
				case 6:
					name = theApp.GetMessageString(IDS_JUNE);
					break;
				case 7:
					name = theApp.GetMessageString(IDS_JULY);
					break;
				case 8:
					name = theApp.GetMessageString(IDS_AUGUST);
					break;
				case 9:
					name = theApp.GetMessageString(IDS_SEPTEMBER);
					break;
				case 10:
					name = theApp.GetMessageString(IDS_OCTOBER);
					break;
				case 11:
					name = theApp.GetMessageString(IDS_NOVEMBER);
					break;
				case 12:
					name = theApp.GetMessageString(IDS_DECEMBER);
					break;
				default:
					name = "";
					break;
			}

			//tag SheetList->Sheet->Name
			MSXML2::IXMLDOMElementPtr pXMLChildName;
			CXmlUtils::AddNode(pXMLChildName, m_pxmlDocument, pXMLChildSheet, "Name", name);

			//tag SheetList->Sheet->CellList
			MSXML2::IXMLDOMElementPtr pXMLChildCellList;
			CXmlUtils::AddNode(pXMLChildCellList, m_pxmlDocument, pXMLChildSheet, "CellList");

			//Procedo con le celle
			long* pTotaleColonna = new long[m_lNumeroMedici + 1];
			for (int i = 0; i < m_lNumeroMedici + 1; i++)
				pTotaleColonna[i] = 0;

			for (int row = 0; row < m_lNumeroEsami; row++)
			{

				AddCell(m_pxmlDocument, pXMLChildCellList, row + 2, 1, CTipoEsameSet().GetDescrizione(m_pArrayEsami[row]), TRUE);

				long lTotaleRiga = 0;
				for (int col = 0; col < m_lNumeroMedici; col++)
				{
					if (row == 0)					
						AddCell(m_pxmlDocument, pXMLChildCellList, 1, col + 2, CMediciSet().GetCognomeNomeFromContatore(m_pArrayMedici[col]), TRUE);

					long lTemp = GetValoreCella(mese - 1, row, col);
					temp.Format("%li", lTemp);
					AddCell(m_pxmlDocument, pXMLChildCellList, row + 2, col + 2, temp, FALSE);

					lTotaleRiga += lTemp;
					pTotaleColonna[col] += lTemp;
				}

				if (row == 0)				
					AddCell(m_pxmlDocument, pXMLChildCellList, 1, m_lNumeroMedici + 2, theApp.GetMessageString(IDS_TOTALE), TRUE);

				temp.Format("%li", lTotaleRiga);
				AddCell(m_pxmlDocument, pXMLChildCellList, row + 2, m_lNumeroMedici + 2, temp, TRUE);

				pTotaleColonna[m_lNumeroMedici] += lTotaleRiga;

			}

			AddCell(m_pxmlDocument, pXMLChildCellList, m_lNumeroEsami + 2, 1, theApp.GetMessageString(IDS_TOTALE), TRUE);

			for (int col = 0; col < m_lNumeroMedici; col++)
			{
				temp.Format("%li", pTotaleColonna[col]);
				AddCell(m_pxmlDocument, pXMLChildCellList, m_lNumeroEsami + 2, col + 2, temp, TRUE);
			}

			temp.Format("%li", pTotaleColonna[m_lNumeroMedici]);
			AddCell(m_pxmlDocument, pXMLChildCellList, m_lNumeroEsami + 2, m_lNumeroMedici + 2, temp, TRUE);

			dlgWait.m_ctrlProgress.SetPos(mese);
			dlgWait.RedrawWindow();

			delete(pTotaleColonna);
		}

		//

		//By default it is writing the encoding = UTF-16. Let us change the encoding to UTF-8
		MSXML2::IXMLDOMNodePtr pXMLFirstChild = m_pxmlDocument->GetfirstChild();
		// A map of the a attributes (vesrsion, encoding) values (1.0, UTF-8) pair
		MSXML2::IXMLDOMNamedNodeMapPtr pXMLAttributeMap = pXMLFirstChild->Getattributes();
		MSXML2::IXMLDOMNodePtr pXMLEncodNode = pXMLAttributeMap->getNamedItem(_T("encoding"));
		pXMLEncodNode->PutnodeValue(_T("UTF-8"));    //encoding = UTF-8
		
		CString ret;
		if (!CreateExcel(CXmlUtils::GetXml(m_pxmlDocument), ret))
			theApp.AfxMessageBoxEndo(ret);		

		//		

		//

		dlgWait.DestroyWindow();

		ShellExecute(NULL, "open", strFileExport, NULL, NULL, SW_SHOWMAXIMIZED);
	}

	if (m_pxmlDocument != NULL)
		m_pxmlDocument.Release();

	EndWaitCursor();	
}

BOOL CStatisticheEsamiDlg::CreateExcel(CString message, CString &ret)
{
	ret = "";
	CString strOutXml = "";

	DWORD dwError = 0, dwExitCode = 0;
	BOOL bResult = FALSE;

	char szModuleName[MAX_PATH];
	GetModuleFileName(NULL, szModuleName, sizeof(szModuleName));

	CString sDirProg = szModuleName;
	int nTemp = sDirProg.ReverseFind('\\');

	CString sFileConfig = sDirProg.Left(nTemp) + "\\ExcelCreator.exe";

	TCHAR szProcess[1024];
	sprintf_s(szProcess, sFileConfig);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	CString str = message;
	DWORD iBufferPSLength = (DWORD)strlen(str);
	CHAR* pBufferPS = (CHAR*)str.GetBuffer(1024*1024);
	str.ReleaseBuffer();

	UINT iOutSize = strlen(pBufferPS);

	HANDLE hChildStdinRd, hChildStdinWr;
	if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &sa, iOutSize + 1))
	{
		ret = "CreatePipe 1 error";
		return FALSE;
	}

	HANDLE hChildStdoutRd, hChildStdoutWr;
	if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 10000000))
	{
		ret = "CreatePipe 2 error";
		return FALSE;
	}

	DWORD dwWritten;
	if (!::WriteFile(hChildStdinWr,
		(BYTE*)pBufferPS,
		iOutSize,
		&dwWritten,
		NULL))
	{
		TCHAR szBuffer[MAX_PATH];
		sprintf_s(szBuffer, "WriteFile 1 error %li", GetLastError());
		ret = szBuffer;
		return FALSE;
	}

	CloseHandle(hChildStdinWr);

	//delete(pBufferPS);

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hChildStdinRd;
	si.hStdOutput = hChildStdoutWr;
	si.hStdError = NULL;

	DWORD iBufferPDFLength = 1024 * 1024;

	//AllocConsole();

	// Start the child process. 
	if (CreateProcess(NULL,
		szProcess,
		NULL,
		NULL,
		TRUE,
		CREATE_NO_WINDOW,
		NULL,
		NULL,
		&si,
		&pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);

		if (GetExitCodeProcess(pi.hProcess, &dwExitCode) && dwExitCode == 0)
		{
			DWORD dwTotalBytes = 0, dwReaded;
			if (PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &dwTotalBytes, NULL) && dwTotalBytes > 0)
			{
				if (dwTotalBytes <= iBufferPDFLength)
				{
					CHAR* pBufferTemp = new CHAR[iBufferPDFLength];
					ZeroMemory(pBufferTemp, sizeof(CHAR)*iBufferPDFLength);
					if (::ReadFile(hChildStdoutRd, pBufferTemp, dwTotalBytes, &dwReaded, NULL))
					{						
						strOutXml.Format("%s", (LPCTSTR)pBufferTemp);

						if (strOutXml == "")
							bResult = TRUE;
					}
					else
					{
						ret = "RTead file error";
						return FALSE;
					}

					delete pBufferTemp;
				}
				else
				{
					ret = "RTead2 file error";
					return FALSE;
				}
			}
			else
			{
				ret = "PeekNamedPipe error";
				return FALSE;
			}
		}
		else
		{
			TCHAR szError[255];
			sprintf_s(szError, "ExitCodeProcess %li", dwExitCode);
			ret = szError;
			return FALSE;
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	else
	{
		ret = "CreateProcess error";
		return FALSE;
	}

	CloseHandle(hChildStdinRd);
	CloseHandle(hChildStdoutRd);
	CloseHandle(hChildStdoutWr);

	if (strOutXml != "")
	{
		ret = strOutXml;
		return TRUE;
	}
	else
	{
		ret = "Error getting empty response";
		return FALSE;
	}
}

void CStatisticheEsamiDlg::AddCell(MSXML2::IXMLDOMDocument3Ptr pxmlDocument, MSXML2::IXMLDOMElementPtr pParent, long rowIndex, long colIndex, CString value, BOOL bold)
{
	CString temp;

	//tag SheetList->Sheet->CellList->Cell
	MSXML2::IXMLDOMElementPtr pXMLChildCell;
	CXmlUtils::AddNode(pXMLChildCell, pxmlDocument, pParent, "Cell");

	//tag SheetList->Sheet->CellList->Cell->RowIndex
	MSXML2::IXMLDOMElementPtr pXMLChildRowIndex;
	temp.Format("%li", rowIndex);
	CXmlUtils::AddNode(pXMLChildRowIndex, pxmlDocument, pXMLChildCell, "RowIndex", temp);

	//tag SheetList->Sheet->CellList->Cell->ColIndex
	MSXML2::IXMLDOMElementPtr pXMLChildColIndex;
	temp.Format("%li", colIndex);
	CXmlUtils::AddNode(pXMLChildColIndex, pxmlDocument, pXMLChildCell, "ColIndex", temp);

	//tag SheetList->Sheet->CellList->Cell->Value
	MSXML2::IXMLDOMElementPtr pXMLChildValue;
	CXmlUtils::AddNode(pXMLChildValue, pxmlDocument, pXMLChildCell, "Value", value);

	//tag SheetList->Sheet->CellList->Cell->Bold
	MSXML2::IXMLDOMElementPtr pXMLChildBold;	
	CXmlUtils::AddNode(pXMLChildBold, pxmlDocument, pXMLChildCell, "Bold", (bold == TRUE ? "true" : "false"));
	
}