#include "stdafx.h"
#include "Endox.h"
#include "VistaFleuryURMSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaFleuryURMSet, CBaseSet)

CVistaFleuryURMSet::CVistaFleuryURMSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("VALORI");

	m_lView = 0;
	m_nFields = 1;
}

CString CVistaFleuryURMSet::GetDefaultSQL()
{
	ASSERT((m_lView == VIEW_UNIDADE) || (m_lView == VIEW_REGIONAL) || (m_lView == VIEW_MARCA));

	switch (m_lView)
	{
		case VIEW_UNIDADE:
		{
			return "VISTA_FLEURY_UNIDADE";
		}
		case VIEW_REGIONAL:
		{
			return "VISTA_FLEURY_REGIONAL";
		}
		case VIEW_MARCA:
		{
			return "VISTA_FLEURY_MARCA";
		}
	}

	return "";
}

void CVistaFleuryURMSet::SetEmpty()
{
	m_sValori = "";
}

void CVistaFleuryURMSet::DoFieldExchange(CFieldExchange* pFX)
{
	ASSERT((m_lView == VIEW_UNIDADE) || (m_lView == VIEW_REGIONAL) || (m_lView == VIEW_MARCA));

	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "VALORI", m_sValori, 4000);
}

void CVistaFleuryURMSet::SetView(long lView)
{
	ASSERT((lView == VIEW_UNIDADE) || (lView == VIEW_REGIONAL) || (lView == VIEW_MARCA));

	m_lView = lView;
}
