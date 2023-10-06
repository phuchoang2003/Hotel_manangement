#pragma once
#include <string>
#include "Customer.h"
#include "Room.h"

class Booking {
private:
    Customer customer;
    const Room* room;
    std::string check_in_date;
    std::string check_out_date;

public:
    Booking(const Customer& customer, const Room* room, const std::string& checkIn, const std::string& checkOut);
    void confirm();
    void saveToFile() const;

};
