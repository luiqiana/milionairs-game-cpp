/**
* @file showStats.h
 * @author Hania Potępa
 * @date 05/12/2025
 * @brief Header file for the individual player statistics module.
 */

#ifndef MIL_SHOWSTATS_H
#define MIL_SHOWSTATS_H

#include <iostream>
#include <string>

/**
 * @class showStats
 * @brief A static utility class for searching and displaying specific player statistics.
 * * Handles the user interface for entering a username and fetching their game history.
 */
class showStats {
public:
	/**
	 * @brief Displays the search menu for player statistics.
	 * * Prompts the user to input a username, validates the input, and calls the display logic.
	 */
	static void showPlayerStats();

private:
	/**
	 * @brief Queries the database and displays statistics for a specific player.
	 * * Fetches data such as high score, games played, or level reached for the given username.
	 * @param player The username (std::string) to search for in the database.
	 */
	static void showPlayer(std::string player);
};

#endif // MIL_SHOWSTATS_H