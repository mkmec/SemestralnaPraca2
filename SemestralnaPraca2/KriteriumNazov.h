#pragma once
#include <string>
#include "Kriterium.h"



class KriteriumNazov : public Kriterium<std::string, int>
{
public:
	std::string ohodnot(const int* obj);

	KriteriumNazov();
	~KriteriumNazov();
};

	