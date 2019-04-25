#pragma once
#include <string>
#include "Kriterium.h"
#include "Data.h"


template <typename T, typename O>
class KriteriumVydaneObalky : public Kriterium<int, Data>
{
public:
	int ohodnot(Data& obj) override { if (kolo_ == 1) return obj.getPocetVydanychObalok(); else if (kolo_ == 2) return obj.getPocetVydanychObalok2(); else return obj.getPocetVydanychObalok() + obj.getPocetVydanychObalok2(); };
	void setKolo(int kolo) { kolo_ = kolo; };
	KriteriumVydaneObalky();
private:
	int kolo_;
};

template<typename T, typename O>
inline KriteriumVydaneObalky<T, O>::KriteriumVydaneObalky()
{
}
