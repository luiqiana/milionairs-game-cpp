//
// Created by Hania Potępa on 06/12/2025.
//

#include "game.h"
#include "gameUI.h"
#include <iostream>
#include <array>
#include "./../../utils/utils.h"

void game::gameInit(const int64_t playerId) {
	std::array<std::string, 5> question = {"Pytanie 1", "Odp A", "Odp B", "Odp C", "Odp D"};
	const std::array<bool, 3> resque = {true, false, true};
	const int level = 5;
	gameUI::drawCombined(level, question, resque);
	std::string inp;
	std::cin >> inp;
	std::cout << RESET;
}