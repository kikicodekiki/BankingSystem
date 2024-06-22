#pragma once
#include "AccountManagement.h"
#include "UserManagement.h"
#include "Messaging.h"
#include "MyString.h"



class Bank {
public:
    Bank() = default;

    Bank(const MyString& name);

    const MyString& getName() const;

    // User Management
    void addUser(Polymorphic_Ptr<User> user);
    Polymorphic_Ptr<User> findUser(const MyString& egn) const;

    // Account Management
    bool createAccount(const MyString& accountNumber, double initialBalance, const MyString& ownerEgn);
    bool closeAccount(const MyString& accountNumber);
    double checkBalance(const MyString& accountNumber) const;
    bool transferAccount(const MyString& fromAccount, const MyString& toBank, const MyString& toAccount);

    // Messaging
    void sendMessage(const MyString& userEgn, const MyString& message);
    Vector<MyString> getMessages(const MyString& userEgn) const;

private:

    MyString bankName;

    AccountManagement accountManager;
    UserManagement userManager;
    Messaging messaging;
};
