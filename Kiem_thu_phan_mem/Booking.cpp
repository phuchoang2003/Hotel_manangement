#include "Booking.h"
#include <iostream>

Booking::Booking(const Customer& cust, Room* r, const std::string& in_date, const std::string& out_date)
    : customer(cust), room(r), check_in_date(in_date), check_out_date(out_date) {}

void Booking::confirm() {
    std::cout << "Thank you " << customer.getName() << "! Your booking for a " << room->getType() << " room has been confirmed from " << check_in_date << " to " << check_out_date << "." << std::endl;
}
