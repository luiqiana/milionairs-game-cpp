//
// Created by Hania Potępa on 06/12/2025.
//

#ifndef MIL_GAME_H
#define MIL_GAME_H

#include "./startGame.h"
#include <cstdint>
#include "./gameUI.h"

class game {
private:
	static void gameInit(int64_t playerId);
	friend class startGame;
};


#endif //MIL_GAME_H