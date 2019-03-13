#include "pch.h"
#include "elementodiscreto.h"


elementodiscreto::elementodiscreto()
{
	centro = new double[2];
}


elementodiscreto::~elementodiscreto()
{
	delete[] centro;
}
