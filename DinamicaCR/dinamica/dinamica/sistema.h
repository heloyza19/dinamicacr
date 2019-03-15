#pragma once
#include <vector>
#include "corporigido.h"
#include "campo.h"


class sistema
{
public:
	vector <corporigido> corpo;
	campo** mapa;

	double L, H, dx,dt, Kn, Cn;

	sistema(double L, double H, double Kn, double Cn, double e);
	~sistema();

	void setdx();
	void integracao();
	int* mapeamento(double x, double y);
	void contato();
	void setmapa();

};



