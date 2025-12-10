//
// Created by Hania Potępa on 02/12/2025.
//

#ifndef MIL_UTILS_H
#define MIL_UTILS_H

#include <iostream>
#include <thread>
#include <chrono>
#include "./formating.h"
#include <cstdlib>
#include <random>

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

inline void clearScreen() { std::system("clear"); }

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

inline void startGameHeader() {
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
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

inline void gameEnd(const int code, const std::string error = "") {
	showTitle();
	if(code == 0) std::cout << "Do zobaczenia ponownie!" << std::endl;
	else std::cerr << error << std::endl;
	std::exit(code);
}

inline bool isAlphanumeric(const std::string str) {
	if(str.empty()) return false;
	for(char c : str) {
		if(!std::isalnum(c)) return false;
	}
	return true;
}

template<typename T>
inline T getRandomC(const T min, const T max) {
	static_assert(std::is_integral<T>::value, "Type must be int, long or int64_t");
	static std::random_device rd;
	static std::mt19937_64 gen(rd());
	std::uniform_int_distribution<T> distrib(min, max);
	return distrib(gen);
}

inline char toUpperCase(const char c) {
	const int difference = 'a' - 'A';
	return c - difference;
}

#endif