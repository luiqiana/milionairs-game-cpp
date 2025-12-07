//
// Created by Hania Potępa on 06/12/2025.
//

#include "game.h"
#include "gameUI.h"
#include <iostream>
#include <array>
#include "./../../utils/utils.h"
#include <mysqlx/xdevapi.h>
#include "./../../database/dbQuerys.h"
#include <optional>
#include <cstdint>
#include "./../mainMenu.h"
#include "./../../utils/utils.h"
#include <algorithm>
#include <random>
#include <iterator>
#include <chrono>
#include <thread>
#include <vector>
#include <sstream>

bool game::useResque(int64_t playerId, const std::string type) {
	mysqlx::string query = std::format("UPDATE `players` SET `{}` = `{}` + 1 WHERE `id` = {}", type, type, playerId);
	return dbQuerys::updateLine(query);
}

auto forceString = [](const mysqlx::Value &val) -> std::string {
	try {
		auto bytes = val.getRawBytes();
		return std::string(reinterpret_cast<const char*>(bytes.first), bytes.second);
	}
	catch( ... ) {
		std::stringstream ss;
		ss << val;
		return ss.str();
	}
};

std::optional<std::array<std::string, 5>> game::getQuestion(const int level) {
	mysqlx::string query = std::format("SELECT `quest`, `ans`, `bad1`, `bad2`, `bad3` FROM `questions` WHERE `level` = {};", level);
	auto result = dbQuerys::selRows(query);
	if(!result.has_value()) return std::nullopt;

	mysqlx::RowResult &rowResult = *result;
	const int64_t rowCount = rowResult.count();
	if(rowCount < 1) return std::nullopt;
	const int64_t random = getRandomC<int64_t>(0, rowCount - 1);

	std::cout << getRandomC<int64_t>(0, 10);
	std::cout << random << std::endl;
	mysqlx::Row row;
	int64_t counter = 0;
	while((row = rowResult.fetchOne())) {
		std::cout << "petla";
		if(counter == random) {
			std::cout << "break";
			break;
		}
		counter++;
	}
	std::cout << row[0] << std::endl;
	std::array<std::string, 5> question = {
		row[0].get<std::string>(),
		row[1].get<std::string>(),
		row[2].get<std::string>(),
		row[3].get<std::string>(),
		row[4].get<std::string>()
	};
	return question;
}

std::string game::getAnswer(std::array<bool, 3> resque) {
	char choosedChar;
	int wrong = 0;
	std::string errorString = "Nieprawidłowe wejście";
	while(true) {
		if(wrong == 1) std::cout << "\033[1A";
		else if(wrong >= 2) std::cout << "\033[2A";
		std::cout << "\033[0J";
		if(wrong != 0) {
			if(wrong == 1) std::cout << "\033[1A";
			else if(wrong >= 2) std::cout << "\033[2A";
			std::cout << "\033[0J";
			std::cout << errorString << std::endl;
		}
		std::cout << RESET << "Wybierz odpowiedź (A/B/C/D), koło ratunkowe (1/2/3) lub wyjście (exit): " << GOLD;
		std::string inp;
		std::cin >> inp;
		std::cout << RESET;

		if(inp == "exit") return "exit";

		if(inp.length() > 1) {
			wrong++;
			errorString = "Nieprawidłowe wejście";
			continue;
		}

		choosedChar = inp.at(0);
		if(!((choosedChar >= 'A' && choosedChar <= 'D') || (choosedChar >= 'a' && choosedChar <= 'd') || (choosedChar >= '1' && choosedChar <= '3'))) {
			wrong++;
			errorString = "Nieprawidłowe wejście";
			continue;
		}

		if((choosedChar >= 'a' && choosedChar <= 'd')) choosedChar = toUpperCase(choosedChar);

		if(choosedChar >= '1' && choosedChar <= '3') {
			std::string charString = "";
			charString += choosedChar;
			const int resqueChoice = std::stoi(charString) - 1;
			if(!resque[resqueChoice]) {
				wrong++;
				errorString = "Niestety to koło jest już wykorzystane";
				continue;
			}
		}
		break;
	}

	std::string answerStringChar = "";
	answerStringChar += choosedChar;
	return answerStringChar;
}

void game::gameInit(const int64_t playerId) {
	std::random_device rd;
	std::mt19937 gen(rd());

	// [0] = 50:50, [1] = phone, [2] = publicity
	std::array<bool, 3> resque = {true, true, true};

	for(int i = 0; i < 12; i++) {
		clearScreen();
		const auto optQuestion = getQuestion(i + 1);
		if(!optQuestion.has_value()) {
			std::cerr << "Nie można pobrać pytania, powrót do menu głównego za 5 sekund..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			mainMenu::showMenu(false);
			return;
		}

		std::array<std::string, 5> question = optQuestion.value();
		const std::string correctAnswerStr = question[1];
		std::shuffle(question.begin() + 1, question.end(), gen);

		// auto = std::array<std::string, 5>::iterator
		auto it = std::find(question.begin() + 1, question.end(), correctAnswerStr);
		if(it == question.end()) {
			std::cerr << "Wystąpił błąd wewnętrzny, powrót do menu głównego za 5 sekund..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			mainMenu::showMenu(false);
			return;
		}
		const int index = std::distance(question.begin(), it);
		const char correctAnswerChar = 'A' + index - 1;

		while(true) {
			clearScreen();
			gameUI::drawCombined(i + 1, question, resque);

			std::string answerStringChar = getAnswer(resque);
			if(answerStringChar == "exit") {
				mainMenu::showMenu(true);
				return;
			}

			char choosedChar = answerStringChar[0];

			if(choosedChar >= '1' && choosedChar <= '3') {
				std::string charString = "";
				charString += choosedChar;
				const int resqueChoice = std::stoi(charString) - 1;
				const std::string resqueType = (choosedChar == '1' ? "5050" : (choosedChar == '2' ? "phone" : "publicity"));
				if(useResque(playerId, resqueType)) {
					resque[resqueChoice] = false;
					if(resqueChoice == 0) {
						const int correctAnswerIndex = correctAnswerChar - 'A' + 1;
						std::vector<int> wrongInd;
						for(int j = 1; j <= 4; j++) {
							if(j != correctAnswerIndex) wrongInd.push_back(j);
						}
						std::shuffle(wrongInd.begin(), wrongInd.end(), gen);
						if(wrongInd.size() >= 2) {
							int idx1 = wrongInd[0];
							int idx2 = wrongInd[1];
							question[idx1] = "Odpowiedź usunięta";
							question[idx2] = "Odpowiedź usunięta";
						}
					}
					else {
						generateRescue(resqueChoice, correctAnswerChar);
						continue;
					}
				}
				else {
					std::cout << "Niestety wystąpił błąd i nie możesz użyć w tej chwili koła ratunkowego..." << std:: endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(5000));
				}
			}

			if(choosedChar >= 'A' && choosedChar <= 'D') {
				if(choosedChar == correctAnswerChar) {
					std::cout << "Gratulację, poprawna odpowiedź! Przechodzimy do pytania " << (i + 2) << std:: endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(5000));
				}
				else {
					std::cout << "Niestety, to jest niepoprawna odpowiedź, powrót do menu głównego..." << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(5000));
					mainMenu::showMenu(true);
				}
				break;
			}
		}
	}
}

void game::generateRescue(const int type, const char correct) {
	clearScreen();
	if(type == 1) {
		const int randomNum = getRandomC<int>(0, 9);
		bool displayCorrect = randomNum  > 0;

		std::random_device rd;
		std::mt19937 gen(rd());

		std::vector<char> v;
		const char ABCD[] = {'A', 'B', 'C', 'D'};
		for(int i = 0; i < 4; i++) {
			if(ABCD[i] == correct) continue;
			v.push_back(ABCD[i]);
		}
		std::shuffle(v.begin(), v.end(), gen);

		std::cout << "[Przyjaciel] Według mnie to na 90% poprawną odpowiedzią jest " << (displayCorrect ? correct : v[0]) << "." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		return;
	}
	else if(type == 2) {
		std::cout << "[Publiczność] Wyniki głosowania:" << std::endl;

		int correctAnswer = getRandomC<int>(40, 60);
		int remaining = 100 - correctAnswer;

		int cut1 = getRandomC<int>(0, remaining);
		int cut2 = getRandomC<int>(0, remaining);

		int low = std::min(cut1, cut2);
		int high = std::max(cut1, cut2);

		int w1 = low;
		int w2 = high - low;
		int w3 = remaining - high;

		std::vector<int> wrongPerc = {w1, w2, w3};

		for(int i = 0; i < 5; i++) {
			int m = getRandomC<int>(0, 2);
			int n = getRandomC<int>(0, 2);
			std::swap(wrongPerc[m], wrongPerc[n]);
		}

		int wrongIndexCounter = 0;
		char c = 'A';
		for(int i = 0; i < 4; i++) {
			int percent;
			if(c == correct) percent = correctAnswer;
			else {
				percent = wrongPerc[wrongIndexCounter];
				wrongIndexCounter++;
			}
			std::cout << c << ": " << percent << "%" << std::endl;
			c++;
		}

		std::cout << RESET << std::endl << "Naciśnij ENTER by powrócić" << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
		return;
	}
}