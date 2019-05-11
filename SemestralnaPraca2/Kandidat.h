#pragma once
#include <string>
//#include "structures/heap_monitor.h"

using namespace std;

class Kandidat
{
private:
	string meno_, priezvisko_;
	int pocetHlasov_, pocetHlasov2_;
public:
	int getPocHlasov1() { return pocetHlasov_; };
	int getPocHlasov2() { return pocetHlasov2_; };
	int getPocHlasov12() { return pocetHlasov_ + pocetHlasov2_; };
	string getMeno() { return meno_; };
	string getPriezvisko() { return priezvisko_; };
	void setPocHlasov2(int pocHlasov) { pocetHlasov2_ = pocHlasov; };
	Kandidat(string meno, string priezvisko, int pocetHlasov);
	~Kandidat();
};

