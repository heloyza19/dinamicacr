#pragma once
#include <vector>
#include "corporigido.h"
#include "campo.h"


class sistema
{
public:
	vector <corporigido*> corpo;  
	campo** mapa;

	double L, H, dx,dt, Kn, Cn, times;
	double e;
	sistema();
	~sistema();

	void setdx();
	void integracao();
	int* mapeamento(double x, double y);
	double contato();
	void setmapa();

};



