#pragma once
#include <vector>
#include "corporigido.h"
#include "campo.h"


class sistema
{
public:
	vector <corporigido*> corpo;  
	campo** mapa;

	double L, H, dx,dt, Kn, Cn, times,ni; //largura, altura, dx do grid, dt, constante da mola, constante de amortecimento, tempo de simulacao, numero de impressoes
	double e; //percentual do tempo critico
	sistema();
	~sistema();

	void setdx();
	void integracao();
	int* mapeamento(double x, double y);
	double contato();
	void setmapa();

};



