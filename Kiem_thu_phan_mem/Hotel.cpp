#include "Hotel.h"
#include "main_functions.h"
#include <iostream>
#include <fstream>
#include <sstream>

Hotel::Hotel() {
    int roomId = 1;

    for (int i = 0; i < 10; ++i) {
        rooms.push_back(Room(roomId, "Single"));  
        roomId++;
    }

    for (int i = 0; i < 10; ++i) {
        rooms.push_back(Room(roomId, "Double"));  
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
    clearScreen(); 
    std::cout << "List of all rooms: \n";
    for (const Room& room : rooms) {
        std::cout << "- Room ID: " << room.getID()
            << ", Type: " << room.getType()
            << ", Status: " << room.getBookingStatus() << "\n";
    }
   
    std::cin.ignore();
    std::cin.get();
}


void Hotel::showAvailableRoomsOfType(const std::string& roomType) {
    clearScreen();
    std::cout << "Available " << roomType << " rooms: \n";
    int count = 0;
    for (const Room& room : rooms) {
        if (room.available() && room.getType() == roomType) {
            std::cout << "- Room ID: " << room.getID() << "\n";
            count++;
        }
    }
    if (count == 0) {
        std::cout << "No " << roomType << " rooms available.\n";
    }
    std::cin.ignore();
    std::cin.get(); // Pause for user to read the list
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
        std::getline(ss, id_str, ',');
        std::getline(ss, type, ',');
        std::getline(ss, status, ',');
        int id = std::stoi(id_str);
        Room room(id, type);
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
            << room.getBookingStatus() << "\n";
    }

    file.close();
}