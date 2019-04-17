#pragma once
#include <iostream>
#include <fstream>
#include "sistema.h"
using namespace std;
class dadosaida
{
public:
	ofstream myfile;
	dadosaida(string filename);
	~dadosaida();
	void salvar(sistema* Dados, int t);
};

