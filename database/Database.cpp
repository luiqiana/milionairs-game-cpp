//
// Created by Hania Potępa on 02/12/2025.
//

#include "Database.h"
#include <iostream>
#include <cstdlib>
#include "envLoader.h"
#include "dbInit.h"

// Constructor that load .env file and creates database session
Database::Database() {
	loadEnv();

	try {
		std::string host = getEnvVar("DB_HOST");
		std::string portStr = getEnvVar("DB_PORT");
		const int port = portStr.empty() ? 33060 : std::stoi(portStr);
		std::string user = getEnvVar("DB_USER");
		std::string pass = getEnvVar("DB_PASS");
		std::string dbNameEnv = getEnvVar("DB_NAME");
		this -> dbName = dbNameEnv.empty() ? "mil" : dbNameEnv;

		if(pass.empty()) throw std::runtime_error("No password in config (.env)");

		std::cout << "[DB] Connecting to " << host << "..." << std::endl;
		// Session closing automatically in unique_ptr
		session = std::make_unique<mysqlx::Session>(host, port, user, pass);
		std::cout << "[DB] Connected succefully!" << std::endl;

		dbInit::init(*session, dbName);
		std::cout << "[DB] Database ready!" << std::endl;

	}
	catch (const std::exception &e) {
		std::cerr << "[DB] System error: " << e.what() << std::endl;
		throw;
	}
	catch(const mysqlx::Error &err) {
		std::cerr << "[DB] MySQL error: " << err << std::endl;
		throw;
	}
}

// Destructor that closes database session
Database::~Database() {
	if(session) {
		session -> close();
		std::cout << "[DB] Connection closed!" << std::endl;
	}
}

// Method that returning mysqlx::Session
mysqlx::Session &Database::getSession() {
	if(!session) throw std::runtime_error("[DB] Session not found!");
	return *session;
}