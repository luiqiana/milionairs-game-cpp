#include <iostream>
#include "database/Database.h"
#include "utils/utils.h"
#include "interface/mainMenu.h"

using namespace std;

int main() {
	try {
		// Generate database instance
		Database::getInstance();
		cout << "Starting game..." << endl;
		startGameHeader();
		// Show main menu
		mainMenu::showMenu(false);

	}
	catch(const std::exception &e) {
		cerr << "Critical error: " << e.what() << endl;
		return 1;
	}
	return 0;
}