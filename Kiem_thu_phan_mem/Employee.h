#pragma once
#include <string>

class Employee {
private:
    std::string username;
    std::string password;
public:
    Employee(const std::string& user, const std::string& pass);

    bool authenticate(const std::string& user, const std::string& pass) const;
};
