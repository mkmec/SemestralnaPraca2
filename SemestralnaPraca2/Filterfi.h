#pragma once
#include "Kriterium.h"
#include "Filter.h"


template <typename T, typename O>
class Filterfi : public Filter<T, O>
{
public:
	bool ohodnot(O& object, Kriterium<T, O>& kriterium) {
		return kriterium.ohodnot(object) == alpha_;
	};
	void setAlpha(T alpha) { alpha_ = alpha; };
private:
	T alpha_;
};

