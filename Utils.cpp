#include "Utils.h"
#include <random>
#include <algorithm>
#include <regex>
#include <vector>  // ADD THIS LINE

std::string Utils::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&time);
    
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &local_time);
    return std::string(buffer);
}

std::string Utils::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&time);
    
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
    return std::string(buffer);
}

std::string Utils::formatDate(const std::string& format) {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&time);
    
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), format.c_str(), &local_time);
    return std::string(buffer);
}

std::string Utils::getVersion() {
    return "1.0.2";
}

bool Utils::isValidEmail(const std::string& email) {
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    return std::regex_match(email, pattern);
}

std::string Utils::toUpperCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Utils::generateRandomString(int length) {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);
    
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += chars[distribution(generator)];
    }
    return result;
}