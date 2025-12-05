//
// Created by Hania Potępa on 04/12/2025.
//

#include "showTop.h"
#include <iostream>
#include "./../utils/utils.h"
#include <thread>
#include <chrono>
#include "./mainMenu.h"
#include <mysqlx/xdevapi.h>
#include "./../database/dbQuerys.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

void showTop::showYourChoice(int wrong) {
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

std::string showTop::makeChoice() {
	std::cout << "  ---==================---" << std::endl;
	showYourChoice(0);

	int choice;
	unsigned int wrong = 0;

	while(true) {
		if(!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			wrong = (wrong == 0 ? 1 : 2);
			showYourChoice(wrong);
			continue;
		}

		if(choice >= 1 && choice <= 4) break;

		wrong = (wrong == 0 ? 1 : 2);
		showYourChoice(wrong);
	}

	switch(choice) {
		case 1:
			return "wins";
			break;
		case 2:
			return "played_games";
			break;
		case 3:
			return "money";
			break;
		case 4:
			showTitle();
			mainMenu::showMenu(false);
			return "";
			break;
		default:
			gameEnd(1, "Internal error while choosing, quitting...");
			return "";
			break;
	}
}

void showTop::showTopPlayers() {
	showTitle();
	std::cout << R"(
+--------------------------------------+
|                                      |
|              Topka graczy            |
|                                      |
|            Wyświetl według:          |
|             1. Wygranych             |
|             2. Zagranych             |
|             3. Pieniędzy             |
|                                      |
|              4. Powrót               |
|                                      |
+--------------------------------------+
)" << std::endl << std::endl;
	std::string choice = makeChoice();
	if(choice.empty()) return;
	const int defaulthowMany = 10;
	int64_t howMany;
	bool incorrect = false;
	std::cout << "Ile graczy chcesz wyświetlić ("<< defaulthowMany << "): ";

	std::string inpLine;
	std::cin.ignore();
	std::getline(std::cin, inpLine);
	/*std::stringstream ss(inpLine);
	if(inpLine.empty() || !(ss >> howMany)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		incorrect = true;
		howMany = defaulthowMany;
	}*/
	if(inpLine.empty()) {
		howMany = defaulthowMany;
		incorrect = false;
	}
	else {
		std::stringstream ss(inpLine);
		if(!(ss >> howMany)) {
			howMany = defaulthowMany;
			incorrect = true;
		}
	}

	if(howMany < 1) {
		incorrect = true;
		howMany = defaulthowMany;
	}

	displayStats(howMany, choice, incorrect);
}

void showTop::displayStats(const int64_t howMany, const std::string choice, const bool incorrect) {
	showTitle();
	if(incorrect) std::cout << "Nieprawidłowe wejście, wyświetlam wartość domyślną" << std::endl;
	mysqlx::string query = std::format("SELECT `username`, `{}` FROM `players` ORDER BY `{}` DESC LIMIT {};", choice, choice, howMany);
	auto result = dbQuerys::selRows(query);

	if(!result.has_value()) {
		std::cerr << "Napotkano błąd: Nie można pobrać danych! Powrót do ekranu głównego za 5 sekund..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		mainMenu::showMenu(false);
		return;
	}

	mysqlx::RowResult &rowResult = *result;

	int counter = 0;
	std::cout << std::left
	<< std::setw(6) << "TOP"
	<< std::setw(25) << "Użytkownik"
	<< (choice == "wins" ? "Wygrane" : (choice == "played_games" ? "Zagrane gry" : "Zebrane pieniądze"))
	<< std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	for(auto it : rowResult) {
		counter++;
		std::cout << std::left
		<< std::setw(6) << (std::to_string(counter) + ".")
		<< std::setw(25) << it[0]
		<< it[1] << std::endl;
	}

	query = "SELECT COUNT(*) FROM `players`";
	auto result1 = dbQuerys::selRows(query);
	if(result1.has_value()) {
		mysqlx::Row row = result1 -> fetchOne();
		int64_t rowCounter = row[0].get<int64_t>();
		std::cout << "Wyświetlono: " << counter << "/" << rowCounter << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Aby powrócic kliknij ENTER" << std::endl;
	std::cin.get();

	showTopPlayers();
}