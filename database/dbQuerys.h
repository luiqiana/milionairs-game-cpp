//
// Created by Hania Potępa on 04/12/2025.
//

#ifndef MIL_DBQUERYS_H
#define MIL_DBQUERYS_H

#include <mysqlx/xdevapi.h>
#include <optional>

class dbQuerys {
public:
	static std::optional<mysqlx::RowResult> selRows(mysqlx::string query);
};


#endif //MIL_DBQUERYS_H