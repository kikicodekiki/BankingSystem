#include "AccountManagement.h"
#include "Bank.h"
#include "Task.h"
#include "Application.h"

bool AccountManagement::createAccount(const MyString& accountNumber, double initialBalance, const MyString& ownerEgn) {
    if (findAccountIndex(accountNumber) != -1) {
        return false; // Account already exists
    }
    accountNumbers.pushBack(accountNumber);
    accountBalances.pushBack(initialBalance);
    accountOwners.pushBack(ownerEgn);
    return true;
}

bool AccountManagement::closeAccount(const MyString& accountNumber) {
    int index = findAccountIndex(accountNumber);
    if (index == -1) {
        return false; // Account does not exist
    }
    accountNumbers.popAt(index);
    accountBalances.popAt(index);
    accountOwners.popAt(index);
    return true;
}

double AccountManagement::checkBalance(const MyString& accountNumber) const {
    int index = findAccountIndex(accountNumber);
    if (index == -1) {
        return -1.0; // Account does not exist
    }
    return accountBalances[index];
}

bool AccountManagement::transferAccount(const MyString& fromAccount, const MyString& toBank, const MyString& toAccount) {
    int index = findAccountIndex(fromAccount);
    if (index == -1) {
        return false; // Account does not exist
    }
    double balance = accountBalances[index];
    MyString ownerEgn = accountOwners[index];
    accountNumbers.popAt(index);
    accountBalances.popAt(index);
    accountOwners.popAt(index);

    // Assuming the toBank object is accessible and can add the account
    Bank* targetBank = Application::getInstance().findBank(toBank);
    if (targetBank) {
        targetBank->createAccount(toAccount, balance, ownerEgn);
        return true;
    }
    return false;
}

int AccountManagement::findAccountIndex(const MyString& accountNumber) const {
    for (size_t i = 0; i < accountNumbers.getSize(); ++i) {
        if (accountNumbers[i] == accountNumber) {
            return i;
        }
    }
    return -1;
}

bool AccountManagement::validate(const MyString& taskId) const {

}
