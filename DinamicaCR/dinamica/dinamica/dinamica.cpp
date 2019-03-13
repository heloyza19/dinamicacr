#include "pch.h"
#include <iostream>
#include "sistema.h"
int main()
{
	int Ncr = 2;			//numero de corpos rigidos
	int Np = 4;            //numero de vertices
	int Ned = 10;	      //numero de elementos discretos
	double Cn = 0;       //constante de amortecimento
	double Kn = 10000;  //constante da mola
	double L = 10;
	double H = 10;

	double** m = new double*[Np];
	double** m2 = new double*[Np];
	double* v = new double[2]{10,10};
	double* f = new double[2]{0,0};

	

	for (int i = 0; i < Np; i++)
	{
		m[i] = new double[2];
		m2[i] = new double[2];
	}
	m[0][0] = 1; m[0][1] = 1;
	m[1][0] = 1; m[1][1] = 4;
	m[2][0] = 4; m[2][1] = 1;
	m[3][0] = 4; m[3][1] = 4;

	m2[0][0] = 5; m2[0][1] = 4;
	m2[1][0] = 5; m2[1][1] = 6;
	m2[2][0] = 8; m2[2][1] = 4;
	m2[3][0] = 8; m2[3][1] = 6;

	corporigido* corpo1 = new corporigido(Np,m,v,f);
	corpo1->centrodemassa();
	corpo1->setsegmento(Ned);

	corpo1->posicao.print();
	corpo1->CM.print();

	corporigido* corpo2 = new corporigido(Np, m2, v, f);
	corpo2->centrodemassa();
	corpo2->setsegmento(Ned);

	corpo2->posicao.print();
	corpo2->CM.print();







	return 0;
}


