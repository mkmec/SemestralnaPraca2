#include "structures/heap_monitor.h"
#include "Menu.h"

using namespace std;

int main()
{
	initHeapMonitor();

	Menu *menu = new Menu();
	menu->vyber();
	delete menu;

	return 0;
}