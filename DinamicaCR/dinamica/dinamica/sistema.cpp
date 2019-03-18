#include "pch.h"
#include "sistema.h"
#include "campo.h"
#include "contato.h"
#include "id.h"
#include <math.h>
#include <iostream>
sistema::sistema(double L, double H, double Kn, double Cn)
{
	this->L = L;
	this->H = H;
	this->Kn = Kn;
	this->Cn = Cn;

}


sistema::~sistema()
{
	delete[] mapa;
}

void sistema::setdx(double e)
{
	double massamax = 0;

	for (int i = 0; i < corpo.size(); i++)
	{
		if (corpo[i]->massa > massamax)
		{
			massamax = corpo[i]->massa;
		}
	}

	double tc = 2 * sqrt(massamax / Kn);    //tempo critico
	dt = tc * e;

	dx = 0; //raio maximo

	for (int i = 0; i < corpo.size(); i++)
	{
		for (int j = 0; j < corpo[i]->segmento.size(); j++)
		{
			if (dx < corpo[i]->segmento[j]->raio)
			{
				dx = corpo[i]->segmento[j]->raio;
			}	
		}
	}
}


void sistema::integracao()
{
	double x, y;
	for (int i = 0; i < corpo.size(); i++)
	{
		


		//Rotação

		for (int j = 0; j < corpo[i]->posicao.size[0]; j++)
		{

			//x1=x0*cos(dteta)-y0*sin(dteta)
			//y1=y0*cos(dteta)+x0*sin(dteta)

			corpo[i]->posicao.M[j][0] = corpo[i]->posicao.M[j][0] * cos(corpo[i]->W*dt)- corpo[i]->posicao.M[j][1]*sin(corpo[i]->W*dt)+ corpo[i]->velocidade.V[0]*dt;
			corpo[i]->posicao.M[j][1] = corpo[i]->posicao.M[j][1] * cos(corpo[i]->W*dt) + corpo[i]->posicao.M[j][0] * sin(corpo[i]->W*dt)+corpo[i]->velocidade.V[1]*dt;

			for (int k = 0; k < corpo[i]->Ned; k++)
			{
				x = corpo[i]->segmento[j]->elemento[k]->centro[0];
				y = corpo[i]->segmento[j]->elemento[k]->centro[1];

				corpo[i]->segmento[j]->elemento[k]->centro[0] = x * cos(corpo[i]->W*dt) - y * sin(corpo[i]->W*dt)+corpo[i]->velocidade.V[0]*dt;
				corpo[i]->segmento[j]->elemento[k]->centro[1] = y * cos(corpo[i]->W*dt) + x * sin(corpo[i]->W*dt) + corpo[i]->velocidade.V[1]*dt;


			}


		}

		//Translacao
		corpo[i]->CM = corpo[i]->velocidade*dt + corpo[i]->CM;

		corpo[i]->velocidade = (corpo[i]->Fcont + corpo[i]->Fext)*(dt / corpo[i]->massa) + corpo[i]->velocidade;
		corpo[i]->W = corpo[i]->torque*(dt / corpo[i]->I) + corpo[i]->W;



		corpo[i]->Fcont.zeros();
		corpo[i]->torque = 0;
	}
}

int* sistema::mapeamento(double x, double y)
{
	int* C = new int(2);
	C[0] = floor(x / dx);
	C[1] = floor(y / dx);

	return C;
}


void sistema::setmapa()
{
	int N = ceil(L / dx);
	int M = ceil(H / dx);
	int* C = new int(2);
	int a, b;
	id ID;

	mapa = new campo*[N];
	for (int i = 0; i < N; i++)
	{
		mapa[i] = new campo[M];
	}

	for (int i = 0; i < corpo.size(); i++)
	{
		for (int j = 0; j < corpo[i]->posicao.size[0]; j++)
		{
			for (int k = 0; k < corpo[i]->Ned; k++)
			{
				C = mapeamento(corpo[i]->segmento[j]->elemento[k]->centro[0], corpo[i]->segmento[j]->elemento[k]->centro[1]);
				ID.c = i;
				ID.s = j;
				ID.n = k;
				mapa[C[0]][C[1]].idelement.push_back(ID);
			}

		}
	}

}