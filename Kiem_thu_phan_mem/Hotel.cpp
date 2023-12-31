﻿#include "Hotel.h"
#include "Booking.h"
#include <algorithm> 
#include "main_functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include "UsersManagement.h"
#include <iomanip>  


Hotel::Hotel() {
    if (!loadHotelData("hotel_data.txt")) {
        double singleRoomPrice = 100.00;
        double doubleRoomPrice = 150.00;
        int roomId = 1;
        for (int i = 0; i < 10; ++i) {
            rooms.push_back(Room(roomId, "Single", singleRoomPrice));
            roomId++;
        }

        for (int i = 0; i < 10; ++i) {
            rooms.push_back(Room(roomId, "Double", doubleRoomPrice));
            roomId++;
        }

        // Lưu dữ liệu vào file sau khi thêm phòng
        saveHotelData("hotel_data.txt");
    }
}





Room* Hotel::findAvailableRoom(const std::string& roomType) {
    clearScreen();
    for (Room& room : rooms) {
        if (room.getType() == roomType && room.available()) {
            return &room;
        }
    }
    return nullptr;
}

bool Hotel::bookRoom(const std::string& roomType) {
    clearScreen();
    Room* room = findAvailableRoom(roomType);
    if (room) {
        room->book();
        saveHotelData("hotel_data.txt");  // Lưu trạng thái sau khi đặt phòng
        return true;
    }
    return false;
}

void Hotel::showAllRooms() { 
        clearScreen();
        int bookedRooms = 0;
        int availableRooms = 0;

        std::cout << "List of all rooms: \n";
        for (const Room& room : rooms) {
            std::cout << "- Room ID: " << room.getID()
                << ", Type: " << room.getType()
                << ", Price: $" << room.getPrice()
                << ", Status: " << room.getBookingStatus() << "\n";

            if (room.getBookingStatus() == "Booked") {
                bookedRooms++;
            }
            else {
                availableRooms++;
            }
        }

        std::cout << "\nTotal booked rooms: " << bookedRooms << std::endl;
        std::cout << "Total available rooms: " << availableRooms << std::endl;

        std::cin.ignore();
        std::cin.get();
    

}



std::string Hotel::showAvailableRoomsOfType() {
    clearScreen();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string roomType;
    bool validRoomType = false;

    do {
        std::cout << "Enter room type (Single/Double): ";
        std::getline(std::cin, roomType);

        // Kiểm tra xem người dùng có nhập một kiểu phòng hợp lệ không
        if (roomType == "Single" || roomType == "Double") {
            validRoomType = true;
        }
        else {
            clearScreen();
            std::cout << "Invalid room type. Please enter again." << std::endl;
            continue;
        }

        int count = 0;
        std::cout << "Available " << roomType << " rooms: \n";
        for (const Room& room : rooms) {
            if (room.available() && room.getType() == roomType) {
                std::cout << "- Room ID: " << room.getID() << "\n";
                count++;
            }
        }

        if (count == 0) {
            std::cout << "No " << roomType << " rooms available.\n";
            validRoomType = false;  // Đặt lại trạng thái không hợp lệ để yêu cầu người dùng nhập lại
            std::cout << "Please choose another room type." << std::endl;
        }
    } while (!validRoomType);

    return roomType;  // Trả về loại phòng đã được chọn
}



bool Hotel::isRoomAvailable(int roomId, const std::string& roomType) const {
    for (const Room& room : rooms) {
        if (room.getID() == roomId && room.available() && room.getType() == roomType) {
            return true;
        }
    }
    return false;
}

void Hotel::bookRoomById(int roomId) {
    for (Room& room : rooms) {
        if (room.getID() == roomId && room.available()) {
            room.book();
            saveHotelData("hotel_data.txt");  // Lưu trạng thái sau khi đặt phòng
            break;
        }
    }
}

Room* Hotel::getRoomById(int roomId) {
    for (Room& room : rooms) {
        if (room.getID() == roomId) {
            return &room;
        }
    }
    return nullptr;
}




bool Hotel::loadHotelData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading!";
        return false;
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        // File trống
        return false;
    }

    rooms.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str, type, status;
        double price;
        std::getline(ss, id_str, ',');
        std::getline(ss, type, ',');
        ss >> price;
        std::getline(ss, status, ',');
        int id = std::stoi(id_str);
        Room room(id, type, price);
        room.setBookingStatus(status);
        rooms.push_back(room);
    }
    file.close();
    return true;
}


void Hotel::saveHotelData(const std::string& filename) {
    // Kiểm tra sự tồn tại của tệp
    std::ifstream checkFile(filename);
    if (!checkFile.good()) {
        std::cerr << "File does not exist!";
        return;
    }
    checkFile.close();

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing!";
        return;
    }

    for (const Room& room : rooms) {
        file << room.getID() << ","
            << room.getType() << ","
            << room.getPrice() << ","
            << room.getBookingStatus() << "\n";
    }

    file.close();
}





std::vector<int> Hotel::searchAvailableRooms(const std::string& checkInDate, const std::string& checkOutDate, const std::string& roomType, double minPrice,
    double maxPrice) {
    std::vector<int> availableRooms;

    // Populate the list with all rooms of the required type
    for (const Room& room : rooms) {
        if (room.getType() == roomType && room.getPrice() >= minPrice && room.getPrice() <= maxPrice) {
            availableRooms.push_back(room.getID());
        }
    }

    std::ifstream inFile("bookings.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open bookings.txt for reading!";
        return availableRooms;  // Return whatever we have till now
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string name, email, phone, rType, roomIdStr, bookedCheckIn, bookedCheckOut;

        std::getline(ss, name, ',');
        std::getline(ss, email, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, rType, ',');
        std::getline(ss, roomIdStr, ',');
        std::getline(ss, bookedCheckIn, ',');
        std::getline(ss, bookedCheckOut, ',');

        if (rType == roomType) {
            if (!((bookedCheckOut <= checkInDate) || (bookedCheckIn >= checkOutDate))) {
                availableRooms.erase(std::remove(availableRooms.begin(), availableRooms.end(), std::stoi(roomIdStr)), availableRooms.end());
            }
        }
    }

    inFile.close();
    return availableRooms;
}

double Hotel::getSingleRoomPrice() const {
    for (const Room& room : rooms) {
        if (room.getType() == "Single") {
            return room.getPrice();  
        }
    }
    return 0.0; 
}

double Hotel::getDoubleRoomPrice() const {
    for (const Room& room : rooms) {
        if (room.getType() == "Double") {
            return room.getPrice();  
        }
    }
    return 0.0;  
}



void Hotel::confirmBookingToCustomer(const Customer& customer) {
    clearScreen();

    std::cout << "-------------------------------------------\n";
    std::cout << "Email to " << customer.getEmail() << ":\n";
    std::cout << "Dear " << customer.getName() << ",\n";
    std::cout << "Your booking has been confirmed!\n";
    std::cout << "-------------------------------------------\n";
    std::cin.get();
}

Booking Hotel::gatherAndBookRoom() {
    std::string customer_name = promptForName();
    std::string customer_email = promptForValidGmail();
    std::string customer_phone = promptForPhoneNumber();

    std::string check_in_date, check_out_date;
    promptForValidDates(check_in_date, check_out_date);

    Customer customer(customer_name, customer_email, customer_phone);

    std::string chosenRoomType = showAvailableRoomsOfType();
    int roomId;
    bool validRoomId = false;

    do {
        std::cout << "Please enter the ID of the room you would like to book: ";
        std::cin >> roomId;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (isRoomAvailable(roomId, chosenRoomType)) {
            validRoomId = true;
        }
        else {
            std::cout << "Sorry, the selected room is not available or invalid ID. Please try again." << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    } while (!validRoomId);


    Room* chosenRoom = getRoomById(roomId);
    if (!chosenRoom) {
        std::cerr << "Error: Could not retrieve room details. Exiting..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        exit(1);
    }

    return Booking(customer, chosenRoom, check_in_date, check_out_date);
}


bool Hotel::finalizeBookingAndPayment(const Booking& booking, UserManager* userManager) {
    int roomId = booking.getRoom()->getID();

    // "Đặt" phòng trước khi tiến hành thanh toán
    Room* roomToBook = getRoomById(roomId);
    if (roomToBook) {
        roomToBook->setBookingStatus("Booked");
        saveHotelData("hotel_data.txt");
    }

    bool paymentSuccess = finalizePayment(roomId, booking.getCheckInDate(), booking.getCheckOutDate(), userManager, booking.getCustomer());

    if (paymentSuccess) {
        this->confirmBookingToCustomer(booking.getCustomer());
        booking.saveToFile();
        std::cin.ignore();
        std::cin.get();
        return true;
    }
    else {
        std::cout << "Sorry, the booking process was not successful. Please try again." << std::endl;
        std::cin.ignore();
        std::cin.get();

        // "Huỷ" việc đặt phòng và cập nhật tệp
        if (roomToBook) {
            roomToBook->setBookingStatus("Available");
            saveHotelData("hotel_data.txt");
        }

        return false;
    }
}



bool Hotel::finalizePayment(int roomId, const std::string& check_in_date, const std::string& check_out_date, UserManager* userManager, Customer customer) {
    bool paymentSuccess = this->processPayment(roomId, check_in_date, check_out_date, userManager);

    if (!paymentSuccess) {  // Thay đổi điều kiện ở đây
        std::cout << "Booking cancelled as payment was not processed." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return false;
    }
    else {  // Thay đổi điều kiện ở đây
        return true;
    }
}



bool Hotel::processPayment(int roomId, const std::string& checkInDate, const std::string& checkOutDate, UserManager* userManager) {
    int daysStayed = calculateDaysStayed(checkInDate, checkOutDate);
    const Room* desiredRoom = getRoomById(roomId);
    double roomPrice = desiredRoom->getPrice();

    double totalAmount = daysStayed * roomPrice;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total amount due for " << daysStayed << " day(s): $" << totalAmount << "\n";

    std::cout << "Would you like to proceed with the payment? (y/n): ";
    char paymentChoice;
    std::cin >> paymentChoice;

    if (paymentChoice == 'y' || paymentChoice == 'Y') {
        bool paymentSuccess = userManager->withdrawFromLoggedInUser(totalAmount);

        if (paymentSuccess) {
            clearScreen();
            for (int i = 0; i < 3; ++i) {
                std::cout << "Processing payment" << std::string(i + 1, '.') << "\r";
                std::cout.flush();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            clearScreen();
            std::cout << "Payment successful!    \n";
            std::cin.ignore();
            std::cin.get();
            return true;
        }
        else {
            clearScreen();
            double userBalance = userManager->getBalanceOfLoggedInUser();  
            if (userBalance < totalAmount) {
                std::cout << "Payment failed! Your balance is $" << userBalance << " which is insufficient. Required amount is $" << totalAmount << ".\n";
                std::cin.ignore();
                std::cin.get();
            }
            else {
                std::cout << "Payment failed! Check your account details or try again later.\n";
                std::cin.ignore();
                std::cin.get();
            }
            return false;
        }
    }
    else {
        return false;
    
    }
}