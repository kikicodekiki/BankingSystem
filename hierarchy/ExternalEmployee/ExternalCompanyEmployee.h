#pragma once
#include "User.h"
#include "IExternalEmployee.h"
#include "MyString.h"
#include <random>



class ExternalEmployee : public User, virtual public IExternalEmployee {
public:
    ExternalEmployee() = default;
    ExternalEmployee(const MyString& firstName, const MyString& lastName,
                            const MyString& EGN, size_t age, const MyString& password);
    ExternalEmployee(MyString&& firstName, MyString&& lastName,
            MyString& EGN, size_t age, MyString&& password);

    void send_check (double sum, const char* verificationCode, const MyString& EGN) override;
    void send_check (double sum, char*&& verificationCode, MyString&& EGN) override;

    void help() const override;

    User* clone() const override {
        return new ExternalEmployee(*this);
    }
protected:
    void saveToFile(std::ofstream& ofs) const override;
    void readFromFile(std::ifstream& ifs) override;
private:
    const char* generateVerificationCode ();
};


