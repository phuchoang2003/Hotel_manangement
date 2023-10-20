#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string name;
    std::string email;
    std::string phone;
    //double accountBalance;


public:
    Customer(const std::string& name, const std::string& email, const std::string& phone/*, const double& accountBalance*/);
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    //void saveToFile() const;

};

#endif // CUSTOMER_H
