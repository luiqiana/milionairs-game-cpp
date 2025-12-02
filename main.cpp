#include <iostream>
#include "database/Database.h"

using namespace std;

int main() {
	try {
		Database db;
		cout << "The game has begun!" << endl;
	}
	catch(const std::exception &e) {
		cerr << "Critical error: " << e.what() << endl;
		return 1;
	}
	return 0;
}