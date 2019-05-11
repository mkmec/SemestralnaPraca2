#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Kriterium.h"
#include "Kandidat.h"


template <typename T, typename O>
class KriteriumMeno : public Kriterium<std::string, Kandidat>
{
public:
	std::string ohodnot(Kandidat& obj) override { return obj.getMeno() + " " + obj.getPriezvisko(); }
	KriteriumMeno();

};

template<typename T, typename O>
inline KriteriumMeno<T, O>::KriteriumMeno()
{
}
