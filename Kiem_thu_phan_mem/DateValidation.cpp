#define _CRT_SECURE_NO_WARNINGS
#include "DateValidation.h"
#include <ctime>
#include <sstream>

bool is_valid_date_format(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    int year, month, day;
    std::stringstream ss(date);
    ss >> year;
    ss.ignore();
    ss >> month;
    ss.ignore();
    ss >> day;

    if (year < 2023 || year > 2024) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) return false;
    if (month == 2) {
        bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 29 || (!is_leap && day == 29)) return false;
    }

    return true;
}

bool is_valid_date_range(const std::string& start_date, const std::string& end_date) {
    return start_date <= end_date;
}

bool is_past_date(const std::string& date) {
    time_t now;
    struct tm newyear;
    double seconds;

    time(&now);  
    newyear = *localtime(&now);

    int year, month, day;
    std::stringstream ss(date);
    ss >> year;
    ss.ignore();
    ss >> month;
    ss.ignore();
    ss >> day;

    newyear.tm_hour = 0;
    newyear.tm_min = 0;
    newyear.tm_sec = 0;
    newyear.tm_year = year - 1900;
    newyear.tm_mon = month - 1;
    newyear.tm_mday = day;

    seconds = difftime(now, mktime(&newyear));

    return seconds > 0;
}
