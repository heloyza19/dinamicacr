#pragma once
#include <list>
#include "elementodiscreto.h"
using namespace std;

class campo
{
public:
	list <elementodiscreto*> element;

	campo();
	~campo();
};

