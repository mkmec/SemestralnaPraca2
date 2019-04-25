#pragma once
#include "Kriterium.h"
#include "Filter.h"


template <typename T, typename O>
class Filterfi : public Filter<T, O>
{
public:
	bool ohodnot(const O& object, const Kriterium<T, O>& kriterium) override {
		return kriterium.ohodnot(object);
	};
	void setAlpha(T alpha) { alpha_ = alpha; };
private:
	T alpha_;
};

