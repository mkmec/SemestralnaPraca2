#include "Data.h"

using namespace std;


Data::Data(string nazov, string okres, string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2):
	nazov_(nazov),
	okres_(okres),
	kraj_(kraj),
	pocetZapisanychVolicov_(pocetZapisanychVolicov),
	pocetVydanychObalok_(pocetVydanychObalok),
	ucast_(ucast),
	pocetOdovzdanychObalok_(pocetOdovzdanychObalok),
	pocetPlatnychHlasov_(pocetPlatnychHlasov),
	pocetZapisanychVolicov2_(pocetZapisanychVolicov2),
	pocetVydanychObalok2_(pocetVydanychObalok2),
	ucast2_(ucast2),
	pocetOdovzdanychObalok2_(pocetOdovzdanychObalok2),
	pocetPlatnychHlasov2_(pocetPlatnychHlasov2)
{
}

Data::Data()
{
}


Data::~Data()
{
}
