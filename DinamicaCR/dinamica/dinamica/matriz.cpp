#include "pch.h"
#include <iostream>
#include "matriz.h"

matriz::matriz(int l, int c) 
{
	size[0] = l;
	size[1] = c;
	M = new double*[l];

	for (int i = 0; i < l; i++)
	{
		M[i] = new double[c];
	}
}


int* matriz::getsize() 
{
	return size;
}


void matriz::setM(double** M1)
{
	M = M1;
}

double** matriz::getM()
{
	return M;
}

void matriz::print()
{
	std::cout << std::endl;
	for (int i = 0; i < size[0]; i++) 
	{
		for (int j = 0; j < size[1]; j++) 
		{
			std::cout << *(*(M + i) + j) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void matriz::eye()
{
	if(size[0]==size[1])
	{
		double** m = new double*[size[0]];
		for (int i = 0; i < size[0]; i++)
		{
			m[i] = new double[size[0]];
			for (int j = 0; j < size[0]; j++)
			{
				if (i == j) {
					*(*(m + i) + j) = 1;
				}
				else {
					*(*(m + i) + j) = 0;
				}

			
			}
		}
		this->setM(m);
		}
	else {
		std::cerr << "A matriz nao e quadrada\n";
	}
}


void matriz::ones()
{
	double** m = new double*[size[0]];
	for (int i = 0; i < size[0]; i++)
	{
		m[i] = new double[size[1]];
		for (int j = 0; j < size[1]; j++)
		{
			
		*(*(m + i) + j) = 1;
		}
	}
	this->setM(m);

}


void matriz::zeros() {
	double** m = new double*[size[0]];
	for (int i = 0; i < size[0]; i++)
	{
		m[i] = new double[size[1]];
		for (int j = 0; j < size[1]; j++)
		{

			*(*(m + i) + j) = 0;
		}
	}
	this->setM(m);

}


//Sobrecarga do igual

void matriz::operator =(const matriz &A) //const
{

	this->size[0] = A.size[0];
	this->size[1] = A.size[1];

	double** matriz1 = new double*[A.size[0]];
	for (int i = 0; i < A.size[0]; i++)
	{
		*(matriz1 + i) = new double[A.size[1]];
	}

	for (int i = 0; i < A.size[0]; i++)
	{
		for (int j = 0; j < A.size[1]; j++) 
		{

			*(*(matriz1 + i) + j) = *(*(A.M + i) + j);

		}
	}

	this->setM(matriz1);
}


//Construtor de copia
matriz::matriz(const matriz &A)
{
	this->size[0] = A.size[0];
	this->size[1] = A.size[1];

	double** m = new double*[A.size[0]];
	for (int i = 0; i < A.size[0]; i++)
	{
		m[i] = new double[A.size[1]];
	}

	for (int i = 0; i < A.size[0]; i++)
	{
		for (int j = 0; j < A.size[1]; j++) 
		{
			m[i][j] = A.M[i][j];
		}
	}
	this->setM(m);
}

//operador +
matriz matriz::operator + (matriz &A)
{
	if (A.size[0] == this->size[0] & A.size[1] == this->size[1])
	{
		matriz C(A.size[0], A.size[1]);
		double** c = new double*[A.size[0]];

		for (int i = 0; i < A.size[0]; i++)
		{
			c[i] = new double[A.size[1]];
			for (int j = 0; j < A.size[1]; j++)
			{

				*(*(c + i) + j) = this->M[i][j] + A.M[i][j];
			}
		}
		C.setM(c);
		return C;
	}
	else
	{
		std::cerr << "Matrizes com dimensoes diferentes\n";
	}
}

//operador -
matriz matriz::operator - (matriz &A)
{
	if (A.size[0] == this->size[0] & A.size[1] == this->size[1])
	{
		matriz C(A.size[0], A.size[1]);
		double** c = new double*[A.size[0]];

		for (int i = 0; i < A.size[0]; i++)
		{
			c[i] = new double[A.size[1]];

			for (int j = 0; j < A.size[1]; j++)
			{

				*(*(c + i) + j) = this->M[i][j] - A.M[i][j];
			}
		}
		C.setM(c);
		return C;
	}
	else 
	{
		std::cerr << "Matrizes com dimensoes diferentes\n";
	}
}

matriz matriz::operator * (matriz &B)
{
	if (this->size[1] == B.size[0])      //numero de colunas em A == numero de colunas em B
	{
		matriz P(this->size[0], B.size[1]);

		double** p = new double*[this->size[0]];


		for (int i = 0; i < this->size[0]; i++)  //tamanho das linhas da nova matriz
		{
			p[i] = new double[B.size[1]];

			for (int j = 0; j < B.size[1]; j++)    //colunas da nova matriz
			{
				*(*(p + i) + j) = 0;
				for (int k = 0; k < this->size[1]; k++)   //linhas da matriz antiga
				{
					*(*(p + i) + j) += this->M[i][k] * B.M[k][j];
				}
			}
		}
		P.setM(p);
		return P;
	}
	else 
	{
		std::cerr << "os requisitos para a multiplicacao nao foram cumpridos" << std::endl;
	}
}

matriz matriz::operator *(double n)
{
	double** p = new double*[this->size[0]];

	matriz M(this->size[0], this->size[1]);

	for (int i = 0; i < this->size[0]; i++)
	{
		p[i] = new double[this->size[1]];
		for (int j = 0; j < this->size[1]; j++)
		{
			*(*(p + i) + j) = n * this->M[i][j];
		}
	}
	M.setM(p);
	return M;
}

	
	matriz matriz::operator * (vetor &B)
	{

		if (this->size[1] == 1)      //numero de colunas em A == numero de linhas em B
		{
			matriz P(this->size[0], B.size);

			double** p = new double*[this->size[0]];


			for (int i = 0; i < this->size[0]; i++)  //tamanho das linhas da nova matriz
			{
				p[i] = new double[B.size];

				for (int j = 0; j < B.size; j++)    //colunas da nova matriz
				{
				
				*(*(p + i) + j) = this->M[i][0] * B.getV()[j];
						
					
				}
			}
			P.setM(p);
			return P;
		}
		else
		{
			std::cerr << "os requisitos para a multiplicacao nao foram cumpridos" << std::endl;
		}
	}
	