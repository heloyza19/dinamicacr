#pragma once
#include "pontointerno.h"

double corporigido::densidade(matriz* massa_esp, matriz posicao, int  nx, int ny, double dx, double dy, double xo, double yo)
{
	double m = 0;
	int ni;
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{

			ni = pontointerno(xo + i * dx, yo + j * dy, posicao);

			if (ni % 2 == 0)
			{
				massa_esp->getM()[i][j] = 0;
			}

			m += massa_esp->getM()[i][j];
		}
	}
	m = m * dx*dy;
	return m;

}