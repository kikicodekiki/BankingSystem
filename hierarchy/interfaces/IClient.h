#pragma once
#include "MyString.h"
class IClient {
public:
    virtual void check_avl (const MyString& bankName, const MyString& accountNumber) const = 0;
    virtual void open (const MyString& bankName) = 0;
    virtual void close (const MyString& bankName, const MyString& accountNumber) = 0;
    virtual void redeem (const MyString& bankName, const MyString& accountNumber, const MyString& verificationCode) = 0;
    virtual void change (const MyString& newBankName, const MyString& currBank, const MyString& accNum) = 0;
    virtual void list (const MyString& bankName) const = 0;
    virtual void messages () const = 0;

    virtual ~IClient() = default;
};
