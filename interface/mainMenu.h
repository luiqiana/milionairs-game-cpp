//
// Created by Hania Potępa on 02/12/2025.
//

#ifndef MIL_MAINMENU_H
#define MIL_MAINMENU_H


class mainMenu {
private:
	static void makeChoice();
	static void showYourChoice(int wrong);

public:
	static void showMenu(bool again = false);
};

#endif