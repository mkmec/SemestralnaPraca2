#pragma once
#include <string>

using namespace std;

class Kandidat
{
private:
	string meno_, priezvisko_;
	int pocetHlasov_, pocetHlasov2_;
public:
	void setPocHlasov2(int pocHlasov) { pocetHlasov2_ = pocHlasov; };
	Kandidat();
	~Kandidat();
};

