#pragma once
#include "Data.h"
#include <string>

using namespace std;

class DataKraj : public Data
{
public:
	DataKraj(string nazov, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2):
		Data::Data(nazov, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, ucast2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2)
	{
	};
	~DataKraj();
};

