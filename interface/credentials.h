/**
* @file Credentials.h
 * @author Hania Potępa
 * @date 02/12/2025
 * @brief Header file for displaying application credits.
 */

#ifndef MIL_CREDENTIALS_H
#define MIL_CREDENTIALS_H

#include "./../utils/utils.h"
#include "mainMenu.h"
#include <iostream>
#include <string>
#include <limits> // Required for std::numeric_limits

/**
 * @brief Displays the application credentials/credits screen.
 * * Shows the author's name and contact information in a formatted ASCII box.
 * * Clears the input buffer and pauses execution until the user presses ENTER.
 * * Redirects the user back to the Main Menu after viewing.
 */
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

	// Clear the input buffer to ensure cin.get() waits for a fresh keypress
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Wait for user to press Enter
	std::cin.get();

	// Refresh title and return to menu
	showTitle();
	mainMenu::showMenu(false);
}

#endif // MIL_CREDENTIALS_H