//
// Created by Hania Potępa on 02/12/2025.
//

#ifndef MIL_CREDENTIALS_H
#define MIL_CREDENTIALS_H

#include "./../utils/utils.h"
#include "mainMenu.h"
#include <iostream>
#include <string>

// Function that show app credentials
inline void showCredentials() {
	showTitle();
	std::cout << R"(
+--------------------------------------+
|                Twórca                |
|                                      |
|             Hanna Potępa             |
|        hannapotepa@icloud.com        |
|                                      |
|      Aby powrócic kliknij ENTER      |
|                                      |
+--------------------------------------+
)" << std::endl;

	// clearing buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cin.get();
	showTitle();
	mainMenu::showMenu(false);
}

#endif