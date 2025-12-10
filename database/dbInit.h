/**
* @file dbInit.h
 * @author Hania Potępa
 * @date 02/12/2025
 * @brief Header file for database initialization utilities.
 */

#ifndef MIL_DBINIT_H
#define MIL_DBINIT_H

#include <string>
#include <mysqlx/xdevapi.h>

/**
 * @class dbInit
 * @brief A utility class responsible for initializing the database structure and content.
 * * Contains static methods to execute SQL scripts and verify if tables are populated.
 */
class dbInit {
public:
	/**
	 * @brief Initializes the database schema and default data.
	 * * This method sets up the necessary tables and seeds them with data if needed.
	 * @param session Reference to the active MySQL session.
	 * @param dbName The name of the database to initialize.
	 */
	static void init(mysqlx::Session &session, const std::string &dbName);

private:
	/**
	 * @brief Executes SQL commands loaded from an external file.
	 * * Helper method used to parse and run .sql scripts (e.g., schema creation).
	 * @param session Reference to the active MySQL session.
	 * @param fileName Path to the .sql file (as std::string).
	 */
	static void executeScriptFromFile(mysqlx::Session &session, const std::string &fileName);

	/**
	 * @brief Checks if a specific query returns any records (is empty).
	 * @param session Reference to the active MySQL session.
	 * @param query The SQL query string to execute (e.g., "SELECT * FROM table").
	 * @return True if the table/result set is empty.
	 * @return False if records exist OR if a database error occurred during the check.
	 */
	static bool recordsEmpty(mysqlx::Session &session, const mysqlx::string& query);
};

#endif // MIL_DBINIT_H