#include "structures/heap_monitor.h"
#include "Data.h"
#include <string>
#include <iostream>

using namespace std;


void Data::vypisInfo()
{
	cout << endl << "Nazov uzemnej jednotky: " << nazov_ << endl;
	cout << "Uzemna jednotka patri do vyssich celkov: ";
	if (okres_ != "") cout << okres_ << ", ";
	if (kraj_ != "") cout << kraj_;
	cout << endl;

	cout << "Pocet volicov " << pocetZapisanychVolicov_ << " v prvom kole a " << pocetZapisanychVolicov2_ << " v druhom kole." << endl;

	cout << "Pocet vydanych obalok " << pocetVydanychObalok_ << " v prvom kole a " << pocetVydanychObalok2_ << " v druhom kole." << endl;

	cout << "Ucast " << ucast_ << "% v prvom kole a " << ucast2_ << "% v druhom kole." << endl;

	cout << "Pocet odovzdanych obalok " << pocetOdovzdanychObalok_ << " v prvom kole a " << pocetOdovzdanychObalok2_ << " v druhom kole." << endl;

	cout << "Pocet platnych hlasov vsetkych kandidatov " << pocetPlatnychHlasov_ << " v prvom kole a " << pocetPlatnychHlasov2_ << " v druhom kole." << endl;

}

Data::Data(string nazov, string okres, string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2) :
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

Data::Data(std::string nazov, std::string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2) :
	nazov_(nazov),
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

Data::Data(std::string nazov, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2):
	nazov_(nazov),	
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
