//
// Created by Hania Potępa on 04/12/2025.
//

#include "dbQuerys.h"
#include <iostream>
#include "./Database.h"
#include <optional> // requires C++ 17
#include <mysqlx/xdevapi.h>

std::optional<mysqlx::RowResult> dbQuerys::selRows(mysqlx::string queryString) {
	mysqlx::Session &session = Database::getInstance().getSession();;
	try {
		mysqlx::RowResult result = session.sql(queryString).execute();
		return result;
	}
	catch(const mysqlx::Error &err) {
		std::cerr << "[DB Query] Error while selecting rows: " << err.what() << std::endl;
		return std::nullopt;
	}
}