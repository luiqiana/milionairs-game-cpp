/**
* @file dbQuerys.h
 * @author Hania Potępa
 * @date 04/12/2025
 * @brief Header file for the database query executor class.
 */

#ifndef MIL_DBQUERYS_H
#define MIL_DBQUERYS_H

#include <mysqlx/xdevapi.h>
#include <optional>
#include <cstdint>

/**
 * @class dbQuerys
 * @brief A static utility class for executing raw SQL queries.
 * * This class provides a simplified interface for standard CRUD operations
 * (SELECT, INSERT, UPDATE) using the mysqlx library.
 */
class dbQuerys {
public:
	/**
	 * @brief Executes a SELECT query to retrieve rows from the database.
	 * @param queryString The SQL query string to be executed.
	 * @return std::optional<mysqlx::RowResult> containing the result set if successful,
	 * or std::nullopt if a database error occurred.
	 */
	static std::optional<mysqlx::RowResult> selRows(mysqlx::string queryString);

	/**
	 * @brief Executes an INSERT query to add new rows to the database.
	 * @param queryString The SQL INSERT statement.
	 * @return The ID of the inserted row (int64_t) if successful,
	 * or -1 if a database error occurred.
	 */
	static int64_t insertLine(mysqlx::string queryString);

	/**
	 * @brief Executes an UPDATE query to modify existing records.
	 * @param queryString The SQL UPDATE statement.
	 * @return True if the update operation was successful, False otherwise.
	 */
	static bool updateLine(mysqlx::string queryString);
};

#endif //MIL_DBQUERYS_H