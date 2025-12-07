//
// Created by Hania Potępa on 06/12/2025.
//

#include "gameUI.h"
#include <iostream>
#include <string>
#include "./../../utils/utils.h"
#include "./../../utils/formating.h"
#include <array>

void gameUI::gotoXY(const int x, const int y) {
	std::cout << "\033[" << y << ";" << x << "H";
}

std::string gameUI::bgColor(const std::string color) {
	if(color == "orange") return "\033[48;5;208m";
	if(color == "green") return "\033[42m";
	return "";
}

void gameUI::drawMoneyTree(const int currentLevel) {
	const std::string prizes[] = {"  1 000 zł", "  2 000 zł", "  5 000 zł", " 10 000 zł", " 15 000 zł", " 25 000 zł", " 50 000 zł", " 75 000 zł", "125 000 zł", "250 000 zł", "500 000 zł", " 1 MILION"};
	const bool guaranteed[] = {false, true, false, false, false, false, true, false, false, false, false, true};

	const int startX = 90;
	const int startY = 3;
	gotoXY(startX, startY - 1);
	std::cout << GOLD << "--- NAGRODY ---" << RESET;

	for(int i = 11; i >= 0; i--) {
		int displayRow = startY + (11 - i);
		gotoXY(startX, displayRow);
		if(i == currentLevel - 1) std::cout << bgColor("orange") << BLACK << (guaranteed[i] ? BOLD : "") << prizes[i] << RESET;
		else if(i < currentLevel - 1) std::cout << GOLD << (guaranteed[i] ? BOLD : "") << prizes[i] << RESET;
		else std::cout << RESET << (guaranteed[i] ? BOLD : "") << prizes[i] << RESET;
	}
}

void gameUI::drawQuestion(std::string &question, std::string &a, std::string &b, std::string &c, std::string &d) {
	const int startX = 4;
	const int startY = 5;
	gotoXY(startX, startY + 2);

	std::cout << BOLD << question << RESET;

	const int ansY = startY + 5;

	gotoXY(startX, ansY);
	std::cout << GOLD << "A: " << RESET << a;
	gotoXY(startX, ansY + 1);
	std::cout << GOLD << "B: " << RESET << b;
	gotoXY(startX, ansY + 2);
	std::cout << GOLD << "C: " << RESET << c;
	gotoXY(startX, ansY + 3);
	std::cout << GOLD << "D: " << RESET << d;
}

void gameUI::drawResque(bool has5050, bool hasPhone, bool hasPublicity) {
	const int startX = 2;
	const int startY = 2;

	gotoXY(startX, startY);
	std::cout << RESET << "Koła ratunkowe:";

	gotoXY(startX, startY + 2);
	std::cout << (has5050 ? GOLD: RED) << "[ " << (has5050 ? "50:50" : "     ")  << " ]" << RESET;
	gotoXY(startX + 14, startY + 2);
	std::cout << (hasPhone ? GOLD: RED) << "[  " << (hasPhone ? "TEL" : "   ")  << "  ]" << RESET;
	gotoXY(startX + 28, startY + 2);
	std::cout << (hasPublicity ? GOLD: RED) << "[  " << (hasPublicity ? "PUB" : "   ")  << "  ]" << RESET;
}

void gameUI::drawCombined(const int level, std::array<std::string, 5> &question, std::array<bool, 3> resque) {
	clearScreen();

	drawMoneyTree(level);

	drawResque(resque[0], resque[1], resque[2]);

	drawQuestion(question[0], question[1], question[2], question[3], question[4]);

	for(int y = 2; y < 18; y++) {
		gotoXY(85, y);
		std::cout << GOLD << "|" << RESET;
	}

	gotoXY(4, 19);
};