#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <libpq-fe.h>  // Use libpq instead of pqxx
#include <string>
#include <memory>

class DatabaseManager {
public:
    // DatabaseManager();
    ~DatabaseManager();
    
    bool connect();
    bool isConnected() const;
    bool validateUser(const std::string& username, const std::string& password);
    bool createUser(const std::string& username, const std::string& password, const std::string& email);
    
private:
    PGconn* connection_;  // libpq connection object
    std::string connection_string_ = "host=pa-pgdimitrov-bfdb.j.aivencloud.com port=25464 dbname=defaultdb user=avnadmin password=AVNS_IONeg4MWBUESkCApRE9";
};

#endif // DATABASEMANAGER_H