#pragma once

#include "corporigido.h"
#include "densidade.h"
#include "momentodeinercia.h"

void corporigido::centrodemassa()
{
	double dx = 0.01;
	double dy = dx;
	double dA = dx * dy;

	double* cm = new double[2];

	double Mx = 0;       //contador momento em x
	double My = 0;       //contador momento em y

	int nx = ceil((maximo(posicao, 0) + dx - minimo(posicao, 0) + dx) / dx);
	int ny = ceil((maximo(posicao, 1) + dy - minimo(posicao, 1) + dy) / dy);

	matriz *massa_esp = new matriz(nx, ny);      //matriz da massa especifica
	massa_esp->ones();

	massa = densidade(massa_esp, posicao, nx, ny, dx, dy, minimo(posicao, 0) - dx, minimo(posicao, 1) - dy);


	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			My += (minimo(posicao, 0) - dx + i * dx) * massa_esp->getM()[i][j];
		}

	}

	for (int i = 0; i < ny; i++)
	{

		for (int j = 0; j < nx; j++)
		{
			Mx += (minimo(posicao, 1) - dy + i * dy) * massa_esp->getM()[j][i];
		}

	}


	CM.V[0] = dA * (My / massa);
	CM.V[1] = dA * (Mx / massa);

	I = momentodeinercia(massa_esp, nx, ny, dx, dy, CM, minimo(posicao, 0) - dx, minimo(posicao, 1) - dy);


}
