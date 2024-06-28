#pragma once
#include "User.h"
#include "Messaging.h"
#include "BankCheck.h"

class Client : public User {
public:
    Client() = default;
    Client(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age, const MyString& password, const MyString& address);

    double getCheckSum(const MyString& verificationCode) const;
    void addCheck(const BankCheck& check);
    void addMessage(const MyString& message);
    void showMessages() const;

    void saveToFile(std::ofstream& ofs) const override;
    void readFromFile(std::ifstream& ifs) override;
    void help() const override;
    User* clone() const override;

    MyString getFullName() const {
        return name + " " + surname;
    }



private:
    MyString address;
    Vector<BankCheck> checks;
    Messaging messages;
};

