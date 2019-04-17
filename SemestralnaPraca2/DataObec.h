#pragma once
#include <string>

using namespace std;

class DataObec
{
private:
	string nazov_, okres_, kraj_;
	int pocetZapisanychVolicov_, pocetVydanychObalok_, pocetOdovzdanychObalok_;
	double ucast_;
public:
	DataObec(string nazov, string okres, string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok);
	~DataObec();
};

