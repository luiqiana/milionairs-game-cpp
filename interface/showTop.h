//
// Created by Hania Potępa on 04/12/2025.
//

#ifndef MIL_SHOWTOP_H
#define MIL_SHOWTOP_H

#include <iostream>
#include <cstdint>

class showTop {
public:
	static void showTopPlayers();
private:
	static void showYourChoice(int wrong);
	static std::string makeChoice();
	static void displayStats(int64_t howMany, std::string choice, bool incorrect);
};


#endif