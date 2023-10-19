#include "Room.h"

Room::Room(int id, const std::string& type,double price) : id(id), roomType(type), isBooked(false),price(price) {} 

double Room::getPrice() const {
    return price;
}

void Room::setPrice(double newPrice) {
    price = newPrice;
}

int Room::getID() const {
    return id;
}

bool Room::available() const {
    return !isBooked;
}

std::string Room::getType() const {
    return roomType;
}

std::string Room::getBookingStatus() const {
    return isBooked ? "Booked" : "Available";
}

void Room::book() {
    if (!isBooked) {
        isBooked = true;
    }
}

void Room::setBookingStatus(const std::string& status) {
    isBooked = (status == "Booked");
}

