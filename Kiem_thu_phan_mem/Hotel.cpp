#include "Hotel.h"

Hotel::Hotel() {
    for (int i = 0; i < 5; ++i) {
        rooms.push_back(Room("Single", 50.0));
        rooms.push_back(Room("Double", 100.0));
    }
}

Room* Hotel::findAvailableRoom(const std::string& roomType) {
    for (Room& room : rooms) {
        if (room.getType() == roomType && room.available()) {
            return &room;
        }
    }
    return nullptr;
}

bool Hotel::bookRoom(const std::string& roomType) {
    Room* room = findAvailableRoom(roomType);
    if (room) {
        room->book();
        return true;
    }
    return false;
}
