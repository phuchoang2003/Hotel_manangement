#include "Hotel.h"
#include "main_functions.h"
#include <iostream>

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
