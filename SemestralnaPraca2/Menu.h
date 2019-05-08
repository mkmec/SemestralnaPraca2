#pragma once
#include "structures/heap_monitor.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/table/sorted_sequence_table.h"
#include "DataObec.h"

class Menu
{
private:
	structures::SortedSequenceTable<std::string, Data*>* obecData;
	structures::UnsortedSequenceTable<std::string, Data*>* obecDataUns;
	structures::SortedSequenceTable<std::string, Data*>* okresData;
	structures::SortedSequenceTable<std::string, Data*>* krajData;
	

	bool run_ = true;	
		
	void vypis21(int zoradenie, structures::UnsortedSequenceTable<std::string, Data*>* table);
	void vypis22(int zoradenie, structures::UnsortedSequenceTable<std::string, Data*>* table, int kolo);
	void vypis23(int zoradenie, structures::UnsortedSequenceTable<std::string, Data*>* table, int kolo);
	void zoradUzemneJednotky();
	void vypisInfoOUzemnychJednotkach();
	void vypisMenu();
	int skontrolujIntVstup();
	void nacitajData();
public:
	void vyber();
	Menu();
	~Menu();
};

