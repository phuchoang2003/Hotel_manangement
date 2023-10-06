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
    Booking(const Customer& cust, Room* r, const std::string& in_date, const std::string& out_date);
    void confirm();
};
