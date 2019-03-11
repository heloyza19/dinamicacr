#include "pch.h"
#include "vetor.h"
#include <iostream>
#include <math.h>

using namespace std;

vetor::vetor(int t)
{
	size = t;
	double *V = new double(t);
}


vetor::~vetor()
{
	delete[]V;
}

void vetor::print()
{
	cout << "=[";
	for (int i = 0; i < size; i++)
	{
		cout << *(V + i) << " ";
	}
	cout << "]\n";
}

void vetor::setV(double* A)
{
	V = A;
}


double* vetor::getV()
{
	return V;
}



double vetor::norm()
{
	double norma = 0;
	for (int i = 0; i < size; i++)
	{
		norma += pow(V[i], 2);
	}

	return sqrt(norma);

}

void vetor::zeros()
{
	double* v = new double[size];
	for (int i = 0; i < size; i++)
	{
		v[i] = 0;

	}
	this->setV(v);

}

void vetor::ones()
{
	double* v = new double[size];
	for (int i = 0; i < size; i++)
	{
		v[i] = 1;

	}
	this->setV(v);

}

//Sobrecarga do igual
void vetor::operator =(const vetor &A) //const
{

	this->size = A.size;

	double* vetor1 = new double[A.size];
	for (int i = 0; i < A.size; i++)
	{
		*(vetor1 + i) = *(A.V + i);
	}
	this->setV(vetor1);

}


//Sobrecarga do igual
//Construtor de c�pia-
//Por que usar o const na sobrecarga do operador



//Construtor de copia
vetor::vetor(const vetor &A)
{
	this->size = A.size;
	double* c = new double[A.size];
	for (int i = 0; i < A.size; i++)
	{
		*(c + i) = A.V[i];
	}
	this->setV(c);
}

vetor vetor::operator + (vetor &A) 
{
	if (A.size == this->size) 
	{
		vetor C(A.size);
		double* c = new double[A.size];

		for (int i = 0; i < A.size; i++)
		{
			c[i] = this->V[i] + A.V[i];
		}

		C.setV(c);

		return C;
	}
	else 
	{
		cerr << "vetores com tamanhos diferentes\n";
	}
}

vetor vetor::operator - (vetor &A) 
{
	if (A.size == this->size) 
	{
		vetor C(A.size);
		double* c = new double[A.size];

		for (int i = 0; i < A.size; i++)
		{
			*(c + i) = this->V[i] - A.V[i];
		}

		C.setV(c);

		return C;
	}
	else
	{
		cerr << "vetores com tamanhos diferentes\n";
	}
}

double vetor::operator *(vetor &B) 
{
	if (this->size == B.size)
	{
		double p = 0;
		for (int i = 0; i < B.size; i++)
		{
			p += this->V[i] * B.V[i];
		}
		return p;
	}
	else 
	{
		cerr << "Vetores com tamanhos diferentes\n";
	}

}

vetor vetor::cross(vetor &B)
{
	if (this->size == B.size & B.size == 3)
	{
		vetor C(3);
		double*c = new double[3];

		c[0] = (this->V[1] * B.V[2]) - (this->V[2] * B.V[1]);
		c[1] = (this->V[2] * B.V[0]) - (this->V[0] * B.V[2]);
		c[2] = (this->V[0] * B.V[1]) - (this->V[1] * B.V[0]);

		C.setV(c);
		return C;
	}
	else
	{
		cerr << "Erro\n";
	}

}

vetor vetor::operator *(double n)
{
	vetor C(this->size);
	double* c = new double[this->size];
	for (int i = 0; i < this->size; i++)
	{
		c[i] = n * this->V[i];
	}
	C.setV(c);
	return C;
}


/*
vetor vetor::operator *(matriz &A)
{
	if (Size == A.getsize()[0])
	{
		double* v = new double[A.getsize()[1]];

			for (int j = 0; j < A.getsize()[1]; j++)
			{
				*(v + j) = 0;
				for (int k = 0; k < Size; k++)
				{

					*(v + j) += this->V[k] * A.getM()[k][j];
				}

			}
			vetor V;
			V.setV(v);
			return V;
	}
	else
	{
		std::cerr << "Os requisitos para a multiplicacao nao foram cumpridos\n";
	}


}
*/