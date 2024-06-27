
#include "ExternalEmployee.h"


ExternalEmployee::ExternalEmployee(const MyString &firstName, const MyString &lastName,
                                   const MyString &EGN, size_t age,
                                   const MyString &password) :
                                   User(firstName, lastName, EGN, age, password){}


ExternalEmployee::ExternalEmployee(MyString &&firstName, MyString &&lastName,
                                   MyString &EGN, size_t age,
                                   MyString &&password) :
        User(std::move(firstName), std::move(lastName), std::move(EGN), age, std::move(password)){}


const char* ExternalEmployee::generateVerificationCode() {
    static int codeSize = 3;

    static const char symbolsToUse[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    char code[codeSize + 1];

    for (int i = 0; i < codeSize; i++) {
        code[i] = symbolsToUse[rand() % (sizeof(symbolsToUse) - 1)];
    }

    code [codeSize] = '\0';
    return code;
}


