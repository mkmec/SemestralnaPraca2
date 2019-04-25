#pragma once
#include <string>
#include "Kriterium.h"
#include "Data.h"


template <typename T, typename O>
class KriteriumUcast : public Kriterium<double, Data>
{
public:
	double ohodnot(Data& obj) override { if (kolo_ == 1) return obj.getUcast(); else return obj.getUcast2(); };
	void setKolo(int kolo) { kolo_ = kolo; };
	KriteriumUcast();
private:
	int kolo_;
};

template<typename T, typename O>
inline KriteriumUcast<T, O>::KriteriumUcast()
{
}
