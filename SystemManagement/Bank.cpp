
#include "Bank.h"
#include "DoubleToString.h"


const Vector<Pair<MyString, Account>>& Bank::getBankAccounts() const {
    return manager.getBankAccounts();
}

void Bank::createAccount(const MyString& username) {
    manager.createAccount(username);
    MyString message = "Account created for " + username;
    messaging.sendMessage(username, message);
}

void Bank::closeAccount(const MyString& username, size_t accNum) {
    manager.closeAccount(username, accNum);

    MyString str1 = "Account with number ";
    MyString str2 = " closed for ";
    MyString message = str1 + toString(accNum) + str2 + username;

    messaging.sendMessage(username, message);
}

double Bank::checkBalance(size_t accNum) const {
    return manager.checkBalance(accNum);
}

void Bank::deposit(size_t accountNumber, const MyString& username, double amount) {
    manager.deposit(accountNumber, username, amount);

    MyString str1 = "Deposited ";
    MyString str2 = " to account number ";

    MyString message = str1 + doubleToString(amount, 5) + str2 + toString(accountNumber);
    messaging.sendMessage(username, message);
}

void Bank::withdraw(size_t accountNumber, const MyString& username, double amount) {
    manager.withdraw(accountNumber, username, amount);

    MyString str1 = "Withdrawn ";
    MyString str2 = " from account number ";

    MyString message = str1 + doubleToString(amount, 2) + str2 + toString(accountNumber);
    messaging.sendMessage(username, message);
}

void Bank::addMessage(const MyString& userEgn, const MyString& message) {
    messaging.sendMessage(userEgn, message);
}

Vector<MyString> Bank::getMessages(const MyString& userEgn) const {
    return messaging.getMessages(userEgn);
}

Employee* Bank::getLeastBusyEmployee() {
    if (employees.getSize() == 0) {
        return nullptr;
    }

    Employee* leastBusy = &employees[0];
    for (size_t i = 1; i < employees.getSize(); ++i) {
        if (employees[i].getNumberOfTasks() < leastBusy->getNumberOfTasks()) {
            leastBusy = &employees[i];
        }
    }
    return leastBusy;
}

void Bank::addEmployee(const Employee& employee) {
    employees.pushBack(employee);
}
