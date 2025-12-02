//
// Created by Hania Potępa on 02/12/2025.
//

#include "dbInit.h"
#include <iostream>
#include <fstream>
#include <sstream>

void dbInit::init(mysqlx::Session &session, const std::string &dbName) {
	try {
		std::cout << "[DB Initializer] Initializing database..." << std::endl;

		session.sql("CREATE SCHEMA IF NOT EXISTS " + dbName + ";").execute();
		session.sql("USE " + dbName + ";").execute();
	}
	catch(const mysqlx::Error &err) {
		std::cerr << "[DB Initializer] Error: " << err << std::endl;
		throw;
	}

	executeScriptFromFile(session, "./database/dbSchem.sql");
}

void dbInit::executeScriptFromFile(mysqlx::Session &session, const std::string &fileName) {
	std::ifstream file(fileName);

	if(!file.is_open()) {
		std::cerr << "[DB Initializer] " << fileName << " not found!" << std::endl;
		return;
	}

	std::string line;
	std::string queryBuffer;

	while(std::getline(file, line)) {
		if(line.empty() || (line.size() >= 2 && line.substr(0, 2) == "--")) {
			continue;
		}

		queryBuffer += line + " ";
		if(line.find(';') != std::string::npos) {
			try {
				session.sql(queryBuffer).execute();
				queryBuffer.clear();
			}
			catch(const mysqlx::Error &err) {
				std::cerr << "[DB Initializer] Error in file " << fileName << ": " << queryBuffer << std::endl
				<< "Reason: " << err << std::endl;
				throw;
			}
		}
	}

	std::cout << "[DB Initializer] Database initialized!" << std::endl;
}