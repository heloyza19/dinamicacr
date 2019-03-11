#pragma once

//#include "matriz.h"
class vetor
{

public:

	int size;
	double *V;

	vetor(int t);
	~vetor();
	vetor(const vetor &A);

	void setV(double* A);
	double* getV();
	void print();

	double norm();
	vetor cross(vetor &);
	void zeros();
	void ones();

	//operadores
	void operator =(const vetor &);
	vetor operator + (vetor &);
	vetor operator - (vetor &);
	double operator *(vetor &);
	vetor operator *(double);
	//vetor operator *(matriz &A);
	
};

