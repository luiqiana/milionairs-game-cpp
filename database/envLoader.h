/**
 * @file EnvLoader.h
 * @author Hania Potępa
 * @date 02/12/2025
 * @brief Header file containing inline utility functions for environment variable management.
 */

#ifndef MIL_ENVLOADER_H
#define MIL_ENVLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/**
 * @brief Retrieves the value of a system environment variable.
 * * This is a safe wrapper around the standard std::getenv function.
 * @param key The name of the environment variable (C-string).
 * @return The value of the variable as a std::string, or an empty string if the variable is not set.
 */
inline std::string getEnvVar(const char *key) {
    const char *val = std::getenv(key);
    return val ? val : "";
}

/**
 * @brief Trims leading and trailing whitespace characters from a string.
 * * Removes spaces, tabs, and newlines from the beginning and end of the input.
 * @param str The input string to be trimmed.
 * @return A new std::string containing the trimmed text.
 */
inline std::string trim(const std::string &str) {
    // Find first char that isn't space, tab or new line
    size_t first = str.find_first_not_of(" \t\n\r");

    // Check if the string is empty or contains only whitespace (npos = No Position)
    if(std::string::npos == first) return str;

    // Find last char that isn't space, tab or new line
    size_t last = str.find_last_not_of(" \t\n\r");

    return str.substr(first, (last - first + 1));
}

/**
 * @brief Loads environment variables from a .env file into the current process.
 * * Reads the file located at "./database/.env".
 * * Parses "KEY=VALUE" pairs and sets them using setenv().
 * * Ignores empty lines and comments starting with '#'.
 */
inline void loadEnv() {
    std::ifstream file("./database/.env");

    if(!file.is_open()) {
       // Check Working Directories in case of using CLion or other IDEs
       std::cerr << "[ENV] Error: .env file not found at ./database/.env!" << std::endl;
       return;
    }

    std::string line;
    while(std::getline(file, line)) {
       // Skip empty lines and comments
       if(line.empty() || line[0] == '#') continue;

       size_t pos = line.find('=');
       if(pos != std::string::npos) {
          std::string key = trim(line.substr(0, pos));
          std::string value = trim(line.substr(pos + 1));

          // Set the environment variable (overwrite allowed)
          setenv(key.c_str(), value.c_str(), 1);
       }
    }
    std::cout << "[ENV] Loaded .env file successfully!" << std::endl;
}

#endif // MIL_ENVLOADER_H