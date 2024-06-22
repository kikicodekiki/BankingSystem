#pragma once
#include "MyString.h"
#include "Vector.h"

class IMessaging {
public:
    virtual void sendMessage(const MyString& userEgn, const MyString& message) = 0;
    virtual Vector<MyString> getMessages(const MyString& userEgn) const = 0;
    virtual ~IMessaging() = default;
};
