#include "main_functions.h"
#include "DateValidation.h"
#include "GmailValidation.h"
#include <limits>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <regex>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <cctype> 

bool isValidName(const std::string& name) {
    for (char c : name) {
        if (!std::isalpha(c) && c != ' ') {  
            return false;
        }
    }
    return true;
}


std::string promptForName() {
    std::string name;
    do {
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    if (!isValidName(name)) {
        clearScreen();

        std::cout << "Your name is not valid. Please enter your name again! " << std :: endl;

    }
    } while (!isValidName(name));
    return name;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string promptForValidGmail() {
    std::string email;
    bool validGmail;
    do {
        std::cout << "Enter your Gmail address: ";
        std::cin >> email;

        validGmail = isValidGmail(email);
        if (!validGmail) {
            clearScreen();

            std::cout << "Invalid Gmail address. Please enter a valid Gmail address." << std::endl;
        }
    } while (!validGmail);
    return email;
}

void promptForValidDates(std::string& check_in_date, std::string& check_out_date) {
    do {
        clearScreen();

        std::cout << "Enter check-in date (YYYY-MM-DD): ";
        std::cin >> check_in_date;

        std::cout << "Enter check-out date (YYYY-MM-DD): ";
        std::cin >> check_out_date;

        if (!is_valid_date_format(check_in_date) || !is_valid_date_format(check_out_date)) {
            std::cout << "Invalid date format. Please try again." << std::endl;
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        if (!is_valid_date_range(check_in_date, check_out_date)) {
            std::cout << "Check-out date cannot be before check-in date. Please try again." << std::endl;
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        if (is_past_date(check_in_date)) {
            std::cout << "Check-in date cannot be in the past. Please try again." << std::endl;
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        break;
    } while (true);
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
            clearScreen();

            std::cout << "Invalid phone number. Please enter a valid phone number." << std::endl;
        }
        else {
            break;  // If phone number is valid, break out of the loop
        }
    } while (true);

    return phone;
}

void searchForAvailableRooms(Hotel& hotel) {
    clearScreen();

    // input
    std::string input;
    std::string checkInDate, checkOutDate, roomType;
    double minPrice, maxPrice;

    // price
    std::cout << "Please enter minimum price: ";
    std::getline(std::cin, input);
    while (!isValidNumberInput(input)) {
        std::cout << "Invalid input. Please enter a valid number for minimum price: ";
        std::getline(std::cin, input);
    }
    minPrice = std::stod(input);

    std::cout << "Please enter maximum price: ";
    std::getline(std::cin, input);
    while (!isValidNumberInput(input)) {
        std::cout << "Invalid input. Please enter a valid number for maximum price: ";
        std::getline(std::cin, input);
    }
    maxPrice = std::stod(input);

    // date
    while (true) {
        std::cout << "Please enter your desired check-in date (e.g., YYYY-MM-DD): ";
        std::getline(std::cin, checkInDate);
        if (!is_valid_date_format(checkInDate)) {
            std::cout << "Invalid date format. Please enter in the format YYYY-MM-DD.\n";
        }
        else if (is_past_date(checkInDate)) {
            std::cout << "You've entered a past date for check-in. Please enter a future date.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "Please enter your desired check-out date (e.g., YYYY-MM-DD): ";
        std::getline(std::cin, checkOutDate);
        if (!is_valid_date_format(checkOutDate)) {
            std::cout << "Invalid date format. Please enter in the format YYYY-MM-DD.\n";
        }
        else if (is_past_date(checkOutDate)) {
            std::cout << "You've entered a past date for check-out. Please enter a future date.\n";
        }
        else if (!is_valid_date_range(checkInDate, checkOutDate)) {
            std::cout << "Check-out date is before check-in date. Please re-enter.\n";
        }
        else {
            break;
        }
    }

    // room type
    std::cout << "Please enter room type (Single/Double): ";
    std::getline(std::cin, roomType);

    if (!isValidRoomType(roomType)) {
        std::cout << "Invalid room type entered. We only offer Single and Double rooms.\n";
        std::cout << "Press any key to continue...";
        std::cin.get();
        return;
    }

    std::vector<int> availableRoomIDs = hotel.searchAvailableRooms(checkInDate, checkOutDate, roomType, minPrice, maxPrice);

    double singleRoomPrice = hotel.getSingleRoomPrice();
    double doubleRoomPrice = hotel.getDoubleRoomPrice();

    if ((minPrice > doubleRoomPrice) || (maxPrice < singleRoomPrice)) {
        std::cout << "There are no rooms available within the specified price range.\n";
        std::cout << "Price of Single Room: " << singleRoomPrice << "\n";
        std::cout << "Price of Double Room: " << doubleRoomPrice << "\n";
        std::cout << "Please choose a valid price range based on the room prices provided.\n";
        std::cin.get();
        return;
    }

    if (availableRoomIDs.empty()) {
        std::cout << "Sorry, no rooms match your search criteria.\n";
    }
    else {
        std::cout << "Available rooms based on your search criteria: \n";
        for (int id : availableRoomIDs) {
            std::cout << "Room ID: " << id << "\n";
        }
    }

    std::cout << "Press any key to continue...";
    std::cin.get();
}



bool isValidNumberInput(const std::string& input) {
    for (char ch : input) {
        if (!std::isdigit(ch) && ch != '.') {
            return false;
        }
    }
    return true;
}


bool isValidRoomType(const std::string& type) {
    return (type == "Single" || type == "Double");
}




int calculateDaysStayed(const std::string& checkInDate, const std::string& checkOutDate) {
    struct std::tm in = {}, out = {};
    std::istringstream ssIn(checkInDate), ssOut(checkOutDate);
    ssIn >> std::get_time(&in, "%Y-%m-%d");
    ssOut >> std::get_time(&out, "%Y-%m-%d");

    auto in_time_t = std::mktime(&in);
    auto out_time_t = std::mktime(&out);

    

    auto duration = std::chrono::system_clock::from_time_t(out_time_t) - std::chrono::system_clock::from_time_t(in_time_t);
    return std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
}


double calculatePayment(const Hotel& hotel, const std::string& roomType, const std::string& checkInDate, const std::string& checkOutDate) {
    int days = calculateDaysStayed(checkInDate, checkOutDate);
    double roomPrice = (roomType == "Single") ? hotel.getSingleRoomPrice() : hotel.getDoubleRoomPrice();
    return roomPrice * days;
}