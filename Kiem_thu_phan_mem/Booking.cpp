#include "Booking.h"
#include <iostream>
#include <fstream>

Booking::Booking(const Customer& customer, Room* room, const std::string& check_in_date, const std::string& check_out_date)
    : customer(customer), room(room), check_in_date(check_in_date), check_out_date(check_out_date) {}
Customer Booking::getCustomer() const { return customer; }
Room* Booking::getRoom() const { return room; }
std::string Booking::getCheckInDate() const { return check_in_date; }
std::string Booking::getCheckOutDate() const { return check_out_date; }



void Booking::saveToFile() const {
    std::ofstream outFile("bookings.txt", std::ios::app); 
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