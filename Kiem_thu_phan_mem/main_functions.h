#pragma once
#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include <string>

std::string promptForName();
std::string promptForValidGmail();
void promptForValidDates(std::string& check_in_date, std::string& check_out_date);
std::string promptForRoomType();
std::string promptForPhoneNumber();
bool isValidPhoneNumber(const std::string& phone);

#endif // MAIN_FUNCTIONS_H