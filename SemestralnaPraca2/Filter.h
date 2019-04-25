#pragma once
#include "Kriterium.h"

template <typename T, typename O>

class Filter
{
public:
	virtual bool ohodnot(const O& object, const Kriterium<T, O>& krit) = 0;
private:

};
