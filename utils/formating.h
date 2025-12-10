/**
* @file Formating.h
 * @author Hania Potępa
 * @date 02/12/2025
 * @brief Header file defining ANSI escape codes for console text formatting.
 * * Contains constant strings used to change text color and style in terminal output.
 */

#ifndef MIL_FORMATING_H
#define MIL_FORMATING_H

#include <string>

/// @brief ANSI escape code to reset all text formatting (colors and styles) to default.
inline const std::string RESET = "\033[0m";

/// @brief ANSI escape code to apply BOLD style to the text.
inline const std::string BOLD = "\033[1m";

/// @brief ANSI escape code for RED text color.
inline const std::string RED = "\033[31m";

/// @brief ANSI escape code for GREEN text color.
inline const std::string GREEN = "\033[32m";

/// @brief ANSI escape code for CYAN text color.
inline const std::string CYAN = "\033[36m";

/// @brief ANSI escape code for YELLOW text color.
inline const std::string YELLOW = "\033[33m";

/// @brief ANSI escape code for GOLD text color (uses extended 256-color palette).
inline const std::string GOLD = "\033[38;5;220m";

/// @brief ANSI escape code for WHITE text color.
inline const std::string WHITE = "\033[37m";

/// @brief ANSI escape code for BLACK text color.
inline const std::string BLACK = "\033[30m";

#endif // MIL_FORMATING_H