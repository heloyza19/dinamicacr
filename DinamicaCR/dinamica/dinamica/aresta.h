#pragma once
#include "elementodiscreto.h"
#include "ponto.h"
#include <vector>


using namespace std;

class aresta
{
public:

	vector <elementodiscreto*> elemento;       //elementosdiscretos do segmento
	double raio;                              //raio dos elementos discretos
	ponto** vertice;						 //vertices do segmento;
	

	aresta();
	~aresta();
};

