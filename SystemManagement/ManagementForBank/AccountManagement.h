#pragma once
#include "MyString.h"
#include <fstream>
#include "Vector.h"
#include "Pair.h"



class Account {
public:
    Account();

    size_t getAccountNumber() const;
    double getBalance() const;
    void depositMoney(double money);
    void withdrawMoney(double money);
    void saveToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);

private:
    size_t accountNumber = 0;
    double balance = 0.0;
    static int accNum;
};



class AccountManagement {
public:
    void createAccount(const MyString& username);
    void closeAccount(const MyString& username, size_t accNum);

    double checkBalance(size_t accNum) const;
    void deposit(size_t accountNumber, const MyString& username, double amount);
    void withdraw(size_t accountNumber, const MyString& username, double amount);

    Vector<Pair<MyString, Account>> getBankAccounts() const;

private:
    Vector<Pair<MyString, Account>> bankAccounts;
    size_t getIndexByAccNumAndUsername(size_t accNum, const MyString& username) const;
    size_t getIndexByAccNum(size_t accNum) const;
};
