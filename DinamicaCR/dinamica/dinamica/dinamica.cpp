#include "pch.h"
#include <iostream>
#include "sistema.h"
int main()
{
	int Ncr = 2;			//numero de corpos rigidos
	int Np = 4;            //numero de vertices
	int Ned = 2;	      //numero de elementos discretos

	double times = 0.01;
	double Cn = 0;       //constante de amortecimento
	double Kn = 10000;  //constante da mola
	double L = 7;
	double H = 6.5;

	double** m = new double*[Np];
	double** m2 = new double*[Np];
	double* v = new double[2]{25,0};
	double* v2 = new double[2]{-25,0 };
	double* f = new double[2]{0,0};

	

	for (int i = 0; i < Np; i++)
	{
		m[i] = new double[2];
		m2[i] = new double[2];
	}
	m[0][0] = 2; m[0][1] = 1;
	m[1][0] = 2; m[1][1] = 2;
	m[2][0] = 3; m[2][1] = 2;
	m[3][0] = 3; m[3][1] = 1;

	m2[0][0] =3.5; m2[0][1] = 1;
	m2[1][0] =3.5; m2[1][1] = 2;
	m2[2][0] =4.5; m2[2][1] = 2;
	m2[3][0] =4.5; m2[3][1] = 1;

	corporigido* corpo1 = new corporigido(Np,m,v,f);
	corpo1->velocidade.setV(v);
	corpo1->centrodemassa();
	corpo1->setsegmento(Ned);

	corpo1->posicao.print();
	corpo1->CM.print();
	corpo1->velocidade.print();
	cout <<"massa="<< corpo1->massa << endl;
	cout << "I=" << corpo1->I << endl;
	corporigido* corpo2 = new corporigido(Np, m2, v, f);
	corpo2->velocidade.setV(v2);
	corpo2->centrodemassa();
	corpo2->setsegmento(Ned);
	
	corpo2->posicao.print();
	corpo2->CM.print();
	corpo2->velocidade.print();
	cout << "massa=" << corpo2->massa << endl;
	cout << "I=" << corpo2->I << endl;
	
	double e = 0.05;

	sistema* Dados = new sistema(L,H,Kn,Cn);
	
	Dados->corpo.push_back(corpo1);
	Dados->corpo.push_back(corpo2);
	Dados->setdx(e);
	Dados->setmapa();
	cout << "dx=" << Dados->dx << endl;
	cout <<"dt= "<< Dados->dt << endl;
	cout << "tc" << Dados->dt / e<<endl;

	int temp = ceil(times / Dados->dt);
	double* Eelas = new double[temp];
	double* Ek = new double[temp];
	double* Ekr = new double[temp];

	for (int t=0; t < temp; t++)
	{	
		Ek[t] = 0;
		Ekr[t] = 0;
		Eelas[t]=Dados->contato();
		
		for (int i = 0; i < Dados->corpo.size(); i++)
		{
			Ek[t] +=0.5* Dados->corpo[i]->massa*pow(Dados->corpo[i]->velocidade.norm(),2);
			Ekr[t] += 0.5*Dados->corpo[i]->I*pow(Dados->corpo[i]->W,2);
			
		}
	
		
		Dados->integracao();
		Dados->setmapa();

	
		

	}


	Dados->corpo[0]->posicao.print();

	Dados->corpo[1]->posicao.print();






	return 0;
}


