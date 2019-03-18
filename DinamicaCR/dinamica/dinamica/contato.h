#pragma once
#include "sistema.h"
#include <iostream>
vetor Fnormal(vetor Vnormal, double Cn, double Kn, vetor Vel1, vetor Vel2, double ra, double rb, double d);

double sistema::contato()
{
	double Eelas = 0;
	double torque1x = 0, torque1y = 0;
	double torque2x = 0, torque2y = 0;
	double ang1x, ang1y, ang2x, and2y;
	int Px, Py;
	int* P;
	double D;
	int nc, na, ne;
	int* ID;

	vetor Vnormal(2), Fn(2), Fr(2),R1(2),Fnx(2),Fny(2);
	Vnormal.zeros();
	Fn.zeros();
	Fr.zeros();
	R1.zeros();
	Fnx.zeros();
	Fny.zeros();

	for (int i = 0; i < corpo.size(); i++)
	{
		for (int j = 0; j < corpo[i]->segmento.size(); j++)
		{
			for (int k = 0; k < corpo[i]->Ned; k++)
			{

				if (corpo[i]->segmento[j]->elemento[k]->centro[0]<= corpo[i]->segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = 1;
					Vnormal.V[1] = 0;
					
					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i]->velocidade, Vel2, corpo[i]->segmento[j]->raio, 0, corpo[i]->segmento[j]->elemento[k]->centro[0]);
					Fr = corpo[i]->Fcont + Fn;
					corpo[i]->Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow(corpo[i]->segmento[j]->raio - corpo[i]->segmento[j]->elemento[k]->centro[0], 2);
	
				}


				else if (corpo[i]->segmento[j]->elemento[k]->centro[0] >= L- corpo[i]->segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = -1;
					Vnormal.V[1] = 0;

					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i]->velocidade, Vel2, corpo[i]->segmento[j]->raio, 0,L- corpo[i]->segmento[j]->elemento[k]->centro[0]);
					Fr = corpo[i]->Fcont + Fn;
					corpo[i]->Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow(corpo[i]->segmento[j]->raio - L-corpo[i]->segmento[j]->elemento[k]->centro[0], 2);

				}

				if (corpo[i]->segmento[j]->elemento[k]->centro[1]<= corpo[i]->segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = 0;
					Vnormal.V[1] = 1;
					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i]->velocidade, Vel2, corpo[i]->segmento[j]->raio, 0, corpo[i]->segmento[j]->elemento[k]->centro[1]);
					Fr = corpo[i]->Fcont + Fn;
					corpo[i]->Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow( corpo[i]->segmento[j]->raio - corpo[i]->segmento[j]->elemento[k]->centro[1], 2);

				}

				else if (corpo[i]->segmento[j]->elemento[k]->centro[1] >= H- corpo[i]->segmento[j]->raio)
				{
					vetor Vel2(2);
					Vel2.zeros();
					Vnormal.V[0] = 0;
					Vnormal.V[1] = -1;
					Fn = Fnormal(Vnormal, Cn, Kn, corpo[i]->velocidade, Vel2, corpo[i]->segmento[j]->raio, 0,H- corpo[i]->segmento[j]->elemento[k]->centro[1]);
					Fr = corpo[i]->Fcont + Fn;
					corpo[i]->Fcont.setV(Fr.getV());
					Eelas += 0.5*Kn*pow(corpo[i]->segmento[j]->raio-H - corpo[i]->segmento[j]->elemento[k]->centro[1], 2);

				}


				 //colisão entre ED

				P = mapeamento(corpo[i]->segmento[j]->elemento[k]->centro[0], corpo[i]->segmento[j]->elemento[k]->centro[1]);
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
						if (mapa[Px + A][Py + B].idelement.size() > 0)
						{
							int k = 0;
							for (std::list<id>::iterator it = mapa[Px + A][Py + B].idelement.begin(); it != mapa[Px + A][Py + B].idelement.end(); it++)
							{

								nc = (*it).c;     //n corpo rigido
								if (nc > i)
								{
									na = (*it).s;  //n aresta
									ne = (*it).n;   //n do elementodiscreto

									D = sqrt(pow(corpo[i]->segmento[j]->elemento[k]->centro[0] - corpo[nc]->segmento[na]->elemento[ne]->centro[0], 2) + pow(corpo[i]->segmento[j]->elemento[k]->centro[1] - corpo[nc]->segmento[na]->elemento[ne]->centro[1], 2));

									if (D < (corpo[i]->segmento[j]->raio + corpo[nc]->segmento[na]->raio))
									{
										
										
										double norma = sqrt(pow(corpo[i]->segmento[j]->elemento[k]->centro[0] - corpo[nc]->segmento[na]->elemento[ne]->centro[0], 2) + pow((corpo[i]->segmento[j]->elemento[k]->centro[1] - corpo[nc]->segmento[na]->elemento[ne]->centro[1]), 2));
										Vnormal.V[0] = (corpo[i]->segmento[j]->elemento[k]->centro[0] - corpo[nc]->segmento[na]->elemento[ne]->centro[0])/norma;
										Vnormal.V[1] = (corpo[i]->segmento[j]->elemento[k]->centro[1] - corpo[nc]->segmento[na]->elemento[ne]->centro[1])/norma;
										Vnormal.print();
										Fn = Fnormal(Vnormal, Cn, Kn, corpo[i]->velocidade, corpo[nc]->velocidade, corpo[i]->segmento[j]->raio, corpo[nc]->segmento[na]->raio, D);
										Fn.print();

										//corpo 1

										R1.V[0] = corpo[i]->segmento[j]->elemento[k]->centro[0] - corpo[i]->CM.V[0];
										R1.V[1] = corpo[i]->segmento[j]->elemento[k]->centro[1] - corpo[i]->CM.V[1];



										//eixo x
										if (Fn.V[0] = 0)
										{
											torque1x = 0;
										}
										else
										{
											Fnx.V[0] = Fn.V[0];
											Fnx.V[1] = 0;
											ang1x = acos((Fnx*R1) / (R1.norm()*Fnx.norm()));
											torque1x = Fnx.norm()*R1.norm()*sin(ang1x);

											if (Fnx.V[0] > 0 & corpo[i]->segmento[j]->elemento[k]->centro[1] > corpo[i]->CM.V[1])
											{
												torque1x = -torque1x;
											}
											else if (Fnx.V[0] < 0 & corpo[i]->segmento[j]->elemento[k]->centro[1] < corpo[i]->CM.V[1])
											{
												torque1x = -torque1x;
											}
										}

										//eixo y
										if (Fn.V[1] == 0)
										{
											torque1y = 0;
										}
										else
										{
											Fny.V[0] = 0;
											Fny.V[1] = Fn.V[1];

											ang1y = acos((Fny*R1) / (R1.norm()*Fny.norm()));
											torque1y = Fny.norm()*R1.norm()*sin(ang1y);

											if (Fny.V[1] > 0 & corpo[i]->segmento[j]->elemento[k]->centro[0] < corpo[i]->CM.V[0])
											{
												torque1y = -torque1y;
											}
											else if (Fny.V[1] < 0 & corpo[i]->segmento[j]->elemento[k]->centro[0] > corpo[i]->CM.V[0])
											{
												torque1y = -torque1y;
											}

										}
										corpo[i]->torque += torque1x + torque1y;




										//corpo 2
										R1.V[0] = corpo[nc]->segmento[na]->elemento[ne]->centro[0] - corpo[nc]->CM.V[0];
										R1.V[1] = corpo[nc]->segmento[na]->elemento[ne]->centro[1] - corpo[nc]->CM.V[1];

										if (Fn.V[0] == 0)
										{
											torque2x = 0;
										}
										else
										{
											Fnx.V[0] = -Fn.V[0];
											Fnx.V[1] = 0;

											ang1x = acos((Fnx*R1) / (R1.norm()*Fnx.norm()));
											torque2x = Fnx.norm()*R1.norm()*sin(ang1x);

											if (Fnx.V[0] > 0 & corpo[nc]->segmento[na]->elemento[ne]->centro[1] > corpo[nc]->CM.V[1])
											{
												torque2x = -torque2x;
											}
											else if (Fnx.V[0] < 0 & corpo[nc]->segmento[na]->elemento[ne]->centro[1] < corpo[nc]->CM.V[1])
											{
												torque2x = -torque2x;
											}


										}

										//eixo y

										if (Fn.V[1] == 0)
										{
											torque2y = 0;
										}
										else
										{
											Fny.V[0] = 0;
											Fny.V[1] = -Fn.V[1];

											ang1y = acos((Fny*R1) / (R1.norm()*Fny.norm()));
											torque2y = Fny.norm()*R1.norm()*sin(ang1y);

											if (Fny.V[1] > 0 & corpo[nc]->segmento[na]->elemento[ne]->centro[0] < corpo[nc]->CM.V[0])
											{
												torque2y = -torque2y;
											}
											else if (Fny.V[1] < 0 & corpo[nc]->segmento[na]->elemento[ne]->centro[1] > corpo[nc]->CM.V[0])
											{
												torque2y = -torque2y;
											}
										}

										corpo[nc]->torque += torque2x + torque2y;


										corpo[i]->Fcont = corpo[i]->Fcont + Fn;
										corpo[nc]->Fcont = corpo[nc]->Fcont - Fn;

										Eelas += 0.5*Kn*pow(corpo[i]->segmento[j]->raio + corpo[nc]->segmento[na]->raio - D, 2);



									}



								}

							}
							 k++;
						}
								



							}
						}
					}
				}

			}
		return Eelas;
}
	




vetor Fnormal(vetor Vnormal, double Cn, double Kn, vetor Vel1, vetor Vel2, double ra, double rb, double d)
{
	vetor Fn(2);
	double Fne = Kn * (ra + rb - d);
	double Fnd = Cn * ((Vel1 - Vel2)*Vnormal);
	Fn = Vnormal * (Fne+Fnd);
	return Fn;

}