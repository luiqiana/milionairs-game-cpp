//
// Created by Hania Potępa on 04/12/2025.
//

#ifndef MIL_SHOWTOP_H
#define MIL_SHOWTOP_H

#include <iostream>

class showTop {
public:
	static void showTopPlayers();
private:
	static void showYourChoice(int wrong);
	static std::string makeChoice();
};


#endif