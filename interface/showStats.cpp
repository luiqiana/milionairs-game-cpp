//
// Created by Hania Potępa on 05/12/2025.
//

#include "showStats.h"
#include <iostream>
#include "./../utils/utils.h"
#include "./../database/dbQuerys.h"
#include <mysqlx/xdevapi.h>
#include <string>
#include "./mainMenu.h"
#include <thread>
#include <chrono>
#include <iomanip>

void showStats::showPlayerStats() {
	showTitle();
	std::cout << "  ---==================---" << std::endl;
	std::cout << "Nazwa użytkownika gracza (\"exit\" by powrócic do menu głównego): ";
	std::string inpPlayer;
	std::cin >> inpPlayer;
	if(inpPlayer == "exit") {
		mainMenu::showMenu(false);
		return;
	}
	showPlayer(inpPlayer);
}

void showStats::showPlayer(const std::string player) {
	showTitle();
	if(!isAlphanumeric(player)) {
		std::cout << "Nie znaleziono gracza o nicku: " << player << ". Powrót za 5 sekund..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		showPlayerStats();
		return;
	}
	mysqlx::string query  = std::format("SELECT `username`, `wins`, `played_games`, `money`, `5050`, `phone`, `publicity` FROM `players` WHERE `username` = '{}';", player);
	auto result = dbQuerys::selRows(query);

	if(!result.has_value()) {
		std::cerr << "Napotkano błąd: Nie można pobrać danych! Powrót do ekranu głównego za 5 sekund..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		mainMenu::showMenu(false);
		return;
	}

	if(result -> count() == 0) {
		std::cout << "Nie znaleziono gracza o nicku: " << player << ". Powrót za 5 sekund..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		showPlayerStats();
		return;
	}

	mysqlx::Row row = result -> fetchOne();

	std::cout << std::left << std::setw(21) << "Username: " << std::setw(0) << row[0] << std::endl;
	std::cout << std::left << std::setw(21) << "Wygrane gry: " << std::setw(0) << row[1] << std::endl;
	std::cout << std::left << std::setw(21) << "Zagrane gry: " << std::setw(0) << row[2] << std::endl;
	std::cout << std::left << std::setw(22) << "Zebrane pieniądze: " << std::setw(0) << row[3] << std::endl;
	std::cout << std::left << std::setw(22) << "Użyte 50/50: " << std::setw(0) << row[4] << std::endl;
	std::cout << std::left << std::setw(22) << "Użyty telefon: " << std::setw(0) << row[5] << std::endl;
	std::cout << std::left << std::setw(24) << "Użyta publiczność: " << std::setw(0) << row[6] << std::endl;

	std::cout << std::endl << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Aby powrócic kliknij ENTER" << std::endl;
	std::cin.get();
	showPlayerStats();
}
