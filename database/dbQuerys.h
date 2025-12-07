//
// Created by Hania Potępa on 04/12/2025.
//

#ifndef MIL_DBQUERYS_H
#define MIL_DBQUERYS_H

#include <mysqlx/xdevapi.h>
#include <optional>
#include <cstdint>

class dbQuerys {
public:
	static std::optional<mysqlx::RowResult> selRows(mysqlx::string queryString);
	static int64_t insertLine(mysqlx::string queryString);
	static bool updateLine(mysqlx::string queryString);
};


#endif //MIL_DBQUERYS_H