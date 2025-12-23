#include "PasswordUtils.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cctype>

// Simple hash using std::hash (NOT for production!)
std::string PasswordUtils::simpleHash(const std::string& input) {
    std::size_t hash = std::hash<std::string>{}(input);
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return ss.str();
}

std::string PasswordUtils::hashPassword(const std::string& password) {
    // Generate salt
    std::string salt = generateSalt(16);
    
    // Combine salt + password
    std::string salted = salt + password;
    
    // Simple hash (in production, use bcrypt or similar)
    std::string hash = simpleHash(salted);
    
    // Format: salt:hash
    return salt + ":" + hash;
}

bool PasswordUtils::verifyPassword(const std::string& password, const std::string& storedHash) {
    // Parse stored hash: salt:hash
    size_t colonPos = storedHash.find(':');
    if (colonPos == std::string::npos) return false;
    
    std::string salt = storedHash.substr(0, colonPos);
    std::string hash = storedHash.substr(colonPos + 1);
    
    // Recreate hash
    std::string salted = salt + password;
    std::string computedHash = simpleHash(salted);
    
    return computedHash == hash;
}

std::string PasswordUtils::generateSalt(size_t length) {
    const std::string charset = 
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, static_cast<int>(charset.size()) - 1);
    
    std::string salt;
    salt.reserve(length);
    
    for (size_t i = 0; i < length; ++i) {
        salt += charset[distribution(generator)];
    }
    
    return salt;
}

bool PasswordUtils::isPasswordStrong(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }
    
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    
    for (char c : password) {
        if (std::isupper(static_cast<unsigned char>(c))) hasUpper = true;
        else if (std::islower(static_cast<unsigned char>(c))) hasLower = true;
        else if (std::isdigit(static_cast<unsigned char>(c))) hasDigit = true;
        else if (!std::isspace(static_cast<unsigned char>(c))) hasSpecial = true;
    }
    
    // Require at least 3 of 4 criteria
    int criteriaMet = (hasUpper ? 1 : 0) + (hasLower ? 1 : 0) + 
                      (hasDigit ? 1 : 0) + (hasSpecial ? 1 : 0);
    
    return criteriaMet >= 3;
}