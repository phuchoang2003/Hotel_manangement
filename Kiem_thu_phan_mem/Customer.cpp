#include "Customer.h"

Customer::Customer(const std::string& name, const std::string& email, const std::string& phone)
    : name(name), email(email), phone(phone) {}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getEmail() const {
    return email;
}

std::string Customer::getPhone() const {
    return phone;
}