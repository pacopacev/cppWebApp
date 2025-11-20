#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#ifdef _WIN32
    #include <libpq-fe.h>  // Windows
#else
    #include <postgresql/libpq-fe.h>  // Linux
#endif

#include <string>
#include <memory>
#include <iostream>  // Add this for std::cout

class DatabaseManager {
public:
    DatabaseManager();  // Add constructor
    ~DatabaseManager();
    
    bool connect();
    bool isConnected() const;
    bool validateUser(const std::string& username, const std::string& password);
    bool createUser(const std::string& username, const std::string& password, const std::string& email);
    
private:
    PGconn* connection_ = nullptr;  // Initialize to nullptr
    std::string connection_string_ = "host=pa-pgdimitrov-bfdb.j.aivencloud.com port=25464 dbname=defaultdb user=avnadmin password=AVNS_IONeg4MWBUESkCApRE9";
};

#endif // DATABASEMANAGER_H