/**
* @file showTop.h
 * @author Hania Potępa
 * @date 04/12/2025
 * @brief Header file for the leaderboard and statistics display module.
 */

#ifndef MIL_SHOWTOP_H
#define MIL_SHOWTOP_H

#include <iostream>
#include <cstdint>
#include <string>

/**
 * @class showTop
 * @brief A static utility class responsible for displaying the leaderboard.
 * * Handles user interaction for viewing top players, selecting sorting criteria,
 * and displaying statistics tables.
 */
class showTop {
public:
	/**
	 * @brief Generates the main Top Players menu.
	 * * Handles the loop where the user selects the sorting category (e.g., by Money, by Level)
	 * and inputs the number of records to display.
	 */
	static void showTopPlayers();

private:
	/**
	 * @brief Displays the input prompt for the user's choice.
	 * * Visualizes error messages if the previous input was invalid.
	 * @param wrong Integer flag indicating input status (non-zero indicates an error).
	 */
	static void showYourChoice(int wrong);

	/**
	 * @brief Processes the user's selection for the leaderboard type.
	 * * Reads input from the user to determine how the statistics should be sorted.
	 * @return A std::string representing the chosen sorting criteria (e.g., database column name).
	 */
	static std::string makeChoice();

	/**
	 * @brief Fetches and displays the statistics table.
	 * * Connects to the database and prints the rows based on the provided parameters.
	 * @param howMany The number of records to retrieve (SQL LIMIT).
	 * @param choice The sorting criteria string (obtained from makeChoice).
	 * @param incorrect Boolean flag indicating if the provided "howMany" number was invalid.
	 */
	static void displayStats(int64_t howMany, std::string choice, bool incorrect);
};

#endif // MIL_SHOWTOP_H