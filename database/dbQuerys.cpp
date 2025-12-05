//
// Created by Hania Potępa on 04/12/2025.
//

#include "dbQuerys.h"
#include <iostream>
#include "./Database.h"
#include <optional> // requires C++ 17
#include <mysqlx/xdevapi.h>

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