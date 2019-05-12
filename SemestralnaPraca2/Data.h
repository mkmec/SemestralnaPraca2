#pragma once
#include "structures/heap_monitor.h"
#include <string>
#include "structures/table/sorted_sequence_table.h"
#include "Kandidat.h"

class Data
{
private:
	structures::SortedSequenceTable<std::string, Kandidat*>* kandidati_;
	std::string nazov_, okres_, kraj_;
	int pocetZapisanychVolicov_, pocetVydanychObalok_, pocetOdovzdanychObalok_, pocetPlatnychHlasov_, pocetZapisanychVolicov2_, pocetVydanychObalok2_, pocetOdovzdanychObalok2_, pocetPlatnychHlasov2_;
	double ucast_, ucast2_;
public:
	structures::SortedSequenceTable<std::string, Kandidat*>* getKandidati() { return kandidati_; };
	void pridajKandidata(std::string meno, std::string priezvisko, int pocHlasov)
	{ 
		Kandidat* kandidat = new Kandidat(meno, priezvisko, pocHlasov);
		string kluc = meno + " " + priezvisko;
		kandidati_->insert(kluc, kandidat); 
	};
	void setKandidati(structures::SortedSequenceTable<std::string, Kandidat*>* kandidati) 
	{	
		kandidati_ = kandidati; 
	};
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

	void vypisInfo();
	Data(std::string nazov, std::string okres, std::string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2);
	Data(std::string nazov, std::string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2);
	Data(std::string nazov, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok, int pocetPlatnychHlasov, int pocetZapisanychVolicov2, int pocetVydanychObalok2, double ucast2, int pocetOdovzdanychObalok2, int pocetPlatnychHlasov2);
	Data();
	~Data();
};

