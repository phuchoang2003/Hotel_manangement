﻿#include "Hotel.h"
#include "Booking.h"
#include <algorithm> // for std::remove

#include "main_functions.h"
#include <iostream>
#include <fstream>
#include <sstream>

Hotel::Hotel() {
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
        return true;
    }
    return false;
}

void Hotel::showAllRooms() {
    /*clearScreen(); 
    std::cout << "List of all rooms: \n";
    for (const Room& room : rooms) {
        std::cout << "- Room ID: " << room.getID()
            << ", Type: " << room.getType()
            << ", Status: " << room.getBookingStatus() << "\n";
    }
   
    std::cin.ignore();
    std::cin.get();*/


    
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


//void Hotel::showAvailableRoomsOfType(const std::string& roomType) {
//    clearScreen();
//    std::cout << "Available " << roomType << " rooms: \n";
//    int count = 0;
//    for (const Room& room : rooms) {
//        if (room.available() && room.getType() == roomType) {
//            std::cout << "- Room ID: " << room.getID() << "\n";
//            count++;
//        }
//    }
//    if (count == 0) {
//        std::cout << "No " << roomType << " rooms available.\n";
//    }
//    std::cin.ignore();
//    std::cin.get(); // Pause for user to read the list
//}

//void Hotel::showAvailableRoomsOfType() {
//    std::string roomType;
//    bool validRoomType = false;
//
//    do {
//        std::cout << "Enter room type (Single/Double): ";
//        std::getline(std::cin, roomType);
//
//        // Kiểm tra xem người dùng có nhập một kiểu phòng hợp lệ không
//        if (roomType == "Single" || roomType == "Double") {
//            validRoomType = true;
//        }
//        else {
//            clearScreen();
//            std::cout << "Invalid room type. Please enter again." << std::endl;
//            continue;
//        }
//
//        int count = 0;
//        std::cout << "Available " << roomType << " rooms: \n";
//        for (const Room& room : rooms) {
//            if (room.available() && room.getType() == roomType) {
//                std::cout << "- Room ID: " << room.getID() << "\n";
//                count++;
//            }
//        }
//
//        if (count == 0) {
//            std::cout << "No " << roomType << " rooms available.\n";
//            validRoomType = false;  // Force user to enter room type again
//        }
//
//    } while (!validRoomType);
//
//    std::cin.ignore();
//    std::cin.get(); // Pause for user to read the list
//}

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



bool Hotel::isRoomAvailable(int roomId) const {
    for (const Room& room : rooms) {
        if (room.getID() == roomId && room.available()) {
            return true;
        }
    }
    return false;
}

void Hotel::bookRoomById(int roomId) {
    for (Room& room : rooms) {
        if (room.getID() == roomId && room.available()) {
            room.book();
            break;
        }
    }
}

const Room* Hotel::getRoomById(int roomId) const {
    for (const Room& room : rooms) {
        if (room.getID() == roomId) {
            return &room;
        }
    }
    return nullptr;
}



void Hotel::loadHotelData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading!";
        return;
    }

    rooms.clear();  // clear the existing data

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str, type, status;
        double price;
        std::getline(ss, id_str, ',');
        std::getline(ss, type, ',');
        ss >> price;  // Read the price
        std::getline(ss, status, ',');
        int id = std::stoi(id_str);
        Room room(id, type, price);  // updated with price
        room.setBookingStatus(status);
        rooms.push_back(room);
    }
    file.close();
}

void Hotel::saveHotelData(const std::string& filename) {
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


void Hotel::searchCustomerByRoomIdFromFile() const {
    clearScreen();
    int roomId;
    std::cout << "Enter the Room ID to search for the customer: ";
    std::cin >> roomId;

    std::ifstream inFile("bookings.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open bookings.txt for reading!";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string name, email, phone, roomType, roomIdStr, checkInDate, checkOutDate;

        std::getline(ss, name, ',');
        std::getline(ss, email, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, roomType, ',');
        std::getline(ss, roomIdStr, ',');
        std::getline(ss, checkInDate, ',');
        std::getline(ss, checkOutDate, ',');

        if (std::stoi(roomIdStr) == roomId) {
            clearScreen();

            std::cout << "Customer Information for Room ID " << roomId << ":\n";
            std::cout << "Name: " << name << "\n";
            std::cout << "Email: " << email << "\n";
            std::cout << "Phone: " << phone << "\n";
            std::cout << "Room Type: " << roomType << "\n";
            std::cout << "Check-in Date: " << checkInDate << "\n";
            std::cout << "Check-out Date: " << checkOutDate << "\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            inFile.close();
            return;
        }
    }
    clearScreen();
    std::cout << "No booking found for Room ID " << roomId << ".\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    inFile.close();
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

