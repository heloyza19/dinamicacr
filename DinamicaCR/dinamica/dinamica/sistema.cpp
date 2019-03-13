#include "pch.h"
#include "sistema.h"
#include <math.h>

sistema::sistema(double L, double H, double Kn, double Cn, double dt)
{
	this->L = L;
	this->H = H;
	this->Kn = Kn;
	this->Cn = Cn;
	this->dt = dt;
}


sistema::~sistema()
{
	delete[] mapa;
}

void sistema::setdx()
{
	dx = 0; //raio maximo

	for (int i = 0; i < corpo.size(); i++)
	{
		for (int j = 0; j < corpo[i].segmento.size(); j++)
		{
			if (dx < corpo[i].segmento[j]->raio)
			{
				dx = corpo[i].segmento[j]->raio;
			}	
		}
	}
}


void sistema::integracao()
{

	for (int i = 0; i < corpo.size(); i++)
	{
		//Translacao
		corpo[i].CM = corpo[i].velocidade*dt + corpo[i].CM;
		corpo[i].velocidade = (corpo[i].Fcont + corpo[i].Fext)*(dt / corpo[i].massa) + corpo[i].velocidade;


		//Rotação

		for (int j = 0; j < corpo[i].posicao.size[0]; j++)
		{

			//x1=x0*cos(dteta)-y0*sin(dteta)
			//y1=y0*cos(dteta)+x0*sin(dteta)

			corpo[i].posicao.M[j][0] = corpo[i].posicao.M[j][0] * cos(corpo[i].W*dt)- corpo[i].posicao.M[j][1]*sin(corpo[i].W*dt);
			corpo[i].posicao.M[j][1] = corpo[i].posicao.M[j][1] * cos(corpo[i].W*dt) + corpo[i].posicao.M[j][0] * sin(corpo[i].W*dt);

		}
		corpo[i].W = corpo[i].torque*(dt / corpo[i].I) + corpo[i].W;

		corpo[i].Fcont.zeros();
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

	mapa = new campo*[N];
	for (int i = 0; i < N; i++)
	{
		mapa[N] = new campo[M];
	}

	for (int i = 0; i < corpo.size(); i++)
	{
		for (int j = 0; j < corpo[i].posicao.size[0]; j++)
		{
			for (int k = 0; k < corpo[i].Ned; k++)
			{
				C = mapeamento(corpo[i].segmento[j]->elemento[k]->centro[0], corpo[i].segmento[j]->elemento[k]->centro[1]);
				mapa[C[0]][C[1]].element.push_back(corpo[i].segmento[j]->elemento[k]);
			}

		}
	}

}