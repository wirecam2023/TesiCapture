#ifndef _BASETREEOBJECT_H_
	#define _BASETREEOBJECT_H_

#include <afx.h>

class CBitmap;

class CBaseTreeObject : public CObject
{

public:

	CBaseTreeObject();


	CBitmap*	bitmapToShow;	// Array monodimensionale di bitmap
	CString		strToShow;		// Stringa usata per la visualizzazione sul LB
	int			figli;			// MSB: 1 = sottoalbero espanso
								// MSB: 0 = sottoalbero compresso
								// LSB: 1 = ci sono sottoalberi
								// LSB: 0 = non ci sono sottoalberi
	int			livello;		// 0 = root, ...
	int			larghezza;		// rappresenta la larghezza della stringa
};

#endif /* _BASETREEOBJECT_H_ */