// ComboBoxExt.cpp : implementation file
// Marvel BUG 4094 - Combo Checklists filtradas deve ser vazio por default
//

#include "stdafx.h"
#include "ComboBoxExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt
BEGIN_MESSAGE_MAP(CComboBoxExt, CComboBox)
	ON_WM_PAINT()
END_MESSAGE_MAP()
// CComboBoxExt message handlers
/////////////////////////////////////////////////////////////////////////////

CComboBoxExt::CComboBoxExt():CComboBox(){}
CComboBoxExt::~CComboBoxExt(){}

// Marvel BUG 4094 - Combo Checklists filtradas deve ser vazio por default
void CComboBoxExt::OnPaint()
{
	// não precisou pq o form/dialogo já gerencia o caso de haver apenas uma opção no combobox
	//int x = this->GetCount();
	//int y = this->GetCurSel();

	// If combo has only one item... choose it
	//bool bHasOnlyOneItem = this->GetCount() == 1;
	//if (bHasOnlyOneItem){
	//	this->SetCurSel(0);
	//}

	CComboBox::OnPaint(); // Call the Base Class implementation

	// If nothing selected ... draw a RED BOX box around the component
	bool bNothingSelected = this->GetCurSel()==0;

	CDC* pDC = GetWindowDC();

	//work out the coordinates of the window rectangle,
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);

	//Draw a single line around the outside
	CBrush brush((bNothingSelected ? RGB(255, 0, 0) : RGB(0, 0, 0))); // RED or BLACK
	pDC->FrameRect(&rect, &brush);
	ReleaseDC(pDC);
}
