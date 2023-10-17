#include "Employee.h"

Employee::Employee(const std::string& user, const std::string& pass)
    : username(user), password(pass) {}

bool Employee::authenticate(const std::string& user, const std::string& pass) const {
    return username == user && password == pass;
}
