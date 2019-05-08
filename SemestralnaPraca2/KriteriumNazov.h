#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Kriterium.h"
#include "Data.h"


template <typename T, typename O>
class KriteriumNazov : public Kriterium<std::string, Data>
{
public:
	std::string ohodnot(Data& obj) override { return obj.getNazov(); }
	KriteriumNazov();

};

template<typename T, typename O>
inline KriteriumNazov<T, O>::KriteriumNazov()
{
}
