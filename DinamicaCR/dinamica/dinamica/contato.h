#pragma once
#include "sistema.h"

vetor Fnormal(vetor Vnormal, double Cn, double Kn, vetor Vel1, vetor Vel2, double ra, double rb, double d);

void sistema::contato()
{
	double Eelas = 0;
	double torque1x = 0, torque1y = 0;
	double torque2x = 0, torque2y = 0;
	double ang1x, ang1y, ang2x, and2y;
	int Px, Py;
	int* P;

	vetor Vnormal(2);
	vetor Fn(2);
	vetor Fr(2);

	for (int i = 0; i < corpo.size(); i++)
	{
		for (int j = 0; j < corpo[i].posicao.size[0]; j++)
		{
			for (int k = 0; k < corpo[i].Ned; k++)
			{

				if (corpo[i].segmento[j]->elemento[k]->centro[0]<= corpo[i].segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = 1;
					Vnormal.V[1] = 0;
					
					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i].velocidade, Vel2, corpo[i].segmento[j]->raio, 0, corpo[i].segmento[j]->elemento[k]->centro[0]);
					Fr = corpo[i].Fcont + Fn;
					corpo[i].Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow(corpo[i].segmento[j]->raio - corpo[i].segmento[j]->elemento[k]->centro[0], 2);
	
				}


				else if (corpo[i].segmento[j]->elemento[k]->centro[0] >= L- corpo[i].segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = -1;
					Vnormal.V[1] = 0;

					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i].velocidade, Vel2, corpo[i].segmento[j]->raio, 0,L- corpo[i].segmento[j]->elemento[k]->centro[0]);
					Fr = corpo[i].Fcont + Fn;
					corpo[i].Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow(corpo[i].segmento[j]->raio - L-corpo[i].segmento[j]->elemento[k]->centro[0], 2);

				}

				if (corpo[i].segmento[j]->elemento[k]->centro[1]<= corpo[i].segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = 0;
					Vnormal.V[1] = 1;
					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i].velocidade, Vel2, corpo[i].segmento[j]->raio, 0, corpo[i].segmento[j]->elemento[k]->centro[1]);
					Fr = corpo[i].Fcont + Fn;
					corpo[i].Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow( corpo[i].segmento[j]->raio - corpo[i].segmento[j]->elemento[k]->centro[1], 2);

				}

				else if (corpo[i].segmento[j]->elemento[k]->centro[1] >= H- corpo[i].segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = 0;
					Vnormal.V[1] = -1;
					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i].velocidade, Vel2, corpo[i].segmento[j]->raio, 0,H- corpo[i].segmento[j]->elemento[k]->centro[1]);
					Fr = corpo[i].Fcont + Fn;
					corpo[i].Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow(corpo[i].segmento[j]->raio-H - corpo[i].segmento[j]->elemento[k]->centro[1], 2);

				}


				 //colisão entre ED

				P = mapeamento(corpo[i].segmento[j]->elemento[k]->centro[0], corpo[i].segmento[j]->elemento[k]->centro[1]);
				Px = P[0];
				Py = P[1];

				int a = -1;
				int b = 1;
				int c = -1;
				int d = 1;

				if (Px == 0)
				{
					a = 0;
				}
				else if (Px == ceil(L / dx))
				{
					b = 0;
				}
				if (Py == 0)
				{
					c = 0;
				}
				else if (Py == ceil(H / dx))
				{
					d = 0;
				}


				for (int A = a; A < b; A++)
				{
					for (int B = c; B < d; B++)
					{
						if (mapa[Px + A][Py + B].element.size() > 0)
						{
							for (int C = 0; C < mapa[Px + A][Py + B].element.size(); C++)
							{






							}
						}
					}
				}
								D = sqrt(pow(element[i].xcentro.getM()[j][k] - element[E].xcentro.getM()[Na][Nba], 2) + pow(element[i].ycentro.getM()[j][k] - element[E].ycentro.getM()[Na][Nba], 2));

								if (D < (element[E].raio.getV()[Na] + element[i].rai






			}
		}
	}


}


vetor Fnormal(vetor Vnormal, double Cn, double Kn, vetor Vel1, vetor Vel2, double ra, double rb, double d)
{
	vetor Fn(2);
	double Fne = Kn * (ra + rb - d);
	double Fnd = Cn * ((Vel1 - Vel2)*Vnormal);
	Fn = Vnormal * (Fne + Fnd);

	return Fn;

}