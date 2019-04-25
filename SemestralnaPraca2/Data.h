#pragma once
#include <string>

class Data
{
private:
	std::string nazov_, okres_, kraj_;
	int pocetZapisanychVolicov_, pocetVydanychObalok_, pocetOdovzdanychObalok_, pocetPlatnychHlasov_, pocetZapisanychVolicov2_, pocetVydanychObalok2_, pocetOdovzdanychObalok2_, pocetPlatnychHlasov2_;
	double ucast_, ucast2_;
public:
	std::string getNazov() {return nazov_;};
	std::string getOkres() {return okres_;};
	std::string getKraj() {return kraj_;};
	int getPocetZapisanychVolicov() { return pocetZapisanychVolicov_; };
	int getPocetVydanychObalok() { return pocetVydanychObalok_; };
	int getPocetOdovzdanychObalok() { return pocetOdovzdanychObalok_; };
	int getPocetPlatnychHlasov() { return pocetPlatnychHlasov_; };
	int getPocetZapisanychVolicov2() { return pocetZapisanychVolicov2_; };
	int getPocetVydanychObalok2() { return pocetVydanychObalok2_; };
	int getPocetOdovzdanychObalok2() { return pocetOdovzdanychObalok2_; };
	int getPocetPlatnychHlasov2() { return pocetPlatnychHlasov2_; };
	double getUcast() { return ucast_; };
	double getUcast2() { return ucast2_; };

	Data(std::string nazov, std::string okres, std::string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2);
	Data();
	~Data();
};

