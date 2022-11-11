#include "stdafx.h"
#include "Endox.h"
#include "FrasiTreeListBox.h"

#include "FrasiTreeObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CFrasiTreeListBox, CBaseTreeListBox)

CFrasiTreeListBox::CFrasiTreeListBox() 
	: CBaseTreeListBox()
{
	m_strSeparatorDesc  = " ";
	m_strSeparatorCode  = " ";
	m_lFamily = 0;
}

CFrasiTreeListBox::~CFrasiTreeListBox()
{
}

BEGIN_MESSAGE_MAP(CFrasiTreeListBox, CBaseTreeListBox)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CFrasiTreeListBox::PrepareDataToShow(CBaseTreeObject* pData)
{
	if (!pData)
		return FALSE;

	CFrasiTreeObject* pRealData = (CFrasiTreeObject* ) pData;

	pRealData->strToShow = "";

	for(int i = 0; i < pRealData->livello  ; i++)
	{
		pRealData->strToShow += "\t";
	}
    
	// Verifica stato "LSB = figli/no figli" e "MSB = espanso/compresso"
	if ((pRealData->figli & 0x0001) == 0x0000)
	{	// Non ha figli
		
		pRealData->strToShow += "\t";	
	
	}
	else
	{
		if (((pRealData->figli & 0x8000) == 0x0000))
		 {		// É compresso quindi usa il bitmap "espandi"
						
			pRealData->strToShow += "[+]\t";
		 }
		else 
	     {	// É espanso quindi usa il bitmap "comprimi"
			
			pRealData->strToShow += "[-]\t";
	     }
	}

//	if (m_lFamily > 0) // Sandro 14/05/2003
		pRealData->strToShow += pRealData->titolo;
//	else
//		pRealData->strToShow += pRealData->descrizione;
	
	return TRUE;
}

BOOL CFrasiTreeListBox::IsValidLevel(CBaseTreeObject* pData)
{
	return TRUE;
}

CString CFrasiTreeListBox::GetLevelStr(CBaseTreeObject* pData)
{
	CString lost = ((CFrasiTreeObject*) pData)->descrizione;
	
	return lost;
}

CString CFrasiTreeListBox::GetDescritionStr(CBaseTreeObject* pData)
{
	CString lost = ((CFrasiTreeObject*) pData)->descrizione;
	
	return lost;
}

CString CFrasiTreeListBox::GetCurDataPathSel()
{
	CString	PathStr = "";
	int		posiz	= GetCurSel();	// CListBox::
//    int		curLev	= 0;

	if (posiz == LB_ERR)
	{
		theApp.AfxMessageBoxEndo("Errore di GetCurSel() in\nint CFrasiTreeListBox::GetCurDataPathSel()");
		return "";
	}

    CBaseTreeObject* pData = GetTreeItemDataPtr(posiz);

	if (!pData)
	{
		theApp.AfxMessageBoxEndo("Errore di GetTreeItemDataPtr() (1) in\nint CFrasiTreeListBox::GetCurDataPathSel()");
		return "";
	}

	if (m_lFamily == 0)
	{
		//frasi standard
		////////////////////////////////////////////////////////////////
		int	curLev = pData->livello;
		
		for(int i = curLev; i > 0; i--)
		{
			if (IsValidLevel(pData))
			{
				CString strCod = GetLevelStr(pData);
				
				if (strCod != "")
				{
					if (PathStr == "")
						PathStr = strCod;
					else
						PathStr = strCod + m_strSeparatorCode + PathStr;
				}
			}
			
			while (curLev <= pData->livello && posiz > 0)
			{
				pData = GetTreeItemDataPtr(--posiz);
				
				if (!pData)
				{
					theApp.AfxMessageBoxEndo("Errore di GetTreeItemDataPtr() (2) in\nint CFrasiTreeListBox::GetCurDataPathSel()");
					return "";
				}
			}
			curLev = pData->livello;
		}
	}
	else
	{
		//Risposte standard / Patologie standard / Consensi informativi
		////////////////////////////////////////////////////////////////
		PathStr = GetLevelStr(pData);
	}
	
	return PathStr;
}

int CFrasiTreeListBox::AddTreeItem(CFrasiTreeObject* pData)
{
	// calcola la lunghezza della stringa
	//CClientDC	CCDC(FromHandle(GetSafeHwnd()));
	CClientDC	CCDC(this);

	CString strDummy = "";

	for(int i = 0; i < pData->livello ; i++)
	{
		strDummy += "\t";
	}
    
	// Verifica stato "LSB = figli/no figli"
	if ((pData->figli & 0x0001) == 0x0000)
	{	// Non ha figli
		strDummy += "\t";	
	}
	else
	{
		strDummy += "[+]\t";
	}

	if (m_lFamily > 0)
		strDummy += pData->titolo;
	else
		strDummy += pData->descrizione;

	CSize sizeStr = CCDC.GetOutputTabbedTextExtent(strDummy, strDummy.GetLength(), 0 , NULL);

	CCDC.LPtoDP(&sizeStr);

	SetHorizontalExtent(sizeStr.cx);

	pData->larghezza = sizeStr.cx;

	return CBaseTreeListBox::AddTreeItem((CBaseTreeObject*) pData);
}

int	CFrasiTreeListBox::InsTreeItem(int nIndex, CFrasiTreeObject* pData)
{
	// calcola la lunghezza della stringa
	//CClientDC	CCDC(FromHandle(GetSafeHwnd()));
	CClientDC	CCDC(this);

	CString strDummy = "";

	for(int i = 0; i < pData->livello  ; i++)
	{
		strDummy += "\t";
	}
    
	// Verifica stato "LSB = figli/no figli"
	if ((pData->figli & 0x0001) == 0x0000)
	{	// Non ha figli
		strDummy += "\t";	
	}
	else
	{
		strDummy += "[+]\t";
	}

	if (m_lFamily > 0)
		strDummy += pData->titolo;
	else
		strDummy += pData->descrizione;

	CSize sizeStr = CCDC.GetOutputTabbedTextExtent(strDummy, strDummy.GetLength(), 0 , NULL);

	CCDC.LPtoDP(&sizeStr);

	SetHorizontalExtent(sizeStr.cx);

	pData->larghezza = sizeStr.cx;

	return CBaseTreeListBox::InsTreeItem(nIndex, (CBaseTreeObject*) pData);
}


int	CFrasiTreeListBox::DelTreeItem(int nIndex)
{
	DWORD	info = GetItemData(nIndex);
	int		counter;
		
	if (info == LB_ERR)
	{
		theApp.AfxMessageBoxEndo("Errore di ClistBox::GetItemData in\nint CCodPatologiaTreeListBox::DeleteTreeItem");
		return -1;
	}

	if (info)
		delete (CFrasiTreeObject*) info;
		
	counter = DeleteString(nIndex);
		
	if (counter == LB_ERR)
	{
		theApp.AfxMessageBoxEndo("Errore (LB_ERR) di ClistBox::DeleteString in\nint CCodPatologiaTreeListBox::DeleteTreeItem");
		return -1;
	}

	AdjustHScrollBar();
	
	return counter;
}

CString CFrasiTreeListBox::GetCurDataDescr()
{
	int					posiz =	GetCurSel();
    CFrasiTreeObject*	pData;
	CString				PathStr;

	if (posiz == LB_ERR)
		return "";

    pData = (CFrasiTreeObject*)GetTreeItemDataPtr(posiz);

	if (!pData)
		return "";
	
	return pData->descrizione;
}

CString CFrasiTreeListBox::GetCurDataTitle()
{
	int					posiz =	GetCurSel();
    CFrasiTreeObject*	pData;
	CString				PathStr;

	if (posiz == LB_ERR)
		return "";

    pData = (CFrasiTreeObject*)GetTreeItemDataPtr(posiz);

	if (!pData)
		return "";
	
	return pData->titolo;
}

int CFrasiTreeListBox::GetCurDataFlag()
{
	int					posiz =	GetCurSel();
    CFrasiTreeObject*	pData;
	CString				PathStr;

	if (posiz == LB_ERR)
		return -1;

    pData = (CFrasiTreeObject*)GetTreeItemDataPtr(posiz);

	if (!pData)
		return -1;
	
	return pData->flag;
}

/////////////////////////////////////////////////////////////////////////////
// CFrasiTreeListBox	message handlers

void CFrasiTreeListBox::OnDestroy()
{
	int counter = GetCount();	// ClistBox::
	
	if (counter == LB_ERR)
	{
		theApp.AfxMessageBoxEndo("Errore di GetCount in\nint CFrasiTreeListBox::OnDestroy()");
		return;
	}

	while(counter)
	{
		DWORD info = GetItemData(counter - 1);	// ClistBox::
		
		if (info == LB_ERR)
		{
			theApp.AfxMessageBoxEndo("Errore di GetItemData in\nint CFrasiTreeListBox::OnDestroy()");
			return;
		}

		delete (CFrasiTreeObject*) info;

		counter = DeleteString(counter - 1);	// ClistBox::
		
		if (counter == LB_ERR)
		{
			theApp.AfxMessageBoxEndo("Errore di DeleteString in\nint CBaseTreeListBox::OnDestroy()");
			return;
		}
	}	

	CBaseTreeListBox::OnDestroy();
}