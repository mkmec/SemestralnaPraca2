#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../../KriteriumVolici.h"
#include <string>
#include "../../../Data.h"

namespace structures
{

	/// <summary> Triedenie Heap sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typeparam>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typeparam>
	template <typename K, typename T>//, typename S, typename O>
	class HeapSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Heap sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
		template<typename S, typename L>
		void sortKriterium(UnsortedSequenceTable<K, T>& table, Kriterium<S, L>& kriterium);


	};

	template<typename K, typename T>
	inline void HeapSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		bool vymena;
		int aktualny, otec, lavy, pravy, max;

		for (int i = 1; i <= static_cast<int>(table.size()) - 1; i++)
		{
			aktualny = i;
			do
			{
				vymena = false;
				otec = (aktualny - 1) / 2;
				if ((aktualny > 0) && (table.getItemAtIndex(aktualny).getKey() > table.getItemAtIndex(otec).getKey()))
				{
					table.swap(table.getItemAtIndex(aktualny), table.getItemAtIndex(otec));
					aktualny = otec;
					vymena = true;
				}
			} while (vymena);
		}

		for (int i = table.size() - 1; i >= 0; i--)
		{
			table.swap(table.getItemAtIndex(0), table.getItemAtIndex(i));
			aktualny = 0;

			do
			{
				vymena = false;
				lavy = aktualny * 2 + 1;
				pravy = aktualny * 2 + 2;
				if ((lavy < i) && (pravy < i))
				{
					max = table.getItemAtIndex(lavy).getKey() > table.getItemAtIndex(pravy).getKey() ? lavy : pravy;
				}
				else
				{
					max = lavy < i ? lavy : pravy;
				}

				if ((max < i) && (table.getItemAtIndex(max).getKey() > table.getItemAtIndex(aktualny).getKey()))
				{
					table.swap(table.getItemAtIndex(max), table.getItemAtIndex(aktualny));
					aktualny = max;
					vymena = true;
				}
			} while (vymena);
		}
	}

	template<typename K, typename T>
	template<typename S, typename L>
	inline void HeapSort<K, T>::sortKriterium(UnsortedSequenceTable<K, T>& table, Kriterium<S, L>& kriterium)
	{

		bool vymena;
		int aktualny, otec, lavy, pravy, max;

		for (int i = 1; i <= static_cast<int>(table.size()) - 1; i++)
		{
			aktualny = i;
			do
			{
				vymena = false;
				otec = (aktualny - 1) / 2;
				if ((aktualny > 0) && (kriterium.ohodnot(*table.getItemAtIndex(aktualny).accessData()) > kriterium.ohodnot(*table.getItemAtIndex(otec).accessData())))
				{
					table.swap(table.getItemAtIndex(aktualny), table.getItemAtIndex(otec));
					aktualny = otec;
					vymena = true;
				}
			} while (vymena);
		}

		for (int i = table.size() - 1; i >= 0; i--)
		{
			table.swap(table.getItemAtIndex(0), table.getItemAtIndex(i));
			aktualny = 0;

			do
			{
				vymena = false;
				lavy = aktualny * 2 + 1;
				pravy = aktualny * 2 + 2;
				if ((lavy < i) && (pravy < i))
				{
					max = kriterium.ohodnot(*table.getItemAtIndex(lavy).accessData()) > kriterium.ohodnot(*table.getItemAtIndex(pravy).accessData()) ? lavy : pravy;
				}
				else
				{
					max = lavy < i ? lavy : pravy;
				}

				if ((max < i) && (kriterium.ohodnot(*table.getItemAtIndex(max).accessData()) > kriterium.ohodnot(*table.getItemAtIndex(aktualny).accessData())))
				{
					table.swap(table.getItemAtIndex(max), table.getItemAtIndex(aktualny));
					aktualny = max;
					vymena = true;
				}
			} while (vymena);
		}
	}


}