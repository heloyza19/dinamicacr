#pragma once
#include "vetor.h"

class matriz
{
private:	
	double **M;
public:
	int size[2];
	matriz(int m, int n);
	matriz(const matriz &);


	void setM(double ** M1);
	int* getsize();
	double** getM();
	void print();

	void eye();     //cria matriz identidade
	void ones();    //cria matriz com 1's
	void zeros();	//cria matriz com 0's

	//operadores 
	void operator = (const matriz &A);
	matriz operator + (matriz &A);
	matriz operator - (matriz &A);
	matriz operator * (matriz &B);
	matriz operator * (double n);
	matriz operator * (vetor &B);

};

