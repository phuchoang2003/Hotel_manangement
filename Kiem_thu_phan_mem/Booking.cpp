#include "Booking.h"
#include "Notification.h"
#include <iostream>
#include <fstream>

Booking::Booking(const Customer& cust, const Room* r, const std::string& in_date, const std::string& out_date)
    : customer(cust), room(r), check_in_date(in_date), check_out_date(out_date) {}


void Booking::confirm() {
    Notification::confirmBookingToCustomer(customer);
}



void Booking::saveToFile() const {
    std::ofstream outFile("bookings.txt", std::ios::app); // append mode
    if (outFile.is_open()) {
        outFile << customer.getName() << ","
            << customer.getEmail() << ","
            << customer.getPhone() << ","
            << room->getType() << ","    
            << room->getID() << ","
            << check_in_date << ","
            << check_out_date << "\n";
        outFile.close();
    }
    else {
        std::cerr << "Unable to open file for writing!";
    }
}