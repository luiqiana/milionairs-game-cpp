//
// Created by Hania Potępa on 06/12/2025.
//

#ifndef MIL_GAME_H
#define MIL_GAME_H

#include "./startGame.h"
#include <cstdint>
#include "./gameUI.h"
#include <iostream>
#include <optional>
#include <mysqlx/xdevapi.h>

class game {
private:
	static bool useResque(int64_t playerId, std::string type);
	static void gameInit(int64_t playerId);
	static std::optional<std::array<std::string, 5>> getQuestion(int level);
	static void generateRescue(int type, char correct);
	static std::string getAnswer(std::array<bool, 3> resque);
	friend class startGame;
};


#endif //MIL_GAME_H