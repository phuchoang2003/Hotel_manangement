#include "Room.h"

Room::Room(const std::string& type, double price) : type(type), price(price), is_available(true) {}

bool Room::book() {
    if (is_available) {
        is_available = false;
        return true;
    }
    return false;
}

void Room::release() {
    is_available = true;
}

bool Room::available() const {
    return is_available;
}

std::string Room::getType() const {
    return type;
}

double Room::getPrice() const {
    return price;
}
