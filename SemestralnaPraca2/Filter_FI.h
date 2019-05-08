#pragma once
#include "structures/heap_monitor.h"
#include "Kriterium.h"
#include "Filter.h"


template <typename T, typename O>
class Filter_Fi : public Filter<T, O>
{
public:
	bool ohodnot (O& object, Kriterium<T, O>& kriterium) override {
		T vystup = kriterium.ohodnot(object);
		return vystup >= alpha_ && vystup <= beta_;
	};
	void setAlpha(T alpha) { alpha_ = alpha; };
	void setBeta(T beta) { beta_ = beta; };
private:
	T alpha_;
	T beta_;
};

