#pragma once
#include "structures/heap_monitor.h"
#include "Kriterium.h"

template <typename T, typename O>

class Filter
{
public:
	virtual bool ohodnot (O& object, Kriterium<T, O>& krit) = 0;
private:

};
