#pragma once
#include <string>
#include "Kriterium.h"
#include "Data.h"


template <typename T, typename O>
class KriteriumVolici : public Kriterium<int, Data>
{
public:
	int ohodnot(Data& obj) override { if (kolo_ == 1) return obj.getPocetZapisanychVolicov(); else return obj.getPocetZapisanychVolicov2(); };
	void setKolo(int kolo) { kolo_ = kolo; };
	KriteriumVolici();
private:
	int kolo_;
};

template<typename T, typename O>
inline KriteriumVolici<T, O>::KriteriumVolici()
{
}
