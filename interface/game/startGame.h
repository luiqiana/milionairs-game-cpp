/**
* @file startGame.h
 * @author Hania Potępa
 * @date 05/12/2025
 * @brief Header file for the game initialization module.
 */

#ifndef MIL_STARTGAME_H
#define MIL_STARTGAME_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdint>

/**
 * @class startGame
 * @brief A static class responsible for player login/registration and launching the game.
 * * Handles the initial user flow: prompting for a username, authenticating (or registering)
 * the player in the database, and transferring control to the main game loop.
 */
class startGame {
public:
	/**
	 * @brief Main entry point to start a new game session.
	 * * Orchestrates the login process and calls the game engine.
	 */
	static void start();

private:
	/**
	 * @brief Retrieves the unique ID for a given username.
	 * * Checks if the user exists in the database. If not, it automatically
	 * calls createPlayer() to register a new user.
	 * @param playerName The username entered by the player.
	 * @return The unique player ID (int64_t) from the database.
	 */
	static int64_t getPlayerId(std::string playerName);

	/**
	 * @brief Registers a new player in the database.
	 * * Inserts a new record into the 'players' table.
	 * @param playerName The username for the new account.
	 * @return The newly generated unique ID (int64_t) for the player.
	 */
	static int64_t createPlayer(std::string playerName);

	/**
	 * @brief Prompts the user to enter their username via the console.
	 * * Handles input validation if necessary.
	 * @return The entered username as a std::string.
	 */
	static std::string getPlayerName();
};

#endif //MIL_STARTGAME_H