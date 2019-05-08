#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Kriterium.h"
#include "Data.h"


template <typename T, typename O>
class KriteriumOdovzdaneObalky : public Kriterium<int, Data>
{
public:
	int ohodnot(Data& obj) override { if (kolo_ == 1) return obj.getPocetOdovzdanychObalok(); else if (kolo_ == 2) return obj.getPocetOdovzdanychObalok2(); else return obj.getPocetOdovzdanychObalok() + obj.getPocetOdovzdanychObalok2(); };
	void setKolo(int kolo) { kolo_ = kolo; };
	KriteriumOdovzdaneObalky();
private:
	int kolo_;
};

template<typename T, typename O>
inline KriteriumOdovzdaneObalky<T, O>::KriteriumOdovzdaneObalky()
{
}
