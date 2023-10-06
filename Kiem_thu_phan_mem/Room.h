#pragma once
#include <string>

class Room {
private:
    std::string type;
    double price;
    bool is_available;

public:
    Room(const std::string& type, double price);
    bool book();
    void release();
    bool available() const;
    std::string getType() const;
    double getPrice() const;
};
