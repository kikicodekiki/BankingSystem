#pragma once
#include "AccountManagement.h"
#include "Messaging.h"
#include "BankCheck.h"
#include "Employee.h"

class Bank {
public:
    Bank() = default;
    Bank(const MyString& name) : bankName(name) {}

    const Vector<Pair<MyString, Account> >& getBankAccounts() const;
    void createAccount(const MyString& username);
    void closeAccount(const MyString& username, size_t accNum);
    double checkBalance(size_t accNum) const;
    void deposit(size_t accountNumber, const MyString& username, double amount);
    void withdraw(size_t accountNumber, const MyString& username, double amount);
    void addMessage(const MyString& userEgn, const MyString& message);
    Vector<MyString> getMessages(const MyString& userEgn) const;
    const MyString& getBankName() const { return bankName; }

    Employee* getLeastBusyEmployee();
    void addEmployee(const Employee& employee);

private:
    MyString bankName;
    AccountManagement manager;
    Messaging messaging;
    Vector<BankCheck> assignedChecks;
    Vector<Employee> employees;

};
