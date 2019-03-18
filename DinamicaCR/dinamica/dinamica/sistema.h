#pragma once
#include <vector>
#include "corporigido.h"
#include "campo.h"


class sistema
{
public:
	vector <corporigido*> corpo;  
	campo** mapa;

	double L, H, dx,dt, Kn, Cn;

	sistema(double L, double H, double Kn, double Cn);
	~sistema();

	void setdx(double e);
	void integracao();
	int* mapeamento(double x, double y);
	double contato();
	void setmapa();

};



