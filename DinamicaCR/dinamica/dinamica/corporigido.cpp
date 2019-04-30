#include "pch.h"

#include "centrodemassa.h"


corporigido::corporigido(int np, double** pos, double* vel, double* F, double W, double d) : Fext(2), Fcont(2), velocidade(2), CM(2), posicao(np, 2)
{
	this->W = W;
	this->d = d;
	posicao.setM(pos);
	Fext.setV(F);
	velocidade.setV(vel);

	Fcont.zeros();  
	CM.zeros();

	torque = 0;
	I = 0;
	massa = 0;

}


corporigido::~corporigido()
{
}


void corporigido::setsegmento(int Ned)
{
	this->Ned = Ned;
	double L,S;
	int n;

	for (int i = 0; i < posicao.size[0]; i++)
	{
		ponto *pont = new ponto();
		ponto *pont2 = new ponto();
		aresta* segment = new aresta();
			
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

		pont->coordenada[0]= posicao.getM()[i][0];
		pont->coordenada[1] = posicao.getM()[i][1];
		segment->vertice[0]= pont;


		pont2->coordenada[0] = posicao.getM()[n][0];
		pont2->coordenada[1] = posicao.getM()[n][1];
		segment->vertice[1] = pont2;


		for (int j = 0; j < Ned; j++)
		{
			elementodiscreto *elem = new elementodiscreto();
			S = segment->raio + 2 * segment->raio * j;
			elem->centro[0]= ( posicao.getM()[i][0] + (S*((posicao.getM()[n][0] - posicao.getM()[i][0]) / L)));
			elem->centro[1]=( posicao.getM()[i][1] + (S*((posicao.getM()[n][1] - posicao.getM()[i][1]) / L)));
			segment->elemento.push_back(elem);
		}

		segmento.push_back(segment);

	}






}
