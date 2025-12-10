/**
 * @file Database.h
 * @author Hania Potępa
 * @date 02/12/2025
 * @brief Header file for the Database singleton class managing MySQL connections.
 */

#ifndef MIL_DATABASE_H
#define MIL_DATABASE_H

#include <string>
#include <mysqlx/xdevapi.h>
#include <memory>

/**
 * @class Database
 * @brief A Singleton class responsible for handling the MySQL database connection.
 * * This class establishes a session with the database using the mysqlx library.
 * The Singleton pattern ensures that only one database connection instance exists
 * throughout the application's lifecycle, optimizing resource usage.
 */
class Database {
private:
    /// @brief Unique smart pointer to the database session. Automatically handles memory deallocation.
    std::unique_ptr<mysqlx::Session> session;

    /// @brief Stores the name of the database.
    std::string dbName;

    /**
     * @brief Private constructor (Singleton pattern).
     * * Loads configuration settings (e.g., from a .env file) and establishes
     * the initial connection session with the MySQL server.
     */
    Database();

public:
    /**
     * @brief Destructor.
     * Safely closes the database session and releases associated resources.
     */
    ~Database();

    /**
     * @brief Deleted copy constructor.
     * Prevents the creation of a copy of the Database instance, ensuring uniqueness.
     */
    Database(const Database&) = delete;

    /**
     * @brief Deleted assignment operator.
     * Prevents assigning one Database instance to another to enforce the Singleton pattern.
     */
    Database &operator=(const Database&) = delete;

    /**
     * @brief Retrieves the active database session.
     * * This method allows other parts of the application to execute SQL queries
     * using the established connection.
     * * @return A reference to the current mysqlx::Session object.
     */
    mysqlx::Session &getSession();

    /**
     * @brief Gets the single instance of the Database class.
     * * Uses lazy initialization to create the instance upon the first call.
     * * @return A reference to the static Database instance.
     */
    static Database &getInstance() {
       static Database instance;
       return instance;
    }
};

#endif // MIL_DATABASE_H