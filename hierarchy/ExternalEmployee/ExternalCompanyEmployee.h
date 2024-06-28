#pragma once
#include "User.h"

class ExternalEmployee: public User {
public:
    ExternalEmployee() = default;
    ExternalEmployee(const MyString& firstName, const MyString& lastName,
                     const MyString& EGN, size_t age, const MyString& password);
    ExternalEmployee(MyString&& firstName, MyString&& lastName,
                     MyString& EGN, size_t age, MyString&& password);
    void help() const;

    User* clone() const override {
        return new ExternalEmployee(*this);
    }
    void saveToFile(std::ofstream& ofs) const ;
    void readFromFile(std::ifstream& ifs);
};

