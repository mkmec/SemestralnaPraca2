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
#include "KriteriumPrislusnostObce.h"
#include "KriteriumUcast.h"
#include "Kriterium.h"
#include "FilterNazov.h"
#include "FilterVolici.h"
#include "FilterUcast.h"
#include "FilterPrislusnostObce.h"
#include "DataOkres.h"
#include "DataKraj.h"
#include <iomanip>
#include "structures/table/sorting/heap_sort.h"


using namespace std;
using namespace structures;


void Menu::vypis21(int zoradenie, UnsortedSequenceTable<string, Data*>* table)
{
	if (zoradenie == 1)
	{
		for (auto item : *table)
		{
			cout << item->getKey() << endl;
		}
	}
	else
	{
		for (int i = table->size() - 1; i >= 0; i--)
		{
			cout << table->getItemAtIndex(i).getKey() << endl;
		}
	}
}


void Menu::vypis22(int zoradenie, UnsortedSequenceTable<string, Data*>* table, int kolo)
{
	if (zoradenie == 1)
	{
		for (auto item : *table)
		{
			cout << left << setw(40) << item->getKey() << left << (kolo == 1 ? item->accessData()->getPocetZapisanychVolicov() : item->accessData()->getPocetZapisanychVolicov()) << endl;
		}
	}
	else
	{
		for (int i = table->size() - 1; i >= 0; i--)
		{
			cout << left << setw(40) << table->getItemAtIndex(i).getKey() << left << (kolo == 1 ? table->getItemAtIndex(i).accessData()->getPocetZapisanychVolicov() :
				table->getItemAtIndex(i).accessData()->getPocetZapisanychVolicov2()) << endl;
		}
	}
}

void Menu::vypis23(int zoradenie, UnsortedSequenceTable<string, Data*>* table, int kolo)
{
	if (zoradenie == 1)
	{
		for (auto item : *table)
		{
			cout << left << setw(40) << item->getKey() << left << (kolo == 1 ? item->accessData()->getUcast() : item->accessData()->getUcast2()) << endl;
		}
	}
	else
	{
		for (int i = table->size() - 1; i >= 0; i--)
		{
			cout << left << setw(40) << table->getItemAtIndex(i).getKey() << left << (kolo == 1 ? table->getItemAtIndex(i).accessData()->getUcast() :
				table->getItemAtIndex(i).accessData()->getUcast2()) << endl;
		}
	}
}

void Menu::zoradUzemneJednotky()
{
	int spodnaHranica, hornaHranica, kolo, zoradenie, kriterium, volba;
	string prislusnost;
	//SortedSequenceTable<string, Data>* utriedeneObce = new SortedSequenceTable<string, Data>();

	KriteriumPrislusnostObce<bool, Data>* kriteriumPrislusnostObce = new KriteriumPrislusnostObce<bool, Data>();
	Kriterium<string, Data>* kriteriumNazov = new KriteriumNazov<string, Data>();
	KriteriumUcast<double, Data>* kriteriumUcast = new KriteriumUcast<double, Data>();
	KriteriumVolici<int, Data>* kriteriumVolici = new KriteriumVolici<int, Data>();


	FilterPrislusnostObce<bool, Kriterium<bool, Data>>* filterPrislusnostObce = new FilterPrislusnostObce<bool, Kriterium<bool, Data>>;
	FilterUcast<double, Kriterium<double, Data>>* filterUcast = new FilterUcast<double, Kriterium<double, Data>>;
	filterPrislusnostObce->setAlpha(true);

	cout << "\nPrajete si vypisat:\n"
		"1. Vsetky obce\n"
		"2. Obce podla filtra\n";
	volba = Menu::skontrolujIntVstup();
	if (volba != 1 && volba != 2) volba = 1;

	cout << "\nZadajte kolo volieb:\n";
	kolo = Menu::skontrolujIntVstup();
	if (kolo != 1 && kolo != 2) kolo = 1; 

	kriteriumUcast->setKolo(kolo);
	kriteriumVolici->setKolo(kolo);

	if (volba == 2)
	{
		cout << "\nZadajte spodnu hranicu ucasti:\n>>";
		cin >> spodnaHranica;
		cout << "\nZadajte hornu hranicu ucasti:\n>>";
		cin >> hornaHranica;

		filterUcast->setAlpha(spodnaHranica);
		filterUcast->setBeta(hornaHranica);

		cout << "\nZadajte vyssiu uzemnu jednotku:\n>>";
		cin.ignore();
		getline(cin, prislusnost);
	}

	cout << "\nZoradit:\n"
		"1. vzostupnu\n"
		"2. zostupne\n";
	zoradenie = Menu::skontrolujIntVstup();
	if (zoradenie != 1 && zoradenie != 2) zoradenie = 1;

	cout << "Podla akeho kriteria si prajete vypisat obce:\n"
		"1. Nazov\n"
		"2. Volici\n"
		"3. Ucast\n"
		">>";
	kriterium = Menu::skontrolujIntVstup();
	if (kriterium != 1 && kriterium != 2 && kriterium != 3) kriterium = 1;

	kriteriumPrislusnostObce->setPrislusnost(prislusnost);

	UnsortedSequenceTable<string, Data*>* utriedeneObce = new UnsortedSequenceTable<string, Data*>();
	HeapSort<string, Data*>* heapsort = new HeapSort<string, Data*>();

	switch (kriterium)
	{
	case 1:
	{
		if (volba == 2)
		{
			for (auto item : *obecData)
			{
				if (filterUcast->ohodnot(*item->accessData(), *kriteriumUcast) && filterPrislusnostObce->ohodnot(*item->accessData(), *kriteriumPrislusnostObce))
				{
					utriedeneObce->insert(item->getKey(), item->accessData());
				}
			}
		}

		if ((volba == 2 && !utriedeneObce->isEmpty()) || (volba == 1 && !obecDataUns->isEmpty()))
		{
			if (volba == 1)
			{
				heapsort->sortKriterium(*obecDataUns, *kriteriumNazov);
				vypis21(zoradenie, obecDataUns);
			}
			else
			{
				heapsort->sortKriterium(*utriedeneObce, *kriteriumNazov);
				vypis21(zoradenie, utriedeneObce);
			}
		}
		else
		{
			cout << "\nZadanym filtrom sa nenasla ziadna zhoda\n";
		}

		break;
	}

	case 2:
	{
		if (volba == 2)
		{
			for (auto item : *obecData)
			{
				if (filterUcast->ohodnot(*item->accessData(), *kriteriumUcast) && filterPrislusnostObce->ohodnot(*item->accessData(), *kriteriumPrislusnostObce))
				{
					utriedeneObce->insert(item->getKey(), item->accessData());
				}
			}
		}

		if ((volba == 2 && !utriedeneObce->isEmpty()) || (volba == 1 && !obecDataUns->isEmpty()))
		{
			cout << endl << left << setw(40) << "NAZOV OBCE" << left << "POCET VOLICOV\n";

			if (volba == 1)
			{
				heapsort->sortKriterium(*obecDataUns, *kriteriumVolici);
				vypis22(zoradenie, obecDataUns, kolo);
			}
			else
			{
				heapsort->sortKriterium(*utriedeneObce, *kriteriumVolici);
				vypis22(zoradenie, utriedeneObce, kolo);
			}
		}
		else
		{
			cout << "\nZadanym filtrom sa nenasla ziadna zhoda\n";
		}

		break;
	}

	case 3:
	{
		if (volba == 2)
		{
			for (auto item : *obecData)
			{
				if (filterUcast->ohodnot(*item->accessData(), *kriteriumUcast) && filterPrislusnostObce->ohodnot(*item->accessData(), *kriteriumPrislusnostObce))
				{
					utriedeneObce->insert(item->getKey(), item->accessData());
				}
			}
		}

		if ((volba == 2 && !utriedeneObce->isEmpty()) || (volba == 1 && !obecDataUns->isEmpty()))
		{
			cout << endl << left << setw(40) << "NAZOV OBCE" << left << "UCAST\n";

			if (volba == 1)
			{
				heapsort->sortKriterium(*obecDataUns, *kriteriumUcast);
				vypis23(zoradenie, obecDataUns, kolo);
			}
			else
			{
				heapsort->sortKriterium(*utriedeneObce, *kriteriumUcast);
				vypis23(zoradenie, utriedeneObce, kolo);
			}
		}
		else
		{
			cout << "\nZadanym filtrom sa nenasla ziadna zhoda\n";
		}

		break;
	}

	}



	delete heapsort;
	delete utriedeneObce;
	delete kriteriumPrislusnostObce;
	delete kriteriumNazov;
	delete kriteriumUcast;
	delete kriteriumVolici;
	delete filterPrislusnostObce;
	delete filterUcast;

}

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
		cin.ignore();
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
		"2. Zoradenie uzemnych jednotiek podla filtra\n"
		"3. \n"
		"4. \n"
		"5. \n"
		"6. \n"
		"7. \n"
		"8. \n"
		"15. \n"
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
			if (obecData->insert(obec, newObec))
			{
				DataObec* newObec2 = new DataObec(obec, okres, kraj, pocetZapisanychVolicov, pocetVydanychObalok, ucast, pocetOdovzdanychObalok, pocetPlatnychHlasov, pocetZapisanychVolicov2, pocetVydanychObalok2, ucast2, pocetOdovzdanychObalok2, pocetPlatnychHlasov2);
				obecDataUns->insert(obec, newObec2);
				break;
			}
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

		case 2:
		{
			Menu::zoradUzemneJednotky();
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
	obecDataUns(new UnsortedSequenceTable<string, Data*>()),
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

	for (auto item : *obecDataUns)
	{
		delete item->accessData();
	}
	delete obecDataUns;
}
