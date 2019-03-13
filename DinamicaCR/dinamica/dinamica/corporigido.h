#pragma once
#include "matriz.h"
#include "aresta.h"
class corporigido
{
private:
	double momentodeinercia(matriz* massa_esp, int  nx, int ny, double dx, double dy, vetor CM, double xo, double yo);
	double densidade(matriz* massa_esp, matriz posicao, int  nx, int ny, double dx, double dy, double xo, double yo);
	int pontointerno(double pos_x, double pos_y, matriz posicao);
public:
	

	matriz posicao;
	vetor velocidade;
	vetor Fext;
	vetor Fcont;
	vetor CM;

	double I;
	double massa;
	double W;
	double torque;
	int Ned;

	vector <aresta*> segmento;

	corporigido (int np,double** pos, double* vel, double* F);
	~corporigido();

	void centrodemassa();
	void setsegmento(int Ned);

};

