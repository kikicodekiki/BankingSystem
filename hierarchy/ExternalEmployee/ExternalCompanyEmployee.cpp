#include "ExternalCompanyEmployee.h"
#include <iostream>
#include <ctime>
#include <fstream>

//ExternalCompanyEmployee::ExternalCompanyEmployee(const MyString& firstName, const MyString& lastName, int age, const MyString& password)
//        : User(firstName, lastName, age, password) {}
//
//ExternalCompanyEmployee::ExternalCompanyEmployee(MyString&& firstName, MyString&& lastName, int age, MyString&& password)
//        : User(std::move(firstName), std::move(lastName), age, std::move(password)) {}

const char* ExternalCompanyEmployee::generateVerificationCode() {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    char code[4];
    for (int i = 0; i < 3; ++i) {
        code[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    code[3] = '\0';
    return code;
}

void ExternalCompanyEmployee::send_check(double sum, const MyString& bankName, const MyString& EGN) {
    const char* code = generateVerificationCode();
    BankCheck check = { code, sum };

    // Send the check to the bank (assuming a method exists in the application to handle this)
    // For now, we will just print the details
    std::cout << "Sending check to " << bankName << " for customer with EGN " << EGN << " of amount " << sum << " with code " << code << std::endl;

    // should add the check to the bank/customer in the application
    // For example:
    // app.addCheckToCustomer(bankName, EGN, check);

    // Also send a message to the customer
    // app.sendMessageToCustomer(EGN, "You have received a check of amount " + std::to_string(sum) + " with verification code " + code);
}

void ExternalCompanyEmployee::saveToFile(std::ofstream& ofs) const {
    User::saveToFile(ofs);
}

void ExternalCompanyEmployee::readFromFile(std::ifstream& ifs) {
    User::readFromFile(ifs);
}
