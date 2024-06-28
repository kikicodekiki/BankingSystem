
#include "Client.h"

#include <iostream>
#include <fstream>

Client::Client(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age,
               const MyString& password, const MyString& address)
        : User(firstName, surname, EGN, age, password), address(address) {}

double Client::getCheckSum(const MyString& verificationCode) const {
    for (size_t i = 0; i < checks.getSize(); ++i) {
        if (checks[i].getVerificationCode() == verificationCode) {
            return checks[i].getSum();
        }
    }
    throw std::runtime_error("Check not found.");
}

void Client::addCheck(const BankCheck& check) {
    checks.pushBack(check);
    MyString message = "You have a check assigned with code " + MyString(check.getVerificationCode());
    addMessage(message);
}

void Client::addMessage(const MyString& message) {
    messages.sendMessage(this->getFullName(), message);
}

void Client::showMessages() const {
    Vector<MyString> msgs = messages.getMessages(this->getFullName());

    size_t size = msgs.getSize();

    for (int i = 0; i < size; i++) {
        std::cout << msgs[i].c_str() << '\n';
    }

}

void Client::saveToFile(std::ofstream& ofs) const {
    User::saveToFile(ofs);
    address.saveToFile(ofs);
    size_t checksCount = checks.getSize();
    ofs.write((const char*)&checksCount, sizeof(checksCount));
    for (size_t i = 0; i < checksCount; ++i) {
        ofs.write(checks[i].getVerificationCode(), 4);
        //ofs.write((const char*)(&checks[i].getSum()), sizeof(checks[i].getSum()));
    }
}

void Client::readFromFile(std::ifstream& ifs) {
    User::readFromFile(ifs);
    address.readFromFile(ifs);
    size_t checksCount;
    ifs.read((char*)&checksCount, sizeof(checksCount));
    for (size_t i = 0; i < checksCount; ++i) {
        char code[4];
        double sum;
        ifs.read(code, 4);
        ifs.read((char*)&sum, sizeof(sum));
        checks.pushBack(BankCheck(code, sum));
    }
}

void Client::help() const {
    std::cout << "Client Help: \n";
    std::cout << "1. check_avl [bank_name] [account_number]\n";
    std::cout << "2. open [bank_name]\n";
    std::cout << "3. close [bank_name] [account_number]\n";
    std::cout << "4. redeem [bank_name] [account_number] [verification_code]\n";
    std::cout << "5. change [new_bank_name] [current_bank_name] [account_number]\n";
    std::cout << "6. list [bank_name]\n";
    std::cout << "7. messages\n";
}

User* Client::clone() const {
    return new Client(*this);
}
