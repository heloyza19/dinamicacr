#pragma once
#include "matriz.h"


//

int corporigido:: pontointerno(double pos_x, double pos_y, matriz posicao)
{
	int ni = 0;
	double Xmin = minimo(posicao, 0);
	double Xmax = maximo(posicao, 0);
	double Ymin = minimo(posicao, 1);
	double Ymax = maximo(posicao, 1);
	int n;
	if (pos_x <= Xmax & pos_x >= Xmin & pos_y <= Ymax & pos_y >= Ymin)
	{
		for (int i = 0; i < posicao.getsize()[0]; i++)   //para cada aresta
		{
			
			if (i == posicao.getsize()[0]-1) 
			{
				n = 0;
			}
			else 
			{
				n = i+1;
			}

			if (posicao.getM()[i][1] != posicao.getM()[n][1])  // se y(i) !=Y(i+1), se a reta não for horizontal
			{
				double min_y;
				double max_y;
				if (posicao.getM()[i][1] > posicao.getM()[n][1])
				{
					min_y = posicao.getM()[n][1];
					max_y = posicao.getM()[i][1];
				}
				else
				{
					max_y = posicao.getM()[n][1];
					min_y = posicao.getM()[i][1];
				}

				if (posicao.getM()[i][0] != posicao.getM()[n][0] & posicao.getM()[i][1] > min_y & posicao.getM()[i][1] <= max_y)
				{
					double a = (posicao.getM()[i][1] - posicao.getM()[n][1]) / (posicao.getM()[i][0] - posicao.getM()[n][0]);   //coef angular da reta
					double Xr = posicao.getM()[i][0] + (pos_y - posicao.getM()[i][1]) / a;

					if (pos_x < Xr)
					{

						ni++;

					}
				}
				else if (posicao.getM()[i][0] == posicao.getM()[n][0] & posicao.getM()[i][1] > min_y & posicao.getM()[i][1] <= max_y)
				{
					double Xr = posicao.getM()[i][0];
					if (pos_x < Xr)
					{
						ni++;

					}
				}
			}
		}
		return ni;
	}
}

double minimo(matriz Mat, int c)
{
double minimo = Mat.getM()[0][c];
	for (int i = 1; i < Mat.getsize()[0]; i++)
	{
	if (Mat.getM()[i][c] < minimo)
	{
	minimo = Mat.getM()[i][c];
	}

}


return minimo;
}

double maximo(matriz Mat, int c)
{

		double maximo = Mat.getM()[0][c];


		for (int i = 1; i < Mat.getsize()[0]; i++)
		{
			if (Mat.getM()[i][c] > maximo)
			{
				maximo = Mat.getM()[i][c];
			}

		}


return maximo;
}
