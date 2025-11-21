#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>
#include <ctime>

class Utils {
public:
    // Static methods - can be called without creating an instance
    static std::string getCurrentDate();
    static std::string getCurrentDateTime();
    static std::string formatDate(const std::string& format);
    static std::string getVersion();
    
    // Other utility functions
    static bool isValidEmail(const std::string& email);
    static std::string toUpperCase(const std::string& str);
    static std::string generateRandomString(int length);
};

#endif // UTILS_H