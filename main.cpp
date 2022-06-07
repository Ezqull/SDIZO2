#include <string>
#include <cstdlib>
#include <ctime>
#include "Menu.h"

int main(){
	srand(time(NULL));
	Menu menu;
    menu.menu();
	return 0;
}
