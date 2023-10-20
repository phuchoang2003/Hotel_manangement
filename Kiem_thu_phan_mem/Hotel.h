#pragma once
#include <vector>
#include "Room.h"
#include "Customer.h"
#include "Booking.h"
#include "UsersManagement.h"

class Hotel {
private:
    std::vector<Room> rooms;

public:
    Hotel();
    void confirmBookingToCustomer(const Customer& customer);
    // get
    double getSingleRoomPrice() const;
    double getDoubleRoomPrice() const;
    Room* getRoomById(int roomId)  ;
    bool isRoomAvailable(int roomId) const;
    
    
    //book
    void bookRoomById(int roomId);
    bool bookRoom(const std::string& roomType);

    //show
    void showAllRooms();
    std::string showAvailableRoomsOfType();

    //search
    Room* findAvailableRoom(const std::string& roomType);
    std::vector<int> searchAvailableRooms(const std::string& checkInDate, const std::string& checkOutDate, const std::string& roomType, double minPrice, double maxPrice);
    void searchForAvailableRooms(Hotel& hotel);
   
    
    // Payment
    bool finalizePayment(int roomId, const std::string& check_in_date, const std::string& check_out_date, UserManager* userManager, Customer customer);
    Booking gatherAndBookRoom();
    bool finalizeBookingAndPayment(const Booking& booking, UserManager* userManager);
    bool processPayment(int roomId, const std::string& checkInDate, const std::string& checkOutDate, UserManager* userManager);
    
    
    
    // Data
    bool loadHotelData(const std::string& filename);
    void saveHotelData(const std::string& filename);
    
    



};
