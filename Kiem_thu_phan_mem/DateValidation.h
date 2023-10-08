#pragma once
#ifndef DATEVALIDATION_H
#define DATEVALIDATION_H

#include <string>

bool is_valid_date_format(const std::string& date);
bool is_valid_date_range(const std::string& start_date, const std::string& end_date);
bool is_past_date(const std::string& date);

#endif // DATEVALIDATION_H 
