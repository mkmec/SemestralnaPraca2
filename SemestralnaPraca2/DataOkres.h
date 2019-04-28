#pragma once
#include "Data.h"
#include <string>

using namespace std;

class DataOkres : public Data
{
public:
	DataOkres(string nazov, string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2):
		Data::Data(nazov, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, ucast2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2)
	{};
	~DataOkres();
};

