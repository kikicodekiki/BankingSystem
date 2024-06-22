#pragma once
#include "MyString.h"

class IAccountManagement {
public:
    virtual bool createAccount(const MyString& accountNumber, double initialBalance, const MyString& ownerEgn) = 0;
    virtual bool closeAccount(const MyString& accountNumber) = 0;
    virtual double checkBalance(const MyString& accountNumber) const = 0;
    virtual bool transferAccount(const MyString& fromAccount, const MyString& toBank, const MyString& toAccount) = 0;
    virtual ~IAccountManagement() = default;
};
