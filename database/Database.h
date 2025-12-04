//
// Created by Hania Potępa on 02/12/2025.
//

#ifndef MIL_DATABASE_H
#define MIL_DATABASE_H

#include <string>
#include <mysqlx/xdevapi.h>
#include <memory>

class Database {
private:
	// Smart pointer on session (to loadout automatically)
	std::unique_ptr<mysqlx::Session> session;
	//std::string getEnvVar(const char *key);
	std::string dbName;
	Database();

public:
	~Database();

	Database(const Database&) = delete;
	Database &operator=(const Database&) = delete;

	// Methods to return active DB session
	mysqlx::Session &getSession();
	static Database &getInstance() {
		static Database instance;
		return instance;
	}
};


#endif