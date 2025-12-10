//
// Created by Hania Potępa on 02/12/2025.
//

#include "dbInit.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

// Void method that initializing database, It needs mysqlx::Session and database name as a std::string value
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
	if(recordsEmpty(session, "SELECT COUNT(*) FROM `questions`")) executeScriptFromFile(session, "./database/dbQuest.sql");
}

// Void method that execute SQL script from .sql file, it needs mysqlx::Session and file name as a std::string value
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

	std::cout << "[DB Initializer] Database initialized with " << fileName << "!" << std::endl;
}


// Method that checks table is empty, it needs mysqlx::Session and mysqlx::string as query value. Returning bool value
// Returns false when table is containing something and if it is error with database, true when it's empty
bool dbInit::recordsEmpty(mysqlx::Session &session, const mysqlx::string& query) {
	if(query.empty()) {
		std::cerr << "[DB Initializer] Query empty, returning false value" << std::endl;
		return false;
	}
	try {
		mysqlx::RowResult result = session.sql(query).execute();
		mysqlx::Row row = result.fetchOne();
		return row[0].get<int64_t>() == 0;
	}
	catch(const mysqlx::Error &err) {
		std::cerr << "[DB Initializer] Error during is table empty: " << err << std::endl;
		return false;
	}
}