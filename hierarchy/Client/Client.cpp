#include "Client.h"
#include "Application.h"
#include <iostream>

Client::Client(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age, const MyString& password, const MyString& address)
        : User(firstName, surname, EGN, age, password), address(address) {}

Client::Client(MyString&& firstName, MyString&& surname, MyString&& EGN, unsigned age, MyString&& password, MyString&& address)
        : User(std::move(firstName), std::move(surname), std::move(EGN), age, std::move(password)), address(std::move(address)) {}

void Client::check_avl(const MyString& bankName, const MyString& accountNumber) const {
    Application& app = Application::getInstance();
    app.checkAccountBalance(bankName, accountNumber, id);
}

void Client::open(const MyString& bankName) {
    Application& app = Application::getInstance();
    app.openAccount(bankName, id);
}

void Client::close(const MyString& bankName, const MyString& accountNumber) {
    Application& app = Application::getInstance();
    app.closeAccount(bankName, accountNumber, id);
}

void Client::redeem(const MyString& bankName, const MyString& accountNumber, const MyString& verificationCode) {
    Application& app = Application::getInstance();
    app.redeemCheck(bankName, accountNumber, verificationCode, id);
}

void Client::change(const MyString& newBankName, const MyString& currBank, const MyString& accNum) {
    Application& app = Application::getInstance();
    app.changeAccountBank(newBankName, currBank, accNum, id);
}

void Client::list(const MyString& bankName) const {
    Application& app = Application::getInstance();
    app.listAccounts(bankName, id);
}

void Client::messages() const {
    for (size_t i = 0; i < messageInbox.getSize(); ++i) {
        std::cout << "[" << i + 1 << "] - " << messageInbox[i] << std::endl;
    }
}

void Client::addAccount(const MyString& accountName) {
    bankAccounts.pushBack(accountName);
}

void Client::addMessage(const MyString& message) {
    messageInbox.pushBack(message);
}

void Client::saveToFile(std::ofstream& ofs) const {
    User::saveToFile(ofs);
    ofs << address << '\n';
    ofs << bankAccounts.getSize() << '\n';
    for (size_t i = 0; i < bankAccounts.getSize(); ++i) {
        ofs << bankAccounts[i] << '\n';
    }
    ofs << messageInbox.getSize() << '\n';
    for (size_t i = 0; i < messageInbox.getSize(); ++i) {
        ofs << messageInbox[i] << '\n';
    }
}

void Client::readFromFile(std::ifstream& ifs) {
    User::readFromFile(ifs);
    std::string str;
    std::getline(ifs, str);
    address = MyString(str.c_str());
    size_t size;
    ifs >> size;
    ifs.ignore(); // ignore newline
    for (size_t i = 0; i < size; ++i) {
        std::getline(ifs, str);
        bankAccounts.pushBack(MyString(str.c_str()));
    }
    ifs >> size;
    ifs.ignore(); // ignore newline
    for (size_t i = 0; i < size; ++i) {
        std::getline(ifs, str);
        messageInbox.pushBack(MyString(str.c_str()));
    }
}

Vector<MyString> Client::getAccounts() const {
    return bankAccounts;
}
