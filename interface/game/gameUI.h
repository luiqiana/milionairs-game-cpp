//
// Created by Hania Potępa on 06/12/2025.
//

#ifndef MIL_GAMEUI_H
#define MIL_GAMEUI_H

#include "./game.h"
#include <iostream>
#include <array>

class gameUI {
private:
	static void drawMoneyTree(int currentLevel);
	static void drawQuestion(std::string &question, std::string &a, std::string &b, std::string &c, std::string &d);
	static void drawResque(bool has5050, bool hasPhone, bool hasPublicity);
	static void drawCombined(int level, std::array<std::string, 5> &question, std::array<bool, 3> resque);
	static void gotoXY(int x, int y);
	static std::string bgColor(std::string color);
	friend class game;
};


#endif //MIL_GAMEUI_H