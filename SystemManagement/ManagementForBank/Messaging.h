#pragma once
#include "MyString.h"
#include "Vector.h"

class Messaging {
public:
    void sendMessage(const MyString& userEgn, const MyString& message);
    Vector<MyString> getMessages(const MyString& userEgn) const;

private:
    Vector<MyString> userEgns;
    Vector<Vector<MyString>> userMessages;

    int findUserMessagesIndex(const MyString& userEgn) const;
};
