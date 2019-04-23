#pragma once
#include "sistema.h"
#include <stdio.h>   
#include <stdlib.h>  
#include <string>
#include <iostream>
#include <fstream>


sistema* leituradedados(int argc, char* argv)
{

	ifstream input("dados.txt");
	string label;
	sistema* Dados=new sistema();

	double temp, p,L, H, Kn, Cn;
	int ni;
	if (input.is_open())
	{
		int nc;
		while (1)
		{
			label = "";
			input >> label;
	
			if (label == "#DADOSDOSISTEMA")
			{
				
				input >> Dados->L;
				input >> Dados->H;
				input >> Dados->Kn;
				input >> Dados->Cn;

				
			}
			else if (label == "#DADOSTEMPORAIS")
			{

				input >> Dados->times;
				input >> Dados->e;
			}
			else if (label == "#DADOSDOSCORPOSRIGIDOS")
			{
				input >> nc;
				for (int i = 0; i < nc; i++)
				{
					
					int np;
					input >> np;
					double** pos=new double*[np];

					for (int j = 0; j < np; j++)
					{
						pos[j] = new double[2];
						input >> pos[j][0];
						input >> pos[j][1];
					}

					double densidade;
					input >> densidade;
					double* vel=new double[2];

					input >> vel[0];
					input >> vel[1];

					double w;
					input >> w;
					double ned;
					input >> ned;
					double* F = new double[2];
					input >> F[0];
					input >> F[1];

					corporigido* corpo = new corporigido(np, pos, vel,F,w);
					corpo->centrodemassa();
					corpo->setsegmento(ned);
					Dados->corpo.push_back(corpo);

				}

				
			}
			else if (label == "#IMPRESSAO")
			{

				input >> ni;
			}

			else if (label == "#END")
			{
				break;

			}



		}



		Dados->setdx();
		Dados->setmapa();
		return Dados;

	}

	

}