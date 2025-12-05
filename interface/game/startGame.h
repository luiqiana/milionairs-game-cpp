//
// Created by Hania Potępa on 05/12/2025.
//

#ifndef MIL_STARTGAME_H
#define MIL_STARTGAME_H

#include <iostream>
#include <cstdlib>

class startGame {
public:
	static void start();
private:
	static int64_t getPlayerId(std::string playerName);
	static int64_t createPlayer(std::string playerName);
	static std::string getPlayerName();
};


#endif //MIL_STARTGAME_H