#include "Booking.h"
#include "Notification.h"
#include <iostream>

Booking::Booking(const Customer& cust, Room* r, const std::string& in_date, const std::string& out_date)
    : customer(cust), room(r), check_in_date(in_date), check_out_date(out_date) {}

void Booking::confirm() {
    Notification::confirmBookingToCustomer(customer);
}
