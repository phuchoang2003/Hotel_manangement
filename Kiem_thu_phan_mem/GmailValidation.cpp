#include "GmailValidation.h"
#include <regex>

bool isValidGmail(const std::string& email) {
    std::regex gmail_regex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    return std::regex_match(email, gmail_regex);
}
