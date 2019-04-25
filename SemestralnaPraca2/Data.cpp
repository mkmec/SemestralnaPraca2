#include "Data.h"

using namespace std;


Data::Data(string nazov, string okres, string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok):
	nazov_(nazov),
	okres_(okres),
	kraj_(kraj),
	pocetZapisanychVolicov_(pocetZapisanychVolicov),
	pocetVydanychObalok_(pocetVydanychObalok),
	ucast_(ucast),
	pocetOdovzdanychObalok_(pocetOdovzdanychObalok)
{
}

Data::Data()
{
}


Data::~Data()
{
}
