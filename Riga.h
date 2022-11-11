#ifndef _RIGA_H_
	#define _RIGA_H_

class CRiga : public CObject
{
	DECLARE_DYNCREATE(CRiga)

public:
	CRiga();

	long	m_nEsame;
	int		m_nPage;
	int		m_nDiapoPerEsame;
};

#endif /* _RIGA_H_ */