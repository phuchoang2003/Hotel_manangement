#pragma once
#include <vector>
#include "Room.h"

class Hotel {
private:
    std::vector<Room> rooms;

public:
    Hotel();
    Room* findAvailableRoom(const std::string& roomType);
    bool bookRoom(const std::string& roomType);
    void showAllRooms();
    void showAvailableRoomsOfType(const std::string& roomType);

};
