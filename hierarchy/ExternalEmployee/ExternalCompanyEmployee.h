#pragma once
#include "IExternalCompanyEmployee.h"
#include "User.h"
#include "Pair.h"
#include <random>
#include <cstring>

struct BankCheck{
    char verificationCode[3];
    double sum;

    BankCheck(const char* code, double sum) {
        strcpy(verificationCode, code);

        this->sum = sum;
    }
};



class ExternalCompanyEmployee : public User, public virtual IExternalEmployee{
public :
    ExternalCompanyEmployee(const MyString& firstName, const MyString& lastName,
                            const MyString& EGN, int age, const MyString& password);
    ExternalCompanyEmployee(MyString&& firstName, MyString&& lastName,
                            MyString& EGN, int age, MyString&& password);

    ExternalCompanyEmployee() = default;


    void send_check (double sum, const MyString& bankName, const MyString& EGN) override;
    void send_check (double sum, MyString&& bankName, MyString&& EGN) override;

protected:
    void saveToFile(std::ofstream ofs) const override;
    void readFromFile(std::ifstream& ifs) override;
private:
    const char* generateVerificationCode ();
};

