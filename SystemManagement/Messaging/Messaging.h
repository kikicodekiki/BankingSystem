#pragma once
#include "MyString.h"
#include "Vector.h"
#include "IMessaging.h"

class Messaging : public IMessaging {
public:
    void sendMessage(const MyString& userEgn, const MyString& message) override;
    Vector<MyString> getMessages(const MyString& userEgn) const override;

private:
    Vector<MyString> userEgns;
    Vector<Vector<MyString>> userMessages;

    int findUserMessagesIndex(const MyString& userEgn) const;
};
