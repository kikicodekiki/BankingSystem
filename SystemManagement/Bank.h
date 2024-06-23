#pragma once
#include "AccountManagement.h"
#pragma once
#include "AccountManagement.h"
#include "UserManagement.h"
#include "Messaging.h"
#include "MyString.h"
#include "Task.h"
#include "BankEmployee.h"
#include "BankCheck.h"

class Bank {
public:
    Bank() = default;

    Bank(const MyString& name);

    const MyString& getName() const;

    // User Management
    void addUser(User* user);
    Polymorphic_Ptr<User> findUser(const MyString& egn) const;
    Polymorphic_Ptr<User> findUser (const size_t arr[EGN_SIZE]) const;


    // Account Management
    bool createAccount(const MyString& accountNumber, double initialBalance, const MyString& ownerEgn);
    bool closeAccount(const MyString& accountNumber);
    double checkBalance(const MyString& accountNumber) const;
    bool transferAccount(const MyString& fromAccount, const MyString& toBank, const MyString& toAccount);

    // Messaging
    void sendMessage(const MyString& userEgn, const MyString& message);
    Vector<MyString> getMessages(const MyString& userEgn) const;

    BankEmployee* getLeastBusyEmployee();
    const BankEmployee* getLeastBusyEmployee() const;

    bool validateClientData (const Client* client, const MyString& accountNumber) const;

    void issueCheck(const MyString& EGN, const BankCheck& check);
    double redeemCheck (const MyString& accountNumber, const MyString& verificationCode);

    void listAccounts (int clientId) ;

private:

    MyString bankName;

    AccountManagement accountManager;
    UserManagement userManager;
    Messaging messaging;

    Vector<BankCheck> issuedChecks;
};
