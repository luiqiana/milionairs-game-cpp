/**
 * @file Utils.h
 * @author Hania Potępa
 * @date 02/12/2025
 * @brief Header file containing general utility functions for the game.
 * * Includes helper functions for UI (ASCII art, screen clearing),
 * input validation, and random number generation.
 */

#ifndef MIL_UTILS_H
#define MIL_UTILS_H

#include <iostream>
#include <thread>
#include <chrono>
#include "./formating.h"
#include <cstdlib>
#include <random>

/**
 * @brief Returns an ASCII art representation of a number (1, 2, or 3).
 * * Used for the countdown animation.
 * @param num The integer to convert (supported values: 1, 2, 3).
 * @return std::string containing the ASCII art or empty string if num is out of range.
 */
inline std::string getHugeNumber(int num) {
    switch(num) {
       case 3:
          return R"(
  ____
 |___ \
   __) |
  |__ <
  ___) |
 |____/
)";
          break;
       case 2:
          return R"(
  ___
 |__ \
    ) |
   / /
  / /_
 |____|
)";
          break;
       case 1:
          return R"(
  __
 /_ |
  | |
  | |
  | |
  |_|
)";
          break;
       default: return "";
    }
}

/**
 * @brief Clears the console screen.
 * * Uses the system command "clear" (Linux/macOS).
 */
inline void clearScreen() { std::system("clear"); }

/**
 * @brief Displays a large animated countdown (3... 2... 1...).
 * * Clears the screen between numbers and waits for 1 second.
 */
inline void hugeCountdown() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    clearScreen();
    for(int i = 3; i >= 1; i--) {
       clearScreen();
       std::cout << getHugeNumber(i) << std::flush;
       std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "\r" << std::endl;
}

/**
 * @brief Displays the main "MILIONERZY" game logo in ASCII art.
 */
inline void showTitle() {
    clearScreen();
    std::cout << R"(
  __  __ _____ _      _____ ____  _   _ ______ _____   ________     __
 |  \/  |_   _| |    |_   _/ __ \| \ | |  ____|  __ \ |___  /\ \   / /
 | \  / | | | | |      | || |  | |  \| | |__  | |__) |   / /  \ \_/ /
 | |\/| | | | | |      | || |  | | . ` |  __| |  _  /   / /    \   /
 | |  | |_| |_| |____ _| || |__| | |\  | |____| | \ \  / /__    | |
 |_|  |_|_____|______|_____\____/|_| \_|______|_|  \_\/_____|   |_|
)" << std::endl << std::endl;
}

/**
 * @brief Displays the introductory sequence ("START ZA:" text).
 * * Triggers the countdown and then shows the main title.
 */
inline void startGameHeader() {
    clearScreen();
    std::cout << GREEN << R"(
   _____ _______       _____ _______   ______
  / ____|__   __|/\   |  __ \__   __| |___  /   /\    _
 | (___    | |  /  \  | |__) | | |       / /   /  \  (_)
  \___ \   | | / /\ \ |  _  /  | |      / /   / /\ \
  ____) |  | |/ ____ \| | \ \  | |     / /__ / ____ \ _
 |_____/   |_/_/    \_\_|  \_\ |_|    /_____/_/    \_(_)
)";
    hugeCountdown();
    std::cout << RESET;
    showTitle();
}

/**
 * @brief Terminates the game application.
 * * Displays a goodbye message or an error message depending on the exit code.
 * @param code Exit status code (0 for success, non-zero for error).
 * @param error Optional error message to display if code is non-zero.
 */
inline void gameEnd(const int code, const std::string error = "") {
    showTitle();
    if(code == 0) std::cout << "Do zobaczenia ponownie!" << std::endl;
    else std::cerr << error << std::endl;
    std::exit(code);
}

/**
 * @brief Checks if a string contains only alphanumeric characters (letters and numbers).
 * @param str The string to validate.
 * @return True if the string is not empty and alphanumeric, False otherwise.
 */
inline bool isAlphanumeric(const std::string str) {
    if(str.empty()) return false;
    for(char c : str) {
       if(!std::isalnum(c)) return false;
    }
    return true;
}

/**
 * @brief Generates a thread-safe random integer within a specified range.
 * * Uses std::mt19937_64 engine seeded with std::random_device.
 * @tparam T The integer type (int, long, int64_t).
 * @param min Inclusive lower bound.
 * @param max Inclusive upper bound.
 * @return A random value of type T between min and max.
 */
template<typename T>
inline T getRandomC(const T min, const T max) {
    static_assert(std::is_integral<T>::value, "Type must be int, long or int64_t");
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<T> distrib(min, max);
    return distrib(gen);
}

/**
 * @brief Converts a lowercase character to uppercase.
 * * Calculates the ASCII difference between 'a' and 'A'.
 * @param c The character to convert.
 * @return The uppercase version of the character.
 */
inline char toUpperCase(const char c) {
    const int difference = 'a' - 'A';
    return c - difference;
}

#endif // MIL_UTILS_H