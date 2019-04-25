#include "Menu.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <errno.h>
#include "KriteriumNazov.h"
#include "KriteriumVolici.h"
#include "KriteriumVydaneObalky.h"
#include "KriteriumOdovzdaneObalky.h"
#include "KriteriumUcast.h"
#include "Kriterium.h"
#include "FilterNazov.h"
#include <iomanip>


using namespace std;
using namespace structures;

void Menu::vypisInfoOUzemnychJednotkach()
{
	int volba;
	Kriterium<string, Data>* kriteriumNazov = new KriteriumNazov<string, Data>();
	KriteriumVolici<int, Data>* kriteriumVolici = new KriteriumVolici<int, Data>();
	KriteriumVydaneObalky<int, Data>* kriteriumVydaneObalky = new KriteriumVydaneObalky<int, Data>();
	KriteriumUcast<double, Data>* kriteriumUcast = new KriteriumUcast<double, Data>();
	KriteriumOdovzdaneObalky<int, Data>* kriteriumOdovzdaneObalky = new KriteriumOdovzdaneObalky<int, Data>();
	

	cout << "Podla akeho filtra si prajete vypisat info:\n"
			"1. Nazov\n"
			"2. Volici\n"
			"3. Ucast\n"
			">>";	
	volba = Menu::skontrolujIntVstup();
	

	switch (volba)
	{
	case 1: 
		{
			string uzJednotka;
			cout << "Zadajte nazov uzemnej jednotky:\n"
				">>";
			cin >> uzJednotka;
			DataObec* obec;
			obecData->tryFind(uzJednotka, obec);

			if (obec != nullptr)
			{
				cout << endl << "Nazov uzemnej jednotky: " << kriteriumNazov->ohodnot(*obec) << endl;				
				cout << "Uzemna jednotka patri do vyssich celkov: " << obec->getOkres() << ", " << obec->getKraj() << endl;
				kriteriumVolici->setKolo(1);
				cout << "Pocet volicov " << kriteriumVolici->ohodnot(*obec) << " v prvom kole a ";
				kriteriumVolici->setKolo(2);
				cout << kriteriumVolici->ohodnot(*obec) << " v druhom kole." << endl;

				kriteriumVydaneObalky->setKolo(1);
				cout << "Pocet vydanych obalok " << kriteriumVydaneObalky->ohodnot(*obec) << " v prvom kole a ";
				kriteriumVydaneObalky->setKolo(2);
				cout << kriteriumVydaneObalky->ohodnot(*obec) << " v druhom kole." << endl;

				kriteriumUcast->setKolo(1);
				cout << "Ucast " << kriteriumUcast->ohodnot(*obec) << "% v prvom kole a ";
				kriteriumUcast->setKolo(2);
				cout << kriteriumUcast->ohodnot(*obec) << "% v druhom kole." << endl;

				kriteriumOdovzdaneObalky->setKolo(1);
				cout << "Pocet odovzdanych obalok " << kriteriumOdovzdaneObalky->ohodnot(*obec) << " v prvom kole a ";
				kriteriumOdovzdaneObalky->setKolo(2);
				cout << kriteriumOdovzdaneObalky->ohodnot(*obec) << " v druhom kole." << endl;
			}

			break;
		}
	default:
		break;
	}

	delete kriteriumNazov;
	delete kriteriumVolici;
}

void Menu::vypisMenu()
{
	cout << "\n_____________________________";
	cout << "\nCaputka s.r.o" << endl;
	cout << "\nVyber moznost:\n"
		"0. Ukonci aplikaciu\n"
		"1. Vypis aktuapny cas\n"
		"2. Posun cas o hodinu\n"
		"3. Pridaj nove vozidlo\n"
		"4. Vypis zoznam vozidiel\n"
		"5. Pridaj novy dron\n"
		"6. Vypis vsetky drony v danom prekladisku\n"
		"7. Vytvor objednavku\n"
		"8. Vypis statistiky\n"
		"15. Zapis do suboru\n"
		"10. Nacitaj data\n"
		">>";
}

int Menu::skontrolujIntVstup()
{
	int vstup;
	bool pod = false;
	do
	{
		cin >> vstup;
		pod = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (pod == true)
		{
			cout << "\nZly vstup. Zadaj znovu:\n>>";
		}
	} while (pod == true);

	return vstup;
}

void Menu::nacitajData()
{
	ifstream stream("dataObce2.csv");	
	string line, obec, okres, kraj, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10;
	int pocetZapisanychVolicov, pocetVydanychObalok, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2;
	double ucast, ucast2;
	int test = 0;
	int cisloObce = 0;
	cout << "\nPrebieha nacitavanie...\n";

	while (getline(stream, line))
	{
		stringstream pomStream(line);

		getline(pomStream, obec, ';');
		getline(pomStream, okres, ';');
		getline(pomStream, kraj, ';');
		getline(pomStream, var1, ';');
		getline(pomStream, var2, ';');
		getline(pomStream, var3, ';');
		getline(pomStream, var4, ';');
		getline(pomStream, var5, ';');
		getline(pomStream, var6, ';');
		getline(pomStream, var7, ';');
		getline(pomStream, var8, ';');
		getline(pomStream, var9, ';');
		getline(pomStream, var10, ';');

		/*var1.erase(remove_if(var1.begin(), var1.end(), isspace), var1.end());
		var2.erase(remove_if(var2.begin(), var2.end(), isspace), var2.end());
		var4.erase(remove_if(var4.begin(), var4.end(), isspace), var4.end());*/
		pocetZapisanychVolicov = stoi(var1);
		pocetVydanychObalok = stoi(var2);
		ucast = stod(var3);
		pocetOdovzdanychObalok = stoi(var4);
		pocetPlatnychHlasov = stoi(var5);
		pocetZapisanychVolicov2 = stoi(var6);
		pocetVydanychObalok2 = stoi(var7);
		ucast2 = stod(var8);
		pocetOdovzdanychObalok2 = stoi(var9);
		pocetPlatnychHlasov2 = stoi(var10);

		do
		{
			DataObec* newObec = new DataObec(obec, okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, ucast2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2);
			if (obecData->insert(obec, newObec)) break;
			delete newObec;
			obec = obec + " okres " + okres;
		} while (true);

		/*DataObec* newObec = new DataObec(obec, okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok);
		cisloObce = stoi(var5);
		if (!obecData->insert(obec, newObec))
		{
			delete newObec;
			obec = obec + " okres " + okres;
			DataObec* newObec = new DataObec(obec, okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok);
			obecData->insert(obec, newObec);
		}
		test++;*/
	}
	cout << "\nNacitavanie dokoncene.\n";
}

void Menu::vyber()
{
	int volba = 0;

	while (run_)
	{
		Menu::vypisMenu();

		volba = Menu::skontrolujIntVstup();

		switch (volba)
		{
		case 0:
			run_ = false;
			break;

		case 1:
		{
			Menu::vypisInfoOUzemnychJednotkach();
			/*Kriterium<string, Data>* kriterium = new KriteriumNazov<string, Data>();
			for (int i = 0; i < 10; i++)
			{
				DataObec* data = obecData->operator[](i);
				cout << kriterium->ohodnot(*data) << endl;
			}
			delete kriterium;*/
			break;
		}

		case 10:
			Menu::nacitajData();
			break;

		default:
			cout << "\nZly vstup, zadaj moznost znovu.\n";
			break;
		}

	}
}

Menu::Menu() :
	obecData(new SortedSequenceTable<string, DataObec*>())
{
}


Menu::~Menu()
{
	for (TableItem<string, DataObec*>* item : *obecData)
	{
		delete item->accessData();
	}
	delete obecData;
}
