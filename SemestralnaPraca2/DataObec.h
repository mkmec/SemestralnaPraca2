#pragma once
#include <string>
#include "Data.h"

using namespace std;

class DataObec : public Data
{
private:
public:
	DataObec(string nazov, string okres, string kraj, int pocetZapisanychVolicov, int pocetVydanychObalok, double ucast, int pocetOdovzdanychObalok) :
		Data::Data(nazov, okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok){
	};
	
	~DataObec();
};

