#pragma once
#include <iostream>
#include <fstream>
#include "sistema.h"
using namespace std;
class dadosaida
{
public:
	ofstream myfile;
	int ni;  //numero de impressoes
	dadosaida(string filename, int n);
	~dadosaida();
	void salvar(sistema* Dados, int t);
};

