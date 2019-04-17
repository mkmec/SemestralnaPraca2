#pragma once
#include "structures/table/unsorted_sequence_table.h"
#include "structures/table/sorted_sequence_table.h"
#include "DataObec.h"

class Menu
{
private:
	structures::SortedSequenceTable<int, DataObec*>* obecData;

	bool run_ = true;

	void vypisMenu();
	int skontrolujIntVstup();
	void nacitajData();
public:
	void vyber();
	Menu();
	~Menu();
};

