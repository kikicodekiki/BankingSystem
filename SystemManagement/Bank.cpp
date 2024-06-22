#include "Bank.h"

Bank::Bank(const MyString &name) : bankName(name) {}

const MyString& Bank::getName () const {
    return bankName;
}

void Bank::addUser(Polymorphic_Ptr<User> user) {
    userManager.addUser(user);
}

Polymorphic_Ptr<User> Bank::findUser(const MyString &egn) const {
    return userManager.findUser(egn);
}

bool Bank::createAccount(const MyString &accountNumber, double initialBalance, const MyString &ownerEgn) {
    return accountManager.createAccount(accountNumber, initialBalance, ownerEgn);
}

bool Bank::closeAccount(const MyString &accountNumber) {
    return accountManager.closeAccount(accountNumber);
}

double Bank::checkBalance(const MyString &accountNumber) const {
    return accountManager.checkBalance(accountNumber);
}

bool Bank::transferAccount(const MyString& fromAccount, const MyString& toBank, const MyString& toAccount) {
    return accountManager.transferAccount(fromAccount, toBank, toAccount);
}

void Bank::sendMessage(const MyString& userEgn, const MyString& message) {
    messaging.sendMessage(userEgn, message);
}

Vector<MyString> Bank::getMessages(const MyString& userEgn) const {
    return messaging.getMessages(userEgn);
}
