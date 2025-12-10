/**
* @file mainMenu.h
 * @author Hania Potępa
 * @date 02/12/2025
 * @brief Header file for the application's main menu interface.
 */

#ifndef MIL_MAINMENU_H
#define MIL_MAINMENU_H

/**
 * @class mainMenu
 * @brief A static utility class that handles the main menu UI and navigation.
 * * Serves as the central hub allowing users to start the game, check stats,
 * view credentials, or exit the application.
 */
class mainMenu {
private:
	/**
	 * @brief Captures and processes the user's menu selection.
	 * * Reads input from the console and redirects the application flow
	 * to the selected module (Game, Stats, Credentials, etc.).
	 */
	static void makeChoice();

	/**
	 * @brief Displays the input prompt and error messages.
	 * @param wrong Integer flag indicating if the previous input was invalid (non-zero for error).
	 */
	static void showYourChoice(int wrong);

public:
	/**
	 * @brief Renders the main menu options to the screen.
	 * @param again Boolean flag indicating the context of the menu display.
	 * * Set to `true` if the user is returning after a finished game (shows "Play Again").
	 * * Set to `false` (default) for the initial application launch.
	 */
	static void showMenu(bool again = false);
};

#endif // MIL_MAINMENU_H