#pragma once
#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include <string>
#include "Hotel.h"
#include <ctime>
#include <chrono>

bool isValidRoomType(const std::string& type);
std::string promptForName();
std::string promptForValidGmail();
void promptForValidDates(std::string& check_in_date, std::string& check_out_date);
//std::string promptForRoomType();
std::string promptForPhoneNumber();
bool isValidPhoneNumber(const std::string& phone);
bool isValidName(const std::string& name);
bool isValidNumberInput(const std::string& input);
//bool authenticateEmployee();
void searchForAvailableRooms(Hotel& hotel);
int calculateDaysStayed(const std::string& checkInDate, const std::string& checkOutDate);
double calculatePayment(const Hotel& hotel, const std::string& roomType, const std::string& checkInDate, const std::string& checkOutDate);

void clearScreen();

#endif // MAIN_FUNCTIONS_H
