#include "pch.h"
#include "aresta.h"


aresta::aresta()
{
	vertice = new ponto*[2]();
}


aresta::~aresta()
{
	delete[]vertice;
}
