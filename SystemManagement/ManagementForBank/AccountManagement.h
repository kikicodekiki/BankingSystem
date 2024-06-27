#pragma once
#include "IAccountManagement.h"
#include "MyString.h"
#include "Vector.h"
#include "BankEmployee.h"

class AccountManagement : public IAccountManagement {
public:
    AccountManagement() = default;

    bool createAccount(const MyString& accountNumber, double initialBalance, const MyString& ownerEgn) override;
    bool closeAccount(const MyString& accountNumber) override;
    double checkBalance(const MyString& accountNumber) const override;
    bool transferAccount(const MyString& fromAccount, const MyString& toBank, const MyString& toAccount) override;

//    bool validate(const MyString& accountNumber, const MyString& ownerEgn) const;

protected:
    struct Account {
        MyString accountNumber;
        double balance = 0.0;
        MyString ownerEGN;

        Account(const MyString& accountNumber, double balance, const MyString& ownerEgn)
                : accountNumber(accountNumber), balance(balance), ownerEGN(ownerEgn) {}

        Account() = default;

        void saveToFIle ( std::ofstream& ofs ) const;
        void readFromFile (std::ifstream& ifs);
    };

    Vector<Account> accounts;

//    int findAccountIndex(const MyString& accountNumber) const;
};
