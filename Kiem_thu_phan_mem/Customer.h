#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string name;
    std::string email;
    std::string phone;
public:
    Customer(const std::string& name, const std::string& email, const std::string& phone);
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
  

};

#endif // CUSTOMER_H
