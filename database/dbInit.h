//
// Created by Hania Potępa on 02/12/2025.
//

#ifndef MIL_DBINIT_H
#define MIL_DBINIT_H

#include <string>
#include <mysqlx/xdevapi.h>

class dbInit {
public:
	static void init(mysqlx::Session &session, const std::string &dbName);

private:
	static void executeScriptFromFile(mysqlx::Session &session, const std::string &fileName);
	static bool recordsEmpty(mysqlx::Session &session, const mysqlx::string& query);
};


#endif