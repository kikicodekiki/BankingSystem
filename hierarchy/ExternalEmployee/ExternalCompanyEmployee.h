#pragma once
#include "User.h"
#include "MyString.h"
#include <random>



class ExternalEmployee : public User {
public:
    ExternalEmployee() = default;
    ExternalEmployee(const MyString& firstName, const MyString& lastName,
                            const MyString& EGN, size_t age, const MyString& password);
    ExternalEmployee(MyString&& firstName, MyString&& lastName,
            MyString& EGN, size_t age, MyString&& password);

    void send_check (double sum, const char* verificationCode, const MyString& EGN) ;
    void send_check (double sum, char*&& verificationCode, MyString&& EGN);

    void help() const;

    User* clone() const override {
        return new ExternalEmployee(*this);
    }
protected:
    void saveToFile(std::ofstream& ofs) const ;
    void readFromFile(std::ifstream& ifs) ;
private:
    const char* generateVerificationCode ();
};


