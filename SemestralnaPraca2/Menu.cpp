#include "Menu.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <errno.h>
#include "KriteriumNazov.h"
#include "Kriterium.h"
#include "FilterNazov.h"


using namespace std;
using namespace structures;

void Menu::vypisInfoOUzemnychJednotkach()
{
	int volba;

	cout << "Podla akeho filtra si prajete vypisat info:\n"
			"1. Nazov\n"
			"2. Volici\n"
			"3. Ucast\n"
			">>\n";	
	

	switch (volba)
	{
	case1: 
		{
			string uzJednotka;
			cout << "Zadajte nazov uzemnej jednotky:\n"
				">>\n";
			cin >> uzJednotka;
			DataObec* obec;
			obecData->tryFind(uzJednotka, obec);


			break;
		}
	default:
		break;
	}
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
	ifstream stream("obceKolo1.csv");	
	string line, obec, okres, kraj, var1, var2, var3, var4, var5;
	int pocetZapisanychVolicov, pocetVydanychObalok, pocetOdovzdanychObalok;
	double ucast;
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

		/*var1.erase(remove_if(var1.begin(), var1.end(), isspace), var1.end());
		var2.erase(remove_if(var2.begin(), var2.end(), isspace), var2.end());
		var4.erase(remove_if(var4.begin(), var4.end(), isspace), var4.end());*/
		pocetZapisanychVolicov = stoi(var1);
		pocetVydanychObalok = stoi(var2);
		ucast = stod(var3);
		pocetOdovzdanychObalok = stoi(var4);

		DataObec* newObec = new DataObec(obec, okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok);
		cisloObce = stoi(var5);
		if (!obecData->insert(obec, newObec))
		{
			delete newObec;
			obec = obec + " okres " + okres;
			DataObec* newObec = new DataObec(obec, okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok);
			obecData->insert(obec, newObec);
		}
		test++;
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
