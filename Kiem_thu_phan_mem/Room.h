// Room.h
#pragma once
#include <string>

class Room {
private:
    int id;
    std::string roomType;
    bool isBooked;
    double price;


public:
    Room(int id, const std::string& type, double price);
    double getPrice() const;
    void setPrice(double newPrice);

    int getID() const;
    bool available() const;
    std::string getType() const;
    std::string getBookingStatus() const;
    void book();
    void setBookingStatus(const std::string& status);
  

};
