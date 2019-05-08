#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Kriterium.h"
#include "Data.h"


template <typename T, typename O>
class KriteriumPrislusnostObce : public Kriterium<bool, Data>
{
public:
	bool ohodnot(Data& obj) override {
		if (prislusnost_ == obj.getOkres() || prislusnost_ == obj.getKraj()) return true;
		else return false;
	};
	void setPrislusnost(std::string prislusnost) { prislusnost_ = prislusnost; };	
	KriteriumPrislusnostObce();
private:
	std::string prislusnost_;	
};

template<typename T, typename O>
inline KriteriumPrislusnostObce<T, O>::KriteriumPrislusnostObce()
{
}
