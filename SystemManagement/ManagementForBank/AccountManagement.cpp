#include "AccountManagement.h"
#include <assert.h>

int Account::accNum = 1;

Account::Account() {
    accountNumber = accNum++;
}

size_t Account::getAccountNumber() const {
    return accountNumber;
}

double Account::getBalance() const {
    return balance;
}

void Account::depositMoney(double money) {
    assert(money > 0.0);
    balance += money;
}

void Account::withdrawMoney(double money) {
    assert(money > 0.0 && money <= balance);
    balance -= money;
}

void Account::saveToFile(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&accountNumber), sizeof(accountNumber));
    ofs.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
}

void Account::readFromFile(std::ifstream& ifs) {
    ifs.read(reinterpret_cast< char*>(&accountNumber), sizeof(accountNumber));
    ifs.read(reinterpret_cast< char*>(&balance), sizeof(balance));
}


void AccountManagement::createAccount(const MyString& username) {
    Account newAccount;
    Pair<MyString, Account> newBankAccount(username, newAccount);
    bankAccounts.pushBack(newBankAccount);
}

void AccountManagement::closeAccount(const MyString& username, size_t accNum) {
    int idx = getIndexByAccNumAndUsername(accNum, username);
    bankAccounts.popAt(idx);
}

double AccountManagement::checkBalance(size_t accNum) const {
    size_t index = getIndexByAccNum(accNum);
    return bankAccounts[index].getRhs().getBalance();
}

void AccountManagement::deposit(size_t accountNumber, const MyString& username, double amount) {
    assert(amount > 0);
    int idx = getIndexByAccNumAndUsername(accountNumber, username);
    bankAccounts[idx].getRhs().depositMoney(amount);
}

void AccountManagement::withdraw(size_t accountNumber, const MyString& username, double amount) {
    assert(amount > 0);
    int idx = getIndexByAccNumAndUsername(accountNumber, username);
    bankAccounts[idx].getRhs().withdrawMoney(amount);
}

size_t AccountManagement::getIndexByAccNumAndUsername(size_t accNum, const MyString& username) const {
    int bankAccountsCount = bankAccounts.getSize();
    if (bankAccountsCount == 0) {
        throw std::runtime_error("There are no such accounts.");
    }
    for (size_t i = 0; i < bankAccountsCount; i++) {
        if (bankAccounts[i].getRhs().getAccountNumber() == accNum && bankAccounts[i].getLhs() == username) {
            return i;
        }
    }
    throw std::runtime_error("There is no such account.");
}

size_t AccountManagement::getIndexByAccNum(size_t accNum) const {
    int bankAccountsCount = bankAccounts.getSize();
    if (bankAccountsCount == 0) {
        throw std::runtime_error("There are no accounts existing in that bank.");
    }
    for (size_t i = 0; i < bankAccountsCount; i++) {
        if (bankAccounts[i].getRhs().getAccountNumber() == accNum) {
            return i;
        }
    }
    throw std::runtime_error("There is no such account.");
}

Vector<Pair<MyString, Account>> AccountManagement::getBankAccounts() const {

    return bankAccounts;
}
