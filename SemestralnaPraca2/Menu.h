#pragma once
#include "structures/table/unsorted_sequence_table.h"
#include "structures/table/sorted_sequence_table.h"
#include "DataObec.h"

class Menu
{
private:
	structures::SortedSequenceTable<std::string, DataObec*>* obecData;

	bool run_ = true;

	void vypisInfoOUzemnychJednotkach();
	void vypisMenu();
	int skontrolujIntVstup();
	void nacitajData();
public:
	void vyber();
	Menu();
	~Menu();
};

