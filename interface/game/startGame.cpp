//
// Created by Hania Potępa on 05/12/2025.
//

#include "startGame.h"
#include <iostream>
#include "./../../utils/utils.h"
#include <mysqlx/xdevapi.h>
#include "../../database/dbQuerys.h"
#include "./../mainMenu.h"

void startGame::start() {
	showTitle();
	long playerId = getPlayerId(getPlayerName());

	if(playerId == -1) {
		std::cerr << "Napotkano błąd: Nie można pobrać danych! Powrót do ekranu głównego za 5 sekund..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		mainMenu::showMenu(false);
		return;
	}

	std::cout << playerId << std::endl;
}

std::string startGame::getPlayerName() {
	int wrong = 0;
	while(true) {
		if(wrong != 0) std::cout << "Możesz użyć tylko zwyklych liter i cyfr!" << std::endl;
		std::cout << "Podaj swoją nazwe użytkownika (litery i cyfry): ";
		std::string playerName;
		std::cin >> playerName;
		if(isAlphanumeric(playerName)) return playerName;
		wrong++;
		if(wrong == 1) std::cout << "\033[1A";
		else std::cout << "\033[2A";
		std::cout << "\033[0J";
	}
}

int64_t startGame::getPlayerId(const std::string playerName) {
	mysqlx::string query = std::format("SELECT `id` FROM `players` WHERE `username` = '{};'", playerName);
	auto result = dbQuerys::selRows(query);

	if(!result.has_value()) return -1;

	int rowCount = result -> count();
	if(rowCount == 1) {
		mysqlx::Row row = result -> fetchOne();
		return row[0].get<int64_t>();
	}
	return (rowCount == 0 ? createPlayer(playerName) : -1);
}

int64_t startGame::createPlayer(const std::string playerName) {
	mysqlx::string query = std::format("INSERT INTO `players` (`username`, `wins`, `played_games`, `5050`, `phone`, `publicity`, `money`) VALUES ('{}', 0, 1, 0, 0, 0, 0);", playerName);
	return dbQuerys::insertLine(query);
}
