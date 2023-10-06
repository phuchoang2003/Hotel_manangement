// Room.h
#pragma once
#include <string>

class Room {
private:
    int id;
    std::string roomType;
    bool isBooked;

public:
    Room(int id, const std::string& type);

    int getID() const;
    bool available() const;
    std::string getType() const;
    std::string getBookingStatus() const;
    void book();
    void setBookingStatus(const std::string& status);
  

};
