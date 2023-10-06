#pragma once
#include <vector>
#include "Room.h"
#include "Customer.h"

class Hotel {
private:
    std::vector<Room> rooms;

public:
    Hotel();
    Room* findAvailableRoom(const std::string& roomType);
    bool bookRoom(const std::string& roomType);
    void showAllRooms();
    void showAvailableRoomsOfType(const std::string& roomType);
    bool isRoomAvailable(int roomId) const;
    void bookRoomById(int roomId);
    const Room* getRoomById(int roomId) const;
    void loadHotelData(const std::string& filename);
    void saveHotelData(const std::string& filename);


};
