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
#include "FilterVolici.h"
#include "FilterUcast.h"
#include "DataOkres.h"
#include "DataKraj.h"
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
		int obec, okres, kraj;
		bool found = false;

		cout << "Zadajte nazov uzemnej jednotky:\n"
			">>";
		getline(cin, uzJednotka);

		obec = uzJednotka.find("obec");
		okres = uzJednotka.find("okres");
		kraj = uzJednotka.find("kraj");

		if (obec != string::npos)
		{
			Data* uzemnaJednotka;
			uzJednotka.erase(0, 5);
			found = obecData->tryFind(uzJednotka, uzemnaJednotka);
			if (found) uzemnaJednotka->vypisInfo();
		}
		else if (okres != string::npos)
		{
			Data* uzemnaJednotka;
			uzJednotka.erase(0, 6);
			found = okresData->tryFind(uzJednotka, uzemnaJednotka);
			if (found) uzemnaJednotka->vypisInfo();
		}
		else if (kraj != string::npos)
		{
			Data* uzemnaJednotka;			
			found = krajData->tryFind(uzJednotka, uzemnaJednotka);
			if (found) uzemnaJednotka->vypisInfo();
		}
		else
		{
			cout << "\nZadana uzemna jednotka sa nenasla.\n";
		}

		if (found)
		{
			/*cout << endl << "Nazov uzemnej jednotky: " << kriteriumNazov->ohodnot(*obec) << endl;
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
			cout << kriteriumOdovzdaneObalky->ohodnot(*obec) << " v druhom kole." << endl;*/

			//uzemnaJednotka->vypisInfo();
			
		} 
		else
		{
			cout << "\nZadana uzemna jednotka sa nenasla.\n";
		}

		break;
	}

	case 2:
	{		
		FilterVolici<int, Kriterium<int, Data>>* filterVolici = new FilterVolici<int, Kriterium<int, Data>>;
		
		int spodnaHranica, hornaHranica, kolo;

		cout << "\nZadajte spodnu hranicu volicov:\n>>";
		spodnaHranica = Menu::skontrolujIntVstup();
		cout << "\nZadajte hornu hranicu volicov:\n>>";
		hornaHranica = Menu::skontrolujIntVstup();
		cout << "\nZadajte kolo volieb:\n";
		kolo = Menu::skontrolujIntVstup();

		filterVolici->setAlpha(spodnaHranica);
		filterVolici->setBeta(hornaHranica);
		if (kolo != 1 && kolo != 2) kriteriumVolici->setKolo(1);	
		else kriteriumVolici->setKolo(kolo);
		
		for (TableItem<string, Data*>* item : *obecData)
		{
			if (filterVolici->ohodnot(*item->accessData(), *kriteriumVolici)) item->accessData()->vypisInfo();
		}

		for (TableItem<string, Data*>* item : *okresData)
		{
			if (filterVolici->ohodnot(*item->accessData(), *kriteriumVolici)) item->accessData()->vypisInfo();
		}

		for (TableItem<string, Data*>* item : *krajData)
		{
			if (filterVolici->ohodnot(*item->accessData(), *kriteriumVolici)) item->accessData()->vypisInfo();
		}

		delete filterVolici;
		break;
	}

	case 3:
	{
		FilterUcast<double, Kriterium<double, Data>>* filterUcast = new FilterUcast<double, Kriterium<double, Data>>;
		double spodnaHranica, hornaHranica;
		int kolo;

		cout << "\nZadajte spodnu hranicu ucasti:\n>>";
		cin >> spodnaHranica;
		cout << "\nZadajte hornu hranicu ucasti:\n>>";
		cin >> hornaHranica;
		cout << "\nZadajte kolo volieb:\n";
		kolo = Menu::skontrolujIntVstup();

		filterUcast->setAlpha(spodnaHranica);
		filterUcast->setBeta(hornaHranica);
		if (kolo != 1 && kolo != 2) kriteriumUcast->setKolo(1);
		else kriteriumUcast->setKolo(kolo);

		for (TableItem<string, Data*>* item : *obecData)
		{
			if (filterUcast->ohodnot(*item->accessData(), *kriteriumUcast)) item->accessData()->vypisInfo();
		}

		for (TableItem<string, Data*>* item : *okresData)
		{
			if (filterUcast->ohodnot(*item->accessData(), *kriteriumUcast)) item->accessData()->vypisInfo();
		}

		for (TableItem<string, Data*>* item : *krajData)
		{
			if (filterUcast->ohodnot(*item->accessData(), *kriteriumUcast)) item->accessData()->vypisInfo();
		}

		delete filterUcast;
		break;
	}

	default:
		cout << "\nZLy vstup,\n";
		break;
	}

	delete kriteriumNazov;
	delete kriteriumVolici;
	delete kriteriumVydaneObalky;
	delete kriteriumUcast;
	delete kriteriumOdovzdaneObalky;
	
}

void Menu::vypisMenu()
{
	cout << "\n_____________________________";
	cout << "\nCaputka s.r.o" << endl;
	cout << "\nVyber moznost:\n"
		"0. Ukonci aplikaciu\n"
		"1. Vypisanie informaci o uzemnych jednotkach\n"
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
	ifstream obce("dataObce2.csv");
	ifstream okresy("dataOkres2.csv");
	ifstream kraje("dataKraj2.csv");
	string line, obec, okres, kraj, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10;
	int pocetZapisanychVolicov, pocetVydanychObalok, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2;
	double ucast, ucast2;
	cout << "\nPrebieha nacitavanie...\n";

	while (getline(obce, line))
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

	}

	while (getline(okresy, line))
	{
		stringstream pomStream(line);

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

		DataOkres* newOkres = new DataOkres(okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, ucast2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2);
		okresData->insert(okres, newOkres);

	}

	while (getline(kraje, line))
	{
		stringstream pomStream(line);
		
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

		DataKraj* newKraj = new DataKraj(kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, ucast2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2);
		krajData->insert(kraj, newKraj);

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
	obecData(new SortedSequenceTable<string, Data*>()),
	okresData(new SortedSequenceTable<string, Data*>()),
	krajData(new SortedSequenceTable<string, Data*>())
{
}


Menu::~Menu()
{
	for (TableItem<string, Data*>* item : *obecData)
	{
		delete item->accessData();
	}
	delete obecData;

	for (TableItem<string, Data*>* item : *okresData)
	{
		delete item->accessData();
	}
	delete okresData;
	
	for (TableItem<string, Data*>* item : *krajData)
	{
		delete item->accessData();
	}
	delete krajData;
}
