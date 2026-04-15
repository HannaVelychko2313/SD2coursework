#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <regex>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class Validator {
public:
    // check if string is not empty
    static bool isNotEmpty(const std::string& input) {
        return !input.empty();
    }
    //name validation
    static bool isValidName(const std::string name){
        const std::regex pattern("^[A-Za-z]+(?:[ '-][A-Za-z]+)*$");
        return std::regex_match(name,pattern);
    }

    // phone validation (10-12 digits)
    static bool isValidPhone(const std::string& phone) {
        const std::regex pattern("^[0-9]{10,12}$");
        return std::regex_match(phone, pattern);
    }
    // basic date validation
    static bool isValidDate(const std::string& dateStr) {
        // Regex check for DD-MM-YYYY
        const std::regex pattern(R"(\d{2}-\d{2}-\d{4})");
        if (!std::regex_match(dateStr, pattern)) return false;

        std::tm t = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&t, "%d-%m-%Y");
        
        // if ss failes, the date islogically impossible (like 31-02-2024)
        return !ss.fail();
    }

    // chack that the date is not in the past
    static bool isFutureDate(const std::string& dateStr) {
        // Get current system time (midnight today)
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm today_tm = *std::localtime(&now_time);
        today_tm.tm_hour = 0; today_tm.tm_min = 0; today_tm.tm_sec = 0;
        std::time_t startOfToday = std::mktime(&today_tm);

        // Parse input DD-MM-YYYY
        std::tm input_tm = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&input_tm, "%d-%m-%Y");

        if (ss.fail()) return false; 
        
        std::time_t input_time = std::mktime(&input_tm);
        return input_time >= startOfToday;
    }

    // function overloading
    // check if value is non-negative
    static bool isNonNegative(double value) {
        return value>= 0;
    }
    static bool isNonNegative(int value) {
        return value>= 0;
    }
     // function overloading
    //check if value is positive
    static bool isPositive(double value) {
        return value>0;
    }
    static bool isPositive(int value) {
        return value>0;
    }
    //duration validation
    static bool isValidDuration(double duration){
        return duration <= 5.0;
    }
    //Item name validation
    static bool isValidItemName(string name){
    // regex pattern that allows letters, numbers, spaces, hyphens, and apostrophes, excludes the pipe '|'
    const std::regex pattern("^[A-Za-z0-9]+(?:[ '-][A-Za-z0-9]+)*$");
    return std::regex_match(name, pattern);
    }
};


#endif