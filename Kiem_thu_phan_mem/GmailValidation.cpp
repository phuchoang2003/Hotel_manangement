#include "GmailValidation.h"
#include <regex>

bool isValidGmail(const std::string& email) {
    // Simple regex to match the Gmail format.
    // This doesn't cover all edge cases, but it's a good start.
    std::regex gmail_regex("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
    return std::regex_match(email, gmail_regex);
}
