#include "DatabaseManager.h"
#include <iostream>
#include <cstring>

// DatabaseManager::DatabaseManager() : connection_(nullptr) {
//     // Update with your PostgreSQL credentials
//     // connection_string_ = "host=pa-pgdimitrov-bfdb.j.aivencloud.com port=25464 dbname=defaultdb user=avnadmin password=AVNS_IONeg4MWBUESkCApRE9";
// }
DatabaseManager::DatabaseManager() : connection_(nullptr) {
#ifdef _WIN32
    std::cout << "Running on Windows" << std::endl;
#elif __linux__
    std::cout << "Running on Linux" << std::endl;
#endif
}
DatabaseManager::~DatabaseManager() {
    if (connection_) {
        PQfinish(connection_);
        connection_ = nullptr;
    }
}

bool DatabaseManager::connect() {
    connection_ = PQconnectdb(connection_string_.c_str());
    
    if (PQstatus(connection_) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(connection_) << std::endl;
        PQfinish(connection_);
        connection_ = nullptr;
        return false;
    }
    
    std::cout << "Connected to PostgreSQL database successfully!" << std::endl;
    return true;
}

bool DatabaseManager::isConnected() const {
    return connection_ && PQstatus(connection_) == CONNECTION_OK;
}

bool DatabaseManager::validateUser(const std::string& username, const std::string& password) {
    if (!isConnected()) {
        std::cerr << "Database not connected" << std::endl;
        return false;
    }
    
    // Use parameterized query to prevent SQL injection
    const char* paramValues[2] = { username.c_str(), password.c_str() };
    std::cout << username << " " << password << std::endl;
    
    PGresult* res = PQexecParams(connection_,
        "SELECT id FROM users WHERE first_name = $1 AND password = $2",
        2,       // number of parameters
        NULL,    // parameter types (NULL = let PostgreSQL infer)
        paramValues,
        NULL,    // parameter lengths (NULL for text)
        NULL,    // parameter formats (NULL for text)
        0        // result format (0 = text)
    );
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "User validation failed: " << PQerrorMessage(connection_) << std::endl;
        PQclear(res);
        return false;
    }
    
    bool userExists = (PQntuples(res) > 0);
    PQclear(res);
    
    return userExists;
}

bool DatabaseManager::createUser(const std::string& username, const std::string& password, const std::string& email) {
    if (!isConnected()) {
        std::cerr << "Database not connected" << std::endl;
        return false;
    }
    
    const char* paramValues[3] = { username.c_str(), password.c_str(), email.c_str() };
    
    PGresult* res = PQexecParams(connection_,
        "INSERT INTO users (username, password_hash, email) VALUES ($1, crypt($2, gen_salt('bf')), $3)",
        3,       // number of parameters
        NULL,    // parameter types
        paramValues,
        NULL,    // parameter lengths
        NULL,    // parameter formats
        0        // result format
    );
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "User creation failed: " << PQerrorMessage(connection_) << std::endl;
        PQclear(res);
        return false;
    }
    
    PQclear(res);
    return true;
}