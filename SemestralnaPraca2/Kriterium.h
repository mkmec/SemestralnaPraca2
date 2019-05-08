#pragma once
#include "structures/heap_monitor.h"

template <typename T, typename O>
class Kriterium
{
public:
	virtual T ohodnot(O& object) = 0;
	
};

