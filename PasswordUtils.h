#ifndef UTILS_PASSWORDUTILS_H
#define UTILS_PASSWORDUTILS_H

#include <string>

class PasswordUtils {
public:
    // Simple password hash (not cryptographically secure - for learning only)
    static std::string hashPassword(const std::string& password);
    
    // Verify password
    static bool verifyPassword(const std::string& password, const std::string& hash);
    
    // Generate random salt
    static std::string generateSalt(size_t length = 16);
    
    // Check password strength
    static bool isPasswordStrong(const std::string& password);
    
private:
    // Simple hash function for demonstration
    static std::string simpleHash(const std::string& input);
};

#endif // UTILS_PASSWORDUTILS_H