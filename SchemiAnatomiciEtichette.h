// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
#ifndef _SchemiAnatomiciEtichette_H_
#define _SchemiAnatomiciEtichette_H_

class CSchemiAnatomiciEtichette
{
public:
	CSchemiAnatomiciEtichette();
	~CSchemiAnatomiciEtichette();

private:
	long m_lID; // da label - PK da tabela schemi_anatomici_etichette
	long m_lID_Schemi_Anatomici; // FK: ID na tabela Schemi_Anatomici
	CString	m_sDescrizione; // descrição suscinta da label
	long m_lPunto_Alto_Sinistra_X; // x do ponto superior esquerdo do retangulo
	long m_lPunto_Alto_Sinistra_Y; // y do ponto superior esquerdo do retangulo
	long m_lPunto_Basso_Destra_X; // x do ponto inferior direito do retangulo
	long m_lPunto_Basso_Destra_Y; // y do ponto inferior direito do retangulo
	long m_lColore;
	double	m_dZoom_Factor;
	BOOL m_bEliminato; // bool deleted or not na tabela schemi_anatomici_etichette
	

	friend class CSchemiAnatomiciEtichetteSet;
	friend class CSchemiAnatomiciRecordDlg;
	friend class CSchemiAnatomiciEditDlg;
};

// -------------------------------------------------------------------------------------
// NÃO ESTÁ SENDO USADO
// -------------------------------------------------------------------------------------
class CSchemiAnatomiciEtichetteAggiunto : CSchemiAnatomiciEtichette
{
public:
	CSchemiAnatomiciEtichetteAggiunto();
	~CSchemiAnatomiciEtichetteAggiunto();

private:
	long m_lContatore; // CONTATORE da inclusao - PK: na tabela schemi_anatomici_aggiunto_posizione_di_etichette
	//long m_lOrdine; // número sequencial para ordenar se necessário
	long m_lPunto_Alto_Sinistra_X; // x do ponto de inclusao superior esquerdo do retangulo
	long m_lPunto_Alto_Sinistra_Y; // y do ponto de inclusao superior esquerdo do retangulo
	BOOL m_bEliminato; // bool deleted or not na tabela schemi_anatomici_aggiunto_posizione_di_etichette
};

#endif