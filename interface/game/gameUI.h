/**
 * @file gameUI.h
 * @author Hania Potępa
 * @date 06/12/2025
 * @brief Header file for the game's visual interface (UI).
 */

#ifndef MIL_GAMEUI_H
#define MIL_GAMEUI_H

#include "./game.h"
#include <iostream>
#include <array>
#include <string>

/**
 * @class gameUI
 * @brief A static class responsible for drawing the game interface in the console.
 * * Handles rendering the question box, answers, money tree, and lifelines (resques).
 * * Uses ANSI escape codes and cursor positioning to layout elements.
 */
class gameUI {
private:
    /**
     * @brief Renders the prize money ladder (Money Tree) on the screen.
     * * Highlights the current prize level.
     * @param currentLevel The integer representing the current question number (1-12).
     */
    static void drawMoneyTree(int currentLevel);

    /**
     * @brief Renders the question frame and the four answer options.
     * @param question Reference to the question text.
     * @param a Reference to Answer A text.
     * @param b Reference to Answer B text.
     * @param c Reference to Answer C text.
     * @param d Reference to Answer D text.
     */
    static void drawQuestion(std::string &question, std::string &a, std::string &b, std::string &c, std::string &d);

    /**
     * @brief Renders the available lifelines (resques) status.
     * * Shows available resques in color and used ones as crossed out or dimmed.
     * @param has5050 True if 50:50 is still available.
     * @param hasPhone True if Phone a Friend is still available.
     * @param hasPublicity True if Ask the Audience is still available.
     */
    static void drawResque(bool has5050, bool hasPhone, bool hasPublicity);

    /**
     * @brief Main rendering method that draws the entire game screen.
     * * Combines the Money Tree, Question, Answers, and Resques into one view.
     * @param level The current question level.
     * @param question Array containing the question [0] and answers [1-4].
     * @param resque Array of booleans representing the availability of lifelines.
     */
    static void drawCombined(int level, std::array<std::string, 5> &question, std::array<bool, 3> resque);

    /**
     * @brief Moves the console cursor to specific X and Y coordinates.
     * * Used for absolute positioning of UI elements.
     * @param x The horizontal coordinate (column).
     * @param y The vertical coordinate (row).
     */
    static void gotoXY(int x, int y);

    /**
     * @brief Helper function to get ANSI background color codes.
     * @param color The name of the desired color (e.g., "blue", "gold").
     * @return A std::string containing the ANSI escape sequence for the background color.
     */
    static std::string bgColor(std::string color);

    // Grant access to the game class to use these private drawing methods
    friend class game;
};

#endif //MIL_GAMEUI_H