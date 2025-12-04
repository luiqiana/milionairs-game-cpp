//
// Created by Hania Potępa on 02/12/2025.
//

#include "mainMenu.h"
#include <iostream>
#include <string>
#include "./../utils/formating.h"
#include "./credentials.h"
#include "./showTop.h"

void mainMenu::showYourChoice(const int wrong) {
	// \033[*A = Cursor * lines up
	// \033[2K = Clear line
	// \033[0J = Clear everything below cursor

	if(wrong == 1) std::cout << "\033[1A";
	else if(wrong == 2) std::cout << "\033[2A";

	if(wrong != 0) {
		std::cout << "\033[0J";
		std::cout << RED << "Nieprawidłowy wybór!" << RESET << std::endl;
	}

	std::cout << "Twój wybór: ";
}

void mainMenu::makeChoice() {
	std::cout << "  ---==================---" << std::endl;
	showYourChoice(0);
	int choice = 0;
	unsigned int wrong = 0;
	while(true) {
		if(!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			wrong = (wrong == 0 ? 1 : 2);
			showYourChoice(wrong);
			continue;
		}

		if(choice >= 1 && choice <= 5) break;

		wrong = (wrong == 0 ? 1 : 2);
		showYourChoice(wrong);
	}

	switch(choice) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			showTop::showTopPlayers();
			break;
		case 4:
			showCredentials();
			break;
		case 5:
			gameEnd(0);
			break;
		default:
			gameEnd(1, "Internal error while choosing, quitting...");
			break;
	}
}

void mainMenu::showMenu(bool again) {
	if(!again) {
		std::cout << R"(
+--------------------------------------+
|         Witaj w teleturnieju         |
|              MILIONERZY              |
|                                      |
|        Wybierz jedną z opcji:        |
|              1. Zagraj               |
|         2. Statystyki gracza         |
|            3. Top graczy             |
|              4. Twórca               |
|              5. Wyjście              |
|                                      |
+--------------------------------------+
)";
	}
	else {
		std::cout << R"(
+--------------------------------------+
|           Zagraj ponownie w          |
|              MILIONERÓW              |
|                                      |
|        Wybierz jedną z opcji:        |
|              1. Zagraj               |
|         2. Statystyki gracza         |
|            3. Top graczy             |
|              4. Twórca               |
|              5. Wyjście              |
|                                      |
+--------------------------------------+
)";
	}
	std::cout << std::endl << std::endl;
	makeChoice();
}