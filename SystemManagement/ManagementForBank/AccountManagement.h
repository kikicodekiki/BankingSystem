#pragma once
#include "IAccountManagement.h"
#include "MyString.h"
#include "Vector.h"
#include "BankEmployee.h"

class AccountManagement : public IAccountManagement {
public:
    bool createAccount(const MyString& accountNumber, double initialBalance, const MyString& ownerEgn) override;
    bool closeAccount(const MyString& accountNumber) override;
    double checkBalance(const MyString& accountNumber) const override;
    bool transferAccount(const MyString& fromAccount, const MyString& toBank, const MyString& toAccount) override;

    bool validate(const MyString& taskId) const;

    AccountManagement() = default;

private:
    Vector<MyString> accountNumbers;
    Vector<double> accountBalances;
    Vector<MyString> accountOwners;

    int findAccountIndex(const MyString& accountNumber) const;
};

