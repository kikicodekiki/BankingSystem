#pragma once
#include "Bank.h"
#include "BankEmployee.h"
#include "Application.h"

Bank::Bank(const MyString &name) : bankName(name) {}

const MyString& Bank::getName () const {
    return bankName;
}

void Bank::addUser(User* user) {
    userManager.addUser(Polymorphic_Ptr<User>(user));
}

Polymorphic_Ptr<User> Bank::findUser(const MyString &egn) const {
    return userManager.findUser(egn);
}

Polymorphic_Ptr<User> Bank:: findUser (const size_t arr[EGN_SIZE]) const {
    return userManager.findUserByEgnArray(arr);
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

bool Bank::validateClientData(const Client *client, const MyString &accountNumber) const {
    Polymorphic_Ptr<User> user = findUser(client->getEgn());
    if(!user) {return false;}

    static constexpr double EPS = 1e-9;
    double balance = accountManager.checkBalance(accountNumber);
    return balance >= 0 && balance < EPS;
}

BankEmployee* Bank::getLeastBusyEmployee() {
    BankEmployee* leastBusyEmployee = nullptr;
    for (size_t i = 0; i < userManager.getUsers().getSize(); ++i) {
        BankEmployee* employee = dynamic_cast<BankEmployee*>(userManager.getUsers()[i].get());
        if (employee) {
            if (!leastBusyEmployee || employee->getTaskCount() < leastBusyEmployee->getTaskCount()) {
                leastBusyEmployee = employee;
            }
        }
    }
    return leastBusyEmployee;
}

const BankEmployee* Bank::getLeastBusyEmployee() const {
    const BankEmployee* leastBusyEmployee = nullptr;
    for (size_t i = 0; i < userManager.getUsers().getSize(); ++i) {
        const BankEmployee* employee = dynamic_cast<const BankEmployee*>(userManager.getUsers()[i].get());
        if (employee) {
            if (!leastBusyEmployee || employee->getTaskCount() < leastBusyEmployee->getTaskCount()) {
                leastBusyEmployee = employee;
            }
        }
    }
    return leastBusyEmployee;
}

void Bank::issueCheck(const MyString& EGN, const BankCheck& check) {
    issuedChecks.pushBack(check);
    Application::getInstance().sendCheck(check.getSum(),check.getVerificationCode(), EGN);


}
double Bank::redeemCheck (const MyString& accountNumber, const MyString& verificationCode) {
    for (size_t i = 0; i < issuedChecks.getSize(); ++i) {
        if (strcmp(issuedChecks[i].getVerificationCode(), verificationCode.c_str()) == 0) {

            double amount = issuedChecks[i].getSum();

            if (accountManager.checkBalance(accountNumber) >= 0) {
                accountManager.deposit(accountNumber, amount);
                issuedChecks.popAt(i);
                return amount;
            } else {

                std::cout << "Account not found.\n";
                return -1;
            }
        }
    }

    return -1; // heck not found
}

void Bank::listAccounts (int clientId)  {
    Client* client = dynamic_cast<Client*>(userManager.findClientById(clientId));

    if (!client) {
        std::cout << "Client not found. \n";
        return;
    }

    Vector<MyString> accounts = client->getAccounts();
    if (accounts.getSize() == 0) {
        std::cout << "No accounts found for this client in this bank.\n";
    } else {
        std::cout << "Accounts for client ID " << clientId << ":\n";
        for (size_t i = 0; i < accounts.getSize(); ++i) {
            std::cout << accounts[i].c_str() << "\n";
        }
    }

}

Vector<MyString> Bank::listAllAccounts (int clientId) {
    Client* client = dynamic_cast<Client*>(userManager.findClientById(clientId));

    if (!client) {
        throw std::runtime_error("Client not found\n");
    }

    Vector<MyString> accounts = client->getAccounts();
    return accounts;
}
