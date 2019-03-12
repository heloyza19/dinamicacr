#include "pch.h"
#include "corporigido.h"
#include "centrodemassa.h"
#include "densidade.h"
#include "pontointerno.h"

corporigido::corporigido(int np, double** pos, double* vel, double* F) : Fext(2), Fcont(2), velocidade(2), CM(2), posicao(np, 2)
{
	posicao.setM(pos);
	Fext.setV(F);
	velocidade.setV(vel);

	Fcont.zeros();
	CM.zeros();
	torque = 0;
	W = 0;
	I = 0;
	massa = 0;

}


corporigido::~corporigido()
{
}


void corporigido::setsegmento(int Ned)
{
	aresta* segment = new aresta();
	elementodiscreto *elem = new elementodiscreto();
	double L,S;
	int n;

	for (int i = 0; i < posicao.size[0]; i++)
	{
	
		aresta* segment = new aresta();
		elementodiscreto *elem = new elementodiscreto();

		if (i == posicao.size[0] - 1)
		{
			n = 0;
		}
		else
		{
			n = i + 1;
		}

		L = sqrt((posicao.getM()[n][0] - posicao.getM()[i][0])*(posicao.getM()[n][0] - posicao.getM()[i][0]) + (posicao.getM()[n][1] - posicao.getM()[i][1]) * (posicao.getM()[n][1] - posicao.getM()[i][1]));
		segment->raio= 0.5*(L / Ned);
		segment->vertice[0][0] = posicao.getM()[i][0];

		for (int j = 0; j < Ned; j++)
		{
			S = segment->raio + 2 * segment->raio * j;
			elem->centro[0]= ( posicao.getM()[i][0] + (S*((posicao.getM()[n][0] - posicao.getM()[i][0]) / L)));
			elem->centro[1]=( posicao.getM()[i][1] + (S*((posicao.getM()[n][1] - posicao.getM()[i][1]) / L)));
		}

	}






}


//L = sqrt((corpo->posicao.getM()[n][0] - corpo->posicao.getM()[i][0])*(corpo->posicao.getM()[n][0] - corpo->posicao.getM()[i][0]) + (corpo->posicao.getM()[n][1] - corpo->posicao.getM()[i][1]) * (corpo->posicao.getM()[n][1] - corpo->posicao.getM()[i][1]));
//Raio[i] = 0.5*(L / Ned);
//
//for (int j = 0; j < Ned; j++)
//{
//	S = Raio[i] + 2 * Raio[i] * j;
//	Xcentro[i][j] = corpo->posicao.getM()[i][0] + (S*((corpo->posicao.getM()[n][0] - corpo->posicao.getM()[i][0]) / L));
//	Ycentro[i][j] = corpo->posicao.getM()[i][1] + (S*((corpo->posicao.getM()[n][1] - corpo->posicao.getM()[i][1]) / L));
//}
//
//	}
//	xcentro.setM(Xcentro);
//	ycentro.setM(Ycentro);
//	raio.setV(Raio);