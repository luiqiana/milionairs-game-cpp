//
// Created by Hania Potępa on 04/12/2025.
//

#include "dbQuerys.h"
#include <iostream>
#include "./Database.h"
#include <optional> // requires C++ 17
#include <mysqlx/xdevapi.h>

// Method to select rows from database, it needs query as mysqlx::string. Returning std::optional<mysqlx::RowResult> value
// Returns std::nullopt when error with database or returns mysqlx::RowResult when everything is fine
std::optional<mysqlx::RowResult> dbQuerys::selRows(mysqlx::string queryString) {
	mysqlx::Session &session = Database::getInstance().getSession();
	try {
		mysqlx::RowResult result = session.sql(queryString).execute();
		return result;
	}
	catch(const mysqlx::Error &err) {
		std::cerr << "[DB Query] Error while selecting rows: " << err.what() << std::endl;
		return std::nullopt;
	}
}

// Method to insert rows to database, it needs query as mysqlx::string. Returning int64_t
// Returns -1 when error with database or returns inserted line id when everything is fine
int64_t dbQuerys::insertLine(mysqlx::string queryString) {
	mysqlx::Session &session = Database::getInstance().getSession();
	try {
		mysqlx::SqlResult result = session.sql(queryString).execute();

		if(result.getAffectedItemsCount() == 0) return -1;

		return result.getAutoIncrementValue();
	}
	catch(const mysqlx::Error &err) {
		std::cerr << "[DB Query] Error while inserting lines: " << err.what() << std::endl;
		return -1;
	}
}

// Method to update rows in database, it needs query as mysqlx::string. Returning bool value
// Returns false when error with database or returns true when everything is fine
bool dbQuerys::updateLine(mysqlx::string queryString) {
	mysqlx::Session &session = Database::getInstance().getSession();
	try {
		mysqlx::SqlResult result = session.sql(queryString).execute();
		if(result.getAffectedItemsCount() == 0) return false;
		return true;
	}
	catch(const mysqlx::Error &err) {
		std::cerr << "[DB Query] Error while updating lines: " <<  err.what() << std::endl;
		return false;
	}
}