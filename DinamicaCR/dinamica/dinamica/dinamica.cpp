#include "pch.h"
#include <iostream>
#include "leituradedados.h"
#include "sistema.h"
#include "dadosaida.h"


int main(int argc, char* argv)
{
	sistema* Dados;
	dadosaida saida("saida.xdmf");

	Dados = leituradedados(argc, argv);
	

	cout << "dx=" << Dados->dx << endl;
	cout <<"dt= "<< Dados->dt << endl;
	cout << "tc= " << Dados->dt / Dados->e<<endl;
	cout << "massa0= " << Dados->corpo[0]->massa << endl;
	cout << "massa1= " << Dados->corpo[1]->massa << endl;

	int temp = ceil(Dados->times / Dados->dt);
	double* Eelas = new double[temp];
	double* Ek = new double[temp];
	double* Ekr = new double[temp];


	for (int t=0; t <temp;t++)
	{	

		/*for (int i = 0; i < Dados->corpo.size(); i++)
		{
			cout << "corpo" << i << endl;
			for (int j = 0; j < Dados->corpo[i]->segmento.size(); j++)
			{
				for (int k = 0; k < Dados->corpo[i]->Ned; k++)
				{

					cout << Dados->corpo[i]->segmento[j]->elemento[k]->centro[0] << " " << Dados->corpo[i]->segmento[j]->elemento[k]->centro[1] << endl;




				}
			}
			cout << endl;
		}*/







		saida.salvar(Dados, t);
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
	cout << "energia final k r e= " << Ek[0]<<" "<< Ekr[0]<<" "<< Eelas[0] << endl;
	cout << "energia final k r e= " << Ek[temp - 2]<< " "<< Ekr[temp-2]<<" "<<Eelas[temp-2]<<endl ;

	Dados->corpo[0]->posicao.print();
	Dados->corpo[1]->posicao.print();

	cout << Dados->corpo[0]->W << " " << Dados->corpo[1]->W << endl;
	Dados->corpo[0]->velocidade.print();
	Dados->corpo[1]->velocidade.print();





	return 0;
}


