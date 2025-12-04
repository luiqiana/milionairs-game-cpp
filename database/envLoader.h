//
// Created by Hania Potępa on 02/12/2025.
//

#ifndef MIL_ENVLOADER_H
#define MIL_ENVLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

inline std::string getEnvVar(const char *key) {
	const char *val = std::getenv(key);
	return val ? val : "";
}

inline std::string trim(const std::string &str) {
	// first char index of char that isn't space, tab or new line
	size_t first = str.find_first_not_of(" \t\n\r");
	// std::string::npos = No Position (probably -1)
	if(std::string::npos == first) return str;
	// last char index of char that isn't space, tab or new line
	size_t last = str.find_last_not_of(" \t\n\r");
	return str.substr(first ,(last - first + 1));
}

inline void loadEnv() {
	std::ifstream file("./database/.env");

	if(!file.is_open()) {
		// Check Working Directories in case of using CLion
		std::cerr << "[ENV] Error: .env file not found!" << std::endl;
		return;
	}

	std::string line;
	while(std::getline(file, line)) {
		if(line.empty() || line[0] == '#') continue;
		size_t pos = line.find('=');
		if(pos != std::string::npos) {
			std::string key = trim(line.substr(0, pos));
			std::string value = trim(line.substr(pos + 1));
			// (string).c_str() to change new string to old one
			setenv(key.c_str(), value.c_str(), 1);
		}
	}
	std::cout << "[ENV] Loaded .env file!" << std::endl;
}

#endif