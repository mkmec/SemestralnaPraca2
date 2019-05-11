#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "Kriterium.h"
#include "Data.h"


template <typename T, typename O>
class KriteriumHlasyOdovzdane : public Kriterium<int, Data>
{
public:
	int ohodnot(Data& obj) override 
	{ 
		if (kolo_ == 1) return obj.getKandidati()->operator[](kandidat_)->getPocHlasov1(); 
		else if (kolo_ == 2) return obj.getKandidati()->operator[](kandidat_)->getPocHlasov2();
		else return obj.getKandidati()->operator[](kandidat_)->getPocHlasov12();
	};
	void setKolo(int kolo) { kolo_ = kolo; };
	void setKandidat(std::string kandidat) { kandidat_ = kandidat; };
	KriteriumHlasyOdovzdane();
private:
	int kolo_;
	std::string kandidat_;
};

template<typename T, typename O>
inline KriteriumHlasyOdovzdane<T, O>::KriteriumHlasyOdovzdane()
{
}
