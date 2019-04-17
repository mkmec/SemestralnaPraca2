#include "Menu.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <errno.h>



using namespace std;
using namespace structures;

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
	//stream.open("obceKolo1.csv");
	string line, obec, okres, kraj, var1, var2, var3, var4, var5;
	int pocetZapisanychVolicov, pocetVydanychObalok, pocetOdovzdanychObalok;
	double ucast;
	//int test = 1;
	int cisloObce = 0;
	cout << "\nPrebieha nacitavanie...\n";


	//FILE *fp;
	//fopen_s(&fp, "obceKolo1.csv", "r");	

	//if (fp != NULL) {
	//	cout << test << endl;
	//	while (feof(fp) == 0) {//(fscanf_s(fp, "%s, %s, %s, %d,%d, %f, %d", obec, okres, kraj, &var1, &var2, &var3, &var4) == 7) {
	//		fscanf_s(fp, "%s", obec);
	//		DataObec* newObec = new DataObec(obec, okres, kraj, stoi(var1.c_str()), stoi(var2), atof(var3.c_str()), stoi(var4));
	//		obecData->insert(test, newObec);
	//		test++;
	//	}
	//	fclose(fp);
	//}


	while (getline(stream, line))
	{
		//cout << test << endl;
		//getline(stream, line);
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
		obecData->insert(cisloObce, newObec);
		//test++;
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
	obecData(new SortedSequenceTable<int, DataObec*>())
{
}


Menu::~Menu()
{
	for (TableItem<int, DataObec*>* item : *obecData)
	{
		delete item->accessData();
	}	
	delete obecData;
}
