/**
 * @file game.h
 * @author Hania Potępa
 * @date 06/12/2025
 * @brief Header file for the core game logic class.
 */

#ifndef MIL_GAME_H
#define MIL_GAME_H

#include "./startGame.h"
#include <cstdint>
#include "./gameUI.h"
#include <iostream>
#include <optional>
#include <array>
#include <string>
#include <mysqlx/xdevapi.h>

/**
 * @class game
 * @brief The main class handling the quiz gameplay mechanics.
 * * This class manages the question flow, lifelines (resques), user input validation,
 * and database updates regarding money and game progress.
 * * Most methods are private and intended to be called via the friend class 'startGame'.
 */
class game {
private:
    /**
     * @brief Marks a specific lifeline (resque) as used in the database.
     * @param playerId The unique ID of the current player.
     * @param type The type of resque used (e.g., "5050", "phone", "audience").
     * @return True if the database update was successful, False otherwise.
     */
    static bool useResque(int64_t playerId, std::string type);

    /**
     * @brief Initializes and runs the main game loop.
     * * Handles the sequence of questions, checking answers, and managing game over states.
     * @param playerId The unique ID of the player starting the game.
     */
    static void gameInit(int64_t playerId);

    /**
     * @brief Fetches a random question from the database for a specific difficulty level.
     * @param level The difficulty level of the question (e.g., 1-12).
     * @return std::optional containing an array of strings if successful, or std::nullopt on error.
     * * Array structure:
     * * [0] - Question text
     * * [1] - Correct answer
     * * [2] - Wrong answer 1
     * * [3] - Wrong answer 2
     * * [4] - Wrong answer 3
     */
    static std::optional<std::array<std::string, 5>> getQuestion(int level);

    /**
     * @brief Simulates the "Phone a Friend" or "Ask the Audience" lifelines.
     * * Displays the result of the resque to the user.
     * @param type Integer representing the resque type (e.g., 1 for Phone, 2 for Audience).
     * @param correct The character representing the correct answer ('A', 'B', 'C', or 'D').
     */
    static void generateResque(int type, char correct);

    /**
     * @brief Captures and validates the user's answer or command.
     * * Checks if the input is a valid answer (A-D) or a request to use a resque.
     * * Prevents using resques that have already been used.
     * @param resque Array of booleans representing the usage status of lifelines [50:50, Phone, Audience].
     * @return A std::string containing the user's choice (e.g., "A", "exit", or a resque command).
     */
    static std::string getAnswer(std::array<bool, 3> resque);

    /**
     * @brief Updates the player's accumulated money in the database.
     * @param playerId The unique ID of the player.
     * @param money The amount of money to add/set (current prize).
     * @return True if the database update was successful, False otherwise.
     */
    static bool updateMoney(int64_t playerId, int money);

    /**
     * @brief Updates the "games won" counter or game status in the database.
     * @param playerId The unique ID of the player.
     * @return True if the database update was successful, False otherwise.
     */
    static bool updateWins(int64_t playerId);

    // Grant access to startGame class to execute gameInit()
    friend class startGame;
};

#endif //MIL_GAME_H