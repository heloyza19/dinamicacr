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

	double	d;		     //densidade
	double I;	        //momento 
	double massa;      //massa
	double W;	      //velocidade angular
	double torque;   //torque
	int Ned;        //numero de elementos discretos 

	vector <aresta*> segmento;

	corporigido (int np,double** pos, double* vel, double* F, double W, double d);
	~corporigido();

	void centrodemassa();
	void setsegmento(int Ned);

};

