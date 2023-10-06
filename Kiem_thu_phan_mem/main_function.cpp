#include "main_functions.h"
#include "DateValidation.h"
#include "GmailValidation.h"
#include <iostream>
#include <regex>

std::string promptForName() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    return name;
}


std::string promptForValidGmail() {
    std::string email;
    bool validGmail;
    do {
        std::cout << "Enter your Gmail address: ";
        std::cin >> email;

        validGmail = isValidGmail(email);
        if (!validGmail) {
            std::cout << "Invalid Gmail address. Please enter a valid Gmail address." << std::endl;
        }
    } while (!validGmail);
    return email;
}

void promptForValidDates(std::string& check_in_date, std::string& check_out_date) {
    do {
        std::cout << "Enter check-in date (YYYY-MM-DD): ";
        std::cin >> check_in_date;

        std::cout << "Enter check-out date (YYYY-MM-DD): ";
        std::cin >> check_out_date;

        if (!is_valid_date_format(check_in_date) || !is_valid_date_format(check_out_date)) {
            std::cout << "Invalid date format. Please try again." << std::endl;
            continue;
        }

        if (!is_valid_date_range(check_in_date, check_out_date)) {
            std::cout << "Check-out date cannot be before check-in date. Please try again." << std::endl;
            continue;
        }

        if (is_past_date(check_in_date)) {
            std::cout << "Check-in date cannot be in the past. Please try again." << std::endl;
            continue;
        }

        break;
    } while (true);
}

std::string promptForRoomType() {
    std::string room_type;
    std::cout << "Enter room type (Single/Double): ";
    std::cin >> room_type;
    return room_type;
}

bool isValidPhoneNumber(const std::string& phone) {
    return phone.length() == 10 && std::all_of(phone.begin(), phone.end(), ::isdigit);
}



std::string promptForPhoneNumber() {
    std::string phone;
    do {
        std::cout << "Enter your phone number: ";
        std::cin >> phone;

        if (!isValidPhoneNumber(phone)) {
            std::cout << "Invalid phone number. Please enter a valid phone number." << std::endl;
        }
        else {
            break;  // If phone number is valid, break out of the loop
        }
    } while (true);

    return phone;
}
