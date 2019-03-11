#include "pch.h"
#include "ponto.h"


ponto::ponto()
{
	coordenada = new double[2];
}


ponto::~ponto()
{
	delete[]coordenada;
}
