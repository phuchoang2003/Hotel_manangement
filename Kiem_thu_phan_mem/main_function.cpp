#include "main_functions.h"
#include "DateValidation.h"
#include "GmailValidation.h"
#include <iostream>
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
            clearScreen();

            std::cout << "Invalid date format. Please try again." << std::endl;
            continue;
        }

        if (!is_valid_date_range(check_in_date, check_out_date)) {
            clearScreen();

            std::cout << "Check-out date cannot be before check-in date. Please try again." << std::endl;
            continue;
        }

        if (is_past_date(check_in_date)) {
            clearScreen();

            std::cout << "Check-in date cannot be in the past. Please try again." << std::endl;
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

    // 1. Nhập thông tin từ người dùng
    std::string checkInDate, checkOutDate, roomType;
    double minPrice, maxPrice;
    std::cout << "Please enter your minimum price: ";
    std::cin >> minPrice;
    std::cin.ignore();  // clear the newline
    std::cout << "Please enter your maximum price: ";
    std::cin >> maxPrice;
    std::cin.ignore();
    std::cout << "Please enter your desired check-in date (e.g., YYYY-MM-DD): ";
    std::getline(std::cin, checkInDate);

    std::cout << "Please enter your desired check-out date (e.g., YYYY-MM-DD): ";
    std::getline(std::cin, checkOutDate);

    std::cout << "Please enter room type (Single/Double): ";
    std::getline(std::cin, roomType);

    // 2. Gọi hàm `searchAvailableRooms` để tìm các phòng trống.
    std::vector<int> availableRoomIDs = hotel.searchAvailableRooms(checkInDate, checkOutDate, roomType,minPrice,maxPrice);

    // 3. Hiển thị các phòng trống hoặc thông báo nếu không có phòng trống.
    if (availableRoomIDs.empty()) {
        std::cout << "Sorry, no rooms available for the given dates and room type.\n";
    }
    else {
        std::cout << "Available rooms for the given dates and room type are: \n";
        for (int id : availableRoomIDs) {
            std::cout << "Room ID: " << id << "\n";
        }
    }

    std::cout << "Press any key to continue...";
    std::cin.get();
}
