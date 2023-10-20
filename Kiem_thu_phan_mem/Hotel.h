#pragma once
#include <vector>
#include "Room.h"
#include "Customer.h"
#include "UsersManagement.h"

class Hotel {
private:
    std::vector<Room> rooms;

public:
    Hotel();
    void confirmBookingToCustomer(const Customer& customer);
    double getSingleRoomPrice() const;
    double getDoubleRoomPrice() const;
    Room* findAvailableRoom(const std::string& roomType);
    bool bookRoom(const std::string& roomType);
    void showAllRooms();
    std::string showAvailableRoomsOfType();
    void finalizePayment(int roomId, const std::string& check_in_date, const std::string& check_out_date, UserManager* userManager, Customer customer);
    bool isRoomAvailable(int roomId) const;
    std::vector<int> searchAvailableRooms(const std::string& checkInDate, const std::string& checkOutDate, const std::string& roomType, double minPrice, double maxPrice);
    void searchForAvailableRooms(Hotel& hotel);
    void bookRoomById(int roomId);
    const Room* getRoomById(int roomId) const;
    bool processPayment(int roomId, const std::string& checkInDate, const std::string& checkOutDate, UserManager* userManager);
    void loadHotelData(const std::string& filename);
    void saveHotelData(const std::string& filename);
    



};
