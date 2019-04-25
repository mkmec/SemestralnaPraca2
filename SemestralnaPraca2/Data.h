#pragma once
#include <string>

class Data
{
private:
	std::string nazov_, okres_, kraj_;
	int pocetZapisanychVolicov_, pocetVydanychObalok_, pocetOdovzdanychObalok_;
	double ucast_;
public:
	std::string getNazov() {return nazov_;};
	Data(std::string nazov, std::string okres, std::string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok);
	Data();
	~Data();
};

