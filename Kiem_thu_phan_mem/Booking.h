#pragma once
#include <string>
#include "Customer.h"
#include "Room.h"

class Booking {
private:
    Customer customer;
    Room* room;
    std::string check_in_date;
    std::string check_out_date;

public:
    Booking(const Customer& customer, Room* room, const std::string& check_in_date, const std::string& check_out_date);
    Customer getCustomer() const;
    Room* getRoom() const;
    std::string getCheckInDate() const;
    std::string getCheckOutDate() const;
    void saveToFile() const;
};

