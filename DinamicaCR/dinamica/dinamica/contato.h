#pragma once
#include "sistema.h"

vetor Fnormal(vetor Vnormal, double Cn, double Kn, vetor Vel1, vetor Vel2, double ra, double rb, double d);

void sistema::contato()
{
	double Eelas = 0;
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