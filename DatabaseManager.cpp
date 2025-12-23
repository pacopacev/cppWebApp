#include "DatabaseManager.h"
#include <iostream>
#include <cstring>

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



bool DatabaseManager::validateUser(const std::string& username, const std::string& password, int& userId) {
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
    /////
    // 2. Check how many rows were returned
    int rowCount = PQntuples(res);
    printf("Number of rows returned: %d\n", rowCount);

if (rowCount > 0) {
    // 3. Process the results
    for (int i = 0; i < rowCount; i++) {
        // Get the id value from the first column (column index 0)
        char* id_str = PQgetvalue(res, i, 0);
        printf("User ID: %s\n", id_str);
        userId = std::stoi(id_str);
        
        // You can also get other columns if you selected more
        // char* firstName = PQgetvalue(res, i, 1); // if you had first_name in SELECT
    }
} else {
    printf("No users found with the given credentials.\n");
}
   

    ///////
    bool userExists = (PQntuples(res) > 0);
    PQclear(res);
    
    if (!userExists) {
        return false;
    }
   
    return true;
}

bool DatabaseManager::createUser(const std::string& username, const std::string& email, const std::string& hashedPassword) {
    std::cout << "Creating user: " << username << " " << hashedPassword << " " << email << std::endl;
    if (!isConnected()) {
        std::cerr << "Database not connected" << std::endl;
        return false;
    }
    std::cout << "Creating user1: " << username << " " << hashedPassword << " " << email << std::endl;
    
    const char* paramValues[3] = { username.c_str(), hashedPassword.c_str(), email.c_str() };
    
    PGresult* res = PQexecParams(connection_,
        "INSERT INTO users (first_name, password, email) VALUES ($1, $2, $3)",
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